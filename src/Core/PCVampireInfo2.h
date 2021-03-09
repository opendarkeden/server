//////////////////////////////////////////////////////////////////////////////
// Filename    : PCVampireInfo2.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_VAMPIRE_INFO_2_H__
#define __PC_VAMPIRE_INFO_2_H__

#include "PCInfo.h"

//////////////////////////////////////////////////////////////////////////////
// Vampire 정보를 담고 있는 객체.
// GCPCList 패킷에 담겨서 클라이언트에게 전송된다.
// 아이템이나 걸려있는 마법 같은 정보는 담겨있지 않다.
//////////////////////////////////////////////////////////////////////////////

class PCVampireInfo2 : public PCInfo 
{
public:
	PCType getPCType () const  { return PC_VAMPIRE; }

	void read (SocketInputStream & iStream) ;
	void write (SocketOutputStream & oStream) const ;

	uint getSize () const 
	{
		return szObjectID				// ObjectID
			+ szBYTE + m_Name.size() 	// 뱀파이어 이름
			+ szLevel					// 레벨
			+ szSex						// 성별
			+ szColor* 2				// 색상
			+ szBYTE
			+ szAlignment				// 성향
			+ szAttr * 3 * 3			// 능력치
			+ szHP* 2					// HP
			+ szRank + szRankExp		// 계급 경험치
			+ szExp						// 경험치
			+ szFame					// Fame
			+ szGold 					// 돈
			+ szSight					// 시야
			+ szSkillType* 8			// 핫 키
			+ szSilver					// 핫 키
			+ szBonus					// 보너스포인트
			+ szGuildID					// 길드 아이디
			+ szBYTE + m_GuildName.size()	// 길드 이름
			+ szGuildMemberRank			// guild member rank
			+ szBYTE					// 권한
			+ szuint
			+ szLevel
			+ szExp;
	}

	static uint getMaxSize () 
	{
		return szObjectID				// ObjectID
			+ szBYTE + 20				// 뱀파이어 이름
			+ szLevel					// 레벨
			+ szSex						// 성별
			+ szColor* 2				// 색상
			+ szBYTE
			+ szAlignment				// 성향
			+ szAttr * 3 * 3			// 능력치
			+ szHP* 2					// HP
			+ szRank + szRankExp		// 계급 경험치
			+ szExp						// 경험치
			+ szFame					// Fame
			+ szGold					// 돈
			+ szSight					// 시야
			+ szSkillType* 8			// 핫 키
			+ szSilver					// 핫 키
			+ szBonus					// 보너스포인트
			+ szGuildID					// 길드 아이디
			+ szBYTE + 30				// 길드 이름
			+ szGuildMemberRank +		// guild member rank
			+ szBYTE					// 권한
			+ szuint
			+ szLevel
			+ szExp;
	}

	string toString () const ;

public:
	ObjectID_t getObjectID () const  { return m_ObjectID; }
	void setObjectID (ObjectID_t objectID)  { m_ObjectID = objectID; }

    string getName () const  { return m_Name; }
    void setName (string name)  { m_Name = (name.size() > 20) ? name.substr(0,20) : name; }

    Level_t getLevel () const  { return m_Level; }
    void setLevel (Level_t Level)  { m_Level = Level; }

	Sex getSex () const  { return m_Sex; }
	void setSex (Sex sex)  { m_Sex = sex; }
	void setSex (string sex)
	{
		if (sex == Sex2String[MALE]) 
			m_Sex = MALE;
		else if (sex == Sex2String[FEMALE]) 
			m_Sex = FEMALE;
		else
			throw InvalidProtocolException("invalid sex value");
	}

	Fame_t getFame () const  { return m_Fame; }
	void setFame (Fame_t f)  { m_Fame = f; }
	
	Color_t getBatColor () const  { return m_BatColor; }
	void setBatColor (Color_t batColor)  { m_BatColor = batColor; }

	Color_t getSkinColor () const  { return m_SkinColor; }
	void setSkinColor (Color_t skinColor)  { m_SkinColor = skinColor; }

	BYTE getMasterEffectColor () const  { return m_MasterEffectColor; }
	void setMasterEffectColor (BYTE color)  { m_MasterEffectColor = color; }

	Alignment_t getAlignment() const  { return m_Alignment; }
	void setAlignment(Alignment_t Alignment)  { m_Alignment = Alignment; }

	Attr_t getSTR (AttrType attrType = ATTR_CURRENT) const 
	{
		if (m_STR[attrType] > maxVampireAttr) throw Error("STR out of range"); 
		return m_STR[attrType]; 
	}
	void setSTR (Attr_t str, AttrType attrType = ATTR_CURRENT) 
	{ 
		if (str > maxVampireAttr) throw Error("STR out of range"); 
		m_STR[attrType] = str; 
	}
	
	Attr_t getDEX (AttrType attrType = ATTR_CURRENT) const 
	{ 
		if (m_DEX[attrType] > maxVampireAttr) throw Error("DEX out of range"); 
		return m_DEX[attrType]; 
	}
	void setDEX (Attr_t dex, AttrType attrType = ATTR_CURRENT) 
	{ 
		if (dex > maxVampireAttr) throw Error("DEX out of range"); 
		m_DEX[attrType] = dex; 
	}
	
	Attr_t getINT (AttrType attrType = ATTR_CURRENT) const 
	{ 
		if (m_INT[attrType] > maxVampireAttr) throw Error("INT out of range"); 
		return m_INT[attrType]; 
	}
	void setINT (Attr_t inte, AttrType attrType = ATTR_CURRENT) 
	{
		if (inte > maxVampireAttr) throw Error("INT out of range"); 
		m_INT[attrType] = inte; 
	}

	HP_t getHP (AttrType attrType = ATTR_CURRENT) const  { return m_HP[attrType]; }
	void setHP (HP_t hp, AttrType attrType = ATTR_CURRENT)  { m_HP[attrType] = hp; }
	void setHP (HP_t curHP, HP_t maxHP)  { m_HP[ATTR_CURRENT] = curHP; m_HP[ATTR_MAX] = maxHP; }

	Rank_t getRank () const  { return m_Rank; }
	void setRank (Rank_t rank)  { m_Rank = rank; }

	RankExp_t getRankExp () const  { return m_RankExp; }
	void setRankExp (RankExp_t rankExp)  { m_RankExp = rankExp; }

	Exp_t getExp () const  { return m_Exp; }
	void setExp (Exp_t exp)  { m_Exp = exp; }

	Gold_t getGold () const  { return m_Gold; }
	void setGold (Gold_t gold)  { m_Gold = gold; }

	Sight_t getSight () const  { return m_Sight; }
	void setSight (Sight_t sight)  { m_Sight = sight; }

	Bonus_t getBonus() const  { return m_Bonus; }
	void setBonus(Bonus_t Bonus)  { m_Bonus = Bonus; }

	SkillType_t getHotKey(BYTE pos) const  { return m_HotKey[pos]; }
	void setHotKey(BYTE pos, SkillType_t SkillType)  { m_HotKey[pos] = SkillType; }

	Silver_t getSilverDamage() const  { return m_SilverDamage; }
	void setSilverDamage(Silver_t SilverDamage )  { m_SilverDamage = SilverDamage; }

	BYTE getCompetence(void) const { return m_Competence; }
	void setCompetence(BYTE competence) { m_Competence = competence; }

	GuildID_t getGuildID(void) const { return m_GuildID; }
	void setGuildID(GuildID_t GuildID) { m_GuildID = GuildID; }

	string getGuildName() const { return m_GuildName; }
	void setGuildName( string guildName ) { m_GuildName = guildName; }

	GuildMemberRank_t getGuildMemberRank() const { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t guildMemberRank ) { m_GuildMemberRank = guildMemberRank; }

	uint getUnionID(void) const { return m_UnionID; }
	void setUnionID(uint UnionID) { m_UnionID = UnionID; }

	Level_t	getAdvancementLevel() const { return m_AdvancementLevel; }
	void setAdvancementLevel( Level_t level ) { m_AdvancementLevel = level; }

	Exp_t	getAdvancementGoalExp() const { return m_AdvancementGoalExp; }
	void setAdvancementGoalExp( Exp_t exp ) { m_AdvancementGoalExp = exp; }
private:

	// PC's object id
	ObjectID_t m_ObjectID;

	// PC name
	string m_Name;

	// PC name
	Level_t m_Level;

	// PC sex
	Sex m_Sex;

	// bat color, skin color,
	Color_t m_BatColor;
	Color_t m_SkinColor;
	BYTE m_MasterEffectColor;

	// Alignment
	Alignment_t m_Alignment;

    // Attributes
	Attr_t m_STR[3];
	Attr_t m_DEX[3];
	Attr_t m_INT[3];

	// HP
	// HP[0] = current hp, hp[1] == max hp
	HP_t m_HP[2];

	// 계급
	Rank_t			m_Rank;
	RankExp_t		m_RankExp;

	// Exp
	Exp_t m_Exp;

	// Fame
	Fame_t m_Fame;

	// Gold
	Gold_t m_Gold;

	// 시야
	Sight_t m_Sight;

	// 보너스 포인트
	Bonus_t m_Bonus;

	// 핫 키
	SkillType_t m_HotKey[8];

	// 실버 데미지
	Silver_t m_SilverDamage;

	// Competence
	BYTE m_Competence;

	GuildID_t m_GuildID;

	// guild name
	string m_GuildName;

	// guild member rank
	GuildMemberRank_t m_GuildMemberRank;

	uint m_UnionID;

	Level_t m_AdvancementLevel;
	Exp_t m_AdvancementGoalExp;
};

#endif
