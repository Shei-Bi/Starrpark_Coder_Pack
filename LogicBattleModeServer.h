#ifndef LBMS_H
#define LBMS_H
#include "Hook.h"
#include "LogicTileMap.h"
#include "LogicPathFinder.h"
#include "LogicGameObjectManagerServer.h"
#include "LogicGameModeUtil.h"
#include "LogicGameObjectFactoryServer.h"

class LogicBattleModeServer
{
private:
	/* data */
public:
	static const int INTRO_TICKS = 182;

	LogicGameObjectManagerServer* GameObjectManager;
	char gap1[164 - 8];
	int GameType;//164
	char gap13746394[228 - 164 - 4];
	int GameModeVariation;//228
	int getTicksGone() {
		return ((int (*)(LogicBattleModeServer*))(base + 0x9458E0))(this);
	}
	int getTick() {
		/*
			����������û���κε����𡣵���Դ����ǰ��ʹ�õ�Ƶ�ʽ�Ϊ���ߵ��߷�֮һ��
			--Shei
		*/
		return getTicksGone();
	}
	LogicTileMap* getTileMap() {
		return ((LogicTileMap * (*)(LogicBattleModeServer*))(base + 0x94A448))(this);
	}
	LogicPathFinder* getPathFinder() {
		return ((LogicPathFinder * (*)(LogicBattleModeServer*))(base + 0x94E278))(this);
	}
	LogicPlayer* getPlayer(int index) {
		if (index < 0 || index >= *(int*)((char*)this + 132)) {
			return nullptr;
		}
		return *(LogicPlayer**)(*(char**)((char*)this + 120) + 8 * index);
	}
	int getRandomInt(int max) {
		return ((int (*)(LogicBattleModeServer*, int))(base + 0x9489E4))(this, max);
	}
	LogicCharacterServer* spawnHero(LogicCharacterData*, LogicHeroUpgrades*, int, int, int, bool);
};
LogicCharacterServer* LogicBattleModeServer::spawnHero(LogicCharacterData* character, LogicHeroUpgrades* upgrades, int index, int teamIndex, int worldIndex, bool isBot) {
	LogicPlayer* player = getPlayer(index);
	if (player) {
		player->PetCharacterSkin = nullptr;
		if (character->getUniqueProperty() == 2 || character->getUniqueProperty() == 7) {//梅格邦妮 Meg and Bonnie
			LogicSkinData* skinData = player->getCurrentHeroSetup()->Skin;
			if (skinData) player->PetCharacterSkin = skinData->getPetSkin();//人机梅格可能没有皮肤数据
		}
	}
	LogicCharacterServer* hero = (LogicCharacterServer*)LogicGameObjectFactoryServer::createGameObjectByData(character);
	GameObjectManager->addLogicGameObject(hero);
	hero->Index = index;
	hero->TeamIndex = teamIndex;
	hero->WorldIndex = worldIndex;
	hero->IsBot = isBot;
	hero->setUpgrades(upgrades);
	hero->SpawnedTicks = getTicksGone();
	hero->setDefaultStartRotation();
	if (LogicGameModeUtil::playersCollectBountyStars(GameModeVariation) && GameType != 5) hero->CoinsHeld = 2;
	if (LogicGameModeUtil::hasSpawnProtectionInTheStart(GameModeVariation)) {
		hero->SpawnTick = INTRO_TICKS + getTicksGone();
		hero->IsInvincible = hero->SpawnTick > 0;
	}
	if (player && character->getUltiChargeInitial() > 0) {
		player->UltiCharge = player->UltiChargeMax * character->getUltiChargeInitial() / 100;
	}
	if (character->getUniqueProperty() == 11) {
		hero->swapSkillTo(1, hero->getNextChesterUlti(hero->getUltiSkill(), true));
		hero->ChesterNextUlti = hero->getNextChesterUlti(hero->getUltiSkill(), false);
	}
	if (character->getAreaEffect()) {
		hero->addAreaEffect(0, 0, nullptr, 0, false);
	}
	return hero;
}
#endif