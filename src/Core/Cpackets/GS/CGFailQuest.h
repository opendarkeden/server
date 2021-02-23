//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGFailQuest.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_FAIL_QUEST_H__
#define __CG_FAIL_QUEST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGFailQuest;
//
//////////////////////////////////////////////////////////////////////

class CGFailQuest : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_FAIL_QUEST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "CGFailQuest"; }

	// get packet's debug string
	string toString() const throw();

public:
	BYTE	isFail() const { return m_bFail != 0; }
	void	setFail(bool bFail) { m_bFail = (bFail)?1:0; }

private :
	BYTE	m_bFail;
};


//////////////////////////////////////////////////////////////////////
//
// class CGFailQuestFactory;
//
// Factory for CGFailQuest
//
//////////////////////////////////////////////////////////////////////

class CGFailQuestFactory : public PacketFactory {

public:
	
	// constructor
	CGFailQuestFactory() throw() {}
	
	// destructor
	virtual ~CGFailQuestFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGFailQuest(); }

	// get packet name
	string getPacketName() const throw() { return "CGFailQuest"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_FAIL_QUEST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGFailQuestHandler;
//
//////////////////////////////////////////////////////////////////////

class CGFailQuestHandler {

public:

	// execute packet's handler
	static void execute(CGFailQuest* pCGFailQuest, Player* pPlayer) throw(Error);

};

#endif
