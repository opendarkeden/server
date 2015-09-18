#include "GQuestStatus.h"
#include "GQuestInfo.h"
#include "GCGQuestStatusModify.h"
#include "PlayerCreature.h"
#include "Player.h"
#include "DB.h"
#include "EffectEventQuestReset.h"

GQuestStatus::~GQuestStatus()
{
	list<MissionInfo*>::iterator itr = m_Missions.begin();

	for (; itr != m_Missions.end() ; ++itr )
		SAFE_DELETE((*itr));
}

void GQuestStatus::initMissions()
{
	map<vector<GQuestElement*>::const_iterator, GQuestMission*>::iterator itr = m_MissionMap.begin();
	for (; itr != m_MissionMap.end() ; ++itr )
	{
		if (itr->second != NULL ) (*(itr->second->m_Position))->whenMissionEnd(m_pOwner, itr->second);
	
	}

	m_MissionMap.clear();
	list<MissionInfo*>::iterator litr = m_Missions.begin();
	for (; litr != m_Missions.end() ; ++litr )
	{
		SAFE_DELETE((*litr));
	}

	m_Missions.clear();
	for (int i=GQuestInfo::HAPPEN; i<GQuestInfo::MAX; ++i )
	{
		m_ElementAdvance[i] = m_pGQuestInfo->getElements((GQuestInfo::ElementType)i).begin();
	}
}

void GQuestStatus::update()
{
	GCGQuestStatusModify gcModify;
	gcModify.setType(checkMissions());
	gcModify.setInfo(this);
	m_pOwner->getPlayer()->sendPacket(&gcModify);
}

BYTE GQuestStatus::checkMissions()
{
	BYTE ret = GCGQuestStatusModify::NO_MODIFY;

	if (m_Status == DOING) {
		GQuestElement::ResultType resultComplete = checkElements(GQuestInfo::COMPLETE);
		switch (resultComplete) {
			case GQuestElement::OK: {
					m_Status = SUCCESS;
					ret = GCGQuestStatusModify::SUCCESS;
					cleanUpMissions();
					break;
				}
			case GQuestElement::FAIL: {
					m_Status = FAIL;
					save();
					ret = GCGQuestStatusModify::FAIL;
					cleanUpMissions();
					break;
				}
			case GQuestElement::WAIT:
			default:
				break;
		}

		GQuestElement::ResultType resultFail = checkElements(GQuestInfo::FAIL);
		switch (resultFail )
		{
			case GQuestElement::OK:
				{
					m_Status = FAIL;
					save();
					ret = GCGQuestStatusModify::FAIL;
					cleanUpMissions();
					break;
				}
			case GQuestElement::FAIL:
			case GQuestElement::WAIT:
			default:
				break;
		}
	}

	if (m_Status == SUCCESS )
	{
		GQuestElement::ResultType resultReward = checkElements(GQuestInfo::REWARD);
		switch (resultReward )
		{
			case GQuestElement::OK:
				{
					m_Status = COMPLETE;
					save();
					m_pOwner->getGQuestManager()->refreshQuest();
					if (m_QuestID == 1001 )
					{
						EffectEventQuestReset* pEffect = new EffectEventQuestReset(m_pOwner, 1);
						int lastSec = 0;
						pEffect->setDeadline((EVENT_QUEST_TIME_LIMIT-lastSec)*10);
						pEffect->setNextTime(((EVENT_QUEST_TIME_LIMIT-lastSec)%BROADCASTING_DELAY) * 10);
						m_pOwner->addEffect(pEffect);
					}
					break;
				}
			case GQuestElement::FAIL:
				{
					m_Status = FAIL;
					save();
					break;
				}
			case GQuestElement::WAIT:
			default:
				break;
		}
	}

	if (m_Status == FAIL )
	{
		m_Status = CAN_REPLAY;
		save();
	}

	return ret;
}

GQuestElement::ResultType GQuestStatus::checkElements(GQuestInfo::ElementType type)
{
	switch (m_pGQuestInfo->getCheckType(type) )
	{
		case GQuestInfo::SEQUENCE:
			return checkElementsSEQ(type);
		case GQuestInfo::AND:
			return checkElementsAND(type);
		case GQuestInfo::OR:
			return checkElementsOR(type);
		default:
			filelog("GQuestBug.log", "%u - GQuestStatus::checkElements(%u) : Invalid checkType : %d", m_pGQuestInfo->getQuestID(), type, m_pGQuestInfo->getCheckType(type));
			Assert(false);
	}

	return GQuestElement::FAIL;
}

// element들을 순서대로 check해야 된다. 앞에꺼가 완결되어야 뒤에꺼를 체크한다.
GQuestElement::ResultType GQuestStatus::checkElementsSEQ(GQuestInfo::ElementType type) {
	GQuestMission* pCurrentMission = m_MissionMap[m_ElementAdvance[type]];
	if (pCurrentMission != NULL) {
		GQuestElement::ResultType result = (*m_ElementAdvance[type])->checkMission(pCurrentMission);

		if (result == GQuestElement::FAIL ) pCurrentMission->m_Status = MissionInfo::FAIL;
		if (result != GQuestElement::OK ) return result;

		pCurrentMission->m_Status = MissionInfo::SUCCESS;
		(*m_ElementAdvance[type])->whenMissionEnd(m_pOwner, pCurrentMission);
		++m_ElementAdvance[type];
	}

	for (; m_ElementAdvance[type] != m_pGQuestInfo->getElements(type).end(); ++m_ElementAdvance[type]) {
		GQuestElement::ResultType result = (*(m_ElementAdvance[type]))->checkCondition(m_pOwner);

		if (result == GQuestElement::WAIT) {
			GQuestMission* pNewMission = (*(m_ElementAdvance[type]))->makeInitMission(m_pOwner);
			if (pNewMission == NULL ) return GQuestElement::FAIL;

			pNewMission->m_Condition = type;
			pNewMission->m_Index = (*(m_ElementAdvance[type]))->getIndex();

			pNewMission->m_Status = MissionInfo::CURRENT;
			pNewMission->m_Position = m_ElementAdvance[type];
			pNewMission->m_pParent = this;
			m_Missions.push_back(pNewMission);
			m_MissionMap[m_ElementAdvance[type]] = pNewMission;
			(*(m_ElementAdvance[type]))->whenMissionStart(m_pOwner, pNewMission);
			// recursive call
			return checkElements(type);
		}
		else if (result == GQuestElement::FAIL )
			return result;
	}

	return GQuestElement::OK;
}

// 하나라도 success면 ok. FAIL 조건 체크할때 쓴다. ㅜ.ㅠ
GQuestElement::ResultType GQuestStatus::checkElementsOR(GQuestInfo::ElementType type) {
	vector<GQuestElement*>::const_iterator itr = m_pGQuestInfo->getElements(type).begin();
	vector<GQuestElement*>::const_iterator endItr = m_pGQuestInfo->getElements(type).end();

	for (; itr != endItr ; )
	{
		GQuestMission* pMission = m_MissionMap[itr];
		if (pMission != NULL ) {
			if (pMission->m_Status == MissionInfo::SUCCESS)
				return GQuestElement::OK;

			if (pMission->m_Status == MissionInfo::FAIL){}
			else {
				GQuestElement::ResultType result = (*itr)->checkMission(pMission);

				if (result == GQuestElement::FAIL) {
					pMission->m_Status = MissionInfo::FAIL;
					(*itr)->whenMissionEnd(m_pOwner, pMission);
				}

				if (result == GQuestElement::OK) {
					pMission->m_Status = MissionInfo::SUCCESS;
					(*itr)->whenMissionEnd(m_pOwner, pMission);
					return GQuestElement::OK;
				}
			}
		} else {
			GQuestElement::ResultType result = (*itr)->checkCondition(m_pOwner);

			if (result == GQuestElement::WAIT) {
				GQuestMission* pNewMission = (*itr)->makeInitMission(m_pOwner);
				if (pNewMission == NULL) {
					++itr;
					continue;
				}

				pNewMission->m_Condition = type;
				pNewMission->m_Index = (*itr)->getIndex();

				pNewMission->m_Status = MissionInfo::CURRENT;
				pNewMission->m_Position = itr;
				pNewMission->m_pParent = this;
				m_Missions.push_back(pNewMission);
				m_MissionMap[itr] = pNewMission;
				(*itr)->whenMissionStart(m_pOwner, pNewMission);
				continue;
			}
			else if (result == GQuestElement::OK )
				return result;
		}
		++itr;
	}
	return GQuestElement::FAIL;
}

// 모든 element를 한꺼번에 평가한다. 기다려야 되는것도 한꺼번에 기다린다.
GQuestElement::ResultType GQuestStatus::checkElementsAND(GQuestInfo::ElementType type) {
	vector<GQuestElement*>::const_iterator itr = m_pGQuestInfo->getElements(type).begin();
	vector<GQuestElement*>::const_iterator endItr = m_pGQuestInfo->getElements(type).end();

	GQuestElement::ResultType ret = GQuestElement::OK;

	for (; itr != endItr ; ) {
		GQuestMission* pMission = m_MissionMap[itr];
		if (pMission != NULL) {
			if (pMission->m_Status == MissionInfo::FAIL)
				return GQuestElement::FAIL;
			else if (pMission->m_Status == MissionInfo::SUCCESS) {}
			else {
				GQuestElement::ResultType result = (*itr)->checkMission(pMission);

				if (result == GQuestElement::OK) {
					pMission->m_Status = MissionInfo::SUCCESS;
					(*itr)->whenMissionEnd(m_pOwner, pMission);
				}

				if (result == GQuestElement::FAIL) {

					pMission->m_Status = MissionInfo::FAIL;
					(*itr)->whenMissionEnd(m_pOwner, pMission);
					return GQuestElement::OK;
				}
				if (result == GQuestElement::WAIT ) ret = GQuestElement::WAIT;
			}
		} else {
			GQuestElement::ResultType result = (*itr)->checkCondition(m_pOwner);
			if (result == GQuestElement::WAIT ) {
				GQuestMission* pNewMission = (*itr)->makeInitMission(m_pOwner);
				if (pNewMission == NULL ) {
					++itr;
					continue;
				}

				pNewMission->m_Condition = type;
				pNewMission->m_Index = (*itr)->getIndex();

				pNewMission->m_Status = MissionInfo::CURRENT;
				pNewMission->m_Position = itr;
				pNewMission->m_pParent = this;
				m_Missions.push_back(pNewMission);
				m_MissionMap[itr] = pNewMission;
				(*itr)->whenMissionStart(m_pOwner, pNewMission);
				ret = GQuestElement::WAIT;
				continue;
			}
			else if (result == GQuestElement::FAIL )
				return result;
		}
		++itr;
	}
	return ret;
}

void GQuestStatus::cleanUpMissions() {
	BYTE whatCond;
	if (m_Status == FAIL ) whatCond = 1;
	else whatCond = 2;

	map<vector<GQuestElement*>::const_iterator, GQuestMission*>::iterator itr = m_MissionMap.begin();
	map<vector<GQuestElement*>::const_iterator, GQuestMission*>::iterator endItr = m_MissionMap.end();

	for (; itr != endItr ; ++itr) {
		if (itr->second == NULL) continue;
		if (itr->second->m_Condition == whatCond) {
			itr->second->m_Status = MissionInfo::FAIL;
			(*(itr->second->m_Position))->whenMissionEnd(m_pOwner, itr->second);
		}
	}
}

void GQuestStatus::save() throw(Error) {
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB {
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("REPLACE INTO GQuestSave (QuestID, OwnerID, Time, Status) VALUES (%u, '%s', now(), %u)", m_QuestID, m_pOwner->getName().c_str(), m_Status);

		SAFE_DELETE(pStmt);
	} END_DB(pStmt);

	__END_CATCH
}
