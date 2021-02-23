#include "MiniGameQuestStatus.h"
#include "PlayerCreature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Player.h"
#include "StringStream.h"
#include "DB.h"

#include "PacketUtil.h"

#include "Gpackets/GCMiniGameScores.h"

GCQuestStatus* MiniGameQuestStatus::makeStatusPacket() const
{
	GCQuestStatus* pPacket = new GCQuestStatus();

	pPacket->setQuestID( (WORD)getQuestID() );
	pPacket->setCurrentNum( (WORD)m_GameType );

	if ( m_State == QUEST_REWARDED )
	{
		pPacket->setRemainTime( 0 );
	}
	else
	{
		pPacket->setRemainTime( (DWORD)VSDateTime::currentDateTime().secsTo( m_Deadline ) );
	}

	return pPacket;
}

void MiniGameQuestStatus::executeWhenStart()
{
	sendGCMiniGameScores( getOwnerPC(), m_GameType, 0 );
/*	GCMiniGameScores gcMGS;
	gcMGS.setGameType( (GameType)m_GameType );
	gcMGS.setLevel(0);

	int index=0;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT Name, Score FROM MiniGameScores WHERE Type=%u AND Level=0 ORDER BY Score DESC LIMIT 1", m_GameType);

		// UPDATE인 경우는 Result* 대신에.. pStmt->getAffectedRowCount()

		if (pResult->next())
		{
			gcMGS.setScore( index++, pResult->getString(1), pResult->getInt(2) );
		}

		pResult = pStmt->executeQuery(
				"SELECT Score FROM MiniGameScores WHERE Type=%u AND Level=0 AND Name='%s' ORDER BY Score DESC LIMIT 1",
					m_GameType, getOwnerPC()->getName().c_str() );

		if (pResult->next())
		{
			gcMGS.setScore( index++, getOwnerPC()->getName(), pResult->getInt(1) );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	getOwnerPC()->getPlayer()->sendPacket(&gcMGS);*/
}

void MiniGameQuestStatus::executeWhenFail()
{
	PlayerCreature* pPC = getOwnerPC();
	Assert( pPC != NULL );

	// 실패하면 죽는다.
	if ( pPC->isSlayer() )
	{
		dynamic_cast<Slayer*>(pPC)->setHP(0);
	}
	else if ( pPC->isVampire() )
	{
		dynamic_cast<Vampire*>(pPC)->setHP(0);
	}
	else if ( pPC->isOusters() )
	{
		dynamic_cast<Ousters*>(pPC)->setHP(0);
	}
	else Assert(false);
}

string MiniGameQuestStatus::toStrong() const throw(Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "MiniGameQuestStatus("
		<< "Game Type : " << m_GameType
		<< ", Score : " << ((m_bScoreSet)?-1:(int)m_GameScore)
		<< ") : " << QuestStatus::toString().c_str();

	return msg.toString();

	__END_CATCH
}

