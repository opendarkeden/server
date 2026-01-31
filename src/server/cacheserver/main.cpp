//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : Àå È« Ã¢   changaya@metrotech.co.kr
// Description : Database Cache Server¿ë main function
//
//////////////////////////////////////////////////////////////////////

// include files
#include <stdlib.h>
#include <unistd.h>

#include <new>

#include <sys/resource.h>
#include <sys/time.h>

#include "Exception.h"
#include "GameServer.h"
#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include "Types.h"

void memoryError() {
    cerr << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
    exit(0);
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    cout << ">>> STARTING CACHE SERVER..." << endl;

    // ¸Þ¸ð¸® ¾ø´Ù..ÇÔ¼ö¸¦ ¼³Á¤ÇÑ´Ù.
    set_new_handler(memoryError);
    cout << ">>> MEMORY HANDLER INSTALL SUCCESS..." << endl;

    // What?
    int* pPointer = NULL;
    pPointer = new int[500000000];
    delete pPointer;

    // ÀûÀýÇÑ À§Ä¡¸¦ Ã£¾Æº¸ÀÚ.
    srand(time(0));
    cout << ">>> RANDOMIZATION INITIALIZATION SUCCESS..." << endl;

    if (argc < 3) {
        cout << "Usage : cacheserver -f È¯°æÆÄÀÏ" << endl;
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
            throw Error("Usage : cacheserver -f È¯°æÆÄÀÏ");
        }

        // Ã¹¹øÂ° ÆÄ¶ó¹ÌÅÍ°¡ -f ÀÏ °æ¿ì, µÎ¹øÂ° ÆÄ¶ó¹ÌÅÍ´Â È¯°æÆÄÀÏÀÇ À§Ä¡°¡ µÈ´Ù.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);

        // cout << g_pConfig->toString() << endl;
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

        log(LOG_GAMESERVER, "", "", "Cache Server Start");

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
        // what?
        struct rlimit rl;
        rl.rlim_cur = RLIM_INFINITY;
        rl.rlim_max = RLIM_INFINITY;
        setrlimit(RLIMIT_CORE, &rl);

        // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÑ´Ù.
        g_pCacheServer = new CacheServer();

        cout << ">>> CACHE SERVER INSTANCE CREATED..." << endl;

        // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ ÃÊ±âÈ­ÇÑ´Ù.
        g_pCacheServer->init();

        cout << ">>> CACHE SERVER INITIALIZATION SUCCESS..." << endl;

        // °ÔÀÓ ¼­¹ö °´Ã¼¸¦ È°¼ºÈ­½ÃÅ²´Ù.
        g_pCacheServer->start();
    } catch (Throwable& e) {
        // ·Î±×°¡ ÀÌ·ïÁö±â Àü¿¡ ¼­¹ö°¡ ³¡³¯ °æ¿ì¸¦ ´ëºñÇØ¼­
        ofstream ofile("../log/instant.log", ios::out);
        ofile << e.toString() << endl;
        ofile.close();

        // Ç¥ÁØ Ãâ·ÂÀ¸·Îµµ Ãâ·ÂÇØÁØ´Ù.
        cout << e.toString() << endl;

        // °ÔÀÓ ¼­¹ö¸¦ Áß´Ü½ÃÅ²´Ù.
        // ÀÌ ³»ºÎ¿¡¼­ ÇÏÀ§ ¸Å´ÏÀú ¿ª½Ã Áß´ÜµÇ¾î¾ß ÇÑ´Ù.
        g_pCacheServer->stop();
    } catch (...) {
        cout << "unknown exception..." << endl;
    }
}
