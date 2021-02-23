//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToQuickSlot.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_MOUSE_TO_QUICKSLOT_H__
#define __CG_ADD_MOUSE_TO_QUICKSLOT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlot;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlot : public Packet 
{
public:
	CGAddMouseToQuickSlot() throw();
	~CGAddMouseToQuickSlot() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_ADD_MOUSE_TO_QUICKSLOT; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szSlotID; }
	string getPacketName() const throw() { return "CGAddMouseToQuickSlot"; }
	string toString() const throw();
	
public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private:
	ObjectID_t m_ObjectID;
	SlotID_t m_SlotID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlotFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlotFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAddMouseToQuickSlot(); }
	string getPacketName() const throw() { return "CGAddMouseToQuickSlot"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_ADD_MOUSE_TO_QUICKSLOT; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlotHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlotHandler 
{
public:
	static void execute(CGAddMouseToQuickSlot* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
