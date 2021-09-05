//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCPCList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_PC_LIST_H__
#define __LC_PC_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCInfo.h"
#include "PCSlayerInfo.h"
#include "PCVampireInfo.h"
#include "PCOustersInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCPCList;
//
//////////////////////////////////////////////////////////////////////

class LCPCList : public Packet {

public:

	// constructor
	// PCInfo* 배열에 각각 NULL을 지정한다.
	LCPCList() ;

	// destructor
	// PCInfo* 배열에 할당된 객체를 삭제한다.
	~LCPCList() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_PC_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;
	
	// get packet's name
	string getPacketName() const  { return "LCPCList"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get/set pc info
	PCInfo* getPCInfo(Slot slot) const
	{ 
		if(m_pPCInfos[ slot ] == NULL)
			throw NoSuchElementException("no such PC exist in that slot");

		return m_pPCInfos[slot];
	}

	void setPCInfo(Slot slot, PCInfo* pPCInfo) 
	{ 
		if(m_pPCInfos[ slot ] != NULL)
			throw DuplicatedException("PCInfo duplicated.");
		m_pPCInfos[slot] = pPCInfo;
	}

	bool isAgree() const { return (m_Agree ? true : false); }
	void setAgree(bool agree ) { m_Agree = agree; }

private : 

	// 캐릭터 정보
	PCInfo* m_pPCInfos[ SLOT_MAX ];

	// 넷마블 사용자 약관 동의 여부
	BYTE m_Agree;
};


//////////////////////////////////////////////////////////////////////
//
// class LCPCListFactory;
//
// Factory for LCPCList
//
//////////////////////////////////////////////////////////////////////

class LCPCListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCPCList(); }

	// get packet name
	string getPacketName() const  { return "LCPCList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_PC_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  
	{ 
		// 슬레이어 정보가 뱀파이어 정보보다 사이즈가 크기 때문에,
		// 이 패킷의 최대 크기는 슬레이어 3 명일 경우이다.
		return PCSlayerInfo::getMaxSize()* SLOT_MAX + SLOT_MAX + szBYTE; 
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCPCListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCPCListHandler {

public:

	// execute packet's handler
	static void execute(LCPCList* pPacket, Player* pPlayer) ;

};

#endif
