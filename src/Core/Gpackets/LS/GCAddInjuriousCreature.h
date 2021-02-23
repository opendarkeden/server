//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddInjuriousCreature.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_INJURIOUS_CREATURE_H__
#define __GC_ADD_INJURIOUS_CREATURE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreature;
//
// 클라이언트가 서버에게 보내는 AddInjuriousCreature 패킷이다.
// 내부에 AddInjuriousCreature String 만을 데이타 필드로 가진다.
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreature : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_INJURIOUS_CREATURE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Name.size(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddInjuriousCreature"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set Name
	string getName() const throw() { return m_Name; }
	void setName(const string & Name) throw() { m_Name = Name; }

private :

	string m_Name;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreatureFactory;
//
// Factory for GCAddInjuriousCreature
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreatureFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new GCAddInjuriousCreature(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddInjuriousCreature"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_INJURIOUS_CREATURE; }

	// get packet's max body size
	// message 의 최대 크기에 대한 설정이 필요하다.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 10; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddInjuriousCreatureHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddInjuriousCreatureHandler {

public:

	// execute packet's handler
	static void execute(GCAddInjuriousCreature* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
