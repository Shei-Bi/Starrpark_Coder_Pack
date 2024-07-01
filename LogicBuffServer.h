#ifndef LOGICBUFFSERVER_H
#define LOGICBUFFSERVER_H
#include "LogicCharacterServer.h"
#include "LogicData.h"
class LogicBuffServer
{
public:
	int Type;//*
	int Duration;//4
	int MaxDuration;//8
	int Modifier;//12
	int Int1;//16
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
		DamageAndSpeed = 6,
		Slippery = 7,
		ReloadDebuff = 8,
		ReloadBuff = 9,
		HealthRegen = 10,
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