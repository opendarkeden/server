//----------------------------------------------------------------------
//
// Filename    : SubItemInfo.h
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_ITEM_INFO_H__
#define __SUB_ITEM_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
// Inventory 정보를 담고 있는 객체.
//
// GCUpdateInfo 패킷에 담겨서 클라이언트에게 전송된다.
// 아이템이나 걸려있는 마법 같은 정보는 담겨있지 않다.
//
//----------------------------------------------------------------------

class SubItemInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream) ;

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const ;

	// get size of object
	static uint getSize () 
	{ return szObjectID + szBYTE + szItemType + szItemNum + szSlotID; }

	// get max size of object
	static uint getMaxSize () 
	{ return szObjectID + szBYTE + szItemType + szItemNum + szSlotID; }

	// get debug string
	string toString () const ;

public :

	// get/set ObjectID
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	ObjectID_t getObjectID() const  { return m_ObjectID; }

	// get/set ItemClass
	void setItemClass (BYTE IClass)  { m_IClass = IClass; }
	BYTE getItemClass () const  { return m_IClass; }

	// get/set ItemType
	void setItemType (ItemType_t ItemType)  { m_ItemType = ItemType; }
	ItemType_t getItemType() const  { return m_ItemType; }

	// get/set ItemNum
	void setItemNum (ItemNum_t ItemNum)  { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum() const  { return m_ItemNum; }

	// set/set SlotID
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }
	SlotID_t getSlotID() const  { return m_SlotID; }

private :

	ObjectID_t m_ObjectID; 

	BYTE m_IClass;

	ItemType_t m_ItemType;

	ItemNum_t m_ItemNum;

	SlotID_t m_SlotID;

};

#endif
