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
		/*
			这两个函数没有任何的区别。但是源码中前者使用的频率仅为后者的七分之一。
			--Shei
		*/
		return getTicksGone();
	}
	LogicTileMap* getTileMap() {
		return ((LogicTileMap * (*)(LogicBattleModeServer*))(base + 0x94A448))(this);
	}
};
#endif