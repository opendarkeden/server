//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTurretLaser.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectTurretLaser.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Tile.h"
#include "Creature.h"
#include "SkillUtil.h"
#include "Player.h"
#include "GCModifyInformation.h"
#include "GCAddEffectToTile.h"

#include <list>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTurretLaser::EffectTurretLaser(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y )
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTurretLaser::affect()
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pZone != NULL);

	setNextTime(5);

	affect(m_pZone, m_X, m_Y);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTurretLaser::affect(Zone* pZone, ZoneCoord_t Cx, ZoneCoord_t Cy)
	throw(Error)
{
	__BEGIN_TRY

	if (!isValidZoneCoord(pZone, Cx, Cy ) ) return;
	Tile& rTile = pZone->getTile(Cx, Cy);
	list<Object*>& oList = rTile.getObjectList();
	list<Object*>::iterator itr = oList.begin();

	for (; itr != oList.end(); ++itr )
	{
		Object* pObject = *itr;
		if (pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

		Creature* pCreature = dynamic_cast<Creature*>(pObject);
		if (pCreature->isMonster() || pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_REINFORCE ) || pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_DEFENDER ) )
			continue;

		GCModifyInformation gcMI;

		setDamage(pCreature, 50, NULL, SKILL_ATTACK_MELEE, &gcMI, NULL, true);
		if (pCreature->isPC() ) pCreature->getPlayer()->sendPacket(&gcMI);

		GCAddEffectToTile gcAE;
		gcAE.setObjectID(0);
		gcAE.setDuration(2);
		gcAE.setEffectID(Effect::EFFECT_CLASS_TURRET_LASER_ATTACK);

		for (int i=-1; i<=1; ++i )
		{
			gcAE.setXY(Cx+i, Cy+i);
			pZone->broadcastPacket(Cx+i, Cy+i, &gcAE);
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTurretLaser::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTurretLaser::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTurretLaser("
		<< ")";
	return msg.toString();

	__END_CATCH
}

