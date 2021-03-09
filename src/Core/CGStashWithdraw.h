////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashWithdraw.h 
// Written By  : ±è¼º¹Î
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_WITHDRAW_H__
#define __CG_STASH_WITHDRAW_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdraw;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashWithdraw : public Packet 
{
public:
    CGStashWithdraw() {};
    virtual ~CGStashWithdraw() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_STASH_WITHDRAW; }
	PacketSize_t getPacketSize() const  { return szGold; }
	string getPacketName() const  { return "CGStashWithdraw"; }
	string toString() const ;
	
public:
	Gold_t getAmount(void) const  { return m_Amount;}
	void setAmount(Gold_t amount)  { m_Amount = amount;}

private :
	Gold_t m_Amount;
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdrawFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashWithdrawFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGStashWithdraw(); }
	string getPacketName() const  { return "CGStashWithdraw"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_STASH_WITHDRAW; }
	PacketSize_t getPacketMaxSize() const  { return szGold; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdrawHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashWithdrawHandler {
	
public:

	// execute packet's handler
	static void execute(CGStashWithdraw* pPacket, Player* player) ;
};

#endif
