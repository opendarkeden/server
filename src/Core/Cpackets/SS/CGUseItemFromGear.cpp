//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromGear.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseItemFromGear.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


void CGUseItemFromGear::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_2(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_Part));
	}
	else
#endif
	{
		iStream.read(m_ObjectID);
		iStream.read(m_Part);
	}

	__END_CATCH
}
		    
void CGUseItemFromGear::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_2(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_Part));
	}
	else
#endif
	{
		oStream.write(m_ObjectID);
		oStream.write(m_Part);
	}

	__END_CATCH
}

void CGUseItemFromGear::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGUseItemFromGearHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGUseItemFromGear::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseItemFromGear("
		<< "ObjectID:" << (int)m_ObjectID 
		<< "Part:" << (int)m_Part
		<< ")";
	return msg.toString();

	__END_CATCH
}
