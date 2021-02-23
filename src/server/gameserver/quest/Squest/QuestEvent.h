//--------------------------------------------------------------------------------
// QuestEvent.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_EVENT_H__
#define __QUEST_EVENT_H__

#include "Types.h"
#include "Exception.h"
#include "Quest.h"

class QuestEvent {
public :
	enum QuestEventType
	{		
		QUEST_EVENT_MONSTER_KILL,

		QUEST_EVENT_MAX
	};

public :
	QuestEvent() throw (Error) {}
	virtual ~QuestEvent() throw (Error) {}

	virtual QuestEventType	getQuestEventType() const = 0;
};

#endif
