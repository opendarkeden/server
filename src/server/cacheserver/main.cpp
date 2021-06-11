//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : 장 홍 창   changaya@metrotech.co.kr
// Description : Database Cache Server용 main function
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Types.h"
#include "Exception.h"
#include "GameServer.h"
#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <new>

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
int main (int argc , char* argv[])
{
	cout << ">>> STARTING CACHE SERVER..." << endl;

	// 메모리 없다..함수를 설정한다.
	set_new_handler(memoryError);
	cout << ">>> MEMORY HANDLER INSTALL SUCCESS..." << endl;

	// What?
	int* pPointer = NULL;
	pPointer = new int[500000000];
	delete pPointer;

	// 적절한 위치를 찾아보자.
	srand(time(0));
	cout << ">>> RANDOMIZATION INITIALIZATION SUCCESS..." << endl;

    if (argc < 3) 
	{
        cout << "Usage : cacheserver -f 환경파일" << endl;
        exit(1);
    }

    // command-line parameter를 string 으로 변환한다. ^^;
    string* Argv;
        
    Argv = new string[argc];
    for (int i = 0 ; i < argc ; i ++)
        Argv[i] = argv[i];

	cout << ">>> COMMAND-LINE PARAMETER READING SUCCESS..." << endl;

    // 환경 파일을 읽어들인다.
    // 단 실행 파일은 $VSHOME/bin에, 환경 파일은 $VSHOME/conf 에 존재해야 한다.�
    // command line 에서 환경 파일을 지정할 수 있도록 한다.

    try 
	{
        if (Argv[1] != "-f") 
		{
            throw Error("Usage : cacheserver -f 환경파일");
        }

        // 첫번째 파라미터가 -f 일 경우, 두번째 파라미터는 환경파일의 위치가 된다.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
    } 
	catch (Error & e) 
	{
        //cout << e.toString() << endl;
    }

	// 로그 매니저를 생성하고 초기화한후 활성화시킨다.
	// 로그 매니저는 게임 서버의 초기화과정에서 발생할 가능성이 있는 에러까지도
	// 검출해내야 하므로 게임 서버 내부에서 초기화해서는 안된다.
	// 또한 다른 객체를 생성하고 초기화하기전에 로그매니저가 우선적으로 생성,
	// 초기화되어야 한다.
	try 
	{
		string LogServerIP   = g_pConfig->getProperty("LogServerIP");
		int    LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
		int    LogLevel      = g_pConfig->getPropertyInt("LogLevel");
		g_pLogClient = new LogClient(LogServerIP, LogServerPort);
		LogClient::setLogLevel(LogLevel);

		log(LOG_GAMESERVER, "", "", "Cache Server Start");

		//cout << "LogServerIP = " << LogServerIP << endl;
		//cout << "LogServerPort = " << LogServerPort << endl;
		//cout << "LogLevel = " << LogClient::getLogLevel() << endl;
	} 
	catch (Error & e) 
	{
		//cout << e.toString() << endl;
	}

	cout << ">>> LOGCLIENT INITIALZATION SUCCESS..." << endl;

	//
	// 게임 서버 객체를 생성하고 초기화한 후 활성화시킨다.
	//
	try 
	{
		// what?
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// 게임 서버 객체를 생성한다.
		g_pCacheServer = new CacheServer();

		cout << ">>> CACHE SERVER INSTANCE CREATED..." << endl;

		// 게임 서버 객체를 초기화한다.
		g_pCacheServer->init();

		cout << ">>> CACHE SERVER INITIALIZATION SUCCESS..." << endl;

		// 게임 서버 객체를 활성화시킨다.
		g_pCacheServer->start();
	} 
	catch (Throwable & e) 
	{
		// 로그가 이뤄지기 전에 서버가 끝날 경우를 대비해서
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// 표준 출력으로도 출력해준다.
		cout << e.toString() << endl;

		// 게임 서버를 중단시킨다.
		// 이 내부에서 하위 매니저 역시 중단되어야 한다.
		g_pCacheServer->stop();
	} 
	catch (...) 
	{
		cout << "unknown exception..." << endl;
	}
}
