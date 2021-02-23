#ifndef __GQUEST_HAS_QUEST_ITEM_ELEMENT_H__
#define __GQUEST_HAS_QUEST_ITEM_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestHasQuestItemElement : public GQuestElement
{
public:
	GQuestHasQuestItemElement() : m_Num(1) { }
	string		 				getElementName() const { return "HasQuestItem"; }

	ResultType	 		checkCondition( PlayerCreature* pPC ) const;

	GQuestHasQuestItemElement*	makeElement(XMLTree* pTree);

	ItemType_t	getType() const { return m_Type; }

private:
	ItemType_t	m_Type;
	ItemNum_t	m_Num;
};

extern GQuestHasQuestItemElement g_HasQuestItemElement;

#endif
