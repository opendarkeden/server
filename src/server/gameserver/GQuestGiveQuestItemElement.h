#ifndef __GQUEST_GIVE_QUEST_ITEM_ELEMENT_H__
#define __GQUEST_GIVE_QUEST_ITEM_ELEMENT_H__

#include "GQuestElement.h"

class GQuestGiveQuestItemElement : public GQuestElement
{
public:
	GQuestGiveQuestItemElement() : m_ItemType(0), m_bSave(false) { }
	string 				getElementName() const { return "GiveQuestItem"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveQuestItemElement*	makeElement(XMLTree* pTree);

private:
	ItemType_t	m_ItemType;
	bool		m_bSave;
};

extern GQuestGiveQuestItemElement g_GiveQuestItemElement;

#endif
