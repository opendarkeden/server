//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDropItemToZone.cc 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCDropItemToZone.h"
#include "Assert.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCDropItemToZone::GCDropItemToZone() 
     throw ()
{
	__BEGIN_TRY

	m_DropPetOID=0;

	__END_CATCH
}

	
//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCDropItemToZone::~GCDropItemToZone() 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void GCDropItemToZone::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	GCAddItemToZone::read(iStream);
	iStream.read( m_DropPetOID );
}

void GCDropItemToZone::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	GCAddItemToZone::write(oStream);
	oStream.write( m_DropPetOID );
}

//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCDropItemToZone::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCDropItemToZoneHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// toString
//////////////////////////////////////////////////////////////////////
string GCDropItemToZone::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCDropItemToZone("
		<< "ObjectID:"     << m_ObjectID
		<< ",X:"           << (int)m_X 
		<< ",Y:"           << (int)m_Y 
		<< ",ItemClass:"   << (int)m_ItemClass
		<< ",ItemType:"    << (int)m_ItemType
		<< ",OptionTypeSize:"  << (int)m_OptionType.size()
		<< ",Durability:"  << (int)m_Durability
		<< ",ItemNum:"     << (int)m_ItemNum
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
