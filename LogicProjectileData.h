#ifndef LPD_H
#define LPD_H
#include "Hook.h"
class LogicProjectileData : public LogicData
{
private:
	/* data */
public:
	LogicProjectileData* getChainedBullet()
	{
		return ((LogicProjectileData * (*)(LogicProjectileData*))(base + 0x865B4C))(this);
	}
	bool isBoomerang()
	{
		return ((bool (*)(LogicProjectileData*))(base + 0x865DBC))(this);
	}
	bool isFriendlyHomingMissile()
	{
		return ((bool (*)(LogicProjectileData*))(base + 0x86591C))(this);
	}
	bool isHomingMissile()
	{
		return ((bool (*)(LogicProjectileData*))(base + 0x865DCC))(this);
	}
};
#endif