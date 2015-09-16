//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemInfo.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_INFO_H__
#define __ITEM_INFO_H__

#include "Types.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ItemInfo
//////////////////////////////////////////////////////////////////////////////

class ItemInfo 
{
// constructor & destructor
public:
	ItemInfo() throw();
	virtual ~ItemInfo() throw();


// 공통 정보
public:
	virtual Item::ItemClass getItemClass() const throw() = 0;
	string getItemClassName() const throw() { return ItemClass2String[getItemClass()]; }

	ItemType_t getItemType() const throw() { return m_ItemType; }
    void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }
 
	string getName() const throw() { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; }

	string getEName() const throw() { return m_EName; }
	void setEName(const string & ename) throw() { m_EName = ename; }
	
	Price_t getPrice() const throw() { return m_Price; }
	void setPrice(Price_t Price) throw(){ m_Price = Price; }

	VolumeType_t getVolumeType() const throw() { return m_VolumeType; }
	void setVolumeType(VolumeType_t VolumeType) throw() { m_VolumeType = VolumeType; }
	VolumeWidth_t getVolumeWidth() const throw();
	VolumeHeight_t getVolumeHeight() const throw();

	Weight_t getWeight() const throw() { return m_Weight; }
	void setWeight(Weight_t weight) throw() { m_Weight = weight; }

	Ratio_t getRatio() const throw() { return m_Ratio; }
	void setRatio(Ratio_t Ratio) throw() { m_Ratio = Ratio; }
	
	string getDescription() const throw() { return m_Description; }
	void setDescription(const string& description) throw() { m_Description = description ; }
	
	virtual Attr_t  getReqSTR(void) const throw()    { return m_ReqSTR; }
	virtual Attr_t  getReqDEX(void) const throw()    { return m_ReqDEX; }
	virtual Attr_t  getReqINT(void) const throw()    { return m_ReqINT; }
	virtual Attr_t  getReqSum(void) const throw()    { return m_ReqSum; }
	virtual Level_t getReqLevel(void) const throw()  { return m_ReqLevel; }
	virtual Level_t getReqAdvancedLevel(void) const throw()  { return m_ReqAdvanceLevel; }
	virtual Attr_t  getReqGender(void) const throw() { return m_ReqGender; }

	virtual void    setReqSTR(Attr_t req) throw()      { m_ReqSTR = req; }
	virtual void    setReqDEX(Attr_t req) throw()      { m_ReqDEX = req; }
	virtual void    setReqINT(Attr_t req) throw()      { m_ReqINT = req; }
	virtual void    setReqSum(Attr_t req) throw()      { m_ReqSum = req; }
	virtual void    setReqLevel(Level_t req) throw()   { m_ReqLevel = req; }
	virtual void    setReqAdvanceLevel(Level_t req) throw()   { m_ReqAdvanceLevel = req; }
	virtual void    setReqGender(Attr_t req) throw()   { m_ReqGender = req; }
	virtual void    setReqAbility(const string& req) throw();

	virtual string toString() const throw() = 0;


// 개별 정보. 편의상 베이스 클래스에 정의해준다.
public:
	virtual Durability_t getDurability() const throw() { return 1; }
	virtual void setDurability(Durability_t durability) throw() {}

	virtual Damage_t getMinDamage() const throw() { return 0; }
	virtual void setMinDamage(Damage_t damage) throw() {}

	virtual Damage_t getMaxDamage() const throw() { return 0; }
	virtual void setMaxDamage(Damage_t damage) throw() {}

	virtual Range_t getRange() const throw() { return 0; }
	virtual void setRange(Range_t range) throw() {}

	virtual ToHit_t getToHitBonus() const throw() { return 0; }
	virtual void setToHitBonus(ToHit_t tohit) throw() {}

	virtual Defense_t getDefenseBonus() const throw() { return 0; }
	virtual void setDefenseBonus(Defense_t defense) throw() {}

	virtual Protection_t getProtectionBonus() const throw() { return 0; }
	virtual void setProtectionBonus(Protection_t defense) throw() {}

	virtual MP_t getMPBonus() const throw() { return 0;}
	virtual void setMPBonus(MP_t bonus) throw() { }

	virtual Silver_t getMaxSilver() const throw() { return 0; }
	virtual void setMaxSilver(Silver_t amount) throw() { }

	virtual Speed_t getSpeed(void) const throw() { return 0; }
	virtual void setSpeed(Speed_t speed) throw() { } 

	virtual uint getItemLevel(void) const throw() { return 99; }
	virtual void setItemLevel(uint level) throw() { }

	virtual int getCriticalBonus(void) const throw() { return 0; }
	virtual void setCriticalBonus(int bonus) throw() { };

	virtual ElementalType getElementalType() const { return ELEMENTAL_MAX; }
	virtual Elemental_t getElemental() const { return 0; }
	
	// ItemType에 따른 기본 옵션
	virtual void    setDefaultOptions(const string& options) throw(Error);
	void			addDefaultOptions(OptionType_t optionType) throw();
	void			clearDefaultOptions() throw();
	bool			hasDefaultOptions() const { return m_bDefaultOptions; }
	const list<OptionType_t>& getDefaultOptions() const { return m_DefaultOptions; }

	Ratio_t         getUpgradeRatio(void) const  { return m_UpgradeRatio; }
	void        setUpgradeRatio(Ratio_t ratio)     { m_UpgradeRatio = ratio; }
	bool 		isUpgradeSucceed() const;

	int         getUpgradeCrashPercent(void) const  { return m_UpgradeCrashPercent; }
	void        setUpgradeCrashPercent(int per)     { m_UpgradeCrashPercent = per; }
	bool 		isUpgradeCrash() const;

	int         isUnique() const  				{ return m_bUnique; }
	void        setUnique(bool bUnique=true)    { m_bUnique = bUnique; }

	Ratio_t     getNextOptionRatio(void) const  { return m_NextOptionRatio; }
	void        setNextOptionRatio(Ratio_t ratio)     { m_NextOptionRatio = ratio; }

	ItemType_t	getNextItemType() const { return m_NextItemType; }
	void		setNextItemType(ItemType_t nextItemType) { m_NextItemType = nextItemType; }

	Ratio_t		getDowngradeRatio() const { return m_DowngradeRatio; }
	void		setDowngradeRatio(Ratio_t ratio ) { m_DowngradeRatio = ratio; }

// member data
protected:
	ItemType_t   m_ItemType;     // 아이템 타입
	string       m_Name;         // 이름
	string       m_EName;        // 영문 이름
	Price_t      m_Price;        // 가격
	VolumeType_t m_VolumeType;   // 부피
	Weight_t     m_Weight;       // 무게
	Ratio_t      m_Ratio;        // 아이템 등장 확률(갬블 확률)
	string       m_Description;  // 아이템 설명
	Attr_t       m_ReqSTR;       // 필요한 STR
	Attr_t       m_ReqDEX;       // 필요한 DEX
	Attr_t       m_ReqINT;       // 필요한 INT
	Attr_t       m_ReqSum;       // 필요한 능력치의 합
	Level_t      m_ReqLevel;     // 필요한 레벨
	Level_t      m_ReqAdvanceLevel;// 필요한 전직 레벨
	Attr_t       m_ReqGender;    // 필요한 성

	bool                    m_bDefaultOptions;	// 기본 옵션이 있나?
	list<OptionType_t>	m_DefaultOptions;	// 기본 옵션

	Ratio_t      m_UpgradeRatio;    		// enchant해서 성공할 확률
	int          m_UpgradeCrashPercent;   // upgrade가 실패해서 부서질 확률 = m_UpgradeCrashPercent%

	bool		 m_bUnique;		// unique item 인가?

	Ratio_t      m_NextOptionRatio;    		// 다른 옵션이 붙을 확률

	ItemType_t	 m_NextItemType;
	Ratio_t		 m_DowngradeRatio;
};

#endif	// __ITEM_INFO_H__
