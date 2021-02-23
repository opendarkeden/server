#include "GQuestPartyDissectElement.h"
#include "Assert.h"
#include "PlayerCreature.h"
#include "MonsterInfo.h"

GQuestElement::ResultType GQuestPartyDissectElement::checkMission(GQuestMission* pMission) const
{
	GQuestPartyDissectMission* pPartyDissectMission = dynamic_cast<GQuestPartyDissectMission*>(pMission);
	if ( pPartyDissectMission == NULL ) return FAIL;

	if ( pPartyDissectMission->getCurrent() >= m_Goal ) return OK;

	return WAIT;
}

GQuestMission* GQuestPartyDissectElement::makeInitMission(PlayerCreature* pPC) const
{
	vector<SpriteType_t>*	pTargetList = getTargetList( (int)pPC->getLevel() );
	if ( pTargetList == NULL ) return NULL;

	GQuestPartyDissectMission* pMission = new GQuestPartyDissectMission;

	int TotalNum = pTargetList->size();
	int TargetNum = min((int)m_TargetNum, TotalNum);
	int selected = 0;
	cout << TotalNum << "중에 " << TargetNum << "개가 선택되어야 합니다." << endl;

	for ( int i=0; i<TotalNum; ++i )
	{
		int toSelect = TargetNum-selected;
		if ( toSelect <= 0 ) break;

		int last = TotalNum - i;

		if ( (rand()%last) < toSelect )
		{
			if ( pMission->m_StrArg != "" ) pMission->m_StrArg += ", ";
			pMission->getTargetList().push_back( (*pTargetList)[i] );
			++selected;
			cout << (int)(*pTargetList)[i] << "가 선택되었습니다." << endl;

			pMission->m_StrArg += g_pMonsterInfoManager->getNameBySpriteType( (*pTargetList)[i] );
		}
	}

	cout << "선택끝~" << endl;
	
	return pMission;
}

GQuestPartyDissectElement* GQuestPartyDissectElement::makeElement(XMLTree* pTree)
{
	GQuestPartyDissectElement* pRet = new GQuestPartyDissectElement;

	Assert( pTree->GetAttribute("num", pRet->m_Goal) );
	Assert( pTree->GetAttribute("sort", pRet->m_TargetNum) );

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	for ( size_t i=0; i<pTree->GetChildCount(); ++i )
	{
		XMLTree* pChild = pTree->GetChild(i);
		Assert( pChild->GetName() == "Level" );
		MonsterTemplate* pTemplate = new MonsterTemplate;
		Assert( pChild->GetAttribute("min", pTemplate->min) );
		Assert( pChild->GetAttribute("max", pTemplate->max) );

		for ( size_t j=0; j<pChild->GetChildCount(); ++j )
		{
			XMLTree* pTarget = pChild->GetChild(j);
			Assert( pTarget->GetName() == "Target" );
			DWORD	targetSType;
			Assert( pTarget->GetAttribute("type", targetSType) );
			pTemplate->m_TargetList.push_back( (SpriteType_t)targetSType );
		}

		pRet->m_MonsterSelecter.push_back( pTemplate );
	}

	return pRet;
}

vector<SpriteType_t>*	GQuestPartyDissectElement::getTargetList(int level) const
{
	list<MonsterTemplate*>::const_iterator itr = m_MonsterSelecter.begin();
	list<MonsterTemplate*>::const_iterator endItr = m_MonsterSelecter.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( level >= (*itr)->min && level <= (*itr)->max ) return &((*itr)->m_TargetList);
	}
	
	return NULL;
}

GQuestPartyDissectElement g_PartyDissectElement;
