//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCRegisterPlayerOK.cpp
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LCRegisterPlayerOK.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void LCRegisterPlayerOK::read ( SocketInputStream & iStream )
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szGroupName;
	iStream.read( szGroupName );
	iStream.read( m_GroupName, szGroupName );
	iStream.read( m_isAdult );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void LCRegisterPlayerOK::write ( SocketOutputStream & oStream ) const
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

    BYTE szGroupName = m_GroupName.size();
	oStream.write( szGroupName );
	oStream.write( m_GroupName );
	oStream.write( m_isAdult );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCRegisterPlayerOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCRegisterPlayerOKHandler::execute( this , pPlayer );
		
	__END_CATCH
}


