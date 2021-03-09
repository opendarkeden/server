//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyJoined.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_JOINED_H__
#define __GC_PARTY_JOINED_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <string>

typedef struct
{
	string name;        // 10 
	BYTE   sex;         // 10 + 1 = 11
	BYTE   hair_style;  // 11 + 1 = 12
	IP_t   ip;          // 12 + 4 = 16

} PARTY_MEMBER_INFO;

// 구조체 맥스 크기(14) + 이름 길이 (1)
const uint PARTY_MEMBER_INFO_MAX_SIZE = 17; 

//////////////////////////////////////////////////////////////////////////////
// class GCPartyJoined;
//////////////////////////////////////////////////////////////////////////////

class GCPartyJoined : public Packet 
{
public:
	GCPartyJoined();
	~GCPartyJoined();

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_PARTY_JOINED; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCPartyJoined"; }
	string toString() const ;

public:
	BYTE getMemberInfoCount(void) { return m_MemberCount; }

	void addMemberInfo(PARTY_MEMBER_INFO* pInfo) ;
	PARTY_MEMBER_INFO* popMemberInfo(void) ;

	void clear(void) ;

private:
	BYTE                     m_MemberCount;
	list<PARTY_MEMBER_INFO*> m_MemberInfoList;
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyJoinedFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPartyJoinedFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCPartyJoined(); }
	string getPacketName() const  { return "GCPartyJoined"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_PARTY_JOINED; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + PARTY_MEMBER_INFO_MAX_SIZE * 6; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyJoinedHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPartyJoinedHandler 
{
public:
	static void execute(GCPartyJoined* pPacket, Player* pPlayer) ;
};

#endif
