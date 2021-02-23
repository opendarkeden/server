//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireCorpse.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "VampireCorpse.h"
#include "Creature.h"
#include "Vampire.h"

VampireCorpse::VampireCorpse (Vampire* pVampire)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pVampire != NULL);

	m_VampireInfo = pVampire->getVampireInfo3();
	setObjectID(m_VampireInfo.getObjectID());

	__END_CATCH
}

VampireCorpse::~VampireCorpse()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}
string VampireCorpse::toString ()
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "VampireCorpse("
		<< m_VampireInfo.toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}

