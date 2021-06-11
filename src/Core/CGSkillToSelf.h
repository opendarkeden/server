//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSkillToSelf.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SKILL_TO_SELF_H__
#define __CG_SKILL_TO_SELF_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSkillToSelf;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToSelf : public Packet {

public:
	
	// constructor
	CGSkillToSelf() ;
	
	// destructor
	~CGSkillToSelf() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SKILL_TO_SELF; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szSkillType + szCEffectID; }

	// get packet name
	string getPacketName() const  { return "CGSkillToSelf"; }

	// get SkillType
	SkillType_t getSkillType() const   { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get CEffectID
	CEffectID_t getCEffectID() const  { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID)  { m_CEffectID = CEffectID; }

	// get packet's debug string
	string toString() const ;

private :

	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToSelfFactory;
//
// Factory for CGSkillToSelf
//
//////////////////////////////////////////////////////////////////////

class CGSkillToSelfFactory : public PacketFactory {

public:
	
	// constructor
	CGSkillToSelfFactory()  {}
	
	// destructor
	virtual ~CGSkillToSelfFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGSkillToSelf(); }

	// get packet name
	string getPacketName() const  { return "CGSkillToSelf"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SKILL_TO_SELF; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType + szCEffectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToSelfHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToSelfHandler {

public:

	// execute packet's handler
	static void execute(CGSkillToSelf* pCGSkillToSelf, Player* pPlayer) ;

};

#endif
