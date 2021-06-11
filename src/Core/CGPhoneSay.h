//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPhoneSay.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PHONE_SAY_H__
#define __CG_PHONE_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSay;
//
// 클라이언트가 서버에게 보내는 PhoneSay 패킷이다.
// 내부에 PhoneSay String 만을 데이타 필드로 가진다.
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSay : public Packet {

public:
	CGPhoneSay() {};
    ~CGPhoneSay() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_PHONE_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szSlotID + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "CGPhoneSay"; }
	
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
// class CGPhoneSayFactory;
//
// Factory for CGPhoneSay
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSayFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGPhoneSay(); }

	// get packet name
	string getPacketName() const  { return "CGPhoneSay"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_PHONE_SAY; }

	// get packet's max body size
	// message 의 최대 크기에 대한 설정이 필요하다.
	PacketSize_t getPacketMaxSize() const  { return szSlotID + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneSayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPhoneSayHandler {

public:

	// execute packet's handler
	static void execute(CGPhoneSay* pPacket, Player* pPlayer) ;

};

#endif
