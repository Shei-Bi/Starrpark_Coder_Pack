#include "LogicCharacterServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicSkillServer.h"
#include "LogicAccessory.h"
#include "LogicProjectileServer.h"
#include "LogicCharacterData.h"
void LogicCharacterServer::addConsumableShield(int amount)
{
	;
}
void LogicCharacterServer::tick()
{
	addConsumableShield(114514);
}
int LogicCharacterServer::getCardValueForPassive(int type, int index) {
	return -1;
}
LogicSkillData* LogicCharacterServer::getCurrentCastingSkill() {
	if (Skills.length < 1) return nullptr;
	for (int i = 0;i < Skills.length;i++) {
		LogicSkillServer* skill = Skills[i];
		if (skill->ActiveTime >= 1 || skill->OnActivate && skill->SkillData->getCastingTime() > 0) return skill->SkillData;
	}
	return nullptr;
}
void LogicCharacterServer::interruptAllSkills(bool ignoreAccessory) {
	return ((void (*)(LogicCharacterServer*, bool))(base + 0x88DFEC))(this, ignoreAccessory);
}
void LogicCharacterServer::stopMovement() {
	MoveStartTick = getLogicBattleModeServer()->getTicksGone() - 1;
	MoveEndTick = MoveStartTick;
}
int LogicCharacterServer::getMoveAngle()
{
	return MoveAngle;
}
void LogicCharacterServer::setForcedAngle(int angle)
{
	MoveAngle = angle;
	ShootAngle = angle;
	ForcedAngleEndTick = getLogicBattleModeServer()->getTick();
}
void LogicCharacterServer::calculateChargeUp() {
	if (Skills.length >= 2) {
		if (Skills[0]->SkillData->getChargeSpeed() > 0 && Skills[0]->SkillData->getChargeType() == 0) {
			ChargeUpType = 1;
			ChargeUpMax = Skills[0]->SkillData->getChargeSpeed();
			return;
		}
		if (Skills[1]->SkillData->getChargeType() == 15) {
			ChargeUpType = 7;
			ChargeUpMax = Skills[1]->SkillData->getActiveTime();
			ChargeUp = 0;
			return;
		}
	}
	LogicCharacterData* characterData = (LogicCharacterData*)getData();
	switch (characterData->getUniqueProperty())
	{
	case 1:
		ChargeUpMax = 1000;
		ChargeUpType = 8;
		break;
	case 3:
		ChargeUpType = 1;
		ChargeUpMax = characterData->getUniquePropertyValue1() * 50;
		break;
	case 10:
		ChargeUpType = 9;
		ChargeUpMax = characterData->getUniquePropertyValue1();
		break;
	case 12:
		ChargeUpType = 10;
		ChargeUpMax = characterData->getUniquePropertyValue1();
		break;
	case 17:
		ChargeUpType = 6;
		ChargeUpMax = characterData->getUniquePropertyValue1();
		break;
	}
	if (getPlayer() && getPlayer()->Accessory && getPlayer()->Accessory->AccessoryData->getShowCountdown()) {
		ChargeUpType = 7;
		ChargeUpMax = getPlayer()->Accessory->AccessoryData->getActiveTicks() * 50;
	}
}
int LogicCharacterServer::heal(int healerIndex, int amount, bool shouldShow, LogicData* source) {
	return ((int (*)(LogicCharacterServer*, int, int, bool, LogicData*))(base + 0x88E6F4))(this, healerIndex, amount, shouldShow, source);
}
void LogicCharacterServer::addExtraHealthRegen(int healPerSecond, int durationTicks,int healerIndex,LogicData* source) {
	Buffs.add(new LogicBuffServer(9, durationTicks, healPerSecond, healerIndex));
}