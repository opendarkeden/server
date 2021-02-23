//--------------------------------------------------------------------------------
// SimpleQuest.cpp
//--------------------------------------------------------------------------------

#include "SimpleQuest.h"
#include "Creature.h"
#include "QuestPriceReward.h"
#include "QuestPricePenalty.h"
#include "Assert.h"
#include "DB.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
SimpleQuest::SimpleQuest()
	throw (Error)
: m_pOwner(NULL), m_AvailableSecond(0), m_pReward(NULL), m_pPenalty(NULL)
{
	//m_Deadline.tv_sec = m_Deadline.tv_usec = 0;
	setDeadline(99999999);
}

SimpleQuest::~SimpleQuest()
	throw (Error)
{
	__BEGIN_TRY

	if (m_pReward!=NULL)	SAFE_DELETE(m_pReward);
	if (m_pPenalty!=NULL)	SAFE_DELETE(m_pPenalty);

	__END_CATCH
}


//--------------------------------------------------------------------------------
// setDeadline
//--------------------------------------------------------------------------------
void SimpleQuest::setDeadline (Turn_t delay) 
	throw ()
{
    __BEGIN_TRY

	// 현재 시간을 측정한다.
	getCurrentTime(m_Deadline);

	// 데드라인을 결정한다.
	// 이때, delay 는 0.1 초가 1 이다.
	m_Deadline.tv_sec += delay / 10;
	m_Deadline.tv_usec += (delay % 10)* 100000;

	__END_CATCH
}

// 남은 duration(1/10초 단위)
Duration_t 
SimpleQuest::getRemainDuration() const
	throw()
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);
	return (m_Deadline.tv_sec  - currentTime.tv_sec)* 10 +
			(m_Deadline.tv_usec - currentTime.tv_usec) / 100000;

	__END_CATCH
}



//--------------------------------------------------------------------------------
// destroy
//--------------------------------------------------------------------------------
void
SimpleQuest::destroy() 
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pOwner!=NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		cout << "DELETE FROM SimpleQuest WHERE OwnerID = '" << m_pOwner->getName().c_str() << "'" << endl;

		pStmt->executeQuery(
			"DELETE FROM SimpleQuest WHERE OwnerID = '%s'", 
				m_pOwner->getName().c_str()); 

		/*
		if (pStmt->getAffectedRowCount()==0)
		{
			SAFE_DELETE(pStmt);
			return false;
		}

		*/
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// checkFail
//--------------------------------------------------------------------------------
bool		
SimpleQuest::checkFail() 
	throw (Error)
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);

	return currentTime >= m_Deadline;	

	__END_CATCH
}

//--------------------------------------------------------------------------------
// heartbeat
//--------------------------------------------------------------------------------
void		
SimpleQuest::heartbeat()
	throw (Error)
{
	__BEGIN_TRY

	if (m_State==STATE_ACTIVE)
	{
		processActive();
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// process Active
//--------------------------------------------------------------------------------
void		
SimpleQuest::processActive() 
	throw (Error)
{
	__BEGIN_TRY

	if (checkFail())
	{
		processFail();
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// process Fail
//--------------------------------------------------------------------------------
void
SimpleQuest::processFail()
	throw (Error)
{
	__BEGIN_TRY

	givePenalty();
	destroy();

	setState( STATE_END );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// take
//--------------------------------------------------------------------------------
void		
SimpleQuest::take(Creature* pCreature, bool bNewQuest) 
	throw (Error)
{
	__BEGIN_TRY

	setOwner( pCreature );
	
	// 처음 받은 퀘스트인 경우만.. 시간 설정과 DB생성을 한다	
	if (bNewQuest)
	{
		getCurrentTime(m_Deadline);
		m_Deadline.tv_sec += m_AvailableSecond;	

		create();
	}

	setState( STATE_ACTIVE );

	__END_CATCH
}

//--------------------------------------------------------------------------------
// give Reward
//--------------------------------------------------------------------------------
void		
SimpleQuest::giveReward() 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pReward!=NULL && m_pOwner!=NULL)
	{
		m_pReward->affect( m_pOwner );
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// give Penalty
//--------------------------------------------------------------------------------
void		
SimpleQuest::givePenalty() 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pPenalty!=NULL && m_pOwner!=NULL)
	{
		m_pPenalty->affect( m_pOwner );
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// add Reward
//--------------------------------------------------------------------------------
void				
SimpleQuest::addReward(QuestPrice* pQuestPrice) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pQuestPrice!=NULL);
	m_pReward = pQuestPrice;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// add Penalty
//--------------------------------------------------------------------------------
void				
SimpleQuest::addPenalty(QuestPrice* pQuestPrice) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pQuestPrice!=NULL);	
	m_pPenalty = pQuestPrice;

	__END_CATCH
}

//
void        
SimpleQuest::addReward(const string& text) 
	throw (Error)
{
	__BEGIN_TRY

	QuestPrice* pQuestPrice = new QuestPriceReward;

	pQuestPrice->setPrice( text );

	addReward( pQuestPrice );

	__END_CATCH
}

void        
SimpleQuest::addPenalty(const string& text) 
	throw (Error)
{
	__BEGIN_TRY

	QuestPrice* pQuestPrice = new QuestPricePenalty;

	pQuestPrice->setPrice( text );

	addPenalty( pQuestPrice );

	__END_CATCH
}

string
SimpleQuest::getRewardToString() const 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pReward==NULL)
		return "";

	return m_pReward->toString();

	__END_CATCH
}

string      
SimpleQuest::getPenaltyToString() const 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pReward==NULL)
		return "";

	return m_pPenalty->toString();

	__END_CATCH
}


