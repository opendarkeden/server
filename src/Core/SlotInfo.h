//----------------------------------------------------------------------
//
// Filename    : SlotInfo.h
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SLOT_INFO_H__
#define __SLOT_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include <list>

//----------------------------------------------------------------------
//
// Inventory 정보를 담고 있는 객체.
//
// GCUpdateInfo 패킷에 담겨서 클라이언트에게 전송된다.
// 아이템이나 걸려있는 마법 같은 정보는 담겨있지 않다.
//
//----------------------------------------------------------------------

class SlotInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get size of object
	uint getSize () const throw ()
	{ return 0; }

	// get max size of object
	static uint getMaxSize () throw ()
	{ return 0; }

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

	// get/set OptionType
	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }
	int getOptionTypeSize() const throw()	{ return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}

	// get/set InvenX
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }
	CoordInven_t getInvenX() const throw() { return m_InvenX; }

	// get/set InvenY
	void setInvenY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }
	CoordInven_t getInvenY() const throw() { return m_InvenY; }

	// get/set ItemNum
	void setItemNum (ItemNum_t ItemNum) throw() { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum() const throw() { return m_ItemNum; }

	// get/set MainColor
	void setMainColor(WORD MainColor) throw() { m_MainColor = MainColor; }
	WORD getMainColor() const throw() { return m_MainColor; }

private :

	ObjectID_t m_ObjectID;

	BYTE m_IClass;

	ItemType_t m_ItemType;

	list<OptionType_t> m_OptionType;

	CoordInven_t m_InvenX;

	CoordInven_t m_InvenY;

	ItemNum_t m_ItemNum;

	WORD m_MainColor;

};

#endif
