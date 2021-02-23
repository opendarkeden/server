//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSystemAvailabilities.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SYSTEM_AVAILABILITIES_H__
#define __GC_SYSTEM_AVAILABILITIES_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCSystemAvailabilities;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCSystemAvailabilities : public Packet 
{
public:
	GCSystemAvailabilities() throw();
	~GCSystemAvailabilities() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SYSTEM_AVAILABILITIES; }
	PacketSize_t getPacketSize() const throw() { return szDWORD + szBYTE + szBYTE; }
	string getPacketName() const throw() { return "GCSystemAvailabilities"; }
	string toString() const throw();

public:
	DWORD	getFlag() const { return m_Flag; }
	void	setFlag(DWORD flag ) { m_Flag = flag; }

	BYTE	getOpenDegree() const { return m_Degree; }
	void	setOpenDegree( BYTE deg ) { m_Degree = deg; }

	BYTE	getSkillLimit() const { return m_SkillLimit; }
	void	setSkillLimit( BYTE lim ) { m_SkillLimit = lim; }

private:
	DWORD	m_Flag;
	BYTE	m_Degree;
	BYTE	m_SkillLimit;
};


//////////////////////////////////////////////////////////////////////////////
// class GCSystemAvailabilitiesFactory;
//////////////////////////////////////////////////////////////////////////////

class GCSystemAvailabilitiesFactory : public PacketFactory 
{
public :
	GCSystemAvailabilitiesFactory() throw() {}
	virtual ~GCSystemAvailabilitiesFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCSystemAvailabilities(); }
	string getPacketName() const throw() { return "GCSystemAvailabilities"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SYSTEM_AVAILABILITIES; }
	PacketSize_t getPacketMaxSize() const throw() { return szDWORD + szBYTE + szBYTE; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCSystemAvailabilitiesHandler;
//////////////////////////////////////////////////////////////////////////////

class GCSystemAvailabilitiesHandler 
{
public:
	static void execute(GCSystemAvailabilities* pGCSystemAvailabilities, Player* pPlayer) throw(Error);

};

#endif
