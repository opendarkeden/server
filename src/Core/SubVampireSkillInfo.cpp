//----------------------------------------------------------------------
//
// Filename    : SubVampireSkillInfo.cpp
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SubVampireSkillInfo.h"

//----------------------------------------------------------------------
// read data from socket input stream
//----------------------------------------------------------------------
void SubVampireSkillInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	try {

	iStream.read( m_SkillType );
	iStream.read( m_Interval );
	iStream.read( m_CastingTime );

	} catch( Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// write data to socket output stream
//----------------------------------------------------------------------
void SubVampireSkillInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try {

	oStream.write( m_SkillType );
	oStream.write( m_Interval );
	oStream.write( m_CastingTime );

	} catch (Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string SubVampireSkillInfo::toString () const 
	throw ()
{
	StringStream msg;

	msg << "SubVampireSkillInfo("
		<< ",SkillType:" << (int)m_SkillType
		<< ",Interval:" << (int)m_Interval
		<< ",CastingTime:" << (int)m_CastingTime
		<< ")";
	
	return msg.toString();
}
