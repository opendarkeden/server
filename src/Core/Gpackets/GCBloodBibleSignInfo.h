//////////////////////////////////////////////////////////////////////////////
// Filename    : GCBloodBibleSignInfo.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_BIBLE_SIGN_INFO_H__
#define __GC_BLOOD_BIBLE_SIGN_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "BloodBibleSignInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleSignInfo;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleSignInfo : public Packet
{
public:
	GCBloodBibleSignInfo()  { }
	virtual ~GCBloodBibleSignInfo() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_BLOOD_BIBLE_SIGN_INFO; }
	PacketSize_t getPacketSize() const  { return m_pInfo->getSize(); }
	string getPacketName() const  { return "GCBloodBibleSignInfo"; }
	string toString() const ;

public:
	BloodBibleSignInfo* getSignInfo() const { return m_pInfo; }
	void setSignInfo(BloodBibleSignInfo* pInfo) { m_pInfo = pInfo; }

private:
	BloodBibleSignInfo*	m_pInfo;
};

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleSignInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleSignInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCBloodBibleSignInfo(); }
	string getPacketName() const  { return "GCBloodBibleSignInfo"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_BLOOD_BIBLE_SIGN_INFO; }
	PacketSize_t getPacketMaxSize() const 
	{
		return BloodBibleSignInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleSignInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleSignInfoHandler 
{
public:
	static void execute(GCBloodBibleSignInfo* pPacket, Player* pPlayer) ;
};

#endif
