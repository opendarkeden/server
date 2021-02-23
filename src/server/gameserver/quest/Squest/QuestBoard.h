#ifndef __QUEST_BOARD_H__
#define __QUEST_BOARD_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>

class Quest;
class GCNPCAskDynamic;
class NPC;
class Script;

class QuestBoard {
public :
	typedef hash_map<QuestID_t, Quest*>		QUESTS;

public :
	QuestBoard();
	virtual ~QuestBoard();

	void		init(int num) throw (Error);
	void		release() throw (Error);

	void		regenerate(int num) throw (Error);

	bool		add(Quest* pQuest) throw (Error);	
	Quest*		remove(QuestID_t qid) throw (Error);
	
	void		setScript(Script* pScript) const throw (Error);
	//void		makeNPCAskPacket(GCNPCAskDynamic& npcAskPacket) const throw (Error);

	const QUESTS& getQuests() const	throw (Error) { return m_Quests; }

private :
	NPC*	m_pNPC;
	QUESTS	m_Quests;
};


#endif
