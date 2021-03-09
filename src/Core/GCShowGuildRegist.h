//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildRegist.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_REGIST_H__
#define __GC_SHOW_GUILD_REGIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegist;
//
// 클라이언트에 길드 등록 창을 띄우도록 한다.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegist : public Packet {

public :
	GCShowGuildRegist() {};
    ~GCShowGuildRegist() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_SHOW_GUILD_REGIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szGold; }

	// get packet name
	string getPacketName() const  { return "GCShowGuildRegist"; }
	
	// get packet's debug string
	string toString() const ;

	// get/set Registration Fee
	Gold_t getRegistrationFee() const  { return m_RegistrationFee; }
	void setRegistrationFee(Gold_t registrationFee )  { m_RegistrationFee = registrationFee; }
	

private :
	
	// Registration Fee
	Gold_t m_RegistrationFee;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegistFactory;
//
// Factory for GCShowGuildRegist
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegistFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCShowGuildRegist(); }

	// get packet name
	string getPacketName() const  { return "GCShowGuildRegist"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SHOW_GUILD_REGIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szGold; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegist;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegistHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildRegist* pPacket, Player* pPlayer) ;

};

#endif
