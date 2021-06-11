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
	CGLotterySelect() {};
    ~CGLotterySelect() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_LOTTERY_SELECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szBYTE + szDWORD + szDWORD; }

	// get packet name
	string getPacketName() const  { return "CGLotterySelect"; }

	// get packet's debug string
	string toString() const ;

	BYTE getType() const  { return m_Type; }
	void setType(BYTE type ) { m_Type = type; }

	DWORD getGiftID() const  { return m_GiftID; }
	void setGiftID(DWORD GiftID )  { m_GiftID = GiftID; }

	DWORD getQuestLevel() const  { return m_QuestLevel; }
	void setQuestLevel(DWORD QuestLevel )  { m_QuestLevel = QuestLevel; }

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
	CGLotterySelectFactory()  {}
	
	// destructor
	virtual ~CGLotterySelectFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGLotterySelect(); }

	// get packet name
	string getPacketName() const  { return "CGLotterySelect"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_LOTTERY_SELECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szDWORD + szDWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelectHandler {

public:

	// execute packet's handler
	static void execute(CGLotterySelect* pCGLotterySelect, Player* pPlayer) ;

};

#endif
