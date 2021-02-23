#ifndef __GQUEST_LOSE_QUEST_ITEM_ELEMENT_H__
#define __GQUEST_LOSE_QUEST_ITEM_ELEMENT_H__

#include "GQuestElement.h"

class GQuestLoseQuestItemElement : public GQuestElement
{
public:
	GQuestLoseQuestItemElement() : m_ItemType(0) { }
	string 				getElementName() const { return "LoseQuestItem"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestLoseQuestItemElement*	makeElement(XMLTree* pTree);

private:
	ItemType_t	m_ItemType;
};

extern GQuestLoseQuestItemElement g_LoseQuestItemElement;

#endif
