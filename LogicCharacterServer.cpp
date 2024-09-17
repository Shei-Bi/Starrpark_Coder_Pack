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
#include "LogicGameModeUtil.h"
#include "LogicGamePlayUtil.h"
#include "LogicPoisonServer.h"
#include "GlobalID.h"

LogicSkillData* LogicCharacterServer::getUltiSkill() {
	if (Skills.length >= 2) return Skills[1]->SkillData;
	return ((LogicCharacterData*)getData())->UltiSkill;
}
void LogicCharacterServer::addConsumableShield(int amount)
{
	;
}
void LogicCharacterServer::tick()
{
	LogicCharacterData* data = (LogicCharacterData*)getData();
	if (data->isTrain()) tickTrain();
	if (isAlive()) {
		tickTimers();
		tickGears();
		tickStarPowers();
		executeBlink();
		handleDynamicWallClearing();
		pushOutOfWalls();
		tickSkills();
		tickTile();
		tickInvisibility();
		tickHeals();
		handleMoveAndAttack();
		tickSpawnMinions();
		tickEffects();
		handleDelayedDeath();
		tickDuplicatorAndCocconAndMinionPercenter();
		tickMovePet();
		executeKickBack();
		tickAutoUltiCharge();
		tickGameModeLogic();
		tickAntiTeaming();
		tickSelfDestruct();
		tickConductor();
		if (AreaEffect) {
			AreaEffect->setPosition(getX(), getY(), 0);
		}
	}
	else {
		InvisibleTicks = 0;
		IsInvisible = false;
		IsRevealed = false;
		DestructAfterTicks--;
		ShadowRealmTicks = 0;
		ShadowRealmWorldIndex = 0;
	}
}
void LogicCharacterServer::tickTrain() {
	;
}
void LogicCharacterServer::tickStarPowers() {
	;
}
void LogicCharacterServer::handleDynamicWallClearing() {
	;
}
void LogicCharacterServer::pushOutOfWalls() {
	;
}
void LogicCharacterServer::tickInvisibility() {
	;
}
void LogicCharacterServer::tickSpawnMinions() {
	;
}
void LogicCharacterServer::tickMovePet() {
	;
}
void LogicCharacterServer::executeKickBack() {
	;
}
void LogicCharacterServer::tickAutoUltiCharge() {
	if (State == 4) return;
	int chargeUltiAutomatically = ((LogicCharacterData*)getData())->getChargeUltiAutomatically();
	if (chargeUltiAutomatically > 0) {
		if (--AutoUltiChargeTimer <= 0) {
			if (getPlayer()) {
				chargeUlti(chargeUltiAutomatically / 4, false, true, getPlayer(), this);
			}
			AutoUltiChargeTimer = 5;
		}
	}
}
void LogicCharacterServer::tickGameModeLogic() {
	;
}
void LogicCharacterServer::tickAntiTeaming() {
	;
}
void LogicCharacterServer::tickTimers() {
	return ((void (*)(LogicCharacterServer*))(base + 0x888834))(this);
}
void LogicCharacterServer::tickSkills() {
	return ((void (*)(LogicCharacterServer*))(base + 0x888D98))(this);
}
void LogicCharacterServer::tickTile() {
	return ((void (*)(LogicCharacterServer*))(base + 0x8891AC))(this);
}
void LogicCharacterServer::tickHeals() {
	return ((void (*)(LogicCharacterServer*))(base + 0x889528))(this);
}
void LogicCharacterServer::handleMoveAndAttack() {
	return ((void (*)(LogicCharacterServer*))(base + 0x8896EC))(this);
}
void LogicCharacterServer::handleDelayedDeath() {
	return ((void (*)(LogicCharacterServer*))(base + 0x88BDD4))(this);
}
void LogicCharacterServer::tickSelfDestruct() {
	return ((void (*)(LogicCharacterServer*))(base + 0x88C0D4))(this);
}
void LogicCharacterServer::tickDuplicatorAndCocconAndMinionPercenter() {
	return ((void (*)(LogicCharacterServer*))(base + 0x88BF14))(this);
}
void LogicCharacterServer::tickConductor() {
	return ((void (*)(LogicCharacterServer*))(base + 0x88C400))(this);
}
void LogicCharacterServer::applyPoison(int index, int damage, int damageConst, bool isUlti, LogicCharacterServer* source, int type, int tickCount) {
	if (LogicPoisonServer::allowStacking(type)) goto LABEL_1;
	for (int i = 0;i < Poisons.length;i++) {
		LogicPoisonServer* poison = Poisons[i];
		if (poison->Type == type && poison->EffectTimes * poison->Damage < damage) {
			poison->refreshPoison(type, damage, damageConst, tickCount, isUlti);
			return;
		}
	}
LABEL_1:
	Poisons.add(new LogicPoisonServer(damage, damageConst, tickCount, isUlti, source, index, type));
}
int LogicCharacterServer::getCardValueForPassive(int type, int index) {
	return getCardValueForPassiveFromPlayer(type, index);
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
		if (getCardValueForPassive(122, 1) >= 1) ChargeUpMax -= 50 * getCardValueForPassive(122, 1);
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
	LogicPlayer* player = getPlayer();
	if (player) {
		if (getCardValueForPassive(60, 1) >= 0) {
			ChargeUpType = 2;
			ChargeUpMax = getCardValueForPassive(60, 3);
			return;
		}
		if (getCardValueForPassive(66, 1) >= 0) {
			ChargeUpType = 3;
			ChargeUpMax = getCardValueForPassive(66, 2);
			return;
		}
		if (getCardValueForPassive(67, 1) >= 0) {
			ChargeUpType = 4;
			ChargeUpMax = getCardValueForPassive(67, 1);
			ChargeUp = ChargeUpMax;
			return;
		}
		if (getCardValueForPassive(82, 1) >= 0) {
			ChargeUpType = 6;
			ChargeUpMax = getCardValueForPassive(82, 1);
			return;
		}
		if (getCardValueForPassive(132, 1) >= 0) {
			ChargeUpType = 6;
			ChargeUpMax = getCardValueForPassive(132, 1);
			return;
		}
		if (getCardValueForPassive(101, 1) >= 0) {
			ChargeUpType = 6;
			ChargeUpMax = getCardValueForPassive(101, 1) * 50;
			return;
		}
		if (getCardValueForPassive(129, 1) >= 0) {
			ChargeUpType = 6;
			ChargeUpMax = getCardValueForPassive(129, 1) * 50;
			return;
		}
		if (getCardValueForPassive(131, 1) >= 0) {
			ChargeUpType = 6;
			ChargeUpMax = getCardValueForPassive(131, 1) * 50;
			return;
		}
		if (getCardValueForPassive(183, 1) >= 0) {
			ChargeUpType = 12;
			ChargeUpMax = getCardValueForPassive(183, 1) * 50;
			return;
		}
		if (player->Accessory && player->Accessory->AccessoryData->getShowCountdown()) {
			ChargeUpType = 7;
			ChargeUpMax = player->Accessory->AccessoryData->getActiveTicks() * 50;
		}
	}
}
LogicSkillData* LogicCharacterServer::getNextChesterUlti(LogicSkillData* orginal, bool shouldBeDifferentFromOrginal) {
	return ((LogicSkillData * (*)(LogicCharacterServer*, LogicSkillData*, bool))(base + 0x8A4F58))(this, orginal, shouldBeDifferentFromOrginal);
}
bool LogicCharacterServer::heal(int healerIndex, int amount, bool shouldShow, LogicData* source) {
	return ((bool (*)(LogicCharacterServer*, int, int, bool, LogicData*))(base + 0x88E6F4))(this, healerIndex, amount, shouldShow, source);
}
void LogicCharacterServer::addExtraHealthRegen(int healPerSecond, int durationTicks, int healerIndex, LogicData* source) {
	LogicCharacterServer::applyBuff(LogicBuffServer::HealthRegen, durationTicks, healPerSecond, healerIndex);
}
void LogicCharacterServer::blockHealthRegen()
{
	HealthRegenBlockedTick = getLogicBattleModeServer()->getTicksGone();
}
LogicProjectileServer* LogicCharacterServer::getControlledProjectile() {
	LogicArrayList<LogicProjectileServer*> projectiles;
	GameObjectManager->getProjectiles(&projectiles);
	for (int i = 0;i < projectiles.length;i++) {
		LogicProjectileServer* projectile = projectiles[i];
		if (projectile->Index == Index && ((LogicProjectileData*)projectile->getData())->getTravelType() == 5) return projectile;
	}
	return nullptr;
}
void LogicCharacterServer::addAreaEffect(int damage, int dot, LogicAreaEffectData* d, int skillType, bool idk) {
	if (!d) d = ((LogicCharacterData*)getData())->getAreaEffect();
	if (!d) return;
	LogicAreaEffectServer* a = (LogicAreaEffectServer*)LogicGameObjectFactoryServer::createGameObjectByData(d);
	int damageFromData = d->getDamage();
	if (damageFromData >= 1) {
		a->Damage = damageFromData + damage;
		a->DamageConst = damageFromData;
	}
	else {
		a->Damage = damageFromData - damage;
		a->DamageConst = 0;
	}
	a->setPosition(getX(), getY(), 0);
	a->Index = Index;
	a->TeamIndex = TeamIndex;
	a->WorldIndex = WorldIndex;
	a->setSource(this, skillType, false);
	this->AreaEffect = a;
	GameObjectManager->addLogicGameObject(a);
	a->trigger();
}
void LogicCharacterServer::triggerStun(int ticks, bool isForcedStun) {
	StunTicks = ticks;
	Stunned = true;
	interruptAllSkills(false);
	if (!(Charging || Knockbacked) || isForcedStun) stopMovement();
	if (getControlledProjectile()) getControlledProjectile()->targetReached(5);
}
void LogicCharacterServer::tickEffects() {
	for (int i = 0;i < Poisons.length;i++) {
		if (Poisons[i]->tick(this)) {
			Poisons.remove(i);
		}
	}
	for (int i = 0;i < Buffs.length;i++) {
		if (Buffs[i]->tick(this)) {
			Buffs.remove(i);
		}
	}
	if (PartialStunnedTicks <= 0) {
		if (PartialStunPromille > 0 && PartialStunPromille < 1000) {
			PartialStunDecrementTimer = LogicMath::positify(PartialStunDecrementTimer - 1);
			if (PartialStunDecrementTimer <= 0) PartialStunPromille = LogicMath::max(0, PartialStunPromille - 2);
			//todo: Lou 2nd Starpower
		}
		if (PartialStunPromille >= 1000) {
			triggerStun(20, false);
			PartialStunnedTicks = 20;
		}
	}
	else {
		PartialStunnedTicks--;
		PartialStunPromille = PartialStunnedTicks ? 1000 : 0;
	}
}
void LogicCharacterServer::setDefaultStartRotation() {
	if (TeamIndex == 1) {
		AttackAngle = 90;
		MoveAngle = 90;
	}
	else {
		AttackAngle = 270;
		MoveAngle = 270;
	}
}
bool LogicCharacterServer::isObject() {
	return IsObject;
}
void LogicCharacterServer::setUpgrades(LogicHeroUpgrades* upgrades) {
	if (upgrades) {
		ShowStarPowerIcon = upgrades->starPower || upgrades->overcharge;
		int level = upgrades->heroLevel - 1;
		LogicCharacterData* data = (LogicCharacterData*)getData();
		int hitpoints = HitpointsMax + data->getHitpoints() / 10 * level;
		Hitpoints = hitpoints;
		HitpointsMax = hitpoints;
		HitpointsMaxOriginal = hitpoints;
		for (int i = 0; i < Skills.length; i++)
		{
			Skills[i]->setNumUpgrades(level);
		}
		calculateChargeUp();
		switch (upgrades->starPower->getType()) {
		case 29:
			StaticSpeedBuff += upgrades->starPower->getValue();
			break;
		case 51:
			hitpoints = HitpointsMax + HitpointsMax * upgrades->starPower->getValue() / 100;
			Hitpoints = hitpoints;
			HitpointsMax = hitpoints;
			HitpointsMaxOriginal = hitpoints;
			break;
		case 48:
			Skills[0]->addCharge(this, 100);
			break;
		}
	}

	if (upgrades->gearBoost1) Gears.add(new LogicGear(upgrades->gearBoost1));
	if (upgrades->gearBoost2) Gears.add(new LogicGear(upgrades->gearBoost2));
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
	if (isOverCharging()) damageBuff += ((LogicCharacterData*)getData())->getOverchargeDamagePercent();
	return damageBuff;
}
void LogicCharacterServer::giveElectrocution(int damage, int damageConst, int bounces, int maxBounces, int effectType, int index, int teamIndex, int worldIndex) {
	LogicBuffServer* buff = new LogicBuffServer(LogicBuffServer::BelleWeapon, 20, damage, damageConst);
	buff->BelleWeaponBounces = bounces;
	buff->BelleWeaponRadius = 6000;
	buff->BelleWeaponSpecialEffectType = effectType;
	buff->Index = index;
	buff->TeamIndex = teamIndex;
	buff->WorldIndex = worldIndex;
	Buffs.add(buff);
}
LogicGear* LogicCharacterServer::getGearBoost(int type) {
	return	((LogicGear * (*)(LogicCharacterServer*, int))(base + 0x89C230))(this, type);

}
int LogicCharacterServer::getBuffBoost(int type) {
	/*
		New Function. Reason: Repeated Usage.
		--Shei
	*/
	int buff = 0;
	for (int i = 0;i < Buffs.length;i++) {
		if (Buffs[i]->Type == type) {
			if (type == LogicBuffServer::HealthRegen) buff++;
			else buff += Buffs[i]->Modifier;
		}
	}
	return buff;
}
LogicBuffServer* LogicCharacterServer::findBuffByType(int type) {
	/*
		New Function. Reason: Repeated Usage.
		--Shei
	*/
	for (int i = 0;i < Buffs.length;i++) {
		if (Buffs[i]->Type == type) return Buffs[i];
	}
	return nullptr;
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
int LogicCharacterServer::getSizeSubtilesForPathfinding() {
	LogicCharacterData* data = (LogicCharacterData*)getData();
	if (data->isCarryable()) {
		if (data->getCollisionRadius() >= 200) return 2;
		return 0;
	}
	if (data->isBoss() || data->getCollisionRadius() > 200) return 2;
	return 1;
}
void LogicCharacterServer::swapSkillTo(int index, LogicSkillData* data) {
	LogicSkillServer* newSkill = new LogicSkillServer(data, index == 1);
	LogicSkillServer* oldSkill = Skills[index];
	Skills[index] = newSkill;
	newSkill->Charges = oldSkill->Charges;
	newSkill->Level = oldSkill->Level;
	delete oldSkill;
}
void LogicCharacterServer::moveTo(int x, int y, bool usePresetSpeed, int presetSpeed, bool canPassDestructibleAny, bool canUseFastTravel) {
	((void (*)(LogicCharacterServer*, int, int, bool, int, bool, bool))(base + 0x89037C))(this, x, y, usePresetSpeed, presetSpeed, canPassDestructibleAny, canUseFastTravel);

}
void LogicCharacterServer::triggerCharge(int x, int y, int damage, int damageConst, int pushback, int speed, bool useSpecialPathfinding, int type, LogicAreaEffectData* spawnedAreaEffect, LogicItemData* spawnedItem, int itemParams1, int itemParams2, int range, bool isUlti, LogicArrayList<LogicVector2*>* presetWaypoints, LogicAreaEffectData* spawnedAreaEffect2) {
	if (Index >= 0)
		;//do anti teaming stuff
	if (!isUlti && ChargeUpType == 1) ChargeUp = 0;//腹蛇出洞！
	if (getCardValueForPassive(94, 1) >= 1) addShield(getCardValueForPassive(94, 3), getCardValueForPassive(94, 1));
	UsingUlti = isUlti;
	Stunned = false;
	Knockbacked = false;
	ChargeHits = 0;
	if (type == 10) {
		//Colette.
		int deltaX = x - getX();
		int deltaY = y - getY();
		int distance = LogicMath::sqrt(deltaX * deltaX + deltaY * deltaY);
		if (distance > 0) {
			deltaX = deltaX * 100 * range / distance;
			deltaY = deltaY * 100 * range / distance;
		}
		clearPath();
		PathPointsX.add(getX());
		PathPointsY.add(getY());
		LogicVector2 vector = LogicVector2(-1, -1);
		if (LogicGamePlayUtil::getClosestPathfinderCollision(getSizeSubtilesForPathfinding(), getX(), getY(), getX() + deltaX, getY() + deltaY, getLogicBattleModeServer()->getPathFinder(), &vector, true, true)) {
			deltaX = vector.X - getX();
			deltaY = vector.Y - getY();
			int distance = LogicMath::sqrt(deltaX * deltaX + deltaY * deltaY);
			if (distance > 0) {
				int distanceScaled = LogicMath::max(1, distance - 150);
				deltaX = distanceScaled * deltaX / distance;
				deltaY = distanceScaled * deltaY / distance;
			}
		}
		PathPointsX.add(getX() + deltaX);
		PathPointsY.add(getY() + deltaY);
		PathPointsX.add(getX());
		PathPointsY.add(getY());
		ensurePathOk(getLogicBattleModeServer()->getPathFinder());
		Pathlength = getPathLength();
		if (Pathlength > 0) {
			MoveStartTick = getLogicBattleModeServer()->getTicksGone();
			MoveEndTick = MoveStartTick + LogicMath::max(1, 20 * Pathlength / speed);
		}
	}
	else if (type != 7) {
		if (useSpecialPathfinding) {
			if (type == 2 || type == 6 || type == 9 || type == 11 || type == 16 || type == 18) {//可以理解为能原地跳起来的英雄，如黑鸦、佩佩...（普里莫则不是）
				int deltaX = x - getX();
				int deltaY = y - getY();
				int distance = LogicMath::sqrt(deltaX * deltaX + deltaY * deltaY);
				speed = LogicMath::max(1, distance * speed / 3000);
			}
			chargeTo(x, y, speed, getLogicBattleModeServer()->getPathFinder(), nullptr);
		}
		else {
			moveTo(x, y, true, speed, false, false);
		}
	}
	if (getCardValueForPassive(22, 1) > 0) addShield(getCardValueForPassive(22, 1), getCardValueForPassive(22, 2));
	if (getCardValueForPassive(54, 1) > 0) giveReloadBuff(100, getCardValueForPassive(54, 1));
	Charging = true;
	TravelSpeed = speed;
	ChargeDamage = damage;
	ChargeDamageConst = damageConst;
	ChargePercentDamage = 0;
	ChargePushback = pushback;
	ChargeType = type;
	ChargeChainDistance = range;
	ChargeDamageImmunitys_GlobalID.length = 0;
	ChargeDamageImmunitys_Timer.length = 0;
	if (type == 6) {
		;//piper.
	}
	else if (type == 2) {
		LogicAreaEffectServer* areaEffect = (LogicAreaEffectServer*)LogicGameObjectFactoryServer::createGameObjectByData(spawnedAreaEffect);
		areaEffect->setPosition(getX(), getY(), 0);
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
		ChargeEndAreaEffectDamageConst = damageConst;
	}
	else if (spawnedAreaEffect2) {
		//buzz.
		ChargeEndAreaEffect = spawnedAreaEffect2;
		ChargeEndAreaEffectDamage = damage;
		ChargeEndAreaEffectDamageConst = damageConst;
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
	applyBuff(LogicBuffServer::ReloadBuff, ticks, percent, 0);
}
void LogicCharacterServer::giveReloadDebuff(int percent, int ticks) {
	applyBuff(LogicBuffServer::ReloadDebuff, ticks, percent, 0);
}
bool LogicCharacterServer::isPlayerControlRemoved() {
	return ((bool (*)(LogicCharacterServer*))(base + 0x888324))(this);
}
bool LogicCharacterServer::isImmuneAndBulletsGoThrough() {
	return ((bool (*)(LogicCharacterServer*))(base + 0x8940DC))(this);
}
void LogicCharacterServer::setPartialStunPromille(int partialStunPromille) {
	if (PartialStunnedTicks <= 0) {
		PartialStunPromille = LogicMath::clamp(partialStunPromille, 0, 1000);
		PartialStunDecrementTimer = 40;
	}
}
void LogicCharacterServer::giveSlipperyDebuff(int modifier, int ticks) {
	if (((LogicCharacterData*)getData())->getSpeed() < 1) return;
	bool shouldRefreshSlipperyStatus = true;
	for (int i = 0;i < Buffs.length;i++) {
		LogicBuffServer* buff = Buffs[i];
		if (buff->Type == 7) shouldRefreshSlipperyStatus = false;
	}
	applyBuff(7, ticks, modifier, 0);
	if (shouldRefreshSlipperyStatus) IsSlippery = true;
}
bool LogicCharacterServer::isPet() {
	if (Index < 0) return false;
	return !((LogicCharacterData*)getData())->isHero();
}
void LogicCharacterServer::kill() {//added
	causeDamage(-1, Hitpoints, 0, nullptr, false, getX(), getY(), nullptr, false, false, true, true, false, false);
}
bool LogicCharacterServer::causeDamage(int sourceIndex, int damage, int damageConst, LogicCharacterServer* source, bool shouldShow, int sourceX, int sourceY, LogicData* sourceData, bool ignoreImmuneAndBulletsGoThrough, bool isUlti, bool forcedDamage, bool showEffect, bool isFromTencentBrawlLeaveBattle, bool idk) {
	return ((bool (*)(LogicCharacterServer*, int, int, int, LogicCharacterServer*, bool, int, int, LogicData*, bool, bool, bool, bool, bool, bool))(base + 0x88C614))(this, sourceIndex, damage, damageConst, source, shouldShow, sourceX, sourceY, sourceData, ignoreImmuneAndBulletsGoThrough, isUlti, forcedDamage, showEffect, isFromTencentBrawlLeaveBattle, idk);
}
bool LogicCharacterServer::isAlive() {
	return Hitpoints > 0;
}
bool LogicCharacterServer::isOverCharging() {
	LogicPlayer* player = getPlayer();
	return player && player->OverCharging;
}
void LogicCharacterServer::chargeUlti(int value, bool isUlti, bool absoluteValue, LogicPlayer* targetPlayer, LogicCharacterServer* target) {
	return ((void (*)(LogicCharacterServer*, int, bool, bool, LogicPlayer*, LogicCharacterServer*))(base + 0x89390C))(this, value, isUlti, absoluteValue, targetPlayer, target);
}
LogicCharacterServer* LogicCharacterServer::summonMinion(LogicCharacterData* characterData, int x, int y, int distance, int numSpawns, int maxSpawns, int extraDamage, int extraHitpoints, LogicBattleModeServer* battle, int index, int teamIndex, int worldIndex, int ownerGID, bool overrideExistingPets, bool chargesUlti, int summonedBoxOfSelfDestructBombsDamage, bool hasStarpower, int areaEffectDot, bool setHitpointToOwners, int size, bool overcharged) {
	LogicCharacterServer* owner = LogicGamePlayUtil::getCharacterFromPlayerIndex(index, battle->GameObjectManager);
	LogicPlayer* player = battle->getPlayer(index);
	if (characterData->isDuplicate() && (!owner || !owner->isAlive())) return nullptr;//萝拉分身：那我缺的本体这块谁给我补啊
	LogicArrayList<LogicCharacterServer*> characters;
	battle->GameObjectManager->getCharacters(&characters);
	int numSpawned = 0;
	for (int i = 0;i < characters.length;i++) {
		LogicCharacterServer* character = characters[i];
		if (character->isAlive() &&
			character->Index == index &&
			(character->getData() == characterData || character->getData() == characterData->getSpawnedPet()) &&
			!character->IsSpecialMinion &&
			!character->DoesNotCountTowardsMaxSpawns) {
			numSpawned++;
		}
	}
	if (overrideExistingPets) {
		for (int i = 0;i < characters.length && numSpawned >= maxSpawns;i++) {
			LogicCharacterServer* character = characters[i];
			if (character->isAlive() &&
				character->Index == index &&
				(character->getData() == characterData || character->getData() == characterData->getSpawnedPet()) &&
				!character->IsSpecialMinion &&
				!character->DoesNotCountTowardsMaxSpawns) {
				character->kill();
				numSpawned--;
			}
		}
	}
	else if (maxSpawns - numSpawned < numSpawns) numSpawns = maxSpawns - numSpawned;
	if (numSpawns <= 0) return nullptr;//都到上限了我Spawn什么啊
	if (owner && owner->getGearBoost(14)) {//训宠
		LogicGearData* gear = owner->getGearBoost(14)->GearData;
		if (gear->isBoostPercentage()) extraDamage += gear->getModifierValue() * (characterData->getAutoAttackDamage() + extraDamage) / 100;
		else extraDamage += gear->getModifierValue();
	}
	LogicCharacterServer* pet;
	for (int i = 0;i < numSpawns;i++) {
		int posX = -1;
		int posY = -1;
		for (int tries = 0;tries < 20;tries++) {
			int angle = battle->getRandomInt(360);
			LogicTileMap* tileMap = battle->getTileMap();
			posX = LogicMath::clamp(x + LogicMath::getRotatedX(distance, 0, angle), 101, tileMap->LogicWidth - 101);
			posY = LogicMath::clamp(y + LogicMath::getRotatedY(distance, 0, angle), 101, tileMap->LogicHeight - 101);
			if (tileMap->isPassablePathFinder(1, posX / 100, posY / 100, false, false))
				break;
		}
		//摆烂，备用位置判定不写了
		//todo: spawn pos fallback

		if (posX == -1) posX = x;
		if (posY == -1) posY = y;
		pet = (LogicCharacterServer*)LogicGameObjectFactoryServer::createGameObjectByData(characterData);
		battle->GameObjectManager->addLogicGameObject(pet);
		pet->MinionInvasionSpawnPosition.X = posX;
		pet->MinionInvasionSpawnPosition.Y = posY;
		pet->setPosition(posX, posY, characterData->getFlyingHeight());
		pet->Index = index;
		pet->TeamIndex = teamIndex;
		pet->WorldIndex = worldIndex;
		pet->DoesNotCountTowardsMaxSpawns = maxSpawns < 1;
		pet->Size = size;
		pet->IsHyperchargeMinion = overcharged;
		if (owner && ((LogicCharacterData*)owner->getData())->getUniqueProperty() == 13) pet->setUpgrades(player->getCurrentHeroSetup()->upgrades);//阿尔提的腿
		if (characterData->isDuplicate()) pet->IgnoreDeployTime = true;
		int newMaxHitpoints = pet->HitpointsMax + extraHitpoints;
		pet->Hitpoints = newMaxHitpoints;
		pet->HitpointsMax = newMaxHitpoints;
		pet->HitpointsMaxOriginal = newMaxHitpoints;
		LogicCharacterServer* ownerByGID = (LogicCharacterServer*)battle->GameObjectManager->getGameObjectByID(ownerGID);
		if (ownerByGID) {
			int angle = LogicMath::normalizeAngle360(LogicMath::getAngle(posX - ownerByGID->getX(), posY - ownerByGID->getY()));
			pet->MoveAngle = angle;
			pet->AttackAngle = angle;
		}
		else {
			//todo: setStartAngle
		}
		pet->SpawnedTicks = battle->getTicksGone();
		pet->ParentGID = ownerGID;
		pet->UsingUlti = true;
		pet->MinionChargesUlti = chargesUlti;
		pet->SummonedBoxOfSelfDestructBombsDamage = summonedBoxOfSelfDestructBombsDamage;
		pet->ShowStarPowerIcon = hasStarpower;
		pet->addAreaEffect(extraDamage, areaEffectDot, nullptr, 0, false);
		//if (pet->AreaEffect&&(pet->AreaEffect->getData()))
		//todo: area effect tweaks

		if (setHitpointToOwners && owner && owner->isAlive()) pet->Hitpoints = owner->Hitpoints;
	}
	return pet;
}
void LogicCharacterServer::triggerBlink(int x, int y, LogicAreaEffectData* areaEffectEnd, LogicAreaEffectData* areaEffectStart, int damage, int damageConst) {
	IsTeleporting = true;
	if (areaEffectEnd) {
		LogicAreaEffectServer* areaEffect = (LogicAreaEffectServer*)LogicGameObjectFactoryServer::createGameObjectByData(areaEffectEnd);
		areaEffect->setPosition(x, y, 0);
		areaEffect->Index = Index;
		areaEffect->Damage = damage;
		areaEffect->DamageConst = damageConst;
		GameObjectManager->addLogicGameObject(areaEffect);
		areaEffect->trigger();
	}
	if (areaEffectStart) {
		LogicAreaEffectServer* areaEffect = (LogicAreaEffectServer*)LogicGameObjectFactoryServer::createGameObjectByData(areaEffectStart);
		areaEffect->setPosition(getX(), getY(), 0);
		areaEffect->Index = Index;
		areaEffect->Damage = damage;
		areaEffect->DamageConst = damageConst;
		GameObjectManager->addLogicGameObject(areaEffect);
		areaEffect->trigger();
	}
	stopMovement();
	BlinkX = x;
	BlinkY = y;
}
void LogicCharacterServer::executeBlink() {
	if (BlinkX != -1) {
		stopMovement();
		setPosition(BlinkX, BlinkY, 0);
		IsTeleporting = true;
		BlinkX = -1;
	}
}
void LogicCharacterServer::triggerPullRope(LogicCharacterServer* target) {
	BuzzHookedCharacter = target;
	if (target) {
		BuzzHookedPosition.X = target->getX();
		BuzzHookedPosition.Y = target->getY();
	}
	else {
		BuzzHookedPosition.X = -1;
		BuzzHookedPosition.Y = -1;
	}
}
void LogicCharacterServer::updateChargeDamage() {
	if (ChargeType == 1 || ChargeType == 3 || ChargeType == 4 || (ChargeType == 5 && ChargeDamage) || ChargeType == 7 || ChargeType == 8 || ChargeType == 9 || ChargeType == 10 || ChargeType == 16 || ChargeType == 17 || ChargeType == 18) {
		LogicCharacterData* data = (LogicCharacterData*)getData();
		int damageRadius = 400;
		int ticksGone = getLogicBattleModeServer()->getTick();
		if (ChargeType == 3 || ChargeType == 9 || data->isBoss()) damageRadius = 800;
		//todo: damage nerfs (cripple)

		if (ChargeType == 7 || data->isTrain()) {//别人只能撞一次，达里尔和矿车可以撞很多次
			for (int i = 0;i < ChargeDamageImmunitys_GlobalID.length;i++) {
				if (!--ChargeDamageImmunitys_Timer[i]) {
					ChargeDamageImmunitys_GlobalID.remove(i);
					ChargeDamageImmunitys_Timer.remove(i);
				}
			}
		}
		if (ChargeType == 10 && (MoveEndTick - (MoveEndTick - MoveStartTick) / 2) == getLogicBattleModeServer()->getTick()) {
			ChargeDamageImmunitys_GlobalID.length = 0;
			ChargeDamageImmunitys_Timer.length = 0;//科莱特可以撞两次
		}
		LogicArrayList<LogicCharacterServer*> characters;
		GameObjectManager->getCharacters(&characters);
		for (int i = 0;i < characters.length;i++) {
			LogicCharacterServer* character = characters[i];
			if (character->isAlive() &&
				character->TeamIndex != TeamIndex &&
				!character->isImmuneAndBulletsGoThrough() &&
				LogicGamePlayUtil::getDistanceBetween(getX(), getY(), character->getX(), character->getY()) <= damageRadius &&
				!ChargeDamageImmunitys_GlobalID.contains(character->getGlobalID())) {
				ChargeDamageImmunitys_GlobalID.add(character->getGlobalID());
				if (ChargeType == 7 || data->isTrain()) {//只有达里尔和矿车按时间计算无敌帧
					ChargeDamageImmunitys_Timer.add(10);
				}
				if (character->causeDamage(Index,
					ChargeType == 10 ? LogicGamePlayUtil::calculatePercentDamage(ChargePercentDamage, ChargeDamage, true, getDamageBuffTemporary() + DamageBuffPermanent, 0/*todo: cripple*/, 1000, character) : ChargeDamage,
					ChargeType == 10 ? 1000 : ChargeDamageConst,
					this, true, getX(), getY(), nullptr, false, UsingUlti, false, true, false, false)) {
					ChargeHits++;
					if (getCardValueForPassive(19, 1) >= 1) {
						character->applyPoison(Index, getCardValueForPassive(19, 1) * getDamageForCalculatingCardDamageAfterV52() / 100, 0, true, this, 2, 4);
					}

					if (getCardValueForPassive(93, 1) >= 1 && character->isAlive()) {
						LogicCharacterData* thatData = (LogicCharacterData*)character->getData();
						if ((thatData->isHero() || thatData->isTrainingDummy()) && ticksGone + 2 < MoveEndTick) {
							character->setDraggingObject(this, getX() - character->getX(), getY() - character->getY(), false);
						}
					}
					if (getCardValueForPassive(94, 1) >= 1) {
						addShield(getCardValueForPassive(94, 3), getCardValueForPassive(94, 1) + getCardValueForPassive(94, 2) * ChargeHits);
					}
					character->triggerPushback(getX(), getY(), ChargePushback, true, false, false, data->isTrain(), data->isTrain(), false, false, false, false, 0);
				}
			}
		}
	}
}
void LogicCharacterServer::triggerPushback(int x, int y, int length, bool knockIntoAir, bool ignoreCcImmunity, bool idk7, bool idk8, bool idk9, bool idk10, bool Bouncing, bool isForced, bool idk, int extraKnockUp) {
	return ((void (*)(LogicCharacterServer*, int, int, int, bool, bool, bool, bool, bool, bool, bool, bool, bool, int))(base + 0x89C698))(this, x, y, length, knockIntoAir, ignoreCcImmunity, idk7, idk8, idk9, idk10, Bouncing, isForced, idk, extraKnockUp);

}
void LogicCharacterServer::triggerAreaEffect(LogicAreaEffectData* areaEffect, int x, int y, int damage, int skillType) {
	((void (*)(LogicCharacterServer*, LogicAreaEffectData*, int, int, int, int))(base + 0x8977C8))(this, areaEffect, x, y, damage, skillType);
}
bool LogicCharacterServer::hasCcImmunity() {
	//todo: TownCrushBoss rangeState > 0 and Bulls's 3rd Starpower
	return CcImmunityTicks > 0;
}
void LogicCharacterServer::setDraggingObject(LogicGameObjectServer* target, int x, int y, bool ignoreCcImmunity) {
	if (!ignoreCcImmunity && (IsInvincible || hasCcImmunity())) return;
	DraggingAngle = LogicMath::getAngle(x, y);
	DraggingObject = target;
	stopMovement();
	interruptAllSkills(false);
}
int LogicCharacterServer::getReloadSpeedChangePercent() {
	return getBuffBoost(LogicBuffServer::ReloadBuff) - getBuffBoost(LogicBuffServer::ReloadDebuff);
}
int LogicCharacterServer::getRadius() {
	return ((LogicCharacterData*)getData())->getCollisionRadius();
}
int LogicCharacterServer::getDamageForCalculatingCardDamageAfterV52() {
	return Skills[0]->SkillData->getDamage() * (Skills[0]->Level + 9) / 10 * (100 + getDamageBuffTemporary() + DamageBuffPermanent) / 100;
}
LogicCharacterServer* LogicCharacterServer::triggerTransformation(LogicCharacterData* data) {
	Hitpoints = 0;
	DoNotUseDefaultDeathEffect = true;
	LogicPlayer* player = getPlayer();
	if (player) {
		LogicCharacterServer* c = getLogicBattleModeServer()->spawnHero(data, player->getCurrentHeroSetup()->upgrades, Index, TeamIndex, WorldIndex, IsBot);
		c->setPosition(getX(), getY(), 0);
		player->characterGID = c->getGlobalID();
		return c;
	}
	return nullptr;
}
int LogicCharacterServer::getPowerLevel() {
	LogicCharacterData* data = ((LogicCharacterData*)getData());
	if (data->HasPowerLevels) {
		// if(getPlayer()) return getPlayer()
	}
	return 3;
}
int LogicCharacterServer::getMovementSpeed() {
	LogicCharacterData* data = ((LogicCharacterData*)getData());
	int speed = data->getSpeed();
	if (isOverCharging()) speed += speed * data->getOverchargeSpeedPercent() / 100;
	speed += StaticSpeedBuff;
	speed += getBuffBoost(LogicBuffServer::SpeedFaster);
	speed += getBuffBoost(LogicBuffServer::SpeedSlower);
	if (data->HasPowerLevels && getPowerLevel() > 0)
		speed += 170;
	return speed;
}
int LogicCharacterServer::getSpeedBuff() {
	return getBuffBoost(LogicBuffServer::SpeedFaster) + getBuffBoost(LogicBuffServer::SpeedSlower);
}
void LogicCharacterServer::encode(BitStream* stream, bool isOwn, int fadeCounter, int index, bool isOwnTeam) {
	LogicGameObjectServer::encode(stream, fadeCounter);
	LogicCharacterData* data = (LogicCharacterData*)getData();
	LogicPlayer* player = getPlayer();
	int mode = getLogicBattleModeServer()->GameModeVariation;
	if (!IsObject) {
		if (isOwn) {
			stream->writeBoolean(isPlayerControlRemoved());
			if (stream->writeBoolean(ForcedAngleEndTick + 1 >= getLogicBattleModeServer()->getTick()) || isPlayerControlRemoved()) {
				stream->writePositiveIntMax511(AttackAngle);
				stream->writePositiveIntMax511(MoveAngle);
			}
		}
		else {
			stream->writePositiveIntMax511(AttackAngle);
			stream->writePositiveIntMax511(MoveAngle);
		}
		stream->writePositiveIntMax7(State);
		stream->writeBoolean(getDamageBuffTemporary() > 0 && !isOverCharging());
		stream->writeIntMax63(AttackAnimation);
		stream->writeBoolean(Knockbacked);
		if (stream->writeBoolean(Stunned)) stream->writeBoolean(WeaklyStunned);
		stream->writeBoolean(false);//Shaking
		stream->writeBoolean(ShowStarPowerIcon);
	}
	else {
		stream->writePositiveIntMax7(State);
		if (data->isTrain() || data->ManualRotations) {
			stream->writePositiveIntMax511(AttackAngle);
			stream->writePositiveIntMax511(MoveAngle);
		}
		else if (data->getAreaEffect()) stream->writePositiveIntMax511(MoveAngle);
	}
	if (data->getLifeTimeTicks()) stream->writePositiveIntMax511(LifeTimeTicks);
	stream->writePositiveVIntMax65535OftenZero(ProjectileEffectId);
	stream->writePositiveVIntMax65535OftenZero(SkinEffectId);
	stream->writeBoolean(findBuffByType(LogicBuffServer::Slippery));
	stream->writeBoolean(findBuffByType(LogicBuffServer::SpeedFaster));
	stream->writeBoolean(findBuffByType(LogicBuffServer::SpeedSlower));
	stream->writeBoolean(false);//Suppress Healing
	stream->writeBoolean(false);
	if (stream->writeBoolean(findBuffByType(LogicBuffServer::BelleWeapon))) {
		stream->writePositiveIntMax7(findBuffByType(LogicBuffServer::BelleWeapon)->BelleWeaponSpecialEffectType);
	}
	stream->writeBoolean(findBuffByType(LogicBuffServer::BelleUlti));
	stream->writeBoolean(false);//IsSilenced
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	if (stream->writeBoolean(getReloadSpeedChangePercent())) stream->writeIntMax127(LogicMath::clamp(getReloadSpeedChangePercent(), -100, 100));
	stream->writePositiveVIntMax255OftenZero(PartialStunPromille / 10);
	stream->writePositiveVIntMax255OftenZero(Poisons.length);
	for (int i = 0;i < Poisons.length;i++) {
		stream->writePositiveIntMax15(Poisons[i]->Type);
		stream->writePositiveIntMax15(Poisons[i]->Index);
	}
	stream->writeBoolean(false);//IsCrippled
	stream->writePositiveVIntMax255OftenZero(getBuffBoost(LogicBuffServer::HealthRegen));
	stream->writePositiveVIntMax16777215(Hitpoints);
	stream->writePositiveVIntMax16777215(HitpointsMax);
	if (Hitpoints <= 0) {
		stream->writeIntMax15(0);//DeathEffect
	}
	stream->writeBoolean(false);
	if (data->isHero()) {
		int itemCount = CoinsHeld;
		if (LogicGameModeUtil::playersCollectBountyStars(mode)) itemCount = LogicMath::max(0, CoinsHeld - 2);
		stream->writePositiveVIntMax255OftenZero(itemCount);
		stream->writePositiveVIntMax255OftenZero(BattleRoyalBuffs);
		if (stream->writeBoolean(ConsumableShield > 0)) {
			stream->writePositiveIntMax16383(ConsumableShield);
			stream->writePositiveIntMax16383(ConsumableShieldMax);
		}
		stream->writeBoolean(HasRuffsBuff);
		if (Hitpoints <= 0) stream->writeBoolean(false);//TransformAnimation
	}
	if (data->isHero()) {
		stream->writePositiveVIntMax255OftenZero(0);
		stream->writeBoolean(false);
		stream->writeBoolean(true);
		stream->writeBoolean(Charging);
		stream->writeBoolean(IsInvincible);
		stream->writeBoolean(AimingUlti);
		stream->writeBoolean(ShowUltiAnimation);
		stream->writeBoolean(CcImmunityTicks > 0);
		if (player && player->hasOverChargeData()) {
			stream->writeBoolean(player->OverCharge == player->OverChargeMax);
			stream->writeBoolean(player->OverCharging);
			stream->writeBoolean(player->OverChargeOnStart);
			stream->writeBoolean(player->OverChargeOnEnd);
		}
		if (isOwn) {
			stream->writeBoolean(false);
		}
		if (data->WeaponSkill) {
			if (data->WeaponSkill->getChargedShotCount() >= 1) stream->writeIntMax3(ChargedShotHits);
			if (isOwn && data->WeaponSkill->getAttackPattern() == 13) stream->writePositiveVIntMax255OftenZero(LogicMath::clamp(SkillHoldTicks, 0, 255));
			if (data->WeaponSkill->getAttackPattern() == 15) {
				stream->writePositiveVIntMax255OftenZero(LogicMath::clamp(SkillHoldTicks, 0, 255));
				if (SkillHoldTicks >= 1) stream->writePositiveIntMax511(SkillHoldAngle);
			}
		}
		if (data->ShouldEncodePetStatus || data->getUniqueProperty() == 13 && data->isHero()) stream->writeBoolean(false);
		if (data->HasPowerLevels) stream->writePositiveIntMax3(0);
		if (data->getUniqueProperty() == 1) stream->writePositiveIntMax3(LogicMath::clamp((3 * ChargeUp / ChargeUpMax), 0, 2));
		if (stream->writeBoolean(false)) {
			stream->writePositiveIntMax15(0);
			stream->writePositiveIntMax7(0);
		}
		if (Charging) {
			stream->writePositiveIntMax255(ChargeAnimation);
			stream->writePositiveIntMax31(ChargeType);
			if (ChargeType == 17) stream->writeBoolean(false);//Chunk
		}
		if (Skills.length >= 2 && Skills[1]->SkillData->getProjectile() && Skills[1]->SkillData->getProjectile()->UniqueProperty == 5) stream->writeBoolean(false);
		switch (ChargeUpType)
		{
		case 0:
			break;
		case 1:
		case 7:
		case 11:
		case 12:
			stream->writePositiveVIntMax255OftenZero(AttackChargedUp ? 255 : ChargeUp / 50);
			break;
		case 8:
			stream->writePositiveIntMax1023(ChargeUp);
			break;
		case 9:
			stream->writePositiveIntMax7(ChargeUp);
			break;
		default:
			stream->writePositiveIntMax1023(AttackChargedUp ? 1023 : LogicMath::clamp(ChargeUp / 50, 0, 1023));
			break;
		}
		for (int i = 0;i < Gears.length;i++) Gears[i]->encode(stream);//libg invoke it with a3 = "isOwn" idk why

	}
	if (data->isTurret()) {
		stream->writeBoolean(IsHyperchargeMinion);
		stream->writeBoolean(Size > 0);
	}
	if (data->getPetAutoSpawnDelay() > 0) stream->writePositiveIntMax1023(LogicMath::clamp(TicksSinceLastMinionSpawn, 0, 1023));
	if (data->getSpawnedPet()) stream->writeBoolean(SpawningPet);
	if (data->getUniqueProperty() == 9) stream->writeBoolean(SamHasWeapon);//山姆
	if (LogicGamePlayUtil::canUseFastTravel(this)) stream->writeBoolean(IsTeleporting);//GamePlayUtil::canUseFastTravel;
	if (data->getUniqueProperty() == 22) {//凯特
		if (stream->writeBoolean(KitAttachingCharacter)) {
			stream->writePositiveVIntMax65535(GlobalID::getInstanceID(KitAttachingCharacter->getGlobalID()));
		}
	}
	stream->writeBoolean(false);
	if (data->getUniqueProperty() == 11 && isOwn) {
		stream->writeIntMax255(ChesterNextUlti->getInstanceID());
		stream->writePositiveIntMax7(ChesterWeaponCounter);
	}
	stream->writeBoolean(ShieldTicks > 0 || data->getUniqueProperty() == 13 && !data->isHero() && data->getUniquePropertyValue2() > 0 || data->isHero() && getPlayer() && getPlayer()->getWillowObjectId() >= 1 && LogicDataTables::getItemFor(data, 3)->getValue() > 0);
	stream->writePositiveIntMax3(0);
	stream->writeBoolean(false);
	stream->writePositiveIntMax511(0);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	if (isOwn) {
		int clientSpeed = getSpeedBuff();
		if (stream->writeBoolean(clientSpeed != 0)) {
			stream->writeIntMax1023(clientSpeed);
		}
		stream->writeBoolean(IsRevealed);
	}
	int damageNumberCount = 0;
	for (int i = 0;i < DamageNumbers_Value.length;i++) {
		if (DamageNumbers_Delay[i] == 0) {
			if (Index == index || DamageNumbers_Index[i] == index) damageNumberCount++;
		}
	}
	stream->writePositiveIntMax31(damageNumberCount);
	for (int i = 0;i < DamageNumbers_Value.length;i++) {
		if (DamageNumbers_Delay[i] == 0) {
			if (Index == index || DamageNumbers_Index[i] == index) stream->writeIntMax32767(LogicMath::clamp(DamageNumbers_Value[i], -32767, 32767));
		}
	}
	for (int i = 0;i < Skills.length;i++) {
		Skills[i]->encode(stream, isOwn, this);
	}
	stream->writePositiveIntMax3(0);
}