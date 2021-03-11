//////////////////////////////////////////////////////////////////////////////
// Filename    : CGCrashReportHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGCrashReport.h"

#ifdef __GAME_SERVER__
	#include "DB.h"
	#include "GamePlayer.h"
	#include "Slayer.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGCrashReportHandler::execute (CGCrashReport* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pCreature = pGamePlayer->getCreature();

	Statement* pStmt = NULL;

	try
	{
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("INSERT INTO CrashReportLog (PlayerID, Name, ReportTime, ExecutableTime, Version, Address, Message, OS, CallStack) VALUES "
								"('%s', '%s', now(), '%s', %u, '%s', '%s', '%s', '%s')", pGamePlayer->getID().c_str(), pCreature->getName().c_str(),
								pPacket->getExecutableTime().c_str(), pPacket->getVersion(), pPacket->getAddress().c_str(), pPacket->getMessage().c_str(),
								pPacket->getOS().c_str(), pPacket->getCallStack().c_str());

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
			// 누가 이상한거 날리면 무시하자
	} catch(...) { filelog("CrashReport.log", "%s", pPacket->toString().c_str()); }

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
