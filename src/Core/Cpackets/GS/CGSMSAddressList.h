//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSMSAddressList.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SMS_ADDRESS_LIST_H__
#define __CG_SMS_ADDRESS_LIST_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSMSAddressList;
//////////////////////////////////////////////////////////////////////////////

class CGSMSAddressList : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_SMS_ADDRESS_LIST; }
	PacketSize_t getPacketSize() const throw() { return 0; }
	string getPacketName() const throw() { return "CGSMSAddressList"; }
	string toString() const throw();

};

//////////////////////////////////////////////////////////////////////
// class CGSMSAddressListFactory;
//////////////////////////////////////////////////////////////////////

class CGSMSAddressListFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGSMSAddressList(); }
	string getPacketName() const throw() { return "CGSMSAddressList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SMS_ADDRESS_LIST; }
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
};


//////////////////////////////////////////////////////////////////////
// class CGSMSAddressListHandler;
//////////////////////////////////////////////////////////////////////

class CGSMSAddressListHandler 
{
public:
	static void execute(CGSMSAddressList* pCGSMSAddressList, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
