#include "Pet.h"
#include "PetInfo.h"
#include "PetUtil.h"
#include "GamePlayer.h"
#include "Corpse.h"
#include "skill/SkillUtil.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCPetUseSkill.h"
#include "CreatureUtil.h"

Pet* Pet::makePet( PlayerCreature* pOwner, PetInfo* pPetInfo )
{
	if ( pPetInfo == NULL ) return NULL;

	Pet* pPet = NULL;

	switch ( pPetInfo->getPetType() )
	{
		case PET_CENTAURO:
			pPet = new Centauro(pOwner, pPetInfo);
			break;
		case PET_STIRGE:
			pPet = new Stirge(pOwner, pPetInfo);
			break;
		case PET_PIXIE:
			pPet = new Pixie(pOwner, pPetInfo);
			break;
		default:
			return NULL;
	}

	Assert( pPet != NULL );
	getCurrentTime( pPet->m_SkillDelay );

	// 1/10초 단위 딜레이
	int delay = pPet->getDelay();

	pPet->m_SkillDelay.tv_sec += delay/10;
	pPet->m_SkillDelay.tv_usec += (delay%10) * 100000;

	return pPet;
}

void Pet::heartbeat(const Timeval& currentTime)
{
	if ( !canUseSkill() ) return;

	if ( m_SkillDelay < currentTime )
	{
		if ( useSkill() )
		{
			// 1/10초 단위 딜레이
			int delay = getDelay();

			m_SkillDelay = currentTime;
			m_SkillDelay.tv_sec += delay/10;
			m_SkillDelay.tv_usec += (delay%10) * 100000;
		}
	}
}

bool Pet::canUseSkill() const 
{
	return getPetInfo()->canAttack() != 0;
}

bool AttackingPet::useSkill()
{
	ObjectID_t TargetOID = getOwner()->getLastTarget();
	if ( TargetOID == 0 ) return false;

	PlayerCreature* pOwner = getOwner();
	if ( pOwner == NULL ) return false;

	Zone* pZone = getOwner()->getZone();
	if ( pZone == NULL ) return false;
	
	Creature* pTarget = pZone->getCreature( TargetOID );
	if ( pTarget == NULL || pTarget->isDead() || !canAttack( getOwner(), pTarget ) )
	{
		getOwner()->setLastTarget( 0 );
		return false;
	}

	Range_t range = getRange();
	if ( !verifyDistance( pOwner, pTarget, range ) ) return false;

	Damage_t damage = getDamage();

	GCPetUseSkill gcPetUseSkill;
	gcPetUseSkill.setAttacker( pOwner->getObjectID() );
	gcPetUseSkill.setTarget( TargetOID );

	pZone->broadcastSkillPacket( pOwner->getX(), pOwner->getY(), pTarget->getX(), pTarget->getY(), &gcPetUseSkill, list<Creature*>() );

	GCModifyInformation gcAttackerMI, gcTargetMI;
	setDamage( pTarget, damage, pOwner, SKILL_ATTACK_MELEE, &gcTargetMI, &gcAttackerMI, false );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>( pOwner->getPlayer() );
	PetExp_t exp = 1;
	if ( pGamePlayer != NULL && pGamePlayer->isPayPlaying() )
	{
		exp = 2;
	}

	increasePetExp( getPetInfo(), exp, &gcAttackerMI );
	addOlympicStat( pOwner, 8, exp );

	if ( pTarget->isPC() )
	{
		pTarget->getPlayer()->sendPacket( &gcTargetMI );
	}

	pOwner->getPlayer()->sendPacket( &gcAttackerMI );

	return true;
}

int Centauro::getDelay() const
{
	return ( 80 - ( getPetInfo()->getPetLevel() * 10 / 15 ) );
}

int Centauro::getRange() const
{
	return 3 + ( getPetInfo()->getPetLevel() / 20 );
}

int Centauro::getDamage() const 
{
	return 5 + ( getPetInfo()->getPetLevel() / 5 );
}

int Stirge::getDelay() const
{
	return ( 80 - ( getPetInfo()->getPetLevel() * 10 / 15 ) );
}

int Stirge::getRange() const
{
	return 3 + ( getPetInfo()->getPetLevel() / 20 );
}

int Stirge::getDamage() const 
{
	return 5 + ( getPetInfo()->getPetLevel() / 5 );
}

int Pixie::getDelay() const 
{
	return ( 80 - ( getPetInfo()->getPetLevel() ) );
}

int Pixie::getRange() const
{
	return 2 + ( getPetInfo()->getPetLevel() / 20 );
}

bool Pixie::useSkill()
{
	ObjectID_t TargetOID = getOwner()->getLastTarget();
	if ( TargetOID == 0 ) return false;

	Zone* pZone = getOwner()->getZone();
	if ( pZone == NULL ) return false;
	
	Ousters* pOwner = dynamic_cast<Ousters*>(getOwner());
	if ( pOwner == NULL ) return false;

	if ( pOwner->getMP( ATTR_MAX ) <= pOwner->getMP( ATTR_CURRENT ) ) return false;

	Creature* pTarget = pZone->getCreature( TargetOID );
	Corpse* pTargetCorpse = dynamic_cast<Corpse*>(pZone->getItem( TargetOID ));

	ZoneCoord_t X, Y;

	if ( pTarget != NULL )
	{
		if ( pTarget->isFlag( Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL ) || !pTarget->isFlag( Effect::EFFECT_CLASS_COMA ) ) return false;
		X = pTarget->getX();
		Y = pTarget->getY();
	}
	else if ( pTargetCorpse != NULL )
	{
		if ( pTargetCorpse->isFlag( Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL ) ) return false;
		X = pTargetCorpse->getX();
		Y = pTargetCorpse->getY();
	}
	else
	{
		getOwner()->setLastTarget(0);
		return false;
	}

//	cout << "타겟 확인" << endl;

	Range_t range = getRange();
	if ( !verifyDistance( pOwner, X, Y, range ) ) return false;

//	cout << "거리 확인" << endl;

	int HealPoint;

	if ( pTarget != NULL )
	{
		HealPoint = computeCreatureExp( pTarget, BLOODDRAIN_EXP );
	}
	else
	{
		HealPoint = getPercentValue(pTargetCorpse->getExp(), 60);
	}

	HealPoint = HealPoint * getPetInfo()->getPetLevel() * 3 / 500;

//	cout << "힐 포인트 : " << HealPoint << endl;
	
	GCPetUseSkill gcPetUseSkill;
	gcPetUseSkill.setAttacker( pOwner->getObjectID() );
	gcPetUseSkill.setTarget( TargetOID );

	pZone->broadcastSkillPacket( pOwner->getX(), pOwner->getY(), X, Y, &gcPetUseSkill, list<Creature*>() );

	MP_t NewMP = min( (int)pOwner->getMP( ATTR_MAX ), pOwner->getMP( ATTR_CURRENT ) + HealPoint );
	pOwner->setMP( NewMP, ATTR_CURRENT );

	GCModifyInformation gcAttackerMI;
	gcAttackerMI.addLongData( MODIFY_CURRENT_MP, NewMP );

	pOwner->getPlayer()->sendPacket( &gcAttackerMI );

	if ( pTarget != NULL )
	{
		pTarget->setFlag( Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL );
	}
	else
	{
		pTargetCorpse->setFlag( Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL );
	}

	return true;
}
