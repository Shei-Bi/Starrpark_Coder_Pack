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
	int StartX;
	int StartY;
	int TargetX;
	int TargetY;
	char gap3[20];
	int Damage;
	int NormalDMG;
	char gap2[4];
	LogicCharacterServer* Owner;
	LogicCharacterServer* HomingTarget;

	static LogicProjectileServer* shootProjectile(int startX, int startY, LogicCharacterServer* source, LogicGameObjectServer* shooter, LogicProjectileData* projectileData, int endX, int endY, int damage, int normalDMG, int a10, bool a11, int a12, LogicBattleModeServer* battleMode, int a14, int catagory) {
		return ((LogicProjectileServer * (*)(int, int, LogicCharacterServer*, LogicGameObjectServer*, LogicProjectileData*, int, int, int, int, int, bool, int, LogicBattleModeServer*, int, int))base + 0x8B8E08)(startX, startY, source, shooter, projectileData, endX, endY, damage, normalDMG, a10, a11, a12, battleMode, a14, catagory);
	};
	LogicProjectileServer(LogicProjectileData* logicProjectileData) : LogicGameObjectServer(logicProjectileData)
	{
		;
	}
	~LogicProjectileServer();
	void tick();
	void returnBoomerang()
	{
		int boomerangX;
		int boomerangY;
		if (Owner)
		{
			boomerangX = Owner->GetX();
			boomerangY = Owner->GetY();
		}
		else
		{
			boomerangX = StartX;
			boomerangY = StartY;
		}
		LogicProjectileServer* boomerang = shootProjectile(-1, -1, Owner, this, ((LogicProjectileData*)getData())->getChainedBullet(), boomerangX, boomerangY, Damage, NormalDMG, 0, false, 0, getLogicBattleModeServer(), 0, 0);
		boomerang->HomingTarget = Owner;
	}
	void targetReached(int);
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
			TargetX = HomingTarget->GetX();
			TargetY = HomingTarget->GetY();
		}
	}
}
#endif