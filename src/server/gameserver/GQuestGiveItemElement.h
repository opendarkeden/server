#ifndef __GQUEST_GIVE_ITEM_ELEMENT_H__
#define __GQUEST_GIVE_ITEM_ELEMENT_H__

#include "GQuestElement.h"
#include "Item.h"

class GQuestGiveItemElement : public GQuestElement
{
public:
	GQuestGiveItemElement() { }
	string 				getElementName() const { return "GiveItem"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestGiveItemElement*	makeElement(XMLTree* pTree);

private:
	Item::ItemClass	m_ItemClass;
	ItemType_t	m_ItemType;
	list<OptionType_t>	m_Option;
	ItemNum_t	m_Num;
};

extern GQuestGiveItemElement g_GiveItemElement;

#endif
