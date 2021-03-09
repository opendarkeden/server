////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStashSell.h 
// Written By  : ±è¼º¹Î
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_STASH_SELL_H__
#define __GC_STASH_SELL_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class GCStashSell;
//
////////////////////////////////////////////////////////////////////////////////

class GCStashSell : public Packet 
{
public:
    GCStashSell() {};
    ~GCStashSell() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_STASH_SELL; }
	PacketSize_t getPacketSize() const  { return szGold; }
	string getPacketName() const  { return "GCStashSell"; }
	string toString() const ;

public:
	Gold_t getPrice(void) const  { return m_Price; }
	void  setPrice(Gold_t price)  { m_Price = price; }

private:
	Gold_t m_Price;

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCStashSellFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCStashSellFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCStashSell(); }
	string getPacketName() const  { return "GCStashSell"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_STASH_SELL; }
	PacketSize_t getPacketMaxSize() const  { return szGold; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class GCStashSellHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCStashSellHandler 
{
public:
	static void execute(GCStashSell* pPacket, Player* pPlayer) ;

};

#endif
