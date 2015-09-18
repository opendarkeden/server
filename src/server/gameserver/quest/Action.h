//////////////////////////////////////////////////////////////////////////////
// Filename    : Action.h
// Written By  : 
// Description :
// 트리거의 조건이 만족할 경우 실행되어야 하는 액션을 나타내는 클래스
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_H__
#define __ACTION_H__

#include "Types.h"
#include "Exception.h"
#include "PropertyBuffer.h"

//////////////////////////////////////////////////////////////////////////////
// class Action
//////////////////////////////////////////////////////////////////////////////

class Creature;

class Action 
{
public:

	enum ActionTypes 
	{
		ACTION_SET_POSITION,             // 위치를 지정한다.
		ACTION_WANDER,                   // 일정 범위를 방황한다.
		ACTION_SAY,                      // 일정 스크립트를 말한다.
		ACTION_RANDOM_SAY,               // 일정 스크립트를 브로드캐스팅한다.
		ACTION_ASK,                      // 플레이어에게 질문을 한다.
		ACTION_QUIT_DIALOGUE,            // 클라이언트로 하여금 대화창을 닫게 한다.
		ACTION_PREPARE_SHOP,             // 상점을 준비한다.
		ACTION_SELL,                     // 플레이어에게 아이템을 판다.
		ACTION_BUY,                      // 플레이어로부터 물건을 사들인다.
		ACTION_REGEN_SHOP,               // 상점 안에 있는 아이템을 재정리한다.
		ACTION_PREPARE_TEACH,            // 기술을 가르칠 준비를 한다.
		ACTION_TEACH_SKILL,              // 플레이어에게 기술을 가르쳐준다.
		ACTION_HEAL,                     // 플레이어를 치료해준다.
		ACTION_REDEEM_MOTORCYCLE,        // 모터사이클을 반환해준다.
		ACTION_SEARCH_MOTORCYCLE,        // 플레이어의 오토바이 위치를 말해준다.
		ACTION_REPAIR,                   // 플레이어의 아이템을 수리해준다.
		ACTION_STASH_SELL,               // 보관함 사기 인터페이스를 열도록 한다.
		ACTION_STASH_OPEN,               // 보관함 인터페이스를 열도록 한다.
		ACTION_RESTORE,                  // 뱀파이어를 슬레이어로 변환해 준다.
		ACTION_SET_RESURRECT_ZONE,       // 부활 위치를 지정한다.
		ACTION_SILVER_COATING,           // 아이템에다 은 도금을 해준다.
		ACTION_CREATE_GUILD,             // 길드 생성 인터페이스를 열게 한다.
		ACTION_DESTROY_GUILD,            // 길드 해체 인터페이스를 열게 한다.
		ACTION_TUTORIAL,                 // 튜토리얼 인터페이스를 열게 한다.
		ACTION_GIVE_NEWBIE_ITEM,         // 초보자용 아이템 선택 인터페이스를 열게 한다.
		ACTION_ACTIVATE_PORTAL,          // 포탈을 작동시킨다.
		ACTION_TURN_ON_FLAG,             // 플래그를 켜고 저장한다.
		ACTION_TURN_OFF_FLAG,            // 플래그를 끄고 저장한다.
		ACTION_SYSTEM_MESSAGE,           // 시스템 메시지를 날린다.
		ACTION_TAKE_DONATION,            // 기부를 받는다.
		ACTION_CALL_HELICOPTER,          // 헬기 인터페이스를 열게 한다.
		ACTION_REGEN_EVENT_SHOP,         // 이벤트용 상점을 갱신한다.
		ACTION_SAY_DYNAMIC,              // 일정 스크립트를 말한다.
		ACTION_ASK_DYNAMIC,              // 플레이어에게 질문을 한다.
		ACTION_GIVE_SPECIAL_EVENT_ITEM,  // 
		ACTION_REDISTRIBUTE_ATTR,        // 
		ACTION_GIVE_GARBAGE_ITEM,        // 가비지 아이템을 준다.

		//ACTION_TALK ,
		//ACTION_RANDOM_TALK ,
		//ACTION_GIVE ,
		//ACTION_TAKE ,
		//ACTION_DROP ,
		//ACTION_CREATE_ITEM ,
		//ACTION_DESTROY_ITEM ,
		//ACTION_SET_ATTRIBUTE ,
		//ACTION_SET_DISCOUNT_RATE ,
		//ACTION_DIE ,
		//ACTION_USE_SKILL ,
		//ACTION_USE_ITEM ,
		//ACTION_REMOVE_QUEST ,
		//ACTION_AFTER ,

		// Monster AI specific actions
		ACTION_ATTACK ,	
		ACTION_RETREAT ,	
		ACTION_MOVE ,
		ACTION_ATTACK_MOVE ,	
		ACTION_STOP ,
		ACTION_HOLD_POSITION ,
		ACTION_PATROL ,

		ACTION_TRADE_EVENT_ITEM,
		ACTION_SHOW_GUILD_DIALOG,

		ACTION_TRADE_LAIR_ITEM,

		ACTION_SIMPLE_QUEST_LIST,
		ACTION_SIMPLE_QUEST_COMPLETE,
		ACTION_SIMPLE_QUEST_REGEN,

		ACTION_TRADE_GIFT_BOX,

		ACTION_GIVE_TEST_SERVER_REWARD,

		// 성에 들어가는 Action
		// 2003. 1.20. by bezz,Sequoia
		ACTION_ENTER_CASTLE_WITH_FEE,

		// 성에 쌓여있는 세금의 잔액을 보여준다.
		ACTION_SHOW_TAX_BALANCE,

		ACTION_ASK_VARIABLE,

		// 전쟁 신청 관련 액션들
		ACTION_WAR_REGISTRATION,
		ACTION_SHOW_WAR_SCHEDULE,

		// 종족 전쟁 신청
		ACTION_JOIN_RACE_WAR,

		// 이벤트 선물 아이템
		ACTION_GIVE_EVENT_ITEM,				// 캐릭별로 줄 때
		ACTION_GIVE_ACCOUNT_EVENT_ITEM,		// 계정별로 줄 때

		// 커플 매니저 관련 초기화 액션
		ACTION_INIT_PARTNER_WAITING_MANAGER,
		ACTION_WAIT_FOR_MEET_COUPLE,
		ACTION_WAIT_FOR_APART_COUPLE,
		ACTION_ACCEPT_COUPLE_REQUEST,
		ACTION_ACCEPT_APART_COUPLE,

		ACTION_FORCE_APART_COUPLE,

		ACTION_ENTER_PK_ZONE,
		ACTION_WARP_TO_RESURRECT_POSITION,

		ACTION_SELECT_QUEST,
		ACTION_QUEST_REWARD,

		ACTION_WARP_TO_NOVICE_ZONE,
		ACTION_CANCEL_QUEST,

		ACTION_INIT_SIMPLE_QUEST,
		ACTION_WANDER_ZONE,

		ACTION_INIT_EVENT_QUEST,
		ACTION_ASK_BY_QUEST_LEVEL,
		ACTION_GIVE_EVENT_QUEST,
		ACTION_ADVANCE_EVENT_QUEST,
		ACTION_REWARD_EVENT_QUEST,
		ACTION_CANCEL_EVENT_QUEST_SCRIPT,
		ACTION_GIVE_LOTTO,
		ACTION_GIVE_EVENT_QUEST_SCRIPT,
		ACTION_START_EVENT_QUEST,
		ACTION_WARP_IN_ZONE,
		ACTION_EVENT_MEET,
		ACTION_GIVE_FINAL_LOTTO_SCRIPT,
		ACTION_GIVE_QUEST_ITEM,
		ACTION_TAKE_OUT_GOODS,
		ACTION_CLEAR_RANK_BONUS,
		ACTION_CONTRACT_GNOMES_HORN,
		ACTION_DOWN_SKILL,
		ACTION_MINI_GAME,
		ACTION_GIVE_ITEM,
		ACTION_ACTIVATE_MAZE_EXIT,
		ACTION_ACTIVATE_MAZE_ENTER,
		ACTION_ACTIVATE_MAZE_RETURN,

		ACTION_SYSTEM_MESSAGE_PER_RACE,           // 시스템 메시지를 날린다.

		ACTION_WARP_LEVEL_WAR_ZONE,

		ACTION_CHECK_PARTNER_NAME,				// 파트너 이름 확인

		ACTION_START_PET_QUEST,					// 2차 펫 퀘스트를 시작한다.

		ACTION_PET_WITHDRAW,					// 펫 찾을래요
		ACTION_PET_DEPOSIT,						// 펫 맡길래요

		ACTION_ENTER_EVENT_ZONE,				// 이벤트 존으로 들어갈래요.
		ACTION_ENTER_GDR_LAIR,					// 일루젼스 웨이에서 질드레 레어로 들어가기

		ACTION_TRADE_GQUEST_EVENT_ITEM,			// 이벤트 퀘스트 아이템

		ACTION_ENTER_SIEGE,						// 공성전 참가(공성 지역으로 이동)

		ACTION_REGISTER_SIEGE,					// 공성 신청
		ACTION_REGISTER_REINFORCE,				// 수비측 참전 신청
		ACTION_ACCEPT_REINFORCE,				// 수비측 참전 신청 수락
		ACTION_DENY_REINFORCE,					// 수비측 참전 신청 거부

		ACTION_RECALL_SIEGE,					// 공성전에 길드원 데려오기
		ACTION_SELECT_BLOOD_BIBLE,				// 피의 성서 대여
		ACTION_CLEAR_BLOOD_BIBLE,				// 피의 성서 제거

		ACTION_MODIFY_TAX_RATIO,				// 세율 조절
		ACTION_SWAP_ADVANCEMENT_ITEM,			// 승직 아이템 교환

		ACTION_SHOW_DONATION_DIALOG,			// 기부창 보여주기
		ACTION_ENTER_QUEST_ZONE,				// DynamicZone 입장
		ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG,	// 이벤트 아이템 받기 확인창
		ACTION_GIVE_COMMON_EVENT_ITEM,			// 공용 이벤트 아이템 주기

		ACTION_MAX
	};

public:
	virtual ~Action() {}
	virtual ActionType_t getActionType() const throw() = 0;
	virtual void read(PropertyBuffer & buffer) throw(Error) = 0;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error) = 0;	
	virtual string toString() const throw() = 0;

};

#endif
