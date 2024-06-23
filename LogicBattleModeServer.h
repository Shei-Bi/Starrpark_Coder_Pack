#ifndef LBMS_H
#define LBMS_H
#include "Hook.h"
#include "LogicTileMap.h"
#include "LogicPathFinder.h"

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
			����������û���κε����𡣵���Դ����ǰ��ʹ�õ�Ƶ�ʽ�Ϊ���ߵ��߷�֮һ��
			--Shei
		*/
		return getTicksGone();
	}
	LogicTileMap* getTileMap() {
		return ((LogicTileMap * (*)(LogicBattleModeServer*))(base + 0x94A448))(this);
	}
	LogicPathFinder* getPathFinder() {
		return ((LogicPathFinder * (*)(LogicBattleModeServer*))(base + 0x94E278))(this);

	}
};
#endif