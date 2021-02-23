#include "GQuestExecuteElement.h"
#include "PlayerCreature.h"
#include "GQuestInfo.h"
#include "Gpackets/GCExecuteElement.h"
#include "Player.h"

GQuestElement::ResultType GQuestExecuteElement::checkCondition( PlayerCreature* pPC ) const
{
	GCExecuteElement gcEE;

	gcEE.setQuestID( m_pParent->getQuestID() );
	gcEE.setCondition( m_Condition );
	gcEE.setIndex( m_Index );

	pPC->getPlayer()->sendPacket( &gcEE );

	return OK;
}

GQuestExecuteElement* GQuestExecuteElement::makeElement(XMLTree* pTree)
{
	GQuestExecuteElement* pRet = new GQuestExecuteElement(getElementName());

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestExecuteElement g_ScriptElement("Script");
GQuestExecuteElement g_MessageElement("Message");
