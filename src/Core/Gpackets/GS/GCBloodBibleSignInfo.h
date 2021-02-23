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
	GCBloodBibleSignInfo() throw() { }
	virtual ~GCBloodBibleSignInfo() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_BLOOD_BIBLE_SIGN_INFO; }
	PacketSize_t getPacketSize() const throw() { return m_pInfo->getSize(); }
	string getPacketName() const throw() { return "GCBloodBibleSignInfo"; }
	string toString() const throw();

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
	Packet* createPacket() throw() { return new GCBloodBibleSignInfo(); }
	string getPacketName() const throw() { return "GCBloodBibleSignInfo"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_BLOOD_BIBLE_SIGN_INFO; }
	PacketSize_t getPacketMaxSize() const throw()
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
	static void execute(GCBloodBibleSignInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
