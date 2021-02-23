//////////////////////////////////////////////////////////////////////////////
// Filename    : PCVampireInfo3.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_VAMPIRE_INFO_3_H__
#define __PC_VAMPIRE_INFO_3_H__

#include "PCInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class PCVampireInfo3;
// 뱀파이어의 외모 정보를 담고 있는 객체
// GCAddSlayer, GCAddVampireCorpse 에 담겨서 전송된다.
//////////////////////////////////////////////////////////////////////////////

class PCVampireInfo3 : public PCInfo 
{
public:
	// Vampire Color Informations
	enum VampireColors 
	{
		VAMPIRE_COLOR_BAT ,
		VAMPIRE_COLOR_SKIN ,
		VAMPIRE_COLOR_COAT1 ,
		VAMPIRE_COLOR_COAT2 ,
		VAMPIRE_COLOR_MAX
	};

public:
	PCVampireInfo3 () throw () 
	{
	}

	PCVampireInfo3 (const PCVampireInfo3 & vampireInfo) throw ()
		: m_ObjectID(vampireInfo.m_ObjectID), m_Name(vampireInfo.m_Name), 
		m_X(vampireInfo.m_X), m_Y(vampireInfo.m_Y), m_Dir(vampireInfo.m_Dir),
		m_Sex(vampireInfo.m_Sex), m_CoatType(vampireInfo.m_CoatType), 
		m_MasterEffectColor(vampireInfo.m_MasterEffectColor),
		m_CurrentHP(vampireInfo.m_CurrentHP), m_MaxHP(vampireInfo.m_MaxHP), m_AttackSpeed(vampireInfo.m_AttackSpeed),
		m_Alignment(vampireInfo.m_Alignment), m_Shape(vampireInfo.m_Shape), m_GuildID(vampireInfo.m_GuildID),
		m_Rank(vampireInfo.m_Rank), m_AdvancementLevel(vampireInfo.m_AdvancementLevel)
	{
		for (uint i = 0 ; i < VAMPIRE_COLOR_MAX ; i ++)
			m_Colors[i] = vampireInfo.m_Colors[i];

		m_Competence = vampireInfo.m_Competence;
	}
	
public:
	PCType getPCType () const throw () { return PC_VAMPIRE; }

	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	uint getSize () const throw ()
	{
		return szObjectID					// ObjectID
			+ szBYTE + m_Name.size() 		// 뱀파이어 이름
			+ szCoord + szCoord + szDir 	// 좌표와 방향				
			+ szSex							// 성별
			+ szBYTE						// coatType
			+ szColor* VAMPIRE_COLOR_MAX	// 색상
			+ szBYTE
			+ szHP* 2						// 최대 체력
			+ szAlignment					// 성향
			+ szShape						// 모양
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
			+ szBYTE						// coatType
			+ szColor* VAMPIRE_COLOR_MAX	// 색상
			+ szBYTE
			+ szHP* 2						// 최대 체력
			+ szShape						// 모양
			+ szSpeed						// 공격 속도
			+ szGuildID						// 길드 아이디
			+ szRank						// 계급
			+ szBYTE						// 권한
			+ szuint
			+ szLevel;
	}

	PCVampireInfo3 & operator = (const PCVampireInfo3 & vampireInfo) throw ()
	{
		if (&vampireInfo == this)
			return *this;

		m_ObjectID = vampireInfo.m_ObjectID;
		m_Name = vampireInfo.m_Name;
		m_X = vampireInfo.m_X;
		m_Y = vampireInfo.m_Y;
		m_Dir = vampireInfo.m_Dir;
		m_Sex = vampireInfo.m_Sex;
		m_CoatType = vampireInfo.m_CoatType;
		m_CurrentHP = vampireInfo.m_CurrentHP;
		m_MaxHP = vampireInfo.m_MaxHP;
		m_AttackSpeed = vampireInfo.m_AttackSpeed;
		m_Alignment = vampireInfo.m_Alignment;
		m_Shape = vampireInfo.m_Shape;

		for (uint i = 0 ; i < VAMPIRE_COLOR_MAX ; i ++)
			m_Colors[i] = vampireInfo.m_Colors[i];

		m_MasterEffectColor = vampireInfo.m_MasterEffectColor;
		m_Competence = vampireInfo.m_Competence;

		m_GuildID = vampireInfo.m_GuildID;
		m_UnionID = vampireInfo.m_UnionID;
		m_Rank = vampireInfo.m_Rank;
		m_AdvancementLevel = vampireInfo.m_AdvancementLevel;

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

	Color_t getBatColor () const throw () { return m_Colors[VAMPIRE_COLOR_BAT]; }
	void setBatColor (Color_t batColor) throw () { m_Colors[VAMPIRE_COLOR_BAT] = batColor; }

	Color_t getSkinColor () const throw () { return m_Colors[VAMPIRE_COLOR_SKIN]; }
	void setSkinColor (Color_t skinColor) throw () { m_Colors[VAMPIRE_COLOR_SKIN] = skinColor; }

	ItemType_t getCoatType() const throw() { return m_CoatType; }
    void setCoatType(ItemType_t CoatType) throw() { m_CoatType = CoatType; }

	Color_t getCoatColor (ColorType colorType = MAIN_COLOR) const throw () { return m_Colors[VAMPIRE_COLOR_COAT1 + (int)colorType]; }
	void setCoatColor (Color_t coatColor, ColorType colorType = MAIN_COLOR) throw () { m_Colors[VAMPIRE_COLOR_COAT1 + (int)colorType] = coatColor; }

	BYTE getMasterEffectColor() const { return m_MasterEffectColor; }
	void setMasterEffectColor( BYTE color ) { m_MasterEffectColor = color; }

	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

	HP_t getMaxHP() const throw() { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) throw() { m_MaxHP = MaxHP; }

	Speed_t getAttackSpeed() const throw() { return m_AttackSpeed; }
	void setAttackSpeed(Speed_t AttackSpeed) throw() { m_AttackSpeed = AttackSpeed; }

	Alignment_t getAlignment() const throw() { return m_Alignment; }
	void setAlignment(Alignment_t Alignment)  throw() { m_Alignment = Alignment; }

	Shape_t getShape() const throw() { return m_Shape; }
	void setShape(Shape_t Shape)  throw() { m_Shape = Shape; }

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
	ItemType_t m_CoatType;

	// colors
	Color_t m_Colors[VAMPIRE_COLOR_MAX];

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

	// 뱀파이어 모양
	Shape_t m_Shape;

	// 권한
	BYTE m_Competence; 

	// 길드 아이디
	GuildID_t m_GuildID;

	uint	m_UnionID;

	// 계급
	Rank_t		m_Rank;

	Level_t		m_AdvancementLevel;
};

#endif
