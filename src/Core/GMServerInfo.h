//----------------------------------------------------------------------
// 
// Filename    : GMServerInfo.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GM_SERVER_INFO_H__
#define __GM_SERVER_INFO_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"

typedef struct _ZONEUSERDATA {
	ZoneID_t ZoneID;
	WORD UserNum;

} ZONEUSERDATA;

//----------------------------------------------------------------------
//
// class GMServerInfo;
//
// Packet sent from the login server so a GM client knows which world/server
// to connect to and how many players are in each zone.
//
// *CAUTION*
// Keep the mapping between character slots and character IDs consistent.
// After the client selects a character in CLSelectPC, CGConnect uses the
// character ID immediately to load it.
//
//----------------------------------------------------------------------

class GMServerInfo : public DatagramPacket {

public :
	GMServerInfo() ;
	~GMServerInfo() noexcept;
	
	// Initialize the packet by reading data from the datagram payload.
	void read(Datagram & iDatagram) ;
		    
	// Serialize the packet into the datagram payload.
	void write(Datagram & oDatagram) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GM_SERVER_INFO; }
	
	// get packet name
	string getPacketName() const  { return "GMServerInfo"; }
	
	PacketSize_t getPacketSize () const  { return szWorldID + szBYTE + m_ZoneCount*(szBYTE+szDWORD); }

	// get packet's debug string
	string toString() const ;

public:

	// get/set playerID
	WorldID_t getWorldID() const  { return m_WorldID; }
	void setWorldID(WorldID_t WorldID)  { m_WorldID= WorldID; }
	
	// get/set playerID
	BYTE getServerID() const  { return m_ServerID; }
	void setServerID(BYTE ServerID)  { m_ServerID= ServerID; }
	
	BYTE getZoneUserCount(void) const  { return m_ZoneCount; }

	void addZoneUserData(ZoneID_t ZoneID, DWORD value) ;

	void popZoneUserData(ZONEUSERDATA& rData) ;

	void clearList(void)  { m_ZoneCount = 0; m_ZoneUserList.clear(); }

private :

	// WorldID
	WorldID_t m_WorldID;

	// ServerID
	BYTE m_ServerID;

	BYTE            m_ZoneCount;
	list<ZONEUSERDATA> m_ZoneUserList;

	// Client IP (reference only; stored elsewhere)

};


//////////////////////////////////////////////////////////////////////
//
// class GMServerInfoFactory;
//
// Factory for GMServerInfo
//
//////////////////////////////////////////////////////////////////////

class GMServerInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GMServerInfo(); }

	// get packet name
	string getPacketName() const  { return "GMServerInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GM_SERVER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// Use GMServerInfoPacketMaxSize if that constant is defined.
	PacketSize_t getPacketMaxSize() const  { return szWorldID + szBYTE + 255*(szBYTE+szDWORD); }

};


//////////////////////////////////////////////////////////////////////
//
// class GMServerInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GMServerInfoHandler {
	
public :

	// execute packet's handler
	static void execute(GMServerInfo* pPacket) ;

};

#endif
