//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDissectionCorpse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDissectionCorpse.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGDissectionCorpse::CGDissectionCorpse () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGDissectionCorpse::~CGDissectionCorpse () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGDissectionCorpse::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_X),
							pEIStream->readEncrypt(m_Y),
							pEIStream->readEncrypt(m_IsPet));
	}
	else
#endif
	{
		iStream.read(m_ObjectID);
		iStream.read(m_X);
		iStream.read(m_Y);
		iStream.read(m_IsPet);
	}

	__END_CATCH
}

void CGDissectionCorpse::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_4(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_X),
							pEOStream->writeEncrypt(m_Y),
							pEOStream->writeEncrypt(m_IsPet));
	}
	else
#endif
	{
		oStream.write(m_ObjectID);
		oStream.write(m_X);
		oStream.write(m_Y);
		oStream.write(m_IsPet);
	}

	__END_CATCH
}

void CGDissectionCorpse::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CGDissectionCorpseHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGDissectionCorpse::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGDissectionCorpse("
		<< "X:"         << (int)m_X 
		<< ",Y:"        << (int)m_Y
		<< ",ObjectID:" << (int)m_ObjectID
	   	<< ")" ;
	return msg.toString();

	__END_CATCH
}
