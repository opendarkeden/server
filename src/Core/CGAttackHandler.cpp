//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAttackHandler.cc
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAttack.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Monster.h"
	#include "Skill.h"
	#include "SkillHandlerManager.h"
	#include "CreatureUtil.h"
	#include "ItemUtil.h"
	#include "ZoneUtil.h"
	#include "CreatureUtil.h"
    #include "Effect.h"

    #include "skill/Sniping.h"

	#include "Gpackets/GCAttack.h"
	#include "Gpackets/GCGetDamage.h"
	#include "Gpackets/GCSkillFailed1.h"

	//#define __PROFILE_SKILLS__

	#ifdef __PROFILE_SKILLS__
		#include "Profile.h"
	#endif
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAttackHandler::execute (CGAttack* pPacket , Player* pPlayer)
	     
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);	// by sigi

		// 플레이어가 정상적인 상태가 아니라면 리턴한다.
		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) 
		{
			GCSkillFailed1 _GCSkillFailed1;
			_GCSkillFailed1.setSkillType(SKILL_ATTACK_MELEE);
			pPlayer->sendPacket(&_GCSkillFailed1);
			return;
		}

		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);	// by sigi

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
		ZoneLevel_t ZoneLevel = pZone->getZoneLevel(pCreature->getX(), pCreature->getY());
		if (ZoneLevel & COMPLETE_SAFE_ZONE)
		{
			GCSkillFailed1 _GCSkillFailed1;
			_GCSkillFailed1.setSkillType( SKILL_ATTACK_MELEE );
			pPlayer->sendPacket( &_GCSkillFailed1 );
			return;
		}

		Creature* pTarget = pZone->getCreature( pPacket->getObjectID() );
		if ( pTarget == NULL )
		{
			GCSkillFailed1 _GCSkillFailed1;
			_GCSkillFailed1.setSkillType( SKILL_ATTACK_MELEE );
			pPlayer->sendPacket( &_GCSkillFailed1 );
			return;
		}
		
		pCreature->setLastTarget( pTarget->getObjectID() );

		// 만약 같은 종족의 성물 보관대라면 공격하지 않도록 한다. bezz 6.8 수정 확인바람.
		
		/*
		if ( pTarget->isMonster() )
		{
			Monster* pMonster = dynamic_cast<Monster*>(pTarget);
			Assert( pMonster != NULL );

			MonsterType_t type = pMonster->getMonsterType();

			if ( ( type == 371 || type == 372 || type == 373 ) && pCreature->isSlayer() )
			{
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SKILL_ATTACK_MELEE);
				pPlayer->sendPacket( &_GCSkillFailed1 );
				return;
			}

			if ( ( type == 374 || type == 375 || type == 376) && pCreature->isVampire() )
			{
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SKILL_ATTACK_MELEE);
				pPlayer->sendPacket( &_GCSkillFailed1 );
				return;
			}

			if ( type >= 371 && type <= 376)
			{
				string RelicName = "";

				switch(type)
				{
					case 371:
						RelicName = "롬멜의훈장";
						break;
					case 372:
						RelicName = "성의";
						break;
					case 374:
						RelicName = "처녀의피";
						break;
					case 375:
						RelicName = "역십자가";
						break;
					default:
						RelicName = pMonster->getName();
				}

				// 이펙트 만들기
				EffectCombatMessage1* pEffect = new EffectCombatMessage1();
				pEffect->setNextTime(30);
				pEffect->setDelay(30);
				pEffect->setDeadline(60);
				pEffect->setRelicName(RelicName);

				// Zone에 이펙트 붙이기
				(pZone->getObjectRegistry()).registerObject(pEffect);
				pZone->addEffect(pEffect);
			}
		}
		*/
		
/*		if (pGamePlayer->isSlayer() &&
				pCreature->isMonster() &&
				(pCreature->getMonsterType() == 371 ||
				 pCreature->getMonsterType() == 372 ||
				 pCreature->getMonsterType() == 371))
			return;
	 	if (pGamePlayer->isVampire() &&
				pCreature->isMonster() &&
				(pCreature->getMonsterType() == 373 ||
				 pCreature->getMonsterType() == 374))
			return;
*/	    
		if (!isAbleToUseObjectSkill(pCreature, SKILL_ATTACK_MELEE)) return;

		if (pCreature->isSlayer())
		{ 
			Slayer* pSlayer = dynamic_cast<Slayer *>(pCreature);

			if (pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
			{
				g_Sniping.checkRevealRatio(pSlayer, 20, 10);
			}

			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			if (pItem != NULL) 
			{
				if (isArmsWeapon(pItem)) 
				{
					SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_ATTACK_ARMS);
					Assert(pSkillHandler != NULL);

					#ifdef __PROFILE_SKILLS__
						beginProfileEx(SkillTypes2String[SKILL_ATTACK_ARMS]);
						pSkillHandler->execute(pSlayer, pPacket->getObjectID());
						endProfileEx(SkillTypes2String[SKILL_ATTACK_ARMS]);
					#else
						pSkillHandler->execute(pSlayer, pPacket->getObjectID());
					#endif
				} 
				else
				{
					SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_ATTACK_MELEE);
					Assert(pSkillHandler != NULL);

					#ifdef __PROFILE_SKILLS__
						beginProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
						pSkillHandler->execute(pSlayer, pPacket->getObjectID());
						endProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
					#else
						pSkillHandler->execute(pSlayer, pPacket->getObjectID());
					#endif
				}
			} 
			else
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_ATTACK_MELEE);
				Assert(pSkillHandler != NULL);

				#ifdef __PROFILE_SKILLS__
					beginProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
					pSkillHandler->execute(pSlayer, pPacket->getObjectID());
					endProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
				#else
					pSkillHandler->execute(pSlayer, pPacket->getObjectID());
				#endif
			}
		} 
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire *>(pCreature);

			if (pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
			{
				addVisibleCreature(pZone, pVampire, true);
			}

			SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_ATTACK_MELEE);
			Assert(pSkillHandler != NULL);

			#ifdef __PROFILE_SKILLS__
				beginProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
				pSkillHandler->execute(pVampire, pPacket->getObjectID());
				endProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
			#else
				pSkillHandler->execute(pVampire, pPacket->getObjectID());
			#endif
		} 
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters *>(pCreature);

			SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_ATTACK_MELEE);
			Assert(pSkillHandler != NULL);

			#ifdef __PROFILE_SKILLS__
				beginProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
				pSkillHandler->execute(pOusters, pPacket->getObjectID());
				endProfileEx(SkillTypes2String[SKILL_ATTACK_MELEE]);
			#else
				pSkillHandler->execute(pOusters, pPacket->getObjectID());
			#endif
		} 
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString();
	}
	catch (...)
	{
	}

#endif

	__END_DEBUG
    __END_DEBUG_EX __END_CATCH
}
