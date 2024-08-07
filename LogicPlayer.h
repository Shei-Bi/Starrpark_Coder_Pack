#ifndef LOGICPLAYER_H
#define LOGICPLAYER_H
class LogicAccessory;
class LogicPlayer
{
public:
   char gap1398483198493[76];
   int ultiCharge;//76
   int ultiChargeMax;//80
   char gap1[280 - 80 - 4];
   LogicAccessory* Accessory;//280
   char gap2[328 - 280 - 8];
   int AccessoryUses;//328
   char gap3[348 - 328 - 4];
   int WillowObjectId;//348
   int getWillowObjectId() {
      return WillowObjectId;
   }
};
#endif