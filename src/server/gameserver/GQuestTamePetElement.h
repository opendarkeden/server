#ifndef __GQUEST_TAME_PET_ELEMENT_H__
#define __GQUEST_TAME_PET_ELEMENT_H__

#include "GQuestElement.h"
#include "GQuestStatus.h"

class GQuestTamePetMission : public GQuestMission
{
public:
	GQuestTamePetMission() : m_bTame(false) { }

	bool	isTamed() const { return m_bTame; }
	void	tame() { m_bTame = true; }

	string	getMissionName() const { return "TamePetMission"; }
private:
	bool	m_bTame;
};

class GQuestTamePetElement : public GQuestElement
{
public:
	GQuestTamePetElement() { }
	string 				getElementName() const { return "TamePet"; }
	GQuestManager::EventTypes	getEventType() const { return GQuestManager::TAMEPET; }

	ResultType			checkMission(GQuestMission* pStatus) const;

	GQuestMission*		makeInitMission(PlayerCreature* pPC) const;
	GQuestTamePetElement*	makeElement(XMLTree* pTree);

private:
};

extern GQuestTamePetElement g_TamePetElement;

#endif
