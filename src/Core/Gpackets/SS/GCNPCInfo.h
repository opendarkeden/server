//--------------------------------------------------------------------------------
// 
// Filename    : GCNPCInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_NPC_INFO_H__
#define __GC_NPC_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "GameTime.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "EffectInfo.h"
#include "Assert.h"
#include "RideMotorcycleInfo.h"
#include "NPCInfo.h"

#define FLAG_PREMIUM_ZONE			0x10	// premium으로 설정된 존이다.
#define FLAG_PREMIUM_PLAY			0x01	// premium play를 하는 중인가?

//--------------------------------------------------------------------------------
//
// class GCNPCInfo;
//
// 클라이언트가 게임 서버에 접속해서 CGConnect 패킷을 보내면, 게임 서버는 크리처와
// 소유 아이템을 로딩해서 존에 들어갈 준비를 하게 된다. 그다음 PC와 아이템 정보,
// 그리고 존 정보를 GCNPCInfo에 담아서 클라이언트로 전송하게 된다.
//
//--------------------------------------------------------------------------------

class GCNPCInfo : public Packet {

public :

	// constructor
	GCNPCInfo() throw();

	// destructor
	~GCNPCInfo() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_NPC_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
		for(; itr != m_NPCInfos.end(); itr++)
		{
			NPCInfo* pInfo = *itr;
			size += pInfo->getSize();
		}

		return size;
	}

	// get packet name
	string getPacketName() const throw() { return "GCNPCInfo"; }
	
	// get packet's debug string
	string toString() const throw();


//--------------------------------------------------
// methods
//--------------------------------------------------
public :
	// get/set npc info
	void addNPCInfo(NPCInfo* pInfo) { m_NPCInfos.push_back(pInfo);}
	NPCInfo* popNPCInfo(void) { if (m_NPCInfos.empty()) return NULL; NPCInfo* pInfo = m_NPCInfos.front(); m_NPCInfos.pop_front(); return pInfo; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :
	// 현재 존에 존재하는 NPC들에 대한 정보
	list<NPCInfo*> m_NPCInfos;
};


//--------------------------------------------------------------------------------
//
// class GCNPCInfoFactory;
//
// Factory for GCNPCInfo
//
//--------------------------------------------------------------------------------

class GCNPCInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCNPCInfo(); }

	// get packet name
	string getPacketName() const throw() { return "GCNPCInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NPC_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCNPCInfoPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		size += NPCInfo::getMaxSize()* 255;

		return size;
	}

};



//--------------------------------------------------------------------------------
//
// class GCNPCInfoHandler;
//
//--------------------------------------------------------------------------------

class GCNPCInfoHandler {

public :

	// execute packet's handler
	static void execute(GCNPCInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
