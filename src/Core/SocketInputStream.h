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
// �ý��ۿ��� ���� ����ϰ� ���Ǵ� Ŭ�������� �ϳ��̴�.
// �ӵ��� ���������� ������ ��ġ�Ƿ�, ���� ���� �ӵ��� �����ϰ�
// �ʹٸ�, exception�� ���� re-write �϶�. 
//
// ���� nonblocking �� ������-�����-���� ���� �߻��Ѵٰ� ������,
// �̰��� NonBlockingIOException���� wrapping�ɶ� overhead�� �߻���
// Ȯ���� ���ٰ� �����ȴ�.
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
	SocketInputStream (Socket* sock, uint BufferSize = DefaultSocketInputBufferSize);
	
	// destructor
	virtual ~SocketInputStream () noexcept;

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// read data from stream (input buffer)
	uint read (char* buf, uint len);
	uint read (string & str, uint len);
	void readPacket (Packet* p);

	template<typename T>
		uint read( T& buf );

/*	uint read (bool   & buf)  { return read((char*)&buf, szbool  ); }
	uint read (char   & buf)  { return read((char*)&buf, szchar  ); }
	uint read (uchar  & buf)  { return read((char*)&buf, szuchar ); }
	uint read (short  & buf)  { return read((char*)&buf, szshort ); }
	uint read (ushort & buf)  { return read((char*)&buf, szushort); }
	uint read (int    & buf)  { return read((char*)&buf, szint   ); }
	uint read (uint   & buf)  { return read((char*)&buf, szuint  ); }
	uint read (long   & buf)  { return read((char*)&buf, szlong  ); }
	uint read (ulong  & buf)  { return read((char*)&buf, szulong ); }
*/
	// peek data from stream (input buffer)
	bool peek (char* buf, uint len);
	
	// skip data from stream (input buffer)
	void skip (uint len);
	
	// fill stream (input buffer) from socket
	uint fill ();
	uint fill_RAW ();

	// resize buffer
	void resize (int size);
	
	// get buffer length
	uint capacity () const { return m_BufferLen; }
	
	// get data length in buffer
	uint length () const;
	uint size () const { return length(); }

	// check if buffer is empty
	bool isEmpty () const { return m_Head == m_Tail; }

	// get debug string
	string toString () const;


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
public :
	WORD m_EncryptKey;
	BYTE* m_HashTable;
	void setKey(WORD EncryptKey, BYTE* HashTable)  {m_EncryptKey = EncryptKey; m_HashTable = HashTable; }
	WORD EncryptData(WORD EncryptKey, char* buf, int len) ;
//end
};


//////////////////////////////////////////////////////////////////////
//
// read data from input buffer
//
//////////////////////////////////////////////////////////////////////
template<typename T>
uint SocketInputStream::read ( T& buf ) 
{
	uint len = (uint)sizeof(T);

	// ��û�� ��ŭ�� ����Ÿ�� ���۳��� �������� ���� ��� ���ܸ� ������.
	// ���� ��� read �� peek() �� üũ�� �� ȣ��ȴٸ�, �Ʒ� if-throw �� 
	// �ߺ��� ���� �ִ�. ����, �ڸ�Ʈ�� ó���ص� �����ϴ�.
	// �� �Ʒ� �ڵ带 �ڸ�Ʈó���ϸ�, �ٷ� �Ʒ��� if-else �� 'if'-'else if'-'else'
	// �� ��������� �Ѵ�.
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
