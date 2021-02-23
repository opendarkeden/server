//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectVampirePortal.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectVampirePortal.h"
#include "EffectPoison.h"
#include "EffectProtectionFromPoison.h"
#include "Creature.h"
#include "Vampire.h"
#include "DB.h"

#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCDeleteEffectFromTile.h"
#include "SkillHandler.h"

#include "item/VampirePortalItem.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectVampirePortal::EffectVampirePortal(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
	throw(Error)
{
	__BEGIN_TRY

	m_pZone              = pZone;
	m_X                  = x;
	m_Y                  = y;
	m_Duration           = 0;
	m_Count              = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampirePortal::affect(Creature* pTargetCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampirePortal::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampirePortal::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectVampirePortal::unaffect() begin" << endl;

	// 타일에서 이펙트를 삭제하고...
	Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	// 이펙트가 사라졌다고 알려준다.
	GCDeleteEffectFromTile gcDeleteEffectFromTile;
	gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);
	gcDeleteEffectFromTile.setObjectID(m_ObjectID);
	gcDeleteEffectFromTile.setXY(m_X, m_Y);
	m_pZone->broadcastPacket(m_X, m_Y, &gcDeleteEffectFromTile);

	//cout << "EffectVampirePortal::unaffect() end" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectVampirePortal::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectVampirePortal::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectVampirePortal("
		<< "DayTime:" << m_Deadline.tv_sec
		<< ")";
	return msg.toString();

	__END_CATCH

}
