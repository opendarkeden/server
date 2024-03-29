//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddBat.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_BAT_H__
#define __GC_ADD_BAT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddBat;
//
// 시야 안에 Bat 가 들어왔을 경우, 이 패킷에 Bat 정보를 담아서 전송받는다.
//////////////////////////////////////////////////////////////////////////////

class GCAddBat : public Packet 
{
public:
    GCAddBat() {};
    ~GCAddBat() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ADD_BAT; }
	PacketSize_t getPacketSize() const  
	{ 
		return szObjectID 
			+ szBYTE + m_Name.size() 
			//+ szSpriteType 
			//+ szColor + szColor
			+ szItemType
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ szColor
			;
	}
	string getPacketName() const  { return "GCAddBat"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	string getName() const  { return m_Name; }
	void setName(string name)  { m_Name = name; }

	/*
	// get/set sprite type
	SpriteType_t getSpriteType() const  { return m_SpriteType; }
	void setSpriteType(SpriteType_t spriteType)  { m_SpriteType = spriteType; }

	// get/set main color
	Color_t getMainColor() const  { return m_MainColor; }
	void setMainColor(Color_t color)  { m_MainColor = color; }

	// get/set sub color
	Color_t getSubColor() const  { return m_SubColor; }
	void setSubColor(Color_t color)  { m_SubColor = color; }
	*/

	// get/set X
	Coord_t getX() const  { return m_X; }
	void setXYDir(Coord_t x, Coord_t y, Dir_t Dir)  { m_X = x; m_Y = y; m_Dir = Dir;}
	
	// get/set Y
	Coord_t getY() const  { return m_Y; }

	// get/set Dir
	Dir_t getDir() const  { return m_Dir; }

	// get /set MaxHP
	HP_t getMaxHP() const  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP)  { m_MaxHP = MaxHP; }

	// get /set CurrentHP
	HP_t getCurrentHP() const  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP)  { m_CurrentHP = CurrentHP; }

	// get / set ItemType
    ItemType_t getItemType() const  { return m_ItemType; }
    void setItemType(ItemType_t ItemType)  { m_ItemType = ItemType; }

	// get/set GuildID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID(GuildID_t GuildID)  { m_GuildID = GuildID; }

	Color_t getColor() const  { return m_Color; }
	void setColor(Color_t color)  { m_Color = color; }

private:
	ObjectID_t   m_ObjectID;
	string       m_Name;       // Bat의 이름
	
	/*
	SpriteType_t m_SpriteType; // 스프라이트 타입
	Color_t      m_MainColor;  // 메인 칼라
	Color_t      m_SubColor;   // 서브 칼라
	*/

	// 변신 아이템의 종류
	ItemType_t	 m_ItemType;

	Coord_t      m_X;          // X
	Coord_t      m_Y;          // Y
	Dir_t        m_Dir;        // Direction
	HP_t         m_CurrentHP;  // current hp
	HP_t         m_MaxHP;      // max hp
	GuildID_t	 m_GuildID;    // GuildID
	Color_t	 	 m_Color;      // Color
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddBatFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddBatFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddBat(); }
	string getPacketName() const  { return "GCAddBat"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ADD_BAT; }
	PacketSize_t getPacketMaxSize() const  
	{
		return szObjectID 
			+ szBYTE + 20 
			+ szItemType
			//+ szSpriteType 
			//+ szColor + szColor
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ szColor
			;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddBatHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddBatHandler 
{
public:
	static void execute(GCAddBat* pPacket, Player* pPlayer) ;

};

#endif
