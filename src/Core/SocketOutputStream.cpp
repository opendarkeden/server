//////////////////////////////////////////////////////////////////////
// 
// SocketOutputStream.cpp
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#include "SocketOutputStream.h"
#include "Assert.h"
#include "Packet.h"
#include "VSDateTime.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SocketOutputStream::SocketOutputStream ( Socket * sock , uint BufferLen ) 
	throw ( Error )
: m_Socket(sock), m_Buffer(NULL), m_BufferLen(BufferLen), m_Head(0), m_Tail(0), m_Sequence(0)
{
	__BEGIN_TRY

//	Assert( m_Socket != NULL );
	Assert( m_BufferLen > 0 );
	
	m_Buffer = new char[ m_BufferLen ];

	//add by viva
	//m_EncryptKey = 0;
	//m_HashTable = NULL;
	//end
	
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SocketOutputStream::~SocketOutputStream () 
	throw ( Error )
{
	__BEGIN_TRY

	if ( m_Buffer != NULL ) {
		// 연결이 끊겨서 ConnectException 을 받아 종료된 상태에서
		// flush를 할 경우 SIGPIPE 가 난다. 따라서, 무시하자~
		// flush();
		delete [] m_Buffer;
		m_Buffer = NULL;
	}
	
	__END_CATCH
}


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
uint SocketOutputStream::write ( const char * buf , uint len ) 
     throw ( Error )
{
	__BEGIN_TRY
		
	// 현재 버퍼의 빈 영역을 계산한다.
	// (!) m_Head > m_Tail인 경우에 m_Head - m_Tail - 1 로 수정했다. by sigi. 2002.9.16
	// 근데 buffer_resize가 더 자주 일어났다. 다른데 문제가 있는데 일단 못 찾겠으므로.. back. by sigi. 2002.9.23
	// 테스트 해보니까.. 정상적이었다. 실제로 buffer resize가 빈번히 일어나는 원인은 뭘까? 다시 수정. by sigi. 2002.9.27
	uint nFree = ( ( m_Head <= m_Tail ) ?  m_BufferLen - m_Tail + m_Head - 1 : m_Head - m_Tail - 1 );
					//m_Tail - m_Head - 1 );

	// 쓸려고 하는 데이타의 크기가 빈 영역의 크기를 초과할 경우 버퍼를 증가시킨다.
	if ( len >= nFree )
		resize( len - nFree + 1 );
		
	if ( m_Head <= m_Tail ) {		// normal order

		//
		//    H   T
		// 0123456789
		// ...abcd...
		//
		
		if ( m_Head == 0 ) {
			
			nFree = m_BufferLen - m_Tail - 1;
			memcpy( &m_Buffer[m_Tail] , buf , len );

		} else {

			nFree = m_BufferLen - m_Tail;
			if ( len <= nFree )
				memcpy( &m_Buffer[m_Tail] , buf , len );
			else {
				memcpy( &m_Buffer[m_Tail] , buf , nFree );
				memcpy( m_Buffer , &buf[nFree] , len - nFree );
			}

		}

	} else {						// reversed order

		//
		//     T  H
		// 0123456789
		// abcd...efg
		//
		
		memcpy( &m_Buffer[m_Tail] , buf , len );

	}
	
	// advance m_Tail
	m_Tail = ( m_Tail + len ) % m_BufferLen;
		
	return len;
	
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// write packet to stream (output buffer)
//////////////////////////////////////////////////////////////////////
void SocketOutputStream::writePacket ( const Packet * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 우선 패킷아이디와 패킷크기를 출력버퍼로 쓴다.
	PacketID_t packetID = pPacket->getPacketID();
	write( (char*)&packetID , szPacketID );
	
	PacketSize_t packetSize = pPacket->getPacketSize();
	write( (char*)&packetSize , szPacketSize );

	// 속흙룐관埼죗
	write( (char*)&m_Sequence, szSequenceSize);
	m_Sequence++;
	
	// 이제 패킷바디를 출력버퍼로 쓴다.
	//cout<<"Send:"<<pPacket->toString()<<endl;
	pPacket->write( *this );
	
	
	/*
	if( packetID == Packet::PACKET_GC_UPDATE_INFO ) {

		ofstream file("flush.txt", ios::out | ios::app);
		file << "SEND GCUPDATE INFO" << endl;
		file.close();

	}
	*/

//	flush();
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// flush stream (output buffer) to socket
//////////////////////////////////////////////////////////////////////
uint SocketOutputStream::flush () 
     throw (IOException, ProtocolException, InvalidProtocolException, Error)
{
	__BEGIN_TRY

	Assert( m_Socket != NULL );

	uint nFlushed = 0;
	uint nSent = 0;
	uint nLeft;
	
	try {

		if ( m_Head < m_Tail ) {
		
			//
			//    H   T
			// 0123456789
			// ...abcd...
			//
	
			nLeft = m_Tail - m_Head;
//add by viva 2008-12-31
			//if(nLeft > 0)
				//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Head], nLeft);
			
			while ( nLeft > 0 ) {
				nSent = m_Socket->send( &m_Buffer[m_Head] , nLeft , MSG_NOSIGNAL );

				// NonBlockException제거. by sigi.2002.5.17
				if (nSent==0) return 0;
				
				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}

			Assert( nLeft == 0 );
	
		} else if ( m_Head > m_Tail ) {
	
			//
			//     T  H
			// 0123456789
			// abcd...efg
			//
			
			nLeft = m_BufferLen - m_Head;
//add by viva 2008-12-31
			//if(nLeft>0)
				//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Head], nLeft);	
			while ( nLeft > 0 ) {
				nSent = m_Socket->send( &m_Buffer[m_Head] , nLeft , MSG_NOSIGNAL );

				// NonBlockException제거. by sigi.2002.5.17
				if (nSent==0) return 0;
				
				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}
			
			Assert( m_Head == m_BufferLen );
			
			m_Head = 0;
			
			nLeft = m_Tail;
//add by viva 2008-12-31
			//if(nLeft>0)
				//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Head], nLeft);	
			while ( nLeft > 0 ) {
				nSent = m_Socket->send( &m_Buffer[m_Head] , nLeft , MSG_NOSIGNAL );

				// NonBlockException제거. by sigi.2002.5.17
				if (nSent==0) return 0;
				
				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}
	
			Assert( nLeft == 0 );
		}
	
		if ( m_Head != m_Tail ) 
		{
			cout << "m_Head : " << m_Head << endl;
			cout << "m_Tail : " << m_Tail << endl;
			Assert( m_Head == m_Tail );
		}
		
	}
	catch ( NonBlockingIOException& ) 
	{
		// 일부만 send되고 마는 경우
		// by sigi. 2002.9.27
		if (nSent>0)
		{
			m_Head += nSent;
		}

		cerr << "SocketOutputStream NonBlockingIOException Check! " << endl;
		throw NonBlockingIOException( "SocketOutputStream NonBlockingIOException Check");
	} 
	catch ( InvalidProtocolException & t ) 
	{
		// 일부만 send되고 마는 경우
		// by sigi. 2002.9.27
		if (nSent>0)
		{
			m_Head += nSent;
		}

		cerr << "SocketOutputStream Exception Check! " << endl;
		cerr << t.toString() << endl;
		throw InvalidProtocolException( "SocketOutputStream Exception Check");
	}

	/*
	ofstream file("flush.txt", ios::out | ios::app);
	file << "flush send size: " << nFlushed << " left size : " << nLeft << endl;
	file.close();
	*/

	// 첨부터 다시.. by sigi. 2002.9.26
	m_Head = m_Tail = 0;

	return nFlushed;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// resize buffer
//////////////////////////////////////////////////////////////////////
void SocketOutputStream::resize ( int size )
	 throw ( IOException , Error )
{
	__BEGIN_TRY
		
	//Assert( m_Socket != NULL );
	Assert( size != 0 );

	int orgSize = size;

	// 잦은 resize를 방지하기 위해서.. 현재 버퍼의 1/2만큼 늘려볼까 by sigi. 2002.9.26
	size = max(size, (int)(m_BufferLen>>1));
	uint newBufferLen = m_BufferLen + size;
	uint len = length();
	
	if ( size < 0 ) {
		
		// 만약 크기를 줄이려는데 버퍼에 들어있는 데이타를 
		// 다 못담아낼 경우 
		if ( newBufferLen < 0 || newBufferLen < len )
			throw IOException("new buffer is too small!");
		
	} 
	
	// 새 버퍼를 할당받는다.
	char * newBuffer = new char[ newBufferLen ];
		
	// 원래 버퍼의 내용을 복사한다.
	if ( m_Head < m_Tail ) {

		//
		//    H   T
		// 0123456789
		// ...abcd...
		//

		memcpy( newBuffer , &m_Buffer[m_Head] , m_Tail - m_Head );

	} else if ( m_Head > m_Tail ) {

		//
		//     T  H
		// 0123456789
		// abcd...efg
		//
		 
		memcpy( newBuffer , &m_Buffer[m_Head] , m_BufferLen - m_Head );
		memcpy( &newBuffer[ m_BufferLen - m_Head ] , m_Buffer , m_Tail );

	}
		
	// 원래 버퍼를 삭제한다.
	delete [] m_Buffer;
		
	// 버퍼 및 버퍼 크기를 재설정한다.
	m_Buffer = newBuffer;
	m_BufferLen = newBufferLen;
	m_Head = 0;
	m_Tail = len;	

	VSDateTime current = VSDateTime::currentDateTime();

	if ( m_Socket == NULL )
	{
		// m_Socket 이 NULL 이라는 것은 이 스트림이 브로드 캐스트용 스트림이라는 말이다.
		// resize 가 불렸다는 말은 패킷의 getPacketSize() 함수가 잘못되어 있다는 말이다.
		filelog( "packetsizeerror.txt", "PacketID = %u", *(PacketID_t*)m_Buffer );
	}
	else
	{
		ofstream ofile("buffer_resized.log",ios::app);
		ofile << "[" << current.toString().c_str() << "] " << m_Socket->getHost().c_str() << " - SocketOutputStream resized: " << orgSize << " / " << size << "/" << m_BufferLen << " bytes!" << endl;
		ofile.close();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get data's size in buffer
//////////////////////////////////////////////////////////////////////
uint SocketOutputStream::length () const
     throw ()
{
    if ( m_Head < m_Tail )
        return m_Tail - m_Head;
	 
    else if ( m_Head > m_Tail )
        return m_BufferLen - m_Head + m_Tail;
			 
    return 0;
}

//add by viva 2008-12-31
/*WORD SocketOutputStream::EncryptData(WORD EncryptKey, char* buf, int len)
	throw()
{
	for(int i = 0; i<len; i++)
		*(buf + i) ^= 0xCC;

	if(m_HashTable == NULL)	return EncryptKey;
	
	for(int i = 0; i<len; i++)
	{
		*(buf + i) ^= m_HashTable[EncryptKey];
		if(++EncryptKey == 512)	EncryptKey = 0;
	}
	
	return EncryptKey;
	
}*/
//end
