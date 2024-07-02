#ifndef LPD_H
#define LPD_H
#include "Hook.h"
#include "String.h"

class LogicProjectileData : public LogicData
{
private:
	/* data */
public:
	char gap1[448];
	int UniqueProperty;//448
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
	int getLifeStealPercent()
	{
		return ((int (*)(LogicProjectileData*))(base + 0x865C14))(this);
	}
	int getPartialStunPromille()
	{
		return ((int (*)(LogicProjectileData*))(base + 0x865BDC))(this);
	}
	int getTravelType()
	{
		return ((int (*)(LogicProjectileData*))(base + 0x865DE4))(this);
	}
	String* getCustomObject() {
		return ((String * (*)(LogicProjectileData*))(base + 0x865E34))(this);
	}
};
#endif