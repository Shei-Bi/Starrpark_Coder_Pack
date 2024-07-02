#ifndef LDT_H
#define LDT_H
#include "Hook.h"
#include "LogicAreaEffectData.h"
#include "LogicProjectileData.h"
#include "LogicCardData.h"
#include "String.h"

class LogicDataTables
{
public:
	static LogicAreaEffectData* getAreaEffectByName(String* name, void* idk) {
		return ((LogicAreaEffectData * (*)(String*, void*))(base + 0x849898))(name, idk);
	}
	static LogicProjectileData* getProjectileByName(String* name, void* idk) {
		return ((LogicProjectileData * (*)(String*, void*))(base + 0x849F9C))(name, idk);
	}
	static LogicCardData* getItemFor(LogicCharacterData* character, int metaType) {
		return ((LogicCardData * (*)(LogicCharacterData*, int))(base + 0x844944))(character, metaType);
	}
};
#endif