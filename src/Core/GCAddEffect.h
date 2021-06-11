//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddEffect.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_EFFECT_H__
#define __GC_ADD_EFFECT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffect;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCAddEffect : public Packet 
{
public:
	GCAddEffect() ;
	~GCAddEffect() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_EFFECT; }
	PacketSize_t getPacketSize() const  { return szObjectID + szEffectID + szDuration; }
	string getPacketName() const  { return "GCAddEffect"; }
	string toString() const ;

public:
	EffectID_t getEffectID() const  { return m_EffectID; }
	void setEffectID(EffectID_t e)  { m_EffectID = e; }
	
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t o)  { m_ObjectID = o; }

	Duration_t getDuration() const  { return m_Duration; }
	void setDuration(Duration_t d)  { m_Duration = d; }
	
private :
	ObjectID_t m_ObjectID;
	EffectID_t m_EffectID;
	Duration_t m_Duration;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectFactory : public PacketFactory 
{
public :
	GCAddEffectFactory()  {}
	virtual ~GCAddEffectFactory()  {}
	
public:
	Packet* createPacket()  { return new GCAddEffect(); }
	string getPacketName() const  { return "GCAddEffect"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_EFFECT; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szEffectID + szDuration; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectHandler 
{
public:
	static void execute(GCAddEffect* pGCAddEffect, Player* pPlayer) ;

};

#endif
