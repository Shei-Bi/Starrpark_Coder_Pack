#ifndef LGOS_H
#define LGOS_H
#include "LogicData.h"
#include "LogicGameObjectManagerServer.h"
class LogicGameObjectServer
{
private:
   /* data */
public:
   int GlobalID;
   char gap1[4];
   LogicData Data;
   LogicGameObjectManagerServer GameObjectManager;
   char gap2[16];
   int X;
   int Y;
   int Z;
   int Index;
   int TeamIndex;
   int WorldIndex;

   LogicGameObjectServer(LogicData logicData)
   {
      GlobalID = 0;
      Data = logicData;

      GameObjectManager = *(static_cast<LogicGameObjectManagerServer *>(nullptr));
      Z = 0;
      Index = 0;
      TeamIndex = 0;
      X = 0;
      Y = 0;
   }
   virtual void tick()
   {
   }
   int GetX()
   {
      return X;
   }
   int GetY()
   {
      return Y;
   }
   ~LogicGameObjectServer()
   {
      ;
   }
};
#endif