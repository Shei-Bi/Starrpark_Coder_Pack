#ifndef LOGICGEAR_H
#define LOGICGEAR_H

#include "LogicGearData.h"
#include "BitStream.h"

//guessed names.
class LogicGear
{
public:
	LogicGearData* GearData;//0
	int Type;//8
	int ShieldMax;//12
	int Shield;//16
	bool IsActive;//20
	int ActiveTicks;

	LogicGear(LogicGearData* data)
	{
		Type = data->getLogicType();
		GearData = data;
		if (Type == 4) {
			ShieldMax = data->getModifierValue();
		}
	}
	void encode(BitStream*);
};
void LogicGear::encode(BitStream* stream) {
	stream->writeBoolean(IsActive);
	if (Type == 4) stream->writePositiveIntMax1023(Shield);
}
#endif