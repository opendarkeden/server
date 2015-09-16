//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddQuickSlotToMouse.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_QUICKSLOT_TO_MOUSE_H__
#define __CG_ADD_QUICKSLOT_TO_MOUSE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddQuickSlotToMouse;
//////////////////////////////////////////////////////////////////////////////

class CGAddQuickSlotToMouse : public Packet 
{
public:
	CGAddQuickSlotToMouse() throw();
	~CGAddQuickSlotToMouse() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_QUICKSLOT_TO_MOUSE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szSlotID; }
	string getPacketName() const throw() { return "CGAddQuickSlotToMouse"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SlotID_t getSlotID() throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private:
	ObjectID_t m_ObjectID;
	SlotID_t m_SlotID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddQuickSlotToMouseFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddQuickSlotToMouseFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddQuickSlotToMouse(); }
	string getPacketName() const throw() { return "CGAddQuickSlotToMouse"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_QUICKSLOT_TO_MOUSE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddQuickSlotToMouseHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddQuickSlotToMouseHandler 
{
public:
	static void execute(CGAddQuickSlotToMouse* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
