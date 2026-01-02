//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetStashVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PET_STASH_VERIFY_H__
#define __GC_PET_STASH_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

enum
{
	PET_STASH_OK,
	PET_STASH_NOT_ENOUGH_MONEY,
	PET_STASH_NO_INVENTORY_SPACE,
		PET_STASH_RACK_IS_NOT_EMPTY,	// Target slot already holds another pet.
		PET_STASH_RACK_IS_EMPTY,		// Requested slot is empty.
		PET_STASH_INVALID_OID,			// Invalid ObjectID.
		PET_STASH_INVALID_INDEX,		// Invalid index.
};

//////////////////////////////////////////////////////////////////////////////
// class GCPetStashVerify
//////////////////////////////////////////////////////////////////////////////

class GCPetStashVerify : public Packet 
{
public:
	GCPetStashVerify()  { m_Code = PET_STASH_OK; }
	virtual ~GCPetStashVerify()  {}

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;

	PacketID_t getPacketID() const  { return PACKET_GC_PET_STASH_VERIFY; }
	PacketSize_t getPacketSize() const  { return szBYTE; }
	string getPacketName() const  { return "GCPetStashVerify"; }
	string toString() const ;
	
public:
	BYTE getCode(void) const  { return m_Code;}
	void setCode(BYTE code)  { m_Code = code;}

private: 
	BYTE m_Code;
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetStashVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPetStashVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCPetStashVerify(); }
	string getPacketName() const  { return "GCPetStashVerify"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_PET_STASH_VERIFY; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetStashVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCPetStashVerifyHandler 
{
public:
	static void execute(GCPetStashVerify* pPacket, Player* pPlayer) ;
};

#endif
