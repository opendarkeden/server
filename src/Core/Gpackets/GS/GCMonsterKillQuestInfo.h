//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMonsterKillQuestInfo.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MONSTER_KILL_QUEST_INFO_H__
#define __GC_MONSTER_KILL_QUEST_INFO_H__

#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GCSelectQuestID.h"

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestInfo;
//////////////////////////////////////////////////////////////////////////////

class GCMonsterKillQuestInfo : public Packet
{
public:
	struct QuestInfo
	{
		QuestID_t	questID;
		SpriteType_t	sType;
		WORD		goal;
		DWORD		timeLimit;
	};

	static const int szQuestInfo;
	
	GCMonsterKillQuestInfo() throw() { }
	virtual ~GCMonsterKillQuestInfo() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_MONSTER_KILL_QUEST_INFO; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCMonsterKillQuestInfo"; }
	string toString() const throw();

public:
	bool		empty() const { return m_QuestInfoList.empty(); }
	QuestInfo*	popQuestInfo() { QuestInfo* pQI = m_QuestInfoList.front(); m_QuestInfoList.pop_front(); return pQI; }
	void		addQuestInfo( QuestInfo* pQI ) { m_QuestInfoList.push_back( pQI ); }
	
private:
	list<QuestInfo*>	m_QuestInfoList;
};

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCMonsterKillQuestInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCMonsterKillQuestInfo(); }
	string getPacketName() const throw() { return "GCMonsterKillQuestInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MONSTER_KILL_QUEST_INFO; }
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szBYTE
			 + GCMonsterKillQuestInfo::szQuestInfo * maxQuestNum;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCMonsterKillQuestInfoHandler 
{
public:
	static void execute(GCMonsterKillQuestInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
