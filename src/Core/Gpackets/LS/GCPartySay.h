//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPartySay.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_SAY_H__
#define __GC_PARTY_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPartySay;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(ObjectID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCPartySay : public Packet
{
public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_PARTY_SAY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCPartySayPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Name.size() + szDWORD + szBYTE + m_Message.size(); }

	// get packet's name
	string getPacketName() const throw() { return "GCPartySay"; }
	
	// get packet's debug string
	string toString() const throw();


public :
	string	getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	DWORD	getColor() const { return m_Color; }
	void	setColor(DWORD color) { m_Color = color; }

	string	getMessage() const { return m_Message; }
	void	setMessage( const string& msg ) { m_Message = msg; }

private :
	string	m_Name;
	DWORD	m_Color;
	string	m_Message;
};


//////////////////////////////////////////////////////////////////////
//
// class GCPartySayFactory;
//
// Factory for GCPartySay
//
//////////////////////////////////////////////////////////////////////

class GCPartySayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCPartySay(); }

	// get packet name
	string getPacketName() const throw() { return "GCPartySay"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_PARTY_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPartySayPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 20 + szDWORD + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPartySayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPartySayHandler {

public :

	// execute packet's handler
	static void execute(GCPartySay* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
