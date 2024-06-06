#ifndef LSD_H
#define LSD_H
#include "Hook.h"
#include"LogicData.h"
class LogicSkillData : public LogicData
{
public:
	int getMaxCharge()
	{
		return ((int (*)(LogicSkillData*))base + 0x873D40)(this);
	}
};
#endif