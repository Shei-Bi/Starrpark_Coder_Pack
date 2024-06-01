#ifndef LGOMS_H
#define LGOMS_H
#include "LogicBattleModeServer.h"
class LogicGameObjectManagerServer
{
private:
   /* data */
public:
   char gap1[168];
   LogicBattleModeServer *BattleMode;
   LogicGameObjectManagerServer(/* args */);
   ~LogicGameObjectManagerServer();
   LogicBattleModeServer *getLogicBattleModeServer()
   {
      return BattleMode;
   }
};

LogicGameObjectManagerServer ::LogicGameObjectManagerServer(/* args */)
{
}

LogicGameObjectManagerServer ::~LogicGameObjectManagerServer()
{
}
#endif