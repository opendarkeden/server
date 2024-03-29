//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCDownSkillOK.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DOWN_SKILL_OK_H__
#define __GC_DOWN_SKILL_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillOK;
//
//////////////////////////////////////////////////////////////////////

class GCDownSkillOK : public Packet {

public :
	
	// constructor
	GCDownSkillOK() ;
	
	// destructor
	~GCDownSkillOK() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_DOWN_SKILL_OK; }
	
	// get packet size
	PacketSize_t getPacketSize() const  { return szSkillType; }
	
	// get packet's name
	string getPacketName() const  { return "GCDownSkillOK"; }
	
	// get packet's debug string
	string toString() const ;
	
	// get/set m_SkillType
	SkillType_t getSkillType() const  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

private : 

	// SkillType
	SkillType_t m_SkillType; 

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillOKFactory;
//
// Factory for  GCDownSkillOK
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillOKFactory : public PacketFactory {

public :
	
	// constructor
	 GCDownSkillOKFactory()  {}
	
	// destructor
	virtual ~GCDownSkillOKFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCDownSkillOK(); }

	// get packet name
	string getPacketName() const  { return "GCDownSkillOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_DOWN_SKILL_OK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCDownSkillOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCDownSkillOKHandler {

public :

	// execute packet's handler
	static void execute(GCDownSkillOK* pGCDownSkillOK, Player* pPlayer) ;

};

#endif	// __GC_DOWN_SKILL_OK_H__
