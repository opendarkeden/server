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
	SlayerCorpse(Slayer* pSlayer) throw(Error);
	virtual ~SlayerCorpse() throw();

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error) {}
	virtual bool destroy() throw(Error) { return true; }
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y) throw(Error) {}
	void tinysave(const string & field) const throw (Error) { tinysave(field.c_str()); }
    void tinysave(const char* field) const throw (Error) {}


public:
	virtual ItemClass getItemClass() const throw() { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType() const throw() { return SLAYER_CORPSE; }
	virtual void setItemType(ItemType_t itemType) throw() { throw UnsupportedError(__PRETTY_FUNCTION__); }

	virtual string toString() const throw();

public:
	PCSlayerInfo3 & getSlayerInfo() throw() { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo() const throw() { return m_SlayerInfo; }
	void setSlayerInfo(const PCSlayerInfo3 & slayerInfo) throw() { m_SlayerInfo = slayerInfo; }

	void setXY(ZoneCoord_t X, ZoneCoord_t Y) { m_SlayerInfo.setX(X); m_SlayerInfo.setY(Y); }

protected:
	PCSlayerInfo3 m_SlayerInfo; // 시체의 외모에 대한 정보
};

#endif
