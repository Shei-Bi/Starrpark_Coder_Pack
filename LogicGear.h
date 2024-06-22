#ifndef LOGICGEAR_H
#define LOGICGEAR_H

#include "LogicGearData.h"
#include "BitStream.h"
#include "LogicCharacterServer.h"

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

	enum GearTypes//guessed names (from csv)
	{
		ForestSpeed = 0,
		HealthRegen = 1,
		LowHealthDamage = 2,
		Vision = 3,
		ConsumableShield = 4
	};
	LogicGear(LogicGearData* data)
	{
		Type = data->getLogicType();
		GearData = data;
		if (Type == ConsumableShield) {
			ShieldMax = data->getModifierValue();
		}
	}
	void encode(BitStream*);
	void tick(LogicCharacterServer* owner) {
		switch (Type)
		{
		case LowHealthDamage:
			if (owner->Hitpoints * 100 / owner->HitpointsMax < 50) owner->giveDamageBuff(GearData->getModifierValue(), 2);
			break;
		case ForestSpeed:
			/*
			Refactor. Reason: Supercell一直用 LogicTileMap::logicToPathFinderTile(logic) / 3 求LogicTile，但前者等价于 / 100 ，也许他这样有特殊的理由......
			--Shei
			*/
			if (owner->getLogicBattleModeServer()->getTileMap()->getTile(owner->GetX() / 300, owner->GetY() / 300)->HidesHero) owner->giveSpeedFasterBuff(GearData->getModifierValue(), 2, false);
			break;
		}
	}
};
void LogicGear::encode(BitStream* stream) {
	stream->writeBoolean(IsActive);
	if (Type == ConsumableShield) stream->writePositiveIntMax1023(Shield);
}
#endif