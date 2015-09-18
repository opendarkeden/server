#include "GQuestElement.h"
#include "GQuestAllElements.h"
#include "PlayerCreature.h"

#include <map>

void GQuestElement::whenMissionStart(PlayerCreature* pOwner, GQuestMission* pMission )
{
	if (getEventType() == GQuestManager::MAX ) return;

	pOwner->getGQuestManager()->getEventMission(getEventType()).push_back(pMission);
}

void GQuestElement::whenMissionEnd(PlayerCreature* pOwner, GQuestMission* pMission )
{
	if (getEventType() == GQuestManager::MAX ) return;

	list<GQuestMission*>& missions = pOwner->getGQuestManager()->getEventMission(getEventType());
	list<GQuestMission*>::iterator itr = find(missions.begin(), missions.end(), pMission);

	if (itr != missions.end() ) missions.erase(itr);
}

void GQuestElementFactory::init()
{
	addProtoType(&g_LevelElement);
	addProtoType(&g_TimeElement);
	addProtoType(&g_LevelElement);
	addProtoType(&g_BloodDrainElement);
	addProtoType(&g_GiveVampireExpElement);
	addProtoType(&g_SayNPCElement);
	addProtoType(&g_TamePetElement);
	addProtoType(&g_ScriptElement);
	addProtoType(&g_MessageElement);
	addProtoType(&g_GiveItemElement);
	addProtoType(&g_GiveQuestItemElement);
	addProtoType(&g_LoseQuestItemElement);
	addProtoType(&g_RaceElement);
	addProtoType(&g_KilledElement);
	addProtoType(&g_GiveDomainExpElement);
	addProtoType(&g_GiveMoneyElement);
	addProtoType(&g_SkillLevelElement);
	addProtoType(&g_RideMotorcycleElement);
	addProtoType(&g_GiveOustersExpElement);
	addProtoType(&g_TouchWayPointElement);
	addProtoType(&g_HasQuestItemElement);
	addProtoType(&g_KillMonsterElement);
	addProtoType(&g_PartyDissectElement);
	addProtoType(&g_GiveEventQuestItemElement);
	addProtoType(&g_EventPartyElement);
	addProtoType(&g_EventPartyCrashElement);
	addProtoType(&g_CompleteQuestElement);
	addProtoType(&g_FastMoveElement);
	addProtoType(&g_IllegalWarpElement);
	addProtoType(&g_TravelElement);
	addProtoType(&g_ORElement);
	addProtoType(&g_NOTElement);
	addProtoType(&g_RandomElement);
	addProtoType(&g_AdvancementClassLevelElement);
	addProtoType(&g_ClearDynamicZoneElement);
	addProtoType(&g_AddEffectElement);
	addProtoType(&g_RemoveEffectElement);
	addProtoType(&g_SetEnterDynamicZoneElement);
	addProtoType(&g_EnterDynamicZoneElement);
	addProtoType(&g_StartOtherQuestElement);
	addProtoType(&g_GiveAdvancementClassExpElement);
	addProtoType(&g_AdvanceClassElement);
	addProtoType(&g_WarpElement);

	map<string, GQuestElement*>::iterator itr = m_ProtoTypes.begin();
	map<string, GQuestElement*>::iterator endItr = m_ProtoTypes.end();
}
