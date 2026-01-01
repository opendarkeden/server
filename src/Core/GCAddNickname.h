//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddNickname.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
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
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCAddNickname : public Packet 
{
public:
	GCAddNickname() ;
	~GCAddNickname() noexcept ;
	
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
