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
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_STASH_WITHDRAW; }
	PacketSize_t getPacketSize() const throw() { return szGold; }
	string getPacketName() const throw() { return "CGStashWithdraw"; }
	string toString() const throw();
	
public:
	Gold_t getAmount(void) const throw() { return m_Amount;}
	void setAmount(Gold_t amount) throw() { m_Amount = amount;}

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
	Packet* createPacket() throw() { return new CGStashWithdraw(); }
	string getPacketName() const throw() { return "CGStashWithdraw"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_STASH_WITHDRAW; }
	PacketSize_t getPacketMaxSize() const throw() { return szGold; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdrawHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashWithdrawHandler {
	
public:

	// execute packet's handler
	static void execute(CGStashWithdraw* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
