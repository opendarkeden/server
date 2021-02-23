//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHydroConvergence.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectHydroConvergence.h"
#include "Monster.h"
#include "Ousters.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"
#include "Zone.h"

#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHydroConvergence::EffectHydroConvergence(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_pTarget = pCreature;
	m_UserOID = 0;
	m_Damage = 0;
	m_Duration = 0;
	m_AttackNum = 0; // 受到攻击次数
	m_TrageSaveHP =0;
	if (!pCreature->isDead() && !pCreature->isOusters())
	{
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer *>(pCreature);
			m_TrageSaveHP = pSlayer->getHP();
		}
		if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire *>(pCreature);
			m_TrageSaveHP = pVampire->getHP();
		}
		if (pCreature->isMonster())
		{
			Monster* pMonsterAttacker = dynamic_cast<Monster*>(pCreature);
			m_TrageSaveHP = pMonsterAttacker->getHP();
		}

	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHydroConvergence::affect()
	throw(Error)
{
	__BEGIN_TRY
	
	setNextTime(10);
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	HP_t CurrentHP=0;
	Slayer* pSlayer;
	Vampire* pVampire;
	Monster* pMonsterAttacker;
	if (!pCreature->isDead() && !pCreature->isOusters())
	{
		if (pCreature->isSlayer())
		{
			pSlayer = dynamic_cast<Slayer *>(pCreature);
			CurrentHP = pSlayer->getHP();
		}
		if (pCreature->isVampire())
		{
			pVampire = dynamic_cast<Vampire *>(pCreature);
			CurrentHP = pVampire->getHP();
		}
		if (pCreature->isMonster())
		{
			pMonsterAttacker = dynamic_cast<Monster*>(pCreature);
			CurrentHP = pMonsterAttacker->getHP();
		}
		if ( CurrentHP < m_TrageSaveHP)
		{
			// 增加其它攻击次数
			m_AttackNum++;
			//m_TrageSaveHP = CurrentHP;
		}
		// 创建伤害
		affect(pCreature);
		if (pCreature->isSlayer())  CurrentHP = pSlayer->getHP();
		if (pCreature->isVampire())	CurrentHP = pVampire->getHP();
		if (pCreature->isMonster())	CurrentHP = pMonsterAttacker->getHP();
		// 记录当前HP
		m_TrageSaveHP = CurrentHP;
		if (m_AttackNum >=5)
		{
			setDuration(0);
			setDeadline(0);
		}
		
	}
	

	
	
	
	
// 	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
// 	affect(pCreature);
// 	int cx = pCreature->getX();
// 	int cy = pCreature->getY();
// 
// 	Zone* pZone = pCreature->getZone();
// 
// 	for ( int i=-1; i<=1; ++i )
// 	for ( int j=-1; j<=1; ++j )
// 	{
// 		int tx = cx + i;
// 		int ty = cy + j;
// 		if ( tx < 0 || ty < 0 ) continue;
// 		if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;
// 
// 		slist<Object*>& olist = pZone->getTile(tx, ty).getObjectList();
// 		slist<Object*>::iterator itr = olist.begin();
// 		for ( ; itr != olist.end() ; ++itr )
// 		{
// 			Object* pObject = *itr;
// 			if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;
// 
// 			Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
// 			if ( pTargetCreature == NULL || pTargetCreature->isOusters() || pTargetCreature == pCreature ) continue;
// 			if ( pTargetCreature->isFlag( getEffectClass() ) ) continue;
// 
// 			EffectHydroConvergence* pEffect = new EffectHydroConvergence( pTargetCreature );
// 			pEffect->setUserOID( m_UserOID );
// 			pEffect->setDamage( m_Damage );
// 			pEffect->setDeadline( m_Duration/2 );
// 			pEffect->setDuration( m_Duration/2 );
// 			pEffect->setNextTime(10);
// 			pTargetCreature->setFlag( pEffect->getEffectClass() );
// 			pTargetCreature->addEffect( pEffect );
// 
// 			GCAddEffect gcAddEffect;
// 			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
// 			gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
// 			gcAddEffect.setDuration( m_Duration/2 );
// 			
// 			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
// 
// 		}
// 	}

	//cout << "EffectHydroConvergence" << "affect BEGIN" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHydroConvergence::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	Ousters* pOusters = dynamic_cast<Ousters*>(pZone->getCreature( m_UserOID ));

	GCModifyInformation gcMI, gcAttackerMI;

	if ( canAttack( pOusters, pCreature )
	&& !(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE) )
	{
		Damage_t damage = getDamage();
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			::setDamage( pPC, damage, pOusters, SKILL_HYDRO_CONVERGENCE, &gcMI, &gcAttackerMI, true, false );
			pPC->getPlayer()->sendPacket( &gcMI );
		}
		else if ( pCreature->isMonster() )
		{
			::setDamage( pCreature, damage, pOusters, SKILL_HYDRO_CONVERGENCE, NULL, &gcAttackerMI, true, false );
		}

		if ( pOusters != NULL )
		{
			computeAlignmentChange(pCreature, damage, pOusters, &gcMI, &gcAttackerMI);
			increaseAlignment(pOusters, pCreature, gcAttackerMI);

			if (pCreature->isDead())
			{
				int exp = computeCreatureExp(pCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, gcAttackerMI);

			}

			pOusters->getPlayer()->sendPacket( &gcAttackerMI );
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHydroConvergence::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	pCreature->removeFlag(Effect::EFFECT_CLASS_HYDRO_CONVERGENCE);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HYDRO_CONVERGENCE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHydroConvergence::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectHydroConvergence" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	// 读取5*5范围内对象,并创建伤害
	// 	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
		// 创建目标伤害
	 	affect(pCreature);

	 	int cx = pCreature->getX();
	 	int cy = pCreature->getY();
	// 
	 	Zone* pZone = pCreature->getZone();
	// 
	 	for ( int i=-2; i<=2; ++i )
	 	for ( int j=-2; j<=2; ++j )
	 	{
	 		int tx = cx + i;
	 		int ty = cy + j;
	 		if ( tx < 0 || ty < 0 ) continue;
	 		if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;
	 
	 		slist<Object*>& olist = pZone->getTile(tx, ty).getObjectList();
	 		slist<Object*>::iterator itr = olist.begin();
	 		for ( ; itr != olist.end() ; ++itr )
	 		{
	 			Object* pObject = *itr;
	 			if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;
	 
	 			Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
	 			if ( pTargetCreature == NULL || pTargetCreature->isOusters() || pTargetCreature == pCreature ) continue;
	 			if ( pTargetCreature->isFlag( getEffectClass() ) ) continue;
				// 创建伤害
				affect(pTargetCreature);
// 	 			EffectHydroConvergence* pEffect = new EffectHydroConvergence( pTargetCreature );
// 	 			pEffect->setUserOID( m_UserOID );
// 	 			pEffect->setDamage( m_Damage );
// 	 			pEffect->setDeadline( m_Duration/2 );
// 	 			pEffect->setDuration( m_Duration/2 );
// 	 			pEffect->setNextTime(10);
// 	 			pTargetCreature->setFlag( pEffect->getEffectClass() );
// 	 			pTargetCreature->addEffect( pEffect );
// 	 
// 	 			GCAddEffect gcAddEffect;
// 	 			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
// 	 			gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
// 	 			gcAddEffect.setDuration( m_Duration/2 );
// 	 			
// 	 			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
	 
	 		}
	 	}
	unaffect(pCreature);

	//cout << "EffectHydroConvergence" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHydroConvergence::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectHydroConvergence("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

