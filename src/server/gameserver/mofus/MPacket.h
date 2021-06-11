/////////////////////////////////////////////////////////////////////////////
// Filename : MPacket.h
// Desc		: 모퍼스 용 패킷
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_H__
#define __MPACKET_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

// packet size type
typedef int MPacketSize_t;
const unsigned int szMPacketSize = sizeof(MPacketSize_t);

// packet type
typedef int MPacketID_t;
const unsigned int szMPacketID = sizeof(MPacketID_t);

const unsigned int szMPacketHeader = szMPacketSize + szMPacketID;


class MPacket
{
public:
	// 패킷 아이디를 반환한다.
	virtual MPacketID_t getID() const = 0;

	// 패킷의 크리를 반환한다.
	virtual MPacketSize_t getSize() const = 0;

	// 새로운 패킷을 생성해서 반환
	virtual MPacket* create() = 0;

	// 입력 스트림으로부터 데이터를 읽어서 패킷을 초기화 한다.
	virtual void read( SocketInputStream& iStream ) = 0;

	// 출력 스트림으로 패킷의 바이너리 이미지를 보낸다.
	virtual void write( SocketOutputStream& oStream ) = 0;

	// debug message
	virtual string toString() const = 0;
};

#endif

