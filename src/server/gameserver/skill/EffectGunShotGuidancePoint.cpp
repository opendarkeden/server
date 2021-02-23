//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGunShotGuidancePoint.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectGunShotGuidancePoint.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectGunShotGuidancePoint::EffectGunShotGuidancePoint(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = x;
	m_Y = y;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGunShotGuidancePoint::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile( m_X, m_Y );
	tile.deleteEffect( m_ObjectID );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectGunShotGuidancePoint::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectGunShotGuidancePoint("
		<< ")";
	return msg.toString();

	__END_CATCH
}

