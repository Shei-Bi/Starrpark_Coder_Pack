#ifndef LOGICBUFFSERVER_H
#define LOGICBUFFSERVER_H
#include "LogicCharacterServer.h"
#include "LogicData.h"
class LogicBuffServer
{
public:
	int Type;
	int Duration;
	int MaxDuration;
	int Modifier;
	int Int1;
	int BelleWeaponRadius;
	int BelleWeaponBounces;
	int field_1C;
	LogicData* SourceData;
	int Index;
	int TeamIndex;
	int WorldIndex;

	LogicBuffServer(int type, int duration, int modifier, int int1)
	{
		Type = type;
		Duration = duration;
		MaxDuration = duration;
		Modifier = modifier;
		Int1 = int1;
	}
	bool tick(LogicCharacterServer* owner) {
		return ((bool (*)(LogicBuffServer*, LogicCharacterServer*))(base + 0x87F660))(this, owner);
	}
};
#endif