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
