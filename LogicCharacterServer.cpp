#include "LogicCharacterServer.h"
#include "LogicArrayList.h"
#include "LogicSkillData.h"
#include "LogicSkillServer.h"
#include "LogicAccessory.h"
#include "LogicProjectileServer.h"
#include "LogicCharacterData.h"
#include "LogicBuffServer.h"
#include "LogicHeroUpgrades.h"
#include "LogicGear.h"

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
void LogicCharacterServer::addExtraHealthRegen(int healPerSecond, int durationTicks, int healerIndex, LogicData* source) {
	LogicCharacterServer::applyBuff(LogicBuffServer::HealthRegen, durationTicks, healPerSecond, healerIndex);
}
void LogicCharacterServer::blockHealthRegen()
{
	HealthRegenBlockedTick = getLogicBattleModeServer()->getTicksGone();
}
void LogicCharacterServer::tickEffects() {
	for (int i = 0;i < Buffs.length;i++) {
		if (Buffs[i]->tick(this)) {
			Buffs.remove(i);
		}
	}
}
void LogicCharacterServer::setUpgrades(LogicHeroUpgrades* upgrades) {
	if (!upgrades) return;//�˻�û������
	if (upgrades->GearData1) Gears.add(new LogicGear(upgrades->GearData1));
	if (upgrades->GearData2) Gears.add(new LogicGear(upgrades->GearData2));
}
void LogicCharacterServer::applyBuff(int type, int duration, int modifier, int int1) {
	if (Buffs.length < 1 || LogicBuffServer::canBuffStack(type)) {
		Buffs.add(new LogicBuffServer(type, duration, modifier, int1));
		return;
	}
	for (int i = 0;i < Buffs.length;i++) {
		LogicBuffServer* buff = Buffs[i];
		if (buff->Type == type && (buff->Duration < duration || buff->Modifier < modifier)) {
			buff->Modifier = modifier;
			buff->Int1 = int1;
			buff->Duration = duration;
			return;
		}
	}
	Buffs.add(new LogicBuffServer(type, duration, modifier, int1));
}
void LogicCharacterServer::giveDamageBuff(int modifier, int duration) {
	LogicCharacterServer::applyBuff(LogicBuffServer::Damage, duration, modifier, 0);
}
void LogicCharacterServer::tickGears() {
	for (int i = 0;i < Gears.length;i++) {
		Gears[i]->tick(this);
	}
}
int LogicCharacterServer::getDamageBuffTemporary() {
	int damageBuff = 0;
	for (int i = 0;i < Buffs.length;i++) {
		if (Buffs[i]->Type == LogicBuffServer::Damage || Buffs[i]->Type == LogicBuffServer::Damage2 || Buffs[i]->Type == LogicBuffServer::DamageAndSize) damageBuff += Buffs[i]->Modifier;
	}
	return damageBuff;
}
int LogicCharacterServer::getBuffBoost(int type) {
	/*
		New Function. Reason: Repeated Usage.
		--Shei
	*/
	int buff = 0;
	for (int i = 0;i < Buffs.length;i++) {
		if (Buffs[i]->Type == type) buff += Buffs[i]->Modifier;
	}
	return buff;
}
void LogicCharacterServer::giveSpeedFasterBuff(int modifier, int duration, bool haveVisualEffects) {
	//todo: visual effects
	LogicCharacterServer::applyBuff(LogicBuffServer::SpeedFaster, duration, modifier, 0);
}