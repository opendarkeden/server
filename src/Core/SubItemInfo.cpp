//----------------------------------------------------------------------
//
// Filename    : SubItemInfo.cpp
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SubItemInfo.h"

//----------------------------------------------------------------------
// read data from socket input stream
//----------------------------------------------------------------------
void SubItemInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	try {

	iStream.read( m_ObjectID );
	iStream.read( m_IClass );
	iStream.read( m_ItemType );
	iStream.read( m_ItemNum );
	iStream.read( m_SlotID );

	} catch( Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// write data to socket output stream
//----------------------------------------------------------------------
void SubItemInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try {

	oStream.write( m_ObjectID );
	oStream.write( m_IClass );
	oStream.write( m_ItemType );
	oStream.write( m_ItemNum );
	oStream.write( m_SlotID );

	} catch (Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string SubItemInfo::toString () const 
	throw ()
{
	StringStream msg;

	msg << "SubItemInfo("
		<< "ObjectID:" << m_ObjectID
		<< ",ItemClass:" << m_IClass
		<< ",ItemType:" << m_ItemType
		<< ",Number:" << m_ItemNum
		<< ",SlotID:" << m_SlotID
		<< ")";
	
	return msg.toString();
}
