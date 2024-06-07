#ifndef LAD_H
#define LAD_H
#include "Hook.h"
#include"LogicData.h"
class LogicAccessoryData : public LogicData
{
public:
	int getMaxCharge()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x873D40)(this);
	}
	bool getInterruptsAction()
	{
		return ((bool (*)(LogicAccessoryData*))base + 0x82AA14)(this);
	}
	bool getStopMovement()
	{
		return ((bool (*)(LogicAccessoryData*))base + 0x82A994)(this);
	}
	int getActivationDelay()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82A964)(this);
	}
	int getActiveTicks()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82A974)(this);
	}
	int getCoolDown()
	{
		return ((int (*)(LogicAccessoryData*))base + 0x82A914)(this);
	}
};
#endif