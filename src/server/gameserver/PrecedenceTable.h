//////////////////////////////////////////////////////////////////////////////
// Filename    : PrecedenceTable.h
// Written by  : excel96
// Description : 
// "먹자" 방지를 위한 우선권 계산을 위한 클래스이다.
// 개별적인 몬스터 객체 안에 존재하다가, 몬스터가 죽거나 흡혈 당할 때가 
// 되면 플레이어가 아이템을 먹거나, 흡혈을 할 수 있는 정당한 권리를 가지고
// 있는지를 검사한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PRECEDENCETABLE_H__
#define __PRECEDENCETABLE_H__

#include "Types.h"
#include "Timeval.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;

//////////////////////////////////////////////////////////////////////////////
// class PrecedenceElement;
// PrecedenceTable 안에 들어가는 객체로서 각각의 플레이어가 몬스터에게 가한
// 데미지 양과 마지막으로 데미지를 가한 시간, 그리고 그 플레이어어에 대한
// 정보를 기록해 두는 데 쓰인다.
//////////////////////////////////////////////////////////////////////////////

class PrecedenceElement
{
public:
	PrecedenceElement();

public:
	string getName(void) const { return m_Name; }
	void setName(const string& name) { m_Name = name; }

	int getPartyID(void) const { return m_PartyID; }
	void setPartyID(int PartyID) { m_PartyID = PartyID; }
	
	int getDamage(void) const { return m_Damage; }
	void setDamage(int Damage) { m_Damage = Damage; }

	Timeval getDeadline(void) const { return m_Deadline; }
	void setDeadline(const Timeval& deadline) { m_Deadline = deadline; }
	void setNextTime(void);

	string toString(void) const;

public:
	string  m_Name;
	int     m_PartyID;
	int     m_Damage;
	Timeval m_Deadline;

};

//////////////////////////////////////////////////////////////////////////////
// class PrecedenceTable;
// PrecedenceElement의 집합체로서 몬스터 객체 안에 composition 형식으로
// 포함된다. addPrecedence 함수를 이용해 각각의 플레이어가 준 데미지를
// 기억하고 있다가, compute 함수를 이용해 누가 이 몬스터에서 나오는 아이템 
// 또는 흡혈에 대해서 우선권을 가지고 있는 가를 판단해 저장하고 있는다.
//////////////////////////////////////////////////////////////////////////////

class PrecedenceTable
{
public:
	PrecedenceTable();
	~PrecedenceTable();

public:
//	void addPrecedence(Creature* pCreature, int damage);
	void addPrecedence(const string & Name, int PartyID, int damage);
	void heartbeat(const Timeval& currentTime);
	void compute(void);

public:
	bool canLoot(Creature* pCreature) const;
	bool canDrainBlood(Creature* pCreature) const;
	bool canGainRankExp(Creature* pCreature) const;

	string getHostName(void) const { return m_HostName; }
	int getHostPartyID(void) const { return m_HostPartyID; }

	bool getComputeFlag(void) const { return m_bComputeFlag; }
	void setComputeFlag(bool bFlag) { m_bComputeFlag = bFlag; }

	string getQuestHostName() const { return m_QuestHostName; }
	void setQuestHostName( const string& name ) { m_QuestHostName = name; }

	double getDamagePercent(const string& Name, int PartyID) const;

	string toString(void) const;

protected:
	hash_map<string, PrecedenceElement*> m_CreatureMap;
	hash_map<int, PrecedenceElement*> m_PartyMap;

	string m_FirstAttackerName; // 제일 먼저 선공을 가한 자의 이름
	int m_FirstAttackerPartyID; // 제일 먼저 선공을 가한 자의 파티 ID

	string m_HostName; // 주인의 이름
	int m_HostPartyID; // 주인의 파티 ID

	string m_QuestHostName; // 퀘스트 아이템의 주인 이름

	bool m_bComputeFlag; // 계산을 마친 상태인가...?

	Damage_t m_TotalDamage;	// 데미지 총합
};

#endif
