#ifndef LOGICPLAYER_H
#define LOGICPLAYER_H
class LogicAccessory;
class LogicPlayer
{
public:
   char gap1[280];
   LogicAccessory* Accessory;
   char gap2[328 - 280 - 8];
   int AccessoryUses;
};
#endif