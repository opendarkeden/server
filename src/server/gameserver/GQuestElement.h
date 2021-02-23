#ifndef __GQUEST_ELEMENT_H__
#define __GQUEST_ELEMENT_H__

#include "Types.h"
#include "Exception.h"
#include "SXml.h"
#include "GQuestManager.h"

#include <hash_map>

class PlayerCreature;
class GQuestStatus;
class GQuestMission;
class GQuestInfo;

class GQuestElement
{
public:
	enum ResultType
	{
		FAIL = 0,
		OK,
		WAIT
	};

	GQuestElement() : m_pParent(NULL), m_Condition(0), m_Index(0) { }
	virtual ~GQuestElement() { }

	virtual string		getElementName() const = 0;
	virtual ResultType	checkCondition(PlayerCreature* pPC) const { return WAIT; }
	virtual ResultType	checkMission(GQuestMission* pMission) const { return FAIL; }

	virtual	GQuestMission*	makeInitMission(PlayerCreature* pPC) const { return NULL; }

	virtual GQuestManager::EventTypes	getEventType() const { return GQuestManager::MAX; }
	virtual void						whenMissionStart( PlayerCreature* pOwner, GQuestMission* pMission );
	virtual void						whenMissionEnd( PlayerCreature* pOwner, GQuestMission* pMission );

	virtual GQuestElement*	makeElement(XMLTree* pTree) = 0;

	void	setParent( GQuestInfo* pParent ) { m_pParent = pParent; }
	void	setCondition( BYTE cond ) { m_Condition = cond; }

	DWORD	getIndex() const { return m_Index; }

protected:
	GQuestInfo*	m_pParent;
	BYTE	m_Condition;
	DWORD	m_Index;
};

class GQuestElementFactory
{
public:
	GQuestElement* makeElement(XMLTree* pTree)
	{
		cout << "make Element : " << pTree->GetName() << endl;
		GQuestElement* pProtoType = m_ProtoTypes[pTree->GetName()];
		if ( pProtoType == NULL ) return NULL;
		return pProtoType->makeElement( pTree );
	}

	void init();

	static GQuestElementFactory&	Instance()
	{
		static GQuestElementFactory theInstance;
		return theInstance;
	}

	void addProtoType(GQuestElement* pQE) {
		cout << "add Prototype : " << pQE->getElementName() << endl;
		m_ProtoTypes[pQE->getElementName()] = pQE;
	}

private:
	hash_map<string, GQuestElement*> m_ProtoTypes;
};

#endif
