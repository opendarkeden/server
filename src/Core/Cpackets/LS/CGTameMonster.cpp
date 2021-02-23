//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTameMonster.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTameMonster.h"
#include "SocketEncryptInputStream.h"
#include "SocketEncryptOutputStream.h"
#include "Assert.h"


CGTameMonster::CGTameMonster () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGTameMonster::~CGTameMonster () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGTameMonster::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );

	__END_CATCH
}

void CGTameMonster::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );

	__END_CATCH
}

void CGTameMonster::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	CGTameMonsterHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGTameMonster::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGTameMonster(" 
		<< "ObjectID :" << (int)m_ObjectID 
		<< ")";
	return msg.toString();

	__END_CATCH
}
