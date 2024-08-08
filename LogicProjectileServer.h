#ifndef LPS_H
#define LPS_H
#include "LogicCharacterServer.h"
#include "LogicGameObjectServer.h"
#include "LogicBattleModeServer.h"
#include "LogicProjectileData.h"
#include "Hook.h"
#include "LogicGamePlayUtil.h"

class LogicProjectileServer : public LogicGameObjectServer
{
public:
	char gap1[88 - 76];
	LogicVector2 PositionVector;//88
	int StartX;//96
	int StartY;//100
	int TargetX;//104
	int TargetY;//108
	char gap3[128 - 108 - 4];
	int DefaultZ;//128
	int Damage;//132
	int NormalDMG;//136
	char gap2[4];
	LogicCharacterServer* Owner;//144
	LogicCharacterServer* HomingTarget;//152
	char gap138438984[240 - 152 - 8];
	int TotalDelta;//240
	char gap8497934879[420 - 240 - 4];
	int Angle;//420
	char gap913489384[4];
	int EarlyTicks;//428
	char gap98493[4];
	int SkillType;//436
	char gap1413948390840[744 - 436 - 4];
	int BelleWeaponBounces;

	void addIgnoredTarget(int, int);
	void addIgnoredTargetToLinkedProjectiles(int, int);
	void applyDamageSpecialEffects(LogicCharacterServer*, int, int, bool);
	void calculateGrappleTargetPos(int, int, LogicCharacterServer const*);
	void destruct(void);
	void encode(BitStream*, bool, int, int);
	void executeChainBullet(int, int, LogicCharacterServer*);
	void executeGrapple(LogicCharacterServer*);
	void getCirclingPosAt(int, LogicVector2&);
	int getInitialZSpeed(LogicProjectileData const*, int, int, int);
	int getModifiedDamage(int, bool, int);
	int getModifiedPushback(void);
	int getModifiedScale(int);
	int getNextSteeredPos(LogicVector2&);
	int getPosAtTick(int, LogicVector2&);
	void getProjectileData(void);
	void getProjectileSpeed(LogicCharacterServer*, LogicProjectileData const*, bool);
	void getProjectileZAtT(float, float, float, float, float);
	void getSpreadMax(LogicProjectileData const*, int, int);
	void getStartX(void);
	void getStartY(void);
	void getTargetX(void);
	void getTargetY(void);
	void getTravelTicks(LogicProjectileData const*, int, int);
	void getType(void);
	void handleCollisions(void);
	void handleStunTrigger(LogicCharacterServer*);
	void hasHitTarget(int);
	void increaseTargetHitCount(int);
	void init(int, int, LogicCharacterServer*, LogicGameObjectServer const*, int, int, LogicData const*, int, int, int, int, int, int);
	void isChainBullet(void);
	void isSummoningMinion(void);
	void petFound(LogicCharacterServer*);
	void removeGameObjectReferences(LogicGameObjectServer const*, int);
	void returnBoomerang(void);
	void runEarlyTicks(void);
	void runTickOutsideMainLoop(void);
	void setCharacterBuffingProjectileData(int, int, int, int);
	void setCharacterSummonProjectileData(LogicCharacterData const*, int, int, int, int, bool);
	void setFreeze(int, int);
	void setItemSummonProjectileData(LogicItemData const*, int, int, int, int);
	void setLinkedProjectiles(LogicArrayList<LogicProjectileServer*>*);
	void setMinionHasSelfDestruct(int);
	void setPrevPos(int, int);
	void setPreyOnTheWeak(int, int);
	void setStealSouls2BuffingData(int, int);
	void setSummonMinionForAreaEffect(LogicCharacterData const*, int, int);
	static LogicProjectileServer* shootProjectile(int, int, LogicCharacterServer*, LogicGameObjectServer*, LogicProjectileData*, int, int, int, int, int, bool, int, LogicBattleModeServer*, int, int);
	void shouldCheckCollision(void);
	void shouldDestruct(void);
	void targetReached(int);
	void tick(void);
	bool tickMovement(void);
	void updateTrailAreaEffect(void);
};
void LogicProjectileServer::targetReached(int type) {
	if (type != 5) {
		LogicProjectileData* data = (LogicProjectileData*)getData();
		if (data->isBoomerang()) {
			if (data->getChainedBullet()) returnBoomerang();
			else if (!data->getChainedBullet() && Owner) Owner->Skills[0]->addCharge(Owner, 100);
		}
	}
}
void LogicProjectileServer::tick() {
	LogicProjectileData* data = (LogicProjectileData*)getData();
	if (data->isFriendlyHomingMissile() || data->isHomingMissile() || (data->isBoomerang() && !data->getChainedBullet())) {
		if (HomingTarget) {
			TargetX = HomingTarget->getX();
			TargetY = HomingTarget->getY();
		}
	}
}
void LogicProjectileServer::returnBoomerang() {
	int boomerangX;
	int boomerangY;
	if (Owner)
	{
		boomerangX = Owner->getX();
		boomerangY = Owner->getY();
	}
	else
	{
		boomerangX = StartX;
		boomerangY = StartY;
	}
	LogicProjectileServer* boomerang = shootProjectile(-1, -1, Owner, this, ((LogicProjectileData*)getData())->getChainedBullet(), boomerangX, boomerangY, Damage, NormalDMG, 0, false, 0, getLogicBattleModeServer(), 0, 0);
	boomerang->HomingTarget = Owner;
}
LogicProjectileServer* LogicProjectileServer::shootProjectile(int startX, int startY, LogicCharacterServer* source, LogicGameObjectServer* shooter, LogicProjectileData* projectileData, int endX, int endY, int damage, int normalDMG, int a10, bool a11, int a12, LogicBattleModeServer* battleMode, int a14, int catagory) {
	return ((LogicProjectileServer * (*)(int, int, LogicCharacterServer*, LogicGameObjectServer*, LogicProjectileData*, int, int, int, int, int, bool, int, LogicBattleModeServer*, int, int))(base + 0x8B8E08))(startX, startY, source, shooter, projectileData, endX, endY, damage, normalDMG, a10, a11, a12, battleMode, a14, catagory);
};
void LogicProjectileServer::applyDamageSpecialEffects(LogicCharacterServer* target, int damage, int damageConst, bool reserved) {
	LogicProjectileData* data = (LogicProjectileData*)getData();
	if (Owner) {
		if (data->getLifeStealPercent() > 0) Owner->heal(Index, data->getLifeStealPercent() * damage / 100, true, data);
	}
	if (data->getPartialStunPromille() > 0) {
		target->setPartialStunPromille(target->PartialStunPromille + data->getPartialStunPromille());
	}
	if (data->PoisonDamagePercent >= 1) {
		target->applyPoison(Index, data->PoisonDamagePercent * damage / 100, data->PoisonDamagePercent * damageConst / 100, SkillType == 2, Owner, data->PoisonType, data->PoisonTickCount);
	}
	if (data->UniqueProperty == 3 && BelleWeaponBounces < data->CustomUniquePropertyValue) {
		target->giveElectrocution(damage / 2, damageConst / 2, BelleWeaponBounces, 3, data->AppliedEffectVisualType, Index, TeamIndex, WorldIndex);
	}
}
int LogicProjectileServer::getPosAtTick(int ticks, LogicVector2& outVector) {
	return ((int (*)(LogicProjectileServer*, int, LogicVector2&))(base + 0x8B7D08))(this, ticks, outVector);
}
int LogicProjectileServer::getNextSteeredPos(LogicVector2& outVector) {
	int ticksGone = getLogicBattleModeServer()->getTicksGone();
	LogicProjectileData* data = (LogicProjectileData*)getData();
	int targetAngle = Angle;
	if (ticksGone + EarlyTicks - MoveStartTick > data->SteerIgnoreTicks) {
		switch (data->getTravelType()) {
		case 4://佩佩二妙等 piper 2nd gadget
		{
			int distance = data->HomeDistance * 300;
			LogicCharacterServer* target = nullptr;
			LogicArrayList<LogicCharacterServer*> characters;
			GameObjectManager->getCharacters(&characters);
			for (int i = 0;i < characters.length;i++) {
				LogicCharacterServer* character = characters[i];
				if (character->isAlive() && character->TeamIndex != TeamIndex && (character->TeamIndex != -1 || !character->isObject()) && (!character->IsInvisible || character->IsRevealed)) {
					int dis = LogicGamePlayUtil::getDistanceBetween(getX(), getY(), character->getX(), character->getY());
					if (dis < distance) {
						target = character;
						distance = dis;
					}
				}
			}
			if (target) {
				targetAngle = LogicMath::getAngle(target->getX() - getX(), target->getY() - getY());
			}
		}
		break;
		case 10://贝尔 belle
			if (HomingTarget) targetAngle = LogicMath::getAngle(HomingTarget->getX() - getX(), HomingTarget->getY() - getY());
			break;
		}
	}
	int speed = data->Speed;
	if (data->getTravelType() == 5) {
		speed = speed * 0.4 + speed * 0.6 * TotalDelta / 1000;
	}
	Angle = LogicMath::normalizeAngle360(Angle + (LogicMath::normalizeAngle360(targetAngle - Angle) < 180 ? 1 : -1) * LogicMath::min(LogicMath::getAngleBetween(Angle, targetAngle), data->SteerStrength));
	outVector.X = getX() + LogicMath::cos(Angle) * speed / 20 / 1024;
	outVector.Y = getY() + LogicMath::sin(Angle) * speed / 20 / 1024;
	return DefaultZ;
}
bool LogicProjectileServer::tickMovement() {
	int ticksGone = getLogicBattleModeServer()->getTicksGone();
	int nowTick = ticksGone + EarlyTicks;
	if (nowTick > MoveEndTick) return true;
	LogicProjectileData* data = (LogicProjectileData*)getData();
	int z = data->SteerStrength > 0 ? getNextSteeredPos(PositionVector) : getPosAtTick(nowTick, PositionVector);
	if (data->Indirect) {
		LogicTileMap* tileMap = getLogicBattleModeServer()->getTileMap();
		if (PositionVector.X < 2 || PositionVector.X >= tileMap->LogicWidth - 2 || PositionVector.Y < 2 || PositionVector.Y >= tileMap->LogicHeight - 2) {
			setPosition(LogicMath::clamp(PositionVector.X, 1, tileMap->LogicWidth - 2), LogicMath::clamp(PositionVector.Y, 1, tileMap->LogicHeight - 2), z);
			return true;
		}
	}
	setPosition(PositionVector.X, PositionVector.Y, z);
	return nowTick == MoveEndTick;
}
#endif