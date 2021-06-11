//--------------------------------------------------------------------------------
// QuestUtil.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_UTIL_H__
#define __QUEST_UTIL_H__

#include "Types.h"
#include "Exception.h"

//--------------------------------------------------------------------------------
// QuestCreateInfo
//--------------------------------------------------------------------------------
class QuestCreateInfo {
public :
	QuestCreateInfo(int level=0) : m_Level(level) {}
	~QuestCreateInfo() {}

	void	setLevel(int level) { m_Level = level; }
	int		getLevel() const	{ return m_Level; }
	
private :
	int			m_Level;
};

#endif
