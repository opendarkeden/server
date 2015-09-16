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
	GCAddEffectToTile() throw();
	~GCAddEffectToTile() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_EFFECT_TO_TILE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord*2 + szEffectID + szDuration; }
	string getPacketName() const throw() { return "GCAddEffectToTile"; }
	string toString() const throw();

public:
	EffectID_t getEffectID() const throw() { return m_EffectID; }
	void setEffectID(EffectID_t e) throw() { m_EffectID = e; }

	Duration_t getDuration() const throw() { return m_Duration; }
	void setDuration(Duration_t d) throw() { m_Duration = d; }

	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t d) throw() { m_ObjectID = d; }

	Coord_t getX() const throw() { return m_X;}
	Coord_t getY() const throw() { return m_Y;}
	void setXY(Coord_t x, Coord_t y) throw() { m_X = x; m_Y = y;}
	
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
	Packet* createPacket() throw() { return new GCAddEffectToTile(); }
	string getPacketName() const throw() { return "GCAddEffectToTile"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_EFFECT_TO_TILE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord*2 + szEffectID + szDuration; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectToTileHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectToTileHandler 
{
public:
	static void execute(GCAddEffectToTile* pGCAddEffectToTile, Player* pPlayer) throw(Error);
};

#endif
