////////////////////////////////////////////////////////////////////////////////
// Filename    : CGDonationMoney.h 
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_DONATION_MONEY_H__
#define __CG_DONATION_MONEY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// 기부 종류
////////////////////////////////////////////////////////////////////////////////
enum DonationType
{
	DONATION_TYPE_200501_PERSONAL = 0,
	DONATION_TYPE_200501_GUILD,			// 1

	DONATION_TYPE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGDonationMoney
//
////////////////////////////////////////////////////////////////////////////////
class CGDonationMoney : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_DONATION_MONEY; }
	PacketSize_t getPacketSize() const throw() { return szGold + szBYTE; }
	string getPacketName() const throw() { return "CGDonationMoney"; }
	string toString() const throw();
	
public:
	// get / set gold
	Gold_t getGold() const { return m_Gold; }
	void setGold( Gold_t gold ) { m_Gold = gold; }

	// get / set donation Type
	BYTE getDonationType() const { return m_DonationType; }
	void setDonationType( BYTE donationType ) { m_DonationType = donationType; }

private:
	Gold_t		m_Gold;				// 기부 금액
	BYTE		m_DonationType;		// 기부 종류
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDonationMoneyFactory
//
////////////////////////////////////////////////////////////////////////////////

class CGDonationMoneyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGDonationMoney(); }
	string getPacketName() const throw() { return "CGDonationMoney"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_DONATION_MONEY; }
	PacketSize_t getPacketMaxSize() const throw() { return szGold + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDonationMoneyHandler
//
////////////////////////////////////////////////////////////////////////////////
class CGDonationMoneyHandler 
{
public:
	static void execute(CGDonationMoney* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif

