//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherModifyInfo.cpp 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "GCOtherModifyInfo.h"

void GCOtherModifyInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	ModifyInfo::read( iStream );

	__END_CATCH
}
		    
void GCOtherModifyInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	ModifyInfo::write( oStream );
	
	__END_CATCH
}

void GCOtherModifyInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCOtherModifyInfoHandler::execute( this , pPlayer );
		
	__END_CATCH
}

string GCOtherModifyInfo::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCOtherModifyInfo("
		<< "ObjectID::" << (int)m_ObjectID << ","
		<< ModifyInfo::toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}
