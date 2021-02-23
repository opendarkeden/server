//////////////////////////////////////////////////////////////////////////////
// Filename    : CGBloodDrainHandler.cpp
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGBloodDrain.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Vampire.h"
	#include "Monster.h"
	#include "Skill.h"
	#include "SkillHandlerManager.h"
	#include "ZonePlayerManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCAttack.h"
	#include "Gpackets/GCGetDamage.h"
	#include "Gpackets/GCSkillFailed1.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGBloodDrainHandler::execute (CGBloodDrain* pPacket , Player* pPlayer)
	     throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);

		if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Assert(pCreature != NULL);

			// 뱀파이어가 아닌 놈이 흡혈을 할 수는 없다.
			if (!pCreature->isVampire()) return;

			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
			ZoneLevel_t ZoneLevel = pCreature->getZone()->getZoneLevel(pCreature->getX(), pCreature->getY());
			if ((ZoneLevel & COMPLETE_SAFE_ZONE)
				|| (!isAbleToUseObjectSkill(pVampire, SKILL_BLOOD_DRAIN)))
			{
				GCSkillFailed1 gcSkillFailed1;
				gcSkillFailed1.setSkillType(SKILL_BLOOD_DRAIN);
				pPlayer->sendPacket(&gcSkillFailed1);
				return;
			}
			
			// Dark Revenge 상태에서 흡혈을 시도하면 풀어준다.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_EXTREME))
			{
				EffectManager * pEffectManager = pVampire->getEffectManager();
				Assert( pEffectManager != NULL );
				Effect * pEffect = pEffectManager->findEffect( Effect::EFFECT_CLASS_EXTREME );
				if ( pEffect != NULL ) {
					pEffect->setDeadline(0);
				}
			}
	
			// 안 보이는 상태에서 흡혈을 시도하면, 보이게 해준다.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
			{
				Zone* pZone = pVampire->getZone();
				Assert(pZone != NULL);
				addVisibleCreature(pZone, pVampire, true);
			}

			SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_BLOOD_DRAIN);
			Assert(pSkillHandler != NULL);
			pSkillHandler->execute(pVampire, pPacket->getObjectID());
		}
	} 
	catch (Throwable & t) 
	{ 
		//cout << t.toString(); 
	}

#endif

	__END_DEBUG
    __END_DEBUG_EX __END_CATCH
}
