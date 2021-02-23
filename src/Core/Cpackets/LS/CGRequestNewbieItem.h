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
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_REQUEST_NEWBIE_ITEM; }
	PacketSize_t getPacketSize() const throw() { return szBYTE; }
	string getPacketName() const throw() { return "CGRequestNewbieItem"; }
	string toString() const throw();
	
public:
	BYTE getItemClass(void) const throw() { return m_ItemClass; }
	void setItemClass(BYTE itemClass) throw() { m_ItemClass = itemClass; }

private:
	BYTE m_ItemClass;
};


//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGRequestNewbieItem(); }
	string getPacketName() const throw() { return "CGRequestNewbieItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_REQUEST_NEWBIE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGRequestNewbieItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGRequestNewbieItemHandler 
{
public:
	static void execute(CGRequestNewbieItem* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
