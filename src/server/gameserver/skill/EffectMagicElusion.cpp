#include "EffectMagicElusion.h"
#include "Zone.h"

EffectMagicElusion::EffectMagicElusion( Zone* pZone, ZoneCoord_t ZoneX, ZoneCoord_t ZoneY ) throw(Error)
	: Effect( pZone, ZoneX, ZoneY, NULL, 0 )
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectMagicElusion::unaffect() throw(Error)
{
	__BEGIN_TRY

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	__END_CATCH
}

string EffectMagicElusion::toString() const throw()
{
	return "EffectMagicElusion()";
}
