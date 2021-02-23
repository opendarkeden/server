#ifndef __GQUEST_START_OTHER_QUEST_ELEMENT_H__
#define __GQUEST_START_OTHER_QUEST_ELEMENT_H__

#include "GQuestElement.h"

class GQuestStartOtherQuestElement : public GQuestElement
{
public:
	GQuestStartOtherQuestElement() : m_QuestID(0) { }
	string 				getElementName() const { return "StartOtherQuest"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestStartOtherQuestElement*	makeElement(XMLTree* pTree);

private:
	DWORD	m_QuestID;
};

extern GQuestStartOtherQuestElement g_StartOtherQuestElement;

#endif
