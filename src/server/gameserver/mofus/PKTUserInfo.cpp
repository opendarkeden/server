/////////////////////////////////////////////////////////////////////////////
// Filename : PKTUserInfo.cpp
// Desc		: User info packet carrying userID, character name, account name, and serials.
// 			  Sent from client to server when updating billing info.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTUserInfo.h"

#include "Assert.h"
#include "MPacketID.h"

// constructor
PKTUserInfo::PKTUserInfo() : _PKT_USERINFO() {
    nSize = szPKTUserInfo - szMPacketSize;
    nCode = 0;
    sJuminNo[0] = '\0';
    sHandPhone[0] = '\0';
    nIndex = 0;
}

// Deserialize packet from input stream.
void PKTUserInfo::read(SocketInputStream& iStream) {
    iStream.read((char*)this, szPKTUserInfo);

    // change order - network to host
    //	nSize		= ntohl( nSize );
    //	nCode		= ntohl( nCode );
    //	nIndex		= ntohl( nIndex );
}

// Serialize packet to output stream.
void PKTUserInfo::write(SocketOutputStream& oStream) {
    nCode = getID();

    // change order - host to network
    //	nSize		= htonl( nSize );
    //	nCode		= htonl( nCode );
    //	nIndex		= htonl( nIndex );

    oStream.write((const char*)this, szPKTUserInfo);

    // restore order
    //	nSize		= ntohl( nSize );
    //	nCode		= ntohl( nCode );
    //	nIndex		= ntohl( nIndex );
}

// debug message
string PKTUserInfo::toString() const {
    char str[32];
    StringStream msg;
    msg << "UserInfo(";
    memcpy(str, sJuminNo, 20);
    str[20] = '\0';
    msg << "JuminNo:" << str;
    memcpy(str, sHandPhone, 12);
    str[12] = '\0';
    msg << ",HandPhone:" << str << ",Index:" << nIndex << ")";

    return msg.toString();
}

// set ssn
void PKTUserInfo::setSSN(const string& ssn) {
    Assert(ssn.size() > 0 && ssn.size() <= 20);

    strcpy(sJuminNo, ssn.c_str());
}

// set cellnum
void PKTUserInfo::setCellNum(const string& cellnum) {
    Assert(cellnum.size() > 0 && cellnum.size() <= 12);

    strcpy(sHandPhone, cellnum.c_str());
}
