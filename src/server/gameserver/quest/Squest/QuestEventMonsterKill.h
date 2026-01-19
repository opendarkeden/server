//--------------------------------------------------------------------------------
// QuestEventMonsterKill.h
//--------------------------------------------------------------------------------

#ifndef __QUEST_EVENT_MONSTER_KILL_H__
#define __QUEST_EVENT_MONSTER_KILL_H__

#include "Exception.h"
#include "MonsterSelector.h"
#include "QuestEvent.h"
#include "QuestUtil.h"
#include "Types.h"

//--------------------------------------------------------------------------------
// QuestEventMonsterKill
//--------------------------------------------------------------------------------
class QuestEventMonsterKill : public QuestEvent, public MonsterSelector {
public:
    QuestEventMonsterKill(MonsterType_t monsterType, SpriteType_t spriteType) throw(Error)
        : MonsterSelector(monsterType, spriteType, 1) {}

    virtual QuestEvent::QuestEventType getQuestEventType() const {
        return QuestEvent::QUEST_EVENT_MONSTER_KILL;
    }
};

#endif
