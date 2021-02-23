//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToMouse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddZoneToMouse.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGAddZoneToMouse::CGAddZoneToMouse () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddZoneToMouse::~CGAddZoneToMouse () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddZoneToMouse::read (SocketInputStream & iStream) 
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
		iStream.read((char*)&m_ObjectID , szObjectID);
		iStream.read((char*)&m_ZoneX , szCoord);
		iStream.read((char*)&m_ZoneY , szCoord);
	}

	__END_CATCH
}

void CGAddZoneToMouse::write (SocketOutputStream & oStream) const 
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
		oStream.write((char*)&m_ObjectID , szObjectID);
		oStream.write((char*)&m_ZoneX , szCoord);
		oStream.write((char*)&m_ZoneY , szCoord);
	}

	__END_CATCH
}

void CGAddZoneToMouse::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddZoneToMouseHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddZoneToMouse::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddZoneToMouse(" 
	    << "ObjectID : " << (int)m_ObjectID 
		<< ", ZoneX : " << (int)m_ZoneX 
		<< ", ZoneY : " << (int)m_ZoneY 
		<< ")";
	return msg.toString();

	__END_CATCH
}
