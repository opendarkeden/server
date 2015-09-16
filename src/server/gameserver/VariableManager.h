#ifndef __VARIABLE_MANAGER_H__
#define __VARIABLE_MANAGER_H__

#include "Exception.h"
#include <map>
#include <vector>

enum VariableType
{
	STAR_RATIO,						// 0
	EVENT_ACTIVE,					// 1
	EVENT_RATIO,					// 2
	ITEM_PROBE_RATIO,				// 3
	EXP_RATIO,						// 4
	COMBAT_BONUS_TIME,				// 5
	COMBAT_SLAYER_HP_BONUS_RATIO,	// 6
	COMBAT_VAMPIRE_HP_BONUS_RATIO,	// 7
	PREMIUM_EXP_BONUS_PERCENT,		// 8
	PREMIUM_ITEM_PROBE_PERCENT,		// 9
	ZONE_GROUP_BALANCING_MINUTE,	// 10
	GAMBLE_ITEM_TYPE_RATIO,			// 11
	GAMBLE_ITEM_OPTION_RATIO,		// 12
	SUMMON_MOTORCYCLE,				// 13
	ENEMY_LIMIT_TIME,				// 14
	COMBAT_SLAYER_DAMAGE_BONUS,		// 15
	COMBAT_VAMPIRE_DAMAGE_BONUS,	// 16
	RARE_ITEM_RATIO,				// 17
	UNIQUE_ITEM_RATIO,				// 18
	ACTIVE_MASTER_LAIR,				// 19
	RETRY_MASTER_LAIR,				// 20
	HARVEST_FESTIVAL_ITEM_RATIO,	// 21
	MASTER_BLOOD_DRAIN_START_HP,	// 22
	MASTER_BLOOD_DRAIN_START_BD,	// 23
	MASTER_BLOOD_DRAIN_END_HP,		// 24
	MASTER_BLOOD_DRAIN_END_BD,		// 25
	ACTIVE_CHIEF_MONSTER,			// 26
	CHIEF_MONSTER_RARE_ITEM_RATIO,	// 27
	NEWBIE_TRANSPORT_TO_GUILD,		// 28
	FREE_PLAY_SLAYER_DOMAIN_SUM,	// 29
	FREE_PLAY_VAMPIRE_LEVEL,		// 30
	LOG_INCOMING_CONNECTION,		// 31
	CHRISTMAS_FIRE_CRACKER_RATIO,	// 32
	CHRISTMAS_TREE_PART_RATIO,		// 33
	CHRISTMAS_GIFT_BOX_RATIO,		// 34
	CHRISTMAS_TREE_DECAY_TIME,		// 35
	MASTER_LAIR_PLAYER_NUM,			// 36
	RANK_EXP_GAIN_PERCENT,			// 37
	ITEM_LUCK_PERCENT,				// 38

	// 대박 이벤트 용 (code name : lotto event )
	// 2003. 1. 12 by bezz. Sequoia. dew
	LOTTO_ITEM_RATIO,				// 39
	LOTTO_ITEM_BONUS_NUM,			// 40
	LOTTO_SKULL_RATIO,				// 41
	PREMIUM_HALF_EVENT,				// 42

	// 2003. 1. 20 by bezz, Sequoia
	COMMON_CASTLE_ENTRANCE_FEE,		// 43
	GUILD_CASTLE_ENTRANCE_FEE,		// 44

	COMMON_CASTLE_ITEM_TAX_RATIO,	// 45
	GUILD_CASTLE_ITEM_TAX_RATIO,	// 46

	WAR_REGISTRATION_FEE,			// 47

	GUILD_WAR_TIME,					// 48
	RACE_WAR_TIME,					// 49

	WAR_PERIOD_WEEK,				// 50

	WAR_ACTIVE,						// 51

	RACE_WAR_TIMEBAND,				// 52

	AUTO_START_RACE_WAR,			// 53
	
	ACTIVE_RACE_WAR_LIMITER,		// 54

	CHIEF_ITEM_BONUS_NUM,			// 55

	ACTIVE_EVENT_GIVE_ITEM,			// 56

	VAMPIRE_REDISTRIBUTE_ATTR_PRICE,//57

	ACTIVATE_COUPLE,				// 58

	CAN_RECOUPLE,					// 59

	GUILD_WAR_ACTIVE,				// 60

	FREE_PLAY_OUSTERS_LEVEL,		// 61

	CAN_APPLY_QUEST,				// 62

	SEND_QUEST_INFO,				// 63

	CAN_BUY_SHOP,					// 64

	PCROOM_EXP_BONUS,				// 65
	PCROOM_ITEM_RATIO_BONUS,		// 66

	MONEY_TRACE_LOG_LIMIT,			// 67

	// 피시방 복권 이벤트
	PC_ROOM_LOTTO_EVENT,			// 68
	ACTIVE_FLAG_WAR,				// 69

	// shutdown
	KILL_DAEMONCTL,					// 70

	EVENT_MOON_CARD,				// 71

	FULL_MOON_CARD_RATIO,			// 72
	HALF_MOON_CARD_RATIO,			// 73
	NEW_MOON_CARD_RATIO,			// 74
	OLD_MOON_CARD_RATIO,			// 75

	ACTIVE_LEVEL_WAR,				// 76
	RACE_WAR_HP_BONUS,				// 77

	HEAD_COUNT,						// 78

	HEAD_PRICE_BONUS,				// 79

	LEVEL_WAR_ZONE_FREE_ENTER, 		// 80
	PET_EXP_RATIO,					// 81

	EVENT_LUCKY_BAG,                // 82
	GREEN_LUCKY_BAG_RATIO,          // 83
	BLUE_LUCKY_BAG_RATIO,           // 84
	GOLD_LUCKY_BAG_RATIO,           // 85
	RED_LUCKY_BAG_RATIO,            // 86

	// 위의 CHRISTMAS_GIFT_BOX 랑은 관련이 없다
	EVENT_GIFT_BOX,                 // 87
	RED_GIFT_BOX_RATIO,             // 88
	BLUE_GIFT_BOX_RATIO,            // 89
	GREEN_GIFT_BOX_RATIO,           // 90
	YELLOW_GIFT_BOX_RATIO,          // 91

	NETMARBLE_CARD_RATIO,			// 92
	NETMARBLE_CARD_EVENT,			// 93

	PREMIUM_TRIAL_EVENT,			// 94

	PET_FOOD_EVENT,					// 95

	HIGHER_PET_FOOD_RATIO,			// 96

	PET_FOOD_RATIO,					// 97
	RACE_PET_FOOD_RATIO,			// 98
	REVIVAL_SET_RATIO,				// 99

	TODAY_IS_HOLYDAY,				// 100

	SLAYER_HP_RATIO,				// 101
	VAMPIRE_HP_RATIO,				// 102
	OUSTERS_HP_RATIO,				// 103
	MONSTER_HP_RATIO,				// 104
	MONSTER_EXP_RATIO,				// 105

	CLOVER_EVENT,					// 106
	CLOVER_RATIO,					// 107

	MONSTER_DAMAGE_RATIO,			// 108

	RACE_PET_QUEST,					// 109

	NICKNAME_PEN_EVENT,				// 110
	NICKNAME_PEN_RATIO,				// 111

	GOLD_MEDAL_RATIO,				// 112
	PET_DAY_EVENT,					// 113

	OLYMPIC_ITEM_RATIO,				// 114
	OLYMPIC_EVENT,					// 115

	CROWN_PRICE,					// 116

	CHOBO_EVENT,					// 117

	PINE_CAKE_EVENT,				// 118
	PINE_CAKE_RATIO,				// 119

	QUIT_GUILD_PENALTY_TERM,		// 120
	GUILD_UNION_MAX,				// 121

	LUCK_CHARM_RATIO,				// 122
	GDR_LAIR_PC_LIMIT,				// 123

	DONATION_EVENT_200501,			// 124

	HOURGLASS_RATIO_S,				// 125
	HOURGLASS_RATIO_M,				// 126
	HOURGLASS_RATIO_L,				// 127

	EVENT_NEW_YEAR_2005,				// 128
	BOKJORY_RATIO,						// 129
	EVENT_RED_RICE_CAKE_SOUP_RATIO,		// 130
	EVENT_GREEN_RICE_CAKE_SOUP_RATIO,	// 131
	EVENT_BLUE_RICE_CAKE_SOUP_RATIO,	// 132
	EVENT_BLACK_RICE_CAKE_SOUP_RATIO,	// 133
	EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO,	// 134

	TIME_PERIOD_EXP_2X,				// 135
	COUNT_KILL_MONSTER,				// 136

	DONATION_EVENT_200505,			// 137

	FAMILY_COIN_EVENT,				// 138
	FAMILY_COIN_RATIO,				// 139
	BALLOON_HEADBAND_EVENT,			// 140
	BALLOON_HEADBAND_RATIO,			// 141
	FULL_PARTY_EXP_EVENT,			// 142

	VARIABLE_MAX
};

const string VariableType2String[VARIABLE_MAX] =
{
	"STAR_RATIO",						// 0
	"EVENT_ACTIVE",						// 1
	"EVENT_RATIO",						// 2
	"ITEM_PROBE_RATIO",					// 3
	"EXP_RATIO",						// 4
	"COMBAT_BONUS_TIME",				// 5
	"COMBAT_SLAYER_HP_BONUS_RATIO",		// 6
	"COMBAT_VAMPIRE_HP_BONUS_RATIO",	// 7
	"PREMIUM_EXP_BONUS_PERCENT",		// 8
	"PREMIUM_ITEM_PROBE_PERCENT",		// 9
	"ZONE_GROUP_BALANCING_MINUTE",		// 10
	"GAMBLE_ITEM_TYPE_RATIO",			// 11
	"GAMBLE_ITEM_OPTION_RATIO",			// 12
	"SUMMON_MOTORCYCLE",				// 13
	"ENEMY_LIMIT_TIME",					// 14
	"COMBAT_SLAYER_DAMAGE_BONUS",		// 15
	"COMBAT_VAMPIRE_DAMAGE_BONUS",		// 16
	"RARE_ITEM_RATIO",					// 17
	"UNIQUE_ITEM_RATIO",				// 18
	"ACTIVE_MASTER_LAIR",				// 19
	"RETRY_MASTER_LAIR",				// 20
	"HARVEST_FESTIVAL_ITEM_RATIO",		// 21
	"MASTER_BLOOD_DRAIN_START_HP",		// 22
	"MASTER_BLOOD_DRAIN_START_BD",		// 23
	"MASTER_BLOOD_DRAIN_END_HP",		// 24
	"MASTER_BLOOD_DRAIN_END_BD",		// 25
	"ACTIVE_CHIEF_MONSTER",				// 26
	"CHIEF_MONSTER_RARE_ITEM_RATIO",	// 27
	"NEWBIE_TRANSPORT_TO_GUILD",		// 28
	"FREE_PLAY_SLAYER_SUM",				// 29
	"FREE_PLAY_VAMPIRE_LEVEL",			// 30
	"LOG_INCOMING_CONNECTION",			// 31
	"CHRISTMAS_FIRE_CRACKER_RATIO",		// 32
	"CHRISTMAS_TREE_PART_RATIO",		// 33
	"CHRISTMAS_GIFT_BOX_RATIO",			// 34
	"CHRISTMAS_TREE_DECAY_TIME",		// 35
	"MASTER_LAIR_PLAYER_NUM",			// 36
	"RANK_EXP_GAIN_PERCENT",			// 37
	"ITEM_LUCK_PERCENT",				// 38

	// 대박 이벤트 용 (code name : lotto event )
	// 2003. 1. 12 by bezz. Sequoia. dew
	"LOTTO_ITEM_RATIO",					// 39
	"LOTTO_ITEM_BONUS_NUM"	,			// 40
	"LOTTO_SKULL_RATIO",				// 41
	"PREMIUM_HALF_EVENT",				// 42

	// 2003. 1. 20 by bezz, Sequoia
	"COMMON_CASTLE_ENTRANCE_FEE",		// 43
	"GUILD_CASTLE_ENTRANCE_FEE",		// 44

	"COMMON_CASTLE_ITEM_TAX_RATIO",		// 45
	"GUILD_CASTLE_ITEM_TAX_RATIO",		// 46

	"WAR_REGISTRATION_FEE",				// 47

	"GUILD_WAR_TIME",					// 48
	"RACE_WAR_TIME",					// 49

	"WAR_PERIOD_WEEK",					// 50

	"WAR_ACTIVE",						// 51

	"RACE_WAR_TIMEBAND",				// 52

	"AUTO_START_RACE_WAR",				// 53

	"ACTIVE_RACE_WAR_LIMITER",			// 54

	"CHIEF_ITEM_BONUS_NUM",				// 55

	"ACTIVE_EVENT_GIVE_ITEM",			// 56

	"VAMPIRE_REDISTRIBUTE_ATTR_PRICE",	//57

	"ACTIVATE_COUPLE",					// 58

	"CAN_RECOUPLE",						// 59

	"GUILD_WAR_ACTIVE",					// 60

	"FREE_PLAY_OUSTERS_LEVEL",			// 61

	"CAN_APPLY_QUEST",				// 62

	"SEND_QUEST_INFO",				// 63
	"CAN_BUY_SHOP",					// 64

	"PCROOM_EXP_BONUS",				// 65
	"PCROOM_ITEM_RATIO_BONUS",		// 66

	"MONEY_TRACE_LOG_LIMIT",		// 67

	"PC_ROOM_LOTTO_EVENT",			// 68
	"ACTIVE_FLAG_WAR",				// 69

	// shutdown
	"KILL_DAEMONCTL",				// 70
	"EVENT_MOON_CARD",				// 71

	"FULL_MOON_CARD_RATIO",			// 72
	"HALF_MOON_CARD_RATIO",			// 73
	"NEW_MOON_CARD_RATIO",			// 74
	"OLD_MOON_CARD_RATIO",			// 75
	"ACTIVE_LEVEL_WAR",				// 76
	"RACE_WAR_HP_BONUS",			// 77
	"HEAD_COUNT",					// 78
	"HEAD_PRICE_BONUS",				// 79
	"LEVEL_WAR_ZONE_FREE_ENTER",	// 80
	"PET_EXP_RATIO",				// 81

	"EVENT_LUCKY_BAG",              // 82
	"GREEN_LUCKY_BAG_RATIO",        // 83
	"BLUE_LUCKY_BAG_RATIO",         // 84
	"GOLD_LUCKY_BAG_RATIO",         // 85
	"RED_LUCKY_BAG_RATIO",          // 86

	// 위의 CHRISTMAS_GIFT_BOX 랑은 관련이 없다
	"EVENT_GIFT_BOX",               // 87
	"RED_GIFT_BOX_RATIO",           // 88
	"BLUE_GIFT_BOX_RATIO",          // 89
	"GREEN_GIFT_BOX_RATIO",         // 90
	"YELLOW_GIFT_BOX_RATIO",        // 91

	"NETMARBLE_CARD_RATIO",			// 92
	"NETMARBLE_CARD_EVENT",			// 93

	"PREMIUM_TRIAL_EVENT",			// 94

	"PET_FOOD_EVENT",				// 95

	"HIGHER_PET_FOOD_RATIO",		// 96

	"PET_FOOD_RATIO",				// 97
	"RACE_PET_FOOD_RATIO",			// 98
	"REVIVAL_SET_RATIO",			// 99

	"TODAY_IS_HOLYDAY",				// 100
	"SLAYER_HP_RATIO",				// 101
	"VAMPIRE_HP_RATIO",				// 102
	"OUSTERS_HP_RATIO",				// 103
	"MONSTER_HP_RATIO",				// 104

	"MONSTER_EXP_RATIO",			// 105

	"CLOVER_EVENT",					// 106
	"CLOVER_RATIO",					// 107

	"MONSTER_DAMAGE_RATIO",			// 108

	"RACE_PET_QUEST",				// 109

	"NICKNAME_PEN_EVENT",				// 110
	"NICKNAME_PEN_RATIO",				// 111

	"GOLD_MEDAL_RATIO",				// 112
	"PET_DAY_EVENT",					// 113

	"OLYMPIC_ITEM_RATIO",				// 114
	"OLYMPIC_EVENT",					// 115
	"CROWN_PRICE",						// 116

	"CHOBO_EVENT",					// 117

	"PINE_CAKE_EVENT",				// 118
	"PINE_CAKE_RATIO",				// 119

	"QUIT_GUILD_PENALTY_TERM",		// 120
	"GUILD_UNION_MAX",				// 121

	"LUCK_CHARM_RATIO",				// 122
	"GDR_LAIR_PC_LIMIT",				// 123

	"DONATION_EVENT_200501",		// 124

	"HOURGLASS_RATIO_S",		// 125
	"HOURGLASS_RATIO_M",				// 126
	"HOURGLASS_RATIO_L",				// 127

	"EVENT_NEW_YEAR_2005",					// 128
	"BOKJORY_RATIO",						// 129
	"EVENT_RED_RICE_CAKE_SOUP_RATIO",		// 130
	"EVENT_GREEN_RICE_CAKE_SOUP_RATIO",		// 131
	"EVENT_BLUE_RICE_CAKE_SOUP_RATIO",		// 132
	"EVENT_BLACK_RICE_CAKE_SOUP_RATIO",		// 133
	"EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO",	// 134
	"TIME_PERIOD_EXP_2X",				// 135
	"COUNT_KILL_MONSTER",				// 136
	"DONATION_EVENT_200505",			// 137
	"FAMILY_COIN_EVENT",				// 138
	"FAMILY_COIN_RATIO",				// 139
	"BALLOON_HEADBAND_EVENT",			// 140
	"BALLOON_HEADBAND_RATIO",			// 141
	"FULL_PARTY_EXP_EVENT",				// 142
};


class VariableManager
{
public :
	typedef vector<int>						VARIABLE;
	typedef map<string, VariableType>	VARIABLE_NAME;

public:
	VariableManager() throw(Error);
    ~VariableManager() throw(Error);

public:
	void init() throw(Error);
	void load() throw(Error);

	// generic value. by sigi. 2002.11.19
	VariableType	 getVariableType(const string& variableName) const;

	void setVariable(VariableType vt, int value);
	void setVariable(VariableType vt, const string& strVariable);	// ON / OFF
	int	 getVariable(VariableType vt) const		 { return m_Variables[vt]; }

	int	 getSize() const		 				{ return m_Variables.size(); }
	string	 toString(VariableType vt) const;

	void setStar(int star) 				{ setVariable(STAR_RATIO, star); }
	int  getStar() const				{ return m_Variables[STAR_RATIO]; }

	// 이벤트가 활성화되고 끊는 함수
	void  setEventActivate(int value) 	{ setVariable(EVENT_ACTIVE, value); }
	int   getEventActivate() const		{ return m_Variables[EVENT_ACTIVE]; }
	
	void  setEventRatio(int value) 		{ setVariable(EVENT_RATIO, value); }
	int   getEventRatio() const 		{ return m_Variables[EVENT_RATIO]; }

	void  setItemProbRatio(int value) 	{ setVariable(ITEM_PROBE_RATIO, value); }
	int   getItemProbRatio() const		{ return m_Variables[ITEM_PROBE_RATIO]; }

	void  setExpRatio(int value) 		{ setVariable(EXP_RATIO, value); }
	int   getExpRatio() const			{ return m_Variables[EXP_RATIO]; }
	
	void  setCombatBonusTime(int value) { setVariable(COMBAT_BONUS_TIME, value); }
	int   getCombatBonusTime() const	{ return m_Variables[COMBAT_BONUS_TIME]; }

	void	setCombatSlayerHPBonusRatio(int value)  { setVariable(COMBAT_SLAYER_HP_BONUS_RATIO, value); }
	int		getCombatSlayerHPBonusRatio() const 	{ return m_Variables[COMBAT_SLAYER_HP_BONUS_RATIO]; }

	void	setCombatVampireHPBonusRatio(int value) { setVariable(COMBAT_VAMPIRE_HP_BONUS_RATIO, value); }
	int		getCombatVampireHPBonusRatio() const 	{ return m_Variables[COMBAT_VAMPIRE_HP_BONUS_RATIO]; }

	void	setCombatSlayerDamageBonus(int value) 	{ setVariable(COMBAT_SLAYER_DAMAGE_BONUS, value); }
	int		getCombatSlayerDamageBonus() const 		{ return m_Variables[COMBAT_SLAYER_DAMAGE_BONUS]; }

	void	setCombatVampireDamageBonus(int value) 	{ setVariable(COMBAT_VAMPIRE_DAMAGE_BONUS, value); }
	int		getCombatVampireDamageBonus() const 	{ return m_Variables[COMBAT_VAMPIRE_DAMAGE_BONUS]; }

	void  setPremiumExpBonusPercent(int value) 		{ setVariable(PREMIUM_EXP_BONUS_PERCENT, value); }
	int   getPremiumExpBonusPercent() const			{ return m_Variables[PREMIUM_EXP_BONUS_PERCENT]; }
	
	void  setPremiumItemProbePercent(int value) 	{ setVariable(PREMIUM_ITEM_PROBE_PERCENT, value); }
	int   getPremiumItemProbePercent() const		{ return m_Variables[PREMIUM_ITEM_PROBE_PERCENT]; }
	
	void  setZoneGroupBalancingMinute(int value) 	{ setVariable(ZONE_GROUP_BALANCING_MINUTE, value); }
	int   getZoneGroupBalancingMinute() const		{ return m_Variables[ZONE_GROUP_BALANCING_MINUTE]; }

	void  setGambleItemTypeRatio(int value) 		{ setVariable(GAMBLE_ITEM_TYPE_RATIO, value); }
	int   getGambleItemTypeRatio() const			{ return m_Variables[GAMBLE_ITEM_TYPE_RATIO]; }

	void  setGambleItemOptionRatio(int value) 		{ setVariable(GAMBLE_ITEM_OPTION_RATIO, value); }
	int   getGambleItemOptionRatio() const			{ return m_Variables[GAMBLE_ITEM_OPTION_RATIO]; }

	void  setSummonMotorcycle(bool value) 			{ setVariable(SUMMON_MOTORCYCLE, (int)value); }
	bool  isSummonMotorcycle() const				{ return m_Variables[SUMMON_MOTORCYCLE]!=0; }

	void  setEnemyLimitTime(int value) 				{ setVariable(ENEMY_LIMIT_TIME, value); }
	int   getEnemyLimitTime() const					{ return m_Variables[ENEMY_LIMIT_TIME]; }

	void  setRareItemRatio(int value) 				{ setVariable(RARE_ITEM_RATIO, value); }
	int   getRareItemRatio() const					{ return m_Variables[RARE_ITEM_RATIO]; }

	void  setUniqueItemRatio(int value) 			{ setVariable(UNIQUE_ITEM_RATIO, value); }
	int   getUniqueItemRatio() const				{ return m_Variables[UNIQUE_ITEM_RATIO]; }

	void  setActiveMasterLair(bool value) 			{ setVariable(ACTIVE_MASTER_LAIR, (int)value); }
	bool  isActiveMasterLair() const 				{ return m_Variables[ACTIVE_MASTER_LAIR]!=0; }

	void  setRetryMasterLair(bool value) 			{ setVariable(RETRY_MASTER_LAIR, (int)value); }
	bool  isRetryMasterLair() const					{ return m_Variables[RETRY_MASTER_LAIR]!=0; }

	void  setHarvestFestivalItemRatio(int value) 	{ setVariable(HARVEST_FESTIVAL_ITEM_RATIO, value); }
	int   getHarvestFestivalItemRatio() const		{ return m_Variables[HARVEST_FESTIVAL_ITEM_RATIO]; }

	void  setMasterBloodDrainStartHP(int value) 	{ setVariable(MASTER_BLOOD_DRAIN_START_HP, value); }
	int   getMasterBloodDrainStartHP() const		{ return m_Variables[MASTER_BLOOD_DRAIN_START_HP]; }

	void  setMasterBloodDrainStartBD(int value) 	{ setVariable(MASTER_BLOOD_DRAIN_START_BD, value); }
	int   getMasterBloodDrainStartBD() const		{ return m_Variables[MASTER_BLOOD_DRAIN_START_BD]; }

	void  setMasterBloodDrainEndHP(int value) 		{ setVariable(MASTER_BLOOD_DRAIN_END_HP, value); }
	int   getMasterBloodDrainEndHP() const			{ return m_Variables[MASTER_BLOOD_DRAIN_END_HP]; }

	void  setMasterBloodDrainEndBD(int value) 		{ setVariable(MASTER_BLOOD_DRAIN_END_BD, value); }
	int   getMasterBloodDrainEndBD() const			{ return m_Variables[MASTER_BLOOD_DRAIN_END_BD]; }

	void 	setActiveChiefMonster(bool value) 		{ setVariable(ACTIVE_CHIEF_MONSTER, (int)value); }
	bool 	isActiveChiefMonster() const 			{ return m_Variables[ACTIVE_CHIEF_MONSTER]!=0; }

	void 	setChiefMonsterRareItemPercent(int value)	{ setVariable(CHIEF_MONSTER_RARE_ITEM_RATIO, value); }
	int 	getChiefMonsterRareItemPercent() const 	{ return m_Variables[CHIEF_MONSTER_RARE_ITEM_RATIO]; }

	void 	setNewbieTransportToGuild(bool value) 	{ setVariable(NEWBIE_TRANSPORT_TO_GUILD, value); }
	bool 	isNewbieTransportToGuild() const 		{ return m_Variables[NEWBIE_TRANSPORT_TO_GUILD]!=0; }

	void setChristmasFireCrackerRatio(int value )	{ setVariable(CHRISTMAS_FIRE_CRACKER_RATIO, value); }
	int	 getChristmasFireCrackerRatio() const		{ return m_Variables[CHRISTMAS_FIRE_CRACKER_RATIO]; }

	void setChristmasTreePartRatio(int value )		{ setVariable(CHRISTMAS_TREE_PART_RATIO, value); }
	int	 getChristmasTreeRatio() const				{ return m_Variables[CHRISTMAS_TREE_PART_RATIO]; }

	bool 	isWarPeriodWeek() const 				{ return m_Variables[WAR_PERIOD_WEEK]!=0; }
	bool 	isWarActive() const 					{ return m_Variables[WAR_ACTIVE]!=0; }
	bool 	isAutoStartRaceWar() const 				{ return m_Variables[AUTO_START_RACE_WAR]!=0; }
	bool	isActiveGuildWar() const				{ return m_Variables[GUILD_WAR_ACTIVE]!=0; }
	bool 	isActiveRaceWarLimiter() const 			{ return m_Variables[ACTIVE_RACE_WAR_LIMITER]!=0; }
	bool 	isActiveGiveEventItem() const 			{ return m_Variables[ACTIVE_EVENT_GIVE_ITEM]!=0; }

	bool	isActivateCouple()	const				{ return m_Variables[ACTIVATE_COUPLE]!=0; }
	bool	canRecouple() const						{ return m_Variables[CAN_RECOUPLE]!=0; }

	bool	canApplyQuest() const					{ return m_Variables[CAN_APPLY_QUEST]!=0; }
	bool	bSendQuestInfo() const					{ return m_Variables[SEND_QUEST_INFO]!=0; }

	void  setPCRoomExpBonusPercent(int value) 		{ setVariable(PCROOM_EXP_BONUS, value); }
	int   getPCRoomExpBonusPercent() const			{ return m_Variables[PCROOM_EXP_BONUS]; }

	void  setPCRoomItemRatioBonusPercent(int value) 		{ setVariable(PCROOM_ITEM_RATIO_BONUS, value); }
	int   getPCRoomItemRatioBonusPercent() const			{ return m_Variables[PCROOM_ITEM_RATIO_BONUS]; }

	void  setMoneyTraceLogLimit(uint value) 		{ setVariable(MONEY_TRACE_LOG_LIMIT, value); }
	uint   getMoneyTraceLogLimit() const			{ return m_Variables[MONEY_TRACE_LOG_LIMIT]; }

	void setPCRoomLottoEvent(bool value)			{ setVariable(PC_ROOM_LOTTO_EVENT, value); }
	bool isPCRoomLottoEvent() const					{ return m_Variables[PC_ROOM_LOTTO_EVENT]!=0; }

	bool isActiveFlagWar() const					{ return m_Variables[ACTIVE_FLAG_WAR]!=0; }

	void setKillDaemonCtl(bool value)				{ setVariable(KILL_DAEMONCTL, value); }
	bool isKillDaemonCtl() const					{ return m_Variables[KILL_DAEMONCTL]!=0; }

	bool isEventMoonCard() const					{ return m_Variables[EVENT_MOON_CARD]!=0; }

	bool isActiveLevelWar() const					{ return m_Variables[ACTIVE_LEVEL_WAR]!=0; }

	uint getRaceWarHPBonus() const					{ return m_Variables[RACE_WAR_HP_BONUS]; }
	bool isHeadCount() const						{ return m_Variables[HEAD_COUNT]!=0; }

	uint getHeadPriceBonus() const					{ return m_Variables[HEAD_PRICE_BONUS]; }
	bool canEnterLevelWarZoneFree() const   		{ return m_Variables[LEVEL_WAR_ZONE_FREE_ENTER]!=0; }

	int getPetExpRatio() const   					{ return m_Variables[PET_EXP_RATIO]; }

	bool isEventLuckyBag() const                    { return m_Variables[EVENT_LUCKY_BAG]!=0; }

	bool isEventGiftBox() const                     { return m_Variables[EVENT_GIFT_BOX]!=0; }

// data members
private:
	VARIABLE					m_Variables;
		
	VARIABLE_NAME 				m_VariableNames;
};

extern VariableManager* g_pVariableManager;

#endif // __VARIABLE_H__
