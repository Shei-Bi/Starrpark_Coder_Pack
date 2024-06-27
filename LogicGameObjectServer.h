#ifndef LGOS_H
#define LGOS_H
#include "LogicData.h"
#include "LogicGameObjectManagerServer.h"
#include "LogicPlayer.h"
#include "BitStream.h"

class LogicGameObjectServer
{
public:
	int GlobalID;//8
	char gap1[4];//12
	LogicData* Data;//16
	LogicGameObjectManagerServer* GameObjectManager;//24
	int MoveStartTick;//32
	int MoveEndTick;//36
	char gap2[8];//40
	int X;//48
	int Y;
	int Z;
	int Index;
	int TeamIndex;
	int WorldIndex;

	LogicGameObjectServer(LogicData* logicData)
	{
		GlobalID = 0;
		Data = logicData;

		GameObjectManager = nullptr;
		Z = 0;
		Index = 0;
		TeamIndex = 0;
		X = 0;
		Y = 0;
	}
	virtual void tick()
	{
	}
	int getX()
	{
		return X;
	}
	int getY()
	{
		return Y;
	}
	LogicData* getData()
	{
		return Data;
	}
	LogicGameObjectManagerServer* getLogicGameObjectManagerServer()
	{
		return GameObjectManager;
	}
	LogicBattleModeServer* getLogicBattleModeServer()
	{
		return GameObjectManager->getLogicBattleModeServer();
	}
	void setPosition(int x, int y, int z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	LogicPlayer* getPlayer() {
		return ((LogicPlayer * (*)(LogicGameObjectServer*))(base + 0x8AFB78))(this);
	}
	virtual void encode(BitStream* stream, int fadeCounter) {
		return ((void (*)(LogicGameObjectServer*, BitStream*, int))(base + 0x8AF7EC))(this, stream, fadeCounter);
	}
	int getGlobalID() {
		return GlobalID;
	}
	int getCardValueForPassiveFromPlayer(int type, int index) {
		return ((int (*)(LogicGameObjectServer*, int, int))(base + 0x8AFBC0))(this, type, index);
	}
};
#endif