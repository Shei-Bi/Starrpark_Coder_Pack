#ifndef LOGICTILE_H
#define LOGICTILE_H
#include "Hook.h"
#include "LogicTileData.h"
class LogicTile
{
public:
	LogicTileData *currentTileData; // 0
	LogicTileData *originalTileData; // 8
	char gap1[48];
	bool HidesHero; // IsGrass | 64
	bool HasWindAnim; // 65
	unsigned char unk_66; // 66
	bool IsIntervalDamageTile; // 67
	bool IsCurrentDataOpenTile; // 68
	char gap2[31]; // 69 to 99
	int TileDamage; // 100
	int TileSpeedChange; // 104

	int setData(LogicTileData *newTileData) {
		return ((int (*)(LogicTile*, LogicTileData*))(base + 0x7F9DD4))(this, newTileData);
	}
};
#endif