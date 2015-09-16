#ifndef __GQUEST_STATUS_H__
#define __GQUEST_STATUS_H__

#include "Types.h"
#include "QuestStatusInfo.h"
#include "GQuestInfo.h"
#include "GQuestElement.h"

#include <list>
#include <map>

class GQuestMission : public MissionInfo
{
public:
	virtual ~GQuestMission() { }
	vector<GQuestElement*>::const_iterator m_Position;
	GQuestStatus*	m_pParent;
	virtual string	getMissionName() const = 0;
};

class GQuestStatus : public QuestStatusInfo
{
public:
	GQuestStatus(PlayerCreature* pOwner, DWORD QuestID) : QuestStatusInfo(QuestID), m_pOwner(pOwner), m_pGQuestInfo(NULL) { }
	GQuestStatus(PlayerCreature* pOwner, GQuestInfo* pGQuestInfo) : QuestStatusInfo(pGQuestInfo->getQuestID()), m_pOwner(pOwner), m_pGQuestInfo(pGQuestInfo) { }
	~GQuestStatus();

	BYTE	getStatus() const { return m_Status; }
	void	setStatus(BYTE status) { m_Status = status; }

	void	initMissions();
	BYTE	checkMissions();
	void	update();

	GQuestElement::ResultType	checkElements(GQuestInfo::ElementType);
	GQuestElement::ResultType	checkElementsSEQ(GQuestInfo::ElementType);
	GQuestElement::ResultType	checkElementsOR(GQuestInfo::ElementType);
	GQuestElement::ResultType	checkElementsAND(GQuestInfo::ElementType);

	void	cleanUpMissions();
	void	save() throw(Error);

private:
	PlayerCreature*	m_pOwner;
	GQuestInfo*	m_pGQuestInfo;
	vector<GQuestElement*>::const_iterator	m_ElementAdvance[GQuestInfo::MAX];
	map<vector<GQuestElement*>::const_iterator, GQuestMission*>	m_MissionMap;
};

#endif
