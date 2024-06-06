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
	char gap3[28];
	int Damage;
	int NormalDMG;
	char gap2[4];
	LogicCharacterServer* Owner;

	static LogicProjectileServer* ShootProjectile(int a1, int a2, LogicCharacterServer* a3, LogicGameObjectServer* a4, LogicProjectileData* a5, int a6, int a7, int a8, int a9, int a10, bool a11, int a12, LogicBattleModeServer* a13, int a14, int a15) {
		return ((LogicProjectileServer * (*)(int, int, LogicCharacterServer*, LogicGameObjectServer*, LogicProjectileData*, int, int, int, int, int, bool, int, LogicBattleModeServer*, int, int))base + 0x8B8E08)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	};
	LogicProjectileServer(LogicProjectileData* logicProjectileData) : LogicGameObjectServer(logicProjectileData)
	{
		;
	}
	~LogicProjectileServer();
	void tick()
	{
		;
	}
	//void __attribute__((used)) returnBoomerang()
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
		LogicProjectileServer* boomerang = ShootProjectile(-1, -1, Owner, this, ((LogicProjectileData*)getData())->getChainedBullet(), boomerangX, boomerangY, Damage, NormalDMG, 0, false, 0, getLogicBattleModeServer(), 0, 0);
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
#endif