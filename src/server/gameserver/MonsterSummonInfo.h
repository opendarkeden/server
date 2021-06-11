//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterSummonInfo.h
// Written By  : 쉭
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_SUMMON_INFO_H__
#define __MONSTER_SUMMON_INFO_H__

#include "Types.h"
#include "MonsterInfoTypes.h"
#include <list>
#include <vector>

struct MonsterCollection;

// 소환될때의 정보
struct SUMMON_INFO
{
	enum ClanType
	{
		CLAN_TYPE_DEFAULT,			// default = 1
		CLAN_TYPE_RANDOM_EACH,		// 이번에 생성되는 애들 각각 다르게
		CLAN_TYPE_RANDOM_GROUP,		// 이번에 생성되는 애들 전부 같게
		CLAN_TYPE_GROUP,			// 이번에 생성되는 애들 전부 같게. clanID지정
	};

	SUMMON_INFO()
	{
		scanEnemy = false;
		canScanEnemy = false;
		clanType = CLAN_TYPE_DEFAULT;
		clanID = 0;
		hasItem = true;
		regenType = REGENTYPE_MAX;
		initHPPercent = 0;
	}

	bool 		canScanEnemy;		// 적(몬스터? -_-;)을 스스로 scan하는가?
	ClanType 	clanType;
	int 	 	clanID;
	bool	 	hasItem;			// 소환된 몬스터가 아이템을 가지는가?
	RegenType   regenType;
	bool 		scanEnemy;			// 생성될때 적(몬스터? -_-;)을  scan하는가?
	int 		initHPPercent;
};

// 소환될때의 정보: 여러가지를 한꺼번에 소환
struct SUMMON_INFO2 : public SUMMON_INFO
{
	ZoneCoord_t   		X;
	ZoneCoord_t   		Y; 
	MonsterCollection*	pMonsters;
};

// 몬스터 몇 마리
struct MonsterCollectionInfo
{
	SpriteType_t	SpriteType;
	MonsterType_t	MonsterType;
	int             Num;

	void parseString(const string& infoString);

	string toString() const;
};

// 몬스터 여러 종류
struct MonsterCollection
{
	list<MonsterCollectionInfo> Infos;

	void parseString(const string& collectionString);

	string toString() const;
};

// 소환 단계
struct MonsterSummonStep
{
	vector<MonsterCollection>  Collections;

	const MonsterCollection* getRandomMonsterCollection() const;

	void parseString(const string& summonStepsString);

	string toString() const;
};

// 소환 정보
struct MonsterSummonInfo
{
	vector<MonsterSummonStep>  Steps;
	
	const MonsterCollection* getRandomMonsterCollection(int step) const;
	bool hasNextMonsterCollection(int step) const;

	void parseString(const string& summonInfoString);

	string toString() const;
};

#endif
