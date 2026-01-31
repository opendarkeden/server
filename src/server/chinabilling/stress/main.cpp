//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : ·Î±×ÀÎ ¼­¹ö¿ë ¸ÞÀÎ ÇÔ¼ö
//
//////////////////////////////////////////////////////////////////////

// include files
#include <stdlib.h>

#include <new>

#include <sys/resource.h>

#include "Exception.h"
#include "PayUserManager.h"
#include "Properties.h"
#include "SBillingPlayerManager.h"
#include "SProfile.h"
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
        cout << "Usage : stress -f È¯°æÆÄÀÏ" << endl;
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
            throw Error("Usage : stress -f È¯°æÆÄÀÏ");
        }

        // Ã¹¹øÂ° ÆÄ¶ó¹ÌÅÍ°¡ -f ÀÏ °æ¿ì, µÎ¹øÂ° ÆÄ¶ó¹ÌÅÍ´Â È¯°æÆÄÀÏÀÇ À§Ä¡°¡ µÈ´Ù.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);

        cout << g_pConfig->toString() << endl;

    } catch (Error& e) {
        cout << e.toString() << endl;
    }

    // ·Î±× ¸Å´ÏÀú¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑÈÄ È°¼ºÈ­½ÃÅ²´Ù.
    // ·Î±× ¸Å´ÏÀú´Â ·Î±×ÀÎ ¼­¹öÀÇ ÃÊ±âÈ­°úÁ¤¿¡¼­ ¹ß»ýÇÒ °¡´É¼ºÀÌ ÀÖ´Â ¿¡·¯±îÁöµµ
    // °ËÃâÇØ³»¾ß ÇÏ¹Ç·Î ·Î±×ÀÎ ¼­¹ö ³»ºÎ¿¡¼­ ÃÊ±âÈ­ÇØ¼­´Â ¾ÈµÈ´Ù.
    // ¶ÇÇÑ ´Ù¸¥ °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÏ±âÀü¿¡ ·Î±×¸Å´ÏÀú°¡ ¿ì¼±ÀûÀ¸·Î »ý¼º,
    // ÃÊ±âÈ­µÇ¾î¾ß ÇÑ´Ù.

    //
    // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÏ°í ÃÊ±âÈ­ÇÑ ÈÄ È°¼ºÈ­½ÃÅ²´Ù.
    //
    try {
        struct rlimit rl;
        rl.rlim_cur = RLIM_INFINITY;
        rl.rlim_max = RLIM_INFINITY;
        setrlimit(RLIMIT_CORE, &rl);

        // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ »ý¼ºÇÑ´Ù.
        g_pSBillingPlayerManager = new SBillingPlayerManager();
        g_pPayUserManager = new PayUserManager();
        g_pSProfile = new SProfile();

        // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ ÃÊ±âÈ­ÇÑ´Ù.
        g_pSBillingPlayerManager->init();
        g_pPayUserManager->init();

        // ·Î±×ÀÎ ¼­¹ö °´Ã¼¸¦ È°¼ºÈ­½ÃÅ²´Ù.
        g_pSBillingPlayerManager->start();
        g_pPayUserManager->start();

        while (true)
            usleep(100);
    } catch (Throwable& e) {
        // ·Î±×°¡ ÀÌ·ïÁö±â Àü¿¡ ¼­¹ö°¡ ³¡³¯ °æ¿ì¸¦ ´ëºñÇØ¼­
        ofstream ofile("../log/instant.log", ios::out);
        ofile << e.toString() << endl;
        ofile.close();

        // Ç¥ÁØ Ãâ·ÂÀ¸·Îµµ Ãâ·ÂÇØÁØ´Ù.
        cout << e.toString() << endl;

        // ·Î±×ÀÎ ¼­¹ö¸¦ Áß´Ü½ÃÅ²´Ù.
        // ÀÌ ³»ºÎ¿¡¼­ ÇÏÀ§ ¸Å´ÏÀú ¿ª½Ã Áß´ÜµÇ¾î¾ß ÇÑ´Ù.
    }
}
