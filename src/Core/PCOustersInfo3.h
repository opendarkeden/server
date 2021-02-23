//////////////////////////////////////////////////////////////////////////////
// Filename    : PCOustersInfo3.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_OUSTERS_INFO_3_H__
#define __PC_OUSTERS_INFO_3_H__

#include "PCInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class PCOustersInfo3;
// 뱀파이어의 외모 정보를 담고 있는 객체
// GCAddOusters, GCAddOustersCorpse 에 담겨서 전송된다.
//////////////////////////////////////////////////////////////////////////////

class PCOustersInfo3 : public PCInfo 
{
public:
	// Ousters Color Informations
	enum OustersColors 
	{
		OUSTERS_COLOR_COAT,
		OUSTERS_COLOR_HAIR,
		OUSTERS_COLOR_ARM,
		OUSTERS_COLOR_BOOTS,
		OUSTERS_COLOR_MAX
	};

public:
	PCOustersInfo3 () throw () 
	{
	}

	PCOustersInfo3 (const PCOustersInfo3 & oustersInfo) throw ()
		: m_ObjectID(oustersInfo.m_ObjectID), m_Name(oustersInfo.m_Name), 
		m_X(oustersInfo.m_X), m_Y(oustersInfo.m_Y), m_Dir(oustersInfo.m_Dir),
		m_Sex(oustersInfo.m_Sex), m_CoatType(oustersInfo.m_CoatType), m_ArmType(oustersInfo.m_ArmType), m_SylphType(oustersInfo.m_SylphType),
		m_MasterEffectColor(oustersInfo.m_MasterEffectColor),
		m_CurrentHP(oustersInfo.m_CurrentHP), m_MaxHP(oustersInfo.m_MaxHP), m_AttackSpeed(oustersInfo.m_AttackSpeed),
		m_Alignment(oustersInfo.m_Alignment), m_GuildID(oustersInfo.m_GuildID),
		m_Rank(oustersInfo.m_Rank), m_AdvancementLevel(oustersInfo.m_AdvancementLevel)
	{
		for (uint i = 0 ; i < OUSTERS_COLOR_MAX ; i ++)
			m_Colors[i] = oustersInfo.m_Colors[i];

		m_Competence = oustersInfo.m_Competence;
	}
	
public:
	PCType getPCType () const throw () { return PC_OUSTERS; }

	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	uint getSize () const throw ()
	{
		return szObjectID					// ObjectID
			+ szBYTE + m_Name.size() 		// 뱀파이어 이름
			+ szCoord + szCoord + szDir 	// 좌표와 방향				
			+ szSex							// 성별
			+ szBYTE						// shape
			+ szColor* OUSTERS_COLOR_MAX	// 색상
			+ szBYTE
			+ szHP* 2						// 최대 체력
			+ szAlignment					// 성향
			+ szSpeed						// 공격 속도
			+ szGuildID						// 길드 아이디
			+ szRank						// 계급
			+ szBYTE						// 권한
			+ szuint
			+ szLevel;
	}

	// get max size of object
	static uint getMaxSize () throw ()
	{
		return szObjectID					// ObjectID
			+ szBYTE + 20 					// 뱀파이어 이름
			+ szCoord + szCoord + szDir 	// 좌표와 방향				
			+ szSex							// 성별
			+ szBYTE						// shape
			+ szColor* OUSTERS_COLOR_MAX	// 색상
			+ szBYTE
			+ szHP* 2						// 최대 체력
			+ szSpeed						// 공격 속도
			+ szGuildID						// 길드 아이디
			+ szRank						// 계급
			+ szBYTE						// 권한
			+ szuint
			+ szLevel;
	}

	PCOustersInfo3 & operator = (const PCOustersInfo3 & oustersInfo) throw ()
	{
		if (&oustersInfo == this)
			return *this;

		m_ObjectID = oustersInfo.m_ObjectID;
		m_Name = oustersInfo.m_Name;
		m_X = oustersInfo.m_X;
		m_Y = oustersInfo.m_Y;
		m_Dir = oustersInfo.m_Dir;
		m_Sex = oustersInfo.m_Sex;
		m_CoatType = oustersInfo.m_CoatType;
		m_ArmType = oustersInfo.m_ArmType;
		m_SylphType = oustersInfo.m_SylphType;
		m_CurrentHP = oustersInfo.m_CurrentHP;
		m_MaxHP = oustersInfo.m_MaxHP;
		m_AttackSpeed = oustersInfo.m_AttackSpeed;
		m_Alignment = oustersInfo.m_Alignment;

		for (uint i = 0 ; i < OUSTERS_COLOR_MAX ; i ++)
			m_Colors[i] = oustersInfo.m_Colors[i];

		m_MasterEffectColor = oustersInfo.m_MasterEffectColor;

		m_Competence = oustersInfo.m_Competence;

		m_GuildID = oustersInfo.m_GuildID;
		m_UnionID = oustersInfo.m_UnionID;
		m_Rank = oustersInfo.m_Rank;
		m_AdvancementLevel = oustersInfo.m_AdvancementLevel;

		return *this;
	}

	string toString () const throw ();

public:
	ObjectID_t getObjectID () const throw () { return m_ObjectID; }
	void setObjectID (ObjectID_t objectID) throw () { m_ObjectID = objectID; }

    string getName () const throw () { return m_Name; }
    void setName (const string & name) throw (Error) { m_Name = name; Assert(m_Name != ""); }

	Coord_t getX () const throw () { return m_X; }
	void setX (Coord_t x) throw () { m_X = x; }

	Coord_t getY () const throw () { return m_Y; }
	void setY (Coord_t y) throw () { m_Y = y; }

	Dir_t getDir () const throw () { return m_Dir; }
	void setDir (Dir_t dir) throw () { m_Dir = dir; }

	Sex getSex () const throw () { return m_Sex; }
	void setSex (Sex sex) throw () { m_Sex = sex; }
	void setSex (const string & sex) throw (InvalidProtocolException)
	{
		if (sex == Sex2String[MALE]) 
			m_Sex = MALE;
		else if (sex == Sex2String[FEMALE]) 
			m_Sex = FEMALE;
		else
			throw InvalidProtocolException("invalid sex value");
	}

	Color_t getCoatColor () const throw () { return m_Colors[OUSTERS_COLOR_COAT]; }
	void setCoatColor (Color_t coatColor) throw () { m_Colors[OUSTERS_COLOR_COAT] = coatColor; }

	Color_t getHairColor () const throw () { return m_Colors[OUSTERS_COLOR_HAIR]; }
	void setHairColor (Color_t hairColor) throw () { m_Colors[OUSTERS_COLOR_HAIR] = hairColor; }

	Color_t getArmColor () const throw () { return m_Colors[OUSTERS_COLOR_ARM]; }
	void setArmColor (Color_t armColor) throw () { m_Colors[OUSTERS_COLOR_ARM] = armColor; }

	Color_t getBootsColor () const throw () { return m_Colors[OUSTERS_COLOR_BOOTS]; }
	void setBootsColor (Color_t bootsColor) throw () { m_Colors[OUSTERS_COLOR_BOOTS] = bootsColor; }

	BYTE getMasterEffectColor() const { return m_MasterEffectColor; }
	void setMasterEffectColor( BYTE color ) { m_MasterEffectColor = color; }

	OustersCoatType getCoatType() const throw() { return m_CoatType; }
    void setCoatType(OustersCoatType CoatType) throw() { m_CoatType = CoatType; }

	OustersArmType getArmType() const throw() { return m_ArmType; }
    void setArmType(OustersArmType ArmType) throw() { m_ArmType = ArmType; }

	OustersSylphType getSylphType() const throw() { return m_SylphType; }
    void setSylphType(OustersSylphType SylphType) throw() { m_SylphType = SylphType; }

	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

	HP_t getMaxHP() const throw() { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) throw() { m_MaxHP = MaxHP; }

	Speed_t getAttackSpeed() const throw() { return m_AttackSpeed; }
	void setAttackSpeed(Speed_t AttackSpeed) throw() { m_AttackSpeed = AttackSpeed; }

	Alignment_t getAlignment() const throw() { return m_Alignment; }
	void setAlignment(Alignment_t Alignment)  throw() { m_Alignment = Alignment; }

	BYTE getCompetence(void) const { return m_Competence; }
	void setCompetence(BYTE competence) { m_Competence = competence; }

	GuildID_t getGuildID(void) const { return m_GuildID; }
	void setGuildID(GuildID_t GuildID ) { m_GuildID = GuildID; }

	uint getUnionID(void) const { return m_UnionID; }
	void setUnionID(uint UnionID ) { m_UnionID = UnionID; }

	Rank_t getRank () const throw () { return m_Rank; }
	void setRank (Rank_t rank) throw () { m_Rank = rank; }

	Level_t	getAdvancementLevel() const { return m_AdvancementLevel; }
	void setAdvancementLevel( Level_t level ) { m_AdvancementLevel = level; }

private :

	// PC's object id
	ObjectID_t m_ObjectID;

	// PC name
	string m_Name;

	Coord_t m_X;
	Coord_t m_Y;
	Dir_t m_Dir;

	// PC sex
	Sex m_Sex;

	// CoatType
	OustersCoatType m_CoatType;

	// ArmType
	OustersArmType m_ArmType;

	// SylphType
	OustersSylphType m_SylphType;

	// colors
	Color_t m_Colors[OUSTERS_COLOR_MAX];

	// 마스터 이펙트 색깔
	BYTE m_MasterEffectColor;

	// Current HP
	HP_t m_CurrentHP;

	// Max HP
	HP_t m_MaxHP;

	// Attack Speed
	Speed_t m_AttackSpeed;

	// 성향
	Alignment_t m_Alignment;

	// 권한
	BYTE m_Competence; 

	// 길드 아이디
	GuildID_t m_GuildID;

	uint m_UnionID;

	// 계급
	Rank_t		m_Rank;

	Level_t		m_AdvancementLevel;

};

#endif
