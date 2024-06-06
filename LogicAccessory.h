#ifndef LOGICACCESSORY_H
#define LOGICACCESSORY_H
#include "LogicMath.h"
#include "LogicSkillData.h"
#include "LogicCharacterServer.h"
#include "LogicAccessoryData.h"
#include "BitStream.h"

class LogicAccessory
{
public:
	LogicAccessoryData* AccessoryData;
	int Uses;
	int UNK2;
	int CoolDown;
	int State;
	int Type;
	int ActivationDelay;
	int X;
	int Y;
	int TicksActive;
	bool IsActive;
	int qword30;
	int field_34;
	int StartUsingTick;
	int Angle;

	LogicAccessory(LogicAccessoryData*, int);
	void encode(BitStream*, bool);
};
LogicAccessory::LogicAccessory(LogicAccessoryData* data, int count) {
	AccessoryData = data;
	IsActive = true;
}
void LogicAccessory::encode(BitStream* stream, bool isSelf) {
	if (isSelf) {
		stream->writePositiveVIntMax255OftenZero(CoolDown);
		stream->writePositiveVIntMax255OftenZero(State);
	}
	else stream->writeBoolean(State == 1);
	if (State == 1) {
		stream->writePositiveIntMax16383(StartUsingTick);
		stream->writePositiveIntMax511(Angle);
	}
}
#endif