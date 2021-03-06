//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGWithdrawTax.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_WITHDRAW_TAX_H__
#define __CG_WITHDRAW_TAX_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGWithdrawTax;
//
//////////////////////////////////////////////////////////////////////

class CGWithdrawTax : public Packet
{
public:
	CGWithdrawTax() {};
    virtual ~CGWithdrawTax() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_WITHDRAW_TAX; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szGold; }

	// get packet name
	string getPacketName() const  { return "CGWithdrawTax"; }

	// get packet's debug string
	string toString() const ;

	// get/set Gold
	Gold_t getGold() const { return m_Gold; }
	void setGold(Gold_t gold ) { m_Gold = gold; }


private :

	Gold_t m_Gold;
};


//////////////////////////////////////////////////////////////////////
//
// class CGWithdrawTaxFactory;
//
// Factory for CGWithdrawTax
//
//////////////////////////////////////////////////////////////////////

class CGWithdrawTaxFactory : public PacketFactory {

public:
	
	// constructor
	CGWithdrawTaxFactory()  {}
	
	// destructor
	virtual ~CGWithdrawTaxFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGWithdrawTax(); }

	// get packet name
	string getPacketName() const  { return "CGWithdrawTax"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_WITHDRAW_TAX; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szGold; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGWithdrawTaxHandler;
//
//////////////////////////////////////////////////////////////////////

class CGWithdrawTaxHandler {

public:

	// execute packet's handler
	static void execute(CGWithdrawTax* pCGWithdrawTax, Player* pPlayer) ;

};

#endif
