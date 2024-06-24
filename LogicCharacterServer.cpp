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
#include "LogicPathFinder.h"
#include "LogicAreaEffectData.h"
#include "LogicGameObjectFactoryServer.h"
#include "LogicAreaEffectServer.h"

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
	AttackAngle = angle;
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
void LogicCharacterServer::ensurePathOk(LogicPathFinder* pathFinder) {
	((void (*)(LogicCharacterServer*, LogicPathFinder*))(base + 0x89A180))(this, pathFinder);
}
int LogicCharacterServer::getPathLength() {
	int length = 0;
	for (int i = 1;i < PathPointsX.length;i++) {
		int dx = PathPointsX[i] - PathPointsX[i - 1];
		int dy = PathPointsY[i] - PathPointsY[i - 1];
		length += LogicMath::sqrt(dx * dx + dy * dy);
	}
	return length;
}
void LogicCharacterServer::chargeTo(int x, int y, int speed, LogicPathFinder* pathFinder, LogicArrayList<LogicVector2*>* presetWaypoints) {
	((void (*)(LogicCharacterServer*, int, int, int, LogicPathFinder*, LogicArrayList<LogicVector2*>*))(base + 0x89A6BC))(this, x, y, speed, pathFinder, presetWaypoints);

}
void LogicCharacterServer::triggerCharge(int x, int y, int damage, int damageConst, int pushback, int speed, bool useSpecialPathfinding, int type, LogicAreaEffectData* spawnedAreaEffect, LogicItemData* spawnedItem, int itemParams1, int itemParams2, int range, bool isUlti, LogicArrayList<LogicVector2*>* presetWaypoints, LogicAreaEffectData* spawnedAreaEffect2) {
	if (Index >= 0)
		;//do anti teaming stuff
	if (!isUlti && ChargeUpType == 1) ChargeUp = 0;//腹蛇出洞！
	if (getCardValueForPassive(94, 1) >= 1) addShield(getCardValueForPassive(94, 0), getCardValueForPassive(94, 1));
	UsingUlti = isUlti;
	Stunned = false;
	Knockbacked = false;
	ChargeHits = 0;
	if (type == 10) {
		//Colette.
		int deltaX = x - GetX();
		int deltaY = y - GetY();
		int distance = LogicMath::sqrt(deltaX * deltaX + deltaY * deltaY);
		if (distance > 0) {
			deltaX = deltaX * 100 * range / distance;
			deltaY = deltaY * 100 * range / distance;
		}
		clearPath();
		PathPointsX.add(GetX());
		PathPointsY.add(GetY());
		PathPointsX.add(GetX() + deltaX);
		PathPointsY.add(GetY() + deltaY);
		PathPointsX.add(GetX());
		PathPointsY.add(GetY());
		ensurePathOk(getLogicBattleModeServer()->getPathFinder());
		Pathlength = getPathLength();
		if (Pathlength > 0) {
			MoveStartTick = getLogicBattleModeServer()->getTicksGone();
			MoveEndTick = MoveStartTick + LogicMath::max(1, 20 * Pathlength / speed);
		}
	}
	else if (type != 7) {
		if (useSpecialPathfinding) {
			if (type == 2 || type == 6) {
				int deltaX = x - GetX();
				int deltaY = y - GetY();
				int distance = LogicMath::sqrt(deltaX * deltaX + deltaY * deltaY);
				speed = LogicMath::max(1, distance * speed / 3000);
			}
			chargeTo(x, y, speed, getLogicBattleModeServer()->getPathFinder(), nullptr);
		}
	}
	if (getCardValueForPassive(22, 1) > 0) addShield(getCardValueForPassive(22, 1), getCardValueForPassive(22, 0));
	if (getCardValueForPassive(54, 1) > 0) giveReloadBuff(getCardValueForPassive(54, 1), 100);
	Charging = true;
	TravelSpeed = speed;
	ChargeDamage = damage;
	ChargeDamageConst = damageConst;
	ChargePercentDamage = 0;
	ChargePushback = pushback;
	ChargeType = type;
	ChargeChainDistance = range;
	if (type == 6) {
		;//piper.
	}
	else if (type == 2) {
		LogicAreaEffectServer* areaEffect = (LogicAreaEffectServer*)LogicGameObjectFactoryServer::createGameObjectByData(spawnedAreaEffect);
		areaEffect->setPosition(GetX(), GetY(), 0);
		areaEffect->Index = Index;
		areaEffect->TeamIndex = TeamIndex;
		areaEffect->WorldIndex = WorldIndex;
		areaEffect->setSource(this, 2, false);
		areaEffect->Damage = damage;
		areaEffect->DamageConst = damageConst;
		//todo: prey on the weak && cripple

		GameObjectManager->addLogicGameObject(areaEffect);
		areaEffect->trigger();
		ChargeEndAreaEffect = spawnedAreaEffect;
		ChargeEndAreaEffectDamage = damage;
		ChargeEndAreaEffectDamageConst = 114514;
	}
}
void LogicCharacterServer::addShield(int ticks, int percent) {
	/*
Supercell only used this function once.
--Shei
	*/
	ShieldTicks = ticks;
	ShieldPercent = percent;
}
void LogicCharacterServer::clearPath() {
	/*
Should keep calling LogicCharacterServer::popTarget until PathPointsX.length == 0,
since LogicCharacterServer::popTarget is only referenced as inline of this function
we will just keep this one.
	*/
	PathPointsX.length = 0;
	PathPointsY.length = 0;
}
void LogicCharacterServer::giveReloadBuff(int percent, int ticks) {
	/*
added in v30;
before v30 only ReloadBuffTicks is used since all reload buffs are 100%
	*/
	ReloadBuffTicks = ticks;
	ReloadBuffPercent = percent;
}
bool LogicCharacterServer::isPlayerControlRemoved() {
	return ((bool (*)(LogicCharacterServer*))(base + 0x888324))(this);
}
void LogicCharacterServer::encode(BitStream* stream, bool isOwn, int fadeCounter, int index, bool isOwnTeam) {
	LogicGameObjectServer::encode(stream, fadeCounter);
	if (!IsObject) {
		if (isOwn) {
			bool isPlayerControlRemoved = stream->writeBoolean(isPlayerControlRemoved());
			bool hasForcedAngle = stream->writeBoolean(ForcedAngleEndTick + 1 >= getLogicBattleModeServer()->getTick());
			if (isPlayerControlRemoved || hasForcedAngle) {
				stream->writePositiveIntMax511(AttackAngle);
				stream->writePositiveIntMax511(MoveAngle);
			}
		}
		else {
			stream->writePositiveIntMax511(AttackAngle);
			stream->writePositiveIntMax511(MoveAngle);
		}
		stream->writePositiveIntMax7(State);
		stream->writeBoolean(false);
		stream->writeIntMax63(AttackAnimation);
		stream->writeBoolean(false);
		if (stream->writeBoolean(false)) stream->writeBoolean(false);
		stream->writeBoolean(false);
		stream->writeBoolean(false);
	}
	stream->writePositiveVIntMax65535OftenZero(ProjectileEffectId);
	stream->writePositiveVIntMax65535OftenZero(SkinEffectId);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writePositiveVIntMax255OftenZero(0);
}