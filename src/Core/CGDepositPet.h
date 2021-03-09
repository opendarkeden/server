////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDepositPet.h 
// Written By  : ±è¼º¹Î 
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_DEPOSIT_PET_H__
#define __CG_DEPOSIT_PET_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGDepositPet;
//
////////////////////////////////////////////////////////////////////////////////

class CGDepositPet : public Packet 
{
public:
    CGDepositPet() {};
    ~CGDepositPet() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_DEPOSIT_PET; }
	PacketSize_t getPacketSize() const  { return szObjectID + szBYTE; }
	string getPacketName() const  { return "CGDepositPet"; }
	string toString() const ;
	
public:
	ObjectID_t	getObjectID() const { return m_ObjectID; }
	void		setObjectID(ObjectID_t objectID ) { m_ObjectID = objectID; }

	BYTE		getIndex(void) const { return m_Index;}
	void		setIndex(BYTE index) { m_Index = index;}

private:
	ObjectID_t	m_ObjectID;
	BYTE		m_Index;

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDepositPetFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGDepositPetFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGDepositPet(); }
	string getPacketName() const  { return "CGDepositPet"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_DEPOSIT_PET; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDepositPetHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGDepositPetHandler {
	
public:

	// execute packet's handler
	static void execute(CGDepositPet* pPacket, Player* player) ;
	//static void executeSlayer(CGDepositPet* pPacket, Player* player) ;
	//static void executeVampire(CGDepositPet* pPacket, Player* player) ;
};

#endif
