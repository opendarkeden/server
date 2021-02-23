//////////////////////////////////////////////////////////////////////////////
// Filename    : PCSlayerInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_SLAYER_INFO_H__
#define __PC_SLAYER_INFO_H__

#include "PCInfo.h"
#include <bitset>

//////////////////////////////////////////////////////////////////////////////
// Slayer 정보를 담고 있는 객체.
// GCPCList 패킷에 담겨서 클라이언트에게 전송된다.
// 아이템이나 걸려있는 마법 같은 정보는 담겨있지 않다.
//////////////////////////////////////////////////////////////////////////////

class PCSlayerInfo : public PCInfo 
{
public:
	// Slayer Outlook Information
    enum SlayerBits 
	{
        SLAYER_BIT_SEX ,
		SLAYER_BIT_HAIRSTYLE1 ,
		SLAYER_BIT_HAIRSTYLE2 ,
		SLAYER_BIT_HELMET1,
		SLAYER_BIT_HELMET2,
		SLAYER_BIT_JACKET1,
		SLAYER_BIT_JACKET2,
		SLAYER_BIT_JACKET3,
		SLAYER_BIT_PANTS1,
		SLAYER_BIT_PANTS2,
		SLAYER_BIT_PANTS3,
		SLAYER_BIT_WEAPON1,
		SLAYER_BIT_WEAPON2,
		SLAYER_BIT_WEAPON3,
		SLAYER_BIT_WEAPON4,
		SLAYER_BIT_SHIELD1,
		SLAYER_BIT_SHIELD2,
		SLAYER_BIT_MAX
		//SLAYER_BIT_WEAPON4,
    };

	// Slayer Color Informations
	enum SlayerColors 
	{
		SLAYER_COLOR_HAIR ,
		SLAYER_COLOR_SKIN ,
		SLAYER_COLOR_HELMET ,
		SLAYER_COLOR_JACKET ,
		SLAYER_COLOR_PANTS ,
		SLAYER_COLOR_WEAPON ,
		SLAYER_COLOR_SHIELD ,
		SLAYER_COLOR_MAX
	};

public:

	// get pc type
	PCType getPCType () const throw () { return PC_SLAYER; }

	// read data from socket input stream
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get size of object
	uint getSize () const throw ()
	{
		return szBYTE + m_Name.size() 
			+ szSlot
			+ szAlignment
			+ szAttr* 3
			+ szRank
			+ szExp* 3
			+ szHP* 2
			+ szMP* 2
			+ szFame
			//+ szGold
			+ szSkillLevel* 6
			//+ szZoneID
			+ szDWORD                       // 슬레이어 플래그
			+ szColor* SLAYER_COLOR_MAX  // 색깔 정보
			+ szLevel;
	}

	// get max size of object
	static uint getMaxSize () throw ()
	{
		return szBYTE + 20
			+ szSlot
			+ szAlignment
			+ szAttr* 3
			+ szRank
			+ szExp* 3
			+ szHP* 2
			+ szMP* 2
			+ szFame
			//+ szGold
			+ szSkillLevel* 6
			//+ szZoneID
			+ szDWORD                       // 슬레이어 플래그
			+ szColor* SLAYER_COLOR_MAX  // 색깔 정보
			+ szLevel;
	}

	// get debug string
	string toString () const throw ();

public:
    // get/set PC's name
    string getName () const throw () { return m_Name; }
    void setName (const string& name) throw () { m_Name = (name.size() > 20) ? name.substr(0,20) : name; }

	// get/set Slot
	Slot getSlot () const throw () { return m_Slot; }
	void setSlot (Slot slot) throw () { m_Slot = slot; }
	void setSlot (string slot) throw (InvalidProtocolException) 
	{
		if (slot == Slot2String[SLOT1]) 
		{
			m_Slot = SLOT1;
		}
		else if (slot == Slot2String[SLOT2]) 
		{
			m_Slot = SLOT2;
		}
		else if (slot == Slot2String[SLOT3]) 
		{
			m_Slot = SLOT3;
		}
		else 
		{
			throw InvalidProtocolException("invalid slot value");
		}
	}

	// get/set Alignment
	Alignment_t getAlignment() const throw() { return m_Alignment; }
	void setAlignment(Alignment_t Alignment) throw() { m_Alignment = Alignment; }

	// get/set STR
	// *CAUTION*
	// Assert()로 할 경우, NDEBUG 모드에서는 disable 되므로 if 로 체크해야 한다. 
	Attr_t getSTR () const throw (Error) { if (m_STR > maxSlayerAttr) throw Error("STR out of range"); return m_STR; }
	void setSTR (Attr_t str) throw (Error) { if (str > maxSlayerAttr) throw Error("STR out of range"); m_STR = str; }

	// get/set DEX
	Attr_t getDEX () const throw (Error) { if (m_DEX > maxSlayerAttr) throw Error("DEX out of range"); return m_DEX; }
	void setDEX (Attr_t dex) throw (Error) { if (dex > maxSlayerAttr) throw Error("DEX out of range"); m_DEX = dex; }

	// get/set INT
	Attr_t getINT () const throw (Error) { if (m_INT > maxSlayerAttr) throw Error("INT out of range"); return m_INT; }
	void setINT (Attr_t inte) throw (Error) { if (inte > maxSlayerAttr) throw Error("INT out of range"); m_INT = inte; }

	// get/set STR Exp
	Exp_t getSTRExp () const throw(Error) { return m_STRExp; };
	void setSTRExp(Exp_t STRExp) throw(Error) { m_STRExp = STRExp; }

	// get/set DEX Exp
	Exp_t getDEXExp () const throw(Error) { return m_DEXExp; };
	void setDEXExp(Exp_t DEXExp) throw(Error) { m_DEXExp = DEXExp; }

	// get/set INT Exp
	Exp_t getINTExp () const throw(Error) { return m_INTExp; };
	void setINTExp(Exp_t INTExp) throw(Error) { m_INTExp = INTExp; }


	Rank_t getRank () const throw () { return m_Rank; }
	void setRank (Rank_t rank) throw () { m_Rank = rank; }


	// get/set HP
	HP_t getHP (AttrType attrType = ATTR_CURRENT) const throw () { return m_HP[attrType]; }
	void setHP (HP_t hp, AttrType attrType = ATTR_CURRENT) throw () { m_HP[attrType] = hp; }
	void setHP (HP_t curHP, HP_t maxHP) throw () { m_HP[ATTR_CURRENT] = curHP; m_HP[ATTR_MAX] = maxHP; }

	// get/set MP
	MP_t getMP (AttrType attrType = ATTR_CURRENT) const throw () { return m_MP[attrType]; }
	void setMP (MP_t mp, AttrType attrType = ATTR_CURRENT) throw () { m_MP[attrType] = mp; }
	void setMP (MP_t curMP, MP_t maxMP) throw () { m_MP[ATTR_CURRENT] = curMP; m_MP[ATTR_MAX] = maxMP; }

	// get/set fame
	Fame_t getFame () const throw () { return m_Fame; }
	void setFame (Fame_t fame) throw () { m_Fame = fame; }

	// get/set gold
	//Gold_t getGold () const throw () { return m_Gold; }
	//void setGold (Gold_t gold) throw () { m_Gold = gold; }

	  // get/set skill domain level
	SkillLevel_t getSkillDomainLevel (SkillDomain domain) const throw () { return m_DomainLevels[ domain ]; }
	void setSkillDomainLevel (SkillDomain domain, SkillLevel_t skillLevel) throw () { m_DomainLevels[ domain ] = skillLevel; }

	  // get/set zoneID
	//ZoneID_t getZoneID () const throw () { return m_ZoneID; }
	//void setZoneID (ZoneID_t zoneID) throw () { m_ZoneID = zoneID; }

	Level_t getAdvancementLevel() const { return m_AdvancementLevel; }
	void	setAdvancementLevel(Level_t level) { m_AdvancementLevel = level; }

// get/set outlook
public:
	// get/set sex
    Sex getSex () const throw () 
	{ 
		return m_Outlook.test(SLAYER_BIT_SEX)?MALE:FEMALE; 
	}
    void setSex (Sex sex) throw () 
	{ 
		m_Outlook.set(SLAYER_BIT_SEX,(sex==MALE?true:false)); 
	}

	void setSex (string sex) throw(InvalidProtocolException)
	{
		if (sex == Sex2String[MALE])
			m_Outlook.set(SLAYER_BIT_SEX, true);
		else if (sex == Sex2String[FEMALE])
			m_Outlook.set(SLAYER_BIT_SEX, false);
		else
			throw InvalidProtocolException("invalid sex value");
	}

	// get/set hair style
	HairStyle getHairStyle () const throw () 
	{ 
		return HairStyle((m_Outlook.to_ulong() >> SLAYER_BIT_HAIRSTYLE1) & 3); 
	}
	void setHairStyle (HairStyle hairStyle) throw () 
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(hairStyle << SLAYER_BIT_HAIRSTYLE1); 
	}

	void setHairStyle (string hairStyle) throw (InvalidProtocolException)
	{
		if (hairStyle == HairStyle2String[HAIR_STYLE1]) 
		{
			m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
			m_Outlook |= bitset<SLAYER_BIT_MAX>(HAIR_STYLE1 << SLAYER_BIT_HAIRSTYLE1);
		}
		else if (hairStyle == HairStyle2String[HAIR_STYLE2]) 
		{
			m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
			m_Outlook |= bitset<SLAYER_BIT_MAX>(HAIR_STYLE2 << SLAYER_BIT_HAIRSTYLE1);
		}
		else if (hairStyle == HairStyle2String[HAIR_STYLE3]) 
		{
			m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
			m_Outlook |= bitset<SLAYER_BIT_MAX>(HAIR_STYLE3 << SLAYER_BIT_HAIRSTYLE1);
		}
		else
			throw InvalidProtocolException("invalid hairstyle value");
	}

	// get/set helmet
	HelmetType getHelmetType () const throw () 
	{ 
		return HelmetType((m_Outlook.to_ulong() >> SLAYER_BIT_HELMET1) & 3); 
	}
	void setHelmetType (HelmetType helmetType) throw ()
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HELMET1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(helmetType << SLAYER_BIT_HELMET1); 
	}

	// get/set jacket
	JacketType getJacketType () const throw () 
	{ 
		return JacketType((m_Outlook.to_ulong() >> SLAYER_BIT_JACKET1) & 7); 
	}
	void setJacketType (JacketType jacketType) throw ()
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_JACKET1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(jacketType << SLAYER_BIT_JACKET1); 
	}

	// get/set pants
	PantsType getPantsType () const throw ()
	{
		return PantsType((m_Outlook.to_ulong() >> SLAYER_BIT_PANTS1) & 7);
	}
	void setPantsType (PantsType pantsType) throw ()
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_PANTS1);
		m_Outlook |= bitset<SLAYER_BIT_MAX>(pantsType << SLAYER_BIT_PANTS1);
	}

	// get/set weapon
	WeaponType getWeaponType () const throw ()
	{ 
		return WeaponType((m_Outlook.to_ulong() >> SLAYER_BIT_WEAPON1) & 15);
	}
	void setWeaponType (WeaponType weaponType) throw ()
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(15 << SLAYER_BIT_WEAPON1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(weaponType << SLAYER_BIT_WEAPON1);
	}

	// get/set Shield Type
	ShieldType getShieldType () const throw () 
	{ 
		return ShieldType((m_Outlook.to_ulong() >> SLAYER_BIT_SHIELD1) & 3); 
	}
	void setShieldType (ShieldType shieldType) throw ()
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_SHIELD1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(shieldType << SLAYER_BIT_SHIELD1); 
	}

	void setShapeInfo(DWORD flag, Color_t color[SLAYER_COLOR_MAX]) throw();

// get/set color
public:

	// get/set hair color
	Color_t getHairColor () const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_HAIR ]; 
	}
	void setHairColor (Color_t color) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_HAIR ] = color; 
	}

	// get/set skin color
	Color_t getSkinColor () const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_SKIN ]; 
	}
	void setSkinColor (Color_t color) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_SKIN ] = color; 
	}

	// get/set helmet color
	Color_t getHelmetColor (ColorType colorType = MAIN_COLOR) const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_HELMET + (uint)colorType ]; 
	}
	void setHelmetColor (Color_t color, ColorType colorType = MAIN_COLOR) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_HELMET + (uint)colorType ] = color; 
	}

	// get/set jacket color
	Color_t getJacketColor (ColorType colorType = MAIN_COLOR) const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_JACKET + (uint)colorType ]; 
	}
	void setJacketColor (Color_t color, ColorType colorType = MAIN_COLOR) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_JACKET + (uint)colorType ] = color; 
	}

	// get/set pants color
	Color_t getPantsColor (ColorType colorType = MAIN_COLOR) const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_PANTS + (uint)colorType ]; 
	}
	void setPantsColor (Color_t color, ColorType colorType = MAIN_COLOR) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_PANTS + (uint)colorType ] = color; 
	}

	// get/set weapon color
	Color_t getWeaponColor (ColorType colorType = MAIN_COLOR) const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_WEAPON + (uint)colorType ]; 
	}
	void setWeaponColor (Color_t color, ColorType colorType = MAIN_COLOR) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_WEAPON + (uint)colorType ] = color; 
	}

	// get/set shield color
	Color_t getShieldColor (ColorType colorType = MAIN_COLOR) const throw () 
	{ 
		return m_Colors[ SLAYER_COLOR_SHIELD + (uint)colorType ]; 
	}
	void setShieldColor (Color_t color, ColorType colorType = MAIN_COLOR) throw () 
	{ 
		m_Colors[ SLAYER_COLOR_SHIELD + (uint)colorType ] = color; 
	}

private:

	// PC name
	string m_Name;

	// PC slot
	Slot m_Slot;

	// Alignment
	Alignment_t m_Alignment;

	// *NOTE
	// ATTR_BASIC   : 순수 능력치.
	Attr_t m_STR;
	Attr_t m_DEX;
	Attr_t m_INT;

	// 능력치 올리는 현재 경험치
	// 다음 레벨로 가기 위한 목표 경험치와
	// 토탈 경험치는 Client에도 Exp Table을 가지므로
	// 클라이언트에서 연산 하도록 한다.
	Exp_t m_STRExp;
	Exp_t m_DEXExp;
	Exp_t m_INTExp;

	// 계급
	Rank_t m_Rank;

	// HP/MP
	// HP[0] = current hp, hp[1] == max hp
	HP_t m_HP[2];
	MP_t m_MP[2];

	// Fame
	Fame_t m_Fame;

	// skill domain levels
	SkillLevel_t m_DomainLevels[6];

	/*
	// Gold
	Gold_t m_Gold;


	// 최종적으로 놀던 존
	ZoneID_t m_ZoneID;
	*/

	bitset<SLAYER_BIT_MAX> m_Outlook;		// 슬레이어 외모 정보
	Color_t m_Colors[SLAYER_COLOR_MAX]; 	// 슬레이어 색깔 정보

	Level_t m_AdvancementLevel;
};

#endif
