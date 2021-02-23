
#include "MonsterKillQuestStatus.h"

#include "StringStream.h"

GCQuestStatus* MonsterKillQuestStatus::makeStatusPacket() const
{
	GCQuestStatus* pPacket = new GCQuestStatus();

	pPacket->setQuestID( (WORD)getQuestID() );
	pPacket->setCurrentNum( (WORD)m_CurrentNum );
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

bool MonsterKillQuestStatus::killed( SpriteType_t targetSType, bool isChief )
{
	bool ret = false;

	if ( m_CurrentNum < m_GoalNum )
	{
		if ( (!m_IsChief || isChief ) && m_TargetMonsterSpriteType == targetSType )
		{
			m_CurrentNum++;
			ret = true;
		}
	}

	if ( m_CurrentNum >= m_GoalNum )
	{
		if ( m_State == QUEST_STARTED )
		{
			m_State = QUEST_SUCCESS;
			ret = true;
		}
	}

	return ret;
}

string MonsterKillQuestStatus::toString() const throw(Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "MonsterKillQuestStatus("
		<< "Target : " << (unsigned long)m_TargetMonsterSpriteType
		<< ", IsChief : " << ( (m_IsChief==0)?"no":"yes" )
		<< ", Goal : " << m_GoalNum
		<< ", Current : " << m_CurrentNum
		<< ") : " << QuestStatus::toString().c_str();

	return msg.toString();

	__END_CATCH
}
