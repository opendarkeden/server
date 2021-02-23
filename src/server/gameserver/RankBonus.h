//////////////////////////////////////////////////////////////////////////////
// Filename    : RankBonus.h
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __RANK_BONUS_H__
#define __RANK_BONUS_H__

#include "Types.h"


class RankBonus
{
public:
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	enum RankBonusType
	{
		RANK_BONUS_DEADLY_SPEAR,			// 0
		RANK_BONUS_BEHEMOTH_ARMOR,			// 1
		RANK_BONUS_DRAGON_EYE,			// 2
		RANK_BONUS_IMMORTAL_HEART,			// 3
		RANK_BONUS_RELIANCE_BRAIN,			// 4
		RANK_BONUS_SLAYING_KNIFE,			// 5
		RANK_BONUS_HAWK_WING,			// 6
		RANK_BONUS_HOLY_SMASHING,			// 7
		RANK_BONUS_SOUL_SMASHING,			// 8
		RANK_BONUS_SAPPHIRE_BLESS,			// 9
		RANK_BONUS_RUBY_BLESS,			// 10
		RANK_BONUS_DIAMOND_BLESS,			// 11
		RANK_BONUS_EMERALD_BLESS,			// 12
		RANK_BONUS_MAGIC_BRAIN,			// 13
		RANK_BONUS_WIGHT_HAND,			// 14
		RANK_BONUS_SEIREN_HAND,			// 15
		RANK_BONUS_FORTUNE_HAND,			// 16

		RANK_BONUS_IMMORTAL_BLOOD,		// 17
		RANK_BONUS_BEHEMOTH_SKIN,			// 18
		RANK_BONUS_SAFE_ROBE,			// 19
		RANK_BONUS_CROW_WING,			// 20
		RANK_BONUS_WISDOM_OF_BLOOD,			// 21
		RANK_BONUS_TIGER_NAIL,			// 22
		RANK_BONUS_URANUS_BLESS,			// 23
		RANK_BONUS_DISRUPTION_STORM,			// 24
		RANK_BONUS_WIDE_STORM,			// 25
		RANK_BONUS_KNOWLEDGE_OF_POISON,			// 26
		RANK_BONUS_KNOWLEDGE_OF_ACID,			// 27
		RANK_BONUS_KNOWLEDGE_OF_CURSE,			// 28
		RANK_BONUS_KNOWLEDGE_OF_BLOOD,			// 29
		RANK_BONUS_KNOWLEDGE_OF_INNATE,			// 30
		RANK_BONUS_KNOWLEDGE_OF_SUMMON,			// 31
		RANK_BONUS_WISDOM_OF_SWAMP,			// 32
		RANK_BONUS_WISDOM_OF_SILENCE,			// 33
		RANK_BONUS_WISDOM_OF_DARKNESS,			// 34
		RANK_BONUS_WIDE_DARKNESS,			// 35

		RANK_BONUS_WOOD_SKIN,				// 36
		RANK_BONUS_WIND_SENSE,			// 37
		RANK_BONUS_HOMING_EYE,			// 38
		RANK_BONUS_LIFE_ENERGY,			// 39
		RANK_BONUS_SOUL_ENERGY,			// 40
		RANK_BONUS_STONE_MAUL,			// 41
		RANK_BONUS_SWIFT_ARM,			// 42
		RANK_BONUS_FIRE_ENDOW,			// 43
		RANK_BONUS_WATER_ENDOW,			// 44
		RANK_BONUS_EARTH_ENDOW,			// 45
		RANK_BONUS_ANTI_ACID_SKIN,			// 46
		RANK_BONUS_ANTI_BLOODY_SKIN,			// 47
		RANK_BONUS_ANTI_CURSE_SKIN,			// 48
		RANK_BONUS_ANTI_POISON_SKIN,			// 49
		RANK_BONUS_ANTI_SILVER_DAMAGE_SKIN,			// 50
		RANK_BONUS_BLESS_OF_NATURE,			// 51
		RANK_BONUS_LIFE_ABSORB,			// 52
		RANK_BONUS_SOUL_ABSORB,			// 53
		RANK_BONUS_MYSTIC_RULE,			// 54

		RANK_BONUS_PERCEPTION,			// 55
		RANK_BONUS_STONE_OF_SAGE,			// 56
		RANK_BONUS_FOOT_OF_RANGER,			// 57
		RANK_BONUS_WARRIORS_FIST,			// 58

		RANK_BONUS_ACID_INQUIRY,			// 59
		RANK_BONUS_BLOODY_INQUIRY,			// 60
		RANK_BONUS_CURSE_INQUIRY,			// 61
		RANK_BONUS_POISON_INQUIRY,			// 62
		RANK_BONUS_INQUIRY_MASTERY,			// 63

		RANK_BONUS_POWER_OF_SPIRIT,			// 64
		RANK_BONUS_WIND_OF_SPIRIT,			// 65
		RANK_BONUS_PIXIES_EYES,			// 66
		RANK_BONUS_GROUND_OF_SPIRIT,			// 67
		RANK_BONUS_FIRE_OF_SPIRIT,			// 68

		RANK_BONUS_EVOLUTION_IMMORTAL_HEART,			// 69
		RANK_BONUS_BEHEMOTH_ARMOR_2,			// 70
		RANK_BONUS_DRAGON_EYE_2,			// 71
		RANK_BONUS_EVOLUTION_RELIANCE_BRAIN,			// 72
		RANK_BONUS_HIT_CONTROL,			// 73

		RANK_BONUS_ACID_MASTERY,			// 74
		RANK_BONUS_BLOODY_MASTERY,			// 75
		RANK_BONUS_CURSE_MASTERY,			// 76
		RANK_BONUS_POISON_MASTERY,			// 77
		RANK_BONUS_SKILL_MASTERY,			// 78

		RANK_BONUS_SALAMANDERS_KNOWLEDGE,			// 79
		RANK_BONUS_UNDINES_KNOWLEDGE,			// 80
		RANK_BONUS_GNOMES_KNOWLEDGE,			// 81

		RANK_BONUS_MAX
	};

public:
	RankBonus() throw();
	RankBonus( DWORD type, DWORD point, Rank_t rank ) throw();
	~RankBonus() throw();

public:
	DWORD getType() const throw() { return m_Type; }
	void setType( DWORD type ) throw() { m_Type = type; }

	DWORD getPoint() const throw() { return m_Point; }
	void setPoint( DWORD point ) throw() { m_Point = point; }

	Rank_t getRank() const throw() { return m_Rank; }
	void setRank( Rank_t rank ) throw() { m_Rank = rank; }

protected:
	DWORD m_Type;
	DWORD m_Point;
	Rank_t m_Rank;

};

#endif
