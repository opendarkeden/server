//--------------------------------------------------------------------------------
//
// Filename   : update.cpp
// Written By : elca
//
//--------------------------------------------------------------------------------

// include files
#include "Types.h"
#include "Exception.h"
#include "Properties.h"
#include "Update.h"
#include "UpdateManager.h"
#include <stdio.h>

#define PATCH_DIR "/home/darkeden/data/patch"
//#define PATCH_DIR "/home/excel96/vs/data/patch"

void version1()
{
	UpdateManager updateManager;
	int version = 1;

	//--------------------------------------------------------------------------------
	// save
	//--------------------------------------------------------------------------------
	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR,version);
	remove(filename);
	updateManager.save(filename);
}

void version2()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 2;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UI.spki 14");
	pUpdate->setParam(1,"Data\\Image\\UI.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"common_button.spk 22184");
	pUpdate->setParam(1,"Data\\UI\\spk\\common_button.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AddonShadow.cfpk 1413570");
	pUpdate->setParam(1,"Data\\Image\\AddonShadow.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemOption.inf 4715");
	pUpdate->setParam(1,"Data\\Info\\ItemOption.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"MousePointer.spk 16350");
	pUpdate->setParam(1,"Data\\UI\\spk\\MousePointer.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AssembleMessageBoxCommon.spk 123968");
	pUpdate->setParam(1,"Data\\UI\\spk\\AssembleMessageBoxCommon.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Addon.cfpk 1413570");
	pUpdate->setParam(1,"Data\\Image\\Addon.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Skill.inf 5921");
	pUpdate->setParam(1,"Data\\Info\\Skill.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Zone.inf 5304");
	pUpdate->setParam(1,"Data\\Info\\Zone.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UI.spk 73662");
	pUpdate->setParam(1,"Data\\Image\\UI.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SkillInfo.inf 7733");
	pUpdate->setParam(1,"Data\\Info\\SkillInfo.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SkillMini.spk 100972");
	pUpdate->setParam(1,"Data\\UI\\spk\\SkillMini.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.inf 24003");
	pUpdate->setParam(1,"Data\\Info\\Creature.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"String.inf 2439");
	pUpdate->setParam(1,"Data\\Info\\String.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_SW.map 563120");
	pUpdate->setParam(1,"Data\\Map\\eslania_SW.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ClientConfig.inf 263");
	pUpdate->setParam(1,"Data\\Info\\ClientConfig.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AssembleMessageBoxButton.spk 41814");
	pUpdate->setParam(1,"Data\\UI\\spk\\AssembleMessageBoxButton.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"tutorial_heliport.mip 61");
	pUpdate->setParam(1,"Data\\Map\\tutorial_heliport.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayer_main.spk 470480");
	pUpdate->setParam(1,"Data\\UI\\spk\\slayer_main.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VampireGameMenu.spk 142870");
	pUpdate->setParam(1,"Data\\UI\\spk\\VampireGameMenu.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.inf 30409");
	pUpdate->setParam(1,"Data\\Info\\Item.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_NE.mip 61");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_NE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"tutorial_bokdo.mip 110");
	pUpdate->setParam(1,"Data\\Map\\tutorial_bokdo.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Tutorial_Book.spk 563728");
	pUpdate->setParam(1,"Data\\UI\\spk\\Tutorial_Book.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AssembleMessageBox.spk 120510");
	pUpdate->setParam(1,"Data\\UI\\spk\\AssembleMessageBox.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_cleric_B1.mip 169");
	pUpdate->setParam(1,"Data\\Map\\guild_cleric_B1.mip");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DarkEden.exe 4247552");
	pUpdate->setParam(1,"DarkEden.exe");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DEUtil.dll 32768");
	pUpdate->setParam(1,"DEUtil.dll");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

int main ()
{
	__BEGIN_DEBUG

	version1();
	version2();

	__END_DEBUG
}
