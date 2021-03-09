//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPartySay 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PARTY_SAY_H__
#define __CG_PARTY_SAY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPartySay; //
//////////////////////////////////////////////////////////////////////

class CGPartySay : public Packet {

public:
	
	// constructor
	CGPartySay() ;
	
	// destructor
	~CGPartySay() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_PARTY_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szDWORD + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName() const  { return "CGPartySay"; }
	
	// get packet's debug string
	string toString() const ;

public:
	void	setColor(DWORD color ) { m_Color = color; }
	DWORD	getColor() const { return m_Color; }

	void	setMessage(const string& msg ) { m_Message = msg; }
	string	getMessage() const { return m_Message; }

private :
	DWORD	m_Color;
	string	m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGPartySayFactory;
//
// Factory for CGPartySay
//
//////////////////////////////////////////////////////////////////////

class CGPartySayFactory : public PacketFactory {

public:
	
	// constructor
	CGPartySayFactory()  {}
	
	// destructor
	virtual ~CGPartySayFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGPartySay(); }

	// get packet name
	string getPacketName() const  { return "CGPartySay"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_PARTY_SAY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szDWORD + szBYTE + 128; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGPartySayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPartySayHandler {
	
public:

	// execute packet's handler
	static void execute(CGPartySay* pCGPartySay, Player* player) ;
};

#endif
