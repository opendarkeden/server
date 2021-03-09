//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectRegenZone.h 
// Written By  : excel96
// Description : 
// 슬레이어가 개인용 포탈을 이용해 다른 곳으로 이동하고자 할 때 보내는 패킷
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_REGEN_ZONE_H__
#define __CG_SELECT_REGEN_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectRegenZone;
//////////////////////////////////////////////////////////////////////////////

class CGSelectRegenZone : public Packet 
{
public:
    CGSelectRegenZone() {};
    virtual ~CGSelectRegenZone() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_CG_SELECT_REGEN_ZONE; }
	PacketSize_t getPacketSize() const  { return szBYTE; }
	string getPacketName() const  { return "CGSelectRegenZone"; }
	string toString() const ;

public:
	BYTE getRegenZoneID() const { return m_RegenZoneID; }
	void setRegenZoneID(BYTE RegenZoneID ) { m_RegenZoneID = RegenZoneID; }
private:
	BYTE m_RegenZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectRegenZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSelectRegenZoneFactory : public PacketFactory 
{
	Packet* createPacket()  { return new CGSelectRegenZone(); }
	string getPacketName() const  { return "CGSelectRegenZone"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_CG_SELECT_REGEN_ZONE; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectRegenZoneHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSelectRegenZoneHandler 
{
public:
	static void execute(CGSelectRegenZone* pCGSelectRegenZone, Player* pPlayer) ;
};

#endif
