//////////////////////////////////////////////////////////////////////
// 
// Filename    : SocketInputStream.h 
// Written by  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////
//
// *Reiot's Notes*
//
// 시스템에서 가장 빈번하게 사용되는 클래스중의 하나이다.
// 속도에 무지막지한 영향을 미치므로, 만일 좀더 속도를 보강하고
// 싶다면, exception을 빼고 re-write 하라. 
//
// 현재 nonblocking 이 굉장히-억수로-졸라 많이 발생한다고 했을때,
// 이것이 NonBlockingIOException으로 wrapping될때 overhead가 발생할
// 확률이 높다고 추측된다.
//
//////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_INPUT_STREAM_H__
#define __SOCKET_INPUT_STREAM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Socket.h"

// constant definitions
const uint DefaultSocketInputBufferSize = 81920;

// forward declaration
class Packet;

//////////////////////////////////////////////////////////////////////
//
// class SocketInputStream
//
//////////////////////////////////////////////////////////////////////

class SocketInputStream {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketInputStream (Socket* sock, uint BufferSize = DefaultSocketInputBufferSize) throw (Error);
	
	// destructor
	virtual ~SocketInputStream () throw (Error);

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// read data from stream (input buffer)
	uint read (char* buf, uint len) throw (ProtocolException, Error);
	uint read (string & str, uint len) throw (ProtocolException, Error);
	void readPacket (Packet* p) throw (ProtocolException, Error);

	template<typename T>
		uint read( T& buf ) throw (ProtocolException, Error);

/*	uint read (bool   & buf) throw (ProtocolException, Error) { return read((char*)&buf, szbool  ); }
	uint read (char   & buf) throw (ProtocolException, Error) { return read((char*)&buf, szchar  ); }
	uint read (uchar  & buf) throw (ProtocolException, Error) { return read((char*)&buf, szuchar ); }
	uint read (short  & buf) throw (ProtocolException, Error) { return read((char*)&buf, szshort ); }
	uint read (ushort & buf) throw (ProtocolException, Error) { return read((char*)&buf, szushort); }
	uint read (int    & buf) throw (ProtocolException, Error) { return read((char*)&buf, szint   ); }
	uint read (uint   & buf) throw (ProtocolException, Error) { return read((char*)&buf, szuint  ); }
	uint read (long   & buf) throw (ProtocolException, Error) { return read((char*)&buf, szlong  ); }
	uint read (ulong  & buf) throw (ProtocolException, Error) { return read((char*)&buf, szulong ); }
*/
	// peek data from stream (input buffer)
	bool peek (char* buf, uint len) throw (ProtocolException, Error);
	
	// skip data from stream (input buffer)
	void skip (uint len) throw (ProtocolException, Error);
	
	// fill stream (input buffer) from socket
	uint fill () throw (IOException, Error);
	uint fill_RAW () throw (IOException, Error);

	// resize buffer
	void resize (int size) throw (IOException, Error);
	
	// get buffer length
	uint capacity () const throw () { return m_BufferLen; }
	
	// get data length in buffer
	uint length () const throw ();
	uint size () const throw () { return length(); }

	// check if buffer is empty
	bool isEmpty () const throw () { return m_Head == m_Tail; }

	// get debug string
	string toString () const throw ();


//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	
	// socket
	Socket* m_pSocket;
	
	// buffer
	char* m_Buffer;
	
	// buffer length
	uint m_BufferLen;
	
	// buffer head/tail
	uint m_Head;
	uint m_Tail;
//add by viva 2008-12-31
//public :
	//WORD m_EncryptKey;
	//BYTE* m_HashTable;
	//void setKey(WORD EncryptKey, BYTE* HashTable) throw() {m_EncryptKey = EncryptKey; m_HashTable = HashTable; }
	//WORD EncryptData(WORD EncryptKey, char* buf, int len) throw();
//end
};


//////////////////////////////////////////////////////////////////////
//
// read data from input buffer
//
//////////////////////////////////////////////////////////////////////
template<typename T>
uint SocketInputStream::read ( T& buf ) 
	throw ( ProtocolException , Error )
{
	uint len = (uint)sizeof(T);

	// 요청한 만큼의 데이타가 버퍼내에 존재하지 않을 경우 예외를 던진다.
	// 만약 모든 read 가 peek() 로 체크한 후 호출된다면, 아래 if-throw 는 
	// 중복된 감이 있다. 따라서, 코멘트로 처리해도 무방하다.
	// 단 아래 코드를 코멘트처리하면, 바로 아래의 if-else 를 'if'-'else if'-'else'
	// 로 수정해줘야 한다.
	if ( len > length() )
		throw InsufficientDataException( len - length() );
	
	if ( m_Head < m_Tail )	// normal order
	{
		//
        //    H   T
        // 0123456789
        // ...abcd...
        //
		buf = *(T*)(m_Buffer+m_Head);

	}
	else					// reversed order ( m_Head > m_Tail )
	{
		
        //
        //     T  H
        // 0123456789
        // abcd...efg
        //
		uint rightLen = m_BufferLen - m_Head;
		if ( len <= rightLen )
		{
			buf = *(T*)(m_Buffer+m_Head);
		}
		else
		{
			memcpy( (char*)&buf , &m_Buffer[m_Head] , rightLen );
			memcpy( ((char*)(&buf)+rightLen), m_Buffer, len - rightLen );
		}
	}

	m_Head = ( m_Head + len ) % m_BufferLen;
	
	return len;
		
//	__END_CATCH
}

#endif
