#include "GQuestSayNPCElement.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "VolumeInfo.h"
#include "Assert1.h"

GQuestElement::ResultType GQuestSayNPCElement::checkMission(GQuestMission* pMission) const
{
	GQuestSayNPCMission* pSayNPCMission = dynamic_cast<GQuestSayNPCMission*>(pMission);
	if (pSayNPCMission == NULL ) return FAIL;
	if (pSayNPCMission->isMet() ) return OK;

	return WAIT;
}

bool GQuestSayNPCElement::checkVolume(PlayerCreature* pPC ) const
{
	if (m_Volume == 0 )
		return true;

	Assert(pPC != NULL);
	Inventory* pInventory = pPC->getInventory();
	Assert(pInventory != NULL);
	VolumeInfo* pVolumeInfo = g_pVolumeInfoManager->getVolumeInfo(m_Volume);
	Assert(pVolumeInfo != NULL);

	_TPOINT pt;
	if (pInventory->getEmptySlot(pVolumeInfo->getVolumeWidth(), pVolumeInfo->getVolumeHeight(), pt ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

GQuestMission* GQuestSayNPCElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestSayNPCMission* pMission = new GQuestSayNPCMission;
	
	return pMission;
}

GQuestSayNPCElement* GQuestSayNPCElement::makeElement(XMLTree* pTree)
{
	GQuestSayNPCElement* pRet = new GQuestSayNPCElement;

	int target;
	Assert(pTree->GetAttribute("target", target));
	pRet->m_Target = target;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	int volume;
	if (pTree->GetAttribute("volume", volume)) pRet->m_Volume = volume;

	return pRet;
}

GQuestSayNPCElement g_SayNPCElement;
