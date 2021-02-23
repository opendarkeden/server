#ifndef __GQUEST_EXECUTE_ELEMENT_H__
#define __GQUEST_EXECUTE_ELEMENT_H__

#include "GQuestElement.h"

class GQuestExecuteElement : public GQuestElement
{
public:
	GQuestExecuteElement(const string& name) : m_ElementName(name) { }
	string 				getElementName() const { return m_ElementName; }
	ResultType	 		checkCondition( PlayerCreature* pPC ) const;
	GQuestExecuteElement*	makeElement(XMLTree* pTree);

private:
	string	m_ElementName;
};

extern GQuestExecuteElement g_ScriptElement;
extern GQuestExecuteElement g_MessageElement;

#endif
