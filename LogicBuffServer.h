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

	enum BuffTypes//guessed names
	{
		Damage = 1,
		DamageAndSize = 2,
		SpeedSlower = 3,
		SpeedFaster = 4,
		Damage2 = 5,
		Slippery = 7,
		DamageNerf = 8,
		HealthRegen = 9,
		BelleWeapon = 14,
		BelleUlti = 15
	};
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
	static bool canBuffStack(int type) {
		return type == HealthRegen;
	}
};
#endif