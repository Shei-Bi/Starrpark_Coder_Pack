#ifndef LSD_H
#define LSD_H
#include "Hook.h"
#include"LogicData.h"
class LogicSkillData : public LogicData
{
public:
	char gap1[340];
	int BehaviorType;
	char gap2[356 - 340 - 4];
	bool HoldToShoot;
	int getMaxCharge()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873D40))(this);
	}
	int getCastingTime()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873BB4))(this);
	}
	int getChargeSpeed()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873B5C))(this);
	}
	int getChargeType()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873D20))(this);
	}
	int getActiveTime()
	{
		return ((int (*)(LogicSkillData*))(base + 0x873B8C))(this);
	}
};
#endif