//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSkillToTile.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SKILL_TO_TILE_H__
#define __CG_SKILL_TO_TILE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSkillToTile;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToTile : public Packet {

public:
	
	// constructor
	CGSkillToTile() ;
	
	// destructor
	~CGSkillToTile() ;

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_CG_SKILL_TO_TILE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const  { return szSkillType + szCEffectID + szCoord + szCoord ; }

	// get packet name
	string getPacketName() const  { return "CGSkillToTile"; }

	// get/set SkillType
	SkillType_t getSkillType() const   { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get/set CEffectID
	CEffectID_t getCEffectID() const  { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID)  { m_CEffectID = CEffectID; }

	// get/set X
	Coord_t getX() const  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	// get/set Y
	Coord_t getY() const  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }
	
	// get packet's debug string
	string toString() const ;

private :

	// SkillType
	SkillType_t m_SkillType;

	// Client EffectID
	CEffectID_t m_CEffectID;

	// Coord X
	Coord_t m_X;

	// Coord Y
	Coord_t m_Y;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToTileFactory;
//
// Factory for CGSkillToTile
//
//////////////////////////////////////////////////////////////////////

class CGSkillToTileFactory : public PacketFactory {

public:
	
	// constructor
	CGSkillToTileFactory()  {}
	
	// destructor
	virtual ~CGSkillToTileFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGSkillToTile(); }

	// get packet name
	string getPacketName() const  { return "CGSkillToTile"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SKILL_TO_TILE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType + szCEffectID + szCoord + szCoord; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSkillToTileHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSkillToTileHandler {

public:

	// execute packet's handler
	static void execute(CGSkillToTile* pCGSkillToTile, Player* pPlayer) ;

};

#endif
