//--------------------------------------------------------------------------------
// 
// Filename    : CGNPCAskAnswer.h 
// Written By  : 김성민
// 
//--------------------------------------------------------------------------------

#ifndef __CG_NPC_ASKANSWER_H__
#define __CG_NPC_ASKANSWER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswer;
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswer : public Packet {

public:
	CGNPCAskAnswer() {};
    ~CGNPCAskAnswer() {};
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) ;
		    
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_NPC_ASK_ANSWER; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGNPCAskAnswerPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const  { return szObjectID + szScriptID + szAnswerID; }

	// get packet name
	string getPacketName() const  { return "CGNPCAskAnswer"; }
	
	// get packet's debug string
	string toString() const ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }
	
	ScriptID_t getScriptID()  { return m_ScriptID;}
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID;}
	
	AnswerID_t getAnswerID()  { return m_AnswerID;}
	void setAnswerID(AnswerID_t answerID)  { m_AnswerID = answerID;}

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
	ScriptID_t m_ScriptID;
	AnswerID_t m_AnswerID;

};


//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswerFactory;
//
// Factory for CGNPCAskAnswer
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswerFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGNPCAskAnswer(); }

	// get packet name
	string getPacketName() const  { return "CGNPCAskAnswer"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_NPC_ASK_ANSWER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGNPCAskAnswerPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szScriptID + szAnswerID; }

};


//--------------------------------------------------------------------------------
//
// class CGNPCAskAnswerHandler;
//
//--------------------------------------------------------------------------------

class CGNPCAskAnswerHandler {
	
public:

	// execute packet's handler
	static void execute(CGNPCAskAnswer* pPacket, Player* player) ;
};

#endif
