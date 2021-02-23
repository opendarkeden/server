//////////////////////////////////////////////////////////////////////
// 
// Filename    : ModifyItemInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __MODIFY_ITEM_INFO_H__
#define __MODIFY_ITEM_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class ModifyItemInfo;
//
// 게임서버에서 클라이언트로 자신의 변형된 데이터를 알려주기 위한 객채
// ModifyItemInformation, SkillToObjectOK 등에 실려서 날아간다.
//
//////////////////////////////////////////////////////////////////////

class ModifyItemInfo {

public :
	
	// constructor
	ModifyItemInfo () throw ();
	
	// destructor
	~ModifyItemInfo () throw ();
	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize () const throw () { return szDWORD + szDWORD* m_ListNum* 3 ; }

	// get packet's debug string
	string toString () const throw ();

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(ObjectID_t ObjectID, ModifyType List, DWORD Value) throw(); 

	// ClearList
	void clearList() throw() { m_SList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	DWORD popFrontListElement() throw() { DWORD StatusList = m_SList.front(); m_SList.pop_front(); return StatusList; }

private :
	
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	list<DWORD> m_SList;

};

#endif
