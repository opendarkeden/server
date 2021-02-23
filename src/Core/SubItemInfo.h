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
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get size of object
	static uint getSize () throw ()
	{ return szObjectID + szBYTE + szItemType + szItemNum + szSlotID; }

	// get max size of object
	static uint getMaxSize () throw ()
	{ return szObjectID + szBYTE + szItemType + szItemNum + szSlotID; }

	// get debug string
	string toString () const throw ();

public :

	// get/set ObjectID
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }

	// get/set ItemClass
	void setItemClass (BYTE IClass) throw() { m_IClass = IClass; }
	BYTE getItemClass () const throw() { return m_IClass; }

	// get/set ItemType
	void setItemType (ItemType_t ItemType) throw() { m_ItemType = ItemType; }
	ItemType_t getItemType() const throw() { return m_ItemType; }

	// get/set ItemNum
	void setItemNum (ItemNum_t ItemNum) throw() { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum() const throw() { return m_ItemNum; }

	// set/set SlotID
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }
	SlotID_t getSlotID() const throw() { return m_SlotID; }

private :

	ObjectID_t m_ObjectID; 

	BYTE m_IClass;

	ItemType_t m_ItemType;

	ItemNum_t m_ItemNum;

	SlotID_t m_SlotID;

};

#endif
