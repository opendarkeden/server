//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddSMSAddress.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_SMS_ADDRESS_H__
#define __CG_ADD_SMS_ADDRESS_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAddSMSAddress;
//////////////////////////////////////////////////////////////////////////////

class CGAddSMSAddress : public Packet 
{
public:
	CGAddSMSAddress() ;
	~CGAddSMSAddress() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_ADD_SMS_ADDRESS; }
	PacketSize_t getPacketSize() const  { return szBYTE + m_CharacterName.size() + szBYTE + m_CustomName.size() + szBYTE + m_Number.size(); }
	string getPacketName() const  { return "CGAddSMSAddress"; }
	string toString() const ;
	
public:
	const string&	getCharacterName() const { return m_CharacterName; }
	void			setCharacterName(const string& name ) { m_CharacterName = name; }

	const string&	getCustomName() const { return m_CustomName; }
	void			setCustomName(const string& name ) { m_CustomName = name; }

	const string&	getNumber() const { return m_Number; }
	void			setNumber(const string& num ) { m_Number = num; }

private:
	string	m_CharacterName;
	string	m_CustomName;
	string	m_Number;
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddSMSAddressFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddSMSAddressFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGAddSMSAddress(); }
	string getPacketName() const  { return "CGAddSMSAddress"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_ADD_SMS_ADDRESS; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + 20 + szBYTE + 40 + szBYTE + 11; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddSMSAddressHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddSMSAddressHandler 
{
public:
	static void execute(CGAddSMSAddress* pPacket, Player* player) ;
};

#endif
