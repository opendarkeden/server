//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGLotterySelect.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_LOTTERY_SELECT_H__
#define __CG_LOTTERY_SELECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

enum
{
	TYPE_SELECT_LOTTERY = 0,					// 복권 선택
	TYPE_FINISH_SCRATCH,				// 복권 긁음 완료
	TYPE_OVER_ENDING,					// 엔딩 종료

	TYPE_MAX,
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelect;
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelect : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_LOTTERY_SELECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + szDWORD + szDWORD; }

	// get packet name
	string getPacketName() const throw() { return "CGLotterySelect"; }

	// get packet's debug string
	string toString() const throw();

	BYTE getType() const throw() { return m_Type; }
	void setType( BYTE type ) { m_Type = type; }

	DWORD getGiftID() const throw() { return m_GiftID; }
	void setGiftID( DWORD GiftID ) throw() { m_GiftID = GiftID; }

	DWORD getQuestLevel() const throw() { return m_QuestLevel; }
	void setQuestLevel( DWORD QuestLevel ) throw() { m_QuestLevel = QuestLevel; }

private :

	BYTE	m_Type;
	DWORD	m_QuestLevel;
	DWORD	m_GiftID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelectFactory;
//
// Factory for CGLotterySelect
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelectFactory : public PacketFactory {

public:
	
	// constructor
	CGLotterySelectFactory() throw() {}
	
	// destructor
	virtual ~CGLotterySelectFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGLotterySelect(); }

	// get packet name
	string getPacketName() const throw() { return "CGLotterySelect"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_LOTTERY_SELECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szDWORD + szDWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelectHandler {

public:

	// execute packet's handler
	static void execute(CGLotterySelect* pCGLotterySelect, Player* pPlayer) throw(Error);

};

#endif
