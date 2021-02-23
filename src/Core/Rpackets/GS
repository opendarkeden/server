//----------------------------------------------------------------------
// 
// Filename    : RCSay.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __RC_SAY_H__
#define __RC_SAY_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class RCSay;
//
// 내가 다른 클라이언트에게 말하는 패킷
//
//----------------------------------------------------------------------

class RCSay : public DatagramPacket {

public :
	
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( Datagram & iDatagram ) throw ( ProtocolException , Error );
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write ( Datagram & oDatagram ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_RC_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szBYTE + m_Name.size()
				+ szBYTE + m_Message.size();			
	}

		// get packet name
		string getPacketName () const throw () { return "RCSay"; }
		
		// get packet's debug string
		string toString () const throw ();

public :

	// get/set Name
	string getName () const throw () { return m_Name; }
	void setName ( string msg ) throw () { m_Name = msg; }

	// get/set Message
	string getMessage () const throw () { return m_Message; }
	void setMessage ( string msg ) throw () { m_Message = msg; }
	
	
private :
	string m_Name;
	string m_Message;	
};


//////////////////////////////////////////////////////////////////////
//
// class RCSayFactory;
//
// Factory for RCSay
//
//////////////////////////////////////////////////////////////////////

class RCSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new RCSay(); }

		// get packet name
		string getPacketName () const throw () { return "RCSay"; }
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_RC_SAY; }

	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return szBYTE + 128 + szBYTE + 20;			
	}

};


//////////////////////////////////////////////////////////////////////
//
// class RCSayHandler;
//
//////////////////////////////////////////////////////////////////////

class RCSayHandler {
	
public :

	// execute packet's handler
	static void execute ( RCSay * pPacket ) throw ( ProtocolException , Error );

};

#endif
