
// Billing Test

#include <iostream>
#include "BillingPlayerManager.h"
#include "DatabaseManager.h"
#include "Properties.h"
#include "CommonBillingPacket.h"

int main (int argc , char* argv[])
{
	CommonBillingPacket cbp;
	cbp.test();
	cout << cbp.toString().c_str() << endl;



	// command-line parameter를 string 으로 변환한다. ^^;
    string* Argv;
        
    Argv = new string[argc];
    for (int i = 0 ; i < argc ; i ++)
        Argv[i] = argv[i];

    // 환경 파일을 읽어들인다.
    // 단 실행 파일은 $VSHOME/bin에, 환경 파일은 $VSHOME/conf 에 존재해야 한다.�
    // command line 에서 환경 파일을 지정할 수 있도록 한다.

	//-------------------------------------------------------------------
	// Load config file
	//-------------------------------------------------------------------
    try 
	{
        if (Argv[1] != "-f") 
		{
            throw Error("Usage : gameserver -f 환경파일");
        }

        // 첫번째 파라미터가 -f 일 경우, 두번째 파라미터는 환경파일의 위치가 된다.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
    } 
	catch (Error & e) 
	{
        cout << e.toString() << endl;
		return 0;
    }

	//-------------------------------------------------------------------
	// DatabaseManager
	//-------------------------------------------------------------------
	g_pDatabaseManager = new DatabaseManager();

	//-------------------------------------------------------------------
	// BillingPlayerManager
	//-------------------------------------------------------------------
	g_pBillingPlayerManager = new BillingPlayerManager();

	try {

		g_pBillingPlayerManager->init();
		g_pBillingPlayerManager->start();

	} catch (Throwable &t) {
		cout << t.toString().c_str() << endl;
	}

	//-------------------------------------------------------------------
	// Main Loop
	//-------------------------------------------------------------------
	string cmd;
	while (1)
	{
		cout << "command> ";
		cin >> cmd;

		if (cmd=="quit")
			break;
	}

	delete g_pBillingPlayerManager;
}

