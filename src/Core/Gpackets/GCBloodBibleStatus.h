//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodBibleStatus.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////
//
// STORAGE_CORPSE  ItemType, ZoneID, Race, X, Y  최초에, 옮겨졌을때: load(), returnBloodBible()  
// STORAGE_INVENTORY  ItemType, ZoneID, OwnerName, Race, X, Y  누군가가 주웠을때: CGAddZoneToInventory  
// STORAGE_MOUSE  ItemType, ZoneID, OwnerName, Race, X, Y  누군가가 주웠을때: CGAddZoneToMouse  
// STORAGE_ZONE  ItemType, ZoneID, X, Y  바닥에 떨어졌을때: CGAddMouseToZone, CGDissectionCorpse  
//
//////////////////////////////////////////////////////////////////////


#ifndef __GC_BLOOD_BIBLE_STATUS_H__
#define __GC_BLOOD_BIBLE_STATUS_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodBibleStatus;
//
// 게임 서버가 특정 플레이어의 BloodBibleStatus 를 다른 플레이어들에게 브로드캐스트
// 할 때 전송하는 패킷이다. 내부에 캐릭터명과 BloodBibleStatus 스트링을 데이타
// 필드로 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class GCBloodBibleStatus : public Packet {

public :
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_BLOOD_BIBLE_STATUS; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szItemType 
				+ szZoneID 
				+ szStorage 
				+ szBYTE + m_OwnerName.size() 
				+ szRace 
				+ szRace 
				+ szZoneCoord + szZoneCoord;
	}

	// get packet name
	string getPacketName() const throw() { return "GCBloodBibleStatus"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set text color
	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType( ItemType_t itemType ) throw() { m_ItemType = itemType; }

	// get/set text color
	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID( ZoneID_t zoneID ) throw() { m_ZoneID = zoneID; }

	// get/set text color
	Storage_t getStorage() const throw() { return m_Storage; }
	void setStorage( Storage_t storage ) throw() { m_Storage = storage; }

	// get/set chatting message
	const string& getOwnerName() const throw() { return m_OwnerName; }
	void setOwnerName(const string & OwnerName) throw() { m_OwnerName = OwnerName; }

	// get/set text color
	Race_t getRace() const throw() { return m_Race; }
	void setRace( Race_t race ) throw() { m_Race = race; }

	// get/set text color
	Race_t getShrineRace() const throw() { return m_ShrineRace; }
	void setShrineRace( Race_t race ) throw() { m_ShrineRace = race; }

	// get/set text color
	ZoneCoord_t getX() const throw() { return m_X; }
	void setX( ZoneCoord_t x ) throw() { m_X = x; }

	// get/set text color
	ZoneCoord_t getY() const throw() { return m_Y; }
	void setY( ZoneCoord_t y ) throw() { m_Y = y; }

private :
	
	ItemType_t 		m_ItemType;	// 피의 성서 종류

	ZoneID_t		m_ZoneID; 

	Storage_t 		m_Storage;
	string 			m_OwnerName;
	Race_t			m_Race;
	Race_t			m_ShrineRace;
	ZoneCoord_t		m_X;
	ZoneCoord_t		m_Y; 
};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodBibleStatusFactory;
//
// Factory for GCBloodBibleStatus
//
//////////////////////////////////////////////////////////////////////

class GCBloodBibleStatusFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCBloodBibleStatus(); }

	// get packet name
	string getPacketName() const throw() { return "GCBloodBibleStatus"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_BLOOD_BIBLE_STATUS; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCBloodBibleStatusPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szItemType 
				+ szZoneID 
				+ szStorage 
				+ szBYTE + 255
				+ szRace 
				+ szRace 
				+ szZoneCoord + szZoneCoord;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodBibleStatusHandler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodBibleStatusHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCBloodBibleStatus* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
