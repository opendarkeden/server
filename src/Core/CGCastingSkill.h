//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGCastingSkill.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_CASTING_SKILL_H__
#define __CG_CASTING_SKILL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGCastingSkill;
//
//////////////////////////////////////////////////////////////////////

class CGCastingSkill : public Packet {

public:
	
	// constructor
	CGCastingSkill() ;
	
	// destructor
	~CGCastingSkill() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_CASTING_SKILL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szSkillType; }

	// get packet name
	string getPacketName() const  { return "CGCastingSkill"; }

	// get/set SkillType
	SkillType_t getSkillType() const   { return m_SkillType; }
	void setObjectID(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get packet's debug string
	string toString() const ;

private :

	// SkillType
	SkillType_t m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class CGCastingSkillFactory;
//
// Factory for CGCastingSkill
//
//////////////////////////////////////////////////////////////////////

class CGCastingSkillFactory : public PacketFactory {

public:
	
	// constructor
	CGCastingSkillFactory()  {}
	
	// destructor
	virtual ~CGCastingSkillFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGCastingSkill(); }

	// get packet name
	string getPacketName() const  { return "CGCastingSkill"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_CASTING_SKILL; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGCastingSkillHandler;
//
//////////////////////////////////////////////////////////////////////

class CGCastingSkillHandler {

public:

	// execute packet's handler
	static void execute(CGCastingSkill* pCGCastingSkill, Player* pPlayer) ;

};

#endif
