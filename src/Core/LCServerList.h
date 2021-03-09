//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCServerList.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_SERVER_LIST_H__
#define __LC_SERVER_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "ServerGroupInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class LCServerList;
//
//////////////////////////////////////////////////////////////////////

class LCServerList : public Packet {

public:

	// constructor
	// PCInfo* 배열에 각각 NULL을 지정한다.
	LCServerList() ;

	// destructor
	// PCInfo* 배열에 할당된 객체를 삭제한다.
	~LCServerList() ;
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_LC_SERVER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const ;
	
	// get packet's name
	string getPacketName() const  { return "LCServerList"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// 현재 서버 그룹
	ServerGroupID_t getCurrentServerGroupID() const  { return m_CurrentServerGroupID; }
	void setCurrentServerGroupID(ServerGroupID_t ServerGroupID )  { m_CurrentServerGroupID = ServerGroupID; }

    BYTE getListNum() const  { return m_ServerGroupInfoList.size(); }

	// add / delete / clear S List
	void addListElement(ServerGroupInfo* pServerGroupInfo)  { m_ServerGroupInfoList.push_back(pServerGroupInfo); }

	// ClearList
	void clearList()  { m_ServerGroupInfoList.clear(); }

	// pop front Element in Status List
	ServerGroupInfo* popFrontListElement() 
	{
		ServerGroupInfo* TempServerGroupInfo = m_ServerGroupInfoList.front(); m_ServerGroupInfoList.pop_front(); return TempServerGroupInfo;
	}

private : 

	// 현재 서버 그룹
	ServerGroupID_t m_CurrentServerGroupID;

	// 캐릭터 정보
	list<ServerGroupInfo*> m_ServerGroupInfoList;

};

//////////////////////////////////////////////////////////////////////
//
// class LCServerListFactory;
//
// Factory for LCServerList
//
//////////////////////////////////////////////////////////////////////

class LCServerListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCServerList(); }

	// get packet name
	string getPacketName() const  { return "LCServerList"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_LC_SERVER_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const  
	{ 
		// 슬레이어 정보가 뱀파이어 정보보다 사이즈가 크기 때문에,
		// 이 패킷의 최대 크기는 슬레이어 3 명일 경우이다.
		return szServerGroupID + ServerGroupInfo::getMaxSize();
	}
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCServerListHandler;
//
//////////////////////////////////////////////////////////////////////

class LCServerListHandler {

public:

	// execute packet's handler
	static void execute(LCServerList* pPacket, Player* pPlayer) ;

};

#endif
