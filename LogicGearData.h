#ifndef LOGICGEARDATA_H
#define LOGICGEARDATA_H
#include "Hook.h"
#include "LogicData.h"
class LogicGearData : public LogicData
{
public:
	int getLogicType()
	{
		return ((int (*)(LogicGearData*))(base + 0x853C20))(this);
	}
	int getModifierValue()
	{
		return ((int (*)(LogicGearData*))(base + 0x853C30))(this);
	}
};
#endif