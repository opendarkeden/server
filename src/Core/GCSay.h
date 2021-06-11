//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSay.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SAY_H__
#define __GC_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCSay;
//
// 게임 서버가 특정 플레이어의 Say 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 Say 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCSay : public Packet {

public :
	GCSay() {};
    ~GCSay() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szObjectID + szuint + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "GCSay"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set sender's creature id
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID)  { m_ObjectID = creatureID; }

	//get/set text color
	uint getColor() const  { return m_Color; }
	void setColor(uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	

private :
	
	// character's creature id
	ObjectID_t m_ObjectID;

	// text color
	uint m_Color;
	
	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCSayFactory;
//
// Factory for GCSay
//
//////////////////////////////////////////////////////////////////////

class GCSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCSay(); }

	// get packet name
	string getPacketName() const  { return "GCSay"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSayPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szuint + szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSayHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSay* pPacket, Player* pPlayer) ;

};

#endif
