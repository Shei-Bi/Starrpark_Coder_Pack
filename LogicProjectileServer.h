#ifndef LPS_H
#define LPS_H
#include "LogicCharacterServer.h"
#include "LogicGameObjectServer.h"
#include "LogicBattleModeServer.h"
#include "LogicProjectileData.h"
#include "Hook.h"
class LogicProjectileServer : public LogicGameObjectServer
{
public:
	char gap1[96 - 72];
	int StartX;//96
	int StartY;//100
	int TargetX;//104
	int TargetY;//108
	char gap3[20];
	int Damage;//132
	int NormalDMG;//136
	char gap2[4];
	LogicCharacterServer* Owner;//144
	LogicCharacterServer* HomingTarget;//148

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
	void getNextSteeredPos(LogicVector2&);
	void getPosAtTick(int, LogicVector2&);
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
	void tickMovement(void);
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
	if (Owner) {
		LogicProjectileData* data = (LogicProjectileData*)getData();
		if (data->getLifeStealPercent() > 0) Owner->heal(Index, data->getLifeStealPercent() * damage / 100, true, data);
	}
}
#endif