#ifndef LBMS_H
#define LBMS_H
#include "Hook.h"
#include "LogicTileMap.h"
class LogicBattleModeServer
{
private:
	/* data */
public:
	int a;
	int b;
	LogicBattleModeServer(/* args */);
	~LogicBattleModeServer();
	int getTicksGone() {
		return ((int (*)(LogicBattleModeServer*))(base + 0x9458E0))(this);
	}
	int getTick() {
		return getTicksGone();
	}
	LogicTileMap* getTileMap() {
		return ((LogicTileMap * (*)(LogicBattleModeServer*))(base + 0x94A448))(this);
	}
};
#endif