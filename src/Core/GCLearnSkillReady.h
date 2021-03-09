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
	GCLearnSkillReady() ;
	
	// destructor
	~GCLearnSkillReady() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_LEARN_SKILL_READY; }
	
	// get packet size
	PacketSize_t getPacketSize() const  { return szSkillDomainType; }
	
	// get packet's name
	string getPacketName() const  { return "GCLearnSkillReady"; }
	
	// get packet's debug string
	string toString() const ;
	
	SkillDomainType_t getSkillDomainType() const  { return m_SkillDomainType;}
	void setSkillDomainType(SkillDomainType_t SkillDomainType) 
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
	 GCLearnSkillReadyFactory()  {}
	
	// destructor
	virtual ~GCLearnSkillReadyFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCLearnSkillReady(); }

	// get packet name
	string getPacketName() const  { return "GCLearnSkillReady"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_LEARN_SKILL_READY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillDomainType;}

};


//////////////////////////////////////////////////////////////////////
//
// class  GCLearnSkillReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCLearnSkillReadyHandler {

public :

	// execute packet's handler
	static void execute(GCLearnSkillReady* pGCLearnSkillReady, Player* pPlayer) ;

};

#endif	// __GC_LEARN_SKILL_READY_H__
