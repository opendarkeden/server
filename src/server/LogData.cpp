//////////////////////////////////////////////////////////////////////////////
// Filename   : LogData.cpp
// Written by : excel96
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
#include "LogData.h"
#include "Utility.h"

#define LOGDATA_BUFFER_SIZE 2000

LogData::LogData() {
    m_Type = 0;
    m_ZoneID = 0;
    m_Source = "";
    m_Target = "";
    m_Content = "";
}


uint LogData::getSize(void) {
    uint rValue = 0;

    // 타입 사이즈
    rValue += szshort;

    // 존 아이디
    rValue += szshort;

    // 소스
    rValue += szBYTE;
    rValue += m_Source.size();

    // 타겟
    rValue += szBYTE;
    rValue += m_Target.size();

    // 컨텐트
    rValue += szshort;
    rValue += m_Content.size();

    return rValue;
}


int LogData::read(int sockfd) {
    BYTE  length;
    short length2;
    char  buf[LOGDATA_BUFFER_SIZE+1];

    // type
    if (recv(sockfd, &m_Type, szshort, 0) == 0) return 0;

    // zone id
    if (recv(sockfd, &m_ZoneID, szshort, 0) == 0) return 0;

    // source
    if (recv(sockfd, &length, szBYTE, 0) == 0) return 0;
    if (length != 0) {
        memset(buf, 0, sizeof(char)*(LOGDATA_BUFFER_SIZE+1));
        if (recv(sockfd, buf, length, 0) == 0) return 0;
        m_Source = string(buf);
    }

    // target
    if (recv(sockfd, &length, szBYTE, 0) == 0) return 0;
    if (length != 0) {
        memset(buf, 0, sizeof(char)*(LOGDATA_BUFFER_SIZE+1));
        if (recv(sockfd, buf, length, 0) == 0) return 0;
        m_Target = string(buf);
    }

    // content
    if (recv(sockfd, &length2, szshort, 0) == 0) return 0;
    if (length2 != 0) {
        memset(buf, 0, sizeof(char)*(LOGDATA_BUFFER_SIZE+1));
        if (recv(sockfd, buf, length2, 0) == 0) return 0;
        m_Content = string(buf);
    }

    return 1;
}


void LogData::write(int sockfd) {
    BYTE  length = 0;
    short length2 = 0;
    
    // type
    send(sockfd, &m_Type, szshort, 0);

    // zone id
    send(sockfd, &m_ZoneID, szshort, 0);

    // source
    length = m_Source.size();
    send(sockfd, &length, szBYTE, 0);
    if (m_Source.size() != 0) send(sockfd, m_Source.c_str(), m_Source.size(), 0);

    // target
    length = m_Target.size();
    send(sockfd, &length, szBYTE, 0);
    if (m_Target.size() != 0) send(sockfd, m_Target.c_str(), m_Target.size(), 0);

    // content
    length2 = m_Content.size();
    send(sockfd, &length2, szshort, 0);
    if (m_Content.size() != 0) send(sockfd, m_Content.c_str(), m_Content.size(), 0);
}


string LogData::toString(void) const {
    string msg = "";
    msg += "TYPE : [" + itos(m_Type) + "]";
    msg += "\nZONEID : [" + itos(m_ZoneID) + "]";
    msg += "\nSOURCE : [" + m_Source + "]";
    msg += "\nTARGET : [" + m_Target + "]";
    msg += "\nCONTENT : [" + m_Content + "]";
    return msg;
}
