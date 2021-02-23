//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToObjectHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToObject.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "ZoneUtil.h"
	#include "Effect.h"

	#include "skill/Sniping.h"
	#include "skill/EffectAberration.h"

	#include "Gpackets/GCSkillFailed1.h"

	//#define __PROFILE_SKILLS__

	#ifdef __PROFILE_SKILLS__
		#include "Profile.h"
	#endif
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSkillToObjectHandler::execute (CGSkillToObject* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

	try 
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		SkillType_t SkillType      = pPacket->getSkillType();

		// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
		ZoneLevel_t ZoneLevel = pZone->getZoneLevel(pCreature->getX(), pCreature->getY());
		if (ZoneLevel & COMPLETE_SAFE_ZONE)
		{
			GCSkillFailed1 _GCSkillFailed1;
			_GCSkillFailed1.setSkillType(SkillType);
			pPlayer->sendPacket(&_GCSkillFailed1);

			return;
		}
		
		ObjectID_t  TargetObjectID = pPacket->getTargetObjectID();
		CEffectID_t EffectID       = pPacket->getCEffectID();
		
		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		if ( pTargetCreature != NULL && pTargetCreature->getCreatureClass() != pCreature->getCreatureClass() )
		{
			pCreature->setLastTarget( TargetObjectID );
		}

		if ( pCreature->isFlag( Effect::EFFECT_CLASS_ABERRATION ) )
		{
			EffectAberration* pEffect = dynamic_cast<EffectAberration*>(pCreature->findEffect(Effect::EFFECT_CLASS_ABERRATION));
			if ( pEffect != NULL && (rand()%100) < pEffect->getRatio())
			{
				cout << "aberration affected " << endl;
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
				pPlayer->sendPacket(&_GCSkillFailed1);

				return;
			}
		}

		disableFlags( pCreature, pZone, SkillType);

		if (pCreature->isSlayer()) 
		{
			Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature);
			SkillSlot* pSkillSlot = ((Slayer *)pCreature)->hasSkill(SkillType);
			bool       bSuccess   = true;
			if ( SkillType == SKILL_TURRET_FIRE ) pSkillSlot = ((Slayer *)pCreature)->hasSkill(SKILL_INSTALL_TURRET);

			if (pSkillSlot == NULL) bSuccess = false;
			if (!isAbleToUseObjectSkill(pSlayer)) bSuccess = false;
/*			if (pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
			{
				g_Sniping.checkRevealRatio(pSlayer, 20, 10);
			} */

			// 만약에 같은 종족의 성물보관함이라면 기술이 사용되지 않는다.
		/*	if ( pTargetCreature->isMonster() )
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				Assert( pMonster != NULL);

				if ( pMonster->getMonsterType() == 371 || pMonster->getMonsterType() == 372 || pMonster->getMonsterType() == 373)
					bSuccess = false;
			}
*/
			if (bSuccess) 
			{
				SkillHandler* SkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(SkillHandler != NULL);

				#ifdef __PROFILE_SKILLS__
					beginProfileEx(SkillTypes2String[SkillType]);
					SkillHandler->execute(pSlayer, TargetObjectID, pSkillSlot, EffectID);
					endProfileEx(SkillTypes2String[SkillType]);
				#else
					SkillHandler->execute(pSlayer, TargetObjectID, pSkillSlot, EffectID);
				#endif
			}
			else 
			{
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
				pPlayer->sendPacket(&_GCSkillFailed1);
			}
		} 
		else if (pCreature->isVampire()) 
		{
			Vampire*          pVampire          = dynamic_cast<Vampire*>(pCreature);
			VampireSkillSlot* pVampireSkillSlot = pVampire->hasSkill(SkillType);
			bool              bSuccess          = true;

			// BITE OF DEATH 워울프 체크는 isAbleToUseObjectSkill 안에서 한다.
			if (pVampireSkillSlot == NULL && SkillType != SKILL_BITE_OF_DEATH) bSuccess = false;
			if (!isAbleToUseObjectSkill(pVampire)) bSuccess = false;

/*			if (pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
			{
				addVisibleCreature(pZone, pVampire, true);
			} */

			// 만약 EXTREME 기술을 사용한 상태라면 기술을 해제해 주어야 한다.
			// EXTREME 기술은 다른 기술과 병행해서 사용하지 못한다.
			// 이유는 EXTREME기술의 데미지 상승이 너무 크기 때문이고.
			// EXTREME기술을 사용한 상태에서 다른 기술을 사용할때 Effect가 없기 때문이다.

			// 2002.4.1
			// EXTREME 기술을 사용한 상태에서 MELEE Attack에 대해서는 사용가능하도록 수정했다.
			// 맨손 공격만으로는 너무 부족하다는 의견때문
			// EXTREME 기술을 사용한 상태에서 사용할 수 있는 MELEE Skill은
			//  ACID TOUCH, POISONOUS HAND, BLOODY NAIL이 있다.
			//                                                  

/*			if (pVampire->isFlag(Effect::EFFECT_CLASS_EXTREME))
			{
				if(!(SkillType == SKILL_ACID_TOUCH) && !(SkillType == SKILL_POISONOUS_HANDS) && !(SkillType == SKILL_BLOODY_NAIL))
				{
					EffectManager * pEffectManager = pVampire->getEffectManager();
					Assert( pEffectManager != NULL );
					Effect * pEffect = pEffectManager->findEffect( Effect::EFFECT_CLASS_EXTREME );
					if ( pEffect != NULL ) {
						pEffect->setDeadline(0);
					}
				}
			} */

			/*
			// 만약에 같은 종족의 성물보관함이라면 기술이 사용되지 않는다.
			if ( pTargetCreature->isMonster() )
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				Assert( pMonster != NULL);

				if ( pMonster->getMonsterType() == 374 || pMonster->getMonsterType() == 375 || pMonster->getMonsterType() == 376)
					bSuccess = false;
			}
			*/


			if (bSuccess) 
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);

				#ifdef __PROFILE_SKILLS__
					beginProfileEx(SkillTypes2String[SkillType]);
					pSkillHandler->execute(pVampire, TargetObjectID, pVampireSkillSlot, EffectID);
					endProfileEx(SkillTypes2String[SkillType]);
				#else
					pSkillHandler->execute(pVampire, TargetObjectID, pVampireSkillSlot, EffectID);
				#endif
			}
			else 
			{
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
				pPlayer->sendPacket(&_GCSkillFailed1);
			}
		} 
		else if (pCreature->isOusters()) 
		{
			Ousters*          pOusters          = dynamic_cast<Ousters*>(pCreature);
			OustersSkillSlot* pOustersSkillSlot = pOusters->hasSkill(SkillType);
			bool              bSuccess          = true;

			if (pOustersSkillSlot == NULL) bSuccess = false;
			if (!isAbleToUseObjectSkill(pOusters)) bSuccess = false;

			if (bSuccess) 
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);

				#ifdef __PROFILE_SKILLS__
					beginProfileEx(SkillTypes2String[SkillType]);
					pSkillHandler->execute(pOusters, TargetObjectID, pOustersSkillSlot, EffectID);
					endProfileEx(SkillTypes2String[SkillType]);
				#else
					pSkillHandler->execute(pOusters, TargetObjectID, pOustersSkillSlot, EffectID);
				#endif
			}
			else 
			{
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
				pPlayer->sendPacket(&_GCSkillFailed1);
			}
		} 
	} 
	catch (Throwable & t) 
	{ 
		//cout << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

