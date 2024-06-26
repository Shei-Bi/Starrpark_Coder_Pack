#ifndef LD_H
#define LD_H
#include "Hook.h"

class LogicData
{
public:
   int getInstanceID()
   {
      return ((int (*)(LogicData*))(base + 0x83F2EC))(this);
   }
};
#endif