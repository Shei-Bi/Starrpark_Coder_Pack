#ifndef LPS_H
#define LPS_H
#include "LogicCharacterServer.h"
#include "LogicGameObjectServer.h"
#include "LogicBattleModeServer.h"
#include "LogicProjectileData.h"
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
   LogicCharacterServer *Owner;

   static LogicProjectileServer *ShootProjectile(int, int, LogicCharacterServer *, LogicGameObjectServer *, LogicProjectileData *, int, int, int, int, int, bool, int, LogicBattleModeServer *, int, int)
   {
      ;
   }
   LogicProjectileServer(LogicProjectileData *logicProjectileData) : LogicGameObjectServer(logicProjectileData)
   {
      ;
   }
   ~LogicProjectileServer();
   void tick()
   {
      ;
   }
   void __attribute__((used)) returnBoomerang()
   // void returnBoomerang();
   {
      int boomerangX;
      int boomerangY;
      if (Owner)
      {
         boomerangX = Owner->GetX();
         boomerangY = Owner->GetY();
      }
      else
      {
         boomerangX = StartX;
         boomerangY = StartY;
      }
      LogicProjectileServer *boomerang = ShootProjectile(-1, -1, Owner, this, ((LogicProjectileData *)getData())->getChainedBullet(), boomerangX, boomerangY, Damage, NormalDMG, 0, false, 0, getLogicBattleModeServer(), 0, 0);
   }
};
#endif