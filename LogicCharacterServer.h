class LogicCharacterServer : public LogicGameObjectServer
{
public:
   LogicCharacterServer(/* args */)
   {
      LogicGameObjectServer();
   }
   LogicCharacterServer(LogicGameObjectServer e)
   {
      LogicGameObjectServer();
   }
   char gap[1504];
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