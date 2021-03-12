//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerCorpse.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_CORPSE_H__
#define __SLAYER_CORPSE_H__

#include "Item.h"
#include "ItemFactory.h"
#include "PCSlayerInfo3.h"
#include "Corpse.h"

class Slayer;

//////////////////////////////////////////////////////////////////////////////
// class SlayerCorpse;
// 슬레이어가 죽었을 경우, 남기는 시체이다.
//////////////////////////////////////////////////////////////////////////////

class SlayerCorpse : public Corpse 
{
public:
	SlayerCorpse(Slayer* pSlayer) ;
	virtual ~SlayerCorpse() ;

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0)  {}
	virtual bool destroy()  { return true; }
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y)  {}
	void tinysave(const string & field) const  { tinysave(field.c_str()); }
    void tinysave(const char* field) const  {}


public:
	virtual ItemClass getItemClass() const  { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType() const  { return SLAYER_CORPSE; }
	virtual void setItemType(ItemType_t itemType)  { throw UnsupportedError(__PRETTY_FUNCTION__); }

	virtual string toString() const ;

public:
	PCSlayerInfo3 & getSlayerInfo()  { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo() const  { return m_SlayerInfo; }
	void setSlayerInfo(const PCSlayerInfo3 & slayerInfo)  { m_SlayerInfo = slayerInfo; }

	void setXY(ZoneCoord_t X, ZoneCoord_t Y) { m_SlayerInfo.setX(X); m_SlayerInfo.setY(Y); }

protected:
	PCSlayerInfo3 m_SlayerInfo; // 시체의 외모에 대한 정보
};

#endif
