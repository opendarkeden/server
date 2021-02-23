//////////////////////////////////////////////////////////////////////////////
// Filename    : CGCastingSkillHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGCastingSkill.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "Creature.h"

	#include "item/Motorcycle.h"

	#include "Gpackets/GCCastingSkill.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGCastingSkillHandler::execute (CGCastingSkill* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
		{
			// Creature를 받아온다.
			Creature* pCreature = pGamePlayer->getCreature();

			Assert (pCreature != NULL);

			GCCastingSkill _GCCastingSkill;
			_GCCastingSkill.setSkillType(pPacket->getSkillType());
		}
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString() << endl;
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

