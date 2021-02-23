//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTrapInstalled.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectTrapInstalled.h"
#include "Zone.h"
#include "Tile.h"
#include "Player.h"

#include "EffectTrapTriggered.h"
#include "Monster.h"
#include "SkillUtil.h"
#include "SkillInfo.h"

#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCModifyInformation.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectTrapInstalled::EffectTrapInstalled( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y )
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
void EffectTrapInstalled::affect()
	throw(Error)
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTrapInstalled::affect(Zone* pZone, ZoneCoord_t Cx, ZoneCoord_t Cy)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTrapInstalled::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;
	if ( m_pZone == NULL ) return;
	if ( pCreature->getX() != m_X || pCreature->getY() != m_Y ) return;

	Creature* pCaster = m_pZone->getCreature( m_UserOID );
	
	if ( pCaster != NULL && pCaster->isSlayer() )
	{
		GCModifyInformation gcAttackerMI;
		Slayer* pCastSlayer = dynamic_cast<Slayer*>( pCaster );

		SkillSlot* pSkillSlot = pCastSlayer->getSkill( SKILL_INSTALL_TRAP );
		if ( pSkillSlot != NULL )
		{
			SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_INSTALL_TRAP );
			SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pCastSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);

			// 걸릴때 경험치 주기
			shareAttrExp(pCastSlayer, ExpUp, 1,8,1, gcAttackerMI);
			increaseDomainExp(pCastSlayer, DomainType, pSkillInfo->getPoint(), gcAttackerMI);
			increaseSkillExp(pCastSlayer, DomainType, pSkillSlot, pSkillInfo, gcAttackerMI);

			pCastSlayer->getPlayer()->sendPacket( &gcAttackerMI );
		}
	}

	if ( pCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		if ( pMonster->isMaster() 
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
		) return;
	}

	EffectTrapTriggered* pEffect = new EffectTrapTriggered( pCreature );
	pEffect->setDeadline( m_Tick );

	pCreature->setFlag( Effect::EFFECT_CLASS_TRAPPED );
	pCreature->addEffect( pEffect );

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID( pCreature->getObjectID() );
	gcAddEffect.setEffectID( Effect::EFFECT_CLASS_TRAP_TRIGGERED );
	gcAddEffect.setDuration( m_Tick );

	m_pZone->broadcastPacket( m_X, m_Y, &gcAddEffect );
	setDeadline(0);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectTrapInstalled::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile( m_X, m_Y );
	if ( !tile.hasEffect() ) return;

	tile.deleteEffect( m_ObjectID );

	GCDeleteEffectFromTile gcDeleteEffect;
	gcDeleteEffect.setXY( m_X, m_Y );
	gcDeleteEffect.setObjectID( getObjectID() );
	gcDeleteEffect.setEffectID( getSendEffectClass() );

	m_pZone->broadcastPacket( m_X, m_Y, &gcDeleteEffect );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectTrapInstalled::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectTrapInstalled("
		<< ")";
	return msg.toString();

	__END_CATCH
}

