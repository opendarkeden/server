//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWhisper.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_WHISPER_H__
#define __GC_WHISPER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCWhisper;
//
// 게임 서버가 특정 플레이어의 Whisper 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 Whisper 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCWhisper : public Packet {

public :
	GCWhisper() {};
    ~GCWhisper() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_WHISPER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szBYTE + m_Name.size() + szuint + szBYTE + m_Message.size() + szBYTE; }

	// get packet name
	string getPacketName() const  { return "GCWhisper"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set sender's creature id
	string getName() const  { return m_Name ; }
	void setName(const string & Name)  { m_Name = Name ; }

	//get/set text color
	uint getColor() const  { return m_Color; }
	void setColor(uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage() const  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	
	// get/set chatting message
	Race_t getRace() const  { return m_Race; }
	void setRace(Race_t race)  { m_Race = race; }

private :
	
	// character's creature Name
	string m_Name;
	
	// text color
	uint m_Color;

	// chatting message
	string m_Message;

	// Race
	Race_t m_Race;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFactory;
//
// Factory for GCWhisper
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCWhisper(); }

	// get packet name
	string getPacketName() const  { return "GCWhisper"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_WHISPER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCWhisperPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szBYTE + 10 + szuint + szBYTE + 128 + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperHandler;
//
//////////////////////////////////////////////////////////////////////

class GCWhisperHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCWhisper* pPacket, Player* pPlayer) ;

};

#endif
