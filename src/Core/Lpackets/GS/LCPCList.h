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
	LCPCList() throw();

	// destructor
	// PCInfo* 배열에 할당된 객체를 삭제한다.
	~LCPCList() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_PC_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();
	
	// get packet's name
	string getPacketName() const throw() { return "LCPCList"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get/set pc info
	PCInfo* getPCInfo(Slot slot) const throw(NoSuchElementException) 
	{ 
		if(m_pPCInfos[ slot ] == NULL)
			throw NoSuchElementException("no such PC exist in that slot");

		return m_pPCInfos[slot];
	}

	void setPCInfo(Slot slot, PCInfo* pPCInfo) throw(DuplicatedException) 
	{ 
		if(m_pPCInfos[ slot ] != NULL)
			throw DuplicatedException("PCInfo duplicated.");
		m_pPCInfos[slot] = pPCInfo;
	}

private : 

	// 캐릭터 정보
	PCInfo* m_pPCInfos[ SLOT_MAX ];

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
	Packet* createPacket() throw() { return new LCPCList(); }

	// get packet name
	string getPacketName() const throw() { return "LCPCList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_PC_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		// 슬레이어 정보가 뱀파이어 정보보다 사이즈가 크기 때문에,
		// 이 패킷의 최대 크기는 슬레이어 3 명일 경우이다.
		return PCSlayerInfo::getMaxSize()* SLOT_MAX + SLOT_MAX; 
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
	static void execute(LCPCList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
