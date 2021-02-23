//////////////////////////////////////////////////////////////////////
// 
// SocketInputStream.cpp
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "SocketInputStream.h"
#include <errno.h>
#include "Assert.h"
#include "Packet.h"

#if __LINUX__
	#include <sys/ioctl.h>
#elif __WINDOWS__
	#include <winsock.h>
#endif


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SocketInputStream::SocketInputStream ( Socket * sock , uint BufferLen ) 
	throw ( Error )
: m_pSocket(sock), m_Buffer(NULL), m_BufferLen(BufferLen), m_Head(0), m_Tail(0)
{
	__BEGIN_TRY
		
	Assert( m_pSocket != NULL );
	Assert( m_BufferLen > 0 );
	
	m_Buffer = new char[ m_BufferLen ];
//add by viva 2008-12-31
	//m_EncryptKey = 0;
	//m_HashTable = NULL;
//end
		
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SocketInputStream::~SocketInputStream () 
	throw ( Error )
{
	__BEGIN_TRY
		
	SAFE_DELETE_ARRAY(m_Buffer);
		
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
//
// read data from input buffer
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::read ( char * buf , uint len ) 
	throw ( ProtocolException , Error )
{
//	__BEGIN_TRY
		
	Assert( buf != NULL );	
	
	if ( len == 0 )
		throw InvalidProtocolException("len==0");
	
	// 요청한 만큼의 데이타가 버퍼내에 존재하지 않을 경우 예외를 던진다.
	// 만약 모든 read 가 peek() 로 체크한 후 호출된다면, 아래 if-throw 는 
	// 중복된 감이 있다. 따라서, 코멘트로 처리해도 무방하다.
	// 단 아래 코드를 코멘트처리하면, 바로 아래의 if-else 를 'if'-'else if'-'else'
	// 로 수정해줘야 한다.
	if ( len > length() )
		throw InsufficientDataException( len - length() );
	
	if ( m_Head < m_Tail ) {	// normal order

		//
        //    H   T
        // 0123456789
        // ...abcd...
        //

		memcpy( buf , &m_Buffer[m_Head] , len );

	} else {					// reversed order ( m_Head > m_Tail )
		
        //
        //     T  H
        // 0123456789
        // abcd...efg
        //
	 
		uint rightLen = m_BufferLen - m_Head;
		if ( len <= rightLen ) {
			memcpy( buf , &m_Buffer[m_Head] , len );
		} else {
			memcpy( buf , &m_Buffer[m_Head] , rightLen );
			memcpy( &buf[rightLen] , m_Buffer , len - rightLen );
		}

	}

	m_Head = ( m_Head + len ) % m_BufferLen;
	
	return len;
		
//	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// read data from input buffer
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::read ( string & str , uint len ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	if ( len == 0 )
		throw InvalidProtocolException("len==0");
	
	// 요청한 만큼의 데이타가 버퍼내에 존재하지 않을 경우 예외를 던진다.
	// 만약 모든 read 가 peek() 로 체크한 후 호출된다면, 아래 if-throw 는 
	// 중복된 감이 있다. 따라서, 코멘트로 처리해도 무방하다.
	// 단 아래 코드를 코멘트처리하면, 바로 아래의 if-else 를 if-else if-else
	// 로 수정해줘야 한다.
	if ( len > length() )
		throw InsufficientDataException( len - length() );
	
	// 스트링에다가 len 만큼 공간을 미리 할당한다.
	str.reserve( len );

	if ( m_Head < m_Tail ) {	// normal order

		//
        //    H   T
        // 0123456789
        // ...abcd...
        //

		str.assign( &m_Buffer[m_Head] , len );

	} else { 					// reversed order ( m_Head > m_Tail )
		
        //
        //     T  H
        // 0123456789
        // abcd...efg
        //
	 
		uint rightLen = m_BufferLen - m_Head;
		if ( len <= rightLen ) {
			str.assign( &m_Buffer[m_Head] , len );
		} else {
			str.assign( &m_Buffer[m_Head] , rightLen );
			str.append( m_Buffer , len - rightLen );
		}
	}
	
	m_Head = ( m_Head + len ) % m_BufferLen;

	return len;
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// read packet from input buffer
//////////////////////////////////////////////////////////////////////
void SocketInputStream::readPacket ( Packet * pPacket ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 이미 상위 레벨에서 ID, Size를 읽고 ID에 맞는 패킷객체를 만들어서
	// 파라미터로 넘겼으므로 ID 는 skip 한다. Size는 객체의 바이너리 
	// 이미지가 모두 도착했는지만 체크할뿐, 객체의 초기화와는 무관하기
	// 때문에 skip 한다.
	skip( szPacketHeader );

	// 이제 하위 패킷 클래스에 정의된 메쏘드를 수행하면, 내부에서
	// 알아서 잘 초기화하게 된다.
	// 단 어떤 패킷의 read()에서 틀리게 되면 그 이후의 모든 패킷은
	// 파싱이 불가능하게 된다. 따라서, 패킷 클래스를 디자인할 때
	// 주의해야 한다.
	//cout<<"Receive_before:"<<pPacket->toString()<<endl;
	pPacket->read( *this );
	cout<<"Receive:"<<pPacket->toString()<<endl;
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// peek data from buffer
//////////////////////////////////////////////////////////////////////
bool SocketInputStream::peek ( char * buf , uint len ) 
	throw ( ProtocolException , Error )
{
//	__BEGIN_TRY
			
	Assert( buf != NULL );	

	if ( len == 0 )
		throw InvalidProtocolException("len==0");
	
	// 요청한 크기보다 버퍼의 데이타가 적은 경우, 예외를 던진다.
	if ( len > length() )
		//throw InsufficientDataException( len - length() );
		// NoSuch제거. by sigi. 2002.5.4
		return false;

	// buf 에 복사는 하되, m_Head 는 변화시키지 않는다.
	if ( m_Head < m_Tail ) {	// normal order

		//
        //    H   T
        // 0123456789
        // ...abcd...
        //

		memcpy( buf , &m_Buffer[m_Head] , len );

	} else { 					// reversed order ( m_Head > m_Tail )
		
        //
        //     T  H
        // 0123456789
        // abcd...efg
        //
	 
		uint rightLen = m_BufferLen - m_Head;
		if ( len <= rightLen ) {
			memcpy( &buf[0]        , &m_Buffer[m_Head] , len );
		} else {
			memcpy( &buf[0]        , &m_Buffer[m_Head] , rightLen );
			memcpy( &buf[rightLen] , &m_Buffer[0]      , len - rightLen );
		}
	}
		
	return true;
//	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
//
// skip data from buffer
//
// read(N) == peek(N) + skip(N)
//
//////////////////////////////////////////////////////////////////////
void SocketInputStream::skip ( uint len ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	if ( len == 0 )
		throw InvalidProtocolException("len==0");
	
	if ( len > length() )
		throw InsufficientDataException( len - length() );
	
	// m_Head 를 증가시킨다.
	m_Head = ( m_Head + len ) % m_BufferLen;

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
//
// fill buffer from socket
//
// 데이타가 없을 경우 0 을 리턴한다.
// 그런데, NonBlocking 일 경우 NonBlockingIOException 을 던진다.
//
// *NOTES*
//
// 가장 쉬운 방법은 함수에다가 char buf[N]; 을 선언한 후에 여기다가
// receive() 결과값을 저장한 후, 버퍼에 복사하는 것이다. 그러나, 이
// 방법은 복사가 2회 발생하기 때문에 지양되어야 하겠다. 
//
// 따라서, 스트림의 내부 버퍼에다가 직접 써야 하는데, 이때 내부 버퍼가
// circular 이므로, normal order 일 경우에는 2회 이상 receive()가 호출될
// 확률이 있게 된다.
//
// 이때 첫번째 receive()에서 소켓의 receive 버퍼의 데이타를 다 읽어버리고, 
// 동시에 버퍼의 끝에 도달한 경우 두번째 receive() 에서 NonBlockingIOException 
// 이 발생하게 된다. (물론 이런 경우는 드물다. 버퍼의 끝과 맨앞에 걸쳐서 
// 데이타가 써질 경우는 종종 발생한다 치더라도.. ) 
//
// 자. 이럴 경우 fill()은 외부로 NonBlockingIOException 을 던져야 하는가?
// 아니면 지금까지 읽은 데이타 크기를 리턴해야 하는가? 정답은 후자다. ^^;
// 즉 내 맘대로야~~~ 이히히히히히~
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::fill () 
	throw ( IOException , Error )
{
	__BEGIN_TRY

	uint nFilled = 0;		// 버퍼에 채워넣은 크기
	uint nReceived;			// Socket::receive()로 한번 읽어들인 크기
	uint nFree;				// 버퍼의 빈 영역의 크기

	if ( m_Head <= m_Tail ) {	// normal order
								// m_Head == m_Tail 일 경우는 버퍼가 빈 상태를 나타낸다.

		// 일단 버퍼의 오른쪽 빈 공간만을 채운다.
		if ( m_Head == 0 ) {

			//
			// H   T
			// 0123456789
			// abcd......
			//
			
			// 주의할 점은, m_Head == 0 일 경우, m_Tail 이 버퍼의 끝을 돌아서 다시 0 으로
			// 되게 되면 buffer empty 와 같은 상태가 된다는 점이다. 따라서, m_Head 를 체크
			// 해서 0 일 경우 m_Tail 을 위해서 버퍼의 맨 마지막 칸을 비워둬야 하겠다. ^^

			nFree = m_BufferLen - m_Tail - 1;
			nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , nFree );
			
			// by sigi. NonblockException제거. 2002.5.17
			if (nReceived==0) return 0;
			//add by viva
			//if(nReceived>0)
				//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
			//end
			m_Tail += nReceived;
			nFilled += nReceived;
			
			if ( nReceived == nFree ) {

				// 소켓의 receive 버퍼에 데이타가 남아있을 가능성이 있다.
				// 그러나, 입력 버퍼에 여유 공간이 없으므로 데이타가 남아 
				// 있다면 버퍼를 증가시켜야 한다.
				uint available = m_pSocket->available();
				if ( available > 0 ) {
					resize( available + 1 );
					// resize 되면, 내부의 데이타가 정렬되므로 m_Tail 부터 쓰면 된다.
					nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , available );

					// by sigi. NonblockException제거. 2002.5.17
					if (nReceived==0) return 0;
					//add by viva
					//if(nReceived>0)
						//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
					//end
					m_Tail += nReceived;
					nFilled += nReceived;
				}
			}

		} else {	// m_Head != 0
			
			//
			//    H   T
			// 0123456789
			// ...abcd...
			//

			// 이 경우, m_Tail 이 버퍼의 앞쪽으로 넘어가도 무방하다.
			nFree = m_BufferLen - m_Tail;
			nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , nFree );

			// by sigi. NonblockException제거. 2002.5.17
			if (nReceived==0) return 0;
			//add by viva
			//if(nReceived>0)
				//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
			//end
			m_Tail = ( m_Tail + nReceived ) % m_BufferLen;
			nFilled += nReceived;

			if ( nReceived == nFree ) {
				
				Assert( m_Tail == 0 );

				// 소켓의 receive 버퍼에 데이타가 더 남아있을 가능성이 있다.
				// 따라서, 입력 버퍼의 앞쪽 여유 공간에 데이타를 쓰도록 한다.
				// 단 이때에도 m_Head == m_Tail 이면 empty 가 되므로,
				// -1 줄이도록 한다.
				nFree = m_Head - 1;
				nReceived = m_pSocket->receive( &m_Buffer[0] , nFree );

				// by sigi. NonblockException제거. 2002.5.17
				if (nReceived==0) return 0;
				//add by viva
				//if(nReceived>0)
					//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
				//end
				m_Tail += nReceived;
				nFilled += nReceived;
			
				if ( nReceived == nFree ) {	// buffer is full

					// 버퍼가 가득 찬 상태일 경우, 소켓의 receive 버퍼에 데이타가 더 
					// 남아있을 가능성이 있다. 따라서, 읽어보고 더 있으면 버퍼를 증가시킨다.
					uint available = m_pSocket->available();
					if ( available > 0 ) {
						resize( available + 1 );
						// resize 되면, 내부의 데이타가 정렬되므로 m_Tail 부터 쓰면 된다.
						nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , available );

						// by sigi. NonblockException제거. 2002.5.17
						if (nReceived==0) return 0;
						//add by viva
						//if(nReceived>0)
							//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
						//end
						m_Tail += nReceived;
						nFilled += nReceived;
					}
				}
			}
		}

	} else {	// reversed order ( m_Head > m_Tail )
		
		//
        //     T  H
        // 0123456789
        // abcd...efg
        //
		
		nFree = m_Head - m_Tail - 1;
		nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , nFree );

		// by sigi. NonblockException제거. 2002.5.17
		if (nReceived==0) return 0;
		//add by viva
		//if(nReceived>0)
			//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
		//end
		m_Tail += nReceived;
		nFilled += nReceived;
		
		if ( nReceived == nFree ) {		// buffer is full

			// 이 경우, 소켓의 receive 버퍼에 데이타가 더 남아있을 
			// 가능성이 있다. 따라서, 읽어보고 더 있으면 버퍼를 증가시킨다.
			uint available = m_pSocket->available();
			if ( available > 0 ) {
				resize( available + 1 );
				// resize 되면, 내부의 데이타가 정렬되므로 m_Tail 부터 쓰면 된다.
				nReceived = m_pSocket->receive( &m_Buffer[m_Tail] , available );
		
				// by sigi. NonblockException제거. 2002.5.17
				if (nReceived==0) return 0;
				//add by viva
				//if(nReceived>0)
					//m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
				//end
				m_Tail += nReceived;
				nFilled += nReceived;
			}
		}

	}
//add by viva 2008-12-31
//	if(nFilled>0)
//	{
//		if(m_Tail>=nFilled)
//			m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail-nFilled], nFilled);
//		else
//		{
//			m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_BufferLen - m_Tail], nFilled - m_Tail);
//			m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[0], m_Tail);
//		}
//	}
//end
	return nFilled;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// fill buffer from socket
//
// 에디트 요망 - 아직 안 고쳤음. 0 -;
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::fill_RAW ()
	 throw ( IOException , Error )
{
	__BEGIN_TRY
		
#if __LINUX__
	uint nfree = m_BufferLen - m_Tail - 1;	

	int nread = recv( m_pSocket->getSOCKET() , &m_Buffer[m_Tail] , nfree , 0 );

	if ( nread < 0 ) {
		if ( errno == EWOULDBLOCK ) {
			// NonBlockingIOException
			nread = 0;
		} else if ( errno == ECONNRESET ) {
			// ConnectException
			throw ConnectException();
		} else {
			// Error
			throw UnknownError(strerror(errno),errno);
		}
	} else if ( nread == 0 ) {
		// EOFException
		throw EOFException();
	}
	
	m_Tail += nread;
	
	if ( nread == (int)nfree ) {
		// 데이타가 더 있을 가능성이 있다.
		uint more = 0;
		int result = ioctl( m_pSocket->getSOCKET() , FIONREAD , &more );
		if ( result < 0 )
			throw UnknownError(strerror(errno),errno);
		
		if ( more > 0 ) {

			// 버퍼를 증가시킨다.
			resize( more + 1 );

			// 버퍼를 채운다.
			nread = recv( m_pSocket->getSOCKET() , &m_Buffer[m_Tail] , more , 0 );
			
			// 무조건 more 만큼 읽어야 한다. 그렇지 않을 경우 에러다.
			Assert( (int)more == nread );
			
			nread += more;
		}		
	}
	
	return nread;

#elif __WINDOWS__
	throw UnsupportedError();
#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// resize buffer
//////////////////////////////////////////////////////////////////////
void SocketInputStream::resize ( int size )
	 throw ( IOException , Error )
{
	__BEGIN_TRY
		
	Assert( size != 0 );
	
	// resize size조절. by sigi. 2002.10.7
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
		
	// ???및 버퍼 크기를 재설정한다.
	m_Buffer = newBuffer;
	m_BufferLen = newBufferLen;
	m_Head = 0;
	m_Tail = len;	// m_Tail 은 들어있는 데이타의 길이와 같다.

	ofstream ofile("buffer_resized.log",ios::app);
	ofile << "SocketInputStream resized " << size << " bytes!" << endl;
	ofile.close();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get data's size in buffer
//
// NOTES
//
//       H   T           T  H
//    0123456789     0123456789
//    ...abcd...     abcd...efg
//
//    7 - 3 = 4      10 - ( 7 - 4 ) = 7
//
// CAUTION
//
//    m_Tail 이 빈 칸을 가리키고 있다는 것에 유의하라. 
//    버퍼의 크기가 m_BufferLen 라면 실제 이 큐에 들어갈 
//    수 있는 데이타는 ( m_BufferLen - 1 ) 이 된다.
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::length () const
     throw ()
{
	__BEGIN_TRY

	if ( m_Head < m_Tail )
		return m_Tail - m_Head;
	
	else if ( m_Head > m_Tail ) 
		return m_BufferLen - m_Head + m_Tail;
	
	return 0;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string SocketInputStream::toString () const
	throw ()
{
	StringStream msg;

	msg << "SocketInputStream("
		<< "BufferLen:" << m_BufferLen
		<< ",Head:" << m_Head
		<< ",Tail:" << m_Tail
		<< ")";

	return msg.toString();
}
//add by viva 2008-12-31
/*WORD SocketInputStream::EncryptData(WORD EncryptKey, char* buf, int len)
	throw()
{
	for(int i = 0; i<len; i++)
		*(buf + i) ^= 0xCC;
	
	if(m_HashTable == NULL) return EncryptKey;

	for(int i = 0; i<len; i++)
	{
		*(buf + i) ^= m_HashTable[EncryptKey];
		if(++EncryptKey == 512)	EncryptKey = 0;
	}
	return EncryptKey;
}*/
//end
