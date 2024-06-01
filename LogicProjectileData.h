#ifndef LPD_H
#define LPD_H
class LogicProjectileData : public LogicData
{
private:
   /* data */
public:
   char gap1[256 - 8];
   LogicProjectileData *ChainedBullet;
   LogicProjectileData *getChainedBullet()
   {
      return ChainedBullet;
   }
};
#endif