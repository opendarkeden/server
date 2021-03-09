//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectQuest.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_QUEST_H__
#define __CG_SELECT_QUEST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectQuest;
//
//////////////////////////////////////////////////////////////////////

class CGSelectQuest : public Packet
{
public:
	CGSelectQuest() {};
    virtual ~CGSelectQuest() {};
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SELECT_QUEST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szQuestID + szObjectID; }

	// get packet name
	string getPacketName() const  { return "CGSelectQuest"; }

	// get packet's debug string
	string toString() const ;

	// get/set QuestID
	QuestID_t getQuestID() const  { return m_QuestID; }
	void setQuestID(QuestID_t QuestID )  { m_QuestID = QuestID; }

	ObjectID_t	getNPCObjectID() const { return m_NPCOID; }
	void		setNPCObjectID(ObjectID_t oid) { m_NPCOID = oid; }

private :

	// Quest ID
	QuestID_t m_QuestID;

	// NPC의 ObjectID
	ObjectID_t	m_NPCOID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectQuestFactory;
//
// Factory for CGSelectQuest
//
//////////////////////////////////////////////////////////////////////

class CGSelectQuestFactory : public PacketFactory {

public:
	
	// constructor
	CGSelectQuestFactory()  {}
	
	// destructor
	virtual ~CGSelectQuestFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGSelectQuest(); }

	// get packet name
	string getPacketName() const  { return "CGSelectQuest"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SELECT_QUEST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szQuestID + szObjectID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectQuestHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectQuestHandler {

public:

	// execute packet's handler
	static void execute(CGSelectQuest* pCGSelectQuest, Player* pPlayer) ;

};

#endif
