//////////////////////////////////////////////////////////////////////
// 
// Filename    : ModifyItemInfo.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
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
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// ModifyItemInformation, SkillToObjectOK � �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////

class ModifyItemInfo {

public :
	
	// constructor
	ModifyItemInfo () ;
	
	// destructor
	~ModifyItemInfo () noexcept ;
	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () const  { return szDWORD + szDWORD* m_ListNum* 3 ; }

	// get packet's debug string
	string toString () const ;

	// get / set ListNumber
	BYTE getListNum() const  { return m_ListNum; }
	void setListNum(BYTE ListNum)  { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(ObjectID_t ObjectID, ModifyType List, DWORD Value) ; 

	// ClearList
	void clearList()  { m_SList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	DWORD popFrontListElement()  { DWORD StatusList = m_SList.front(); m_SList.pop_front(); return StatusList; }

private :
	
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	list<DWORD> m_SList;

};

#endif
