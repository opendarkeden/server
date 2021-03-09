//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSkillToObject.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SKILL_TO_OBJECT_H__
#define __CG_SKILL_TO_OBJECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSkillToObject;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToObject : public Packet {

public:
	
	// constructor
	CGSkillToObject() ;
	
	// destructor
	~CGSkillToObject() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SKILL_TO_OBJECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szSkillType + szCEffectID + szObjectID; }

	// get packet name
	string getPacketName() const  { return "CGSkillToObject"; }

	// get/set SkillType
	SkillType_t getSkillType() const   { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get/set CEffectID
	CEffectID_t getCEffectID() const  { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID)  { m_CEffectID = CEffectID; }

	// get/set TargetObjectID
	ObjectID_t getTargetObjectID() const  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID)  { m_TargetObjectID = TargetObjectID; }
	
	// get packet's debug string
	string toString() const ;

private :

	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToObjectFactory;
//
// Factory for CGSkillToObject
//
//////////////////////////////////////////////////////////////////////

class CGSkillToObjectFactory : public PacketFactory {

public:
	
	// constructor
	CGSkillToObjectFactory()  {}
	
	// destructor
	virtual ~CGSkillToObjectFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGSkillToObject(); }

	// get packet name
	string getPacketName() const  { return "CGSkillToObject"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SKILL_TO_OBJECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType + szCEffectID + szObjectID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToObjectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToObjectHandler {

public:

	// execute packet's handler
	static void execute(CGSkillToObject* pCGSkillToObject, Player* pPlayer) ;

};

#endif
