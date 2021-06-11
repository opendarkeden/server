#include "GQuestRideMotorcycleElement.h"
#include "Assert.h"

GQuestElement::ResultType GQuestRideMotorcycleElement::checkMission(GQuestMission* pMission) const
{
	GQuestRideMotorcycleMission* pRideMotorcycleMission = dynamic_cast<GQuestRideMotorcycleMission*>(pMission);
	if ( pRideMotorcycleMission == NULL ) return FAIL;
	if ( pRideMotorcycleMission->isRide() ) return OK;

	return WAIT;
}

GQuestMission* GQuestRideMotorcycleElement::makeInitMission(PlayerCreature* pPC) const
{
	GQuestRideMotorcycleMission* pMission = new GQuestRideMotorcycleMission;
	
	return pMission;
}

GQuestRideMotorcycleElement* GQuestRideMotorcycleElement::makeElement(XMLTree* pTree)
{
	GQuestRideMotorcycleElement* pRet = new GQuestRideMotorcycleElement;

	DWORD index;
	if (pTree->GetAttribute("index", index)) pRet->m_Index = index;

	return pRet;
}

GQuestRideMotorcycleElement g_RideMotorcycleElement;
