//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : °ÔÀÓ ¼­¹ö¿ë ¸ÞÀÎ ÇÔ¼ö
//
//////////////////////////////////////////////////////////////////////

// include files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <new>
#include <stdexcept>

#include <sys/resource.h>
#include <sys/time.h>

#include "Exception.h"
#include "GameServer.h"
#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include "Types.h"

void handleMemoryError() {
    cerr << "==============================================================================" << endl;
    cerr << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
    cerr << "==============================================================================" << endl;
    filelog("CriticalError.log", "CRITICAL ERROR! NOT ENOUGH MEMORY!");
    abort();
}

void handleUnhandledException() {
    cerr << "==============================================================================" << endl;
    cerr << "UNHANDLED EXCEPTION OCCURED" << endl;
    cerr << "==============================================================================" << endl;
    filelog("CriticalError.log", "UNHANDLED EXCEPTION OCCURED");
    abort();
}

void handleUnexpectedException() {
    cerr << "==============================================================================" << endl;
    cerr << "UNEXPECTED EXCEPTION OCCURED" << endl;
    cerr << "==============================================================================" << endl;
    filelog("CriticalError.log", "UNEXPECTED EXCEPTION OCCURED");
    abort();
}

void testMaxMemory() {
    long mem = 10 * 1024 * 1024; // 10M

    char str[80];

    for (int i = 1; i < 2048; i++) {
        char* p = new char[mem];

        sprintf(str, "0x%08X = %04d0 M", p, i);

        cout << str << endl;
    }
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    cout << ">>> STARTING GAME SERVER..." << endl;

    filelog("serverStart.log", "GameServer Start");

    // °¢Á¾ ÇÚµé·¯¸¦ ¼³Á¤ÇÑ´Ù.
    std::set_new_handler(handleMemoryError);
    std::set_terminate(handleUnhandledException);
    std::set_unexpected(handleUnexpectedException);

    /*
    int* pPointer = NULL;
    pPointer = new int[10000000];
    delete [] pPointer;
    */

    // ÀûÀýÇÑ À§Ä¡¸¦ Ã£¾Æº¸ÀÚ.
    srand(time(0));
    cout << ">>> RANDOMIZATION INITIALIZATION SUCCESS..." << endl;

    if (argc < 3) {
        // cout << "Usage : gameserver -f È¯°æÆÄÀÏ" << endl;
        exit(1);
    }

    // command-line parameter¸¦ string À¸·Î º¯È¯ÇÑ´Ù. ^^;
    string* Argv;

    Argv = new string[argc];
    for (int i = 0; i < argc; i++)
        Argv[i] = argv[i];

    cout << ">>> COMMAND-LINE PARAMETER READING SUCCESS..." << endl;

    // È¯°æ ÆÄÀÏÀ» ÀÐ¾îµéÀÎ´Ù.
    // ´Ü ½ÇÇà ÆÄÀÏÀº $VSHOME/bin¿¡, È¯°æ ÆÄÀÏÀº $VSHOME/conf ¿¡ Á¸ÀçÇØ¾ß ÇÑ´Ù.½
    // command line ¿¡¼­ È¯°æ ÆÄÀÏÀ» ÁöÁ¤ÇÒ ¼ö ÀÖµµ·Ï ÇÑ´Ù.

    try {
        if (Argv[1] != "-f") {
            throw Error("Usage : gameserver -f È¯°æÆÄÀÏ -t Å×½ºÆ®È¯°æÆÄÀÏ");
        }

        // Ã¹¹øÂ° ÆÄ¶ó¹ÌÅÍ°¡ -f ÀÏ °æ¿ì, µÎ¹øÂ° ÆÄ¶ó¹ÌÅÍ´Â È¯°æÆÄÀÏÀÇ À§Ä¡°¡ µÈ´Ù.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);

        // cout << g_pConfig->toString() << endl;

        // by sigi. 2002.12.26
        if (argc >= 4 && Argv[3] == "-t") {
            g_pTestConfig = new Properties();

            if (argc >= 5) {
                g_pTestConfig->load(Argv[4]);
            }
        }
    } catch (Error& e) {
        // cout << e.toString() << endl;
    }

    // ·Î±× ¸Å´ÏÀú¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑÈÄ È°¼ºÈ­½ÃÅ²´Ù.
    // ·Î±× ¸Å´ÏÀú´Â °ÔÀÓ ¼­¹öÀÇ ÃÊ±âÈ­°úÁ¤¿¡¼­ ¹ß»ýÇÒ °¡´É¼ºÀÌ ÀÖ´Â ¿¡·¯±îÁöµµ
    // °ËÃâÇØ³»¾ß ÇÏ¹Ç·Î °ÔÀÓ ¼­¹ö ³»ºÎ¿¡¼­ ÃÊ±âÈ­ÇØ¼­´Â ¾ÈµÈ´Ù.
    // ¶ÇÇÑ ´Ù¸¥ °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÏ±âÀü¿¡ ·Î±×¸Å´ÏÀú°¡ ¿ì¼±ÀûÀ¸·Î »ý¼º,
    // ÃÊ±âÈ­µÇ¾î¾ß ÇÑ´Ù.
    try {
        string LogServerIP = g_pConfig->getProperty("LogServerIP");
        int LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
        int LogLevel = g_pConfig->getPropertyInt("LogLevel");
        g_pLogClient = new LogClient(LogServerIP, LogServerPort);
        LogClient::setLogLevel(LogLevel);

        log(LOG_GAMESERVER, "", "", "Game Server Start");

        // cout << "LogServerIP = " << LogServerIP << endl;
        // cout << "LogServerPort = " << LogServerPort << endl;
        // cout << "LogLevel = " << LogClient::getLogLevel() << endl;
    } catch (Error& e) {
        // cout << e.toString() << endl;
    }

    cout << ">>> LOGCLIENT INITIALZATION SUCCESS..." << endl;

    //
    // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑ ÈÄ È°¼ºÈ­½ÃÅ²´Ù.
    //
    try {
        struct rlimit rl;
        rl.rlim_cur = RLIM_INFINITY;
        rl.rlim_max = RLIM_INFINITY;
        setrlimit(RLIMIT_CORE, &rl);

        // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÑ´Ù.
        g_pGameServer = new GameServer();

        cout << ">>> GAME SERVER INSTANCE CREATED..." << endl;

        // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ ÃÊ±âÈ­ÇÑ´Ù.
        g_pGameServer->init();

        cout << ">>> GAME SERVER INITIALIZATION SUCCESS..." << endl;

        // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ È°¼ºÈ­½ÃÅ²´Ù.
        g_pGameServer->start();
    } catch (Throwable& e) {
        // ·Î±×°¡ ÀÌ·ïÁö±â Àü¿¡ ¼­¹ö°¡ ³¡³¯ °æ¿ì¸¦ ´ëºñÇØ¼­
        ofstream ofile("../log/instant.log", ios::out);
        ofile << e.toString() << endl;
        ofile.close();

        // Ç¥ÁØ Ãâ·ÂÀ¸·Îµµ Ãâ·ÂÇØÁØ´Ù.
        cout << e.toString() << endl;

        // °ÔÀÓ ¼­¹ö¸¦ Áß´Ü½ÃÅ²´Ù.
        // ÀÌ ³»ºÎ¿¡¼­ ÇÏÀ§ ¸Å´ÏÀú ¿ª½Ã Áß´ÜµÇ¾î¾ß ÇÑ´Ù.
        g_pGameServer->stop();
    } catch (...) {
        cout << "unknown exception..." << endl;
    }
}
