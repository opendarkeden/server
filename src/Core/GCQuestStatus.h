//////////////////////////////////////////////////////////////////////////////
// Filename    : GCQuestStatus.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_QUEST_STATUS_H__
#define __GC_QUEST_STATUS_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCQuestStatus;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatus : public Packet 
{
public:
	GCQuestStatus() throw();
	~GCQuestStatus() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_QUEST_STATUS; }
	PacketSize_t getPacketSize() const throw() { return szWORD + szWORD + szDWORD; }
	string getPacketName() const throw() { return "GCQuestStatus"; }
	string toString() const throw();

public:
	WORD getQuestID() const throw() { return m_QuestID; }
	void setQuestID(WORD e) throw() { m_QuestID = e; }
	
	WORD getCurrentNum() const throw() { return m_CurrentNum; }
	void setCurrentNum(WORD n) throw() { m_CurrentNum = n; }

	DWORD getRemainTime() const throw() { return m_Time; }
	void setRemainTime(DWORD d) throw() { m_Time = d; }
	
private :
	WORD m_QuestID;
	WORD m_CurrentNum;
	DWORD m_Time;
};


//////////////////////////////////////////////////////////////////////////////
// class GCQuestStatusFactory;
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatusFactory : public PacketFactory 
{
public :
	GCQuestStatusFactory() throw() {}
	virtual ~GCQuestStatusFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCQuestStatus(); }
	string getPacketName() const throw() { return "GCQuestStatus"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_QUEST_STATUS; }
	PacketSize_t getPacketMaxSize() const throw() { return szWORD + szWORD + szDWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCQuestStatusHandler;
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatusHandler 
{
public:
	static void execute(GCQuestStatus* pGCQuestStatus, Player* pPlayer) throw(Error);

};

#endif
