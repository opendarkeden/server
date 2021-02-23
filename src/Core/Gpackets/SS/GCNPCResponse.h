//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCResponse.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_RESPONSE_H__
#define __GC_NPC_RESPONSE_H__

#include "Packet.h"
#include "PacketFactory.h"

enum 
{
	// 클라이언트로 하여금 적당한 인터페이스를 열도록 하는 코드
	NPC_RESPONSE_INTERFACE_REPAIR = 0,
	NPC_RESPONSE_INTERFACE_STASHOPEN,	// 1
	NPC_RESPONSE_INTERFACE_SILVER_COATING,	// 2
	NPC_RESPONSE_INTERFACE_CREATE_GUILD,	// 3
	NPC_RESPONSE_INTERFACE_DESTROY_GUILD,	// 4
	NPC_RESPONSE_INTERFACE_NEWBIE_ITEM,	// 5
	NPC_RESPONSE_INTERFACE_TUTORIAL_COMPUTER,	// 6
	NPC_RESPONSE_INTERFACE_TUTORIAL_BRIEFING,	// 7
	NPC_RESPONSE_INTERFACE_TUTORIAL_BOOKCASE,	// 8
	NPC_RESPONSE_INTERFACE_HELICOPTER,	// 9

	// ...
	NPC_RESPONSE_QUIT_DIALOGUE,	// 10
	NPC_RESPONSE_HEAL,	// 11

	// 클라이언트의 패킷에 대한 응답 코드
	NPC_RESPONSE_REPAIR_OK,	// 12
	NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST,	// 13
	NPC_RESPONSE_REPAIR_FAIL_ITEM_TYPE,	// 14
	NPC_RESPONSE_REPAIR_FAIL_MONEY,	// 15

	NPC_RESPONSE_STASH_SELL_OK,	// 16
	NPC_RESPONSE_STASH_SELL_FAIL_MAX,	// 17
	NPC_RESPONSE_STASH_SELL_FAIL_MONEY,	// 18

	NPC_RESPONSE_SILVER_COATING_OK,	// 19
	NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_NOT_EXIST, 	// 20
	NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_TYPE,	// 21
	NPC_RESPONSE_SILVER_COATING_FAIL_MONEY,	// 22

	NPC_RESPONSE_DONATION_OK,	// 23
	NPC_RESPONSE_DONATION_FAIL_MONEY,	// 24

	// 임시용 아이디
	// 월드컵 패치에서 축구공을 줄을 방법이 없는 관계로 NPC Response를 사용해서 줄인다.
	NPC_RESPONSE_DECREASE_BALL,	// 25

	// 길드 관련
	NPC_RESPONSE_TEAM_REGIST_FAIL_ALREADY_JOIN,			// 어디 한번 볼까? 자네는 이미 <team_name> 팀 소속이라고 나와 있군	// 26
	NPC_RESPONSE_TEAM_REGIST_FAIL_QUIT_TIMEOUT,			// 자네는 다른 팀을 탈퇴한지 얼마 되지 않았군. 조금 더 신중하게 생각하고 행동하게	// 27
	NPC_RESPONSE_TEAM_REGIST_FAIL_CANCEL_TIMEOUT,		// 자네는 팀을 취소 당한 지 얼마 되지 않았군. 등록 조건에 부합하도록 자신을 좀 더 기르고 오게. 좀 더 신중하게 기회를 엿보도록 하게	// 28
	NPC_RESPONSE_TEAM_REGIST_FAIL_LEVEL,				// 훌륭하지만 리더로써의 자질은 좀 부족한 것 같군. 실력을 닦고 오게나	// 29
	NPC_RESPONSE_TEAM_REGIST_FAIL_MONEY,				// 팀을 만들려면 많은 돈이 필요하다네. 자네는 돈이 없어 보이는군...	// 30
	NPC_RESPONSE_TEAM_REGIST_FAIL_FAME,					// <player_name>이라.. 난 아직 그런 이름은 들어보지도 못했다네. 그건 자네가 풋내기라는 것을 의미하지. 실력을 닦고 다시 찾아오게나	// 31
	NPC_RESPONSE_TEAM_REGIST_FAIL_NAME,					// 팀 이름이 이미 쓰이고 있군, 다른 이름을 생각해 보게	// 32
	NPC_RESPONSE_TEAM_REGIST_FAIL_DENY,					// 거부되었습니다.	// 33

	NPC_RESPONSE_TEAM_STARTING_FAIL_ALREADY_JOIN,		// 당신은 이미 다른 팀에 가입되어 있습니다.	// 34
	NPC_RESPONSE_TEAM_STARTING_FAIL_QUIT_TIMEOUT,		// 자네는 다른 팀을 탈퇴한지 얼마 되지 않았군. 조금 더 신중하게 생각하고 행동하게	// 35
	NPC_RESPONSE_TEAM_STARTING_FAIL_CANCEL_TIMEOUT,		// 자네는 팀을 취소 당한 지 얼마 되지 않았군. 조건에 부합하도록 자신을 좀 더 기르고 오게. 좀 더 신중하게 기회를 엿보도록 하게	// 36
	NPC_RESPONSE_TEAM_STARTING_FAIL_LEVEL,				// 자네는 아직 부족한 점이 많아 보이는구만. 조금 더 실력을 닦고 찾게나.	// 37
	NPC_RESPONSE_TEAM_STARTING_FAIL_MONEY,				// <player_name>, 팀 등록을 위해서는 돈이 더 필요하다네	// 38
	NPC_RESPONSE_TEAM_STARTING_FAIL_FAME,				// <player_name>이라.. 난 아직 그런 이름은 들어보지도 못했다네. 그건 자네가 풋내기라는 것을 의미하지. 실력을 닦고 다시 찾아오게나	// 39
	NPC_RESPONSE_TEAM_STARTING_FAIL_DENY,				// 거부되었습니다.	// 40

	NPC_RESPONSE_CLAN_REGIST_FAIL_ALREADY_JOIN,			// 어디 한번 볼까? 자네는 이미 <clan_name> 클랜과 서약을 맺은 상태라고 나와있군	// 41
	NPC_RESPONSE_CLAN_REGIST_FAIL_QUIT_TIMEOUT,			// 자네는 다른 클랜을 탈퇴한지 얼마되지 않았군. 나무 이리저리 옮겨 다니는 것은 좋지 않지. 신중을 기하게	// 42
	NPC_RESPONSE_CLAN_REGIST_FAIL_CANCEL_TIMEOUT,		// 자네는 클랜을 취소 당한 지 얼마 되지 않았군. 좀 더 신중하게 기회를 엿보도록 하게	// 43
	NPC_RESPONSE_CLAN_REGIST_FAIL_LEVEL,				// 훌륭하지만 우두머리로써의 자질은 좀 부족한 것 같군. 실력을 닦고 오게나.	// 44
	NPC_RESPONSE_CLAN_REGIST_FAIL_MONEY,				// 클랜을 등록하려면 많은 돈이 필요하다네. 자네는 돈이 없어보이는군...	// 45
	NPC_RESPONSE_CLAN_REGIST_FAIL_FAME,					// <player_name>이라.. 아직 어린 뱀파이어인가보군. 더 많은 피를 마시고 다시 찾아오게나.	// 46
	NPC_RESPONSE_CLAN_REGIST_FAIL_NAME,					// 	// 47
	NPC_RESPONSE_CLAN_REGIST_FAIL_DENY,					// 거부되었습니다.	// 48

	NPC_RESPONSE_CLAN_STARTING_FAIL_ALREADY_JOIN,		// 당신은 이미 다른 클랜에 가입되어 있습니다.	// 49
	NPC_RESPONSE_CLAN_STARTING_FAIL_QUIT_TIMEOUT,		// 자네는 다른 클랜을 탈퇴한지 얼마되지 않았군. 나무 이리저리 옮겨 다니는 것은 좋지 않지. 신중을 기하게	// 50
	NPC_RESPONSE_CLAN_STARTING_FAIL_CANCEL_TIMEOUT,		// 자네는 클랜을 취소 당한 지 얼마 되지 않았군. 좀 더 신중하게 기회를 엿보도록 하게	// 51
	NPC_RESPONSE_CLAN_STARTING_FAIL_LEVEL,				// 훌륭한 조력자가 되기에는 자질이 좀 부족한 것 같군. 가서 좀더 수련을 하고 오게나	// 52
	NPC_RESPONSE_CLAN_STARTING_FAIL_MONEY,				// 기술이 월등해도 클랜을 유지할 수 있는 돈이 부족하면 그 클랜은 무너지기 쉽상이지	// 53
	NPC_RESPONSE_CLAN_STARTING_FAIL_FAME,				// <player_name>이라.. 난 아직 그런 이름은 들어보지도 못했다네. 그건 자네가 풋내기라는 것을 의미하지. 실력을 닦고 다시 찾아오게나	// 54
	NPC_RESPONSE_CLAN_STARTING_FAIL_DENY,				//  거부되었습니다.	// 55

	NPC_RESPONSE_GUILD_SHOW_REGIST,				// 길드 등록 창 띄우기	// 56
	NPC_RESPONSE_GUILD_SHOW_STARTING_JOIN,		// 길드 스타팅 멤버 가입 창 띄우기	// 57
	NPC_RESPONSE_GUILD_SHOW_JOIN,				// 길드 가입 창 띄우기	// 58
	NPC_RESPONSE_GUILD_SHOW_QUIT,				// 길드 탈퇴 창 띄우기	// 59
	NPC_RESPONSE_GUILD_ERROR,					// 길드 오류	// 60

	NPC_RESPONSE_TRADE_GIFT_BOX_OK,				// 선물 상자 교환 성공	// 61
	NPC_RESPONSE_TRADE_GIFT_BOX_NO_ITEM,		// 선물 상자 없다	// 62
	NPC_RESPONSE_TRADE_GIFT_BOX_ALREADY_TRADE,	// 선물 상자를 이미 한번 교환했다.	// 63
	NPC_RESPONSE_TRADE_GIFT_BOX_ERROR,			// 선물 상자 교환에 따른 기타 오류	// 64

	NPC_RESPONSE_REWARD_OK,		            	// 보상을 받았습니다.	// 65
	NPC_RESPONSE_REWARD_FAIL,		            // 보상을 받을 수 없습니다.	// 66
	NPC_RESPONSE_NO_EMPTY_SLOT,		            // 빈 자리가 없습니다.	// 67

	NPC_RESPONSE_SHOW_TAX_BALANCE,				// 성에 쌓여있는 세금의 잔액을 보여준다.	// 68
	NPC_RESPONSE_WITHDRAW_TAX_OK,				// 길드 마스터가 세금을 찾는 데에 성공했다.	// 69
	NPC_RESPONSE_WITHDRAW_TAX_FAIL,				// 길드 마스터가 세금을 찾는 데에 실패했다.	// 70

	NPC_RESPONSE_NO_GUILD,						// 팀(클랜)에 소속되어 있지 않습니다.	// 71
	NPC_RESPONSE_NOT_GUILD_MASTER,				// 팀(클랜) 마스터가 아닙니다.	// 72
	NPC_RESPONSE_HAS_NO_CASTLE,					// 팀(클랜)이 가진 성이 없습니다.	// 73
	NPC_RESPONSE_NOT_YOUR_CASTLE,				// 팀(클랜)이 소유한 성이 아닙니다.	// 74

	// 전쟁관련
	NPC_RESPONSE_NOT_ENOUGH_MONEY,				// 돈이 부족합니다.(전쟁신청금 부족이지만 범용적으로 쓸려고 -_-;)	// 75
	NPC_RESPONSE_WAR_SCHEDULE_FULL,				// 전쟁 스케쥴이 꽉 찼습니다.	// 76
	NPC_RESPONSE_WAR_ALREADY_REGISTERED,		// 이미 전쟁을 신청했었습니다.	// 77
	NPC_RESPONSE_WAR_REGISTRATION_OK,			// 전쟁 스케쥴에 등록 되었습니다.	// 78
	NPC_RESPONSE_ALREADY_HAS_CASTLE,			// 이미 성을 가지고 있습니다.	// 79
	NPC_RESPONSE_WAR_UNAVAILABLE,				// 전쟁 신청을 할 수 없습니다.	// 80

	// 전쟁 참가 관련
	NPC_RESPONSE_RACE_WAR_JOIN_FAILED,			// <사용자> 님 레벨대의 종족 전쟁 신청인원이 꽉 찼습니다.	// 81
	NPC_RESPONSE_RACE_WAR_JOIN_OK,				// 종족 전쟁 참가 신청을 했습니다.	// 82
	NPC_RESPONSE_RACE_WAR_GO_FIRST_SERVER, 		// 종족 전쟁은 각 월드의 첫번째 서버에서만 신청 및 참가가 가능합니다.	// 83

	// 이벤트 선물아이템
	NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL_NOW,		// 지금은 이벤트 아이템을 받을 수 없습니다.	// 84
	NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL,			// 이벤트 아이템을 받을 수 없습니다.	// 85
	NPC_RESPONSE_GIVE_EVENT_ITEM_OK,			// 이벤트에 따른 아이템을 받았습니다.	// 86
	NPC_RESPONSE_GIVE_PREMIUM_USER_ONLY,		// 프리미엄서비스 사용자만 받을 수 있습니다.	// 87

	// 커플신청 관련
	NPC_RESPONSE_WAIT_FOR_MEET_COUPLE,			// 커플 신청 할 상대의 이름을 입력하세요	// 88
	NPC_RESPONSE_COUPLE_MEET_SUCCESS,			// 커플이 성사되었습니다.	// 89
	NPC_RESPONSE_COUPLE_CANNOT_MEET,			// 커플이 성사될 수 없습니다.	// 90
	NPC_RESPONSE_MEET_WAIT_TIME_EXPIRED,		// 시간이 지나서 신청이 취소되었습니다.	// 91

	NPC_RESPONSE_WAIT_FOR_APART_COUPLE,			// 헤어질 상대의 이름을 입력하세요	// 92
	NPC_RESPONSE_COUPLE_APART_SUCCESS,			// 헤어졌습니다.	// 93
	NPC_RESPONSE_NOT_COUPLE,					// 커플이 아니라서 헤어질 수 없습니다.	// 94
	NPC_RESPONSE_APART_WAIT_TIME_EXPIRED,		// 시간이 지나서 신청이 취소되었습니다.	// 95

	NPC_RESPONSE_APART_COUPLE_FORCE,			// 일방적으로 헤어질 상대의 이름을 입력하세요.	// 96

	NPC_RESPONSE_QUEST,							// 퀘스트 관련 메시지 --;	// 97
	NPC_RESPONSE_LOTTERY,						// 복권 보여주기	// 98
	NPC_RESPONSE_CANNOT_BUY,					// 지금은 구입한 아이템을 찾을 수 없습니다.	// 99

	NPC_RESPONSE_CLEAR_RANK_BONUS_OK,			// 선택하신 계급의 스킬이 삭제 되었습니다.	// 100
	NPC_RESPONSE_NO_RANK_BONUS,					// 해당 자격이 없습니다.	// 101
	NPC_RESPONSE_ALREADY_CLEAR_RANK_BONUS,		// 선택하신 계급 스킬을 삭제한 적이 있습니다.	// 102

	NPC_RESPONSE_GNOME_CONTRACT_OK,				// 대지 정령과의 계약을 맺었습니다.	// 103
	NPC_RESPONSE_DOWN_SKILL,					// 다운시킬 스킬을 선택하세요>.<	// 104

	// 아우스터즈 길드 관련
	NPC_RESPONSE_GUILD_REGIST_FAIL_ALREADY_JOIN,		// 어디 한번 볼까? 자네는 이미 <guild_name> 길드 소속이라고 나와 있군	// 105
	NPC_RESPONSE_GUILD_REGIST_FAIL_QUIT_TIMEOUT,		// 자네는 다른 길드를 탈퇴한지 얼마 되지 않았군. 조금 더 신중하게 생각하고 행동하게	// 106
	NPC_RESPONSE_GUILD_REGIST_FAIL_CANCEL_TIMEOUT,		// 자네는 길드를 취소 당한 지 얼마 되지 않았군. 등록 조건에 부합하도록 자신을 좀 더 기르고 오게. 좀 더 신중하게 기회를 엿보도록 하게	// 107
	NPC_RESPONSE_GUILD_REGIST_FAIL_LEVEL,				// 훌륭하지만 리더로써의 자질은 좀 부족한 것 같군. 실력을 닦고 오게나	// 108
	NPC_RESPONSE_GUILD_REGIST_FAIL_MONEY,				// 길드를 만들려면 많은 돈이 필요하다네. 자네는 돈이 없어 보이는군...	// 109
	NPC_RESPONSE_GUILD_REGIST_FAIL_FAME,				// <player_name>이라.. 난 아직 그런 이름은 들어보지도 못했다네. 그건 자네가 풋내기라는 것을 의미하지. 실력을 닦고 다시 찾아오게나	// 110
	NPC_RESPONSE_GUILD_REGIST_FAIL_NAME,				// 길드 이름이 이미 쓰이고 있군, 다른 이름을 생각해 보게	// 111
	NPC_RESPONSE_GUILD_REGIST_FAIL_DENY,				// 거부되었습니다.	// 112

	NPC_RESPONSE_GUILD_STARTING_FAIL_ALREADY_JOIN,		// 당신은 이미 다른 길드에 가입되어 있습니다.	// 113
	NPC_RESPONSE_GUILD_STARTING_FAIL_QUIT_TIMEOUT,		// 자네는 다른 길드를 탈퇴한지 얼마 되지 않았군. 조금 더 신중하게 생각하고 행동하게	// 114
	NPC_RESPONSE_GUILD_STARTING_FAIL_CANCEL_TIMEOUT,	// 자네는 길드를 취소 당한 지 얼마 되지 않았군. 조건에 부합하도록 자신을 좀 더 기르고 오게. 좀 더 신중하게 기회를 엿보도록 하게	// 115
	NPC_RESPONSE_GUILD_STARTING_FAIL_LEVEL,				// 자네는 아직 부족한 점이 많아 보이는구만. 조금 더 실력을 닦고 찾게나.	// 116
	NPC_RESPONSE_GUILD_STARTING_FAIL_MONEY,				// <player_name>, 길드 등록을 위해서는 돈이 더 필요하다네	// 117
	NPC_RESPONSE_GUILD_STARTING_FAIL_FAME,				// <player_name>이라.. 난 아직 그런 이름은 들어보지도 못했다네. 그건 자네가 풋내기라는 것을 의미하지. 실력을 닦고 다시 찾아오게나	// 118
	NPC_RESPONSE_GUILD_STARTING_FAIL_DENY,				// 거부되었습니다.	// 119

	NPC_RESPONSE_TOO_MANY_GUILD_REGISTERED,				// 신청한 길드가 너무 많아서 신청할 수 없습니다.	// 120
	NPC_RESPONSE_REINFORCE_DENYED,						// 수비측 참전 신청이 이미 거부당해서 재신청 할 수 없습니다.	// 121
	NPC_RESPONSE_ALREADY_REINFORCE_ACCEPTED,			// 수비측 참전 신청이 허가된 길드가 이미 있어서 신청할 수 없습니다.	// 122
	NPC_RESPONSE_NO_WAR_REGISTERED,						// 공성 신청한 길드가 없어서 수비측 참전 신청을 할 수 없습니다.	// 123
	NPC_RESPONSE_CANNOT_ACCEPT,							// 수비측 참전 신청을 수락할 수 없습니다.
	NPC_RESPONSE_ACCEPT_OK,								// 참전 신청을 수락하였습니다.
	NPC_RESPONSE_CANNOT_DENY,							// 수비측 참전 신청을 거부할 수 없습니다.
	NPC_RESPONSE_DENY_OK,								// 참전 신청을 거부하였습니다.

	NPC_RESPONSE_SHOW_TAX_RATIO,						// 성의 세율을 보여준다.
	NPC_RESPONSE_MODIFY_TAX_RATIO_OK,					// 성의 세율을 조절했다.
	NPC_RESPONSE_MODIFY_TAX_RATIO_FAIL,					// 성의 세율을 조절했다.

	NPC_RESPONSE_SWAP_ADVANCEMENT_ITEM,					// 승직 아이템으로 교환해준다.
	NPC_RESPONSE_NOT_ADVANCED,							// 승직하지 않아서 아이템 교환이 안됩니다.

	NPC_RESPONSE_SHOW_DONATION_DIALOG,					// 기부창을 띄운다.
	NPC_RESPONSE_SHOW_DONATION_COMPLETE_DIALOG,			// 기부해주신 금액은 온정의 손길이 필요한 불우한 이웃을 위하여 소중하게 쓰여질 것입니다. 모금에 참여해주셔서 감사합니다.
	NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG,	// 이벤트 아이템 받기 확인 다이얼로그를 띄운다.
	NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG,			// 각종 메시지 다이얼로그를 띄운다.

	NPC_RESPONSE_MAX	// 123
};

enum CoupleMessage
{
	COUPLE_MESSAGE_NOT_EVENT_TERM = 1,			// 커플 이벤트 기간이 아닙니다.
	COUPLE_MESSAGE_ALREADY_WAITING,				// 이미 상대를 기다리고 있습니다.
	COUPLE_MESSAGE_LOGOFF,						// 상대방이 로그인 하지 않았습니다.
	COUPLE_MESSAGE_DIFFERENT_RACE,				// 서로 다른 종족입니다.
	COUPLE_MESSAGE_SAME_SEX,					// 남녀 사이에만 커플이 성립됩니다.
	COUPLE_MESSAGE_NOT_PAY_PLAYER,				// 유료 사용자가 아닙니다.
	COUPLE_MESSAGE_ALREADY_COUPLE,				// 이미 커플입니다.
	COUPLE_MESSAGE_WAS_COUPLE,					// 커플을 맺은 적이 있습니다.
	COUPLE_MESSAGE_NOT_ENOUGH_GOLD,				// 소지금이 부족합니다.
	COUPLE_MESSAGE_NOT_ENOUGH_ATTR,				// 능력치가 부족합니다.
	COUPLE_MESSAGE_NOT_ENOUGH_LEVEL,			// 레벨이 부족합니다.
	COUPLE_MESSAGE_INVENTORY_FULL,				// 커플링을 받을 공간이 부족합니다.
	COUPLE_MESSAGE_NO_WAITING,					// 당신을 기다리는 파트너가 없습니다.
	COUPLE_MESSAGE_NOT_COUPLE,					// 커플이 아닙니다.

	COUPLE_MESSAGE_MAX
};

enum QuestMessage
{
	START_SUCCESS = 0,
	START_FAIL_QUEST_NUM_EXCEEDED,	// 1
	START_FAIL_DUPLICATED_QUEST_ID,	// 2
	START_FAIL_PC,					// 3
	COMPLETE_SUCCESS,				// 4
	COMPLETE_FAIL_NOT_COMPLETE,		// 5
	COMPLETE_FAIL_NO_INVENTORY_SPACE,// 6
	COMPLETE_FAIL_NOT_IN_QUEST,		// 7
	COMPLETE_FAIL_TIME_EXPIRED,		// 8
	START_FAIL_CANNOT_APPLY_QUEST,	// 9
	CANCEL_SUCCESS,					// 10
	CANCEL_NOT_IN_QUEST,			// 11
	COMPLETE_FAIL_INVALID_NPC,		// 12
	FAIL_BUG						// 13
};

enum CommonMessage
{
	YOU_CAN_GET_EVENT_200501_COMBACK_ITEM = 0,			// 0	컴백 사용자 아이템을 받을 수 있습니다.
	YOU_CAN_GET_EVENT_200501_COMBACK_PREMIUM_ITEM,		// 1	컴백 사용자 결제 아이템을 받을 수 있습니다.
	YOU_CAN_GET_EVENT_200501_COMBACK_RECOMMEND_ITEM,	// 2	컴백 사용자 추천 아이템을 받을 수 있습니다.
	YOU_GET_EVENT_ITEM,									// 3	이벤트 아이템을 받았습니다.
	NOT_ENOUGH_INVENTORY_SPACE,							// 4	인벤토리에 공간이 부족합니다.
	ALEADY_GET_EVENT_ITEM,								// 5	이미 이벤트 아이템을 수령하셨습니다.
	FAIL_GET_EVENT_ITEM,								// 6	이벤트 아이템 받기 실패
	YOU_ARE_NOT_EVENT_TARGET,							// 7	이벤트 대상자가 아니다.

	COMMON_MESSAGE_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponse
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponse : public Packet 
{

public:
	GCNPCResponse() throw() { m_Code = NPC_RESPONSE_MAX; m_Parameter = 0;}
	virtual ~GCNPCResponse() throw() {}

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t getPacketID() const throw() { return PACKET_GC_NPC_RESPONSE; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCNPCResponse"; }
	string toString() const throw();
	
public:
	BYTE getCode(void) const throw() { return m_Code;}
	void setCode(WORD code) throw() { m_Code = code;}

	uint getParameter(void) const throw() { return m_Parameter; }
	void setParameter(uint parameter) throw() { m_Parameter = parameter; }

private: 
	WORD m_Code;
	uint m_Parameter;

};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponseFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponseFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNPCResponse(); }
	string getPacketName() const throw() { return "GCNPCResponse"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NPC_RESPONSE; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponseHandler
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponseHandler 
{
public:
	static void execute( GCNPCResponse* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
