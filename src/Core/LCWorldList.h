//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCWorldList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_WORLD_LIST_H__
#define __LC_WORLD_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WorldInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCWorldList;
//
//////////////////////////////////////////////////////////////////////

class LCWorldList : public Packet {

public:

	// constructor
	// PCInfo* 배열에 각각 NULL을 지정한다.
	LCWorldList() ;

	// destructor
	// PCInfo* 배열에 할당된 객체를 삭제한다.
	~LCWorldList() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_WORLD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;
	
	// get packet's name
	string getPacketName() const  { return "LCWorldList"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// 현재 월드
	WorldID_t getCurrentWorldID() const  { return m_CurrentWorldID; }
	void setCurrentWorldID(WorldID_t WorldID )  { m_CurrentWorldID = WorldID; }

    BYTE getListNum() const  { return m_WorldInfoList.size(); }

	// add / delete / clear S List
	void addListElement(WorldInfo* pWorldInfo)  { m_WorldInfoList.push_back(pWorldInfo); }

	// ClearList
	void clearList()  { m_WorldInfoList.clear(); }

	// pop front Element in Status List
	WorldInfo* popFrontListElement() 
	{
		WorldInfo* TempWorldInfo = m_WorldInfoList.front(); m_WorldInfoList.pop_front(); return TempWorldInfo;
	}

private : 

	// 현재 WorldID
	WorldID_t m_CurrentWorldID;

	// 캐릭터 정보
	list<WorldInfo*> m_WorldInfoList;

};

//////////////////////////////////////////////////////////////////////
//
// class LCWorldListFactory;
//
// Factory for LCWorldList
//
//////////////////////////////////////////////////////////////////////

class LCWorldListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCWorldList(); }

	// get packet name
	string getPacketName() const  { return "LCWorldList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_WORLD_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  
	{ 
		// 슬레이어 정보가 뱀파이어 정보보다 사이즈가 크기 때문에,
		// 이 패킷의 최대 크기는 슬레이어 3 명일 경우이다.
		return szWorldID + WorldInfo::getMaxSize();
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCWorldListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCWorldListHandler {

public:

	// execute packet's handler
	static void execute(LCWorldList* pPacket, Player* pPlayer) ;

};

#endif
