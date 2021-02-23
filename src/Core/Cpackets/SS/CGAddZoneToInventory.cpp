//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAddZoneToInventory.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGAddZoneToInventory::CGAddZoneToInventory () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGAddZoneToInventory::~CGAddZoneToInventory () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGAddZoneToInventory::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __USE_ENCRYPTER__
	SocketEncryptInputStream* pEIStream = dynamic_cast<SocketEncryptInputStream*>(&iStream);
    Assert(pEIStream!=NULL);

	if (pEIStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_5(pEIStream->getEncryptCode(),
							pEIStream->readEncrypt(m_ObjectID),
							pEIStream->readEncrypt(m_ZoneX),
							pEIStream->readEncrypt(m_ZoneY),
							pEIStream->readEncrypt(m_InvenX),
							pEIStream->readEncrypt(m_InvenY));
	}
	else
#endif
	{
		iStream.read(m_ObjectID);
		iStream.read(m_ZoneX);
		iStream.read(m_ZoneY);
		iStream.read(m_InvenX);
		iStream.read(m_InvenY);
	}

	__END_CATCH
}

void CGAddZoneToInventory::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream* pEOStream = dynamic_cast<SocketEncryptOutputStream*>(&oStream);
    Assert(pEOStream!=NULL);

	if (pEOStream->getEncryptCode()!=0)
	{
		SHUFFLE_STATEMENT_5(pEOStream->getEncryptCode(),
							pEOStream->writeEncrypt(m_ObjectID),
							pEOStream->writeEncrypt(m_ZoneX),
							pEOStream->writeEncrypt(m_ZoneY),
							pEOStream->writeEncrypt(m_InvenX ),
							pEOStream->writeEncrypt(m_InvenY ));
	}
	else
#endif
	{
		oStream.write(m_ObjectID);
		oStream.write(m_ZoneX);
		oStream.write(m_ZoneY);
		oStream.write(m_InvenX );
		oStream.write(m_InvenY );
	}

	__END_CATCH
}

void CGAddZoneToInventory::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGAddZoneToInventoryHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGAddZoneToInventory::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGAddZoneToInventory("
	    << "ObjectID : "     << (int)m_ObjectID 
		<< ", ZoneX : "      << (int)m_ZoneX 
		<< ", ZoneY : "      << (int)m_ZoneY 
		<< ", InventoryX : " << (int)m_InvenX
		<< ", InventoryY : " << (int)m_InvenY 
		<< ")";
	return msg.toString();

	__END_CATCH
}
