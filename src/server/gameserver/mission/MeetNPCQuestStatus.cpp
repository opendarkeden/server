
#include "MeetNPCQuestStatus.h"

#include "StringStream.h"

GCQuestStatus* MeetNPCQuestStatus::makeStatusPacket() const
{
	GCQuestStatus* pPacket = new GCQuestStatus();

	pPacket->setQuestID( (WORD)getQuestID() );
	pPacket->setCurrentNum( (WORD)getTargetID() );
	if ( m_State == QUEST_REWARDED )
	{
		pPacket->setRemainTime( 0 );
	}
	else
	{
		pPacket->setRemainTime( (DWORD)VSDateTime::currentDateTime().secsTo( m_Deadline ) );
	}

//	cout << "Make Packet : " << pPacket->toString() << endl;

	return pPacket;
}

bool MeetNPCQuestStatus::isTarget( NPCID_t npcID ) const
{
	if ( m_State != QUEST_STARTED ) return false;
	if ( !m_bMet[0] ) return m_TargetNPCID[0] == npcID;
	if ( !m_bMet[1] ) return m_TargetNPCID[1] == npcID;
	return false;
}

bool MeetNPCQuestStatus::met( NPCID_t npcID )
{ 
	if ( m_State != QUEST_STARTED ) return false;
	if ( !m_bMet[0] ) return (m_TargetNPCID[0]==npcID)?(m_bMet[0]=true):false;
	if ( !m_bMet[1] ) return (m_TargetNPCID[1]==npcID)?(m_bMet[1]=true):false;
	return false;
}

NPCID_t	MeetNPCQuestStatus::getTargetID() const
{
	if ( m_State != QUEST_STARTED ) return 0;
	if ( !m_bMet[0] ) return m_TargetNPCID[0];
	if ( !m_bMet[1] ) return m_TargetNPCID[1];
	return 0;
}

string MeetNPCQuestStatus::toString() const throw(Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "MeetNPCQuestStatus("
		<< ") : " << QuestStatus::toString().c_str();

	return msg.toString();

	__END_CATCH
}
