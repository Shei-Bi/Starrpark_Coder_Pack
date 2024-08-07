#ifndef LGOMS_H
#define LGOMS_H
#include "LogicArrayList.h"

class LogicGameObjectServer;
class LogicItemServer;
class LogicCharacterServer;
class LogicProjectileServer;
class LogicAreaEffectServer;
class LogicBattleModeServer;
class LogicGameObjectManagerServer
{
public:
   LogicArrayList<LogicGameObjectServer*> GameObjects;//0
   char gap2243978[32 - 0 - 16];
   LogicArrayList<LogicCharacterServer*> Characters;//32
   LogicArrayList<LogicItemServer*> Items;//48
   LogicArrayList<LogicProjectileServer*> Projectiles;//64
   LogicArrayList<LogicAreaEffectServer*> AreaEffects;//80
   char gap1[168 - 80 - 16];
   LogicBattleModeServer* BattleMode;//168
   LogicBattleModeServer* getLogicBattleModeServer()
   {
      return BattleMode;
   }
   void addLogicGameObject(LogicGameObjectServer* object) {
      return ((void (*)(LogicGameObjectManagerServer*, LogicGameObjectServer*))(base + 0x8AB358))(this, object);
   }
   LogicArrayList<LogicGameObjectServer*> getGameObjects() {
      /*
For some enigmatic reason Supercell sort all types of objects into individual lists in tick(),
to avoid type casting?
Well, we should try to avoid using getGameObjects() then?
--Shei
      */
      return GameObjects;
   }
   void getCharacters(LogicArrayList<LogicCharacterServer*>* out) {
      ((void (*)(LogicGameObjectManagerServer*, LogicArrayList<LogicCharacterServer*>*))(base + 0x8AA0AC))(this, out);
   }
   void getProjectiles(LogicArrayList<LogicProjectileServer*>* out) {
      ((void (*)(LogicGameObjectManagerServer*, LogicArrayList<LogicProjectileServer*>*))(base + 0x8AA44C))(this, out);
   }
   LogicArrayList<LogicAreaEffectServer*> getAreaEffects() {
      return AreaEffects;
   }
   LogicArrayList<LogicItemServer*> getItems() {
      return Items;
   }
};
#endif