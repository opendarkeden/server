////////////////////////////////////////////////////////////////////////////////
// Filename    : CGMouseToStash.h 
// Written By  : ±è¼º¹Î
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_MOUSE_TO_STASH_H__
#define __CG_MOUSE_TO_STASH_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGMouseToStash
//
////////////////////////////////////////////////////////////////////////////////

class CGMouseToStash : public Packet 
{
public:
    void         read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void         write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void         execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t   getPacketID() const throw() { return PACKET_CG_MOUSE_TO_STASH; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE*2; }
	string       getPacketName() const throw() { return "CGMouseToStash"; }
	string       toString() const throw();
	
public:
	ObjectID_t getObjectID(void) throw() { return m_ObjectID; }
	void       setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }
	BYTE       getRack(void) throw() { return m_Rack;}
	void       setRack(BYTE rack) throw() { m_Rack = rack;}
	BYTE       getIndex(void) throw() { return m_Index;}
	void       setIndex(BYTE index) throw() { m_Index = index;}

private:
	ObjectID_t m_ObjectID;
	BYTE       m_Rack;
	BYTE       m_Index;

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGMouseToStashFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGMouseToStashFactory : public PacketFactory 
{
public:
	Packet*      createPacket() throw() { return new CGMouseToStash(); }
	string       getPacketName() const throw() { return "CGMouseToStash"; }
	PacketID_t   getPacketID() const throw() { return Packet::PACKET_CG_MOUSE_TO_STASH; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID+szBYTE*2; }

};

////////////////////////////////////////////////////////////////////////////////
//
// class CGMouseToStashHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGMouseToStashHandler 
{
public:
	static void execute(CGMouseToStash* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeSlayer(CGMouseToStash* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeVampire(CGMouseToStash* pPacket, Player* player) throw(ProtocolException, Error);
};


#endif
