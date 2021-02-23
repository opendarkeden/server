////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGWithdrawPet.h 
// Written By  : ±è¼º¹Î 
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_WITHDRAW_PET_H__
#define __CG_WITHDRAW_PET_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGWithdrawPet;
//
////////////////////////////////////////////////////////////////////////////////

class CGWithdrawPet : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_WITHDRAW_PET; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }
	string getPacketName() const throw() { return "CGWithdrawPet"; }
	string toString() const throw();
	
public:
	ObjectID_t	getObjectID() const { return m_ObjectID; }
	void		setObjectID( ObjectID_t objectID ) { m_ObjectID = objectID; }

	BYTE		getIndex(void) const { return m_Index;}
	void		setIndex(BYTE index) { m_Index = index;}

private:
	ObjectID_t	m_ObjectID;
	BYTE		m_Index;

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGWithdrawPetFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGWithdrawPetFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGWithdrawPet(); }
	string getPacketName() const throw() { return "CGWithdrawPet"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_WITHDRAW_PET; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGWithdrawPetHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGWithdrawPetHandler {
	
public:

	// execute packet's handler
	static void execute(CGWithdrawPet* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeSlayer(CGWithdrawPet* pPacket, Player* player) throw(ProtocolException, Error);
	//static void executeVampire(CGWithdrawPet* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
