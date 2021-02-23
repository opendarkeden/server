#ifndef __GQUEST_INFO_H__
#define __GQUEST_INFO_H__

#include "Types.h"
#include "SXml.h"
#include "Exception.h"
#include <hash_map>
#include <vector>

class GQuestElement;
class PlayerCreature;
class GQuestStatus;

class GQuestInfo
{
public:
	enum ElementType
	{
		HAPPEN,
		COMPLETE,
		FAIL,
		REWARD,
		MAX
	};

	enum CheckType
	{
		SEQUENCE,
		OR,
		AND,
	};

	GQuestInfo(XMLTree* pInfo);
	DWORD	getQuestID() const { return m_QuestID; }
//	void	makeVector(XMLTree* pTree, vector<GQuestElement*>& eVector);
	void	makeVector(XMLTree* pTree, ElementType type);

	GQuestElement*	getElement(ElementType type, uint index);
	const vector<GQuestElement*>& getElements(ElementType type) const { return m_Elements[type]; }

	bool	isInstanceSuccess(ElementType type, PlayerCreature* pPC);

	GQuestStatus*	makeInitStatus(PlayerCreature* pOwner);
	CheckType		getCheckType(ElementType type) const { return m_CheckTypes[type]; }

private:
	DWORD		m_QuestID;

	vector<GQuestElement*>	m_Elements[MAX];
	CheckType				m_CheckTypes[MAX];
};

class GQuestInfoManager
{
public:
	GQuestInfoManager() : m_pXMLInfo(NULL) { }

	void load() throw(Error);
	static GQuestInfoManager&	Instance()
	{
		static GQuestInfoManager theInstance;
		return theInstance;
	}

	hash_map<DWORD, GQuestInfo*>&	getInfos() { return m_Infos; }
	const hash_map<DWORD, GQuestInfo*>&	getInfos() const { return m_Infos; }

private:
	XMLTree*	m_pXMLInfo;
	hash_map<DWORD, GQuestInfo*>	m_Infos;
};

#endif
