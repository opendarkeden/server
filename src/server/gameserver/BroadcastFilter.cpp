/////////////////////////////////////////////////////////////////////////////
// BroadcastFilter.cpp
/////////////////////////////////////////////////////////////////////////////

// include files
#include "BroadcastFilter.h"
#include "GamePlayer.h"
#include "Creature.h"

/////////////////////////////////////////////////////////////////////////////
// class BroadcastFilterRace
/////////////////////////////////////////////////////////////////////////////
bool BroadcastFilterRace::isSatisfy( GamePlayer* pGamePlayer )
	throw()
{
	__BEGIN_TRY

	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	return pCreature->getRace() == m_Race;

	__END_CATCH
}

BroadcastFilter* BroadcastFilterRace::Clone()
	throw()
{
	__BEGIN_TRY

	BroadcastFilter* pFilter = new BroadcastFilterRace( m_Race );

	return pFilter;

	__END_CATCH
}

