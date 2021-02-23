//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAbsorbSoulHandler.cpp
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGAbsorbSoul.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Ousters.h"
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
void CGAbsorbSoulHandler::execute (CGAbsorbSoul* pPacket , Player* pPlayer)
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

			// 아우스터즈가 아닌 놈이 흡영을 할 수는 없다.
			if (!pCreature->isOusters()) return;

			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
			ZoneLevel_t ZoneLevel = pCreature->getZone()->getZoneLevel(pCreature->getX(), pCreature->getY());
			if ((ZoneLevel & COMPLETE_SAFE_ZONE)
				|| (!isAbleToUseObjectSkill(pOusters, SKILL_ABSORB_SOUL)))
			{
				GCSkillFailed1 gcSkillFailed1;
				gcSkillFailed1.setSkillType(SKILL_ABSORB_SOUL);
				pPlayer->sendPacket(&gcSkillFailed1);
				return;
			}
			
			SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_ABSORB_SOUL);
			Assert(pSkillHandler != NULL);
			pSkillHandler->execute(pOusters, pPacket->getObjectID(), pPacket->getTargetZoneX(), pPacket->getTargetZoneY(), pPacket->getInvenObjectID(), pPacket->getInvenX(), pPacket->getInvenY(), pPacket->getTargetInvenX(), pPacket->getTargetInvenY() );
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
