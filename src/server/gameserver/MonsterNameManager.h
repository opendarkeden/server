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
	string getRandomName(Monster* pMonster, bool isEventMonster) throw();

///// Member data ///// 

protected:
	string* m_pFirstName;
	string* m_pMiddleName;
	string* m_pLastName;

	string* m_pEventFirstName;
	string* m_pEventMiddleName;
	string* m_pEventLastName;

	short   m_nFirstNameCount;
	short   m_nMiddleNameCount;
	short   m_nLastNameCount;

	short   m_nEventFirstNameCount;
	short   m_nEventMiddleNameCount;
	short   m_nEventLastNameCount;


	hash_map<ulonglong, string> m_UsedName;

};

// global varible definition
extern MonsterNameManager* g_pMonsterNameManager;

#endif
