//////////////////////////////////////////////////////////////////////
// 
// Filename    : PCSkillInfo.h 
// Written By  : elca@ewestsoft.com
// Description :  스킬의 정보들
// 
//////////////////////////////////////////////////////////////////////

#ifndef __PC_SKILL_INFO_H__
#define __PC_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class PCSkillInfo;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class PCSkillInfo {

public :
	
	// destructor
	virtual ~PCSkillInfo () throw () {}

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    virtual void read (SocketInputStream & iStream) throw (ProtocolException, Error) = 0;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    virtual void write (SocketOutputStream & oStream) const throw (ProtocolException, Error) = 0;

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	virtual PacketSize_t getSize () throw () = 0;

	// get packet's debug string
	virtual string toString () const throw () = 0;

};

#endif
