//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMove.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGMove.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


void CGMove::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_X),
							pEIStream->readEncrypt(m_Y),
							pEIStream->readEncrypt(m_Dir));
	}
	else
#endif
	{
		iStream.read(m_X);
		iStream.read(m_Y);
		iStream.read(m_Dir);
	}

	__END_CATCH
}

void CGMove::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_X),
							pEOStream->writeEncrypt(m_Y),
							pEOStream->writeEncrypt(m_Dir));
	}
	else
#endif
	{
		oStream.write(m_X);
		oStream.write(m_Y);
		oStream.write(m_Dir);
	}

	__END_CATCH
}

void CGMove::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGMoveHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGMove::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGMove("
		<< "X:" << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",Dir:" << Dir2String[m_Dir] << ")";
	return msg.toString();

	__END_CATCH
}
