#ifndef LCS_H
#define LCS_H
class LogicCharacterServer : public LogicGameObjectServer
{
public:
   LogicCharacterServer(LogicData *logicData) : LogicGameObjectServer(logicData)
   {
      ;
   }
   char gap[1504 - 72];
   int ConsumableShield;
   int ConsumableShieldMax;
   void addConsumableShield(int amount)
   {
      ConsumableShield = amount;
      ConsumableShieldMax = amount;
   }
   void tick()
   {
      addConsumableShield(114514);
   }
};
#endif