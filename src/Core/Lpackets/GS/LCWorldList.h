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
	LCWorldList() throw();

	// destructor
	// PCInfo* 배열에 할당된 객체를 삭제한다.
	~LCWorldList() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_WORLD_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();
	
	// get packet's name
	string getPacketName() const throw() { return "LCWorldList"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// 현재 월드
	WorldID_t getCurrentWorldID() const throw() { return m_CurrentWorldID; }
	void setCurrentWorldID( WorldID_t WorldID ) throw() { m_CurrentWorldID = WorldID; }

    BYTE getListNum() const throw() { return m_WorldInfoList.size(); }

	// add / delete / clear S List
	void addListElement(WorldInfo* pWorldInfo) throw() { m_WorldInfoList.push_back(pWorldInfo); }

	// ClearList
	void clearList() throw() { m_WorldInfoList.clear(); }

	// pop front Element in Status List
	WorldInfo* popFrontListElement() throw()
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
	Packet* createPacket() throw() { return new LCWorldList(); }

	// get packet name
	string getPacketName() const throw() { return "LCWorldList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_WORLD_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(LCWorldList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
