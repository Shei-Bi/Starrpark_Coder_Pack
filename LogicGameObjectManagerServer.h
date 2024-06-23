#ifndef LGOMS_H
#define LGOMS_H
#include "LogicBattleModeServer.h"

class LogicGameObjectServer;
class LogicGameObjectManagerServer
{
private:
   /* data */
public:
   char gap1[168];
   LogicBattleModeServer* BattleMode;
   LogicGameObjectManagerServer(/* args */);
   ~LogicGameObjectManagerServer();
   LogicBattleModeServer* getLogicBattleModeServer()
   {
      return BattleMode;
   }
   void addLogicGameObject(LogicGameObjectServer* object) {
      return ((void (*)(LogicGameObjectManagerServer*, LogicGameObjectServer*))(base + 0x8AB358))(this, object);
   }
};

LogicGameObjectManagerServer::LogicGameObjectManagerServer(/* args */)
{
}

LogicGameObjectManagerServer ::~LogicGameObjectManagerServer()
{
}
#endif