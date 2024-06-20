#ifndef LOGICHEROUPGRADES_H
#define LOGICHEROUPGRADES_H
#include "LogicCardData.h"
#include "LogicAccessoryData.h"
#include "LogicGearData.h"

class LogicHeroUpgrades
{
public:
	int Level;
	char gap[4];
	LogicCardData* CardData;
	LogicAccessoryData* AccessoryData;
	LogicGearData* GearData1;
	LogicGearData* GearData2;
	LogicCardData* OverchargeData;
};
#endif