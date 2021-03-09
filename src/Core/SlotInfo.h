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
	void read (SocketInputStream & iStream) ;

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const ;

	// get size of object
	uint getSize () const 
	{ return 0; }

	// get max size of object
	static uint getMaxSize () 
	{ return 0; }

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

	// get/set OptionType
	void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionType)  { m_OptionType = OptionType; }
	int getOptionTypeSize() const 	{ return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const  { return m_OptionType; }
	OptionType_t popOptionType() 
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}

	// get/set InvenX
	void setInvenX(CoordInven_t InvenX)  { m_InvenX = InvenX; }
	CoordInven_t getInvenX() const  { return m_InvenX; }

	// get/set InvenY
	void setInvenY(CoordInven_t InvenY)  { m_InvenY = InvenY; }
	CoordInven_t getInvenY() const  { return m_InvenY; }

	// get/set ItemNum
	void setItemNum (ItemNum_t ItemNum)  { m_ItemNum = ItemNum; }
	ItemNum_t getItemNum() const  { return m_ItemNum; }

	// get/set MainColor
	void setMainColor(WORD MainColor)  { m_MainColor = MainColor; }
	WORD getMainColor() const  { return m_MainColor; }

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
