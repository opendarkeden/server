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
	Update* pUpdate;
	int version = 1;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
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
	pUpdate->setParam(0,"VampireGameMenu.spk 142870");
	pUpdate->setParam(1,"Data\\UI\\spk\\VampireGameMenu.spk");
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
	pUpdate->setParam(0,"Addon.cfpk 1413570");
	pUpdate->setParam(1,"Data\\Image\\Addon.cfpk");
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


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version3()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 3;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version4()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 4;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_dungeon.mip 299");
	pUpdate->setParam(1,"Data\\Map\\limbo_dungeon.mip");
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
	pUpdate->setParam(0,"UI.spki 14");
	pUpdate->setParam(1,"Data\\Image\\UI.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_knight_2F.mip 160");
	pUpdate->setParam(1,"Data\\Map\\guild_knight_2F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VampireSkillView.spk 375782");
	pUpdate->setParam(1,"Data\\UI\\spk\\VampireSkillView.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_dungeon.mip 320");
	pUpdate->setParam(1,"Data\\Map\\eslania_dungeon.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Book.rpk 20349");
	pUpdate->setParam(1,"Data\\UI\\txt\\Book.rpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"TutorialEtc.rpk 3452");
	pUpdate->setParam(1,"Data\\UI\\txt\\TutorialEtc.rpk");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version5()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 5;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version6()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 6;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_NE.map 692298");
	pUpdate->setParam(1,"Data\\Map\\eslania_NE.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"credit.spk 974002");
	pUpdate->setParam(1,"Data\\UI\\spk\\credit.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_SW.map 858870");
	pUpdate->setParam(1,"Data\\Map\\drobeta_SW.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_cleric_1F.mip 162");
	pUpdate->setParam(1,"Data\\Map\\guild_cleric_1F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_stadium.map 76446");
	pUpdate->setParam(1,"Data\\Map\\drobeta_stadium.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_NE.map 578298");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_NE.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_SE.map 602508");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_SE.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_knight_B1.mip 204");
	pUpdate->setParam(1,"Data\\Map\\guild_knight_B1.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_SE.map 618706");
	pUpdate->setParam(1,"Data\\Map\\drobeta_SE.map");
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
	pUpdate->setParam(0,"drobeta_NW.map 647922");
	pUpdate->setParam(1,"Data\\Map\\drobeta_NW.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_SW.map 562644");
	pUpdate->setParam(1,"Data\\Map\\eslania_SW.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.rpk 83923");
	pUpdate->setParam(1,"Data\\UI\\txt\\Item.rpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemTile.ispki 922");
	pUpdate->setParam(1,"Data\\Image\\ItemTile.ispki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_SE.map 611136");
	pUpdate->setParam(1,"Data\\Map\\eslania_SE.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_NE.map 649370");
	pUpdate->setParam(1,"Data\\Map\\drobeta_NE.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_army_B1.mip 174");
	pUpdate->setParam(1,"Data\\Map\\guild_army_B1.mip");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version7()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 7;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version8()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 8;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Event_Fanfare.wav 746540");
	pUpdate->setParam(1,"Data\\Sound\\Event_Fanfare.wav");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version9()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 9;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version10()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 10;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version11()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 11;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version12()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 12;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New12Effect.aspk 4199002");
	pUpdate->setParam(1,"Data\\Image\\Effect.aspk");
	pUpdate->setParam(2,"New12Effect.aspki 1014");
	pUpdate->setParam(3,"Data\\Image\\Effect.aspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DomainExp.inf 11236");
	pUpdate->setParam(1,"Data\\Info\\DomainExp.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"INTExp.inf 1204");
	pUpdate->setParam(1,"Data\\Info\\INTExp.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"STRExp.inf 1204");
	pUpdate->setParam(1,"Data\\Info\\STRExp.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DEXExp.inf 1204");
	pUpdate->setParam(1,"Data\\Info\\DEXExp.inf");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version13()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 13;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"InventoryBackColor.spk 122642");
	pUpdate->setParam(1,"Data\\UI\\spk\\InventoryBackColor.spk");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version14()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 14;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version15()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 15;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Updater2.exe 950272");
	pUpdate->setParam(1,"Updater2.exe");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UpdateClient.inf 94");
	pUpdate->setParam(1,"Data\\Info\\UpdateClient.inf");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version16()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 16;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"face.spk 253570");
	pUpdate->setParam(1,"Data\\UI\\spk\\face.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayer_sys_button.spk 43434");
	pUpdate->setParam(1,"Data\\UI\\spk\\slayer_sys_button.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Time.spk 98198");
	pUpdate->setParam(1,"Data\\UI\\spk\\Time.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_sys_button.spk 45826");
	pUpdate->setParam(1,"Data\\UI\\spk\\vampire_sys_button.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_etc.spk 160744");
	pUpdate->setParam(1,"Data\\UI\\spk\\vampire_etc.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Time.spki 26");
	pUpdate->setParam(1,"Data\\UI\\spk\\Time.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"face.spki 34");
	pUpdate->setParam(1,"Data\\UI\\spk\\face.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_main.spk 476434");
	pUpdate->setParam(1,"Data\\UI\\spk\\vampire_main.spk");
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
	pUpdate->setParam(0,"VampireSkillView.spki 14");
	pUpdate->setParam(1,"Data\\UI\\spk\\VampireSkillView.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"minimap.spki 154");
	pUpdate->setParam(1,"Data\\UI\\spk\\minimap.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"minimap.spk 1157772");
	pUpdate->setParam(1,"Data\\UI\\spk\\minimap.spk");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version17()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 17;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version18()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 18;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_dungeon_B1F.mip 262");
	pUpdate->setParam(1,"Data\\Map\\bathory_dungeon_B1F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.ispki 942");
	pUpdate->setParam(1,"Data\\UI\\spk\\Item.ispki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemDrop.ispk 556160");
	pUpdate->setParam(1,"Data\\Image\\ItemDrop.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_village.map 149230");
	pUpdate->setParam(1,"Data\\Map\\vampire_village.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayers_training.mip 187");
	pUpdate->setParam(1,"Data\\Map\\slayers_training.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_dungeon_B3F.map 266674");
	pUpdate->setParam(1,"Data\\Map\\bathory_dungeon_B3F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_NW.mip 51");
	pUpdate->setParam(1,"Data\\Map\\eslania_NW.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_cleric_4F.map 4304");
	pUpdate->setParam(1,"Data\\Map\\guild_cleric_4F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CreatureShadow.cfpki 270");
	pUpdate->setParam(1,"Data\\Image\\CreatureShadow.cfpki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Skill.rpk 19498");
	pUpdate->setParam(1,"Data\\UI\\txt\\Skill.rpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemTile.ispk 136688");
	pUpdate->setParam(1,"Data\\Image\\ItemTile.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_army_4F.mip 47");
	pUpdate->setParam(1,"Data\\Map\\guild_army_4F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_SW.mip 26");
	pUpdate->setParam(1,"Data\\Map\\drobeta_SW.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.ispk 419102");
	pUpdate->setParam(1,"Data\\UI\\spk\\item.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CreatureShadow.cfpk 387307");
	pUpdate->setParam(1,"Data\\Image\\CreatureShadow.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_dungeon_B1F.map 241144");
	pUpdate->setParam(1,"Data\\Map\\bathory_dungeon_B1F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemDescription.spki 862");
	pUpdate->setParam(1,"Data\\UI\\spk\\ItemDescription.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New18Effect.aspk 1293266");
	pUpdate->setParam(1,"Data\\Image\\Effect.aspk");
	pUpdate->setParam(2,"New18Effect.aspki 730");
	pUpdate->setParam(3,"Data\\Image\\Effect.aspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_cleric_4F.mip 47");
	pUpdate->setParam(1,"Data\\Map\\guild_cleric_4F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_cleric_3F.mip 167");
	pUpdate->setParam(1,"Data\\Map\\guild_cleric_3F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SkillIcon.spk 331662");
	pUpdate->setParam(1,"Data\\UI\\spk\\SkillIcon.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_dungeon_B2F.map 236896");
	pUpdate->setParam(1,"Data\\Map\\bathory_dungeon_B2F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_NW.mip 58");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_NW.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_SE.mip 26");
	pUpdate->setParam(1,"Data\\Map\\drobeta_SE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_NE.mip 33");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_NE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_army_4F.map 4304");
	pUpdate->setParam(1,"Data\\Map\\guild_army_4F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New18Creature.sspk 558166");
	pUpdate->setParam(1,"Data\\Image\\Creature.sspk");
	pUpdate->setParam(2,"New18Creature.sspki 4194");
	pUpdate->setParam(3,"Data\\Image\\Creature.sspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_knight_4F.mip 47");
	pUpdate->setParam(1,"Data\\Map\\guild_knight_4F.mip");
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
	pUpdate->setParam(0,"eslania_SE.mip 51");
	pUpdate->setParam(1,"Data\\Map\\eslania_SE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_NE.mip 33");
	pUpdate->setParam(1,"Data\\Map\\drobeta_NE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_army_3F.mip 181");
	pUpdate->setParam(1,"Data\\Map\\guild_army_3F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_lair.mip 40");
	pUpdate->setParam(1,"Data\\Map\\bathory_lair.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemTile.ifpk 1388");
	pUpdate->setParam(1,"Data\\Image\\ItemTile.ifpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_NE.mip 152");
	pUpdate->setParam(1,"Data\\Map\\eslania_NE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New18Tile.spk 5645274");
	pUpdate->setParam(1,"Data\\Image\\tile.spk");
	pUpdate->setParam(2,"New18Tile.spki 12682");
	pUpdate->setParam(3,"Data\\Image\\tile.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New18ImageObject.sspk 36842");
	pUpdate->setParam(1,"Data\\Image\\ImageObject.sspk");
	pUpdate->setParam(2,"New18ImageObject.sspki 522");
	pUpdate->setParam(3,"Data\\Image\\ImageObject.sspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_dungeon_B2F.mip 75");
	pUpdate->setParam(1,"Data\\Map\\bathory_dungeon_B2F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_SW.mip 58");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_SW.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SkillIcon.spki 462");
	pUpdate->setParam(1,"Data\\UI\\spk\\SkillIcon.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_lair.map 33734");
	pUpdate->setParam(1,"Data\\Map\\bathory_lair.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SkillMini.spki 462");
	pUpdate->setParam(1,"Data\\UI\\spk\\SkillMini.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_knight_3F.mip 174");
	pUpdate->setParam(1,"Data\\Map\\guild_knight_3F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"drobeta_NW.mip 33");
	pUpdate->setParam(1,"Data\\Map\\drobeta_NW.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"eslania_SW.mip 51");
	pUpdate->setParam(1,"Data\\Map\\eslania_SW.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayers_training.map 679678");
	pUpdate->setParam(1,"Data\\Map\\slayers_training.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemDrop.afpk 8780");
	pUpdate->setParam(1,"Data\\Image\\ItemDrop.afpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_knight_4F.map 4304");
	pUpdate->setParam(1,"Data\\Map\\guild_knight_4F.map");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version19()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 19;


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version20()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 20;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Effect.efpk 123088");
	pUpdate->setParam(1,"Data\\Image\\Effect.efpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.inf 27443");
	pUpdate->setParam(1,"Data\\Info\\Creature.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VD_drained.wav 179244");
	pUpdate->setParam(1,"Data\\Sound\\VD_drained.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VD_damage.wav 16428");
	pUpdate->setParam(1,"Data\\Sound\\VD_damage.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Help.rpk 10740");
	pUpdate->setParam(1,"Data\\UI\\txt\\Help.rpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CreatureSprite.inf 1246");
	pUpdate->setParam(1,"Data\\Info\\CreatureSprite.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VD_die.wav 116780");
	pUpdate->setParam(1,"Data\\Sound\\VD_die.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UICreature.cfpk 1578");
	pUpdate->setParam(1,"Data\\UI\\frame\\UICreature.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_knight_3F.map 40710");
	pUpdate->setParam(1,"Data\\Map\\guild_knight_3F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ShopTemplate.inf 1204");
	pUpdate->setParam(1,"Data\\Info\\ShopTemplate.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_blade_TS.wav 69292");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_blade_TS.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"BF_drain.wav 225580");
	pUpdate->setParam(1,"Data\\Sound\\BF_drain.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Action.inf 41685");
	pUpdate->setParam(1,"Data\\Info\\Action.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.ispki 47514");
	pUpdate->setParam(1,"Data\\Image\\Creature.ispki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"NpcFace.spk 1478514");
	pUpdate->setParam(1,"Data\\UI\\spk\\NpcFace.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_Enchant_Identify.wav 161412");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_Enchant_Identify.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bathory_dungeon_B3F.mip 156");
	pUpdate->setParam(1,"Data\\Map\\bathory_dungeon_B3F.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_Heal_Sacrifice.wav 110380");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_Heal_Sacrifice.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"EffectStatus.inf 587");
	pUpdate->setParam(1,"Data\\Info\\EffectStatus.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_Enchant_DetectInvisibility.wav 71980");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_Enchant_DetectInvisibility.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_SE.mip 233");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_SE.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UICreature.ispk 583074");
	pUpdate->setParam(1,"Data\\UI\\spk\\UICreature.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_army_3F.map 41686");
	pUpdate->setParam(1,"Data\\Map\\guild_army_3F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemOption.inf 4714");
	pUpdate->setParam(1,"Data\\Info\\ItemOption.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_enchant_PFA.wav 66988");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_enchant_PFA.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_sword_SW.wav 47660");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_sword_SW.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_sword_LH.wav 30590");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_sword_LH.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"BF_attack.wav 35948");
	pUpdate->setParam(1,"Data\\Sound\\BF_attack.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VD_attack.wav 28108");
	pUpdate->setParam(1,"Data\\Sound\\VD_attack.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"BF_die.wav 192044");
	pUpdate->setParam(1,"Data\\Sound\\BF_die.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"NpcFace.spki 190");
	pUpdate->setParam(1,"Data\\UI\\spk\\NpcFace.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_sword_SC.wav 47468");
	pUpdate->setParam(1,"Data\\Sound\\Slayer_sword_SC.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"BF_damage.wav 21452");
	pUpdate->setParam(1,"Data\\Sound\\BF_damage.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Sound.inf 9547");
	pUpdate->setParam(1,"Data\\Info\\Sound.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"NPCScript.inf 48008");
	pUpdate->setParam(1,"Data\\Info\\NPCScript.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DEUtil.dll 32768");
	pUpdate->setParam(1,"DEUtil.dll");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_village.mip 215");
	pUpdate->setParam(1,"Data\\Map\\vampire_village.mip");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild_cleric_3F.map 42942");
	pUpdate->setParam(1,"Data\\Map\\guild_cleric_3F.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Zone.inf 6165");
	pUpdate->setParam(1,"Data\\Info\\Zone.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"EffectSpriteType.inf 868");
	pUpdate->setParam(1,"Data\\Info\\EffectSpriteType.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Skill.inf 5935");
	pUpdate->setParam(1,"Data\\Info\\Skill.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Vampire_AcidSwamp.wav 103468");
	pUpdate->setParam(1,"Data\\Sound\\Vampire_AcidSwamp.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VampireExp.inf 1204");
	pUpdate->setParam(1,"Data\\Info\\VampireExp.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VD_drain.wav 216364");
	pUpdate->setParam(1,"Data\\Sound\\VD_drain.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"BF_drained.wav 181036");
	pUpdate->setParam(1,"Data\\Sound\\BF_drained.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"NPC.inf 548");
	pUpdate->setParam(1,"Data\\Info\\NPC.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"String.inf 2729");
	pUpdate->setParam(1,"Data\\Info\\String.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"New18Creature.ispk 4343846");
	pUpdate->setParam(1,"Data\\Image\\New18Creature.ispk");
	updateManager.push_back( pUpdate );

	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}


void version21()
{
	UpdateManager updateManager;
	Update* pUpdate;
	int version = 21;


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.inf 33074");
	pUpdate->setParam(1,"Data\\Info\\Item.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"New18ImageObject.spk 1968462");
	pUpdate->setParam(1,"Data\\Image\\New18ImageObject.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SkillInfo.inf 7966");
	pUpdate->setParam(1,"Data\\Info\\SkillInfo.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.cfpk 387763");
	pUpdate->setParam(1,"Data\\Image\\Creature.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.cfpki 270");
	pUpdate->setParam(1,"Data\\Image\\Creature.cfpki");
	updateManager.push_back( pUpdate );



	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Chat.inf 10783");
	pUpdate->setParam(1,"Data\\Info\\Chat.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DarkEden.exe 4276224");
	pUpdate->setParam(1,"DarkEden.exe");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"limbo_lair_SW.map 606494");
	pUpdate->setParam(1,"Data\\Map\\limbo_lair_SW.map");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

int main()
{
	__BEGIN_DEBUG


	version1();
	version2();
	version3();
	version4();
	version5();
	version6();
	version7();
	version8();
	version9();
	version10();
	version11();
	version12();
	version13();
	version14();
	version15();
	version16();
	version17();
	version18();
	version19();
	version20();
	version21();


	__END_DEBUG
}
