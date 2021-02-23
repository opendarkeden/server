void version0002()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 2


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemDrop.ispk 332580");
	pUpdate->setParam(1,"Data/Image/ItemDrop.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_sys_button.spk 17118");
	pUpdate->setParam(1,"Data/UI/SPK/vampire_sys_button.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_etc.spk 47028");
	pUpdate->setParam(1,"Data/UI/SPK/vampire_etc.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayer_main.spk 163142");
	pUpdate->setParam(1,"Data/UI/SPK/slayer_main.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"skilltree_ico_heal.spk 27342");
	pUpdate->setParam(1,"Data/UI/SPK/skilltree_ico_heal.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"itemTile.ispk 86008");
	pUpdate->setParam(1,"Data/Image/itemTile.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"vampire_main.spk 183598");
	pUpdate->setParam(1,"Data/UI/SPK/vampire_main.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"skilltree_back_heal.spk 201078");
	pUpdate->setParam(1,"Data/UI/SPK/skilltree_back_heal.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"item.ispk 293172");
	pUpdate->setParam(1,"Data/UI/SPK/item.ispk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"skill.rbt 391318");
	pUpdate->setParam(1,"Data/UI/RBT/skill.rbt");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Music.inf 303");
	pUpdate->setParam(1,"Data/Info/Music.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Slayer_belt.wav 13872");
	pUpdate->setParam(1,"Data/Sound/Slayer_belt.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"skilltree_ico_gun.spk 30076");
	pUpdate->setParam(1,"Data/UI/SPK/skilltree_ico_gun.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"skilltree_back_gun.spk 277118");
	pUpdate->setParam(1,"Data/UI/SPK/skilltree_back_gun.spk");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0003()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 3


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0004()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 4


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0005()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 5


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0006()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 6


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"itemTile.ifpk 866");
	pUpdate->setParam(1,"Data/Image/itemTile.ifpk");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0007()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 7


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0008()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 8


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0009()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 9


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0010()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 10


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0011()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 11


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0012()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 12


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0013()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 13


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g2.spr 48870");
	pUpdate->setParam(1,"Data/Image/g2.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g3.spr 47444");
	pUpdate->setParam(1,"Data/Image/g3.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ex3.spr 66564");
	pUpdate->setParam(1,"Data/Image/ex3.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g1.spr 49802");
	pUpdate->setParam(1,"Data/Image/g1.spr");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0014()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 14


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-01.map 541650");
	pUpdate->setParam(1,"Data/Map/Exit-01.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Skill.inf 4626");
	pUpdate->setParam(1,"Data/Info/Skill.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"gb1.spr 47226");
	pUpdate->setParam(1,"Data/Image/gb1.spr");
	updateManager.push_back( pUpdate );


	// [Error] Not Exist Info. --> NewTile.spk
	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-02.map 699632");
	pUpdate->setParam(1,"Data/Map/Exit-02.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemBroken.afpk 982");
	pUpdate->setParam(1,"Data/Image/ItemBroken.afpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-B1.map 36636");
	pUpdate->setParam(1,"Data/Map/guild-B1.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewImageObject.spk 2133494");
	pUpdate->setParam(1,"Data/Image/ImageObject.spk");
	pUpdate->setParam(2,"NewImageObject.spki 314");
	pUpdate->setParam(3,"Data/Image/ImageObject.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewImageObject.sspk 5946");
	pUpdate->setParam(1,"Data/Image/ImageObject.sspk");
	pUpdate->setParam(2,"NewImageObject.sspki 314");
	pUpdate->setParam(3,"Data/Image/ImageObject.sspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bg00.spr 49234");
	pUpdate->setParam(1,"Data/Image/bg00.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemOption.inf 2684");
	pUpdate->setParam(1,"Data/Info/ItemOption.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemBroken.spk 35130");
	pUpdate->setParam(1,"Data/Image/ItemBroken.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-04.map 602400");
	pUpdate->setParam(1,"Data/Map/Exit-04.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-2.map 41110");
	pUpdate->setParam(1,"Data/Map/guild-2.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-3.map 44778");
	pUpdate->setParam(1,"Data/Map/guild-3.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewEffect.aspk 991390");
	pUpdate->setParam(1,"Data/Image/Effect.aspk");
	pUpdate->setParam(2,"NewEffect.aspki 250");
	pUpdate->setParam(3,"Data/Image/Effect.aspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-1.map 43222");
	pUpdate->setParam(1,"Data/Map/guild-1.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-03.map 568822");
	pUpdate->setParam(1,"Data/Map/Exit-03.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemDrop.afpk 5550");
	pUpdate->setParam(1,"Data/Image/ItemDrop.afpk");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0015()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 15


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ex2.spr 66564");
	pUpdate->setParam(1,"Data/Image/ex2.spr");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0016()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 16


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bamp00.map 238828");
	pUpdate->setParam(1,"Data/Map/bamp00.map");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0017()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 17


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Action.inf 23615");
	pUpdate->setParam(1,"Data/Info/Action.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DS_DRAINED.wav 147218");
	pUpdate->setParam(1,"Data/Sound/DS_DRAINED.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CG_ATTACK.wav 44216");
	pUpdate->setParam(1,"Data/Sound/CG_ATTACK.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"RE_DIE.wav 153104");
	pUpdate->setParam(1,"Data/Sound/RE_DIE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DS_DAMAGE.wav 32444");
	pUpdate->setParam(1,"Data/Sound/DS_DAMAGE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"EffectSpriteType.inf 331");
	pUpdate->setParam(1,"Data/Info/EffectSpriteType.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"WORLD_WATER_DROP.wav 261992");
	pUpdate->setParam(1,"Data/Sound/WORLD_WATER_DROP.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DS_ATTACK.wav 88360");
	pUpdate->setParam(1,"Data/Sound/DS_ATTACK.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New17ImageObject.sspk 898");
	pUpdate->setParam(1,"Data/Image/ImageObject.sspk");
	pUpdate->setParam(2,"New17ImageObject.sspki 210");
	pUpdate->setParam(3,"Data/Image/ImageObject.sspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Etc.spk 19918");
	pUpdate->setParam(1,"Data/Image/Etc.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AL_DRAIN.wav 94246");
	pUpdate->setParam(1,"Data/Sound/AL_DRAIN.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ExchangeVampire.spk 445206");
	pUpdate->setParam(1,"Data/UI/SPK/ExchangeVampire.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ex1.spr 66564");
	pUpdate->setParam(1,"Data/Image/ex1.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UserOption.inf 48");
	pUpdate->setParam(1,"Data/Info/UserOption.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New17ImageObject.spk 867616");
	pUpdate->setParam(1,"Data/Image/ImageObject.spk");
	pUpdate->setParam(2,"New17ImageObject.spki 210");
	pUpdate->setParam(3,"Data/Image/ImageObject.spki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Effect.aspk 20776582");
	pUpdate->setParam(1,"Data/Image/Effect.aspk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AL_MAGIC.wav 88360");
	pUpdate->setParam(1,"Data/Sound/AL_MAGIC.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Help.inf 1339");
	pUpdate->setParam(1,"Data/Info/Help.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ShopTemplate.inf 829");
	pUpdate->setParam(1,"Data/Info/ShopTemplate.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"RE_DRAIN.wav 235506");
	pUpdate->setParam(1,"Data/Sound/RE_DRAIN.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Effect.efpk 62301");
	pUpdate->setParam(1,"Data/Image/Effect.efpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exchange.spk 408350");
	pUpdate->setParam(1,"Data/UI/SPK/Exchange.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ClientConfig.inf 263");
	pUpdate->setParam(1,"Data/Info/ClientConfig.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Effect.aspki 3626");
	pUpdate->setParam(1,"Data/Image/Effect.aspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New17Creature.sspk 1431374");
	pUpdate->setParam(1,"Data/Image/Creature.sspk");
	pUpdate->setParam(2,"New17Creature.sspki 10358");
	pUpdate->setParam(3,"Data/Image/Creature.sspki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayers.map 679068");
	pUpdate->setParam(1,"Data/Map/slayers.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AL_DRAINED.wav 94246");
	pUpdate->setParam(1,"Data/Sound/AL_DRAINED.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AL_ATTACK.wav 64816");
	pUpdate->setParam(1,"Data/Sound/AL_ATTACK.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"RE_MAGIC.wav 103074");
	pUpdate->setParam(1,"Data/Sound/RE_MAGIC.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g001.map 40710");
	pUpdate->setParam(1,"Data/Map/g001.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Sound.inf 6658");
	pUpdate->setParam(1,"Data/Info/Sound.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CG_DAMAGE.wav 35386");
	pUpdate->setParam(1,"Data/Sound/CG_DAMAGE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Config.exe 36864");
	pUpdate->setParam(1,"Config.exe");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"GO_DRAIN.wav 120732");
	pUpdate->setParam(1,"Data/Sound/GO_DRAIN.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Tutorial_Bookcase.spk 738410");
	pUpdate->setParam(1,"Data/UI/SPK/Tutorial_Bookcase.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"RE_ATTACK.wav 55986");
	pUpdate->setParam(1,"Data/Sound/RE_ATTACK.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DS_DIE.wav 129560");
	pUpdate->setParam(1,"Data/Sound/DS_DIE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayer_etc.spk 45946");
	pUpdate->setParam(1,"Data/UI/SPK/slayer_etc.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"VampireGameOption.spk 6046");
	pUpdate->setParam(1,"Data/UI/SPK/VampireGameOption.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"RE_DRAINED.wav 106016");
	pUpdate->setParam(1,"Data/Sound/RE_DRAINED.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ex4.spr 66564");
	pUpdate->setParam(1,"Data/Image/ex4.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g003.map 42278");
	pUpdate->setParam(1,"Data/Map/g003.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DEUtil.dll 40960");
	pUpdate->setParam(1,"DEUtil.dll");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DS_DRAIN.wav 88360");
	pUpdate->setParam(1,"Data/Sound/DS_DRAIN.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"RE_DAMAGE.wav 35386");
	pUpdate->setParam(1,"Data/Sound/RE_DAMAGE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.cfpk 238824");
	pUpdate->setParam(1,"Data/UI/Frame/Creature.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"GO_DIE.wav 176648");
	pUpdate->setParam(1,"Data/Sound/GO_DIE.wav");
	updateManager.push_back( pUpdate );


	// [Error] Not Exist Info. --> New17Tile.spk
	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"GO_DRAINED.wav 120732");
	pUpdate->setParam(1,"Data/Sound/GO_DRAINED.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g03.map 42922");
	pUpdate->setParam(1,"Data/Map/g03.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CreatureSprite.inf 788");
	pUpdate->setParam(1,"Data/Info/CreatureSprite.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"GO_MOVE.wav 70702");
	pUpdate->setParam(1,"Data/Sound/GO_MOVE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CG_DRAINED.wav 147218");
	pUpdate->setParam(1,"Data/Sound/CG_DRAINED.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"SlayerGameOption.spk 6046");
	pUpdate->setParam(1,"Data/UI/SPK/SlayerGameOption.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AL_DAMAGE.wav 29500");
	pUpdate->setParam(1,"Data/Sound/AL_DAMAGE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"New17Creature.ispk 14453772");
	pUpdate->setParam(1,"Data/UI/SPK/Creature.ispk");
	pUpdate->setParam(2,"New17Creature.ispki 10354");
	pUpdate->setParam(3,"Data/Image/Creature.ispki");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"GO_DAMAGE.wav 29500");
	pUpdate->setParam(1,"Data/Sound/GO_DAMAGE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"GO_ATTACK.wav 82474");
	pUpdate->setParam(1,"Data/Sound/GO_ATTACK.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g002.map 38330");
	pUpdate->setParam(1,"Data/Map/g002.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"NPC.inf 432");
	pUpdate->setParam(1,"Data/Info/NPC.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"AL_DIE.wav 94246");
	pUpdate->setParam(1,"Data/Sound/AL_DIE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CreatureShadow.cfpk 238392");
	pUpdate->setParam(1,"Data/Image/CreatureShadow.cfpk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CG_DIE.wav 103074");
	pUpdate->setParam(1,"Data/Sound/CG_DIE.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g02.map 42306");
	pUpdate->setParam(1,"Data/Map/g02.map");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DS_MAGIC.wav 61872");
	pUpdate->setParam(1,"Data/Sound/DS_MAGIC.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.inf 20497");
	pUpdate->setParam(1,"Data/Info/Item.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"CG_DRAIN.wav 103074");
	pUpdate->setParam(1,"Data/Sound/CG_DRAIN.wav");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Tutorial_Book.spk 563730");
	pUpdate->setParam(1,"Data/UI/SPK/Tutorial_Book.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"EffectStatus.inf 180");
	pUpdate->setParam(1,"Data/Info/EffectStatus.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"slayers.spr 43322");
	pUpdate->setParam(1,"Data/Image/slayers.spr");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"g01.map 40498");
	pUpdate->setParam(1,"Data/Map/g01.map");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0018()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 18


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Zone.inf 1374");
	pUpdate->setParam(1,"Data/Info/Zone.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Creature.inf 12254");
	pUpdate->setParam(1,"Data/Info/Creature.inf");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

void version0019()
{
	UpdateManager updateManager;
	Update* pUpdate:
	int version = 19


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Progress.spk 3878880");
	pUpdate->setParam(1,"Data/UI/SPK/Progress.spk");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"String.inf 2252");
	pUpdate->setParam(1,"Data/Info/String.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Chat.inf 10659");
	pUpdate->setParam(1,"Data/Info/Chat.inf");
	updateManager.push_back( pUpdate );


	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DarkEden.exe 3874816");
	pUpdate->setParam(1,"DarkEden.exe");
	updateManager.push_back( pUpdate );


	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR, version);
	remove(filename);
	updateManager.save(filename);
}

int main()
{
	__BEGIN_DEBUG


	version0002();
	version0003();
	version0004();
	version0005();
	version0006();
	version0007();
	version0008();
	version0009();
	version0010();
	version0011();
	version0012();
	version0013();
	version0014();
	version0015();
	version0016();
	version0017();
	version0018();
	version0019();


	__END_DEBUG
}
