#include "GQuestRandomElement.h"
#include "PlayerCreature.h"

GQuestElement::ResultType GQuestRandomElement::checkCondition( PlayerCreature* pPC ) const
{
/*	vector<GQuestElement*>::const_iterator itr = m_Elements.begin();
	for ( ; itr != m_Elements.end() ; ++itr )
	{
		if ( (*itr)->checkCondition(pPC) == OK ) return OK;
	}*/

	int idx = rand()%m_Elements.size();

	return m_Elements[idx]->checkCondition(pPC);
}

GQuestRandomElement* GQuestRandomElement::makeElement(XMLTree* pTree)
{
	GQuestRandomElement* pRet = new GQuestRandomElement;

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

GQuestRandomElement g_RandomElement;
