//////////////////////////////////////////////////////////////////////
// 
// Filename    : ExtraInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 인벤토리 아이템의 정보들
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EXTRA_INFO_H__
#define __EXTRA_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ExtraSlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class ExtraInfo;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class ExtraInfo {

public :
	
	// constructor
	ExtraInfo () throw ();
	
	// destructor
	~ExtraInfo () throw ();

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () throw ();

	static uint getMaxSize () throw () { 
		return szBYTE + (ExtraSlotInfo::getMaxSize()* 1);
	}

	// get packet's debug string
	string toString () const throw ();

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(ExtraSlotInfo* pExtraSlotInfo) throw() { m_ExtraSlotInfoList.push_back(pExtraSlotInfo); }

	// ClearList
	void clearList() throw() { m_ExtraSlotInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	ExtraSlotInfo* popFrontListElement() throw() 
	{ 
		ExtraSlotInfo* TempExtraSlotInfo = m_ExtraSlotInfoList.front(); m_ExtraSlotInfoList.pop_front(); return TempExtraSlotInfo; 
	}

private :
	
	// ExtraSlotInfo List Total Number
	BYTE m_ListNum;

	// ExtraSlotInfo List
	list<ExtraSlotInfo*> m_ExtraSlotInfoList;

};

#endif
