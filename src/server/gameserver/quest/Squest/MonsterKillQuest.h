//--------------------------------------------------------------------------------
// MonsterKillQuest.h
//--------------------------------------------------------------------------------

#ifndef __MONSTER_KILL_QUEST_H__
#define __MONSTER_KILL_QUEST_H__

#include "MonsterKillQuest.h"
#include "SimpleQuest.h"
#include "QuestFactoryManager.h"
#include "QuestUtil.h"
#include "MonsterSelector.h"
#include <list>
#include <vector>

//--------------------------------------------------------------------------------
// MonsterKillQuest
//--------------------------------------------------------------------------------
class MonsterKillQuest : public SimpleQuest, public MonsterSelector {
public :
	MonsterKillQuest(const MonsterSelector& mtc) throw (Error)
	: MonsterSelector(mtc)
	{
	}
	MonsterKillQuest(MonsterType_t monsterType, SpriteType_t spriteType, int number) throw (Error)
	: MonsterSelector(monsterType, spriteType, number)
	{
	}

	virtual ~MonsterKillQuest() throw (Error) {}

	virtual QuestType	getQuestType() const 	{ return QUEST_MONSTER_KILL; }

	virtual void		create() throw (Error);
	virtual void        save() throw (Error);

	virtual bool		checkSuccess(const QuestEvent* pQuestEvent) throw (Error);
	virtual bool		checkComplete() throw (Error);

public :
	virtual void        setObjective(const string& text) throw (Error)	{ MonsterSelector::setMonster(text); }
	virtual string      getObjectiveToString() const throw (Error)		{ return MonsterSelector::toString(); }

	string				toString() const throw (Error);

};

//--------------------------------------------------------------------------------
// MonsterKillQuestFactory
//--------------------------------------------------------------------------------
class MonsterKillQuestFactory : public QuestFactory {
public :
	virtual Quest::QuestType	getQuestType() const { return Quest::QUEST_MONSTER_KILL; }
	virtual Quest*				create(const QuestCreateInfo* qcInfo=NULL) const throw (Error);	

	static void		initMonsterTypeInfos();
	
private :
	typedef vector<MonsterSelector>	MonsterTypeInfos;	// 레벨에 따른 몬스터 종류

	static MonsterTypeInfos	m_MonsterTypeInfos;
};

#endif

