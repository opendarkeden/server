//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddressListVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADDRESS_LIST_VERIFY_H__
#define __GC_ADDRESS_LIST_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddressListVerify
//////////////////////////////////////////////////////////////////////////////

class GCAddressListVerify : public Packet 
{
public:
	enum VerifyCodes
	{
		ADDRESS_LIST_ADD_OK = 0,
		ADDRESS_LIST_DELETE_OK,
		ADDRESS_LIST_ADD_FAIL,
		ADDRESS_LIST_DELETE_FAIL,

		SMS_SEND_OK,
		SMS_SEND_FAIL,

		SMS_CHARGE_OK,

		ADDRESS_LIST_VERIFY_MAX
	};

	enum ErrorParameters
	{
		ADD_FAIL_MAX_NUM_EXCEEDED = 1,
		ADD_FAIL_INVALID_DATA,
		DELETE_FAIL_NO_SUCH_EID,

		SMS_SEND_FAIL_NOT_ENOUGH_CHARGE,
	};

	GCAddressListVerify()  { m_Code = ADDRESS_LIST_VERIFY_MAX; m_Parameter = 0;}
	virtual ~GCAddressListVerify()  {}

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;

	PacketID_t getPacketID() const  { return PACKET_GC_ADDRESS_LIST_VERIFY; }
	PacketSize_t getPacketSize() const  { return szBYTE + szDWORD; }
	string getPacketName() const  { return "GCAddressListVerify"; }
	string toString() const ;
	
public:
	BYTE getCode(void) const  { return m_Code;}
	void setCode(BYTE code)  { m_Code = code;}

	DWORD getParameter(void) const  { return m_Parameter; }
	void setParameter(uint parameter)  { m_Parameter = parameter; }

private: 
	BYTE m_Code;
	DWORD m_Parameter;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddressListVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddressListVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddressListVerify(); }
	string getPacketName() const  { return "GCAddressListVerify"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADDRESS_LIST_VERIFY; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szDWORD; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddressListVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCAddressListVerifyHandler 
{
public:
	static void execute(GCAddressListVerify* pPacket, Player* pPlayer) ;
};

#endif
