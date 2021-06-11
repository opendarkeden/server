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

	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
};

class GCSMSAddressList : public Packet 
{
public:
	GCSMSAddressList() ;
	~GCSMSAddressList() ;
	
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SMS_ADDRESS_LIST; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCSMSAddressList"; }
	string toString() const ;

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
	GCSMSAddressListFactory()  {}
	virtual ~GCSMSAddressListFactory()  {}
	
public:
	Packet* createPacket()  { return new GCSMSAddressList(); }
	string getPacketName() const  { return "GCSMSAddressList"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SMS_ADDRESS_LIST; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + AddressUnit::getMaxPacketSize() * MAX_ADDRESS_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCSMSAddressListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCSMSAddressListHandler 
{
public:
	static void execute(GCSMSAddressList* pGCSMSAddressList, Player* pPlayer) ;

};

#endif
