//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMoveOK.cc 
// Written By  : elca@ewestsoft.com
// Description : CGMove가 날아 왓을때 자기 자신에게 OK 사인을 날리기
//               위한 패킷 클래스 함수 정의
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMoveOK.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCMoveOK::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	/*
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );
	*/

#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt( m_X ),
							pEIStream->readEncrypt( m_Y ),
							pEIStream->readEncrypt( m_Dir ));
	}
	else
#endif
	{
		iStream.read( m_X );
		iStream.read( m_Y );
		iStream.read( m_Dir );
	}


	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCMoveOK::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	/*
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );
	*/

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt( m_X ),
							pEOStream->writeEncrypt( m_Y ),
							pEOStream->writeEncrypt( m_Dir ));
	}
	else
#endif
	{
		oStream.write( m_X );
		oStream.write( m_Y );
		oStream.write( m_Dir );
	}


	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCMoveOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMoveOKHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCMoveOK::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCMoveOK("
		<< "X:" << (int)m_X 
		<< ",Y:" << (int) m_Y 
		<< ",Dir:" << Dir2String[m_Dir] 
		<< ")";
	return msg.toString();

	__END_CATCH
}


