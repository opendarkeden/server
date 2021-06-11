#include "VariableManager.h"
#include "DB.h"
#include "Properties.h"
#include "SystemAvailabilitiesManager.h"
#include <stdlib.h>

extern void strlwr(char* str);

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
VariableManager::VariableManager()
	
{
	__BEGIN_TRY

	m_Variables.resize(VARIABLE_MAX);

	m_Variables[STAR_RATIO] = 1000;
	m_Variables[EVENT_ACTIVE] = 1;
	m_Variables[EVENT_RATIO] = 1000;
    m_Variables[ITEM_PROBE_RATIO] = 1;
	m_Variables[EXP_RATIO] = 1;
	m_Variables[COMBAT_BONUS_TIME] = 30;	// 30분
	m_Variables[COMBAT_SLAYER_HP_BONUS_RATIO] = 0;
	m_Variables[COMBAT_VAMPIRE_HP_BONUS_RATIO] = 0;
	m_Variables[COMBAT_SLAYER_DAMAGE_BONUS]= 0;
	m_Variables[COMBAT_VAMPIRE_DAMAGE_BONUS]= 0;
	m_Variables[PREMIUM_EXP_BONUS_PERCENT] = 150; // 150%
	m_Variables[PREMIUM_ITEM_PROBE_PERCENT] = 220; // 220%
	m_Variables[ZONE_GROUP_BALANCING_MINUTE] = 4*7*24*60; // 4주일
	m_Variables[GAMBLE_ITEM_TYPE_RATIO] = 100;	// 100%
	m_Variables[GAMBLE_ITEM_OPTION_RATIO] = 100;	// 100%
	m_Variables[SUMMON_MOTORCYCLE] = 0;
	m_Variables[ENEMY_LIMIT_TIME] = 300; // 5분 
	m_Variables[RARE_ITEM_RATIO] = 100; // 100%
	m_Variables[UNIQUE_ITEM_RATIO] = 100; // 100%
	m_Variables[ACTIVE_MASTER_LAIR] = 0;
	m_Variables[RETRY_MASTER_LAIR] = 0;
	m_Variables[HARVEST_FESTIVAL_ITEM_RATIO] = 100;	// 100%

	// [마스터 흡혈 방식]
	// HP가 70% 이상일때는 흡혈하지 않고
	// HP가 70%일때 10%의 확률로 흡혈하고
	//      50%     20%
	// HP가 30%일때 30%의 확률로 흡혈한다.
	// HP가 30%이하일때는 30%의 확률로 흡혈한다.
	m_Variables[MASTER_BLOOD_DRAIN_START_HP] 	= 70;
	m_Variables[MASTER_BLOOD_DRAIN_START_BD] 	= 10;
	m_Variables[MASTER_BLOOD_DRAIN_END_HP] 	= 30;
	m_Variables[MASTER_BLOOD_DRAIN_END_BD] 	= 30;

	m_Variables[ACTIVE_CHIEF_MONSTER] = 0;
	m_Variables[CHIEF_MONSTER_RARE_ITEM_RATIO] = 0;

	m_Variables[NEWBIE_TRANSPORT_TO_GUILD] = 1;

	// 2002.11.19
	m_Variables[FREE_PLAY_SLAYER_DOMAIN_SUM] = 30;
	m_Variables[FREE_PLAY_VAMPIRE_LEVEL] = 30;

	// 2002.12.10
	m_Variables[LOG_INCOMING_CONNECTION] = false;

	// 2002.12.11
	m_Variables[CHRISTMAS_FIRE_CRACKER_RATIO] = 0;
	m_Variables[CHRISTMAS_TREE_PART_RATIO] = 0;

	// 2002.12.12
	m_Variables[CHRISTMAS_GIFT_BOX_RATIO] = 0;

	// 2002.12.17
	m_Variables[CHRISTMAS_TREE_DECAY_TIME] = 6*60*60*10;

	// 2002.12.31
	m_Variables[MASTER_LAIR_PLAYER_NUM] = 15;
	m_Variables[RANK_EXP_GAIN_PERCENT] 	= 100;	// 100이면 원래 그대로
	m_Variables[ITEM_LUCK_PERCENT] 		= 100;	// 200이면 두배(200%)라는 의미다.

	// 대박 이벤트 용 ( code name : lotto event )
	// 2003. 1. 12 by bezz. Sequoia. dew
	m_Variables[LOTTO_ITEM_RATIO]		= 0;
	m_Variables[LOTTO_ITEM_BONUS_NUM]	= 0;
	m_Variables[LOTTO_SKULL_RATIO]		= 0;
	m_Variables[PREMIUM_HALF_EVENT]		= false;

	// 2003. 1. 20 by bezz, Sequoia
	m_Variables[COMMON_CASTLE_ENTRANCE_FEE]	= 1000;
	m_Variables[GUILD_CASTLE_ENTRANCE_FEE] = 10000;

	m_Variables[COMMON_CASTLE_ITEM_TAX_RATIO] = 110;
	m_Variables[GUILD_CASTLE_ITEM_TAX_RATIO] = 150;
	m_Variables[WAR_REGISTRATION_FEE] 	= 50000000;

	m_Variables[GUILD_WAR_TIME] 	= 1*60*60;	// 1시간
	m_Variables[RACE_WAR_TIME] 		= 3*60*60;	// 3시간

	m_Variables[WAR_PERIOD_WEEK] 	= true;		// 전쟁은 한 주 단위의 주기를 가진다.

	m_Variables[WAR_ACTIVE] 		= false;	// 전쟁 기능이 작동하지 않는다.

	m_Variables[RACE_WAR_TIMEBAND]	= 2;		// 종족 전쟁시 시간

	m_Variables[AUTO_START_RACE_WAR]= false;	// 종족 전쟁을 자동으로 시작하는가?

	m_Variables[ACTIVATE_COUPLE] = false;	// 커플이 성사될 수 있는 기간인가?

	m_Variables[ACTIVE_RACE_WAR_LIMITER] = true;	// 종족 전쟁 참가 인원 제한

	m_Variables[CHIEF_ITEM_BONUS_NUM] = 0;		// 치프 몬스터 추가 아이템 개수

	m_Variables[ACTIVE_EVENT_GIVE_ITEM] = false;		// 아이템 주는 이벤트

	m_Variables[VAMPIRE_REDISTRIBUTE_ATTR_PRICE] = 1000000;	// 능력치 재분배 비용

	m_Variables[ACTIVATE_COUPLE] = true;		// 커플 기능

	m_Variables[CAN_RECOUPLE] = false;			// 재혼(?) 이라기보단 다시 커플이 될 수 있는가

	m_Variables[GUILD_WAR_ACTIVE] = false;		// 길드전을 하는가?

	m_Variables[FREE_PLAY_OUSTERS_LEVEL] = 30;	// 아우스터스로 무료로 플레이할 수 있는 레벨

	m_Variables[CAN_APPLY_QUEST] = true;	// 퀘스트를 신청할 수 있는가
	m_Variables[SEND_QUEST_INFO] = false;	// 퀘스트 정보를 보내줘야 하는가
	m_Variables[CAN_BUY_SHOP] = true;

	m_Variables[PCROOM_EXP_BONUS] = 100;
	m_Variables[PCROOM_ITEM_RATIO_BONUS] = 100;

	m_Variables[MONEY_TRACE_LOG_LIMIT] = 5000000;

	m_Variables[PC_ROOM_LOTTO_EVENT] = false;	// 피시방 복권 이벤트 여부
	m_Variables[ACTIVE_FLAG_WAR] = false;	// 깃발뺏기 실행 여부

	m_Variables[KILL_DAEMONCTL] = false;	// daemonctl2 죽이는 거 여부
	m_Variables[EVENT_MOON_CARD] = false;	// daemonctl2 죽이는 거 여부

	m_Variables[FULL_MOON_CARD_RATIO] = 3000;
	m_Variables[HALF_MOON_CARD_RATIO] = 100;
	m_Variables[NEW_MOON_CARD_RATIO] = 200;
	m_Variables[OLD_MOON_CARD_RATIO] = 1000;

	m_Variables[ACTIVE_LEVEL_WAR] = 1000;
	m_Variables[RACE_WAR_HP_BONUS] = 0;
	m_Variables[HEAD_COUNT] = 0;

	m_Variables[HEAD_PRICE_BONUS] = 100;

	m_Variables[LEVEL_WAR_ZONE_FREE_ENTER] = false;
	m_Variables[PET_EXP_RATIO] = 100;

	m_Variables[EVENT_LUCKY_BAG] = false;
	m_Variables[GREEN_LUCKY_BAG_RATIO] = 150;
	m_Variables[BLUE_LUCKY_BAG_RATIO] = 1000;
	m_Variables[GOLD_LUCKY_BAG_RATIO] = 5000;
	m_Variables[RED_LUCKY_BAG_RATIO] = 20000;

	m_Variables[EVENT_GIFT_BOX] = false;
	m_Variables[RED_GIFT_BOX_RATIO] = 10000;
	m_Variables[BLUE_GIFT_BOX_RATIO] = 10000;
	m_Variables[GREEN_GIFT_BOX_RATIO] = 10000;
	m_Variables[YELLOW_GIFT_BOX_RATIO] = 10000;

	m_Variables[NETMARBLE_CARD_RATIO] = 0;
	m_Variables[NETMARBLE_CARD_EVENT] = 0;

	m_Variables[PET_FOOD_EVENT] = 0;

	m_Variables[HIGHER_PET_FOOD_RATIO] = 30;

	m_Variables[PET_FOOD_RATIO] = 125;
	m_Variables[RACE_PET_FOOD_RATIO] = 30;

	m_Variables[SLAYER_HP_RATIO] = 100;
	m_Variables[VAMPIRE_HP_RATIO] = 100;
	m_Variables[OUSTERS_HP_RATIO] = 100;
	m_Variables[MONSTER_HP_RATIO] = 100;
	m_Variables[MONSTER_EXP_RATIO] = 100;

	m_Variables[CLOVER_EVENT] = 0;
	m_Variables[CLOVER_RATIO] = 0;

	m_Variables[MONSTER_DAMAGE_RATIO] = 100;
	m_Variables[RACE_PET_QUEST] = 0;

	m_Variables[NICKNAME_PEN_EVENT] = 0;
	m_Variables[NICKNAME_PEN_RATIO] = 0;
	m_Variables[GOLD_MEDAL_RATIO] = 0;
	m_Variables[PET_DAY_EVENT] = 0;

	m_Variables[OLYMPIC_ITEM_RATIO] = 0;
	m_Variables[OLYMPIC_EVENT] = 0;

	m_Variables[CROWN_PRICE] = 0;
	m_Variables[CHOBO_EVENT] = 0;

	m_Variables[QUIT_GUILD_PENALTY_TERM] = 0;
	m_Variables[GUILD_UNION_MAX] = 0;

	m_Variables[LUCK_CHARM_RATIO] = 0;
	m_Variables[GDR_LAIR_PC_LIMIT] = 36;

	m_Variables[DONATION_EVENT_200501] = 0;

	m_Variables[EVENT_NEW_YEAR_2005] = 0;
	m_Variables[BOKJORY_RATIO] = 80000;
	m_Variables[EVENT_RED_RICE_CAKE_SOUP_RATIO] = 1000;
	m_Variables[EVENT_GREEN_RICE_CAKE_SOUP_RATIO] = 1000;
	m_Variables[EVENT_BLUE_RICE_CAKE_SOUP_RATIO] = 1000;
	m_Variables[EVENT_BLACK_RICE_CAKE_SOUP_RATIO] = 80000;
	m_Variables[EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO] = 80000;

	m_Variables[TIME_PERIOD_EXP_2X] = 0;

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	
	m_fRemoveAllGame = false;
	m_fEggDummyDB    = false;

#endif
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
VariableManager::~VariableManager() 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void VariableManager::init()
	
{
	__BEGIN_TRY

	m_VariableNames.clear();

	for (int i=0; i<VARIABLE_MAX; i++)
	{
		char str[256];
		strcpy(str, VariableType2String[i].c_str());
		strlwr(str);
		m_VariableNames[str] = (VariableType)i;
	}

	load();


	// 특별히 다른 초기값을 설정하는 경우
	setVariable( AUTO_START_RACE_WAR, g_pConfig->getPropertyInt("ActiveRaceWar") );
	setVariable( GUILD_WAR_ACTIVE, g_pConfig->getPropertyInt("ActiveGuildWar") );
	setVariable( ACTIVE_FLAG_WAR, g_pConfig->getPropertyInt("ActiveFlagWar") );
	setVariable( ACTIVE_LEVEL_WAR, g_pConfig->getPropertyInt("ActiveLevelWar") );
	setVariable( HEAD_COUNT, g_pConfig->getPropertyInt("HeadCount") );
	setVariable( KILL_DAEMONCTL, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_HOLY_LAND_WAR ) )
		setVariable( WAR_ACTIVE, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_GUILD_WAR ) )
		setVariable( GUILD_WAR_ACTIVE, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_RACE_WAR ) )
		setVariable( AUTO_START_RACE_WAR, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_FLAG_WAR ) )
		setVariable( ACTIVE_FLAG_WAR, 0 );

	if ( !SystemAvailabilitiesManager::getInstance()->isAvailable( SystemAvailabilitiesManager::SYSTEM_MASTER_LAIR ) )
		setVariable( ACTIVE_MASTER_LAIR, 0 );

	__END_CATCH
}


void VariableManager::load()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(attrID) FROM AttrInfo");

		if (pResult->getRowCount() <= 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("VariableManager::load(): attrID MAX값을 구할 수 없습니다.");
		}

		pResult->next();
		int maxAttr = pResult->getInt(1);
		m_Variables.clear();
		m_Variables.resize( max((maxAttr+1), (int)VARIABLE_MAX) );

		pResult = pStmt->executeQuery("SELECT attrID, attr1, attr2 FROM AttrInfo");

		if(pResult->getRowCount() <= 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("VariableManager::load(): 값이 하나도 존재하지 않습니다");
		}

		while(pResult->next())
		{
			VariableType    attrID = (VariableType)pResult->getInt(1);
			int    			attr1  = pResult->getInt(2);
			//int    			attr2  = pResult->getInt(3);


			setVariable(attrID, attr1);
			cout << toString(attrID).c_str() << endl;
		}
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

VariableType     
VariableManager::getVariableType(const string& variableName) const
{
	char str[256];
	strcpy(str, variableName.c_str());
	strlwr(str);

	VARIABLE_NAME::const_iterator itr = m_VariableNames.find( str );

	if (itr==m_VariableNames.end())
	{
		return VARIABLE_MAX;
	}

	return itr->second;
}

void 
VariableManager::setVariable(VariableType vt, const string& strVariable)
{
	int value = atoi(strVariable.c_str());

	if (value==0)
	{
		if (strcasecmp(strVariable.c_str(), "on")==0)
		{
			setVariable(vt, 1);
		}
		else if (strcasecmp(strVariable.c_str(), "off")==0)
		{
			setVariable(vt, 0);
		}
		else
		{
			setVariable(vt, 0);
		}
	}
	else
	{
		setVariable(vt, value);
	}
}

void 
VariableManager::setVariable(VariableType vt, int value)
{ 
	try {

		// RACE_WAR_TIMEBAND 범위 체크
		if ( vt == RACE_WAR_TIMEBAND )
		{
			if ( value < 0 || value > 3 )
				return;
		}

		m_Variables[vt] = value; 

		Statement* pStmt = NULL;
		//Result*    pResult = NULL;
		
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("UPDATE AttrInfo SET attr1=%d WHERE attrID=%d", value, (int)vt);

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
		
	} catch (Throwable& t){
		filelog("variableManagerError.log", "%s", t.toString().c_str());
	}
}

string   
VariableManager::toString(VariableType vt) const
{
	StringStream msg;

	int attr1 = m_Variables[vt];

	switch (vt)
	{
		case EVENT_ACTIVE:
			msg << "Event ACTIVE: " << attr1;
			break;
		case EVENT_RATIO:
			msg << "Event RATIO: " << attr1;
			break;
		case ITEM_PROBE_RATIO:
			msg << "Item PROBE RATIO:  " << attr1;
			break;
		case EXP_RATIO:
			msg << "EXP RATIO: " << attr1;
			break;
		case COMBAT_BONUS_TIME:
			msg << "COMBAT BONUM TIME: " << attr1;
			break;

		case COMBAT_SLAYER_HP_BONUS_RATIO:
			msg << "COMBAT SLAYER HP BONUS RATIO: " << attr1;
			break;

		case COMBAT_VAMPIRE_HP_BONUS_RATIO:
			msg << "COMBAT VAMPIREE  HP BONUS RATIO: " << attr1;
			break;

		case PREMIUM_EXP_BONUS_PERCENT:
			msg << "PREMIUM EXP BONUS PERCENT: " << attr1;
			break;

		case PREMIUM_ITEM_PROBE_PERCENT:
			msg << "PREMIUM ITEM PROBE PERCENT: " << attr1;
			break;

		case ZONE_GROUP_BALANCING_MINUTE:
			msg << "ZoneGroupBalancing minute: " << attr1 << "분";
			break;

		case GAMBLE_ITEM_TYPE_RATIO:
			msg << "GAMBLE_ITEM_TYPE_RATIO: " << attr1;
			break;

		case GAMBLE_ITEM_OPTION_RATIO:
			msg << "GAMBLE_ITEM_OPTION_RATIO: " << attr1;
			break;

		case SUMMON_MOTORCYCLE:
			msg << "SUMMON_MOTORCYCLE: " << (attr1? "ON":"OFF");
			break;

		case ENEMY_LIMIT_TIME:
			msg << "ENEMY_LIMIT_TIME: " << attr1 << "초"; 
			break;

		case COMBAT_SLAYER_DAMAGE_BONUS:
			msg << "COMBAT_SLAYER_DAMAGE_BONUS: " << attr1;
			break;

		case COMBAT_VAMPIRE_DAMAGE_BONUS:
			msg << "COMBAT_VAMPIRE_DAMAGE_BONUS: " << attr1;
			break;

		case RARE_ITEM_RATIO:
			msg << "RARE_ITEM_RATIO: " << attr1;
			break;

		case UNIQUE_ITEM_RATIO:
			msg << "UNIQUE_ITEM_RATIO: " << attr1; 
			break;

		case ACTIVE_MASTER_LAIR:
			msg << "ACTIVE_MASTER_LAIR: " << (attr1? "ON":"OFF");
			break;

		case RETRY_MASTER_LAIR:
			msg << "RETRY_MASTER_LAIR: " << (attr1? "ON":"OFF");
			break;


		case HARVEST_FESTIVAL_ITEM_RATIO:
			if (attr1==0)
			{
				msg << "HARVEST_FESTIVAL_ITEM_RATIO: 0";
			}
			else
			{
				msg << "HARVEST_FESTIVAL_ITEM_RATIO: 1/" << attr1;
			}
			break;

		case MASTER_BLOOD_DRAIN_START_HP:
			msg << "MASTER_BLOOD_DRAIN_START_HP: " << attr1 << "%";
			break;
		case MASTER_BLOOD_DRAIN_START_BD:
			msg << "MASTER_BLOOD_DRAIN_START_BD: " << attr1 << "%";
			break;
		case MASTER_BLOOD_DRAIN_END_HP:
			msg << "MASTER_BLOOD_DRAIN_END_HP: " << attr1 << "%";
			break;
		case MASTER_BLOOD_DRAIN_END_BD:
			msg << "MASTER_BLOOD_DRAIN_END_BD: " << attr1 << "%";
			break;

		case ACTIVE_CHIEF_MONSTER:
			msg << "ACTIVE_CHIEF_MONSTER: " << (attr1? "ON":"OFF");
			break;
		case CHIEF_MONSTER_RARE_ITEM_RATIO:
			msg << "CHIEF_MONSTER_RARE_ITEM_RATIO: " << attr1 << "%";
			break;

		case NEWBIE_TRANSPORT_TO_GUILD:
			msg << "NEWBIE_TRANSPORT_TO_GUILD: " << (attr1? "ON":"OFF");
			break;

		case FREE_PLAY_SLAYER_DOMAIN_SUM:
			msg << "FREE_PLAY_SLAYER_DOMAIN_SUM: " << attr1;
			break;

		case FREE_PLAY_VAMPIRE_LEVEL:
			msg << "FREE_PLAY_VAMPIRE_LEVEL: " << attr1;
			break;

		case LOG_INCOMING_CONNECTION:
			msg << "LOG_INCOMING_CONNECTION: " << (attr1? "ON":"OFF");
			break;

		case CHRISTMAS_FIRE_CRACKER_RATIO:
			msg << "CHRISTMAS_FIRE_CRACKER_RATIO: " << attr1 << " / 10000 ";
			break;

		case CHRISTMAS_TREE_PART_RATIO:
			msg << "CHRISTMAS_TREE_PART_RATIO: " << attr1 << " / 10000 ";
			break;

		case CHRISTMAS_GIFT_BOX_RATIO :
			msg << "christmas_gift_box_ratio: " << attr1 << " / 10000 ";
			break;

		case CHRISTMAS_TREE_DECAY_TIME :
			msg << "CHRISTMAS_TREE_DECAY_TIME: " << attr1/600 << "분";
			break;

		case MASTER_LAIR_PLAYER_NUM :
			msg << "MASTER_LAIR_PLAYER_NUM: " << attr1 << "명";
			break;

		case RANK_EXP_GAIN_PERCENT :
			msg << "RANK_EXP_GAIN_PERCENT: " << attr1 << "%";
			break;

		case ITEM_LUCK_PERCENT :
			msg << "ITEM_LUCK_PERCENT: " << attr1 << "%";
			break;

		case LOTTO_ITEM_RATIO :
			msg << "LOTTO_ITEM_RATIO: " << attr1 << " / 10000";
			break;

		case LOTTO_ITEM_BONUS_NUM:
			msg << "LOTTO_ITEM_BONUS_NUM: " << attr1;
			break;

		case LOTTO_SKULL_RATIO :
			msg << "LOTTO_SKULL_RATIO: " << attr1 << " / 10000";
			break;

		case PREMIUM_HALF_EVENT :
			msg << "PREMIUM_HALF_EVENT: " << (attr1?"ON":"OFF");
			break;

		case COMMON_CASTLE_ENTRANCE_FEE :
			msg << "COMMON_CASTLE_ENTRANCE_FEE: " << attr1;
			break;

		case GUILD_CASTLE_ENTRANCE_FEE :
			msg << "GUILD_CASTLE_ENTRANCE_FEE: " << attr1;
			break;

		case COMMON_CASTLE_ITEM_TAX_RATIO :
			msg << "COMMON_CASTLE_ITEM_TAX_RATIO: " << attr1;
			break;

		case GUILD_CASTLE_ITEM_TAX_RATIO :
			msg << "GUILD_CASTLE_ITEM_TAX_RATIO: " << attr1;
			break;

		case WAR_REGISTRATION_FEE :
			msg << "WAR_REGISTRATION_FEE: " << attr1;
			break;

		case GUILD_WAR_TIME :
			msg << "GUILD_WAR_TIME : " << attr1 << " 초 == " << attr1/60 << "분";
			break;

		case RACE_WAR_TIME :
			msg << "RACE_WAR_TIME :" << attr1 << " 초 == " << attr1/60 << "분";
			break;

		case WAR_PERIOD_WEEK :
			msg << "WAR_PERIOD_WEEK :" << (attr1? "주 단위":"일 단위");
			break;

		case WAR_ACTIVE :
			msg << "WAR_ACTIVE :" << (attr1?"ON":"OFF");
			break;

		case RACE_WAR_TIMEBAND:
			msg << "RACE_WAR_TIMEBAND:";
			if ( attr1 == 0 )
				msg << "새벽";
			else if ( attr1 == 1 )
				msg << "낮";
			else if ( attr1 == 2 )
				msg << "저녁";
			else if ( attr1 == 3 )
				msg << "밤";
			else
				msg << "알 수 없음";
			break;

		case AUTO_START_RACE_WAR:
			msg << "AUTO_START_RACE_WAR:" << (attr1?"ON":"OFF");
			break;

		case ACTIVE_RACE_WAR_LIMITER :
			msg << "ACTIVE_RACE_WAR_LIMITER :" << (attr1?"ON":"OFF");
			break;

		case CHIEF_ITEM_BONUS_NUM:
			msg << "CHIEF_ITEM_BONUS_NUM:" << attr1 << " 개";
			break;

		case ACTIVE_EVENT_GIVE_ITEM :
			msg << "ACTIVE_EVENT_GIVE_ITEM :" << (attr1?"ON":"OFF");
			break;

		case VAMPIRE_REDISTRIBUTE_ATTR_PRICE:
			msg << "VAMPIRE_REDISTRIBUTE_ATTR_PRICE:" << attr1;
			break;

		case ACTIVATE_COUPLE:
			msg << "ACTIVATE_COUPLE:" << (attr1?"ON":"OFF");
			break;

		case CAN_RECOUPLE:
			msg << "CAN_RECOUPLE:" << (attr1?"Y":"N");
			break;

		case GUILD_WAR_ACTIVE:
			msg << "GUILD_WAR_ACTIVE:" << (attr1?"Yes":"No");
			break;

		case FREE_PLAY_OUSTERS_LEVEL:
			msg << "FREE_PLAY_OUSTERS_LEVEL: " << attr1;
			break;

		case CAN_APPLY_QUEST:
			msg << "CAN_APPLY_QUEST:" << (attr1?"Yes":"No");
			break;

		case SEND_QUEST_INFO:
			msg << "SEND_QUEST_INFO:" << (attr1?"Yes":"No");
			break;

		case CAN_BUY_SHOP:
			msg << "CAN_BUY_SHOP:" << (attr1?"Yes":"No");
			break;
		case PCROOM_EXP_BONUS:
			msg << "PCROOM_EXP_BONUS:" << attr1;
			break;
		case PCROOM_ITEM_RATIO_BONUS:
			msg << "PCROOM_ITEM_RATIO_BONUS:" << attr1;
			break;
		case MONEY_TRACE_LOG_LIMIT:
			msg << "MONEY_TRACE_LOG_LIMIT:" << attr1;
			break;
		case PC_ROOM_LOTTO_EVENT:
			msg << "피씨방 복권 이벤트: " << attr1;
			break;
		case ACTIVE_FLAG_WAR:
			msg << "깃발뺏기 게임 실행: " << (attr1?"yes":"no");
			break;
		case KILL_DAEMONCTL:
			msg << "DAEMONCTL 죽이는 여부: " << (attr1?"yes":"no");
			break;

		case EVENT_MOON_CARD:
			if ( attr1 )
				msg << "달카드 이벤트가 진행중입니다.";
			else
				msg << "달카드 이벤트를 중단했습니다.";
			break;

		case FULL_MOON_CARD_RATIO:
			msg << "보름달 카드 나올 확률: 1 / " << attr1;
			break;

		case HALF_MOON_CARD_RATIO:
			msg << "반달 카드 나올 확률: 1 / " << attr1;
			break;

		case NEW_MOON_CARD_RATIO:
			msg << "NEW_MOON_CARD_RATIO:" << attr1;
			break;

		case OLD_MOON_CARD_RATIO:
			msg << "그믐달(없는) 카드 나올 확률: 1 / " << attr1;
			break;

		case ACTIVE_LEVEL_WAR:
			msg << "레벨별 전쟁 진행 여부: " << (attr1?"yes":"no");
			break;

		case RACE_WAR_HP_BONUS:
			msg << "종족전시 HP 보너스: " << attr1;
			break;

		case HEAD_COUNT:
			msg << "머리 갯수 카운트하기: " << (attr1?"yes":"no");
			break;

		case HEAD_PRICE_BONUS:
			msg << "HEAD_PRICE_BONUS:" << attr1;
			break;

		case LEVEL_WAR_ZONE_FREE_ENTER:
			msg << "LEVEL_WAR_ZONE_FREE_ENTER:" << (attr1?"yes":"no");
			break;

		case PET_EXP_RATIO:
			msg << "펫 경험치 비율 : " << attr1;
			break;

		case EVENT_LUCKY_BAG:
			if ( attr1 )
				msg << "복주머니 이벤트가 진행중입니다.";
			else
				msg << "복주머니 이벤트가 진행중이지 않습니다.";
			break;

		case GREEN_LUCKY_BAG_RATIO:
			msg << "초록색 복주머니 나올 확률 : 1 / " << attr1;
			break;

		case BLUE_LUCKY_BAG_RATIO:
			msg << "파란색 복주머니 나올 확률 : 1 / " << attr1;
			break;

		case GOLD_LUCKY_BAG_RATIO:
			msg << "황금색 복주머니 나올 확률 : 1 / " << attr1;
			break;

		case RED_LUCKY_BAG_RATIO:
			msg << "빨간색 복주머니 나올 확률 : 1 / " << attr1;
			break;

		case EVENT_GIFT_BOX:
			if ( attr1 )
				msg << "선물상자 교환 이벤트가 진행중입니다.";
			else
				msg << "선물상자 교환 이벤트가 진행중이지 않습니다.";
			break;

		case RED_GIFT_BOX_RATIO:
			msg << "빨간색 선물상자 나올 확률 : 1 / " << attr1;
			break;

		case BLUE_GIFT_BOX_RATIO:
			msg << "파란색 선물상자 나올 확률 : 1 / " << attr1;
			break;

		case GREEN_GIFT_BOX_RATIO:
			msg << "초록색 선물상자 나올 확률 : 1 / " << attr1;
			break;

		case YELLOW_GIFT_BOX_RATIO:
			msg << "YELLOW_GIFT_BOX_RATIO:" << attr1;
			break;

		case NETMARBLE_CARD_RATIO:
			msg << "넷마블 카드 나올 확률 : " << attr1 << " / 100000";
			break;

		case NETMARBLE_CARD_EVENT:
			msg << "넷마블 카드 이벤트 : " << ((attr1)?"Yes":"No");
			break;

		case PREMIUM_TRIAL_EVENT:
			msg << "프리미엄 체험 이벤트 : " << ((attr1)?"Yes":"No");
			break;

		case PET_FOOD_EVENT:
			msg << "펫 먹이 이벤트 : " << ((attr1)?"Yes":"No");
			break;

		case HIGHER_PET_FOOD_RATIO:
			msg << "고단계 펫 먹이 확률 : " << attr1 << "%";
			break;

		case RACE_PET_FOOD_RATIO:
			msg << "RACE_PET_FOOD_RATIO:" << attr1 << "%";
			break;

		case PET_FOOD_RATIO:
			msg << "PET_FOOD_RATIO:" << attr1 << " / 100000";
			break;

		case REVIVAL_SET_RATIO:
			msg << "리바이벌 셋 확률 : " << attr1 << "%";
			break;

		case TODAY_IS_HOLYDAY:
			if ( attr1 ) msg << "오늘은 국경일 입니다.";
			else msg << "오늘은 국경일이 아닙니다.";
			break;

		case SLAYER_HP_RATIO:
			msg << "슬레이어 HP비율 : " << attr1 << "%";
			break;
		case VAMPIRE_HP_RATIO:
			msg << "뱀파이어 HP비율 : " << attr1 << "%";
			break;
		case OUSTERS_HP_RATIO:
			msg << "아우스터즈 HP비율 : " << attr1 << "%";
			break;
		case MONSTER_HP_RATIO:
			msg << "몬스터 HP비율 : " << attr1 << "%";
			break;

		case MONSTER_EXP_RATIO:
			msg << "몬스터 EXP비율 : " << attr1 << "%";
			break;

		case CLOVER_EVENT:
			msg << "네잎클로버 이벤트 : " << ((attr1)?"on":"off");
			break;

		case CLOVER_RATIO:
			msg << "네잎클로버 확률 : " << attr1 << "/100000";
			break;

		case MONSTER_DAMAGE_RATIO:
			msg << "몬스터 Damage 비율 : " << attr1 << "%";
			break;

		case RACE_PET_QUEST:
			msg << "2차 펫 퀘스트 : " << ((attr1)?"on":"off");
			break;

		case NICKNAME_PEN_EVENT:
			msg << "네이밍펜 이벤트 : " << ((attr1)?"on":"off");
			break;

		case NICKNAME_PEN_RATIO:
			msg << "네이밍펜 확률 : " << attr1 << "/100000";
			break;

		case GOLD_MEDAL_RATIO:
			msg << "금메달 확률 : " << attr1 << "/100000";
			break;

		case PET_DAY_EVENT:
			msg << "복날 이벤트 : " << ((attr1)?"on":"off");
			break;

		case OLYMPIC_ITEM_RATIO:
			msg << "올림픽 이벤트 아이템 루팅 확률 : " << attr1 << "/100000";
			break;

		case OLYMPIC_EVENT:
			msg << "다덴 올림픽 이벤트 : " << ((attr1)?"on":"off");
			break;

		case CROWN_PRICE:
			msg << "월계관 가격 : " << attr1;
			break;

		case CHOBO_EVENT:
			msg << "초보자 이벤트 : " << ((attr1)?"on":"off");
			break;

		case QUIT_GUILD_PENALTY_TERM:
			msg << "길드 탈퇴시 재가입 불가 기간 : " << attr1;
			break;

		case GUILD_UNION_MAX:
			msg << "GUILD_UNION_MAX:" << attr1;
			break;

		case LUCK_CHARM_RATIO:
			msg << "LUCK_CHARM_RATIO:" << attr1;
			break;

		case GDR_LAIR_PC_LIMIT:
			msg << "GDR_LAIR_PC_LIMIT:" << attr1;
			break;

		case DONATION_EVENT_200501:
			msg << "DONATION_EVENT_200501:" << ((attr1)?"on":"off");
			break;

		case EVENT_NEW_YEAR_2005:
			msg << "EVENT_NEW_YEAR_2005: " << ((attr1)?"on":"off");
			break;

		case BOKJORY_RATIO:
			msg << "BOKJORY_RATIO:" << attr1;
			break;
			
		case EVENT_RED_RICE_CAKE_SOUP_RATIO:
			msg << "EVENT_RED_RICE_CAKE_SOUP_RATIO:" << attr1;
			break;
			
		case EVENT_GREEN_RICE_CAKE_SOUP_RATIO:
			msg << "EVENT_GREEN_RICE_CAKE_SOUP_RATIO:" << attr1;
			break;
			
		case EVENT_BLUE_RICE_CAKE_SOUP_RATIO:
			msg << "EVENT_BLUE_RICE_CAKE_SOUP_RATIO:" << attr1;
			break;
			
		case EVENT_BLACK_RICE_CAKE_SOUP_RATIO:
			msg << "EVENT_BLACK_RICE_CAKE_SOUP_RATIO:" << attr1;
			break;
			
		case EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO:
			msg << "EVENT_MUGWORT_RICE_CAKE_SOUP_RATIO:" << attr1;
			break;

		case TIME_PERIOD_EXP_2X:
			msg << "TIME_PERIOD_EXP_2X:" << ((attr1)?"on":"off");
			break;

		default:
                       if(vt<VARIABLE_MAX) //add by viva
                        msg << VariableType2String[vt] << ": " << attr1;
//			msg << VariableType2String[vt] << ": " << attr1;
			break;
	}

	return msg.toString();
}

VariableManager* g_pVariableManager = NULL;

