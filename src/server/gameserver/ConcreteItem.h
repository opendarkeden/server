#ifndef __CONCRETE_ITEM_H__
#define __CONCRETE_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "DB.h"
#include "ItemPolicies.h"

/*#define InitTableNameClass(C, S) \
class C { public: \
	static const string& getObjectTableName() { static string theString(string(S) + "Object"); return theString; } \
	static const string& getInfoTableName() { static string theString(string(S) + "Info"); return theString; } \
};*/

template <Item::ItemClass IClass,
	typename StackPolicy = NoStack, typename DurabilityPolicy = NoDurability, typename OptionPolicy = NoOption, typename GradePolicy = NoGrade,
	typename AttackingStatPolicy = NoAttacking, typename EnchantLevelPolicy = HasEnchantLevel>
class ConcreteItem : public Item
{
public:
	// 가상 함수 구체화
	ItemClass	getItemClass() const  { return IClass; }
	string		getObjectTableName() const  { return ItemObjectTableName[getItemClass()]; }
	ItemInfo*	getItemInfo() const { return g_pItemInfoManager->getItemInfo( getItemClass(), getItemType() ); }

	ItemType_t	getItemType() const  { return m_ItemType; }
	void		setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	VolumeWidth_t	getVolumeWidth() const  { return getItemInfo()->getVolumeWidth(); }
	VolumeHeight_t	getVolumeHeight() const  { return getItemInfo()->getVolumeHeight(); }
	Weight_t		getWeight() const  { return getItemInfo()->getWeight(); }

public:
	// 아이템 쌓기 관련
	bool	isStackable() const  { return m_Stack.hasValue(); }

	ItemNum_t	getNum() const  { return m_Stack.getValue(); }
	void		setNum(ItemNum_t Num)  { m_Stack.setValue(Num); }

public:
	// 내구도 관련
	Durability_t	getDurability() const  { return m_Durability.getValue(); }
	void			setDurability(Durability_t durability)  { m_Durability.setValue(durability); }
	Durability_t	getMaxDurability() const {
		if ( m_Durability.hasValue() )
		{
			Durability_t baseDur = getItemInfo()->getDurability();
//			return max(1000,((int)baseDur) + min((int)m_Grade.getDurabilityOffset(), 65000-baseDur));
			return max(1000,(int)baseDur + m_Grade.getDurabilityOffset());
		}
		else
			return getItemInfo()->getDurability();
	}

public:
	// 옵션 관련
	bool						hasOptionType() const  { return m_Option.hasOptionType(); }
	int							getOptionTypeSize() const  { return m_Option.getOptionTypeSize(); }
	int							getRandomOptionType() const  { return m_Option.getRandomOptionType(); }
	const list<OptionType_t>&	getOptionTypeList() const  { return m_Option.getOptionTypeList(); }
	OptionType_t				getFirstOptionType() const  { return m_Option.getFirstOptionType(); }
	void						removeOptionType(OptionType_t OptionType)  { m_Option.removeOptionType(OptionType); }
	void						changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType)  { m_Option.changeOptionType(currentOptionType, newOptionType); }
	void						addOptionType(OptionType_t OptionType)  { m_Option.addOptionType(OptionType); }
	void						setOptionType(const list<OptionType_t>& OptionType)  { m_Option.setOptionType(OptionType); }

public:
	// 아이템 등급 관련
	Grade_t	getGrade() const { return m_Grade.getValue(); }
	void	setGrade(Grade_t Grade) { m_Grade.setValue(Grade); }

	Luck_t	getLuck() const { return m_Grade.getLuck(); }

public:
	// 공격력 관련 속성
	Damage_t	getMinDamage() const  { return max(1,((int)getItemInfo()->getMinDamage()) + ((int)getBonusDamage()) + m_Grade.getDamageOffset()); }
	Damage_t	getMaxDamage() const  { return max(1,((int)getItemInfo()->getMaxDamage()) + ((int)getBonusDamage()) + m_Grade.getDamageOffset()); }
	Range_t		getRange() const  { return getItemInfo()->getRange(); }
	ToHit_t		getToHitBonus() const  { return getItemInfo()->getToHitBonus(); }
	Speed_t		getSpeed() const  { return getItemInfo()->getSpeed(); }
	int			getCriticalBonus() const  { return max(0,getItemInfo()->getCriticalBonus() + m_Grade.getCriticalOffset()); }

	BYTE		getBulletCount() const  { return m_AttackingStat.getBulletCount(); }
	void		setBulletCount(BYTE bulletCount)  { m_AttackingStat.setBulletCount(bulletCount); }

	bool		isSilverWeapon() const  { return m_AttackingStat.isSilverWeapon(); }
	Silver_t	getSilver() const  { return m_AttackingStat.getSilver(); }
	void		setSilver(Silver_t amount)  { m_AttackingStat.setSilver(amount); }

	bool		isGun() const  { return m_AttackingStat.isGun(); }

	Damage_t	getBonusDamage() const  { return m_AttackingStat.getBonusDamage(); }
	void		setBonusDamage(Damage_t BonusDamage)  { m_AttackingStat.setBonusDamage(BonusDamage); }

public:
	// 방어력 관련 속성
	Defense_t	getDefenseBonus() const  { return max(0,((int)getItemInfo()->getDefenseBonus()) + m_Grade.getDefenseOffset()); }
	Protection_t	getProtectionBonus() const  { return max(0,((int)getItemInfo()->getProtectionBonus()) + m_Grade.getProtectionOffset()); }

public:
	// 인챈트 레벨
	EnchantLevel_t	getEnchantLevel() const  { return m_EnchantLevel.getValue(); }
	void			setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel.setValue(level); }

private:
	ItemType_t			m_ItemType;

	StackPolicy			m_Stack;
	DurabilityPolicy	m_Durability;
	OptionPolicy		m_Option;
	GradePolicy			m_Grade;

	AttackingStatPolicy	m_AttackingStat;
	EnchantLevelPolicy	m_EnchantLevel;
};

#endif
