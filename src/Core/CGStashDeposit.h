////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashDeposit.h 
// Written By  : ±è¼º¹Î
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_DEPOSIT_H__
#define __CG_STASH_DEPOSIT_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashDeposit;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashDeposit : public Packet 
{
public:
    CGStashDeposit() {};
    virtual ~CGStashDeposit() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_STASH_DEPOSIT; }
	PacketSize_t getPacketSize() const  { return szGold; }
	string getPacketName() const  { return "CGStashDeposit"; }
	string toString() const ;
	
public:
	Gold_t getAmount(void) const  { return m_Amount;}
	void setAmount(Gold_t amount)  { m_Amount = amount;}

private :
	Gold_t m_Amount;
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashDepositFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashDepositFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGStashDeposit(); }
	string getPacketName() const  { return "CGStashDeposit"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_STASH_DEPOSIT; }
	PacketSize_t getPacketMaxSize() const  { return szGold; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashDepositHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashDepositHandler {
	
public:

	// execute packet's handler
	static void execute(CGStashDeposit* pPacket, Player* player) ;
};

#endif
