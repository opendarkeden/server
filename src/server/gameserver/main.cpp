//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : ���� ������ ���� �Լ�
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Types.h"
#include "Exception.h"
#include "GameServer.h"
//#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <new>
#include <stdexcept>
#include <stdio.h>
#include "zlog.h"

void handleMemoryError()
{
	cerr << "==============================================================================" << endl;
	cerr << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
	cerr << "==============================================================================" << endl;
	filelog("CriticalError.log", "CRITICAL ERROR! NOT ENOUGH MEMORY!");
	abort();
}

void handleUnhandledException()
{
	cerr << "==============================================================================" << endl;
	cerr << "UNHANDLED EXCEPTION OCCURED" << endl;
	cerr << "==============================================================================" << endl;
	filelog("CriticalError.log", "UNHANDLED EXCEPTION OCCURED");
	abort();
}

void handleUnexpectedException()
{
	cerr << "==============================================================================" << endl;
	cerr << "UNEXPECTED EXCEPTION OCCURED" << endl;
	cerr << "==============================================================================" << endl;
	filelog("CriticalError.log", "UNEXPECTED EXCEPTION OCCURED");
	abort();
}

void testMaxMemory()
{
	long mem = 10*1024*1024; // 10M

	char str[80];

	for (int i=1; i<2048; i++)
	{
		char* p = new char [mem];

		sprintf(str, "0x%08X = %04d0 M", p, i);

		cout << str << endl;
	}
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main (int argc, char** argv) {
	cout << "[GAMESERVER] Starting..." << endl;

	filelog("serverStart.log", "GameServer Start");

	std::set_new_handler(handleMemoryError);
	std::set_terminate(handleUnhandledException);
	std::set_unexpected(handleUnexpectedException);

	srand(time(0));
	cout << "[GAMESERVER] Randomization Initialization success." << endl;

    g_pConfig = new Properties();
    g_pConfig->load("../conf/gameserver.conf");

    int rc = dzlog_init("../conf/log.conf", "my_cat");
    if (rc != 0) {
        printf("zlog init failed\n");
        return -1;
    }

	try 
	{
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// ���� ���� ��ü�� �����Ѵ�.
		g_pGameServer = new GameServer();

		cout << "[GAMESERVER] Instance created." << endl;

		// ���� ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pGameServer->init();

		cout << "[GAMESERVER] Initialization success." << endl;

		// ���� ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pGameServer->start();
	} 
	catch (Throwable & e) 
	{
		// �αװ� �̷����� ���� ������ ���� ���츦 �����ؼ�
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// ǥ�� �������ε� �������ش�.
		cout << e.toString() << endl;

		// ���� ������ �ߴܽ�Ų��.
		// �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ��� �Ѵ�.
		g_pGameServer->stop();
        zlog_fini();
	} 
	catch (...) 
	{
		cout << "unknown exception..." << endl;
	}
}
