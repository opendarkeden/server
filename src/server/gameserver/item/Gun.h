//////////////////////////////////////////////////////////////////////////////
// Filename    : Gun.h
// Written By  : sigi
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUN_H__
#define __GUN_H__

#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class Gun;
//////////////////////////////////////////////////////////////////////////////

class Gun : public Item 
{
public:
	Gun() throw();
	Gun(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	virtual ~Gun() throw();
	
public:
	virtual void saveBullet() throw(Error) = 0;
	bool isGun() const throw() { return true; }

public:
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


	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	BYTE getBulletCount() const throw() { return m_BulletCount; }
	void setBulletCount(BYTE bulletCount) throw() { m_BulletCount = bulletCount; }

	Damage_t getBonusDamage() const throw() { return m_BonusDamage;}
	void setBonusDamage(Damage_t damage) throw() { m_BonusDamage = damage;}

	virtual Silver_t getSilver() const throw() { return m_Silver; }
	virtual void setSilver(Silver_t amount) throw() { m_Silver = amount; }

	virtual EnchantLevel_t getEnchantLevel() const throw() { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	void makePCItemInfo(PCItemInfo& result) const;

protected:
	ItemType_t     m_ItemType;
	list<OptionType_t>   m_OptionType;
	Durability_t   m_Durability;
	BYTE           m_BulletCount;
	BYTE           m_BonusDamage;
	Silver_t       m_Silver;
	EnchantLevel_t m_EnchantLevel;
};

#endif
