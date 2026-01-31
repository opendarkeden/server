//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : ·Î±×ÀÎ ¼­¹ö¿ë ¸ÞÀÎ ÇÔ¼ö
//
//////////////////////////////////////////////////////////////////////

// include files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <new>

#include <sys/resource.h>
#include <sys/time.h>

#include "Exception.h"
#include "LogClient.h"
#include "LoginServer.h"
#include "Properties.h"
#include "StringStream.h"
#include "Types.h"

void memoryError() {
    cout << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
    exit(0);
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    // ¸Þ¸ð¸® ¾ø´Ù.. ÇÔ¼ö¸¦ ¼³Á¤ÇÑ´Ù.
    set_new_handler(memoryError);

    if (argc < 3) {
        cout << "Usage : loginserver -f È¯°æÆÄÀÏ [-p port]" << endl;
        exit(1);
    }

    // command-line parameter¸¦ string À¸·Î º¯È¯ÇÑ´Ù. ^^;
    string* Argv;

    Argv = new string[argc];
    for (int i = 0; i < argc; i++)
        Argv[i] = argv[i];

    // È¯°æ ÆÄÀÏÀ» ÀÐ¾îµéÀÎ´Ù.
    // ´Ü ½ÇÇà ÆÄÀÏÀº $VSHOME/bin¿¡, È¯°æ ÆÄÀÏÀº $VSHOME/conf ¿¡ Á¸ÀçÇØ¾ß ÇÑ´Ù.½
    // command line ¿¡¼­ È¯°æ ÆÄÀÏÀ» ÁöÁ¤ÇÒ ¼ö ÀÖµµ·Ï ÇÑ´Ù.

    try {
        if (Argv[1] != "-f") {
            throw Error("Usage : loginserver -f È¯°æÆÄÀÏ [-p port]");
        }

        // Ã¹¹øÂ° ÆÄ¶ó¹ÌÅÍ°¡ -f ÀÏ °æ¿ì, µÎ¹øÂ° ÆÄ¶ó¹ÌÅÍ´Â È¯°æÆÄÀÏÀÇ À§Ä¡°¡ µÈ´Ù.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);

        cout << g_pConfig->toString() << endl;

    } catch (Error& e) {
        cout << e.toString() << endl;
    }

    try {
        if (argc > 3) {
            if (argc < 5 || Argv[3] != "-i")
                throw Error("Usage : loginserver -f È¯°æÆÄÀÏ [-i ID]");

            // port¸¦ °­Á¦·Î ¼³Á¤ÇÑ´Ù.
            char sLoginServerPort[5], sLoginServerUDPPort[5], sLoginServerID[5];
            sprintf(sLoginServerPort, "%d", g_pConfig->getPropertyInt("LoginServerBasePort") + atoi(argv[4]));
            sprintf(sLoginServerUDPPort, "%d", g_pConfig->getPropertyInt("LoginServerBaseUDPPort") + atoi(argv[4]));
            sprintf(sLoginServerID, "%d", g_pConfig->getPropertyInt("LoginServerBaseID") + atoi(argv[4]));

            g_pConfig->setProperty("LoginServerPort", sLoginServerPort);
            g_pConfig->setProperty("LoginServerUDPPort", sLoginServerUDPPort);
            g_pConfig->setProperty("LoginServerID", sLoginServerID);

            cout << "LoginServerPort : " << sLoginServerPort << endl;
            cout << "LoginServerUDPPort : " << sLoginServerUDPPort << endl;
            cout << "LoginServerID : " << sLoginServerID << endl;
        }

    } catch (Error& e) {
        cout << e.toString() << endl;
    }


    // ·Î±× ¸Å´ÏÀú¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑÈÄ È°¼ºÈ­½ÃÅ²´Ù.
    // ·Î±× ¸Å´ÏÀú´Â ·Î±×ÀÎ ¼­¹öÀÇ ÃÊ±âÈ­°úÁ¤¿¡¼­ ¹ß»ýÇÒ °¡´É¼ºÀÌ ÀÖ´Â ¿¡·¯±îÁöµµ
    // °ËÃâÇØ³»¾ß ÇÏ¹Ç·Î ·Î±×ÀÎ ¼­¹ö ³»ºÎ¿¡¼­ ÃÊ±âÈ­ÇØ¼­´Â ¾ÈµÈ´Ù.
    // ¶ÇÇÑ ´Ù¸¥ °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÏ±âÀü¿¡ ·Î±×¸Å´ÏÀú°¡ ¿ì¼±ÀûÀ¸·Î »ý¼º,
    // ÃÊ±âÈ­µÇ¾î¾ß ÇÑ´Ù.

    try {
        string LogServerIP = g_pConfig->getProperty("LogServerIP");
        int LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
        g_pLogClient = new LogClient(LogServerIP, LogServerPort);
        LogClient::setLogLevel(g_pConfig->getPropertyInt("LogLevel"));

        log(LOG_LOGINSERVER, "", "", "Login Server Start");
    } catch (Throwable& t) {
        cout << t.toString() << endl;
    }

    //
    // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑ ÈÄ È°¼ºÈ­½ÃÅ²´Ù.
    //
    try {
        struct rlimit rl;
        rl.rlim_cur = RLIM_INFINITY;
        rl.rlim_max = RLIM_INFINITY;
        setrlimit(RLIMIT_CORE, &rl);

        // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÑ´Ù.
        g_pLoginServer = new LoginServer();

        // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ ÃÊ±âÈ­ÇÑ´Ù.
        g_pLoginServer->init();

        // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ È°¼ºÈ­½ÃÅ²´Ù.
        g_pLoginServer->start();
    } catch (Throwable& e) {
        // ·Î±×°¡ ÀÌ·ïÁö±â Àü¿¡ ¼­¹ö°¡ ³¡³¯ °æ¿ì¸¦ ´ëºñÇØ¼­
        ofstream ofile("../log/instant.log", ios::out);
        ofile << e.toString() << endl;
        ofile.close();

        // ÇÏÀ§¿¡¼­ Ä³Ä¡µÇÁö ¾ÊÀº ¿¹¿Ü ¶Ç´Â ¿¡·¯°¡ ¹ß»ýÇß´Ù´Â ¶æÀÌ´Ù.
        // ÀÌ °æ¿ì LEVEL1·Î ·Î±×ÇØ¾ß ÇÑ´Ù. (¹«Á¶°Ç ·Î±×ÇÑ´Ù´Â ¶æ)
        log(LOG_LOGINSERVER_ERROR, "", "", e.toString());

        // Ç¥ÁØ Ãâ·ÂÀ¸·Îµµ Ãâ·ÂÇØÁØ´Ù.
        cout << e.toString() << endl;

        // ·Î±×ÀÎ ¼­¹ö¸¦ Áß´Ü½ÃÅ²´Ù.
        // ÀÌ ³»ºÎ¿¡¼­ ÇÏÀ§ ¸Å´ÏÀú ¿ª½Ã Áß´ÜµÇ¾î¾ß ÇÑ´Ù.
        g_pLoginServer->stop();
    }
}
