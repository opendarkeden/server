//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireCoupleRing.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_COUPLE_RING_H__
#define __VAMPIRE_COUPLE_RING_H__

#include "CoupleRingBase.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRing;
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRing : public CoupleRingBase 
{
public:
	VampireCoupleRing() throw();
	VampireCoupleRing(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string getObjectTableName() const throw() { return "VampireCoupleRingObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual bool hasOptionType() const throw() { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	virtual int getRandomOptionType() const throw() { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList() const throw() { return m_OptionType; }
	virtual OptionType_t getFirstOptionType() const throw() { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }

	Defense_t getDefenseBonus() const throw(Error) { return 8; }
	Protection_t getProtectionBonus() const throw(Error) { return 3; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	bool	hasPartnerItem() throw(Error);

private:
	ItemType_t 			m_ItemType;
	list<OptionType_t>	m_OptionType;
	
	static Mutex    	m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t 	m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingInfo
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string toString() const throw();

private:
};

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingInfoManager;
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual void load() throw(Error);
};

extern VampireCoupleRingInfoManager* g_pVampireCoupleRingInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingFactory
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string getItemClassName() const throw() { return "VampireCoupleRing"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new VampireCoupleRing(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingLoader;
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string getItemClassName() const throw() { return "VampireCoupleRing"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern VampireCoupleRingLoader* g_pVampireCoupleRingLoader;

#endif
