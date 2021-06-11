#include "GQuestNOTElement.h"
#include "PlayerCreature.h"

GQuestElement::ResultType GQuestNOTElement::checkCondition( PlayerCreature* pPC ) const
{
	vector<GQuestElement*>::const_iterator itr = m_Elements.begin();
	if ( (*itr)->checkCondition(pPC) != OK ) return OK;

	return FAIL;
}

GQuestNOTElement* GQuestNOTElement::makeElement(XMLTree* pTree)
{
	GQuestNOTElement* pRet = new GQuestNOTElement;

	for ( size_t i=0; i<pTree->GetChildCount() ; ++i )
	{
		XMLTree* pChild = pTree->GetChild(i);
		GQuestElement* pElement = GQuestElementFactory::Instance().makeElement(pChild);
		if ( pElement != NULL )
		{
			pRet->m_Elements.push_back( pElement );
		}
		else
		{
			cout << "엘리먼트를 못 만들겠음 : " << pChild->GetName() << endl;
			Assert( false );
		}
	}

	return pRet;
}

GQuestNOTElement g_NOTElement;
