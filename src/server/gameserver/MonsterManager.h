//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterManager.h 
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "CreatureManager.h"
#include "MonsterCounter.h"
#include "Item.h"
#include "Timeval.h"
#include <map>
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class MonsterManager
//////////////////////////////////////////////////////////////////////////////

class Zone;
class Monster;
class MonsterCorpse;
struct SUMMON_INFO;
struct ITEM_TEMPLATE;

struct EventMonsterInfo
{
	MonsterType_t   monsterType;
	int				regenDelay;
	Timeval			regenTime;
	int				x, y;
	bool			bExist;
};

class MonsterManager : public CreatureManager 
{
public:
	MonsterManager(Zone* pZone) throw(Error);
	~MonsterManager() throw();
	
public:
	// load from database
	void load() throw(Error);

	// add monster
	void addCreature(Creature* pCreature) throw(DuplicatedException, Error);

	// 몬스터들을 추가한다.
	void addMonsters(ZoneCoord_t x, ZoneCoord_t y, MonsterType_t monsterType, int num, const SUMMON_INFO& summonInfo, list<Monster*>* pSummonedMonsters=NULL);

	// delete monster
	void deleteCreature(ObjectID_t objectID) throw();//NoSuchElementException, Error);

	// 매니저에 소속된 크리처들(NPC,Monster)을 처리한다.
	void processCreatures() throw(Error);

	// 몬스터의 숫자가 줄어들었을 경우에, 몬스터를 추가한다.
	void regenerateCreatures() throw(Error);

	// 몬스터를 추가할 적절한 위치를 검색한다.
	bool findPosition(MonsterType_t monsterType, ZoneCoord_t& x, ZoneCoord_t& y) const throw();

	// 죽은 크리처를 처리한다.
	void killCreature(Creature* pDeadMonster) throw(Error);

	// 죽은 몬스터에게서 아이템을 생성한다.
	void addItem(Monster* pDeadMonster, MonsterCorpse* pMonsterCorpse) throw(Error);
	
	// 해쉬맵을 직접 액세스할 때
	const map<MonsterType_t, MonsterCounter*>& getMonsters(void) { return m_Monsters;}

	// 전체의 잠재적인 적으로 인식한다. pMonster를 pCreature가 공격한 경우에..
	void addPotentialEnemy(Monster* pMonster, Creature* pCreature) throw(Error);

	// 전체의 적으로 인식한다. pMonster를 pCreature가 공격한 경우에..
	void addEnemy(Monster* pMonster, Creature* pCreature) throw(Error);

	// get debug string 
	string toString() const throw();

	// delete AllMonsters
	void deleteAllMonsters(bool bDeleteFromZone=true) throw(Error);//NoSuchElementException, Error);

	// kill AllMonsters
	void killAllMonsters(const map<ObjectID_t, ObjectID_t>& exceptCreatures) throw(Error);//NoSuchElementException, Error);

	int upgradeItemTypeByLuck(int luckLevel, Creature::CreatureClass ownerCreatureClass, ITEM_TEMPLATE& it) throw(Error);
	int upgradeOptionByLuck(int luckLevel, Creature::CreatureClass ownerCreatureClass, ITEM_TEMPLATE& it) throw(Error);

protected :
	void parseMonsterList(const string& text, bool bReload=false) throw(Error);
	void parseEventMonsterList(const string& text, bool bReload=false) throw(Error);

private:
	Zone* m_pZone; // 몬스터 매니저가 소속된 존에 대한 포인터
	map< SpriteType_t, MonsterCounter* > m_Monsters; // 현재 존에 존재하는 몬스터의 숫자 현황
	Timeval m_RegenTime; // 다음 몬스터 재생 시간

	int m_RICE_CAKE_PROB_RATIO[5];
	int m_SumOfCakeRatio;

	// by sigi. 2002.10.14
	vector<EventMonsterInfo>* 	m_pEventMonsterInfo; 
	int							m_nEventMonster;

	ZoneID_t					m_CastleZoneID;
};

#endif
