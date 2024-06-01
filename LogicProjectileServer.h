#ifndef LPS_H
#define LPS_H
#include "LogicCharacterServer.h"
#include "LogicGameObjectServer.h"
#include "LogicBattleModeServer.h"
class LogicProjectileServer : public LogicGameObjectServer
{
public:
   char gap1[96 - 72];
   int StartX;
   int StartY;
   char gap3[28];
   int Damage;
   int NormalDMG;
   char gap2[4];
   LogicCharacterServer Owner = *(static_cast<LogicCharacterServer *>(nullptr));

   static LogicProjectileServer ShootProjectile(int, int, LogicCharacterServer, LogicGameObjectServer, LogicData, int, int, int, int, int, bool, int, LogicBattleModeServer, int, int);
   LogicProjectileServer(LogicData logicData) : LogicGameObjectServer(logicData)
   {
      ;
   }
   ~LogicProjectileServer();
   void tick()
   {
      ;
   }
   void __attribute__((used)) returnBoomerang()
   {
      if (Owner)
      {
         int boomerangX = Owner.GetX();
      }
      ShootProjectile(1, 2, *(static_cast<LogicCharacterServer *>(nullptr)), *(static_cast<LogicGameObjectServer *>(nullptr)), *(static_cast<LogicData *>(nullptr)), 4, 5, 6, 7, 8, true, 9, *(static_cast<LogicBattleModeServer *>(nullptr)), 10, 11);
   }
};
#endif