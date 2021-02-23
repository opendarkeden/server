//////////////////////////////////////////////////////////////////////////////
// Filename    : PCOustersInfo.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_OUSTERS_INFO_H__
#define __PC_OUSTERS_INFO_H__

#include "PCInfo.h"

//////////////////////////////////////////////////////////////////////////////
// Ousters 정보를 담고 있는 객체.
// GCPCList 패킷에 담겨서 클라이언트에게 전송된다.
// 아이템이나 걸려있는 마법 같은 정보는 담겨있지 않다.
//////////////////////////////////////////////////////////////////////////////

class PCOustersInfo : public PCInfo 
{
public:
	enum OustersColors
	{
		OUSTERS_COLOR_COAT,
		OUSTERS_COLOR_HAIR,
		OUSTERS_COLOR_ARM,
		OUSTERS_COLOR_BOOTS,
		OUSTERS_COLOR_MAX
	};

public:
	PCType getPCType () const throw () { return PC_OUSTERS; }

	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	uint getSize () const throw ()
	{
		return szBYTE					// 이름길이
			+ m_Name.size() 			// 아우스터스 이름
			+ szSlot					// 슬롯
			+ szAlignment				// 성향
			+ szSex						// 성별
			+ szColor * OUSTERS_COLOR_MAX	// 색상
			+ szBYTE 					// 옷, 무기 타입
			+ szAttr* 3 				// 능력치
			+ szHP* 2					// HP
			+ szMP* 2					// MP
			+ szRank					// 계급
			+ szExp						// 경험치
			+ szLevel					// 레벨
			+ szFame					// 명성
			+ szBonus					// 보너스 포인트
			+ szSkillBonus				// 스킬보너스 포인트
			+ szLevel;
	}

	// get max size of object
	static uint getMaxSize () throw ()
	{
		return szBYTE + 20				// 아우스터스 이름
			+ szSlot					// 슬롯
			+ szAlignment				// 성향
			+ szSex						// 성별
			+ szColor* OUSTERS_COLOR_MAX	// 색상
			+ szBYTE 					// 옷, 무기 타입
			+ szAttr* 3	 				// 능력치
			+ szHP* 2					// HP
			+ szMP* 2					// MP
			+ szRank					// 계급
			+ szExp						// 경험치
			+ szFame					// 명성치
			+ szLevel					// 레벨
			+ szBonus					// 보너스 포인트
			+ szSkillBonus				// 스킬 보너스 포인트
			+ szLevel;
	}

	string toString () const throw ();

public:
    string getName () const throw () { return m_Name; }
    void setName (string name) throw () { m_Name = (name.size() > 20) ? name.substr(0,20) : name; }

	Slot getSlot () const throw () { return m_Slot; }
	void setSlot (Slot slot) throw () { m_Slot = slot; }
	void setSlot (string slot) throw (InvalidProtocolException)
	{
		if (slot == Slot2String[SLOT1])
			m_Slot = SLOT1;
		else if (slot == Slot2String[SLOT2])
			m_Slot = SLOT2;
		else if (slot == Slot2String[SLOT3])
			m_Slot = SLOT3;
		else
			throw InvalidProtocolException("invalid slot value");
	}

	Alignment_t getAlignment() const throw() { return m_Alignment; }
	void setAlignment(Alignment_t Alignment) throw() { m_Alignment = Alignment; }

	Fame_t getFame () const throw () { return m_Fame; }
	void setFame (Fame_t f) throw () { m_Fame = f; }

	Sex getSex () const throw () { return m_Sex; }
	void setSex (Sex sex) throw () { m_Sex = sex; }
	void setSex (string sex) throw (InvalidProtocolException)
	{
		if (sex == Sex2String[MALE]) 
			m_Sex = MALE;
		else if (sex == Sex2String[FEMALE]) 
			m_Sex = FEMALE;
		else
			throw InvalidProtocolException("invalid sex value");
	}

	Color_t getCoatColor() const throw() { return m_CoatColor; }
	void setCoatColor(Color_t CoatColor) throw() { m_CoatColor = CoatColor; }

	Color_t getHairColor () const throw () { return m_HairColor; }
	void setHairColor (Color_t hairColor) throw () { m_HairColor = hairColor; }

	Color_t getArmColor () const throw () { return m_ArmColor; }
	void setArmColor (Color_t armColor) throw () { m_ArmColor = armColor; }

	Color_t getBootsColor () const throw () { return m_BootsColor; }
	void setBootsColor (Color_t bootsColor) throw () { m_BootsColor = bootsColor; }

	OustersCoatType getCoatType() const throw() { return m_CoatType; }
	void setCoatType(OustersCoatType coatType) throw() { m_CoatType = coatType; }

	OustersArmType getArmType() const throw() { return m_ArmType; }
	void setArmType( OustersArmType armType ) throw() { m_ArmType = armType; }

    Attr_t getSTR () const throw (Error) { if (m_STR > maxOustersAttr) throw Error("STR out of range"); return m_STR; }
	void setSTR (Attr_t str) throw (Error) { if (str > maxOustersAttr) throw Error("STR out of range"); m_STR = str; }

	Attr_t getDEX () const throw (Error) { if (m_DEX > maxOustersAttr) throw Error("DEX out of range"); return m_DEX; }
	void setDEX (Attr_t dex) throw (Error) { if (dex > maxOustersAttr) throw Error("DEX out of range"); m_DEX = dex; }

	Attr_t getINT () const throw (Error) { if (m_INT > maxOustersAttr) throw Error("INT out of range"); return m_INT; }
	void setINT (Attr_t inte) throw (Error) { if (inte > maxOustersAttr) throw Error("INT out of range"); m_INT = inte; }

	HP_t getHP (AttrType attrType = ATTR_CURRENT) const throw () { return m_HP[attrType]; }
	void setHP (HP_t hp, AttrType attrType = ATTR_CURRENT) throw () { m_HP[attrType] = hp; }
	void setHP (HP_t curHP, HP_t maxHP) throw () { m_HP[ATTR_CURRENT] = curHP; m_HP[ATTR_MAX] = maxHP; }

	MP_t getMP (AttrType attrType = ATTR_CURRENT) const throw () { return m_MP[attrType]; }
	void setMP (MP_t mp, AttrType attrType = ATTR_CURRENT) throw () { m_MP[attrType] = mp; }
	void setMP (MP_t curMP, MP_t maxMP) throw () { m_MP[ATTR_CURRENT] = curMP; m_MP[ATTR_MAX] = maxMP; }

	Level_t getLevel () const throw () { return m_Level; }
	void setLevel (Level_t exp) throw () { m_Level = exp; }

	Exp_t getExp () const throw () { return m_Exp; }
	void setExp (Exp_t exp) throw () { m_Exp = exp; }

	Rank_t getRank () const throw () { return m_Rank; }
	void setRank (Rank_t rank) throw () { m_Rank = rank; }

	Bonus_t getBonus() const throw () { return m_Bonus; }
	void setBonus(Bonus_t Bonus) throw () { m_Bonus = Bonus; }

	SkillBonus_t getSkillBonus() const throw () { return m_SkillBonus; }
	void setSkillBonus( SkillBonus_t skillBonus ) throw () { m_SkillBonus = skillBonus; }

	Level_t getAdvancementLevel() const { return m_AdvancementLevel; }
	void	setAdvancementLevel(Level_t level) { m_AdvancementLevel = level; }

private:
	// PC name
	string m_Name;

	// PC 슬롯
	Slot m_Slot;

	// Alignment
	Alignment_t m_Alignment;

	// PC sex
	Sex m_Sex;

	// hair color, skin color,
	Color_t m_CoatColor;
	Color_t m_HairColor;
	Color_t m_ArmColor;
	Color_t m_BootsColor;

	// wear Type/ color
	OustersCoatType m_CoatType;
	OustersArmType m_ArmType;

	// 계급
	Rank_t m_Rank;

	// Exp
	Level_t m_Level;

	// Attributes
	Attr_t m_STR;
	Attr_t m_DEX;
	Attr_t m_INT;

	// HP
	// HP[0] = current hp, hp[1] == max hp
	HP_t m_HP[2];

	// MP
	// MP[0] = current mp, mp[1] == max mp
	MP_t m_MP[2];

	// Exp
	Exp_t m_Exp;

	// Fame 
	Fame_t m_Fame;

	// Bonus Point
	Bonus_t m_Bonus;

	// Skill Bonus Point
	SkillBonus_t m_SkillBonus;

	Level_t	m_AdvancementLevel;
};

#endif
