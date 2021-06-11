//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDeleteEffectFromTile.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DELETE_EFFECT_FROM_TILE_H__
#define __GC_DELETE_EFFECT_FROM_TILE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCDeleteEffectFromTile;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCDeleteEffectFromTile : public Packet {

public :
	
	// constructor
	GCDeleteEffectFromTile() ;
	
	// destructor
	~GCDeleteEffectFromTile() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_DELETE_EFFECT_FROM_TILE; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord*2 + szEffectID; }

	// get packet's name
	string getPacketName() const  { return "GCDeleteEffectFromTile"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set EffectID 
	EffectID_t getEffectID() const  { return m_EffectID; }
	void setEffectID(EffectID_t e)  { m_EffectID = e; }
	

	// get / set ObjectID 
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t d)  { m_ObjectID = d; }

	// get & set X, Y
	Coord_t getX() const  { return m_X;}
	Coord_t getY() const  { return m_Y;}
	void setXY(Coord_t x, Coord_t y)  { m_X = x; m_Y = y;}
	
private :
	
	Coord_t  m_X, m_Y;
	ObjectID_t m_ObjectID;

	EffectID_t	m_EffectID;
};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteEffectFromTileFactory;
//
// Factory for GCDeleteEffectFromTile
//
//////////////////////////////////////////////////////////////////////

class GCDeleteEffectFromTileFactory : public PacketFactory {

public :
	
	// constructor
	GCDeleteEffectFromTileFactory()  {}
	
	// destructor
	virtual ~GCDeleteEffectFromTileFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCDeleteEffectFromTile(); }

	// get packet name
	string getPacketName() const  { return "GCDeleteEffectFromTile"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_DELETE_EFFECT_FROM_TILE; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize() const  { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE* m_ListNum* 2 ; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord*2 + szEffectID ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteEffectFromTileHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteEffectFromTileHandler {

public :

	// execute packet's handler
	static void execute(GCDeleteEffectFromTile* pGCDeleteEffectFromTile, Player* pPlayer) ;

};

#endif
