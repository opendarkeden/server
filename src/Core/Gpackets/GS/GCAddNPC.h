//--------------------------------------------------------------------------------
// 
// Filename    : GCAddNPC.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_NPC_H__
#define __GC_ADD_NPC_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class GCAddNPC;
//
// 시야 안에 NPC 가 들어왔을 경우, 이 패킷에 NPC 정보를 담아서 전송받는다.
//
//--------------------------------------------------------------------------------

class GCAddNPC : public Packet 
{

public :
	
	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
			
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_NPC; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddNPCPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID 
			+ szBYTE + m_Name.size() + szNPCID
			+ szSpriteType 
			+ szColor + szColor
			+ szCoord + szCoord + szDir;
	}

	// get packet's name
	string getPacketName() const throw() { return "GCAddNPC"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set name
	string getName() const throw() { return m_Name; }
	void setName(string name) throw() { m_Name = name; }

	// get/set NPC id
	NPCID_t getNPCID(void) const throw() { return m_NPCID;}
	void setNPCID(NPCID_t NPCID) throw() { m_NPCID = NPCID;}

	// get/set sprite type
	SpriteType_t getSpriteType() const throw() { return m_SpriteType; }
	void setSpriteType(SpriteType_t spriteType) throw() { m_SpriteType = spriteType; }

	// get/set main color
	Color_t getMainColor() const throw() { return m_MainColor; }
	void setMainColor(Color_t color) throw() { m_MainColor = color; }

	// get/set sub color
	Color_t getSubColor() const throw() { return m_SubColor; }
	void setSubColor(Color_t color) throw() { m_SubColor = color; }

	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	// get/set Dir
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }

private :
	
	// 존 레벨에서 유니크한 아이디로 객체 구분을 위해서 사용한다.
	ObjectID_t m_ObjectID;

	// NPC의 이름
	string m_Name;

	// NPC의 아이디(오브젝트 아이디가 아니다.)
	NPCID_t m_NPCID;

	// 스프라이트 타입
	SpriteType_t m_SpriteType;

	// 색깔 정보
	Color_t m_MainColor;
	Color_t m_SubColor;

	// X, Y 및 방향
	Coord_t m_X;
	Coord_t m_Y;
	Dir_t m_Dir;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddNPCFactory;
//
// Factory for GCAddNPC
//
//////////////////////////////////////////////////////////////////////

class GCAddNPCFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddNPC(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddNPC"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_NPC; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddNPCPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{
		return szObjectID 
			+ szBYTE + 20 + szNPCID
			+ szSpriteType 
			+ szColor + szColor
			+ szCoord + szCoord + szDir;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddNPCHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddNPCHandler {

public :

	// execute packet's handler
	static void execute(GCAddNPC* pPacket, Player* pPlayer) throw(Error);

};

#endif
