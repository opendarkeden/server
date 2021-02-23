//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDarkBluePoison.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDarkBluePoison.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "SkillHandler.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDarkBluePoison::EffectDarkBluePoison(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_Level = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDarkBluePoison::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDarkBluePoison " << "affect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectDarkBluePoison " << "affect END" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDarkBluePoison::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDarkBluePoison " << "affect BEGIN" << endl;

	Assert(pCreature != NULL);

	if ( canAttack( NULL, pCreature ) )
	{
		// 슬레이어일 경우에만 독 데미지가 존재한다.
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Assert(pSlayer != NULL);

			//int PoisonDamage = computeMagicDamage(pSlayer, m_Damage, SKILL_DARKBLUE_POISON);

			MP_t CurrentMP = pSlayer->getMP(ATTR_CURRENT);
			MP_t RemainMP  = max(0,(int)CurrentMP - m_Damage);

			pSlayer->setMP(RemainMP, ATTR_CURRENT);

			GCModifyInformation gcMI;
			gcMI.addShortData(MODIFY_CURRENT_MP, RemainMP);

			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);
			pPlayer->sendPacket(&gcMI);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			Assert(pOusters != NULL);

			//int PoisonDamage = computeMagicDamage(pOusters, m_Damage, SKILL_DARKBLUE_POISON);

			// 아우스터즈는 1/2만 깎인다.
			MP_t CurrentMP = pOusters->getMP(ATTR_CURRENT);
			MP_t RemainMP  = max(0,(int)CurrentMP - (m_Damage/2));

			pOusters->setMP(RemainMP, ATTR_CURRENT);

			GCModifyInformation gcMI;
			gcMI.addShortData(MODIFY_CURRENT_MP, RemainMP);

			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);
			pPlayer->sendPacket(&gcMI);
		}
	}
	
	setNextTime(m_Tick);

	//cout << "EffectDarkBluePoison " << "affect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDarkBluePoison::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDarkBluePoison::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectDarkBluePoison " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// 크리쳐에게서 플래그를 제거한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_DARKBLUE_POISON);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	if (pCreature->isPC())
	{
		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pCreature->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		//pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

		Player* pPlayer = pCreature->getPlayer();
		Assert(pPlayer != NULL);
		pPlayer->sendPacket(&gcRemoveEffect);
	}

	//cout << "EffectDarkBluePoison " << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDarkBluePoison::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDarkBluePoison " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectDarkBluePoison " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDarkBluePoison::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDarkBluePoison::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectDarkBluePoison("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

