//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestIP.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_IP_H__
#define __CG_REQUEST_IP_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestIP;
// client에서 server로 누군가의 IP를 요청하는데
// 누군가가 근처에 있다면 objectID로 요청하고
// 아니면.. 캐릭터 이름으로 요청한다.
//////////////////////////////////////////////////////////////////////////////

class CGRequestIP : public Packet
{
public:
	CGRequestIP () ;
	~CGRequestIP () ;
	
public:
    void read (SocketInputStream & iStream ) ;
    void write (SocketOutputStream & oStream ) const ;
	void execute (Player * pPlayer ) ;
    PacketID_t getPacketID () const  { return PACKET_CG_REQUEST_IP; }
	PacketSize_t getPacketSize () const  { return szBYTE + m_Name.size(); }
	string getPacketName () const  { return "CGRequestIP"; }
	string toString () const ;

public:
	string getName() const  { return m_Name; }
	void setName(const char* pName)  { m_Name = pName;}

protected:
	string			m_Name;
};

//////////////////////////////////////////////////////////////////////////////
// class CGRequestIPFactory;
//////////////////////////////////////////////////////////////////////////////

class CGRequestIPFactory : public PacketFactory 
{
public:
	Packet * createPacket ()  { return new CGRequestIP(); }
	string getPacketName () const  { return "CGRequestIP"; }
	PacketID_t getPacketID () const  { return Packet::PACKET_CG_REQUEST_IP; }
	PacketSize_t getPacketMaxSize () const  { return szBYTE + 10;}
};

//////////////////////////////////////////////////////////////////////////////
// class CGRequestIPHandler;
//////////////////////////////////////////////////////////////////////////////

class CGRequestIPHandler 
{
public:
	static void execute (CGRequestIP * pCGRequestIP , Player * pPlayer ) ;
};


#endif
