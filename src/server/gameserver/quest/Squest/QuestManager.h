//--------------------------------------------------------------------------------
// QuestManager.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_MANAGER_H__
#define __QUEST_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <list>
class Quest;
class QuestEvent;

//--------------------------------------------------------------------------------
// QuestManager
//--------------------------------------------------------------------------------
class QuestManager {
public :
	typedef list<Quest*>	QUEST_LIST;

public :
	QuestManager() throw (Error);
	~QuestManager() throw (Error);

//	void		load(const string& name) throw (Error);
	void		release() throw (Error);

	int			isEmpty() const		{ return m_Quests.empty(); }
	
	bool		addQuest(Quest* pQuest) throw (Error);

	Quest*		checkEvent(QuestEvent* pQuestEvent) throw (Error);

	Quest*		removeCompleteQuest() throw (Error);

	void		heartbeat() throw (Error);


private :
	QUEST_LIST	m_Quests;
};

#endif
