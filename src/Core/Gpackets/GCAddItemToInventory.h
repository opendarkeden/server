//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToInventory.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_ITEM_TO_INVENTORY_H__
#define __GC_ADD_ITEM_TO_INVENTORY_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToInventory;
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToInventory 
{
public:
	GCAddItemToInventory() throw();
	~GCAddItemToInventory() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord + szCoord + szBYTE + szItemType + szBYTE + m_OptionType.size() + szDurability; }
	string getPacketName() const throw() { return "GCAddItemToInventory"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ID) throw() { m_ObjectID = ID; }

	CoordInven_t getX() const throw() { return m_X; }
	void setX(CoordInven_t x) throw() { m_X = x; }
	
	CoordInven_t getY() const throw() { return m_Y; }
	void setY(CoordInven_t y) throw() { m_Y = y; }

	BYTE getItemClass() const throw() { return m_ItemClass; }
	void setItemClass(BYTE Class) throw() { m_ItemClass = Class; }

	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }

	int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionTypes) throw() { m_OptionType = OptionTypes; }

	Durability_t getDurability() const throw() { return m_Durability; }
	void setDurability(Durability_t Durability) throw() { m_Durability = Durability; }

	ItemNum_t getItemNum() const throw() { return m_ItemNum; }
	void setItemNum(ItemNum_t ItemNum) throw() { m_ItemNum = ItemNum; }

protected:
    ObjectID_t    		m_ObjectID;     // item object id
   	CoordInven_t  		m_X;            // inventory x coord
	CoordInven_t  		m_Y;            // inventory y coord
	BYTE          		m_ItemClass;    // item Class
	ItemType_t    		m_ItemType;     // item type
	list<OptionType_t>  m_OptionType;   // item option type
	Durability_t  		m_Durability;   // item durability
	ItemNum_t     		m_ItemNum;      // number of item
};

#endif
