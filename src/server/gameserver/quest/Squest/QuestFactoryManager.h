//--------------------------------------------------------------------------------
// QuestFactoryManager.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_FACTORY_MANAGER_H__
#define __QUEST_FACTORY_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Quest.h"
class QuestCreateInfo;

//--------------------------------------------------------------------------------
// QuestFactory
//--------------------------------------------------------------------------------
class QuestFactory {
public :
	virtual Quest::QuestType	getQuestType() const = 0;
	virtual Quest*				create(const QuestCreateInfo* qcInfo=NULL) const throw (Error) = 0;
};

//--------------------------------------------------------------------------------
// QuestFactoryManager
//--------------------------------------------------------------------------------
class QuestFactoryManager {
public :
	QuestFactoryManager() throw (Error);
	~QuestFactoryManager() throw (Error);

	static QuestFactoryManager*	getInstance()
	{
		static QuestFactoryManager		QPFM;
		return &QPFM;	
	}

	Quest*		create(Quest::QuestType qptype, const QuestCreateInfo* qcInfo=NULL) const throw(Error);

	
protected :
	void		addFactory(QuestFactory* pQuestFactory) throw (Error);
	
private :
	QuestFactory*		m_pQuestFactories[Quest::QUEST_MAX];
};

#endif
