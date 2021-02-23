//----------------------------------------------------------------------
//
// Filename    : SubSlayerSkillInfo.cpp
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SubSlayerSkillInfo.h"

//----------------------------------------------------------------------
// read data from socket input stream
//----------------------------------------------------------------------
void SubSlayerSkillInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	try {

	iStream.read( m_SkillType );
	iStream.read( m_Exp );
	iStream.read( m_ExpLevel );
	iStream.read( m_Interval );
	iStream.read( m_CastingTime );
	iStream.read( m_Enable );

	} catch( Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// write data to socket output stream
//----------------------------------------------------------------------
void SubSlayerSkillInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try {

	oStream.write( m_SkillType );
	oStream.write( m_Exp );
	oStream.write( m_ExpLevel );
	oStream.write( m_Interval );
	oStream.write( m_CastingTime );
	oStream.write( m_Enable );

	} catch (Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string SubSlayerSkillInfo::toString () const 
	throw ()
{
	StringStream msg;

	msg << "SubSlayerSkillInfo("
		<< ",SkillType:" << (int)m_SkillType
		<< ",Exp:" << (int)m_Exp
		<< ",ExpLevel:" << (int)m_ExpLevel
		<< ",Interval:" << (int)m_Interval
		<< ",CastingTime:" << (int)m_CastingTime
		<< ",Enable:" << (int)m_Enable
		<< ")";
	
	return msg.toString();
}
