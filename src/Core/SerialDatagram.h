//////////////////////////////////////////////////////////////////////
//
// Filename    : SerialSerialDatagram.h
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __SERIAL_DATAGRAM_H__
#define __SERIAL_DATAGRAM_H__

#include "Types.h"
#include "Exception.h"
#include "SocketAPI.h"

#if __LINUX__
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
#elif __WINDOWS__
	#include <winsock.h>
#endif

// forward declaration
class SerialDatagramPacket;

//////////////////////////////////////////////////////////////////////
//
// class SerialDatagram;
//
// UDP 소켓으로부터 입력받거나 출력할 데이타의 집합이다.
// 각 SerialDatagram은 보낼 곳 또는 보낸 곳의 주소를 가지고 있다.
//
//////////////////////////////////////////////////////////////////////

class SerialDatagram {

public :

	// constructor
	SerialDatagram () throw ();

	// destructor
	~SerialDatagram () throw ();

	// read SerialDatagramPacket from datagram's internal buffer
	void read (char* buf, uint len) throw (Error);
	void read (string & str, uint len) throw (Error);
	void read (SerialDatagramPacket* & pPacket) throw (ProtocolException, Error);

	void read (char   & buf) throw (Error) { read((char*)&buf, szchar  ); }
    void read (uchar  & buf) throw (Error) { read((char*)&buf, szuchar ); }
    void read (short  & buf) throw (Error) { read((char*)&buf, szshort ); }
    void read (ushort & buf) throw (Error) { read((char*)&buf, szushort); }
    void read (int    & buf) throw (Error) { read((char*)&buf, szint   ); }
    void read (uint   & buf) throw (Error) { read((char*)&buf, szuint  ); }
    void read (long   & buf) throw (Error) { read((char*)&buf, szlong  ); }
    void read (ulong  & buf) throw (Error) { read((char*)&buf, szulong ); }

	// write SerialDatagramPacket into datagram's internal buffer
	void write (const char* buf, uint len) throw (Error);
	void write (const string & buf) throw (Error);
	void write (const SerialDatagramPacket* pPacket) throw (ProtocolException, Error);

	void write (char   buf) throw (Error) { write((char*)&buf, szchar  ); }
    void write (uchar  buf) throw (Error) { write((char*)&buf, szuchar ); }
    void write (short  buf) throw (Error) { write((char*)&buf, szshort ); }
    void write (ushort buf) throw (Error) { write((char*)&buf, szushort); }
    void write (int    buf) throw (Error) { write((char*)&buf, szint   ); }
    void write (uint   buf) throw (Error) { write((char*)&buf, szuint  ); }
    void write (long   buf) throw (Error) { write((char*)&buf, szlong  ); }
    void write (ulong  buf) throw (Error) { write((char*)&buf, szulong ); }

	// get data
	char* getData () throw () { return m_Data; }

	// set data
	void setData (char* data, uint len) throw (Error);
	void setData (uint len) throw (Error); 
	
	// get length
	uint getLength () const throw () { return m_Length; }

	// get address
	SOCKADDR* getAddress () throw () { return (SOCKADDR*)&m_SockAddr; }

	// set address
	void setAddress (SOCKADDR_IN* pSockAddr) throw (Error);

	// get host
	string getHost () const throw () { return string(inet_ntoa(m_SockAddr.sin_addr)); }

	// set host
	void setHost (const string & host) throw () { m_SockAddr.sin_addr.s_addr = inet_addr(host.c_str()); }

	// get port 
	uint getPort () const throw () { return ntohs(m_SockAddr.sin_port); }

	// set port
	void setPort (uint port) throw () { m_SockAddr.sin_port = htons(port); }

	string toString () const throw ();

private :

	// buffer length
	uint m_Length;

	// reading/writing offset
	uint m_InputOffset;
	uint m_OutputOffset;

	// internal buffer
	char* m_Data;

	// socket address
	SOCKADDR_IN m_SockAddr;

};

#endif
