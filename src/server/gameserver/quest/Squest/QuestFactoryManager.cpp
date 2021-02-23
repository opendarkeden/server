//--------------------------------------------------------------------------------
// QuestFactoryManager.cpp
//--------------------------------------------------------------------------------

#include "QuestFactoryManager.h"
#include "MonsterKillQuest.h"
#include "Assert.h"


//--------------------------------------------------------------------------------
// constructor / destructor
//--------------------------------------------------------------------------------
QuestFactoryManager::QuestFactoryManager() 
	throw (Error)
{
	for (int i=0; i<Quest::QUEST_MAX; i++)
		m_pQuestFactories[i] = NULL;

	addFactory(new MonsterKillQuestFactory());
}

QuestFactoryManager::~QuestFactoryManager() 
	throw (Error)
{
	for (int i=0; i<Quest::QUEST_MAX; i++)
		SAFE_DELETE(m_pQuestFactories[i]);
}

//--------------------------------------------------------------------------------
// add Factory
//--------------------------------------------------------------------------------
void			
QuestFactoryManager::addFactory(QuestFactory* pQuestFactory) 
	throw (Error)
{
	Assert(pQuestFactory!=NULL);
	Assert(pQuestFactory->getQuestType() < Quest::QUEST_MAX);
	Assert(m_pQuestFactories[pQuestFactory->getQuestType()]==NULL);	
	
	m_pQuestFactories[pQuestFactory->getQuestType()] = pQuestFactory;
}

//--------------------------------------------------------------------------------
// create
//--------------------------------------------------------------------------------
Quest*		
QuestFactoryManager::create(Quest::QuestType qptype, const QuestCreateInfo* qcInfo) const 
	throw(Error)
{
	Assert(qptype<Quest::QUEST_MAX);

	return m_pQuestFactories[qptype]->create(qcInfo);
}
