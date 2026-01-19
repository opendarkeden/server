//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterNameManager.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTERNAMEMANAGER_H__
#define __MONSTERNAMEMANAGER_H__

#include <unordered_map>

#include "Exception.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterNameManager
//////////////////////////////////////////////////////////////////////////////

class Monster;

class MonsterNameManager {
    ///// Member methods /////

public:
    MonsterNameManager();
    virtual ~MonsterNameManager();

public:
    void init(void);

    string getRandomName(Monster* pMonster);

    ///// Member data /////

protected:
    string* m_pFirstName;
    string* m_pMiddleName;
    string* m_pLastName;

    short m_nFirstNameCount;
    short m_nMiddleNameCount;
    short m_nLastNameCount;

    unordered_map<ulonglong, string> m_UsedName;
};

// global varible definition
extern MonsterNameManager* g_pMonsterNameManager;

#endif
