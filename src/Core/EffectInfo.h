//////////////////////////////////////////////////////////////////////
// 
// Filename    : EffectInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INFO_H__
#define __EFFECT_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class EffectInfo;
//
// 게임서버에서 클라이언트로 이펙트 정보를 알려주기 위한 객채
// GCUpdateInfo, AddSlayer, AddVampire, AddMonster등에 실려서 날아간다.
//
//////////////////////////////////////////////////////////////////////

class EffectInfo {

public :
	
	// constructor
	EffectInfo () throw ();
	
	// destructor
	~EffectInfo () throw ();
	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () const throw () { return szBYTE + szWORD* m_ListNum* 2; }
	static PacketSize_t getMaxSize() throw() { return 255;}

	// get packet's debug string
	string toString () const throw ();

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(EffectID_t EffectID, WORD Value) throw(); 

	// ClearList
	void clearList() throw() { m_EList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	WORD popFrontListElement() throw() { WORD EffectList = m_EList.front(); m_EList.pop_front(); return EffectList; }

protected :
	
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	list<WORD> m_EList;

};

#endif
