//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPickupMoney.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPickupMoney.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGPickupMoney::CGPickupMoney () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGPickupMoney::~CGPickupMoney () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGPickupMoney::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_ZoneX),
							pEIStream->readEncrypt(m_ZoneY));
	}
	else
#endif
	{
		iStream.read(m_ObjectID);
		iStream.read(m_ZoneX);
		iStream.read(m_ZoneY);
	}

	__END_CATCH
}

void CGPickupMoney::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_3(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_ZoneX),
							pEOStream->writeEncrypt(m_ZoneY));
	}
	else
#endif
	{
		oStream.write(m_ObjectID);
		oStream.write(m_ZoneX);
		oStream.write(m_ZoneY);
	}

	__END_CATCH
}

void CGPickupMoney::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGPickupMoneyHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGPickupMoney::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGPickupMoney("
	    << "ObjectID : " << (int)m_ObjectID 
		<< ", ZoneX : "  << (int)m_ZoneX 
		<< ", ZoneY : "  << (int)m_ZoneY
		<< ")";
	return msg.toString();

	__END_CATCH
}
