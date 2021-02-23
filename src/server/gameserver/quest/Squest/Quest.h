//--------------------------------------------------------------------------------
// Quest.h
//--------------------------------------------------------------------------------
//
// {START}
//			[WAIT]
//
// [WAIT]
//			take() --> create() --> [ACTIVE]
//
// [ACTIVE]
//			processActive()
//			{
//				checkFail() --> givePenalty() --> {END}
//				checkSuccess() --> [COMPLETE]
//			}
// 
// [COMPLETE]
//			checkComplete() --> giveReward() --> {END}
//
// {END}
//			destroy()
//
//
//--------------------------------------------------------------------------------
// QuestID는 단순한 각 Quest구분용이다.
// Thread Safe하지 않고, 서버간에도 동기화되지 않는다.
//--------------------------------------------------------------------------------

#ifndef __QUEST_H__
#define __QUEST_H__

#include "Types.h"
#include "Exception.h"
class Creature;
class QuestEvent;

//#define __ACTIVE_QUEST__


class Quest {
public :
	enum QuestType
	{		
		QUEST_MONSTER_KILL,

		QUEST_MAX
	};

	enum QuestState
	{
		STATE_NULL,
		
		STATE_WAIT,			// QuestBoard에서 누군가가 받아가기를 기다리는 상태
		STATE_ACTIVE,		// 누가 Quest를 받아서 진행중인 상태
		STATE_COMPLETE,		// Quest가 완료된 상태(Reward 받기 전)
		STATE_END			// Quest가 끝난 상태
	};

public :
	Quest() throw (Error) : m_QuestID(m_QuestIDRegistry++), m_State(STATE_NULL)  {}
	virtual ~Quest() throw (Error) { if (m_State!=STATE_NULL) destroy(); }
	
	static void			initQuestIDRegistry() throw(Error);
	QuestID_t			getQuestID()					{ return m_QuestID; }
    void				setQuestID(QuestID_t QuestID)	{ m_QuestID = QuestID; }

	virtual QuestType	getQuestType() const = 0;
	QuestState			getState() const	{ return m_State; }	

	virtual void		create() throw (Error) = 0;
	virtual void		save() throw (Error) = 0;
	virtual void		destroy() throw (Error) {}
	
	virtual bool		checkSuccess(const QuestEvent* pQuestEvent) throw (Error) = 0;
	virtual bool		checkFail() throw (Error) = 0;
	virtual bool		checkComplete() throw (Error) = 0;

	virtual void		take(Creature* pCreature, bool bNewQuest=true) throw (Error) = 0;
	virtual void		giveReward() throw (Error) = 0;
	virtual void		givePenalty() throw (Error) = 0;

	virtual void		heartbeat() throw (Error) = 0;

	virtual string		toString() const throw (Error) = 0;

protected :
	void setState(QuestState qs)	{ m_State = qs; }

protected :
	QuestID_t			m_QuestID;
	QuestState			m_State;

	static QuestID_t	m_QuestIDRegistry;
};

#endif

