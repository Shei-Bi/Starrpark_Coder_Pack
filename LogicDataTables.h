#ifndef LDT_H
#define LDT_H
#include "Hook.h"
#include "LogicAreaEffectData.h"
#include "LogicProjectileData.h"

class LogicDataTables
{
public:
	static LogicAreaEffectData* getAreaEffectByName(void* name, void* idk) {
		return ((LogicAreaEffectData * (*)(void*, void*))base + 0x849898)(name, idk);
	}
	static LogicProjectileData* getProjectileByName(void* name, void* idk) {
		return ((LogicProjectileData * (*)(void*, void*))base + 0x849F9C)(name, idk);
	}
};
#endif