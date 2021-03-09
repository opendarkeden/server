//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddGearToMouse.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_GEAR_TO_MOUSE_H__
#define __CG_ADD_GEAR_TO_MOUSE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddGearToMouse;
//////////////////////////////////////////////////////////////////////////////

class CGAddGearToMouse : public Packet 
{
public:
	CGAddGearToMouse() ;
	~CGAddGearToMouse() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_ADD_GEAR_TO_MOUSE; }
	PacketSize_t getPacketSize() const  { return szObjectID + szSlotID; }
	string getPacketName() const  { return "CGAddGearToMouse"; }
	string toString() const ;
	
public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	SlotID_t getSlotID() const  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID ; }

private:
	ObjectID_t m_ObjectID;
	SlotID_t m_SlotID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddGearToMouseFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddGearToMouseFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGAddGearToMouse(); }
	string getPacketName() const  { return "CGAddGearToMouse"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_ADD_GEAR_TO_MOUSE; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szSlotID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddGearToMouseHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddGearToMouseHandler 
{
public:
	static void execute(CGAddGearToMouse* pPacket, Player* player) ;
};

#endif
