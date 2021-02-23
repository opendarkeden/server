//--------------------------------------------------------------------------------
// 
// Filename    : GCMorph1.h 
// Written By  : crazydog
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_MORPH1_H__
#define __GC_MORPH1_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "GameTime.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
//
// class GCMorph1;
//
//	slayer등이 vampire로 변신할때, 변신하시는 분에게 보내는 패킷.
//--------------------------------------------------------------------------------

class GCMorph1 : public Packet {

public :

	// constructor
	GCMorph1() throw();

	// destructor
	~GCMorph1() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_MORPH_1; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		// [PCType][PCInfo]
		// [GameTime][Weather][WeatherLevel][DarkLevel][LightLevel]
		// [#NPCTypes][NPCType1]...[NPCTypeN]
		// [#MonsterTypes][MonsterType1]...[MonsterTypeM]
		return m_pPCInfo->getSize() 
			+ m_pInventoryInfo->getSize()
			+ m_pGearInfo->getSize()
			+ m_pExtraInfo->getSize();
	}

	// get packet name
	string getPacketName() const throw() { return "GCMorph1"; }
	
	// get packet's debug string
	string toString() const throw();


//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get/set PC info
	PCInfo* getPCInfo2() const throw() { return m_pPCInfo; }
	void setPCInfo2(PCInfo* pPCInfo) throw(Error) { m_pPCInfo = pPCInfo; }

	// get/set Inventory Info
	InventoryInfo* getInventoryInfo() const throw() { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo) throw(Error) { m_pInventoryInfo = pInventoryInfo; }

	// get/set Gear Info
	GearInfo* getGearInfo() const throw() { return m_pGearInfo; }
	void setGearInfo(GearInfo* pGearInfo) throw(Error) { m_pGearInfo = pGearInfo; }

	// get/set ExtraInfo
	ExtraInfo* getExtraInfo() const throw() { return m_pExtraInfo; }
	void setExtraInfo(ExtraInfo* pExtraInfo) throw(Error) { m_pExtraInfo = pExtraInfo; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :

	//--------------------------------------------------------------------------------
	// PC Information
	//--------------------------------------------------------------------------------
	// PCSlayerInfo2 또는 PCVampireInfo2 를 사용한다.
	PCInfo* m_pPCInfo;

	//--------------------------------------------------------------------------------
	// Inventory Information
	//--------------------------------------------------------------------------------
	InventoryInfo* m_pInventoryInfo;

	//--------------------------------------------------------------------------------
	// Gear Information
	//--------------------------------------------------------------------------------
	GearInfo* m_pGearInfo;

	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	ExtraInfo* m_pExtraInfo;
	
	// inventory
	// quick item slot
	// gear

	// 저널(PDA)
	// 수행 퀘스트 정보
	// 공지사항, 이벤트 정보
	// 흐흠.. 얘들은 처음 PDS를 켤 때 다운받을까나.. - -;


};


//--------------------------------------------------------------------------------
//
// class GCMorph1Factory;
//
// Factory for GCMorph1
//
//--------------------------------------------------------------------------------

class GCMorph1Factory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMorph1(); }

	// get packet name
	string getPacketName() const throw() { return "GCMorph1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MORPH_1; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCMorph1PacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szBYTE + PCSlayerInfo2::getMaxSize() 
			+ InventoryInfo::getMaxSize()
			+ GearInfo::getMaxSize()
			+ ExtraInfo::getMaxSize()
			;
	}

};



//--------------------------------------------------------------------------------
//
// class GCMorph1Handler;
//
//--------------------------------------------------------------------------------

class GCMorph1Handler {

public :

	// execute packet's handler
	static void execute(GCMorph1* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
