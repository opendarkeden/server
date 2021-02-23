//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 함수
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Types.h"
#include "Exception.h"
#include "LoginServer.h"
#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void memoryError()
{
	cout << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
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

	if ( argc < 3 ) {
		cout << "Usage : loginserver -f 환경파일 [-p port]" << endl;
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
			throw Error("Usage : loginserver -f 환경파일 [-p port]"); 
		}

		// 첫번째 파라미터가 -f 일 경우, 두번째 파라미터는 환경파일의 위치가 된다.
		g_pConfig = new Properties();
		g_pConfig->load(Argv[2]);
		
		cout << g_pConfig->toString() << endl;

	} catch ( Error & e ) {
		cout << e.toString() << endl;
	}

	try {

		if ( argc>3 )
		{
			if (argc<5 || Argv[3] != "-i" )
				throw Error("Usage : loginserver -f 환경파일 [-i ID]");

			// port를 강제로 설정한다.
			char sLoginServerPort[5], sLoginServerUDPPort[5], sLoginServerID[5];
			sprintf( sLoginServerPort, "%d", g_pConfig->getPropertyInt("LoginServerBasePort") + atoi(argv[4]) );
			sprintf( sLoginServerUDPPort, "%d", g_pConfig->getPropertyInt("LoginServerBaseUDPPort") + atoi(argv[4]) );
			sprintf( sLoginServerID, "%d", g_pConfig->getPropertyInt("LoginServerBaseID") + atoi(argv[4]) );

			g_pConfig->setProperty("LoginServerPort", sLoginServerPort );
			g_pConfig->setProperty("LoginServerUDPPort", sLoginServerUDPPort );
			g_pConfig->setProperty("LoginServerID", sLoginServerID );

			cout << "LoginServerPort : " << sLoginServerPort << endl;
			cout << "LoginServerUDPPort : " << sLoginServerUDPPort << endl;
			cout << "LoginServerID : " << sLoginServerID << endl;
		}

	} catch ( Error & e ) {
		cout << e.toString() << endl;
	}


	// 로그 매니저를 생성하고 초기화한후 활성화시킨다.
	// 로그 매니저는 로그인 서버의 초기화과정에서 발생할 가능성이 있는 에러까지도
	// 검출해내야 하므로 로그인 서버 내부에서 초기화해서는 안된다.
	// 또한 다른 객체를 생성하고 초기화하기전에 로그매니저가 우선적으로 생성,
	// 초기화되어야 한다.
	
	try 
	{
		string LogServerIP   = g_pConfig->getProperty("LogServerIP");
		int    LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
		g_pLogClient = new LogClient(LogServerIP, LogServerPort);
		LogClient::setLogLevel(g_pConfig->getPropertyInt("LogLevel"));

		log(LOG_LOGINSERVER, "", "", "Login Server Start");
	} 
	catch ( Throwable & t ) 
	{
		cout << t.toString() << endl;
	}

	//
	// 로그인 서버 객체를 생성하고 초기화한 후 활성화시킨다.
	//
	try 
	{
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// 로그인 서버 객체를 생성한다.
		g_pLoginServer = new LoginServer();

		// 로그인 서버 객체를 초기화한다.
		g_pLoginServer->init();

		// 로그인 서버 객체를 활성화시킨다.
		g_pLoginServer->start();
	} 
	catch ( Throwable & e ) 
	{
		// 로그가 이뤄지기 전에 서버가 끝날 경우를 대비해서
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// 하위에서 캐치되지 않은 예외 또는 에러가 발생했다는 뜻이다.
		// 이 경우 LEVEL1로 로그해야 한다. (무조건 로그한다는 뜻)
		log(LOG_LOGINSERVER_ERROR, "", "", e.toString());

		// 표준 출력으로도 출력해준다.
		cout << e.toString() << endl;

		// 로그인 서버를 중단시킨다.
		// 이 내부에서 하위 매니저 역시 중단되어야 한다.
		g_pLoginServer->stop();
	}
}
