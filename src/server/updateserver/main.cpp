//--------------------------------------------------------------------------------
//
// Filename    : main.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Types.h"
#include "Exception.h"
#include "UpdateServer.h"
#include "Properties.h"

// 업데이트 디렉토리 스캔 관련
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/resource.h>

#include <iostream.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include "UpdateManager.h"
#include "Update.h"
#include "StringStream.h"

//	scandir
//	readdir
//	seekdir
//	getcwd
//
//	// 문자열 비교
//	strcasecmp( "LISt" , "LIST" ) == 0

class SourceInfo {

public :
	string getName() { return m_Name; }
	void setName( string Name ) { m_Name = Name; }

	string getDirectory() { return m_Directory; }
	void setDirectory( string Directory ) { m_Directory = Directory; }

private :

	string m_Name;
	string m_Directory;

};

class VersionInfo {

public :
	string getName() { return m_Name; }
	void setName( string Name ) { m_Name = Name; }

	string getDirectory() { return m_Directory; }
	void setDirectory( string Directory ) { m_Directory = Directory; }

	int getVersion() { return m_Version; }
	void setVersion( int Version ) { m_Version = Version; }

	int getSize() { return m_Size; }
	void setSize( int Size ) { m_Size = Size; }

private :

	string m_Name;
	string m_Directory;
	int m_Size;
	int m_Version;
};

list<SourceInfo *> SourceInfoList;
list<VersionInfo*> VersionInfoList;


class isSameName {

public :

	// constructor
	isSameName ( string Name ) : m_Name(Name) {}


	bool operator () ( VersionInfo * pVersionInfo ) throw ()
	{
		// 이름이 같다.
		if( strcasecmp( m_Name.c_str(), pVersionInfo->getName().c_str() ) == 0 ) {
			return true;
		} else {
			return false;
		}
	}

private :

	// Name identifier
	string m_Name;

};

class isSource {

public :

	// constructor
	isSource ( string Name ) : m_Name(Name) {}


	bool operator () ( SourceInfo * pSourceInfo ) throw ()
	{
		// 이름이 같다.
		if( strcasecmp( m_Name.c_str(), pSourceInfo->getName().c_str() ) == 0 ) {
			return true;
		} else {
			return false;
		}
	}

private :

	// Name identifier
	string m_Name;

};


/*
void main(void) {

	struct dirent * Testdir;
	int count = 0;

	readdir( 0, Testdir, count );
	scandir

	//cout << " DirName : " << TestDir->d_Name << endl;

}
*/
/*
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
*/


#include <dirent.h>

int myselect( const struct dirent *entry ) {

	const char * filename = entry->d_name;
	if( *filename == '.' ) {
		return 0;
	} else {
		return 1;
	}

}

void scan_Source( const string & Directory ) {

//	struct dirent **namelist;

	DIR * pDIR = opendir( Directory.c_str() );
	struct dirent * versionDir;
//	//cout << "Open Dir : " << Directory << endl;

	while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

		string vName = versionDir->d_name;

		if ( versionDir->d_ino != 0  && vName[0] != '.' ) {

//			//cout << "versionDir : " << versionDir->d_name<< endl;

			string DirectoryName = Directory + "/";
			string SubDirectory = DirectoryName + versionDir->d_name;

			struct stat List;
			stat( SubDirectory.c_str(), &List );
//			//cout << versionDir->d_name << " " << List.st_size << endl;

			replace ( DirectoryName.begin(), DirectoryName.end(), '/', '\\' );
//			//cout << "Path : " << array << " Path Size : " << size << endl;

			if( S_ISDIR( List.st_mode ) ) {

//				//cout << versionDir->d_name << " is Directory " << endl;


//			string SubDirectory = DirectoryName + "/" + namelist[n]->d_name;

//				//cout << "SubDirectory : " << SubDirectory << endl;
				scan_Source( SubDirectory );
//			//cout << get_current_dir_name() << endl;
			} else {
				SourceInfo * pSourceInfo = new SourceInfo();
				pSourceInfo->setName( versionDir->d_name );
				pSourceInfo->setDirectory( DirectoryName.substr( g_pConfig->getProperty("SourceDirectory").size() + 1, DirectoryName.size()-1 ) );
				SourceInfoList.push_back( pSourceInfo );

				/*
				// 일단 같은 이름이 있는지 찾는다.
				list<SourceInfo*>::iterator itr = find_if( SourceInfoList.begin(), SourceInfoList.end(), isSameName(pSourceInfo->getName()) );
				
				// 똑같은 이름이 있다면 최신 버젼으로 넣어 줘야쥐.
				if ( itr != SourceInfoList.end() ) {

					//cout << "원본 파일에서 같은 이름의 파일이 발견 되었다!" << endl;

					//cout << "원래 있던 파일의 디렉은 : " << (*itr)->getDirectory() << ", 파일 이름은 : " << (*itr)->getName() << endl;
					//cout << "최신 파일의 버젼은 : " << pSourceInfo->getDirectory() << ", 파일 이름은 : " << pSourceInfo->getName() << endl;

				// 같은 파일이 없다.
				} else {
					SourceInfoList.push_back( pSourceInfo );
				}
				*/

			}

		}

	}
	closedir( pDIR );

}

void scan_Version( const string & Directory, int version ) {

//	struct dirent **namelist;

	DIR * pDIR = opendir( Directory.c_str() );
	struct dirent * versionDir;
//	//cout << "Open Dir : " << Directory << endl;

	while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

		string vName = versionDir->d_name;

		if( vName == "index.dat" ) {
			string removeName = Directory + "/" + "index.dat";
			//cout << "Remove index.dat Directory : " << removeName << endl;
			remove( removeName.c_str() );
		}

		if ( versionDir->d_ino != 0  && vName[0] != '.' && vName != "index.dat" ) {

//			//cout << "versionDir : " << versionDir->d_name<< endl;
			string DirectoryName = Directory;

			string SubDirectory = DirectoryName + "/" + versionDir->d_name;

			/*
			replace ( DirectoryName.begin(), DirectoryName.end(), '/', '\\' );
//			//cout << "ChangeName : " << DirectoryName << endl;
			*/

			struct stat List;
			stat( SubDirectory.c_str(), &List );
//			//cout << versionDir->d_name << " " << List.st_size << endl;

//			//cout << "Path : " << array << " Path Size : " << size << endl;

			if( S_ISDIR( List.st_mode ) ) {

				int version = atoi( vName.substr( 1 , 5 ).c_str() );

//				//cout << versionDir->d_name << " is Directory " << endl;


//			string SubDirectory = DirectoryName + "/" + namelist[n]->d_name;

//				//cout << "SubDirectory : " << SubDirectory << endl;
				scan_Version( SubDirectory, version );
//			//cout << get_current_dir_name() << endl;
			} else {

				VersionInfo * pVersionInfo = new VersionInfo();
				pVersionInfo->setName( versionDir->d_name );

				list<SourceInfo*>::iterator itr2 = find_if( SourceInfoList.begin(), SourceInfoList.end(), isSource( pVersionInfo->getName() ) );

				pVersionInfo->setDirectory( (*itr2)->getDirectory() );
				pVersionInfo->setSize( List.st_size );

				pVersionInfo->setVersion( version );

				// 일단 같은 이름이 있는지 찾는다.
				list<VersionInfo*>::iterator itr = find_if( VersionInfoList.begin(), VersionInfoList.end(), isSameName( pVersionInfo->getName() ) );
				
				// 똑같은 이름이 있다면 최신 버젼으로 넣어 줘야쥐.
				if ( itr != VersionInfoList.end() ) {
					//cout << "같은 파일이 발견 되었다 최신 버젼으로 고치자" << endl;

					//cout << "원래 있던 파일의 버젼은 : " << (*itr)->getVersion() << ", 파일 이름은 : " << (*itr)->getName() << endl;
					//cout << "최신 파일의 버젼은 : " << pVersionInfo->getVersion() << ", 파일 이름은 : " << pVersionInfo->getName() << endl;

					if( (*itr)->getVersion() < pVersionInfo->getVersion() ) {

						VersionInfo * pTempVersionInfo = (*itr);

						VersionInfoList.erase( itr );
						//cout << "기존의 파일을 삭제한다." << endl;

						delete pTempVersionInfo;

						VersionInfoList.push_back(pVersionInfo);
						//cout << "새 파일을 리스트에 추가한다." << endl;

					} else {

					}

				// 같은 파일이 없다.
				} else {
					VersionInfoList.push_back(pVersionInfo);
				}
			}
		}
	}
	closedir( pDIR );

}

void create_Index() {

	list<VersionInfo*>::const_iterator itr = VersionInfoList.begin();

	int beforeVersion = 0;
	int version = 0;

	// 버젼인포에서 파일을 하나씩 꺼내면서 파일이 들어갈 위치를 뽑아낸다.
	for( ; itr != VersionInfoList.end(); itr++ ) {

		StringStream msg1;
		StringStream msg2;
		StringStream msg3;
		StringStream msg4;

		UpdateManager updatemanager;

		Update * pUpdate = new Update();

		msg1 << (*itr)->getName() << " " << (*itr)->getSize();
		msg2 << (*itr)->getDirectory() << (*itr)->getName();

		version = (*itr)->getVersion();

		char filename[256];
		sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , version);

		ofstream ofile( filename , ios::out | ios::app );

		// 업데이트 갯수를 알아내서 쓴다.
		if( beforeVersion != version ) {

			int Count = 0;
			list<VersionInfo*>::const_iterator itr2 = VersionInfoList.begin();

			for(; itr2 != VersionInfoList.end(); itr2++ ) {
				if( (*itr2)->getVersion() == version ) {
					Count++;
				}
			}
			//cout << "Version : " << version << ", Count: " << Count << endl;

			ofile.write( (const char *)&Count , szWORD );
			beforeVersion = version;
		}

		//cout << "create Index msg1 : " << msg1.toString() << endl;
		//cout << "create Index msg2 : " << msg2.toString() << endl;

		pUpdate = new Update();
		pUpdate->setVersion(version);
		pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
		pUpdate->setParam(0,msg1.toString());
		pUpdate->setParam(1,msg2.toString());

		pUpdate->save(ofile);
		ofile.close();

	}

	// 빈 인덱스를 생성한다.
	for( int i = 0; i <= version ; i++ ) {

		char filename[256];
		sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , i );
		ifstream ifile( filename, ios::in | ios::binary | ios::nocreate );
		// 파일이 없으면 빈 인덱스를 생성한다.
		if ( !ifile ) {
			int Count = 0;

			char filename[256];
			sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , i );
			ofstream ofile( filename , ios::out | ios::app );
			ofile.write( (const char *)&Count , szWORD );

		}
		ifile.close();
	}
}

//--------------------------------------------------------------------------------
//
// main()
//
// UpdateServer의 메인 루프
//
//--------------------------------------------------------------------------------
int main ( int argc , char * argv[] )
{
    if ( argc < 3 ) {
        //cout << "Usage : updateserver -f 환경파일" << endl;
        exit(1);
    }

    // command-line parameter를 string 으로 변환한다. ^^;
    string * Argv;
        
    Argv = new string[argc];
    for ( int i = 0 ; i < argc ; i ++ )
        Argv[i] = argv[i];

    // 환경 파일을 읽어들인다.
    // 단 실행 파일은 $VSHOME/bin에, 환경 파일은 $VSHOME/conf 에 존재해야 한다.�
    // command line 에서 환경 파일을 지정할 수 있도록 한다.

    try {

        if ( Argv[1] != "-f" ) {
            throw Error("Usage : updateserver -f 환경파일");
        }

        // 첫번째 파라미터가 -f 일 경우, 두번째 파라미터는 환경파일의 위치가 된다.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
    
    } catch ( Error & e ) {
        //cout << e.toString() << endl;
    }

	// 소스 디렉토리를 읽는다.
//	scan_Source( g_pConfig->getProperty( "SourceDirectory") );

	/*
	//cout << "============================================================================" << endl;
	for( list<SourceInfo*>::const_iterator itr = SourceInfoList.begin(); itr != SourceInfoList.end(); itr++ ) {
		//cout << "Name : " << (*itr)->getName() << ", Directory : " << (*itr)->getDirectory() << endl;
	}
	//cout << "============================================================================" << endl;
	*/

//	scan_Version( g_pConfig->getProperty("PatchDirectory" ), 0 );

	/*
	// 버젼 디렉토리를 읽는다.
	//cout << "============================================================================" << endl;
	for( list<VersionInfo*>::const_iterator itr = VersionInfoList.begin(); itr != VersionInfoList.end(); itr++ ) {
		//cout << "Version : " << (*itr)->getVersion() << ",Name : " << (*itr)->getName() << ", Directory : " << (*itr)->getDirectory() << endl;
	}
	//cout << "============================================================================" << endl;
	*/

	// index.dat 생성을 위한 작업을 한다.
//	create_Index();


	//
	// 업데이트 서버 객체를 생성하고 초기화한 후 활성화시킨다.
	//
	try {

		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// 업데이트 서버 객체를 생성한다.
		g_pUpdateServer = new UpdateServer();

		// 업데이트 서버 객체를 초기화한다.
		g_pUpdateServer->init();

		// 업데이트 서버 객체를 활성화시킨다.
		g_pUpdateServer->start();

	} catch ( Throwable & e ) {

		// 로그가 이뤄지기 전에 서버가 끝날 경우를 대비해서
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// 표준 출력으로도 출력해준다.
		//cout << e.toString() << endl;

		// 업데이트 서버를 중단시킨다.
		// 이 내부에서 하위 매니저 역시 중단되어야 한다.
		g_pUpdateServer->stop();

	}
}
