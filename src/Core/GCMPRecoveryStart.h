//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMPRecoveryStart.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MP_RECOVERY_START_H__
#define __GC_MP_RECOVERY_START_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryStart;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryStart : public Packet {

public :
	
	// constructor
	GCMPRecoveryStart() ;
	
	// destructor
	~GCMPRecoveryStart() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_MP_RECOVERY_START; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szBYTE + szMP + szMP; }

	// get packet's name
	string getPacketName() const  { return "GCMPRecoveryStart"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set Delay
	BYTE getDelay() const  { return m_Delay; }
	void setDelay(BYTE Delay)  { m_Delay = Delay; }

	// get / set Period
	MP_t getPeriod() const  { return m_Period; }
	void setPeriod(MP_t Period)  { m_Period = Period; }

	// get / set Quantity
	MP_t getQuantity() const  { return m_Quantity; }
	void setQuantity(MP_t Quantity)  { m_Quantity = Quantity; }

private :
	
	// 한 턴
	BYTE m_Delay;

	// 몇번
	MP_t m_Period;

	// 얼마나
	MP_t m_Quantity;


};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryStartFactory;
//
// Factory for GCMPRecoveryStart
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryStartFactory : public PacketFactory {

public :
	
	// constructor
	GCMPRecoveryStartFactory()  {}
	
	// destructor
	virtual ~GCMPRecoveryStartFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCMPRecoveryStart(); }

	// get packet name
	string getPacketName() const  { return "GCMPRecoveryStart"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MP_RECOVERY_START; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szMP + szMP; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryStartHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryStartHandler {

public :

	// execute packet's handler
	static void execute(GCMPRecoveryStart* pGCMPRecoveryStart, Player* pPlayer) ;

};

#endif
