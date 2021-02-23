//////////////////////////////////////////////////////////////////////
// 
// SocketOutputStream.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_OUTPUT_STREAM_H__
#define __SOCKET_OUTPUT_STREAM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Socket.h"

// constant definitions
const unsigned int DefaultSocketOutputBufferSize = 81920;

// forward declaration
class Packet;

//////////////////////////////////////////////////////////////////////
//
// class SocketOutputStream
//
//////////////////////////////////////////////////////////////////////

class SocketOutputStream {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketOutputStream (Socket* sock, uint BufferSize = DefaultSocketOutputBufferSize) throw (Error);
	
	// destructor
	virtual ~SocketOutputStream () throw (Error);

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// write data to stream (output buffer)
	// *CAUTION*
	// string 을 버퍼에 writing 할 때, 자동으로 size 를 앞에 붙일 수도 있다.
	// 그러나, string 의 크기를 BYTE/WORD 중 어느 것으로 할 건지는 의문이다.
	// 패킷의 크기는 작을 수록 좋다는 정책하에서 필요에 따라서 string size 값을
	// BYTE 또는 WORD 를 수동으로 사용하도록 한다.
	uint write (const char* buf, uint len) throw (Error);
	uint write (const string & buf) throw (Error) { return write(buf.c_str(),buf.size()); }
	void writePacket (const Packet* pPacket) throw (ProtocolException, Error);
	
	template<typename T>
		uint write( T buf ) throw (Error);
/*	uint write (bool   buf) throw (ProtocolException, Error) { return write((const char*)&buf, szbool  ); }
	uint write (char   buf) throw (ProtocolException, Error) { return write((const char*)&buf, szchar  ); }
	uint write (uchar  buf) throw (ProtocolException, Error) { return write((const char*)&buf, szuchar ); }
	uint write (short  buf) throw (ProtocolException, Error) { return write((const char*)&buf, szshort ); }
	uint write (ushort buf) throw (ProtocolException, Error) { return write((const char*)&buf, szushort); }
	uint write (int    buf) throw (ProtocolException, Error) { return write((const char*)&buf, szint   ); }
	uint write (uint   buf) throw (ProtocolException, Error) { return write((const char*)&buf, szuint  ); }
	uint write (long   buf) throw (ProtocolException, Error) { return write((const char*)&buf, szlong  ); }
	uint write (ulong  buf) throw (ProtocolException, Error) { return write((const char*)&buf, szulong ); }
*/
	// flush stream (output buffer) to socket
	uint flush () throw (IOException, ProtocolException, InvalidProtocolException, Error);

	// resize buffer 
	void resize (int size) throw (IOException, Error);

	// get buffer length
	int capacity () const throw () { return m_BufferLen; }
 
    // get data length in buffer
    uint length () const throw ();
    uint size () const throw () { return length(); }

	// get data in buffer
	char* getBuffer() const { return m_Buffer; }
 
    // check if buffer is empty
    bool isEmpty () const throw () { return m_Head == m_Tail; }

    // get debug string
    string toString () const throw ()
    {
        StringStream msg;
        msg << "SocketOutputStream(m_BufferLen:"<<m_BufferLen<<",m_Head:"<<m_Head<<",m_Tail:"<<m_Tail
<<")";
        return msg.toString();
    }

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	
	// socket
	Socket* m_Socket;
	
	// output buffer
	char* m_Buffer;
	
	// buffer length
	uint m_BufferLen;
	
	// buffer head/tail
	uint m_Head;
	uint m_Tail;

	// 룐관埼죗
	BYTE m_Sequence;
//add by viva 2008-12-31
//public :
//	WORD m_EncryptKey;
//	BYTE* m_HashTable;
//	void setKey(WORD EncryptKey, BYTE* HashTable) throw() { m_EncryptKey = EncryptKey; m_HashTable = HashTable;};
//	WORD EncryptData(WORD EncryptKey, char* buf, int len) throw();
//end
};


//////////////////////////////////////////////////////////////////////
//
// write data to stream (output buffer)
//
// *Notes*
//
// ( ( m_Head = m_Tail + 1 ) ||  
//   ( ( m_Head == 0 ) && ( m_Tail == m_BufferLen - 1 ) )
//
// 일 때 버퍼 full 로 간주한다는 것을 잊지 말라. 따라서, 버퍼의 빈
// 공간의 크기는 항상 1 을 빼줘야 한다는 사실!
//
//////////////////////////////////////////////////////////////////////
template<typename T>
uint SocketOutputStream::write ( T buf ) 
     throw ( Error )
{
	__BEGIN_TRY

	uint len = sizeof(T);
		
	// 현재 버퍼의 빈 영역을 계산한다.
	// (!) m_Head > m_Tail인 경우에 m_Head - m_Tail - 1 로 수정했다. by sigi. 2002.9.16
	// 근데 buffer_resize가 더 자주 일어났다. 다른데 문제가 있는데 일단 못 찾겠으므로.. back. by sigi. 2002.9.23
	// 테스트 해보니까.. 정상적이었다. 실제로 buffer resize가 빈번히 일어나는 원인은 뭘까? 다시 수정. by sigi. 2002.9.27
	uint nFree = ( ( m_Head <= m_Tail ) ?  m_BufferLen - m_Tail + m_Head - 1 : m_Head - m_Tail - 1 );
					//m_Tail - m_Head - 1 );

	// 쓸려고 하는 데이타의 크기가 빈 영역의 크기를 초과할 경우 버퍼를 증가시킨다.
	if ( len >= nFree )
		resize( len - nFree + 1 );
		
	if ( m_Head <= m_Tail )		// normal order
	{
		//
		//    H   T
		// 0123456789
		// ...abcd...
		//
		
		if ( m_Head == 0 )
		{
			nFree = m_BufferLen - m_Tail - 1;
			*((T*)(m_Buffer+m_Tail)) = buf;
		}
		else
		{
			nFree = m_BufferLen - m_Tail;
			if ( len <= nFree )
			{
				*((T*)(m_Buffer+m_Tail)) = buf;
			}
			else
			{
				memcpy( &m_Buffer[m_Tail] , (char *)&buf , nFree );
				memcpy( m_Buffer , (((char*)&buf)+nFree), len - nFree );
			}
		}
	} 
	else						// reversed order
	{
		//
		//     T  H
		// 0123456789
		// abcd...efg
		//
		*((T*)(m_Buffer+m_Tail)) = buf;
	}

	// advance m_Tail
	m_Tail = ( m_Tail + len ) % m_BufferLen;

	return len;
	
	__END_CATCH
}

#endif
