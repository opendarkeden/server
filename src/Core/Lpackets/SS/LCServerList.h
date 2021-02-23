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
	LCServerList() throw();

	// destructor
	// PCInfo* 배열에 할당된 객체를 삭제한다.
	~LCServerList() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_LC_SERVER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();
	
	// get packet's name
	string getPacketName() const throw() { return "LCServerList"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// 현재 서버 그룹
	ServerGroupID_t getCurrentServerGroupID() const throw() { return m_CurrentServerGroupID; }
	void setCurrentServerGroupID( ServerGroupID_t ServerGroupID ) throw() { m_CurrentServerGroupID = ServerGroupID; }

    BYTE getListNum() const throw() { return m_ServerGroupInfoList.size(); }

	// add / delete / clear S List
	void addListElement(ServerGroupInfo* pServerGroupInfo) throw() { m_ServerGroupInfoList.push_back(pServerGroupInfo); }

	// ClearList
	void clearList() throw() { m_ServerGroupInfoList.clear(); }

	// pop front Element in Status List
	ServerGroupInfo* popFrontListElement() throw()
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
	Packet* createPacket() throw() { return new LCServerList(); }

	// get packet name
	string getPacketName() const throw() { return "LCServerList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_SERVER_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(LCServerList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
