#include "LogicGameObjectServer.h"
#include "LogicSkillServer.h"
#include "LogicCharacterServer.h"
#include "LogicProjectileServer.h"
#include "LogicAccessory.h"
#include "Hook.h"
#include <cstddef>
//#include<dlfcn.h>
int main() {
	//*void useds[] = {LogicProjectileServer::ShootProjectile};
	//base = dlsym(dlopen("libg.so", 1), "JNI_Onload") - 0xD02390;
	/*LogicProjectileServer::ShootProjectile(int a1, int a2, LogicCharacterServer* a3, LogicGameObjectServer* a4, LogicProjectileData* a5, int a6, int a7, int a8, int a9, int a1, bool, int, LogicBattleModeServer*, int, int) {
		(void(*)(void))libgbase;
	}*/
	// LogicGameObjectServer l[2];
	// l[0] = new LogicCharacterServer();
	// l[0].tick();
	// LogicData o = LogicData();
	// LogicCharacterServer e = LogicCharacterServer(o);
	// // e = LogicCharacterServer();
	// e.tick();
	// LogicProjectileServer p = LogicProjectileServer(o);
	// p.tick();
	// new LogicProjectileServer(new LogicData())->returnBoomerang();

};