//--------------------------------------------------------------------------------
//
// Filename    : CUBeginUpdateHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "CUBeginUpdate.h"

#ifdef __UPDATE_SERVER__
	#include <sys/dir.h>
//	#include <stdio.h>
//	#include <fcntl.h>
//	#include <unistd.h>
	#include "UpdateServerPlayer.h"
	#include "Properties.h"
	#include "Upackets/UCUpdateList.h"
	#include "UpdateServerPlayer.h"
	#include "UpdateServer.h"

	// 업데이트 디렉토리 스캔 관련
	#include <stdio.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <sys/stat.h>

#endif

/*
//--------------------------------------------------------------------------------
//
// 클라이언트의 버전 바로 윗버전부터 최신 버전까지의 리스트를 생성한 후,
// 각 버전의 업데이트 명령을 merge 해서 최적화된 업데이트 명령의 리스트를
// 생성해서 UCUpdateList 패킷에 담아 클라이언트로 전송한다.
//
//--------------------------------------------------------------------------------
void CUBeginUpdateHandler::execute ( CUBeginUpdate * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	try {

		//cout << "Client Version : " << pPacket->getVersion() << endl;

		//--------------------------------------------------------------------------------
		// 패치 디렉토리의 하위 디렉토리들의 리스트를 생성한다.
		// 이때 클라이언트 버전보다 같거나 낮은 버전은 무시해도 된다.
		//--------------------------------------------------------------------------------

		// 디렉토리 이름의 리스트
		list<string> directories;

		string patchDir = g_pConfig->getProperty("HomeDir") + separator + g_pConfig->getProperty("PatchDir");

		//cout << "patchDir = " << patchDir << endl;

		// 패치 디렉토리를 오픈한다.
		DIR * pDIR = opendir( patchDir.c_str() );

		// 패치 디렉토리가 없으면 말짱 황!
		Assert( pDIR != NULL );

		// 패치 디렉토리의 하위 디렉토리(버전 디렉토리)들을 읽어들인다.
		bool sameVersionFound = false;
		struct dirent * versionDir;
		while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

			// 빈 슬랏(inode==0)은 무시한다...
			if ( versionDir->d_ino != 0 ) {

				//	
				// 버전 디렉토리는 v + 0으로 채워진 5자리 정수 문자열로 되어 있다.
				//  ex> v00001/ v00002/ v00003/ ...
				//
				string dir = versionDir->d_name;

				// v 로 시작하지 않는 하위 디렉토리로는 "." 과 ".." 이 있다. -_-;
				if ( dir[0] == 'v' ) {

					// 버전을 비교하기 위해서는
					// 숫자 부분을 스트링으로 변환해서 다시 정수로 변환한다.
					Version_t version = atoi( dir.substr( 1 , 5 ).c_str() );

					if ( version == pPacket->getVersion() )
						sameVersionFound = true;

					if ( version > pPacket->getVersion() )
						directories.push_back( dir );

				} else
					//cout << endl;
			}
			
		}

		closedir( pDIR );

		if ( !sameVersionFound ) {
			throw InvalidProtocolException("invalid client version");
		}

		// 테스트로 출력해본다.
		for ( list<string>::iterator itr = directories.begin() ; itr != directories.end() ; itr ++ )
			//cout << "Newer Version : " << *itr << endl;


		//--------------------------------------------------------------------------------
		// 최신 버전 디렉토리들을 검색하면서, 각 디렉토리의 index.dat 파일들을 로딩해서
		// UpdateManager 객체를 생성한다.
		//--------------------------------------------------------------------------------
	
		UCUpdateList ucUpdateList;
		UpdateManager * pUpdateManager = ucUpdateList.getUpdateManager();

//		int i = 0;

		for ( list<string>::iterator itr = directories.begin() ; itr != directories.end() ; itr ++ ) {
			
			// ex> "/home/vs/reiot/data/patch" + "/" + "v00010" + "/" + "index.dat"
			string filename = patchDir + separator + *itr + separator + "index.dat";

			//cout << "try to open " << filename << endl;

			pUpdateManager->load( filename );

//			if( i == 12 ) break;
//			i++;
		}

		//cout << pUpdateManager->toString() << endl;

		pUpdateServerPlayer->sendPacket( &ucUpdateList );

		pUpdateServerPlayer->setPlayerStatus( USPS_AFTER_SENDING_UC_UPDATE_LIST );

	} catch ( FileNotExistException & fnee ) {
		throw InvalidProtocolException( fnee.toString() );
	}

#endif
		
	__END_CATCH
}
*/

void CUBeginUpdateHandler::scan_Dir( const string Directory, CUBeginUpdate* pPacket, UpdateManager * pUpdateManager, bool bHttpPatch, bool bUpdaterPatch )
	throw( ProtocolException, Error )
{

#ifdef __UPDATE_SERVER__

	DIR * pDIR = opendir( Directory.c_str() );
	struct dirent * versionDir;
	//cout << "Open Dir : " << Directory << endl;

	while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

		string vName = versionDir->d_name;

		if ( versionDir->d_ino != 0  && vName[0] != '.' ) {

			//cout << "versionDir : " << versionDir->d_name<< endl;

			string DirectoryName = Directory + "/";
			string SubDirectory = DirectoryName + versionDir->d_name;

			struct stat List;
			stat( SubDirectory.c_str(), &List );
			//cout << versionDir->d_name << " " << List.st_size << endl;

			//cout << "Path : " << SubDirectory << " Path Size : " << List.st_size << endl;

			if( S_ISDIR( List.st_mode ) ) {

				// 버전을 비교하기 위해서는
				// 숫자 부분을 스트링으로 변환해서 다시 정수로 변환한다.
				Version_t version = atoi( vName.substr( 1 , 5 ).c_str() );

				Version_t ClientVersion = pPacket->getVersion() - 3000;
				if( bUpdaterPatch ) 
				{
					ClientVersion = (ClientVersion<=46? 1 : 2);
				}

				if ( version == ClientVersion ) {

					//cout << versionDir->d_name << " is Directory " << endl;


					string SubDirectory = DirectoryName + versionDir->d_name;

					//cout << "SubDirectory : " << SubDirectory << endl;
					scan_Dir( SubDirectory, pPacket, pUpdateManager, bHttpPatch, bUpdaterPatch );
//					//cout << get_current_dir_name() << endl;
				}

			} else {

				//string tempversion = g_pConfig->getProperty("PatchVersion");

				//Version_t PatchVersion = atoi( tempversion.c_str() );

				//cout << "It is correct file" << endl;

				StringStream msg1;
				StringStream msg2;

				msg1 << versionDir->d_name << " " << List.st_size;

				if( vName == "AppendPatch.inf" ) {
					msg2 << "Data\\Info\\" << versionDir->d_name;
				} else {
					msg2 << versionDir->d_name;
				}


				//cout << " msg1 :" << msg1.toString() << endl;
				//cout << " msg2 :" << msg2.toString() << endl;

				Update * pUpdate = new Update();

				// ClientVersion으로 바꿈. by sigi. 2002.10.16
				Version_t ClientVersion = pPacket->getVersion();
				if (ClientVersion > 3000)
					ClientVersion -= 3000;

				pUpdate->setVersion( ClientVersion );//pPacket->getVersion() );
				pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
				pUpdate->setParam(0,msg1.toString());
				pUpdate->setParam(1,msg2.toString());

//				pUpdate->setVersion( PatchVersion );
//				if( pPacket->getVersion() > 1000 ) {
				if( bHttpPatch ) {

					srand(time(NULL));
					int randomv = rand();
					// URL 선정 작업....... 및 어쩌구 저쩌구
					int Random = randomv % g_pConfig->getPropertyInt( "MAXURL" );
					StringStream ConfigParam;
					ConfigParam << "URL" << Random;
					StringStream URL;
					URL << g_pConfig->getProperty( ConfigParam.toString() );
					pUpdate->setParam(5, URL.toString() );

				}

				pUpdateManager->push_back( pUpdate );

			}
		}
	}
	closedir( pDIR );

#endif

}

//--------------------------------------------------------------------------------
//
// 클라이언트의 버전 바로 윗버전부터 최신 버전까지의 리스트를 생성한 후,
// 각 버전의 업데이트 명령을 merge 해서 최적화된 업데이트 명령의 리스트를
// 생성해서 UCUpdateList 패킷에 담아 클라이언트로 전송한다.
//
//--------------------------------------------------------------------------------
void CUBeginUpdateHandler::execute ( CUBeginUpdate * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	bool bHttpPatch = true;
	bool bUpdaterPatch = false;


	// 3000번 이상 버전은 2002.7.12 새버전부터이다.
	// 이전 버전은 더 이상 유지하지 않을 예정이므로
	// 3000번 이하는 짜른다.
	if (pPacket->getVersion() < 3000)
	{
		throw DisconnectException("under3000");	
	}

	/*
	if( pPacket->getVersion() < 2000 ) {
		if( pPacket->getVersion () > 1000 ) {
			bHttpPatch = true;
			pPacket->setVersion( pPacket->getVersion() - 1000 );
		}

		bUpdaterPatch = true;
	} else {

		if (pPacket->getVersion() > 2000)
		{
			bHttpPatch = true;
			pPacket->setVersion( pPacket->getVersion() - 2000 );
		}

	}
	*/

	// 3000번 이상은 무조건 HTTP patch이다.
	if( bHttpPatch )
	{
		((UpdateServerPlayer*)pPlayer)->setExpiredTime( 5 );
	}

	// 이제 여기서 모든 처리를 하게 된다.
	// 길게 갈 것도 없다. 현재 버젼의 디렉토리를 읽어서 그 안에 파일이 있으면 리스트를 만들어 보내고
	// 없으면 무시 하면 된다.
	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	string Directory = g_pConfig->getProperty("HomeDir") + separator + g_pConfig->getProperty("PatchDir");

	UCUpdateList ucUpdateList;
	UpdateManager * pUpdateManager = ucUpdateList.getUpdateManager();

	// Info 관련되서 업데이트를 하나 추가한다.
	if ( pPacket->getVersion() >= g_pConfig->getPropertyInt("InfoVersion") )
	{
		if ( pPacket->getInfoVersion() < g_pConfig->getPropertyInt("InfoMarkVersion") )
		{
			Update* pUpdate = new Update();

			Version_t ClientVersion = pPacket->getVersion();
			if (ClientVersion > 3000)
				ClientVersion -= 3000;

			pUpdate->setVersion( ClientVersion );//pPacket->getVersion() );
			pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);

			string infoFileName = "InfoPatch" + g_pConfig->getProperty("InfoMarkVersion");
			infoFileName = infoFileName + " 1";
			pUpdate->setParam(0, infoFileName);

			int Random = rand() % g_pConfig->getPropertyInt( "MAXINFOURL" );
			StringStream ConfigParam;
			ConfigParam << "INFOURL" << Random;
			StringStream URL;
			URL << g_pConfig->getProperty( ConfigParam.toString() );

			pUpdate->setParam(5, URL.toString() );
			pUpdateManager->push_back( pUpdate );
		}
	}

	scan_Dir( Directory, pPacket, pUpdateManager, bHttpPatch, bUpdaterPatch );

//	WORD version = pPacket->getVersion();
//	WORD keyver = atoi( g_pConfig->getProperty("KeyVersion").c_str() );

	if ( pPacket->getType() == CUBeginUpdate::OLD_UPDATE )
	{
		ucUpdateList.setOld(true);
	}
	else
	{
		ucUpdateList.setOld(false);
		string KeyFileName = Directory + "/../" + g_pConfig->getProperty("KeyFile");
		FILE* pKeyFile = fopen( KeyFileName.c_str(), "r" );
		if ( pKeyFile == NULL )
		{
			filelog("UpdateServerError.log", "키 파일이 없어요.");
			throw Error("키 파일이 없슴당 ㅜ.ㅠ");
		}

		fread( (void*)ucUpdateList.getKeyArray(), szBYTE, 10, pKeyFile );
		fclose( pKeyFile );

		if ( pPacket->getType() == CUBeginUpdate::ONE_VERSION_KEY_BACK ) ucUpdateList.setFront( false );
		else 
		{
			ucUpdateList.setFront( true );

			Update* pUpdate = new Update();

			Version_t ClientVersion = pPacket->getVersion();
			if (ClientVersion > 3000)
				ClientVersion -= 3000;

			pUpdate->setVersion( ClientVersion );//pPacket->getVersion() );
			pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);

			WORD lastGuildMarkVersion = g_pConfig->getPropertyInt("LastGuildMarkVersion");
			string guildFileName = "Guild";

			if ( lastGuildMarkVersion > pPacket->getGuildVersion() )
				guildFileName = guildFileName + itos( lastGuildMarkVersion ) + ".txt" + " 1"; 
			else 
				guildFileName = guildFileName + itos( pPacket->getGuildVersion() ) + ".txt" + " 1";

			pUpdate->setParam(0, guildFileName);
			pUpdate->setParam(5, g_pConfig->getProperty("GUILDURL"));

			if ( pPacket->getGuildVersion() > 0 && pPacket->getGuildVersion() < g_pConfig->getPropertyInt("GuildMarkVersion") && ClientVersion > g_pConfig->getPropertyInt("StartGuildVersion") )
				pUpdateManager->push_back( pUpdate );

		}
	}

	//cout << pUpdateManager->toString() << endl;
	pUpdateServerPlayer->sendPacket( &ucUpdateList );
	pUpdateServerPlayer->setPlayerStatus( USPS_AFTER_SENDING_UC_UPDATE_LIST );

#endif
		
	__END_CATCH
}


