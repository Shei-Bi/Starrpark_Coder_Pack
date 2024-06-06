#ifndef LPD_H
#define LPD_H
#include "Hook.h"
class LogicProjectileData : public LogicData
{
private:
	/* data */
public:
	char gap1[256 - 8];
	LogicProjectileData* ChainedBullet;
	LogicProjectileData* getChainedBullet()
	{
		return ((LogicProjectileData * (*)(LogicProjectileData*))base + 0x865B4C)(this);
	}
	bool isBoomerang()
	{
		return ((bool (*)(LogicProjectileData*))base + 0x865DBC)(this);
	}
};
#endif