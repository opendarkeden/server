//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterNameManager.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTERNAMEMANAGER_H__
#define __MONSTERNAMEMANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class MonsterNameManager
//////////////////////////////////////////////////////////////////////////////

class Monster;

class MonsterNameManager
{

///// Member methods /////

public:
	MonsterNameManager() throw();
	virtual ~MonsterNameManager() throw();

public:
	void init(void) throw();

	string getRandomName(Monster* pMonster) throw();

///// Member data ///// 

protected:
	string* m_pFirstName;
	string* m_pMiddleName;
	string* m_pLastName;

	short   m_nFirstNameCount;
	short   m_nMiddleNameCount;
	short   m_nLastNameCount;

	hash_map<ulonglong, string> m_UsedName;

};

// global varible definition
extern MonsterNameManager* g_pMonsterNameManager;

#endif
