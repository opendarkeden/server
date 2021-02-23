//--------------------------------------------------------------------------------
// 
// Filename    : GCSkillInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SKILL_INFO_H__
#define __GC_SKILL_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSkillInfo.h"
#include "SlayerSkillInfo.h"
#include "VampireSkillInfo.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
//
// class GCSkillInfo;
//
// 클라이언트가 게임 서버에 접속해서 CGConnect 패킷을 보내면, 게임 서버는 크리처와
// 소유 아이템을 로딩해서 존에 들어갈 준비를 하게 된다. 그다음 PC와 아이템 정보,
// 그리고 존 정보를 GCSkillInfo에 담아서 클라이언트로 전송하게 된다.
//
//--------------------------------------------------------------------------------

class GCSkillInfo : public Packet {

public :

	// constructor
	GCSkillInfo() throw();

	// destructor
	~GCSkillInfo() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();

	// get packet name
	string getPacketName() const throw() { return "GCSkillInfo"; }
	
	// get packet's debug string
	string toString() const throw();

//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get / set PCType
	BYTE getPCType() const throw() { return m_PCType; }
	void setPCType(BYTE PCType) throw() { m_PCType = PCType; }

    // add / delete / clear Skill List
	void addListElement(PCSkillInfo* pPCSkillInfo) throw() { m_pPCSkillInfoList.push_back(pPCSkillInfo); }
	
	// ClearList
	void clearList() throw() { m_pPCSkillInfoList.clear(); }
	
	// pop front Element in Status List
	PCSkillInfo* popFrontListElement() throw()
	{
		PCSkillInfo* TempPCSkillInfo = m_pPCSkillInfoList.front(); m_pPCSkillInfoList.pop_front(); return TempPCSkillInfo;
	}

private :

	BYTE m_PCType;

	//---------------------------------------------------------
	// PC Skill Information
	// SlayerSkillInfo 또는 VampireSkillInfo 를 사용한다.
	//---------------------------------------------------------
	list<PCSkillInfo *> m_pPCSkillInfoList;

};


//--------------------------------------------------------------------------------
//
// class GCSkillInfoFactory;
//
// Factory for GCSkillInfo
//
//--------------------------------------------------------------------------------

class GCSkillInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillInfo(); }

	// get packet name
	string getPacketName() const throw() { return "GCSkillInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSkillInfoPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return SlayerSkillInfo::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCSkillInfoHandler;
//
//--------------------------------------------------------------------------------

class GCSkillInfoHandler {

public :

	// execute packet's handler
	static void execute(GCSkillInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
