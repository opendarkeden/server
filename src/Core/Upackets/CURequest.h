//--------------------------------------------------------------------------------
// 
// Filename    : CURequest.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_REQUEST_H__
#define __CU_REQUEST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Resource.h"

//--------------------------------------------------------------------------------
//
// class CURequest;
//
// 
// 
//
//--------------------------------------------------------------------------------

class CURequest : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
	// 소켓으로부터 직접 데이타를 읽어서 패킷을 초기화한다.
    void read ( Socket * pSocket ) throw ( ProtocolException , Error );

    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_CU_REQUEST; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return m_Resource.getSize(); }

	// 임시 코드당. -_-;
	static PacketSize_t getPacketMaxSize () throw () { return Resource::getMaxSize(); }

	// get packet name
	string getPacketName () const throw () { return "CURequest"; }
	
	// get packet's debug string
	string toString () const throw ();


public :

	// get/set resource
	const Resource & getResource () const throw () { return m_Resource; }
	void setResource ( const Resource & resource ) throw () { m_Resource = resource; }


private :

	// resource
	Resource m_Resource;	

};


//--------------------------------------------------------------------------------
//
// class CURequestFactory;
//
// Factory for CURequest
//
//--------------------------------------------------------------------------------

class CURequestFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new CURequest(); }

	// get packet name
	string getPacketName () const throw () { return "CURequest"; }
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CU_REQUEST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return Resource::getMaxSize(); 
	}

};


//--------------------------------------------------------------------------------
//
// class CURequestHandler;
//
//--------------------------------------------------------------------------------

class CURequestHandler {

public :

	// execute packet's handler
	static void execute ( CURequest * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
