#ifndef LOGICAREAEFFECTSERVER_H
#define LOGICAREAEFFECTSERVER_H

#include "LogicGameObjectServer.h"
#include "LogicBattleModeServer.h"
#include "Hook.h"
#include "LogicCharacterServer.h"
#include "LogicGamePlayUtil.h"

class LogicAreaEffectServer : public LogicGameObjectServer
{
public:
	int StartingTick;//76
	int EndingTick;//80
	int LifeTimeConsumedPromille;//84
	char gap9832[4];
	int EffectTimer;//92
	int Damage;//96
	int DamageConst;//100
	int DamageOverTime;//104
	bool ShouldDestruct;//108
	char ga3278437[120 - 108 - 1];
	int FadeCounter;//120
	char gap197846[128 - 120 - 4];
	LogicCharacterServer* Owner;//128
	void setSource(LogicCharacterServer* source, int skillType, bool idk) {
		return ((void (*)(LogicAreaEffectServer*, LogicCharacterServer*, int, int))(base + 0x87E78C))(this, source, skillType, idk);
	}
	void trigger() {
		return ((void (*)(LogicAreaEffectServer*))(base + 0x87E7A0))(this);
	}
	void tick();
};
void LogicAreaEffectServer::tick() {
	int ticksGone = getLogicBattleModeServer()->getTicksGone();
	if (EndingTick - ticksGone < 10) {
		FadeCounter = LogicMath::max(0, EndingTick - ticksGone);
	}
	LifeTimeConsumedPromille = (ticksGone - StartingTick) * 1000 / (EndingTick - StartingTick);
	if (ticksGone >= EndingTick) {
		ShouldDestruct = true;
		return;
	}
	LogicAreaEffectData* data = (LogicAreaEffectData*)getData();
	int type = data->Type;
	if (type == 2 || type == 4 || type == 8 || type == 10 || type == 19 || type == 22) {
		if (++EffectTimer < (type == 22 || type == 19 ? 1 : 20)) return;
		EffectTimer = 0;
		LogicArrayList<LogicCharacterServer*> characters;
		GameObjectManager->getCharacters(&characters);
		for (int i = 0;i < characters.length;i++) {
			LogicCharacterServer* character = characters[i];
			bool teamFlag = (type == 2 || type == 8 || type == 19 || type == 22) ? character->TeamIndex != TeamIndex : character->TeamIndex == TeamIndex && ((LogicCharacterData*)character->getData())->isHero();
			bool specialFlag = type == 2 && Owner && Owner->getCardValueForPassive(5, 1) >= 0 && character->Index == Index;//滋养之地
			if ((teamFlag || specialFlag) && character->isAlive() && !character->isImmuneAndBulletsGoThrough()) {
				if (LogicGamePlayUtil::getDistanceBetween(getX(), getY(), character->getX(), character->getY()) <= data->getRadius() + character->getRadius() - 50) {
					switch (data->Type) {
					case 22:
						if (!character->IsInvincible && character->DelayedDeathTicks <= 0) {
							character->giveSlipperyDebuff(0, 4);
							character->setPartialStunPromille(character->PartialStunPromille + data->getCustomValue2());
						}
						break;
					}
				}
			}
		}
	}
	if (type == 28 || type == 32) {
		if (++EffectTimer < 20) return;
		EffectTimer = 0;
		LogicArrayList<LogicCharacterServer*> characters;
		GameObjectManager->getCharacters(&characters);
		for (int i = 0;i < characters.length;i++) {
			LogicCharacterServer* character = characters[i];
			bool teamFlag = type == 28 ? character->TeamIndex != TeamIndex : character->TeamIndex == TeamIndex;
			if (teamFlag && character->isAlive() && !character->isImmuneAndBulletsGoThrough()) {
				if (LogicGamePlayUtil::getDistanceBetween(getX(), getY(), character->getX(), character->getY()) <= data->getRadius() + character->getRadius() - 50) {
					Owner->chargeUlti(data->getCustomValue(), false, true, getPlayer(), Owner);
				}
			}
		}
	}
}
#endif