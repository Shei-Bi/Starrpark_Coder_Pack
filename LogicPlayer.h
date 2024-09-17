#ifndef LOGICPLAYER_H
#define LOGICPLAYER_H
#include "LogicArrayList.h"
#include "LogicHeroEntry.h"
#include "LogicSkinData.h"
#include "LogicLong.h"

class LogicAccessory;
class LogicPlayer
{
public://found names from json encode lol
   LogicLong* avatarId;//0
   int index;//8
   int team;//12
   int characterGID;//16
   char gap394723894[48 - 16 - 4];
   LogicArrayList<LogicHeroEntry*> heroSetups;//48
   char gap193819849[64 - 48 - 16];
   int CurrentHeroIndex;//64
   char gap1398483198493[76 - 64 - 4];
   int UltiCharge;//76
   int UltiChargeMax;//80
   char gap1894393489[92 - 80 - 4];
   int OverCharge;//92
   int OverChargeMax;//96
   bool OverCharging;//100
   bool OverChargeStartedFlag;//101
   bool OverChargeOnStart;//102
   bool OverChargeOnEnd;//103
   int speedIncrease;//104
   char gap1[280 - 104 - 4];
   LogicAccessory* Accessory;//280
   char gap2[328 - 280 - 8];
   int AccessoryUses;//328
   char gap13040349[336 - 328 - 4];
   LogicSkinData* PetCharacterSkin;//336
   char gap3[348 - 336 - 8];
   int WillowObjectId;//348
   int getWillowObjectId() {
      return WillowObjectId;
   }
   LogicHeroEntry* getCurrentHeroSetup() { //refactor: potential inlined functoin in libg?
      return heroSetups[CurrentHeroIndex];
   }
   bool hasOverChargeData() {
      LogicHeroUpgrades* upgrades = getCurrentHeroSetup()->upgrades;
      return upgrades && upgrades->overcharge;
   }
};
#endif