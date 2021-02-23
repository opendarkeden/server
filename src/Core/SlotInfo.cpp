//----------------------------------------------------------------------
//
// Filename    : SlotInfo.cpp
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SlotInfo.h"

//----------------------------------------------------------------------
// read data from socket input stream
//----------------------------------------------------------------------
void SlotInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	try {

	iStream.read( m_ObjectID );
	iStream.read( m_IClass );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );

	for (int i=0; i<optionSize; i++)
	{
		OptionType_t optionType;
		iStream.read( optionType );
		addOptionType( optionType );
	}

	iStream.read( m_InvenX );
	iStream.read( m_InvenY );
	iStream.read( m_ItemNum );
	iStream.read( m_MainColor );

	} catch( Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// write data to socket output stream
//----------------------------------------------------------------------
void SlotInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try {

	oStream.write( m_ObjectID );
	oStream.write( m_IClass );
	oStream.write( m_ItemType );

	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );

	list<OptionType_t>::const_iterator itr = m_OptionType.begin();
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
		oStream.write( optionType );
	}

	oStream.write( m_InvenX );
	oStream.write( m_InvenY );
	oStream.write( m_ItemNum );
	oStream.write( m_MainColor );

	} catch (Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string SlotInfo::toString () const 
	throw ()
{
	StringStream msg;

	msg << "SlotInfo("
		<< ",ObjectID:" << (int)m_ObjectID
		<< ",ItemClass:" << (int)m_IClass
		<< ",ItemType:" << (int)m_ItemType
		<< ",OptionTypeSize:" << (int)m_OptionType.size()
		<< ",InvenX:" << (int)m_InvenX
		<< ",InvenY:" << (int)m_InvenY
		<< ",Number:" << (int)m_ItemNum
		<< ",MainColor:" << (int)m_MainColor
		<< ")";
	
	return msg.toString();
}
