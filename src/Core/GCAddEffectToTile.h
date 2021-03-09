//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddEffectToTile.h 
// Written By  : elca@ewestsoft.com
// Description :
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_EFFECT_TO_TILE_H__
#define __GC_ADD_EFFECT_TO_TILE_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTile;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTile : public Packet 
{
public:
	GCAddEffectToTile() ;
	~GCAddEffectToTile() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_EFFECT_TO_TILE; }
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord*2 + szEffectID + szDuration; }
	string getPacketName() const  { return "GCAddEffectToTile"; }
	string toString() const ;

public:
	EffectID_t getEffectID() const  { return m_EffectID; }
	void setEffectID(EffectID_t e)  { m_EffectID = e; }

	Duration_t getDuration() const  { return m_Duration; }
	void setDuration(Duration_t d)  { m_Duration = d; }

	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t d)  { m_ObjectID = d; }

	Coord_t getX() const  { return m_X;}
	Coord_t getY() const  { return m_Y;}
	void setXY(Coord_t x, Coord_t y)  { m_X = x; m_Y = y;}
	
private:
	Coord_t     m_X;
	Coord_t     m_Y;
	ObjectID_t  m_ObjectID;
	EffectID_t	m_EffectID;
	Duration_t	m_Duration;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTileFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTileFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddEffectToTile(); }
	string getPacketName() const  { return "GCAddEffectToTile"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_EFFECT_TO_TILE; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord*2 + szEffectID + szDuration; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTileHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTileHandler 
{
public:
	static void execute(GCAddEffectToTile* pGCAddEffectToTile, Player* pPlayer) ;
};

#endif
