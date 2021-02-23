//////////////////////////////////////////////////////////////////////////////
// Filename    : RideMotorcycleSlotInfo.cpp
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "RideMotorcycleSlotInfo.h"

//////////////////////////////////////////////////////////////////////////////
// read data from socket input stream
//////////////////////////////////////////////////////////////////////////////
void RideMotorcycleSlotInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try 
	{
		PCItemInfo::read(iStream);

		iStream.read( m_InvenX );
		iStream.read( m_InvenY );
	} 
	catch( Throwable & t ) 
	{
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// write data to socket output stream
//////////////////////////////////////////////////////////////////////////////
void RideMotorcycleSlotInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try 
	{
		PCItemInfo::write(oStream);

		oStream.write( m_InvenX );
		oStream.write( m_InvenY );
	} 
	catch (Throwable & t ) 
	{
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string RideMotorcycleSlotInfo::toString () const 
	throw ()
{
	StringStream msg;

	msg << "RideMotorcycleSlotInfo("
		<< PCItemInfo::toString()
		<< ",InvenX:" << (int)m_InvenX
		<< ",InvenY:" << (int)m_InvenY
		<< ")";
	
	return msg.toString();
}
