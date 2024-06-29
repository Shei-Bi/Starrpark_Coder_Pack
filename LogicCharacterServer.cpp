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

void LogicCharacterServer::addConsumableShield(int amount)
{
	;
}
void LogicCharacterServer::tick()
{
	addConsumableShield(114514);
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
void LogicCharacterServer::triggerStun(int ticks, bool isForcedStun) {
	StunTicks = ticks;
	Stunned = true;
}
void LogicCharacterServer::tickEffects() {
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
		PartialStunPromille = 1000;
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
			if (type == 2 || type == 6) {
				int deltaX = x - getX();
				int deltaY = y - getY();
				int distance = LogicMath::sqrt(deltaX * deltaX + deltaY * deltaY);
				speed = LogicMath::max(1, distance * speed / 3000);
			}
			chargeTo(x, y, speed, getLogicBattleModeServer()->getPathFinder(), nullptr);
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
void LogicCharacterServer::giveSlipperyDebuff() {
	if (((LogicCharacterData*)getData())->getSpeed() < 1) return;
}
bool LogicCharacterServer::isPet() {
	if (Index < 0) return false;
	return !((LogicCharacterData*)getData())->isHero();
}
bool LogicCharacterServer::causeDamage(int sourceIndex, int damage, int damageConst, LogicCharacterServer* source, bool shouldShow, int sourceX, int sourceY, LogicData* sourceData, bool ignoreImmuneAndBulletsGoThrough, bool isUlti, bool forcedDamage, bool showEffect, bool isFromTencentBrawlLeaveBattle, bool idk) {
	return ((bool (*)(LogicCharacterServer*, int, int, int, LogicCharacterServer*, bool, int, int, LogicData*, bool, bool, bool, bool, bool, bool))(base + 0x88C614))(this, sourceIndex, damage, damageConst, source, shouldShow, sourceX, sourceY, sourceData, ignoreImmuneAndBulletsGoThrough, isUlti, forcedDamage, showEffect, isFromTencentBrawlLeaveBattle, idk);
}
bool LogicCharacterServer::isAlive() {
	return Hitpoints > 0;
}
void LogicCharacterServer::updateChargeDamage() {
	if (ChargeType == 1 || ChargeType == 3 || ChargeType == 4 || ChargeType == 7 || ChargeType == 8 || ChargeType == 9 || ChargeType == 10) {
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
					//todo: Primo's Fire

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
void LogicCharacterServer::encode(BitStream* stream, bool isOwn, int fadeCounter, int index, bool isOwnTeam) {
	LogicGameObjectServer::encode(stream, fadeCounter);
	LogicCharacterData* data = (LogicCharacterData*)getData();
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
		stream->writeBoolean(getDamageBuffTemporary() > 0);
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
		stream->writePositiveIntMax7(findBuffByType(LogicBuffServer::BelleWeapon)->Int1);
	}
	stream->writeBoolean(findBuffByType(LogicBuffServer::BelleUlti));
	stream->writeBoolean(false);//IsSilenced
	stream->writeBoolean(false);
	stream->writeBoolean(false);
	if (stream->writeBoolean(getReloadSpeedChangePercent())) stream->writeIntMax127(LogicMath::clamp(getReloadSpeedChangePercent(), -100, 100));
	stream->writePositiveVIntMax255OftenZero(PartialStunPromille / 10);
	stream->writePositiveVIntMax255OftenZero(0);//Poison
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
		if (isOwn) {
			stream->writeBoolean(false);
		}
		if (data->WeaponSkill) {
			if (data->WeaponSkill->getChargedShotCount() >= 1) stream->writeIntMax3(ChargedShotCount);
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
	if (data->getSpawnedPet()) stream->writeBoolean(SpawningPet);
	if (data->getUniqueProperty() == 9) stream->writeBoolean(SamHasWeapon);
	if (LogicGamePlayUtil::canUseFastTravel(this)) stream->writeBoolean(IsTeleporting);//GamePlayUtil::canUseFastTravel;
	stream->writeBoolean(false);
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
		stream->writeBoolean(false);
		stream->writeBoolean(false);
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