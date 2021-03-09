//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneSay.h 
// Written By  : elca 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_SAY_H__
#define __GC_PHONE_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSay;
//
// 게임 서버가 특정 플레이어의 PhoneSay 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 PhoneSay 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSay : public Packet {

public :
	GCPhoneSay() {};
    ~GCPhoneSay() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_PHONE_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szSlotID + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "GCPhoneSay"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set SlotID
	SlotID_t getSlotID() const  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	

private :

	// SlotID
	SlotID_t m_SlotID;
	
	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSayFactory;
//
// Factory for GCPhoneSay
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCPhoneSay(); }

	// get packet name
	string getPacketName() const  { return "GCPhoneSay"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_PHONE_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPhoneSayPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szSlotID + szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSayHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCPhoneSay* pPacket, Player* pPlayer) ;

};

#endif
