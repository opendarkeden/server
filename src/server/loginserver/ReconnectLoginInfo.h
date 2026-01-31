//----------------------------------------------------------------------
//
// Filename    : ReconnectLoginInfo.h
// Written by  : reiot@ewestsoft.com
// Description :
//
//----------------------------------------------------------------------

#ifndef __RECONNECT_LOGIN_INFO_H__
#define __RECONNECT_LOGIN_INFO_H__

// include files
#include "Exception.h"
#include "StringStream.h"
#include "Timeval.h"
#include "Types.h"

//----------------------------------------------------------------------
//
// class ReconnectLoginInfo;
//
// ¼­¹ö°£ ÀÌµ¿¿¡¼­ Á¤´çÇÑ ¿¬°á¿¡ ´ëÇÑ Á¤º¸¸¦ ³ªÅ¸³»´Â °´Ã¼
//
//----------------------------------------------------------------------

class ReconnectLoginInfo {
public:
    // constructor
    ReconnectLoginInfo() throw() : m_Key(0) {
        m_ExpireTime.tv_sec = 0;
        m_ExpireTime.tv_usec = 0;
    }

    // destructor
    ~ReconnectLoginInfo() throw() {}

    // get/set client ip
    string getClientIP() const throw() {
        return m_ClientIP;
    }
    void setClientIP(const string& clientIP) throw() {
        m_ClientIP = clientIP;
    }

    // get/set PlayerID
    string getPlayerID() const throw() {
        return m_PlayerID;
    }
    void setPlayerID(const string& PlayerID) throw() {
        m_PlayerID = PlayerID;
    }

    // get/set expire time
    Timeval getExpireTime() const throw() {
        return m_ExpireTime;
    }
    void setExpireTime(Timeval tv) throw() {
        m_ExpireTime = tv;
    }

    // get/set validation key
    DWORD getKey() const throw() {
        return m_Key;
    }
    void setKey(DWORD key) throw() {
        m_Key = key;
    }

    // get debug string
    string toString() const throw() {
        StringStream msg;
        msg << "ReconnectLoginInfo(ClientIP:" << m_ClientIP << ",ExpireTime:" << m_ExpireTime.tv_sec << "."
            << m_ExpireTime.tv_usec << ",KEY: " << m_Key << ")";
        return msg.toString();
    }

private:
    // valid client's ip
    string m_ClientIP;

    // PlayerID
    string m_PlayerID;

    // expire time : ¾ðÁ¦±îÁö ÀÌ Á¤º¸¸¦ À¯ÁöÇÏ°í ÀÖ¾î¾ß ÇÏ´ÂÁö..
    Timeval m_ExpireTime;

    // validation key
    DWORD m_Key;
};

//----------------------------------------------------------------------
//
// CompareReconnectLoginInfo
//
// priority_queue ¿¡¼­ ReconnectLoginInfo ³¢¸® ºñ±³ÇÒ ¶§ »ç¿ëÇÏ´Â Å¬·¡½º¸
//
// *CAUTION*
//
// ½Ã°£ÀûÀ¸·Î ÀÌ¸¥(½Ã°£°ªÀÌ ÀÛÀº) ÂÊÀÌ PQ ÀÇ top ¿¡ À§Ä¡ÇØ¾ß ÇÑ´Ù.
// Áï PQ ´Â ascending order ¸¦ ÀÌ·ï¾ß ÇÑ´Ù. ¿Ö ±×·±Áö´Â Àß »ìÆìº¸±â¸¦..
// ½Ã°£ÀÌ ¾ø´Â °ü°è·Î.. - -;
//
//----------------------------------------------------------------------
class CompareReconnectLoginInfo {
public:
    // compare which is more recent
    bool operator()(const ReconnectLoginInfo& left, const ReconnectLoginInfo& right) {
        // Ascending Order
        return left.getExpireTime() > right.getExpireTime();

        // Descending Order
        // return left.getExpireTime() < right.getExpireTime();
    }
};

#endif
