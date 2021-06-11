//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : 절대 서버용 메인 함수
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Types.h"
#include "Exception.h"
#include "TheOneServer.h"
#include "Properties.h"
#include "StringStream.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#include <vector>

void memoryError()
{
	cerr << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
	exit(0);
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main ( int argc , char * argv[] )
{
	// 메모리 없다.. 함수를 설정한다.
	set_new_handler(memoryError);
	cerr << "Processing Arguments..." << endl;

	if ( argc < 3 ) {
		cout << "Usage : theoneserver -f 환경파일 [-p port]" << endl;
		exit(1);
	}

	// command-line parameter를 string 으로 변환한다. ^^;
	vector<string> Argv;
	Argv.reserve(argc);

	for ( int i = 0 ; i < argc ; i ++ )
		Argv.push_back( argv[i] );

	// 환경 파일을 읽어들인다.
	// 단 실행 파일은 $VSHOME/bin에, 환경 파일은 $VSHOME/conf 에 존재해야 한다.
	// command line 에서 환경 파일을 지정할 수 있도록 한다.

	try {

		if ( Argv[1] != "-f" ) {
			throw Error("Usage : loginserver -f 환경파일 [-p port]"); 
		}

		cerr << "Making Properties.." << endl;

		// 첫번째 파라미터가 -f 일 경우, 두번째 파라미터는 환경파일의 위치가 된다.
		g_pConfig = new Properties();
		g_pConfig->load(Argv[2]);
		
		cerr << "Making Properties Complete!" << endl;
		
		cout << g_pConfig->toString() << endl;

	} catch ( Error & e ) {
		cerr << e.toString() << endl;
		exit(1);
	}

	try {

		if ( argc>3 )
		{
			if (argc<5 || Argv[3] != "-p" )
				throw Error("Usage : theoneserver -f 환경파일 [-p port]");

			g_pConfig->setProperty("TheOneServerUDPPort", Argv[4]);
			cout << "TheOneServerUDPPort : " << g_pConfig->getProperty("TheOneServerUDPPort") << endl;;
		}

	} catch ( Error & e ) {
		cerr << e.toString() << endl;
		exit(1);
	}

	cerr << "Processing Arguments Complete!" << endl;

	//
	// 절대 서버 객체를 생성하고 초기화한 후 활성화시킨다.
	//
	try 
	{
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// 절대 서버 객체를 생성한다.
		g_pTheOneServer = new TheOneServer();

		// 절대 서버 객체를 초기화한다.
		g_pTheOneServer->init();

		// 절대 서버 객체를 활성화시킨다.
		g_pTheOneServer->start();
	} 
	catch ( Throwable & e ) 
	{
		cerr << e.toString() << endl;

		// 절대 서버를 중단시킨다.
		// 이 내부에서 하위 매니저 역시 중단되어야 한다.
		g_pTheOneServer->stop();
	}
}
