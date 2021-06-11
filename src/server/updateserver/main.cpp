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

// ¾÷µ¥ÀÌÆ® µð·ºÅä¸® ½ºÄµ °ü·Ã
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/resource.h>

#include <iostream>
#include <cstdlib>
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
//	// ¹®ÀÚ¿­ ºñ±³
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
		// ÀÌ¸§ÀÌ °°´Ù.
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
		// ÀÌ¸§ÀÌ °°´Ù.
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
		// ÆÐÄ¡ µð·ºÅä¸®¸¦ ¿ÀÇÂÇÑ´Ù.
		DIR * pDIR = opendir( patchDir.c_str() );

		// ÆÐÄ¡ µð·ºÅä¸®°¡ ¾øÀ¸¸é ¸»Â¯ È®!
		Assert( pDIR != NULL );

		// ÆÐÄ¡ µð·ºÅä¸®ÀÇ ÇÏÀ§ µð·ºÅä¸®(¹öÀü µð·ºÅä¸®)µéÀ» ÀÐ¾îµéÀÎ´Ù.
		bool sameVersionFound = false;
		struct dirent * versionDir;
		while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

			// ºó ½½¶ù(inode==0)Àº ¹«½ÃÇÑ´Ù...
			if ( versionDir->d_ino != 0 ) {

				//	
				// ¹öÀü µð·ºÅä¸®´Â v + 0À¸·Î Ã¤¿öÁø 5ÀÚ¸® Á¤¼ö ¹®ÀÚ¿­·Î µÇ¾î ÀÖ´Ù.
				//  ex> v00001/ v00002/ v00003/ ...
				//
				string dir = versionDir->d_name;

				// v ·Î ½ÃÀÛÇÏÁö ¾Ê´Â ÇÏÀ§ µð·ºÅä¸®·Î´Â "." °ú ".." ÀÌ ÀÖ´Ù. -_-;
				if ( dir[0] == 'v' ) {

					// ¹öÀüÀ» ºñ±³ÇÏ±â À§ÇØ¼­´Â
					// ¼ýÀÚ ºÎºÐÀ» ½ºÆ®¸µÀ¸·Î º¯È¯ÇØ¼­ ´Ù½Ã Á¤¼ö·Î º¯È¯ÇÑ´Ù.
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
				// ÀÏ´Ü °°Àº ÀÌ¸§ÀÌ ÀÖ´ÂÁö Ã£´Â´Ù.
				list<SourceInfo*>::iterator itr = find_if( SourceInfoList.begin(), SourceInfoList.end(), isSameName(pSourceInfo->getName()) );
				
				// ¶È°°Àº ÀÌ¸§ÀÌ ÀÖ´Ù¸é ÃÖ½Å ¹öÁ¯À¸·Î ³Ö¾î Áà¾ßÁã.
				if ( itr != SourceInfoList.end() ) {

					//cout << "¿øº» ÆÄÀÏ¿¡¼­ °°Àº ÀÌ¸§ÀÇ ÆÄÀÏÀÌ ¹ß°ß µÇ¾ú´Ù!" << endl;

					//cout << "¿ø·¡ ÀÖ´ø ÆÄÀÏÀÇ µð·ºÀº : " << (*itr)->getDirectory() << ", ÆÄÀÏ ÀÌ¸§Àº : " << (*itr)->getName() << endl;
					//cout << "ÃÖ½Å ÆÄÀÏÀÇ ¹öÁ¯Àº : " << pSourceInfo->getDirectory() << ", ÆÄÀÏ ÀÌ¸§Àº : " << pSourceInfo->getName() << endl;

				// °°Àº ÆÄÀÏÀÌ ¾ø´Ù.
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

				// ÀÏ´Ü °°Àº ÀÌ¸§ÀÌ ÀÖ´ÂÁö Ã£´Â´Ù.
				list<VersionInfo*>::iterator itr = find_if( VersionInfoList.begin(), VersionInfoList.end(), isSameName( pVersionInfo->getName() ) );
				
				// ¶È°°Àº ÀÌ¸§ÀÌ ÀÖ´Ù¸é ÃÖ½Å ¹öÁ¯À¸·Î ³Ö¾î Áà¾ßÁã.
				if ( itr != VersionInfoList.end() ) {
					//cout << "°°Àº ÆÄÀÏÀÌ ¹ß°ß µÇ¾ú´Ù ÃÖ½Å ¹öÁ¯À¸·Î °íÄ¡ÀÚ" << endl;

					//cout << "¿ø·¡ ÀÖ´ø ÆÄÀÏÀÇ ¹öÁ¯Àº : " << (*itr)->getVersion() << ", ÆÄÀÏ ÀÌ¸§Àº : " << (*itr)->getName() << endl;
					//cout << "ÃÖ½Å ÆÄÀÏÀÇ ¹öÁ¯Àº : " << pVersionInfo->getVersion() << ", ÆÄÀÏ ÀÌ¸§Àº : " << pVersionInfo->getName() << endl;

					if( (*itr)->getVersion() < pVersionInfo->getVersion() ) {

						VersionInfo * pTempVersionInfo = (*itr);

						VersionInfoList.erase( itr );
						//cout << "±âÁ¸ÀÇ ÆÄÀÏÀ» »èÁ¦ÇÑ´Ù." << endl;

						delete pTempVersionInfo;

						VersionInfoList.push_back(pVersionInfo);
						//cout << "»õ ÆÄÀÏÀ» ¸®½ºÆ®¿¡ Ãß°¡ÇÑ´Ù." << endl;

					} else {

					}

				// °°Àº ÆÄÀÏÀÌ ¾ø´Ù.
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

	// ¹öÁ¯ÀÎÆ÷¿¡¼­ ÆÄÀÏÀ» ÇÏ³ª¾¿ ®¨³»¸é¼­ ÆÄÀÏÀÌ µé¾î°¥ À§Ä¡¸¦ »Ì¾Æ³½´Ù.
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

		// ¾÷µ¥ÀÌÆ® °¹¼ö¸¦ ¾Ë¾Æ³»¼­ ¾´´Ù.
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

	// ºó ÀÎµ¦½º¸¦ »ý¼ºÇÑ´Ù.
	for( int i = 0; i <= version ; i++ ) {

		char filename[256];
		sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , i );
		ifstream ifile( filename, ios::in | ios::binary );
		// ÆÄÀÏÀÌ ¾øÀ¸¸é ºó ÀÎµ¦½º¸¦ »ý¼ºÇÑ´Ù.
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
// UpdateServerÀÇ ¸ÞÀÎ ·çÇÁ
//
//--------------------------------------------------------------------------------
int main ( int argc , char * argv[] )
{
    if ( argc < 3 ) {
        //cout << "Usage : updateserver -f È¯°æÆÄÀÏ" << endl;
        exit(1);
    }

    // command-line parameter¸¦ string À¸·Î º¯È¯ÇÑ´Ù. ^^;
    string * Argv;
        
    Argv = new string[argc];
    for ( int i = 0 ; i < argc ; i ++ )
        Argv[i] = argv[i];

    // È¯°æ ÆÄÀÏÀ» ÀÐ¾îµéÀÎ´Ù.
    // ´Ü ½ÇÇà ÆÄÀÏÀº $VSHOME/bin¿¡, È¯°æ ÆÄÀÏÀº $VSHOME/conf ¿¡ Á¸ÀçÇØ¾ß ÇÑ´Ù.½
    // command line ¿¡¼­ È¯°æ ÆÄÀÏÀ» ÁöÁ¤ÇÒ ¼ö ÀÖµµ·Ï ÇÑ´Ù.

    try {

        if ( Argv[1] != "-f" ) {
            throw Error("Usage : updateserver -f È¯°æÆÄÀÏ");
        }

        // Ã¹¹øÂ° ÆÄ¶ó¹ÌÅÍ°¡ -f ÀÏ °æ¿ì, µÎ¹øÂ° ÆÄ¶ó¹ÌÅÍ´Â È¯°æÆÄÀÏÀÇ À§Ä¡°¡ µÈ´Ù.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
    
    } catch ( Error & e ) {
        //cout << e.toString() << endl;
    }

	// ¼Ò½º µð·ºÅä¸®¸¦ ÀÐ´Â´Ù.
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
	// ¹öÁ¯ µð·ºÅä¸®¸¦ ÀÐ´Â´Ù.
	//cout << "============================================================================" << endl;
	for( list<VersionInfo*>::const_iterator itr = VersionInfoList.begin(); itr != VersionInfoList.end(); itr++ ) {
		//cout << "Version : " << (*itr)->getVersion() << ",Name : " << (*itr)->getName() << ", Directory : " << (*itr)->getDirectory() << endl;
	}
	//cout << "============================================================================" << endl;
	*/

	// index.dat »ý¼ºÀ» À§ÇÑ ÀÛ¾÷À» ÇÑ´Ù.
//	create_Index();


	//
	// ¾÷µ¥ÀÌÆ® ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑ ÈÄ È°¼ºÈ­½ÃÅ®´Ù.
	//
	try {

		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// ¾÷µ¥ÀÌÆ® ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÑ´Ù.
		g_pUpdateServer = new UpdateServer();

		// ¾÷µ¥ÀÌÆ® ¼­¹ö °´Ã¼¸¦ ÃÊ±âÈ­ÇÑ´Ù.
		g_pUpdateServer->init();

		// ¾÷µ¥ÀÌÆ® ¼­¹ö °´Ã¼¸¦ È°¼ºÈ­½ÃÅ®´Ù.
		g_pUpdateServer->start();

	} catch ( Throwable & e ) {

		// ·Î±×°¡ ÀÌ·ïÁö±â Àü¿¡ ¼­¹ö°¡ ³¡³¯ °æ¿ì¸¦ ´ëºñÇØ¼­
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// Ç¥ÁØ Ãâ·ÂÀ¸·Îµµ Ãâ·ÂÇØÁØ´Ù.
		//cout << e.toString() << endl;

		// ¾÷µ¥ÀÌÆ® ¼­¹ö¸¦ Áß´Ü½ÃÅ®´Ù.
		// ÀÌ ³»ºÎ¿¡¼­ ÇÏÀ§ ¸Å´ÏÀú ¿ª½Ã Áß´ÜµÇ¾î¾ß ÇÑ´Ù.
		g_pUpdateServer->stop();

	}
}
