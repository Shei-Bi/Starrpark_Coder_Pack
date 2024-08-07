#ifndef LOGICHEROUPGRADES_H
#define LOGICHEROUPGRADES_H
#include "LogicCardData.h"
#include "LogicAccessoryData.h"
#include "LogicGearData.h"

class LogicHeroUpgrades
{
public:
	int Level;//0
	char gap[4];
	LogicCardData* CardData;//8
	LogicAccessoryData* AccessoryData;//16
	LogicGearData* GearData1;//24
	LogicGearData* GearData2;//32
	LogicCardData* OverchargeData;//40
};
#endif