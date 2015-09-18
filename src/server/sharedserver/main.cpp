//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : �α��� ������ ���� �Լ�
//
//////////////////////////////////////////////////////////////////////

#include "Types.h"
#include "Exception.h"
#include "SharedServer.h"
//#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include <stdlib.h>
#include <new>
#include <sys/resource.h>

void memoryError() {
    cout << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
    exit(0);
}

int main()
{
    // �޸��� ����.. �Լ��� �����Ѵ�.
    set_new_handler(memoryError);

    g_pConfig = new Properties();
    g_pConfig->load("../conf/sharedserver.conf");

    // �α� �Ŵ����� �����ϰ� �ʱ�ȭ���� Ȱ��ȭ��Ų��.
    // �α� �Ŵ����� �α��� ������ �ʱ�ȭ�������� �߻��� ���ɼ��� �ִ� ����������
    // �����س��� �ϹǷ� �α��� ���� ���ο��� �ʱ�ȭ�ؼ��� �ȵȴ�.
    // ���� �ٸ� ��ü�� �����ϰ� �ʱ�ȭ�ϱ����� �α׸Ŵ����� �켱������ ����,
    // �ʱ�ȭ�Ǿ��� �Ѵ�.

    try {
        string LogServerIP = g_pConfig->getProperty("LogServerIP");
        int LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
 //       g_pLogClient = new LogClient(LogServerIP, LogServerPort);
 //       LogClient::setLogLevel(g_pConfig->getPropertyInt("LogLevel"));

        //log(LOG_SHAREDSERVER, "", "", "Shared Server Start");
    }
    catch (Throwable & t) {
        cout << t.toString() << endl;
    }

    //
    // �α��� ���� ��ü�� �����ϰ� �ʱ�ȭ�� �� Ȱ��ȭ��Ų��.
    //
    try {
        struct rlimit rl;
        rl.rlim_cur = RLIM_INFINITY;
        rl.rlim_max = RLIM_INFINITY;
        setrlimit(RLIMIT_CORE, &rl);

        // �α��� ���� ��ü�� �����Ѵ�.
        g_pSharedServer = new SharedServer();

        // �α��� ���� ��ü�� �ʱ�ȭ�Ѵ�.
        g_pSharedServer->init();

        // �α��� ���� ��ü�� Ȱ��ȭ��Ų��.
        g_pSharedServer->start();
    }
    catch (Throwable & e) {
        // �αװ� �̷����� ���� ������ ���� ���츦 �����ؼ�
        ofstream ofile("../log/instant.log", ios::out);
        ofile << e.toString() << endl;
        ofile.close();

        // �������� ĳġ���� ���� ���� �Ǵ� ������ �߻��ߴٴ� ���̴�.
        // �� ���� LEVEL1�� �α��ؾ� �Ѵ�. (������ �α��Ѵٴ� ��)
        //log(LOG_SHAREDSERVER_ERROR, "", "", e.toString());

        // ǥ�� �������ε� �������ش�.
        cout << e.toString() << endl;

        // �α��� ������ �ߴܽ�Ų��.
        // �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ��� �Ѵ�.
        g_pSharedServer->stop();
    }
}
