//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRequestedIP.h 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_REQUESTED_IP_H__
#define __GC_REQUESTED_IP_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCRequestedIP;
//////////////////////////////////////////////////////////////////////////////

class GCRequestedIP : public Packet
{
public:
	GCRequestedIP () throw ();
	~GCRequestedIP () throw ();
	
public:
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
    PacketID_t getPacketID () const throw () { return PACKET_GC_REQUESTED_IP; }
	string getPacketName () const throw () { return "GCRequestedIP"; }
	PacketSize_t getPacketSize () const throw () { return szBYTE + szuint + m_Name.size() + 4; }
	string toString () const throw ();

public:
	string getName() const throw() { return m_Name;}
	void setName( const char* pName) throw(Error) { m_Name = pName;}

	void setIP(IP_t ip) throw() { m_IP = ip; }
	IP_t getIP() const throw() { return m_IP; }

	void setPort(uint port) throw() { m_Port = port; }
	uint getPort() const throw() { return m_Port; }

protected:
	string m_Name;
	IP_t   m_IP;
	uint   m_Port;
};

//////////////////////////////////////////////////////////////////////////////
// class GCRequestedIPFactory;
//////////////////////////////////////////////////////////////////////////////

class GCRequestedIPFactory : public PacketFactory 
{
public:
	Packet * createPacket () throw () { return new GCRequestedIP(); }
	string getPacketName () const throw () { return "GCRequestedIP"; }
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_REQUESTED_IP; }
	PacketSize_t getPacketMaxSize () const throw () { return szBYTE + szuint + 10 + 4;}
};

//////////////////////////////////////////////////////////////////////////////
// class GCRequestedIPHandler;
//////////////////////////////////////////////////////////////////////////////

class GCRequestedIPHandler 
{
public:
	static void execute ( GCRequestedIP * pGCRequestedIP , Player * pPlayer ) throw ( Error );
};

#endif
