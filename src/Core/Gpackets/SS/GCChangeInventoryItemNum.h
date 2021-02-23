//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeInventoryItemNum.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CHANGE_INVENTORY_ITEM_NUM_H__
#define __GC_CHANGE_INVENTORY_ITEM_NUM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCChangeInventoryItemNum;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCChangeInventoryItemNum {

public :
	
	// constructor
	GCChangeInventoryItemNum() throw();
	
	// destructor
	~GCChangeInventoryItemNum() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	PacketSize_t getPacketSize() const throw() { return szBYTE + szObjectID* m_ChangedItemListNum + szItemNum*m_ChangedItemListNum;} 

	// get packet's debug string
	string toString() const throw();

	// get / set ListNumber
	BYTE getChangedItemListNum() const throw() { return m_ChangedItemListNum; }
	void setChangedItemListNum(BYTE ListNum) throw() { m_ChangedItemListNum = ListNum; }

	// add / delete / clear S List
	void addChangedItemListElement(ObjectID_t objectID, BYTE itemNum) throw(); 

	// ClearList
	void clearChangedItemList() throw() { m_ChangedItemList.clear(); m_ChangedItemNumList.clear(); m_ChangedItemListNum = 0; }

	// pop front Element in Object List
	ObjectID_t popFrontChangedItemListElement() throw() { ObjectID_t item = m_ChangedItemList.front(); m_ChangedItemList.pop_front(); return item; }
	ItemNum_t popFrontChangedItemNumListElement() throw() { ItemNum_t itemNum = m_ChangedItemNumList.front(); m_ChangedItemNumList.pop_front(); return itemNum; }

protected:
	
	// List Element Number
	BYTE m_ChangedItemListNum;

	// 수량등이 변경된 Inventory내의 Item List
	list<ObjectID_t> m_ChangedItemList;		// 변경될 Item object id
	list<ItemNum_t> m_ChangedItemNumList;	// 변경될 Item object id의 변경 수량.


};

#endif
