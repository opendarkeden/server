//--------------------------------------------------------------------------------
// QuestLoaderManager.h
//--------------------------------------------------------------------------------

#ifndef __SIMPLE_QUEST_LOADER_H__
#define __SIMPLE_QUEST_LOADER_H__

#include "Types.h"
#include "Exception.h"
#include "Quest.h"
class QuestCreateInfo;

//--------------------------------------------------------------------------------
// QuestLoader
//--------------------------------------------------------------------------------
class SimpleQuestLoader {
public :
	static SimpleQuestLoader*	getInstance()
	{
		static SimpleQuestLoader QL;
		return &QL;	
	}

	virtual void	load(Creature* pCreature) throw (Error);
};

#endif
