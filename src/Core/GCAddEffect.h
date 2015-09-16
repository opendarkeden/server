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
	GCAddEffect() throw();
	~GCAddEffect() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_EFFECT; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szEffectID + szDuration; }
	string getPacketName() const throw() { return "GCAddEffect"; }
	string toString() const throw();

public:
	EffectID_t getEffectID() const throw() { return m_EffectID; }
	void setEffectID(EffectID_t e) throw() { m_EffectID = e; }
	
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t o) throw() { m_ObjectID = o; }

	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t d) throw() { m_Duration = d; }
	
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
	GCAddEffectFactory() throw() {}
	virtual ~GCAddEffectFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCAddEffect(); }
	string getPacketName() const throw() { return "GCAddEffect"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_EFFECT; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szEffectID + szDuration; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectHandler 
{
public:
	static void execute(GCAddEffect* pGCAddEffect, Player* pPlayer) throw(Error);

};

#endif
