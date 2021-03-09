//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddNickname.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_NICKNAME_H__
#define __GC_ADD_NICKNAME_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "NicknameInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddNickname;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCAddNickname : public Packet 
{
public:
	GCAddNickname() ;
	~GCAddNickname() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_NICKNAME; }
	PacketSize_t getPacketSize() const  { return m_NicknameInfo.getSize(); }
	string getPacketName() const  { return "GCAddNickname"; }
	string toString() const ;

public:
	NicknameInfo&	getNicknameInfo() { return m_NicknameInfo; }

private :
	NicknameInfo	m_NicknameInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddNicknameFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddNicknameFactory : public PacketFactory 
{
public :
	GCAddNicknameFactory()  {}
	virtual ~GCAddNicknameFactory()  {}
	
public:
	Packet* createPacket()  { return new GCAddNickname(); }
	string getPacketName() const  { return "GCAddNickname"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_NICKNAME; }
	PacketSize_t getPacketMaxSize() const  { return NicknameInfo::getMaxSize(); }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddNicknameHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddNicknameHandler 
{
public:
	static void execute(GCAddNickname* pGCAddNickname, Player* pPlayer) ;

};

#endif
