//////////////////////////////////////////////////////////////////////////////
// Filename    : LogClient.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include "LogClient.h"
#include "LogData.h"


LogClient* g_pLogClient = NULL;
int LogClient::m_LogLevel = 0;

//void log(short type, const string& source, const string& target) {
    /*
    // 로그 타입을 검사하는 일은 LogClient::log() 함수 내에서
    // 체크해야 깔끔할 것 같지만, 될 수 있는 한 함수 호출을 줄이기 위해서
    // 전역 함수 내에서 했다.
    if (type < LogClient::getLogLevel())
    {
        g_pLogClient->_log(type, source, target);
    }
    else { }
    */
//}

//void log(short type, const string& source, const string& target, const string& content) {
    /*
    // 로그 타입을 검사하는 일은 LogClient::log() 함수 내에서
    // 체크해야 깔끔할 것 같지만, 될 수 있는 한 함수 호출을 줄이기 위해서
    // 전역 함수 내에서 했다.
    if (type < LogClient::getLogLevel())
    {
        g_pLogClient->_log(type, source, target, content);
    }
    else { }
    */
//}

//void log(short type, const string& source, const string& target, const string& content, short zoneid) {
    /*
    // 로그 타입을 검사하는 일은 LogClient::log() 함수 내에서
    // 체크해야 깔끔할 것 같지만, 될 수 있는 한 함수 호출을 줄이기 위해서
    // 전역 함수 내에서 했다.
    if (type < LogClient::getLogLevel())
    {
        g_pLogClient->_log(type, source, target, content, zoneid);
    }
    else { }
    */
//}


LogClient::LogClient(string ip, short port) {
    m_bConnected = false;
    m_Sent = 0;

    connect(ip, port);
}


//void LogClient::connect(string ip, short port) {
    /*
    if (m_bConnected)
    {
        cout << "LogClient::connect() : already connected" << endl;
        return;
    }

    sockaddr_in serv_addr;
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    int n = inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
    if (n <= 0)
    {
        cout << "LogClient::connect() : could not complete inet_pton" << endl;
        exit(0);
    }

    ::connect(m_Socket, (sockaddr*)&serv_addr, sizeof(serv_addr));

    m_bConnected = true;
    */
//}

//void LogClient::disconnect(void) {
    /*
    if (!m_bConnected)
    {
        cout << "LogClient::disconnect() : not connected yet" << endl;
        return;
    }

    close(m_Socket);
    */
//}

//void LogClient::_log(short type, const string& source, const string& target) {
    /*
    LogData data;

    data.setType(type);
    data.setSource(source);
    data.setTarget(target);

    //m_Sent += data.getSize();

    data.write(m_Socket);
    */
//}

//void LogClient::_log(short type, const string& source, const string& target, const string& content) {
    /*
    LogData data;

    data.setType(type);
    data.setSource(source);
    data.setTarget(target);
    data.setContent(content);

    //m_Sent += data.getSize();

    data.write(m_Socket);
    */
//}

//void LogClient::_log(short type, const string& source, const string& target, const string& content, short zoneid) {
    /*
    LogData data;

    data.setType(type);
    data.setSource(source);
    data.setTarget(target);
    data.setContent(content);
    data.setZoneID(zoneid);

    //m_Sent += data.getSize();

    data.write(m_Socket);
    */
//}
