void version14()
{

	UpdateManager updateManager;
	Update * pUpdate;
	int version = 14;

	//--------------------------------------------------------------------------------
	// save
	//--------------------------------------------------------------------------------
	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Action.inf 23527");
	pUpdate->setParam(1,"Data\\Info\\Action.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Chat.inf 10569");
	pUpdate->setParam(1,"Data\\Info\\Chat.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ClientConfig.inf 177");
	pUpdate->setParam(1,"Data\\Info\\ClientConfig.inf");
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
	pUpdate->setParam(0,"Creature.inf 7084");
	pUpdate->setParam(1,"Data\\Info\\Creature.inf");
	updateManager.push_back( pUpdate );
	//5

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Effect.efpk 57668");
	pUpdate->setParam(1,"Data\\Image\\Effect.efpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"EffectSpriteType.inf 304");
	pUpdate->setParam(1,"Data\\Info\\EffectSpriteType.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"EffectStatus.inf 158");
	pUpdate->setParam(1,"Data\\Info\\EffectStatus.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Etc.spk 14830");
	pUpdate->setParam(1,"Data\\Image\\Etc.spk");
	updateManager.push_back( pUpdate );
	//10

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exchange.spk 380028");
	pUpdate->setParam(1,"Data\\UI\\SPK\\Exchange.spk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ExchangeVampire.spk 437152");
	pUpdate->setParam(1,"Data\\UI\\SPK\\ExchangeVampire.spk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-01.map 541650");
	pUpdate->setParam(1,"Data\\Map\\Exit-01.map");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-02.map 699632");
	pUpdate->setParam(1,"Data\\Map\\Exit-02.map");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-03.map 568822");
	pUpdate->setParam(1,"Data\\Map\\Exit-03.map");
	updateManager.push_back( pUpdate );
	//15

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Exit-04.map 602400");
	pUpdate->setParam(1,"Data\\Map\\Exit-04.map");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemBroken.afpk 982");
	pUpdate->setParam(1,"Data\\Image\\ItemBroken.afpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemBroken.ifpk 140");
	pUpdate->setParam(1,"Data\\Image\\ItemBroken.ifpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemBroken.spk 35130");
	pUpdate->setParam(1,"Data\\Image\\ItemBroken.spk");
	updateManager.push_back( pUpdate );
	//20

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemDrop.afpk 5550");
	pUpdate->setParam(1,"Data\\Image\\ItemDrop.afpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemTile.ifpk 878");
	pUpdate->setParam(1,"Data\\Image\\ItemTile.ifpk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemTile.ispk 90292");
	pUpdate->setParam(1,"Data\\Image\\ItemTile.ispk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"NPC.inf 176");
	pUpdate->setParam(1,"Data\\Info\\NPC.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewEffect.aspk 991390");
	pUpdate->setParam(1,"Data\\Image\\Effect.aspk");
	pUpdate->setParam(2,"NewEffect.aspki 250");
	pUpdate->setParam(3,"Data\\Image\\Effect.aspki");
	updateManager.push_back( pUpdate );
	//26

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewImageObject.spk 2133494");
	pUpdate->setParam(1,"Data\\Image\\ImageObject.spk");
	pUpdate->setParam(2,"NewImageObject.spki 314");
	pUpdate->setParam(3,"Data\\Image\\ImageObject.spki");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewImageObject.sspk 5946");
	pUpdate->setParam(1,"Data\\Image\\ImageObject.sspk");
	pUpdate->setParam(2,"NewImageObject.sspki 314");
	pUpdate->setParam(3,"Data\\Image\\ImageObject.sspki");
	updateManager.push_back( pUpdate );
	//30

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_APPEND_SPRITE_PACK);
	pUpdate->setParam(0,"NewTile.spk 5866180");
	pUpdate->setParam(1,"Data\\Image\\Tile.spk");
	pUpdate->setParam(2,"NewTile.spki 15282");
	pUpdate->setParam(3,"Data\\Image\\Tile.spki");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ShopTemplate.inf 379");
	pUpdate->setParam(1,"Data\\Info\\ShopTemplate.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Skill.inf 4626");
	pUpdate->setParam(1,"Data\\Info\\Skill.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Storage.spk 490982");
	pUpdate->setParam(1,"Data\\UI\\SPK\\Storage.spk");
	updateManager.push_back( pUpdate );
	//35

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"StorageVampire.spk 535284");
	pUpdate->setParam(1,"Data\\UI\\SPK\\StorageVampire.spk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"String.inf 1844");
	pUpdate->setParam(1,"Data\\Info\\String.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"UserOption.inf 32");
	pUpdate->setParam(1,"Data\\Info\\UserOption.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Zone.inf 632");
	pUpdate->setParam(1,"Data\\Info\\Zone.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bg00.spr 49234");
	pUpdate->setParam(1,"Data\\Image\\bg00.spr");
	updateManager.push_back( pUpdate );
	//40

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"gb1.spr 47226");
	pUpdate->setParam(1,"Data\\Image\\gb1.spr");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-1.map 43222");
	pUpdate->setParam(1,"Data\\Map\\guild-1.map");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-2.map 41110");
	pUpdate->setParam(1,"Data\\Map\\guild-2.map");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-3.map 44778");
	pUpdate->setParam(1,"Data\\Map\\guild-3.map");
	updateManager.push_back( pUpdate );
	//45

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"guild-B1.map 36636");
	pUpdate->setParam(1,"Data\\Map\\guild-B1.map");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"itemDrop.ispk 351268");
	pUpdate->setParam(1,"Data\\Image\\itemDrop.ispk");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ItemOption.inf 2684");
	pUpdate->setParam(1,"Data\\Info\\ItemOption.inf");
	updateManager.push_back( pUpdate );
	//48

	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR,version);
	remove(filename);
	updateManager.save(filename);

}

void version15()
{

	UpdateManager updateManager;
	Update * pUpdate;
	int version = 15;

	//--------------------------------------------------------------------------------
	// save
	//--------------------------------------------------------------------------------
	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"ex2.spr 66564");
	pUpdate->setParam(1,"Data\\Image\\ex2.spr");
	updateManager.push_back( pUpdate );

	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR,version);
	remove(filename);
	updateManager.save(filename);

}

void version16()
{

	UpdateManager updateManager;
	Update * pUpdate;
	int version = 16;

	//--------------------------------------------------------------------------------
	// save
	//--------------------------------------------------------------------------------
	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"DarkEden.exe 3796992");
	pUpdate->setParam(1,"DarkEden.exe");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"Item.inf 20496");
	pUpdate->setParam(1,"Data\\Info\\Item.inf");
	updateManager.push_back( pUpdate );

	pUpdate = new Update();
	pUpdate->setVersion(version);
	pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
	pUpdate->setParam(0,"bamp00.map 238828");
	pUpdate->setParam(1,"Data\\Image\\bamp00.map");
	updateManager.push_back( pUpdate );

	char filename[256];
	sprintf(filename,"%s/v%05d/index.dat",PATCH_DIR,version);
	remove(filename);
	updateManager.save(filename);

}
