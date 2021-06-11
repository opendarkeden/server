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
	CGAddMouseToQuickSlot() ;
	~CGAddMouseToQuickSlot() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_ADD_MOUSE_TO_QUICKSLOT; }
	PacketSize_t getPacketSize() const  { return szObjectID + szSlotID; }
	string getPacketName() const  { return "CGAddMouseToQuickSlot"; }
	string toString() const ;
	
public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	SlotID_t getSlotID() const  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }

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
	Packet* createPacket()  { return new CGAddMouseToQuickSlot(); }
	string getPacketName() const  { return "CGAddMouseToQuickSlot"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_ADD_MOUSE_TO_QUICKSLOT; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddMouseToQuickSlotHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddMouseToQuickSlotHandler 
{
public:
	static void execute(CGAddMouseToQuickSlot* pPacket, Player* player) ;
};

#endif
