#ifndef __GQUEST_WARP_ELEMENT_H__
#define __GQUEST_WARP_ELEMENT_H__

#include "GQuestElement.h"

class GQuestWarpElement : public GQuestElement
{
public:
	GQuestWarpElement() : m_ZoneID(0), m_X(0), m_Y(0) { }
	string 				getElementName() const { return "Warp"; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestWarpElement*	makeElement(XMLTree* pTree);

private:
	int	m_ZoneID, m_X, m_Y;
};

extern GQuestWarpElement g_WarpElement;

#endif
