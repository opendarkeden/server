#ifndef __GQUEST_GIVE_EVENT_QUEST_ITEM_ELEMENT_H__
#define __GQUEST_GIVE_EVENT_QUEST_ITEM_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveEventQuestItemElement : public GQuestElement
{
public:
	GQuestGiveEventQuestItemElement() : m_Type(0), m_Grade(0) { }
	string 				getElementName() const { return "GiveEventQuestItem"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveEventQuestItemElement*	makeElement(XMLTree* pTree);

private:
	uint	m_Type;
	uint 	m_Grade;
};

extern GQuestGiveEventQuestItemElement g_GiveEventQuestItemElement;

#endif
