//----------------------------------------------------------------------
//
// Filename    : PCInfo.h
// Writen By   : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PC_INFO_H__
#define __PC_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
// class PCInfo;
//
// LCPCList 패킷에 담겨서 날아오는 SlayerPCInfo, VampirePCInfo 클래스의 베이스
// 클래스이다. LCPCList 패킷에는 PCInfo* [3] 이 저장되며, DB 상의 캐릭터의
// 숫자에 따라서, 여기에 실제 SlayerPCInfo, VampirePCInfo 또는 NULL 이 저장
// 된다.
//
//----------------------------------------------------------------------

class PCInfo {

public :

	// destructor
	virtual ~PCInfo () {}	

	// 현재 인스턴스가 슬레이어인지 뱀파이어인지..
	virtual PCType getPCType () const throw () = 0;	

	//----------------------------------------------------------------------
	// 패킷에 embedding 되려는 객체는 아래와 같은 데이타를 명시해야 한다.
	//----------------------------------------------------------------------

	// read data from socket input stream
	virtual void read (SocketInputStream & iStream) throw (ProtocolException, Error) = 0;

	// write data to socket output stream
	virtual void write (SocketOutputStream & oStream) const throw (ProtocolException, Error) = 0;

	// get size of object
	virtual uint getSize () const throw () = 0;

	// get debug string
	virtual string toString () const throw () = 0;

};

#endif
