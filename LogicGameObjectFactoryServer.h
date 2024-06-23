#ifndef LOGICGAMEOBJECTFACTORYSERVER_H
#define LOGICGAMEOBJECTFACTORYSERVER_H
#include "Hook.h"
#include "LogicGameObjectServer.h"
#include "LogicData.h"
class LogicGameObjectFactoryServer
{
public:
	static LogicGameObjectServer* createGameObjectByData(LogicData* data) {
		return ((LogicGameObjectServer * (*)(LogicData*))(base + 0x8A5F64))(data);
	}
};
#endif