//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestNewbieItem.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_NEWBIE_ITEM_H__
#define __CG_REQUEST_NEWBIE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItem;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItem : public Packet 
{
public:
    CGRequestNewbieItem() {};
    virtual ~CGRequestNewbieItem() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_REQUEST_NEWBIE_ITEM; }
	PacketSize_t getPacketSize() const  { return szBYTE; }
	string getPacketName() const  { return "CGRequestNewbieItem"; }
	string toString() const ;
	
public:
	BYTE getItemClass(void) const  { return m_ItemClass; }
	void setItemClass(BYTE itemClass)  { m_ItemClass = itemClass; }

private:
	BYTE m_ItemClass;
};


//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGRequestNewbieItem(); }
	string getPacketName() const  { return "CGRequestNewbieItem"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_REQUEST_NEWBIE_ITEM; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItemHandler 
{
public:
	static void execute(CGRequestNewbieItem* pPacket, Player* player) ;
};

#endif
