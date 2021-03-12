
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDivineGuidance.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectDivineGuidance.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDivineGuidance::EffectDivineGuidance(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDivineGuidance::affect()
	
{
	__BEGIN_TRY

	//cout << "EffectDivineGuidance " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectDivineGuidance " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDivineGuidance::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectDivineGuidance " << "begin" << endl;
	//cout << "EffectDivineGuidance " << "end" << endl;
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		&& !pCreature->isDead()
		&& !pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
		// 무적상태 체크. by sigi. 2002.9.5
		&& canAttack( pAttacker, pCreature )
	   )
	{
		GCModifyInformation gcMI, gcAttackerMI;
		setDamage( pCreature, m_Point, pAttacker, SKILL_DIVINE_GUIDANCE, &gcMI, &gcAttackerMI );
		if ( pCreature->isPC() ) pCreature->getPlayer()->sendPacket( &gcMI );

		if (pAttacker!=NULL) 
		{
			computeAlignmentChange( pCreature, m_Point, pAttacker, &gcMI, &gcAttackerMI );
			if ( pAttacker->isPC() )
			{ 
				if ( pAttacker->isSlayer() && !pCreature->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pAttacker);

					if ( pSlayer != NULL )
					{
						GCModifyInformation gcMI;
						shareAttrExp( pSlayer, m_Point, 1, 1, 8, gcAttackerMI );
					}
				}

				if ( pAttacker->isPC() ) pAttacker->getPlayer()->sendPacket( &gcAttackerMI );
			}
		}

	}

	setNextTime( m_Tick );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDivineGuidance::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	pCreature->removeFlag(Effect::EFFECT_CLASS_DIVINE_GUIDANCE);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_DIVINE_GUIDANCE );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect );

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDivineGuidance::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDivineGuidance::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDivineGuidance("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

