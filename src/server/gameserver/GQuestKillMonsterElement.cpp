#include "GQuestKillMonsterElement.h"
#include "Assert1.h"

GQuestElement::ResultType GQuestKillMonsterElement::checkMission(GQuestMission* pMission) const
{
	GQuestKillMonsterMission* pKillMonsterMission = dynamic_cast<GQuestKillMonsterMission*>(pMission);
	if (pKillMonsterMission == NULL ) return FAIL;

	if (pKillMonsterMission->getCurrent() >= m_Goal ) return OK;

	return WAIT;
}

GQuestMission* GQuestKillMonsterElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestKillMonsterMission* pMission = new GQuestKillMonsterMission;

	int TotalNum = m_TargetList.size();
	int TargetNum = min((int)m_TargetNum, TotalNum);
	int selected = 0;

	for (int i=0; i<TotalNum; ++i )
	{
		int toSelect = TargetNum-selected;
		if (toSelect <= 0 ) break;

		int last = TotalNum - i;

		if ((rand()%last) < toSelect )
		{
			pMission->getTargetList().push_back(m_TargetList[i]);
			++selected;
		}
	}
	
	return pMission;
}

GQuestKillMonsterElement* GQuestKillMonsterElement::makeElement(XMLTree* pTree)
{
	GQuestKillMonsterElement* pRet = new GQuestKillMonsterElement;

	Assert(pTree->GetAttribute("num", pRet->m_Goal));
	Assert(pTree->GetAttribute("sort", pRet->m_TargetNum));

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	for (size_t i=0; i<pTree->GetChildCount(); ++i )
	{
		XMLTree* pChild = pTree->GetChild(i);
		Assert(pChild->GetName() == "Target");
		DWORD	targetSType;
		Assert(pChild->GetAttribute("type", targetSType));
		m_TargetList.push_back((SpriteType_t)targetSType);
	}

	return pRet;
}

GQuestKillMonsterElement g_KillMonsterElement;
