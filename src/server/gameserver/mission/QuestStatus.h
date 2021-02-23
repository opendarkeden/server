#ifndef __QUEST_STATUS_H__
#define __QUEST_STATUS_H__

#include "Types.h"
#include "Exception.h"
#include "VSDateTime.h"
#include "Assert.h"

#include "QuestInfo.h"

class PlayerCreature;
class QuestManager;
class Packet;

class QuestStatus
{
protected:
	enum STATE
	{
		QUEST_STARTED,	// 0
		QUEST_SUCCESS,	// 1
		QUEST_REWARDED	// 2
	};
public:
	QuestStatus( QuestID_t qID, const VSDateTime& deadline, QuestClass questClass ) : m_QuestClass( questClass ), m_Deadline(deadline), m_State( QUEST_STARTED ) { m_QuestID = qID; m_bTimeLimit = false; }
	virtual ~QuestStatus() { }

	QuestClass		getQuestClass() const { return m_QuestClass; }
	
	QuestID_t		getQuestID() const { return m_QuestID; }
	bool			timeExpired() const { return m_bTimeLimit && m_Deadline < VSDateTime::currentDateTime(); }

	virtual bool	isSuccess() const throw(Error) { return m_State == QUEST_SUCCESS && !timeExpired(); }
	virtual bool	isRewarded() const throw(Error) { return m_State == QUEST_REWARDED; }

	void	setSuccess() const { Assert( m_State == QUEST_STARTED ); m_State = QUEST_SUCCESS; }
	void	setRewarded() const { Assert( m_State == QUEST_SUCCESS ); m_State = QUEST_REWARDED; }
	void	setRewardClass( RewardClass_t rClass) { m_RewardClass = rClass; }

	bool	isMonsterKillQuest() { return m_QuestClass == QUEST_CLASS_MONSTER_KILL; }

	bool	isEventQuest() const { return m_bEventQuest; }
	int		getQuestLevel() const { return m_QuestLevel; }

	void	setEventQuest( bool bEQ ) { m_bEventQuest = bEQ; }
	void	setQuestLevel( int qLvl ) { m_QuestLevel = qLvl; }

	bool	isTimeLimit() const { return m_bTimeLimit; }
	void	setTimeLimit( bool bTL ) { m_bTimeLimit = bTL; }

	virtual Packet*	makeStatusPacket() const = 0;

	virtual string	toString() const throw(Error);
	virtual void	executeWhenStart() { }
	virtual void	executeWhenCancel() { }
	virtual void	executeWhenFail() { }

protected:
	QuestClass		m_QuestClass;

	QuestID_t		m_QuestID;
	VSDateTime		m_Deadline;
	RewardClass_t	m_RewardClass;

	mutable STATE	m_State;

	bool			m_bEventQuest;
	int				m_QuestLevel;

	bool			m_bTimeLimit;

protected:
	PlayerCreature*	getOwnerPC() const;
	void			setOwnerQM( QuestManager* pQM ) { m_pOwnerQM = pQM; }
	RewardClass_t	getRewardClass() const { return m_RewardClass; }

	friend class	QuestManager;

private:
	QuestManager*	m_pOwnerQM;
};

#endif // __QUEST_STATUS_H__

