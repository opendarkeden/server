#include "GQuestElement.h"
#include "GQuestAllElements.h"
#include "PlayerCreature.h"

void GQuestElement::whenMissionStart( PlayerCreature* pOwner, GQuestMission* pMission )
{
	if ( getEventType() == GQuestManager::MAX ) return;
	cout << "Mission " << pMission->getMissionName() << " inserts into Event " << (int)getEventType() << endl;
	pOwner->getGQuestManager()->getEventMission(getEventType()).push_back(pMission);
}

void GQuestElement::whenMissionEnd( PlayerCreature* pOwner, GQuestMission* pMission )
{
	if ( getEventType() == GQuestManager::MAX ) return;
	cout << "Mission " << pMission->getMissionName() << " removes from Event " << (int)getEventType() << endl;
	list<GQuestMission*>& missions = pOwner->getGQuestManager()->getEventMission(getEventType());
	list<GQuestMission*>::iterator itr = find(missions.begin(), missions.end(), pMission);

	if ( itr != missions.end() ) missions.erase(itr);
	else cout << "****** but cannot find! ******" << endl;
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

	hash_map<string, GQuestElement*>::iterator itr = m_ProtoTypes.begin();
	hash_map<string, GQuestElement*>::iterator endItr = m_ProtoTypes.end();

	for ( ; itr != endItr ; ++itr )
	{
		cout << "Prototype : " << itr->second->getElementName() << endl;
	}
}

