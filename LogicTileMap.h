#ifndef LOGICTILEMAP_H
#define LOGICTILEMAP_H
#include "Hook.h"
#include "LogicTile.h"
#include "LogicArrayList.h"

class LogicTileMap
{
public:
	LogicArrayList<LogicTile*> Tiles;
	char gap1[148];
	int Width;
	int Height;
	int LogicWidth;
	int LogicHeight;
	int logicToPathFinderTile(int logic) {
		return logic / 100;
	}
	LogicTile* getTile(int x, int y) {
		if (x < 0 || Width <= x || y < 0 || Height <= y) return nullptr;
		return Tiles[x + Width * y];
	}

};
#endif