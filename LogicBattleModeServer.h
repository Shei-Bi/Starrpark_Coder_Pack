#ifndef LBMS_H
#define LBMS_H
#include "Hook.h"
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
	   return ((int (*)(LogicBattleModeServer*))base + 0x9458E0)(this);
   }
   int getTick() {
	   return getTicksGone();
   }
};

LogicBattleModeServer::LogicBattleModeServer(/* args */)
{
}

LogicBattleModeServer::~LogicBattleModeServer()
{
}
#endif