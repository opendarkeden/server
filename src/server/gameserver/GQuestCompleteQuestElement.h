#ifndef __GQUEST_COMPLETE_QUEST_ELEMENT_H__
#define __GQUEST_COMPLETE_QUEST_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestCompleteQuestElement : public GQuestElement
{
public:
	GQuestCompleteQuestElement() : m_QuestID(0) { }
	string		 				getElementName() const { return "CompleteQuest"; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;

	GQuestCompleteQuestElement*	makeElement(XMLTree* pTree);

	DWORD getQuestID() const { return m_QuestID; }

private:
	DWORD	m_QuestID;
};

extern GQuestCompleteQuestElement g_CompleteQuestElement;

#endif
