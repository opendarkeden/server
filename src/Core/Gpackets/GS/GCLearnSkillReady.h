//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCLearnSkillReady.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_LEARN_SKILL_READY_H__
#define __GC_LEARN_SKILL_READY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReady;
//
//////////////////////////////////////////////////////////////////////

class GCLearnSkillReady : public Packet {

public :
	
	// constructor
	GCLearnSkillReady() throw();
	
	// destructor
	~GCLearnSkillReady() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_LEARN_SKILL_READY; }
	
	// get packet size
	PacketSize_t getPacketSize() const throw() { return szSkillDomainType; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCLearnSkillReady"; }
	
	// get packet's debug string
	string toString() const throw();
	
	SkillDomainType_t getSkillDomainType() const throw() { return m_SkillDomainType;}
	void setSkillDomainType(SkillDomainType_t SkillDomainType) throw()
	{
		m_SkillDomainType = SkillDomainType;
	}
private : 

	// 스킬 타입
	SkillDomainType_t m_SkillDomainType;

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReadyFactory;
//
// Factory for  GCLearnSkillReady
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillReadyFactory : public PacketFactory {

public :
	
	// constructor
	 GCLearnSkillReadyFactory() throw() {}
	
	// destructor
	virtual ~GCLearnSkillReadyFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCLearnSkillReady(); }

	// get packet name
	string getPacketName() const throw() { return "GCLearnSkillReady"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_LEARN_SKILL_READY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillDomainType;}

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillReadyHandler {

public :

	// execute packet's handler
	static void execute( GCLearnSkillReady* pGCLearnSkillReady, Player* pPlayer) throw(Error);

};

#endif	// __GC_LEARN_SKILL_READY_H__
