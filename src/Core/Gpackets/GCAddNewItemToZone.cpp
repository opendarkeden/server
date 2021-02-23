//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddNewItemToZone.cc 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCAddNewItemToZone.h"
#include "Assert.h"

//--------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------
GCAddNewItemToZone::GCAddNewItemToZone() 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//--------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------
GCAddNewItemToZone::~GCAddNewItemToZone() 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddNewItemToZone::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddNewItemToZoneHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddNewItemToZone::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GCAddNewItemToZone("
		<< "ObjectID:" << m_ObjectID
		<< ",X:" << (int)m_X 
		<< ",Y:" << (int)m_Y 
		<< ",ItemClass: " << (int)m_ItemClass
		<< ",ItemType: " << (int)m_ItemType
		<< ",OptionTypeSize: " << (int)m_OptionType.size()
		<< ",Durability: " << (int)m_Durability
		<< ",ItemNum: " << (int)m_ItemNum
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
