#ifndef LPD_H
#define LPD_H
#include "Hook.h"
#include "String.h"

class LogicProjectileData : public LogicData
{
private:
	/* data */
public:
	char gap9403849[152];
	bool Indirect;//152
	char gap13493849384[172 - 152 - 1];
	int Speed;//172
	char gap18499138493[372 - 172 - 4];
	int PoisonDamagePercent;//372
	int PoisonTickCount;//376
	char gap1[408 - 376 - 4];
	int PoisonType;//408
	int AppliedEffectVisualType;//412
	int TravelType;//416
	int TravelTypeVariable;//420
	bool IgnoreLevelBoarder;//424
	int SteerStrength;//428
	int SteerIgnoreTicks;//432
	int HomeDistance;//436
	int SteerLifeTime;//440
	bool VisualizeEndPoint;//444
	int UniqueProperty;//448
	int CustomUniquePropertyValue;//452
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