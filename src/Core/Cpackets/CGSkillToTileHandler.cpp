//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToTileHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToTile.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "Creature.h"
	#include "ZoneUtil.h"
	
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
void CGSkillToTileHandler::execute (CGSkillToTile* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		// 특수기술 테스트를 위해서 임시로 넣어두는 코드이다.
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		Assert(pGamePlayer != NULL);	// by sigi

		if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Assert(pCreature != NULL);	// by sigi

			Zone* pZone = pCreature->getZone();
			Assert(pZone != NULL);
		
			SkillType_t SkillType = pPacket->getSkillType();

			// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
			ZoneLevel_t ZoneLevel = pZone->getZoneLevel(pCreature->getX(), pCreature->getY());
			if (ZoneLevel & COMPLETE_SAFE_ZONE)
			{
				GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
				pPlayer->sendPacket(&_GCSkillFailed1);

				return;
			}

			if ( pCreature->isFlag( Effect::EFFECT_CLASS_ABERRATION ) )
			{
				EffectAberration* pEffect = dynamic_cast<EffectAberration*>(pCreature->findEffect(Effect::EFFECT_CLASS_ABERRATION));
				if ( pEffect != NULL && (rand()%100) < pEffect->getRatio())
				{
					cout << "aberration affected " << endl;
					Dir_t dir = rand()%8;
					pPacket->setX( pPacket->getX() + dirMoveMask[dir].x*3 );
					pPacket->setY( pPacket->getY() + dirMoveMask[dir].y*3 );
				}
			}

			disableFlags( pCreature, pZone, SkillType);
		
			if (pCreature->isSlayer()) 
			{
				Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature);
				SkillSlot* pSkillSlot = ((Slayer *)pCreature)->hasSkill(SkillType);
				bool       bSuccess   = true;

				if ( SkillType == SKILL_BURNING_SOL_LAUNCH )
				{
					pSkillSlot = ((Slayer *)pCreature)->hasSkill(SKILL_BURNING_SOL_CHARGING);
				}

				if ( SkillType == SKILL_SWEEP_VICE_3 || SkillType == SKILL_SWEEP_VICE_5 )
				{
					pSkillSlot = ((Slayer *)pCreature)->hasSkill(SKILL_SWEEP_VICE_1);
				}

				if ( SkillType == SKILL_TURRET_FIRE ) pSkillSlot = ((Slayer *)pCreature)->hasSkill(SKILL_INSTALL_TURRET);

				if (pSkillSlot == NULL) bSuccess = false;
				if (!isAbleToUseTileSkill(pSlayer)) bSuccess = false;

/*				if (pCreature->isSlayer() && pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
					Assert(pSlayer != NULL);
					g_Sniping.checkRevealRatio(pSlayer, 20, 10);
				} */

				if (bSuccess)
				{
					SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
					Assert(pSkillHandler != NULL);

					#ifdef __PROFILE_SKILLS__
						beginProfileEx(SkillTypes2String[SkillType]);
						pSkillHandler->execute(pSlayer, pPacket->getX(), pPacket->getY(), pSkillSlot, pPacket->getCEffectID());
						endProfileEx(SkillTypes2String[SkillType]);
					#else
						pSkillHandler->execute(pSlayer, pPacket->getX(), pPacket->getY(), pSkillSlot, pPacket->getCEffectID());
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

				if (SkillType == SKILL_EAT_CORPSE && pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF))
				{
					SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_EAT_CORPSE);
					Assert(pSkillHandler != NULL);
					pSkillHandler->execute(pVampire, pPacket->getX(), pPacket->getY(), pVampireSkillSlot, pPacket->getCEffectID());
					return;
				}

				if (pVampireSkillSlot == NULL) bSuccess = false;
				if (!isAbleToUseTileSkill(pVampire)) bSuccess = false;

/*				if (pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
				{
					addVisibleCreature(pZone, pVampire, true);
				}

                if (pVampire->isFlag(Effect::EFFECT_CLASS_EXTREME))
	            {
	            	EffectManager * pEffectManager = pVampire->getEffectManager();
	            	Assert( pEffectManager != NULL );
	            	Effect * pEffect = pEffectManager->findEffect( Effect::EFFECT_CLASS_EXTREME );
	            	if ( pEffect != NULL ) {
	            		pEffect->setDeadline(0);
	            	}
				} */
				if (bSuccess)
				{
					SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
					Assert(pSkillHandler != NULL);

					#ifdef __PROFILE_SKILLS__
						beginProfileEx(SkillTypes2String[SkillType]);
						pSkillHandler->execute(pVampire, pPacket->getX(), pPacket->getY(), pVampireSkillSlot, pPacket->getCEffectID());
						endProfileEx(SkillTypes2String[SkillType]);
					#else
						pSkillHandler->execute(pVampire, pPacket->getX(), pPacket->getY(), pVampireSkillSlot, pPacket->getCEffectID());
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
				if (!isAbleToUseTileSkill(pOusters)) bSuccess = false;
				if ( SkillType == SKILL_DESTRUCTION_SPEAR && pOusters->hasSkill(SKILL_DESTRUCTION_SPEAR_MASTERY) == NULL )
				{
					cout << "has no mastery : destruction spear" << endl;
					bSuccess = false;
				}
				if ( SkillType == SKILL_ICE_LANCE && pOusters->hasSkill(SKILL_ICE_LANCE_MASTERY) == NULL )
				{
					cout << "has no mastery : ice lance" << endl;
					bSuccess = false;
				}

				if (bSuccess)
				{
					SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
					Assert(pSkillHandler != NULL);

					#ifdef __PROFILE_SKILLS__
						beginProfileEx(SkillTypes2String[SkillType]);
						pSkillHandler->execute(pOusters, pPacket->getX(), pPacket->getY(), pOustersSkillSlot, pPacket->getCEffectID());
						endProfileEx(SkillTypes2String[SkillType]);
					#else
						pSkillHandler->execute(pOusters, pPacket->getX(), pPacket->getY(), pOustersSkillSlot, pPacket->getCEffectID());
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
	} 
	catch(Throwable & t) 
	{
		//cout << t.toString() << endl;
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

