//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetUseSkill.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PET_USE_SKILL_H__
#define __GC_PET_USE_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class GCPetUseSkill;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCPetUseSkill : public Packet 
{
public:
	GCPetUseSkill() throw();
	~GCPetUseSkill() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_PET_USE_SKILL; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szObjectID; }
	string getPacketName() const throw() { return "GCPetUseSkill"; }
	string toString() const throw();

public:
	ObjectID_t	getAttacker() const { return m_Attacker; }
	ObjectID_t	getTarget() const { return m_Target; }

	void	setAttacker( ObjectID_t Attacker ) { m_Attacker = Attacker; }
	void	setTarget( ObjectID_t Target ) { m_Target = Target; }

private:
	ObjectID_t	m_Attacker, m_Target;
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetUseSkillFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPetUseSkillFactory : public PacketFactory 
{
public :
	GCPetUseSkillFactory() throw() {}
	virtual ~GCPetUseSkillFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCPetUseSkill(); }
	string getPacketName() const throw() { return "GCPetUseSkill"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_PET_USE_SKILL; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCPetUseSkillHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPetUseSkillHandler 
{
public:
	static void execute(GCPetUseSkill* pGCPetUseSkill, Player* pPlayer) throw(Error);

};

#endif
