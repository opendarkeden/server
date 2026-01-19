#ifndef __QUEST_INFO_MANAGER_H__
#define __QUEST_INFO_MANAGER_H__

#include <unordered_map>

#include "Exception.h"
#include "GCNPCResponse.h"
#include "QuestInfo.h"
#include "Types.h"

class QuestInfo;
class QuestStatus;
class PlayerCreature;
class NPC;

class QuestInfoManager {
protected:
    typedef unordered_map<QuestID_t, QuestInfo*> QuestInfoHashMap;

public:
    QuestInfoManager(NPC* pNPC) {
        m_QuestInfos.clear();
        m_pOwnerNPC = pNPC;
    }
    virtual ~QuestInfoManager();

public:
    void clear();
    virtual void load(const string& name = "") = 0;
    void addQuestInfo(QuestInfo* pQI);

    QuestMessage canExecuteQuest(QuestID_t qID, PlayerCreature* pPC) const;
    QuestMessage startQuest(QuestID_t qID, PlayerCreature* pPC);
    QuestStatus* makeQuestStatus(QuestID_t qID, PlayerCreature* pPC) const;

    bool isEventQuest(QuestID_t qID) const;

    // OutITR must be a container<QuestID_t>::output_iterator-compatible type.
    template <class OutITR> void getEventQuestIDs(int questLevel, PlayerCreature* pPC, OutITR outItr) const {
        __BEGIN_TRY

        QuestInfoHashMap::const_iterator itr = m_QuestInfos.begin();
        QuestInfoHashMap::const_iterator endItr = m_QuestInfos.end();

        for (; itr != endItr; ++itr)
            if (itr->second->isEventQuest() && itr->second->getQuestLevel() == questLevel &&
                canExecuteQuest(itr->first, pPC) == START_SUCCESS)
                (*outItr++) = itr->first;

        __END_CATCH
    }

    // OutITR must be a container<QuestID_t>::output_iterator-compatible type.
    template <class OutITR> void getPossibleQuestIDs(PlayerCreature* pPC, OutITR outItr) const {
        __BEGIN_TRY

        QuestInfoHashMap::const_iterator itr = m_QuestInfos.begin();
        QuestInfoHashMap::const_iterator endItr = m_QuestInfos.end();

        for (; itr != endItr; ++itr)
            if (canExecuteQuest(itr->first, pPC) == START_SUCCESS)
                (*outItr++) = itr->first;

        __END_CATCH
    }

    // *InITR yields QuestID_t values, *OutITR receives QuestInfo pointers.
    template <class InITR, class OutITR> void getMonsterKillQuests(InITR b, InITR e, OutITR t) {
        QuestInfoHashMap::const_iterator endItr = m_QuestInfos.end();
        for (InITR i = b; i != e; ++i) {
            QuestInfoHashMap::const_iterator itr = m_QuestInfos.find(*i);
            if (itr != endItr) {
                QuestInfo* pQI = itr->second;
                if (pQI->isMonsterKillQuest())
                    (*t++) = pQI;
            }
        }
    }

private:
    NPC* m_pOwnerNPC;
    QuestInfoHashMap m_QuestInfos;
};

#endif // __QUEST_INFO_MANAGER_H__
