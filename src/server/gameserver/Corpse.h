//////////////////////////////////////////////////////////////////////////////
// Filename    : Corpse.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CORPSE_H__
#define __CORPSE_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include "ItemFactory.h"

//////////////////////////////////////////////////////////////////////////////
// 시체 타입
//////////////////////////////////////////////////////////////////////////////
enum CorpseType 
{
	SLAYER_CORPSE = 0,
	VAMPIRE_CORPSE,
	NPC_CORPSE,
	MONSTER_CORPSE,
	OUSTERS_CORPSE
};

//////////////////////////////////////////////////////////////////////////////
// class Corpse
//////////////////////////////////////////////////////////////////////////////

class Corpse : public Item 
{
public:
	Corpse() ;
	virtual ~Corpse() ;

public:
	virtual ItemClass getItemClass() const  { return ITEM_CLASS_CORPSE; }
	virtual string getObjectTableName() const  { return ""; }

	virtual ItemType_t getItemType() const  = 0;
	virtual void setItemType(ItemType_t monsterType)  = 0;

    virtual VolumeWidth_t getVolumeWidth() const  { return 0; }
    virtual VolumeHeight_t getVolumeHeight() const  { return 0; }
    virtual Weight_t getWeight() const  { return 0; }

	virtual string toString() const  = 0;

public:
	void addTreasure(Item* pItem) ;
	Item* getTreasure() ;
	Item* getTreasure( ObjectID_t objectID ) const ;
	Item* popTreasure( ObjectID_t objectID ) ;

	BYTE getTreasureCount() const  { return m_TreasureCount; }
	void setTreasureCount(BYTE Count)  { m_TreasureCount = Count; }

	ZoneCoord_t getX() const  { return m_X; }
	void setX(ZoneCoord_t x)  { m_X = x; }

	ZoneCoord_t getY() const  { return m_Y; }
	void setY(ZoneCoord_t y)  { m_Y = y; }

	// get/set zone
    Zone* getZone() const  { return m_pZone; }
    void setZone(Zone* pZone)  { m_pZone = pZone; }

	int getLevel() const  { return m_Level; }
	void setLevel(int level)  { m_Level = level; }

	Exp_t getExp() const  { return m_Exp; }
	void setExp(Exp_t exp)  { m_Exp = exp; }

protected:
	list<Item*> m_Treasures;     // 보물의 리스트
	BYTE        m_TreasureCount; // 보물의 숫자

	// 성물 보관대를 위한 필살 좌표 넣기
	// 그 외에는 좌표가 제대로 설정 안될 수 있으므로 사용금지
	ZoneCoord_t  m_X, m_Y;

	Zone*		m_pZone;

	// 시체에 별 내용이 다 들어가는군 ;;;
	int 		m_Level;		// 레벨 -_-;
	Exp_t		m_Exp;			// 이넘 죽이고 얻은 경험치;
	
	// 몬스터가 Relic인지 아닌지를 저장하는 변수
	// 만약 Relic이라면, 몬스터의 시체가 사라지지 않도록 해야 한다.
};

//////////////////////////////////////////////////////////////////////////////
// class CorpseFactory
//////////////////////////////////////////////////////////////////////////////

class CorpseFactory : public ItemFactory 
{
public:
	Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return NULL; }
	string getItemName() const  { return "Corpse"; }
	Item::ItemClass getItemClass() const  { return Item::ITEM_CLASS_CORPSE; }
};

#endif
