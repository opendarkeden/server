//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSkillToInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSkillToInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "ZoneUtil.h"

	#include "skill/Sniping.h"

	#include "Gpackets/GCSkillFailed1.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSkillToInventoryHandler::execute (CGSkillToInventory* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

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

		BYTE        X         = pPacket->getX();
		BYTE        Y         = pPacket->getY();
		BYTE        TX        = pPacket->getTargetX();
		BYTE        TY        = pPacket->getTargetY();

		disableFlags( pCreature, pZone, SkillType);

		if (pCreature->isSlayer()) 
		{
			Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature);
			SkillSlot* pSkillSlot = pSlayer->hasSkill(SkillType);
			bool       bSuccess   = true;

			if (pSkillSlot == NULL) bSuccess = false;
			if ( SkillType == SKILL_INSTALL_MINE ) {
				bSuccess = true;
				TY = 0;
			} else {
				if (!isAbleToUseInventorySkill(pSlayer, X, Y, TX, TY)) bSuccess = false;
			}
/*			if (pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
			{
				g_Sniping.checkRevealRatio(pSlayer, 20, 10);
			} */

			if (bSuccess)
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);
   			 	pSkillHandler->execute(pSlayer, pPacket->getObjectID(), X, Y, TX, TY, pSkillSlot);
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
			
			if (pVampireSkillSlot == NULL) bSuccess = false;
			if (!isAbleToUseInventorySkill(pVampire, X, Y, TX, TY)) bSuccess = false;

/*			if (pVampire->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
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
   			 	pSkillHandler->execute(pVampire, pPacket->getObjectID(), X, Y, TX, TY, pVampireSkillSlot);
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
			if (!isAbleToUseInventorySkill(pOusters, X, Y, TX, TY)) bSuccess = false;

			if (bSuccess) 
			{
				SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
				Assert(pSkillHandler != NULL);
   			 	pSkillHandler->execute(pOusters, pPacket->getObjectID(), X, Y, TX, TY, pOustersSkillSlot);
   			 }
             else
             {
                 GCSkillFailed1 _GCSkillFailed1;
				_GCSkillFailed1.setSkillType(SkillType);
                 pPlayer->sendPacket(&_GCSkillFailed1);
             }
		}
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

