//////////////////////////////////////////////////////////////////////////////
// Filename    : PCSlayerInfo3.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_SLAYER_INFO3_H__
#define __PC_SLAYER_INFO3_H__

#include "PCInfo.h"
#include "Assert.h"
#include <bitset>

//////////////////////////////////////////////////////////////////////////////
// 슬레이어의 정보는 다음과 같다. 
//
//(1) OID 
//(2) Name 
//(3) X,Y,Dir 
//
// bit_set 으로 표현되는 정보들
//
//(4) Sex - MALE | FEMALE 
//(5) HairStyle - HAIR_STYLE1 | HAIR_STYLE2 | HAIR_STYLE3 
//(8) Helmet Type - NONE | HELMET1 | HELMET2
//(9) Jacket Type - BASIC | JACKET1 | JACKET2 
//(10) Pants Type - BASIC | PANTS1 | PANTS2 
//(11) Weapon Type - NONE | SWORD | BLADE | SHIELD | SWORD + SHIELD | AR | TR | SG | SMG | CROSS 
//(12) Motorcycle Type - NONE | MOTORCYCLE1 
//
// 상의/하의를 제외하면 모두 한 부분의 색상만이 바뀐다.
//
//(13) HairColor 
//(14) SkinColor 
//(15) Helmet Color 
//(16) Jacket Color[2] 
//(17) Pants Color[2] 
//(18) Weapon Color 
//(19) Shield Color 
//(20) Motorcycle Color 
//////////////////////////////////////////////////////////////////////////////

class PCSlayerInfo3 : public PCInfo 
{
public:

	// Slayer Outlook Information
    enum SlayerBits {
        SLAYER_BIT_SEX ,
		SLAYER_BIT_HAIRSTYLE1 ,
		SLAYER_BIT_HAIRSTYLE2 ,
		SLAYER_BIT_HELMET1,
		SLAYER_BIT_HELMET2,
		SLAYER_BIT_HELMET3,//by viva
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
		SLAYER_BIT_WEAPON5,	//by viva
		SLAYER_BIT_MOTORCYCLE1,
		SLAYER_BIT_MOTORCYCLE2,
		SLAYER_BIT_SHIELD1,
		SLAYER_BIT_SHIELD2,
		SLAYER_BIT_SHIELD3,//by viva
		SLAYER_BIT_SHOULDER1,
		SLAYER_BIT_SHOULDER2,
		SLAYER_BIT_MAX
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
		SLAYER_COLOR_MOTORCYCLE ,
		SLAYER_COLOR_SHOULDER ,
		SLAYER_COLOR_MAX
	};


public:
	PCSlayerInfo3 () 
	{
		m_Outlook.reset();
	}

	PCSlayerInfo3 (const PCSlayerInfo3 & slayerInfo) 
		: m_ObjectID(slayerInfo.m_ObjectID), m_Name(slayerInfo.m_Name), 
		m_X(slayerInfo.m_X), m_Y(slayerInfo.m_Y), m_Dir(slayerInfo.m_Dir), 
		m_Outlook(slayerInfo.m_Outlook), m_MasterEffectColor(slayerInfo.m_MasterEffectColor),
		m_CurrentHP(slayerInfo.m_CurrentHP), m_MaxHP(slayerInfo.m_MaxHP), m_AttackSpeed(slayerInfo.m_AttackSpeed),
		m_Alignment(slayerInfo.m_Alignment), m_GuildID(slayerInfo.m_GuildID), m_Rank(slayerInfo.m_Rank), m_AdvancementLevel(slayerInfo.m_AdvancementLevel)
	{
		for (uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++)
			m_Colors[i] = slayerInfo.m_Colors[i]; 	// 슬레이어 색깔 정보

		m_Competence = slayerInfo.m_Competence;
	}


public:
	PCType getPCType () const  { return PC_SLAYER; }
	
    void read (SocketInputStream & iStream) ;
    void write (SocketOutputStream & oStream) const ;

	uint getSize () const  
	{ 
		return szObjectID 					// 크리처 아이디
			+ szBYTE + m_Name.size() 		// 이름
			+ szCoord + szCoord + szDir 	// 좌표와 방향
			+ szDWORD						// 슬레이어 플래그
			+ szColor* SLAYER_COLOR_MAX 	// 색깔 정보
			+ szBYTE
			+ szHP* 2						// 최대 체력
			+ szAlignment					// 성향
			+ szRank						// 계급
			+ szSpeed 						// 공격 스피드
			+ szGuildID						// 공격 스피드
			+ szBYTE						// 권한
			+ szuint
			+ szLevel;
	}

	static uint getMaxSize () 
	{
		return szObjectID 					// 크리처 아이디
			+ szBYTE + 20					// 이름
			+ szCoord + szCoord + szDir 	// 좌표와 방향
			+ szDWORD						// 슬레이어 플래그
			+ szColor* SLAYER_COLOR_MAX 	// 색깔 정보
			+ szBYTE
			+ szHP* 2						// 최대 체력
			+ szAlignment					// 성향
			+ szRank						// 계급
			+ szSpeed						// 공격 스피드
			+ szGuildID						// 공격 스피드
			+ szBYTE						// 권한
			+ szuint
			+ szLevel;
	}

	PCSlayerInfo3 &operator = (const PCSlayerInfo3 & slayerInfo) 
	{    
		if (&slayerInfo == this)
			return *this;
		m_ObjectID = slayerInfo.m_ObjectID;
		m_Name = slayerInfo.m_Name;
		m_X = slayerInfo.m_X;
		m_Y = slayerInfo.m_Y;
		m_Dir = slayerInfo.m_Dir;
		m_Outlook = slayerInfo.m_Outlook;
		m_CurrentHP = slayerInfo.m_CurrentHP;
		m_MaxHP = slayerInfo.m_MaxHP;
		m_AttackSpeed = slayerInfo.m_AttackSpeed;
		m_Alignment = slayerInfo.m_Alignment;

		for (uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++)
			m_Colors[i] = slayerInfo.m_Colors[i]; 	// 슬레이어 색깔 정보

		m_MasterEffectColor = slayerInfo.m_MasterEffectColor;

		m_Competence = slayerInfo.m_Competence;
		m_GuildID	 = slayerInfo.m_GuildID;
		m_UnionID	= slayerInfo.m_UnionID;

		m_Rank	 = slayerInfo.m_Rank;
		m_AdvancementLevel = slayerInfo.m_AdvancementLevel;

		return *this;
	}

	string toString () const ;

public:
	ObjectID_t getObjectID () const  { return m_ObjectID; }
	void setObjectID (ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	string getName () const  { Assert(m_Name != ""); return m_Name; }
	void setName (const string & name)  { m_Name = name; Assert(m_Name != ""); }

	Coord_t getX () const  { return m_X; }
	void setX (Coord_t x)  { m_X = x; }
	
	Coord_t getY () const  { return m_Y; }
	void setY (Coord_t y)  { m_Y = y; }

	Dir_t getDir () const  { return m_Dir; }
	void setDir (Dir_t dir)  { m_Dir = dir; }

public:
    Sex getSex () const  
	{ 
		return m_Outlook.test(SLAYER_BIT_SEX)?MALE:FEMALE; 
	}
    void setSex (Sex sex)  
	{ 
		m_Outlook.set(SLAYER_BIT_SEX,(sex==MALE?true:false)); 
	}

	HairStyle getHairStyle () const  
	{ 
		return HairStyle((m_Outlook.to_ulong() >> SLAYER_BIT_HAIRSTYLE1) & 3); 
	}
	void setHairStyle (HairStyle hairStyle)  
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(hairStyle << SLAYER_BIT_HAIRSTYLE1); 
	}

	HelmetType getHelmetType () const  
	{ 
		return HelmetType((m_Outlook.to_ulong() >> SLAYER_BIT_HELMET1) & 7); 
	}
	void setHelmetType (HelmetType helmetType) 
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_HELMET1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(helmetType << SLAYER_BIT_HELMET1); 
	}

	JacketType getJacketType () const  
	{ 
		return JacketType((m_Outlook.to_ulong() >> SLAYER_BIT_JACKET1) & 7); 
	}
	void setJacketType (JacketType jacketType) 
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_JACKET1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(jacketType << SLAYER_BIT_JACKET1); 
	}

	PantsType getPantsType () const  
	{ 
		return PantsType((m_Outlook.to_ulong() >> SLAYER_BIT_PANTS1) & 7); 
	}
	void setPantsType (PantsType pantsType) 
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_PANTS1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(pantsType << SLAYER_BIT_PANTS1); 
	}

	WeaponType getWeaponType () const 
	{ 
		return WeaponType((m_Outlook.to_ulong() >> SLAYER_BIT_WEAPON1) & 31); 
	}
	void setWeaponType (WeaponType weaponType) 
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(31 << SLAYER_BIT_WEAPON1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(weaponType << SLAYER_BIT_WEAPON1); 
	}

	ShieldType getShieldType () const 
	{
		return ShieldType((m_Outlook.to_ulong() >> SLAYER_BIT_SHIELD1) & 7);
	}
	void setShieldType (ShieldType shieldType) 
	{
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_SHIELD1);
		m_Outlook |= bitset<SLAYER_BIT_MAX>(shieldType << SLAYER_BIT_SHIELD1);
	}

	MotorcycleType getMotorcycleType () const 
	{ 
		return MotorcycleType((m_Outlook.to_ulong() >> SLAYER_BIT_MOTORCYCLE1) & 3); 
	}
	void setMotorcycleType (MotorcycleType motorcycleType) 
	{ 
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_MOTORCYCLE1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(motorcycleType << SLAYER_BIT_MOTORCYCLE1); 
	}

	BYTE getShoulderType () const 
	{
		return BYTE((m_Outlook.to_ulong() >> SLAYER_BIT_SHOULDER1) & 3); 
	}
	void setShoulderType (BYTE shoulder) 
	{
		m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_SHOULDER1); 
		m_Outlook |= bitset<SLAYER_BIT_MAX>(shoulder << SLAYER_BIT_SHOULDER1); 
	}

public:
	Color_t getHairColor () const  
	{ 
		return m_Colors[ SLAYER_COLOR_HAIR ]; 
	}
	void setHairColor (Color_t color)  
	{ 
		m_Colors[ SLAYER_COLOR_HAIR ] = color; 
	}

	Color_t getSkinColor () const  
	{ 
		return m_Colors[ SLAYER_COLOR_SKIN ]; 
	}
	void setSkinColor (Color_t color)  
	{ 
		m_Colors[ SLAYER_COLOR_SKIN ] = color; 
	}

	Color_t getHelmetColor (ColorType colorType = MAIN_COLOR) const  
	{ 
		return m_Colors[ SLAYER_COLOR_HELMET + (uint)colorType ]; 
	}
	void setHelmetColor (Color_t color, ColorType colorType = MAIN_COLOR)  
	{ 
		m_Colors[ SLAYER_COLOR_HELMET + (uint)colorType ] = color; 
	}

	Color_t getJacketColor (ColorType colorType = MAIN_COLOR) const  
	{ 
		return m_Colors[ SLAYER_COLOR_JACKET + (uint)colorType ]; 
	}
	void setJacketColor (Color_t color, ColorType colorType = MAIN_COLOR)  
	{ 
		m_Colors[ SLAYER_COLOR_JACKET + (uint)colorType ] = color; 
	}

	Color_t getPantsColor (ColorType colorType = MAIN_COLOR) const  
	{ 
		return m_Colors[ SLAYER_COLOR_PANTS + (uint)colorType ]; 
	}
	void setPantsColor (Color_t color, ColorType colorType = MAIN_COLOR)  
	{ 
		m_Colors[ SLAYER_COLOR_PANTS + (uint)colorType ] = color; 
	}

	Color_t getWeaponColor (ColorType colorType = MAIN_COLOR) const  
	{ 
		return m_Colors[ SLAYER_COLOR_WEAPON + (uint)colorType ]; 
	}
	void setWeaponColor (Color_t color, ColorType colorType = MAIN_COLOR)  
	{ 
		m_Colors[ SLAYER_COLOR_WEAPON + (uint)colorType ] = color; 
	}

	Color_t getShieldColor (ColorType colorType = MAIN_COLOR) const  
	{ 
		return m_Colors[ SLAYER_COLOR_SHIELD + (uint)colorType ]; 
	}
	void setShieldColor (Color_t color, ColorType colorType = MAIN_COLOR)  
	{ 
		m_Colors[ SLAYER_COLOR_SHIELD + (uint)colorType ] = color; 
	}

	Color_t getMotorcycleColor (ColorType colorType = MAIN_COLOR) const  
	{ 
		return m_Colors[ SLAYER_COLOR_MOTORCYCLE + (uint)colorType ]; 
	}
	void setMotorcycleColor (Color_t color, ColorType colorType = MAIN_COLOR)  
	{ 
		m_Colors[ SLAYER_COLOR_MOTORCYCLE + (uint)colorType ] = color; 
	}

	Color_t getShoulderColor () const  
	{ 
		return m_Colors[ SLAYER_COLOR_SHOULDER ]; 
	}
	void setShoulderColor (Color_t color)  
	{ 
		m_Colors[ SLAYER_COLOR_SHOULDER ] = color; 
	}

	BYTE getMasterEffectColor() const { return m_MasterEffectColor; }
	void setMasterEffectColor( BYTE color ) { m_MasterEffectColor = color; }

	HP_t getCurrentHP() const  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP)  { m_CurrentHP = CurrentHP; }

	HP_t getMaxHP() const  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP)  { m_MaxHP = MaxHP; }

	Speed_t getAttackSpeed() const  { return m_AttackSpeed; }
	void setAttackSpeed(Speed_t AttackSpeed)  { m_AttackSpeed = AttackSpeed; }

	Alignment_t getAlignment() const  { return m_Alignment; }
	void setAlignment(Alignment_t Alignment)  { m_Alignment = Alignment; }

	BYTE getCompetence(void) const { return m_Competence; }
	void setCompetence(BYTE competence) { m_Competence = competence; }

	GuildID_t getGuildID(void) const { return m_GuildID; }
	void setGuildID(GuildID_t GuildID ) { m_GuildID = GuildID; }

	uint getUnionID(void) const { return m_UnionID; }
	void setUnionID(uint UnionID ) { m_UnionID = UnionID; }

	Rank_t getRank () const  { return m_Rank; }
	void setRank (Rank_t rank)  { m_Rank = rank; }

	Level_t	getAdvancementLevel() const { return m_AdvancementLevel; }
	void setAdvancementLevel( Level_t level ) { m_AdvancementLevel = level; }

private:
	ObjectID_t				m_ObjectID;					// OID
	string					m_Name; 					// PC의 이름
	Coord_t					m_X;						// X 좌표
	Coord_t					m_Y;						// Y 좌표
	Dir_t					m_Dir;						// 방향
	bitset<SLAYER_BIT_MAX>	m_Outlook;					// 슬레이어외모정보
	Color_t					m_Colors[SLAYER_COLOR_MAX];	// 슬레이어색깔정보
	BYTE					m_MasterEffectColor;		// 마스터 이펙트 색깔
	HP_t					m_CurrentHP;				// 슬레이어현재체력
	HP_t					m_MaxHP;					// 슬레이어최대체력
	Speed_t					m_AttackSpeed;				// 공격속도
	Alignment_t				m_Alignment;				// 성향
	BYTE					m_Competence;				// 권한
	GuildID_t				m_GuildID;					// 길드 아이디
	uint					m_UnionID;
	Rank_t					m_Rank;						// 계급
	Level_t					m_AdvancementLevel;
};

#endif
