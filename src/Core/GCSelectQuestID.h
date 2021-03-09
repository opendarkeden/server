//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSelectQuestID.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SELECT_QUEST_ID_H__
#define __GC_SELECT_QUEST_ID_H__

#include <list>
#include "Packet.h"
#include "PacketFactory.h"

#ifdef __GAME_SERVER__
#include <algorithm>
#endif

const BYTE maxQuestNum = 255;

//////////////////////////////////////////////////////////////////////////////
// class GCSelectQuestID;
//////////////////////////////////////////////////////////////////////////////

class GCSelectQuestID : public Packet
{
public:
#ifdef __GAME_SERVER__
	// inItr은 container<QuestID_t>::input_iterator 여야 한다.
	template<class inItr>
	explicit GCSelectQuestID(inItr b, inItr e ) 
	{
		copy(b, e, back_inserter(m_QuestIDList ));
	}
#endif
	GCSelectQuestID()  { }
	virtual ~GCSelectQuestID() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SELECT_QUEST_ID; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCSelectQuestID"; }
	string toString() const ;

public:
	bool		empty() const { return m_QuestIDList.empty(); }
	QuestID_t	popQuestID() { QuestID_t qID = m_QuestIDList.front(); m_QuestIDList.pop_front(); return qID; }
	
private:
	list<QuestID_t>	m_QuestIDList;
};

//////////////////////////////////////////////////////////////////////////////
// class GCSelectQuestIDFactory;
//////////////////////////////////////////////////////////////////////////////

class GCSelectQuestIDFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCSelectQuestID(); }
	string getPacketName() const  { return "GCSelectQuestID"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SELECT_QUEST_ID; }
	PacketSize_t getPacketMaxSize() const 
	{
		return szBYTE
			 + szQuestID * maxQuestNum;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCSelectQuestIDHandler;
//////////////////////////////////////////////////////////////////////////////

class GCSelectQuestIDHandler 
{
public:
	static void execute(GCSelectQuestID* pPacket, Player* pPlayer) ;
};

#endif
