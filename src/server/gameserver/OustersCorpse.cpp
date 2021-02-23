//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersCorpse.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "OustersCorpse.h"
#include "Creature.h"
#include "Ousters.h"

OustersCorpse::OustersCorpse (Ousters* pOusters)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);

	m_OustersInfo = pOusters->getOustersInfo3();
	setObjectID(m_OustersInfo.getObjectID());

	__END_CATCH
}

OustersCorpse::~OustersCorpse()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}
string OustersCorpse::toString ()
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "OustersCorpse("
		<< m_OustersInfo.toString()
		<< ")";
	return msg.toString();

	__END_CATCH
}

