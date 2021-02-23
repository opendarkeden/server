
#include "QuestInfo.h"
#include "RewardClass.h"
#include "QuestManager.h"
#include "EventQuestAdvance.h"
#include "PlayerCreature.h"

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "StringStream.h"
#include "Assert.h"

QuestInfo::QuestInfo( QuestID_t qID, Race_t race, QuestGrade_t maxGrade, QuestGrade_t minGrade, DWORD timeLimitSec, RewardClass_t rClass, QuestClass questClass )
	: m_QuestClass( questClass )
{
	m_QuestID = qID;
	m_Race = race;
	m_MaxGrade = maxGrade;
	m_MinGrade = minGrade;
	m_TimeLimitSec = timeLimitSec;
	m_RewardClass = rClass;

	m_bEventQuest = false;
	m_QuestLevel = -1;
}

QuestInfo::~QuestInfo()
{
}

string QuestInfo::toString() const throw()
{
	StringStream msg;

	msg << "QuestInfo("
		<< "QuestID : " << m_QuestID
		<< " ,Race : " << ( (m_Race==0)?"Slayer":"Vampire" )
		<< " ,MinGrade : " << m_MinGrade
		<< " ,MaxGrade : " << m_MaxGrade
		<< " ,TimeLimit : " << m_TimeLimitSec
		<< " ,RewardClass : " << m_RewardClass
		<< " ,isEventQuest : " << ( (m_bEventQuest)?"yes":"no" )
		<< " ,QuestLevel : " << m_QuestLevel
		<< ")";

	return msg.toString();
}

bool QuestInfo::canExecute( PlayerCreature* pPC ) const
	throw(Error)
{
	__BEGIN_TRY

	if ( pPC->getRace() != m_Race ) return false;

	if ( isEventQuest() )
	{
		if ( !pPC->getQuestManager()->getEventQuestAdvanceManager()->canExecute( getQuestLevel() ) ) return false;
	}

	QuestGrade_t curGrade = 0;
	if ( m_Race == RACE_SLAYER )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert( pSlayer != NULL );
		
		curGrade = (QuestGrade_t)pSlayer->getQuestGrade();
	}
	else if ( m_Race == RACE_VAMPIRE )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert( pVampire != NULL );

		curGrade = (QuestGrade_t)pVampire->getLevel();
	}
	else if ( m_Race == RACE_OUSTERS )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert( pOusters != NULL );

		curGrade = (QuestGrade_t)pOusters->getLevel();
	}
	else
	{
	//	cout << "아우스터즈냐? -_-; QuestInfo::canExecute()" << endl;
		cout << "넌대체머냐-_-; QuestInfo::canExecute()" << endl;
		return false;
	}

	if ( m_MinGrade > curGrade ) return false;
	if ( m_MaxGrade < curGrade ) return false;

	return true;

	__END_CATCH
}
