//////////////////////////////////////////////////////////////////////////////
// Filename	: GCSMSAddressList.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SMS_ADDRESS_LIST_H__
#define __GC_SMS_ADDRESS_LIST_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class GCSMSAddressList;
//////////////////////////////////////////////////////////////////////////////

#define MAX_ADDRESS_NUM 30

struct AddressUnit
{
	DWORD	ElementID;
	string	CharacterName;
	string	CustomName;
	string	Number;

	PacketSize_t getPacketSize() const { return szDWORD + szBYTE + CharacterName.size() + szBYTE + CustomName.size() + szBYTE + Number.size(); }
	static PacketSize_t getMaxPacketSize() { return szDWORD + szBYTE + 20 + szBYTE + 40 + szBYTE + 11; }

	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
};

class GCSMSAddressList : public Packet 
{
public:
	GCSMSAddressList() throw();
	~GCSMSAddressList() throw();
	
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SMS_ADDRESS_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCSMSAddressList"; }
	string toString() const throw();

public:
	vector<AddressUnit*>& getAddresses() { return m_Addresses; }

private :
	vector<AddressUnit*>	m_Addresses;
};

//////////////////////////////////////////////////////////////////////////////
// class GCSMSAddressListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCSMSAddressListFactory : public PacketFactory 
{
public :
	GCSMSAddressListFactory() throw() {}
	virtual ~GCSMSAddressListFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCSMSAddressList(); }
	string getPacketName() const throw() { return "GCSMSAddressList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SMS_ADDRESS_LIST; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + AddressUnit::getMaxPacketSize() * MAX_ADDRESS_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCSMSAddressListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCSMSAddressListHandler 
{
public:
	static void execute(GCSMSAddressList* pGCSMSAddressList, Player* pPlayer) throw(Error);

};

#endif
