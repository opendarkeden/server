//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDropMoney.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DROP_MONEY_H__
#define __CG_DROP_MONEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGDropMoney;
//
//////////////////////////////////////////////////////////////////////

class CGDropMoney : public Packet {
public:

	// constructor
	CGDropMoney() ;

	// destructor
	~CGDropMoney() ;

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_DROP_MONEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGDropMoneyPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szGold; }

	// get packet name
	string getPacketName() const  { return "CGDropMoney"; }
	
	// get packet's debug string
	string toString() const ;
	
public:
	Gold_t getAmount(void) const  { return m_Amount;}
	void setAmount(Gold_t amount)  { m_Amount = amount;}

private :
	
	Gold_t m_Amount;
};


//////////////////////////////////////////////////////////////////////
//
// class CGDropMoneyFactory;
//
// Factory for CGDropMoney
//
//////////////////////////////////////////////////////////////////////

class CGDropMoneyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGDropMoney(); }

	// get packet name
	string getPacketName() const  { return "CGDropMoney"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_DROP_MONEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGDropMoneyPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szGold; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGDropMoneyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDropMoneyHandler {
	
public:

	// execute packet's handler
	static void execute(CGDropMoney* pPacket, Player* player) ;
};

#endif
