//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterFunctionObject.h
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_FUNCTION_OBJECT_H__
#define __MONSTER_FUNCTION_OBJECT_H__

#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"

//////////////////////////////////////////////////////////////////////////////
//
// class StrongerSlayer, WeakerSlayer, StrongerVampire, WeakerVampire;
//
// 이 클래스들은, 몬스터에게 enemy 를 추가하는 Monster::addEnemy() 메쏘드
// 에서 존의 크리처 매니저에서 새 enemy 의 적절한 삽입 위치를 찾아낼 때
// 사용하는 function object 로서 사용된다.
//
// ex> 현재 몬스터의 AttackOrder가 ATTACK_WEAKEST 라고 가정하자. 이 
// 몬스터의 m_Enemies 는 약한 순서대로 정렬되어 있을 것이다. 일단 
// 현재의 스펙에는 뱀파이어 몬스터만 존재하기 때문에, 이 몬스터들은
// 뱀파이어와 슬레이어에게 공격을 같이 받게 되면, 특정 상황에서는
// 슬레이어를 먼저 공격하게 된다. 따라서, 이 m_Enemies 는 앞쪽에
// 슬레이어들의 OID가 저장되어 있으며, 뒷쪽에 뱀파이어들의 OID가
// 저장되어 있다. 
//
// 이제 SkillDomainLevelSum == 5000 인 슬레이어가 이 몬스터를 공격해서
// 적으로 지정될려고 하는 순간이 되었다고 치자. 이 슬레이어를 적절한
// 위치에 삽입하기 위해서는, 가장 약한 슬레이어의 위치를 알아내야 한다.
// (슬레이어가 없다면 최초의 뱀파이어의 위치를 알아내야 한다.)
//
// 이럴 경우, STL의 find_if 알고리즘을 사용하면 코드가 간단해 지는데,
// 여기의 파라미터로 WeakerSlayer(5000) 을 지정해주면 알아서 찾게 된다.
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// class StrongerSlayer;
// enemy list 는 현재 약한 순서로 정렬되어 있다.
// 따라서, operator()는 슬레이어가 아니거나 자신보다 강한 슬레이어일 경우
// true을 리턴해야 한다. 그래서, 그 앞쪽 노드에 추가하면 약한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class StrongerSlayer 
{
public:
	StrongerSlayer (Zone* pZone , SkillLevel_t skillLevelSum) 
	{
		m_pZone = pZone;
		m_SkillDomainLevelSum = skillLevelSum;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isSlayer())
			return true;

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		return pSlayer->getSkillDomainLevelSum() > m_SkillDomainLevelSum;
	}

private:
	Zone*        m_pZone;
	SkillLevel_t m_SkillDomainLevelSum;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerSlayer;
// enemy list 는 현재 강한 순서로 정렬되어 있다.
// 따라서, 슬레이어가 아니거나 자신보다 약한 슬레이어일 경우
// true을 리턴해야 한다. 그래서, 그 앞쪽 노드에 추가하면
// 강한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class WeakerSlayer 
{
public :

	// constructor
	WeakerSlayer (Zone* pZone , SkillLevel_t skillLevelSum) 
	{
		m_pZone = pZone;
		m_SkillDomainLevelSum = skillLevelSum;
	}

	bool operator () (ObjectID_t objectID)
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isSlayer())
			return true;

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		return pSlayer->getSkillDomainLevelSum() < m_SkillDomainLevelSum;
	}

private:
	Zone*        m_pZone;
	SkillLevel_t m_SkillDomainLevelSum;

};


//////////////////////////////////////////////////////////////////////////////
// class StrongerVampire;
// enemy list 는 현재 약한 순서로 정렬되어 있다.
// 따라서, 자신보다 강한 뱀파이어일 경우에만 true을 리턴해야 한다. 
// 그래서, 그 앞쪽 노드에 추가하면 약한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class StrongerVampire 
{
public:
	StrongerVampire (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isVampire())
			return false;

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		return pVampire->getLevel() > m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerVampire;
// enemy list 는 현재 강한 순서로 정렬되어 있다.
// 따라서, 자신보다 약한 뱀파이어일 경우에만 true을 리턴해야 한다. 
// 그래서, 그 앞쪽 노드에 추가하면 약한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class WeakerVampire 
{
public:
	WeakerVampire (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isVampire())
			return false;

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		return pVampire->getLevel() < m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;

};

class StrongerOusters 
{
public:
	StrongerOusters (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isOusters())
			return false;

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		return pOusters->getLevel() > m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerOusters;
// enemy list 는 현재 강한 순서로 정렬되어 있다.
// 따라서, 자신보다 약한 뱀파이어일 경우에만 true을 리턴해야 한다. 
// 그래서, 그 앞쪽 노드에 추가하면 약한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class WeakerOusters 
{
public:
	WeakerOusters (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isOusters())
			return false;

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		return pOusters->getLevel() < m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;

};

//////////////////////////////////////////////////////////////////////////////
// class StrongerMonster;
// enemy list 는 현재 약한 순서로 정렬되어 있다.
// 따라서, 자신보다 강한 뱀파이어일 경우에만 true을 리턴해야 한다. 
// 그래서, 그 앞쪽 노드에 추가하면 약한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class StrongerMonster 
{
public:
	StrongerMonster (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isMonster())
			return false;

		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		return pMonster->getLevel() > m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerMonster;
// enemy list 는 현재 강한 순서로 정렬되어 있다.
// 따라서, 자신보다 약한 뱀파이어일 경우에만 true을 리턴해야 한다. 
// 그래서, 그 앞쪽 노드에 추가하면 약한 순서를 유지하게 된다.
//////////////////////////////////////////////////////////////////////////////

class WeakerMonster 
{
public:
	WeakerMonster (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isMonster())
			return false;

		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		return pMonster->getLevel() < m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;

};



#endif
