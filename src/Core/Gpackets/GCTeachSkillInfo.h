//////////////////////////////////////////////////////////////////////////////
// Filename    : GCTeachSkillInfo.h 
// Written By  : 김성민
// Description : 
// NPC가 플레이어에게 스킬을 가르쳐 줄 때 제일 먼저 플레이어에게
// 전송되는 패킷이다. NPC가 가르쳐 줄 수 있는 기술의 범위를 기술하는 
// 데 쓰이는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TEACH_SKILL_INFO_H__
#define __GC_TEACH_SKILL_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfo;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfo : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TEACH_SKILL_INFO; }
	PacketSize_t getPacketSize() const throw() { return szSkillDomainType+szSkillLevel; }
	string getPacketName() const throw() { return "GCTeachSkillInfo"; }
	string toString() const throw();

public :
	SkillDomainType_t getDomainType(void) const throw() { return m_DomainType;}
	void setDomainType(SkillDomainType_t type) throw()  { m_DomainType = type;}

	SkillLevel_t getTargetLevel(void) const throw() { return m_TargetLevel;}
	void setTargetLevel(SkillLevel_t level) throw() { m_TargetLevel = level;}

private:
	SkillDomainType_t m_DomainType;  // NPC가 가르쳐주는 기술의 도메인 타입
	SkillLevel_t      m_TargetLevel; // 플레이어가 이제 배울 기술 레벨
};

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTeachSkillInfo(); }
	string getPacketName() const throw() { return "GCTeachSkillInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TEACH_SKILL_INFO; }
	PacketSize_t getPacketMaxSize() const throw() { return szSkillDomainType+szSkillLevel; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCTeachSkillInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCTeachSkillInfoHandler 
{
public :
	static void execute(GCTeachSkillInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
