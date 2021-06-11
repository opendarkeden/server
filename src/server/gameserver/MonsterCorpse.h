//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_CORPSE_H__
#define __MONSTER_CORPSE_H__

#include "Item.h"
#include "ItemFactory.h"
#include "Inventory.h"
#include "Corpse.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterCorpse;
// 몬스터가 죽었을 경우, 남기는 시체이다.
//////////////////////////////////////////////////////////////////////////////

class Monster;

class MonsterCorpse : public Corpse 
{
public:
	MonsterCorpse(Monster* pMonster) ;
	MonsterCorpse (MonsterType_t MType, const string& name, Dir_t dir) ;
	virtual ~MonsterCorpse() ;

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0) ;
	virtual bool destroy() ;
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y) ;
	void tinysave(const string & field) const  { tinysave(field.c_str()); }
    void tinysave(const char* field) const  {}

	virtual ItemClass getItemClass() const  { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType() const  { return MONSTER_CORPSE; }
	virtual void setItemType(ItemType_t monsterType)  { throw UnsupportedError(__PRETTY_FUNCTION__); }

	bool isNextTreasureHead() { return (!m_Treasures.empty() && m_Treasures.front()->getItemClass() == ITEM_CLASS_SKULL); }

	virtual string toString() const ;

// own methods
public:
	MonsterType_t getMonsterType() const  { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType)  { m_MonsterType = monsterType; }

	string getName() const  { return m_Name; }
	void setName(string name)  { m_Name = name; }

	string getMonsterName() const  { return m_Name; }
	void setMonsterName(string name)  { m_Name = name; }

	Dir_t getDir() const  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }

	bool gethasHead() const  { return m_bhasHead; }
	void addHead()  { m_bhasHead = true; }
	void removeHead()  { m_bhasHead = false; }

	const string& getHostName(void) const { return m_HostName; }
	void setHostName(const string& name) { m_HostName = name; }
	
	int getHostPartyID(void) const { return m_HostPartyID; }
	void setHostPartyID(int ID) { m_HostPartyID = ID; }

	const string& getQuestHostName() const { return m_QuestHostName; }
	void setQuestHostName( const string& name ) { m_QuestHostName = name; }

	bool isShrine() const { return m_bShrine; }
	void setShrine( bool bShrine = true ) { m_bShrine = bShrine; }

	void setLastKiller(ObjectID_t id) { m_LastKiller = id; }
	ObjectID_t getLastKiller() const { return m_LastKiller; }

// data members
protected:
	MonsterType_t m_MonsterType; // 몬스터 타입
	string        m_Name;        // 몬스터 이름
	Dir_t         m_Dir;         // 시체의 방향
	bool          m_bhasHead;    // 머리가 달려 있나 없나.
	string        m_HostName;    // 이 시체에서 나오는 아이템에 대한 우선권을 가진 자의 이름
	int           m_HostPartyID; // 이 시체에서 나오는 아이템에 대한 우선권을 가진 파티의 ID
	string		  m_QuestHostName;	// 이 시체에서 나오는 퀘스트 아이템에 대한 우선권을 가진 자의 이름

	bool		  m_bShrine;	 // 성단인가?
	ObjectID_t	m_LastKiller;
};

#endif
