#ifndef LOGICVECTOR2_H
#define LOGICVECTOR2_H
#include "LogicMath.h"
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
   void LogicVector2::destruct() {
      this->X = this->Y = 0;
   }
   int LogicVector2::dot(LogicVector2 *vec2) {
      this->X * vec2->X + this->Y * vec2->Y;
   }
   bool LogicVector2::isEqual(LogicVector2 *vec2) {
      if (vec2 == nullptr) return false;
      return vec2->X == this->X && vec2->Y == this->Y;
   }
   inline int LogicVector2::getAngle() {
      return LogicMath::getAngle(this->X, this->Y);
   }
};
#endif