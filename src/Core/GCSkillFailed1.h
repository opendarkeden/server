//////////////////////////////////////////////////////////////////////////////
// Filename    :  GCSkillFailed1.h 
// Written By  :  elca@ewestsoft.com
// Description :  Å
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_FAILED_1_H__
#define __GC_SKILL_FAILED_1_H__

#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class  GCSkillFailed1;
//////////////////////////////////////////////////////////////////////////////

class GCSkillFailed1 : public ModifyInfo 
{
public:
	GCSkillFailed1() ;
	~GCSkillFailed1() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SKILL_FAILED_1; }
	PacketSize_t getPacketSize() const  { return szSkillType + szBYTE + ModifyInfo::getPacketSize(); }
	string getPacketName() const  { return "GCSkillFailed1"; }
	string toString() const ;

public:
	SkillType_t getSkillType(void) const { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) { m_SkillType = SkillType; }

	BYTE getGrade() const { return m_Grade; }
	void setGrade(BYTE grade ) { m_Grade = grade; }
	
private: 
	SkillType_t m_SkillType;
	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed1Factory;
//
// Factory for  GCSkillFailed1
//
//////////////////////////////////////////////////////////////////////

class  GCSkillFailed1Factory : public PacketFactory 
{
public:
	GCSkillFailed1Factory()  {}
	virtual ~GCSkillFailed1Factory()  {}
	
public:
	Packet* createPacket()  { return new GCSkillFailed1(); }
	string getPacketName() const  { return "GCSkillFailed1"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SKILL_FAILED_1; }
	PacketSize_t getPacketMaxSize() const  { return szSkillType + szBYTE + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed1Handler;
//
//////////////////////////////////////////////////////////////////////

class  GCSkillFailed1Handler 
{
public:
	static void execute(GCSkillFailed1* pGCSkillFailed1, Player* pPlayer) ;
};

#endif	// __GC_SKILL_FAILED_1_H__
