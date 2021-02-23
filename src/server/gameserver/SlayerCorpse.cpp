//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerCorpse.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SlayerCorpse.h"
#include "Creature.h"
#include "Slayer.h"

SlayerCorpse::SlayerCorpse (Slayer* pSlayer)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);

	m_SlayerInfo = pSlayer->getSlayerInfo3();
	setObjectID(m_SlayerInfo.getObjectID());

	__END_CATCH
}

SlayerCorpse::~SlayerCorpse()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string SlayerCorpse::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "SlayerCorpse(" 
		<< m_SlayerInfo.toString() 
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
