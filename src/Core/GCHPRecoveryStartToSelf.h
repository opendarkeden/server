//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryStartToSelf.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HP_RECOVERY_START_TO_SELF_H__
#define __GC_HP_RECOVERY_START_TO_SELF_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryStartToSelf;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryStartToSelf : public Packet {

public :
	
	// constructor
	GCHPRecoveryStartToSelf() throw();
	
	// destructor
	~GCHPRecoveryStartToSelf() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_HP_RECOVERY_START_TO_SELF; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const throw() { return szBYTE + szHP + szHP; }

	// get packet's name
	string getPacketName() const throw() { return "GCHPRecoveryStartToSelf"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set Delay
	BYTE getDelay() const throw() { return m_Delay; }
	void setDelay(BYTE Delay) throw() { m_Delay = Delay; }

	// get / set Period
	HP_t getPeriod() const throw() { return m_Period; }
	void setPeriod(HP_t Period) throw() { m_Period = Period; }

	// get / set Quantity
	HP_t getQuantity() const throw() { return m_Quantity; }
	void setQuantity(HP_t Quantity) throw() { m_Quantity = Quantity; }

private :
	
	// 한 턴
	BYTE m_Delay;

	// 몇번
	HP_t m_Period;

	// 얼마나
	HP_t m_Quantity;


};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryStartToSelfFactory;
//
// Factory for GCHPRecoveryStartToSelf
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryStartToSelfFactory : public PacketFactory {

public :
	
	// constructor
	GCHPRecoveryStartToSelfFactory() throw() {}
	
	// destructor
	virtual ~GCHPRecoveryStartToSelfFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCHPRecoveryStartToSelf(); }

	// get packet name
	string getPacketName() const throw() { return "GCHPRecoveryStartToSelf"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_HP_RECOVERY_START_TO_SELF; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szHP + szHP; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryStartToSelfHandler;
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryStartToSelfHandler {

public :

	// execute packet's handler
	static void execute(GCHPRecoveryStartToSelf* pGCHPRecoveryStartToSelf, Player* pPlayer) throw(Error);

};

#endif
