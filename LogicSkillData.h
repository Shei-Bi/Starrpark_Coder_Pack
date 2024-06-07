#ifndef LSD_H
#define LSD_H
#include "Hook.h"
#include"LogicData.h"
class LogicSkillData : public LogicData
{
public:
	char gap1[340];
	int BehaviorType;
	int getMaxCharge()
	{
		return ((int (*)(LogicSkillData*))base + 0x873D40)(this);
	}
	int getCastingTime()
	{
		return ((int (*)(LogicSkillData*))base + 0x873BB4)(this);
	}
};
#endif