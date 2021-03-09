//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRequestFailed.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_REQUEST_FAILED_H__
#define __GC_REQUEST_FAILED_H__

#include "Packet.h"
#include "PacketFactory.h"

enum
{
	REQUEST_FAILED_NULL,
	REQUEST_FAILED_IP,
};

//////////////////////////////////////////////////////////////////////////////
// class GCRequestFailed
//////////////////////////////////////////////////////////////////////////////

class GCRequestFailed : public Packet 
{
public:
	GCRequestFailed()	{ m_Code = REQUEST_FAILED_NULL; }
    ~GCRequestFailed() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_REQUEST_FAILED; }
	PacketSize_t getPacketSize() const  { return szBYTE + szBYTE + m_Name.size(); }
	string getPacketName() const  { return "GCRequestFailed"; }
	string toString() const ;
	
public:
	BYTE getCode(void) const { return m_Code;}
	void setCode(WORD code) { m_Code = code;}

	string getName(void) const { return m_Name; }
	void setName(const string& name) { m_Name = name; }

private: 
	BYTE   m_Code;
	string m_Name;
};

//////////////////////////////////////////////////////////////////////////////
// class GCRequestFailedFactory;
//////////////////////////////////////////////////////////////////////////////

class GCRequestFailedFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCRequestFailed(); }
	string getPacketName() const  { return "GCRequestFailed"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_REQUEST_FAILED; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szBYTE + 10; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCRequestFailedHandler
//////////////////////////////////////////////////////////////////////////////

class GCRequestFailedHandler 
{
public:
	static void execute(GCRequestFailed* pPacket, Player* pPlayer) ;
};

#endif
