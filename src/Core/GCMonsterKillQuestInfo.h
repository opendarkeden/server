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
	
	GCMonsterKillQuestInfo()  { }
	virtual ~GCMonsterKillQuestInfo() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_MONSTER_KILL_QUEST_INFO; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCMonsterKillQuestInfo"; }
	string toString() const ;

public:
	bool		empty() const { return m_QuestInfoList.empty(); }
	QuestInfo*	popQuestInfo() { QuestInfo* pQI = m_QuestInfoList.front(); m_QuestInfoList.pop_front(); return pQI; }
	void		addQuestInfo(QuestInfo* pQI ) { m_QuestInfoList.push_back(pQI); }
	
private:
	list<QuestInfo*>	m_QuestInfoList;
};

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCMonsterKillQuestInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCMonsterKillQuestInfo(); }
	string getPacketName() const  { return "GCMonsterKillQuestInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_MONSTER_KILL_QUEST_INFO; }
	PacketSize_t getPacketMaxSize() const 
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
	static void execute(GCMonsterKillQuestInfo* pPacket, Player* pPlayer) ;
};

#endif
