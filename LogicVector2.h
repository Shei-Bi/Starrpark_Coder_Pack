#ifndef LOGICVECTOR2_H
#define LOGICVECTOR2_H
class LogicVector2
{
public:
   int X;
   int Y;
   LogicVector2()
   {
      X = 0;
      Y = 0;
   }
   LogicVector2(int x, int y)
   {
      X = x;
      Y = y;
   }
};
#endif