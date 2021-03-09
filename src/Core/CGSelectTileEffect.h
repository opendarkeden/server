//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectTileEffect.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_TILE_EFFECT_H__
#define __CG_SELECT_TILE_EFFECT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectTileEffect
//////////////////////////////////////////////////////////////////////////////

class CGSelectTileEffect : public Packet 
{
public:
    CGSelectTileEffect() {};
    virtual ~CGSelectTileEffect() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_SELECT_TILE_EFFECT; }
	PacketSize_t getPacketSize() const  { return szObjectID; }
	string getPacketName() const  { return "CGSelectTileEffect"; }
	string toString() const ;

public:
	ObjectID_t getEffectObjectID(void) const { return m_EffectObjectID; }
	void setEffectObjectID(ObjectID_t id) { m_EffectObjectID = id; }

private:
	ObjectID_t m_EffectObjectID; // 선택한 이펙트의 오브젝트 ID
};


//////////////////////////////////////////////////////////////////////////////
// class CGSelectTileEffectFactory
//////////////////////////////////////////////////////////////////////////////

class CGSelectTileEffectFactory : public PacketFactory 
{
	Packet* createPacket()  { return new CGSelectTileEffect(); }
	string getPacketName() const  { return "CGSelectTileEffect"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SELECT_TILE_EFFECT; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID; }
};


//////////////////////////////////////////////////////////////////////////////
// class CGSelectTileEffectHandler
//////////////////////////////////////////////////////////////////////////////

class Effect;

class CGSelectTileEffectHandler 
{
public:
	static void execute(CGSelectTileEffect* pCGSelectTileEffect, Player* pPlayer) ;
	static void executeVampirePortal(CGSelectTileEffect* pCGSelectTileEffect, Player* pPlayer, Effect* pEffect) ;
};

#endif
