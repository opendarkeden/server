
#include "EffectKeepSweeper.h"
#include "Item.h"
#include "GCRemoveEffect.h"

EffectKeepSweeper::EffectKeepSweeper(Item* pItem) 
{
	__BEGIN_TRY

	setTarget( pItem );
	m_Part = 0;

	__END_CATCH
}

void EffectKeepSweeper::unaffect() 
{
	__BEGIN_TRY

	Item* pItem = dynamic_cast<Item*>(m_pTarget);
	Assert( pItem != NULL );

	pItem->removeFlag( getEffectClass() );

	__END_CATCH
}

string EffectKeepSweeper::toString() const 
{
	__BEGIN_TRY

	return "EffectKeepSweeper";

	__END_CATCH
}
