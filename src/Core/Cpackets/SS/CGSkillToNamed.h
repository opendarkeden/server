//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSkillToNamed.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SKILL_TO_NAMED_H__
#define __CG_SKILL_TO_NAMED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSkillToNamed;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToNamed : public Packet {

public:
	
	// constructor
	CGSkillToNamed() throw();
	
	// destructor
	~CGSkillToNamed() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_SKILL_TO_NAMED; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szSkillType + szCEffectID + szBYTE + m_TargetName.size(); }

	// get packet name
	string getPacketName() const throw() { return "CGSkillToNamed"; }

	// get SkillType
	SkillType_t getSkillType() const throw()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get CEffectID
	CEffectID_t getCEffectID() const throw() { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID) throw() { m_CEffectID = CEffectID; }

	// get Target name
	const string& getTargetName() const throw() { return m_TargetName; }
	void setTargetName( const string& targetName ) throw() { m_TargetName = targetName; }
	
	// get packet's debug string
	string toString() const throw();

private :

	// SkillType
	SkillType_t m_SkillType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// Target Name
	string m_TargetName;

};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToNamedFactory;
//
// Factory for CGSkillToNamed
//
//////////////////////////////////////////////////////////////////////

class CGSkillToNamedFactory : public PacketFactory {

public:
	
	// constructor
	CGSkillToNamedFactory() throw() {}
	
	// destructor
	virtual ~CGSkillToNamedFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSkillToNamed(); }

	// get packet name
	string getPacketName() const throw() { return "CGSkillToNamed"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SKILL_TO_NAMED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szCEffectID + szBYTE + 20; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToNamedHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToNamedHandler {

public:

	// execute packet's handler
	static void execute(CGSkillToNamed* pCGSkillToNamed, Player* pPlayer) throw(Error);

};

#endif
