#ifndef LOGICHEROUPGRADES_H
#define LOGICHEROUPGRADES_H
#include "LogicCardData.h"
#include "LogicAccessoryData.h"
#include "LogicGearData.h"

class LogicHeroUpgrades
{
public://found names from json encode lol
	int heroLevel;//0
	LogicCardData* starPower;//8
	LogicAccessoryData* accessory;//16
	LogicGearData* gearBoost1;//24
	LogicGearData* gearBoost2;//32
	LogicCardData* overcharge;//40
};
#endif