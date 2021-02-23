//////////////////////////////////////////////////////////////////////
// 
// Filename    : SerialDatagramPacket.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SERIAL_DATAGRAM_PACKET_H__
#define __SERIAL_DATAGRAM__PACKET_H__

// include files
#include "Packet.h"
#include "SerialDatagram.h"
#include "SocketAPI.h"


//////////////////////////////////////////////////////////////////////
//
// class SerialDatagramPacket;
//
// 서버간의 UDP 통신에 사용되는 패킷의 베이스 클래스이다.
// 기본적으로 이 패킷들은 보낸 쪽의 주소(address)와 포트(port)를 저장
// 하고 있어야 하며, SerialDatagram에 읽고 쓰는 메쏘드를 override 해야 하기
// 때문에 도입되었다.
//
//////////////////////////////////////////////////////////////////////

class SerialDatagramPacket : public Packet {
	
public :
	
	// destructor
	virtual ~SerialDatagramPacket () throw () {}

	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	// 데이터그램 패킷이 TCP 소켓으로 전송되어 왔다면 프로토콜 에러로 간주한다.
	virtual void read (SocketInputStream & iStream) throw (ProtocolException, Error) 
	{ 
		throw ProtocolException("datagram packet from TCP socket"); 
	}

	// SerialDatagram 객체에서 데이터를 읽어서 패킷을 초기화한다.
	virtual void read (SerialDatagram & iDatagram) throw (ProtocolException, Error) = 0;
	
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	// 데이터그램 패킷을 TCP 소켓으로 출력할 수 없다.
	virtual void write (SocketOutputStream & oStream) const throw (ProtocolException, Error)
	{ 
		throw Error("cannot write datagram-packet to TCP-socket-stream"); 
	}

	// SerialDatagram 객체로 패킷의 바이너리 이미지를 보낸다.
	virtual void write (SerialDatagram & oDatagram) const throw (ProtocolException, Error) = 0;
	
	// execute packet's handler
	virtual void execute (Player* pPlayer) throw (ProtocolException, Error) = 0;
	
	// get packet's SerialDatagramPacketID	
	virtual PacketID_t getPacketID () const throw () = 0;

	// get packet's body size
	virtual PacketSize_t getPacketSize () const throw () = 0;

	// get packet's name
	virtual string getPacketName () const throw () = 0;
	
	// get packet's debug string
	virtual string toString () const throw () = 0;

	// get/set host
	string getHost () const throw () { return m_Host; }
	void setHost (string host) throw () { m_Host = host; }

	// get/set port
	uint getPort () const throw () { return m_Port; }
	void setPort (uint port) throw () { m_Port = port; }

	// get/set serial number
	uint getSerial() const throw() { return m_Serial; }
	void setSerial( uint serial ) throw() { m_Serial = serial; }
	

protected :

	// sender's host
	string m_Host;

	// sender's port
	uint m_Port;

	// Packet Serial Number
	uint m_Serial;
	
};

#endif
