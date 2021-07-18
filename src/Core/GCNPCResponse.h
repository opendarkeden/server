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
	// Ŭ���̾�Ʈ�� �Ͽ��� ������ �������̽��� ������ �ϴ� �ڵ�
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

	// Ŭ���̾�Ʈ�� ��Ŷ�� ���� ���� �ڵ�
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

	// �ӽÿ� ���̵�
	// ������ ��ġ���� �౸���� ���� ����� ���� ����� NPC Response�� ����ؼ� ���δ�.
	NPC_RESPONSE_DECREASE_BALL,	// 25

	// ��� ����
	NPC_RESPONSE_TEAM_REGIST_FAIL_ALREADY_JOIN,			// ��� �ѹ� ����? �ڳ״� �̹� <team_name> �� �Ҽ��̶�� ���� �ֱ�	// 26
	NPC_RESPONSE_TEAM_REGIST_FAIL_QUIT_TIMEOUT,			// �ڳ״� �ٸ� ���� Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�	// 27
	NPC_RESPONSE_TEAM_REGIST_FAIL_CANCEL_TIMEOUT,		// �ڳ״� ���� ��� ���� �� �� ���� �ʾұ�. ��� ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�	// 28
	NPC_RESPONSE_TEAM_REGIST_FAIL_LEVEL,				// �Ǹ������� �����ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�	// 29
	NPC_RESPONSE_TEAM_REGIST_FAIL_MONEY,				// ���� ������� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ���� ���̴±�...	// 30
	NPC_RESPONSE_TEAM_REGIST_FAIL_FAME,					// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�	// 31
	NPC_RESPONSE_TEAM_REGIST_FAIL_NAME,					// �� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����	// 32
	NPC_RESPONSE_TEAM_REGIST_FAIL_DENY,					// �źεǾ����ϴ�.	// 33

	NPC_RESPONSE_TEAM_STARTING_FAIL_ALREADY_JOIN,		// ����� �̹� �ٸ� ���� ���ԵǾ� �ֽ��ϴ�.	// 34
	NPC_RESPONSE_TEAM_STARTING_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� ���� Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�	// 35
	NPC_RESPONSE_TEAM_STARTING_FAIL_CANCEL_TIMEOUT,		// �ڳ״� ���� ��� ���� �� �� ���� �ʾұ�. ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�	// 36
	NPC_RESPONSE_TEAM_STARTING_FAIL_LEVEL,				// �ڳ״� ���� ������ ���� ���� ���̴±���. ���� �� �Ƿ��� �۰� ã�Գ�.	// 37
	NPC_RESPONSE_TEAM_STARTING_FAIL_MONEY,				// <player_name>, �� ����� ���ؼ��� ���� �� �ʿ��ϴٳ�	// 38
	NPC_RESPONSE_TEAM_STARTING_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�	// 39
	NPC_RESPONSE_TEAM_STARTING_FAIL_DENY,				// �źεǾ����ϴ�.	// 40

	NPC_RESPONSE_CLAN_REGIST_FAIL_ALREADY_JOIN,			// ��� �ѹ� ����? �ڳ״� �̹� <clan_name> Ŭ���� ������ ���� ���¶�� �����ֱ�	// 41
	NPC_RESPONSE_CLAN_REGIST_FAIL_QUIT_TIMEOUT,			// �ڳ״� �ٸ� Ŭ���� Ż������ �󸶵��� �ʾұ�. ���� �̸����� �Ű� �ٴϴ� ���� ���� ����. ������ ���ϰ�	// 42
	NPC_RESPONSE_CLAN_REGIST_FAIL_CANCEL_TIMEOUT,		// �ڳ״� Ŭ���� ��� ���� �� �� ���� �ʾұ�. �� �� �����ϰ� ��ȸ�� �������� �ϰ�	// 43
	NPC_RESPONSE_CLAN_REGIST_FAIL_LEVEL,				// �Ǹ������� ��θӸ��ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�.	// 44
	NPC_RESPONSE_CLAN_REGIST_FAIL_MONEY,				// Ŭ���� ����Ϸ��� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ����̴±�...	// 45
	NPC_RESPONSE_CLAN_REGIST_FAIL_FAME,					// <player_name>�̶�.. ���� � �����̾��ΰ�����. �� ���� �Ǹ� ���ð� �ٽ� ã�ƿ��Գ�.	// 46
	NPC_RESPONSE_CLAN_REGIST_FAIL_NAME,					// 	// 47
	NPC_RESPONSE_CLAN_REGIST_FAIL_DENY,					// �źεǾ����ϴ�.	// 48

	NPC_RESPONSE_CLAN_STARTING_FAIL_ALREADY_JOIN,		// ����� �̹� �ٸ� Ŭ���� ���ԵǾ� �ֽ��ϴ�.	// 49
	NPC_RESPONSE_CLAN_STARTING_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� Ŭ���� Ż������ �󸶵��� �ʾұ�. ���� �̸����� �Ű� �ٴϴ� ���� ���� ����. ������ ���ϰ�	// 50
	NPC_RESPONSE_CLAN_STARTING_FAIL_CANCEL_TIMEOUT,		// �ڳ״� Ŭ���� ��� ���� �� �� ���� �ʾұ�. �� �� �����ϰ� ��ȸ�� �������� �ϰ�	// 51
	NPC_RESPONSE_CLAN_STARTING_FAIL_LEVEL,				// �Ǹ��� �����ڰ� �Ǳ⿡�� ������ �� ������ �� ����. ���� ���� ������ �ϰ� ���Գ�	// 52
	NPC_RESPONSE_CLAN_STARTING_FAIL_MONEY,				// ����� �����ص� Ŭ���� ������ �� �ִ� ���� �����ϸ� �� Ŭ���� �������� ��������	// 53
	NPC_RESPONSE_CLAN_STARTING_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�	// 54
	NPC_RESPONSE_CLAN_STARTING_FAIL_DENY,				//  �źεǾ����ϴ�.	// 55

	NPC_RESPONSE_GUILD_SHOW_REGIST,				// ��� ��� â ����	// 56
	NPC_RESPONSE_GUILD_SHOW_STARTING_JOIN,		// ��� ��Ÿ�� ��� ���� â ����	// 57
	NPC_RESPONSE_GUILD_SHOW_JOIN,				// ��� ���� â ����	// 58
	NPC_RESPONSE_GUILD_SHOW_QUIT,				// ��� Ż�� â ����	// 59
	NPC_RESPONSE_GUILD_ERROR,					// ��� ����	// 60

	NPC_RESPONSE_TRADE_GIFT_BOX_OK,				// ���� ���� ��ȯ ����	// 61
	NPC_RESPONSE_TRADE_GIFT_BOX_NO_ITEM,		// ���� ���� ����	// 62
	NPC_RESPONSE_TRADE_GIFT_BOX_ALREADY_TRADE,	// ���� ���ڸ� �̹� �ѹ� ��ȯ�ߴ�.	// 63
	NPC_RESPONSE_TRADE_GIFT_BOX_ERROR,			// ���� ���� ��ȯ�� ���� ��Ÿ ����	// 64

	NPC_RESPONSE_REWARD_OK,		            	// ������ �޾ҽ��ϴ�.	// 65
	NPC_RESPONSE_REWARD_FAIL,		            // ������ ���� �� �����ϴ�.	// 66
	NPC_RESPONSE_NO_EMPTY_SLOT,		            // �� �ڸ��� �����ϴ�.	// 67

	NPC_RESPONSE_SHOW_TAX_BALANCE,				// ���� �׿��ִ� ������ �ܾ��� �����ش�.	// 68
	NPC_RESPONSE_WITHDRAW_TAX_OK,				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.	// 69
	NPC_RESPONSE_WITHDRAW_TAX_FAIL,				// ��� �����Ͱ� ������ ã�� ���� �����ߴ�.	// 70

	NPC_RESPONSE_NO_GUILD,						// ��(Ŭ��)�� �ҼӵǾ� ���� �ʽ��ϴ�.	// 71
	NPC_RESPONSE_NOT_GUILD_MASTER,				// ��(Ŭ��) �����Ͱ� �ƴմϴ�.	// 72
	NPC_RESPONSE_HAS_NO_CASTLE,					// ��(Ŭ��)�� ���� ���� �����ϴ�.	// 73
	NPC_RESPONSE_NOT_YOUR_CASTLE,				// ��(Ŭ��)�� ������ ���� �ƴմϴ�.	// 74

	// �������
	NPC_RESPONSE_NOT_ENOUGH_MONEY,				// ���� �����մϴ�.(�����û�� ���������� ���������� ������ -_-;)	// 75
	NPC_RESPONSE_WAR_SCHEDULE_FULL,				// ���� �������� �� á���ϴ�.	// 76
	NPC_RESPONSE_WAR_ALREADY_REGISTERED,		// �̹� ������ ��û�߾����ϴ�.	// 77
	NPC_RESPONSE_WAR_REGISTRATION_OK,			// ���� �����쿡 ��� �Ǿ����ϴ�.	// 78
	NPC_RESPONSE_ALREADY_HAS_CASTLE,			// �̹� ���� ������ �ֽ��ϴ�.	// 79
	NPC_RESPONSE_WAR_UNAVAILABLE,				// ���� ��û�� �� �� �����ϴ�.	// 80

	// ���� ���� ����
	NPC_RESPONSE_RACE_WAR_JOIN_FAILED,			// <�����> �� �������� ���� ���� ��û�ο��� �� á���ϴ�.	// 81
	NPC_RESPONSE_RACE_WAR_JOIN_OK,				// ���� ���� ���� ��û�� �߽��ϴ�.	// 82
	NPC_RESPONSE_RACE_WAR_GO_FIRST_SERVER, 		// ���� ������ �� ������ ù��° ���������� ��û �� ������ �����մϴ�.	// 83

	// �̺�Ʈ ����������
	NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL_NOW,		// ������ �̺�Ʈ �������� ���� �� �����ϴ�.	// 84
	NPC_RESPONSE_GIVE_EVENT_ITEM_FAIL,			// �̺�Ʈ �������� ���� �� �����ϴ�.	// 85
	NPC_RESPONSE_GIVE_EVENT_ITEM_OK,			// �̺�Ʈ�� ���� �������� �޾ҽ��ϴ�.	// 86
	NPC_RESPONSE_GIVE_PREMIUM_USER_ONLY,		// �����̾����� ����ڸ� ���� �� �ֽ��ϴ�.	// 87

	// Ŀ�ý�û ����
	NPC_RESPONSE_WAIT_FOR_MEET_COUPLE,			// Ŀ�� ��û �� ����� �̸��� �Է��ϼ���	// 88
	NPC_RESPONSE_COUPLE_MEET_SUCCESS,			// Ŀ���� ����Ǿ����ϴ�.	// 89
	NPC_RESPONSE_COUPLE_CANNOT_MEET,			// Ŀ���� ����� �� �����ϴ�.	// 90
	NPC_RESPONSE_MEET_WAIT_TIME_EXPIRED,		// �ð��� ������ ��û�� ��ҵǾ����ϴ�.	// 91

	NPC_RESPONSE_WAIT_FOR_APART_COUPLE,			// ����� ����� �̸��� �Է��ϼ���	// 92
	NPC_RESPONSE_COUPLE_APART_SUCCESS,			// ��������ϴ�.	// 93
	NPC_RESPONSE_NOT_COUPLE,					// Ŀ���� �ƴ϶� ����� �� �����ϴ�.	// 94
	NPC_RESPONSE_APART_WAIT_TIME_EXPIRED,		// �ð��� ������ ��û�� ��ҵǾ����ϴ�.	// 95

	NPC_RESPONSE_APART_COUPLE_FORCE,			// �Ϲ������� ����� ����� �̸��� �Է��ϼ���.	// 96

	NPC_RESPONSE_QUEST,							// ����Ʈ ���� �޽��� --;	// 97
	NPC_RESPONSE_LOTTERY,						// ���� �����ֱ�	// 98
	NPC_RESPONSE_CANNOT_BUY,					// ������ ������ �������� ã�� �� �����ϴ�.	// 99

	NPC_RESPONSE_CLEAR_RANK_BONUS_OK,			// �����Ͻ� ����� ��ų�� ���� �Ǿ����ϴ�.	// 100
	NPC_RESPONSE_NO_RANK_BONUS,					// �ش� �ڰ��� �����ϴ�.	// 101
	NPC_RESPONSE_ALREADY_CLEAR_RANK_BONUS,		// �����Ͻ� ��� ��ų�� ������ ���� �ֽ��ϴ�.	// 102

	NPC_RESPONSE_GNOME_CONTRACT_OK,				// ���� ���ɰ��� ����� �ξ����ϴ�.	// 103
	NPC_RESPONSE_DOWN_SKILL,					// �ٿ��ų ��ų�� �����ϼ���>.<	// 104

	// �ƿ콺���� ��� ����
	NPC_RESPONSE_GUILD_REGIST_FAIL_ALREADY_JOIN,		// ��� �ѹ� ����? �ڳ״� �̹� <guild_name> ��� �Ҽ��̶�� ���� �ֱ�	// 105
	NPC_RESPONSE_GUILD_REGIST_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� ��带 Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�	// 106
	NPC_RESPONSE_GUILD_REGIST_FAIL_CANCEL_TIMEOUT,		// �ڳ״� ��带 ��� ���� �� �� ���� �ʾұ�. ��� ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�	// 107
	NPC_RESPONSE_GUILD_REGIST_FAIL_LEVEL,				// �Ǹ������� �����ν��� ������ �� ������ �� ����. �Ƿ��� �۰� ���Գ�	// 108
	NPC_RESPONSE_GUILD_REGIST_FAIL_MONEY,				// ��带 ������� ���� ���� �ʿ��ϴٳ�. �ڳ״� ���� ���� ���̴±�...	// 109
	NPC_RESPONSE_GUILD_REGIST_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�	// 110
	NPC_RESPONSE_GUILD_REGIST_FAIL_NAME,				// ��� �̸��� �̹� ���̰� �ֱ�, �ٸ� �̸��� ������ ����	// 111
	NPC_RESPONSE_GUILD_REGIST_FAIL_DENY,				// �źεǾ����ϴ�.	// 112

	NPC_RESPONSE_GUILD_STARTING_FAIL_ALREADY_JOIN,		// ����� �̹� �ٸ� ��忡 ���ԵǾ� �ֽ��ϴ�.	// 113
	NPC_RESPONSE_GUILD_STARTING_FAIL_QUIT_TIMEOUT,		// �ڳ״� �ٸ� ��带 Ż������ �� ���� �ʾұ�. ���� �� �����ϰ� �����ϰ� �ൿ�ϰ�	// 114
	NPC_RESPONSE_GUILD_STARTING_FAIL_CANCEL_TIMEOUT,	// �ڳ״� ��带 ��� ���� �� �� ���� �ʾұ�. ���ǿ� �����ϵ��� �ڽ��� �� �� �⸣�� ����. �� �� �����ϰ� ��ȸ�� �������� �ϰ�	// 115
	NPC_RESPONSE_GUILD_STARTING_FAIL_LEVEL,				// �ڳ״� ���� ������ ���� ���� ���̴±���. ���� �� �Ƿ��� �۰� ã�Գ�.	// 116
	NPC_RESPONSE_GUILD_STARTING_FAIL_MONEY,				// <player_name>, ��� ����� ���ؼ��� ���� �� �ʿ��ϴٳ�	// 117
	NPC_RESPONSE_GUILD_STARTING_FAIL_FAME,				// <player_name>�̶�.. �� ���� �׷� �̸��� ������ ���ߴٳ�. �װ� �ڳװ� ǲ������ ���� �ǹ�����. �Ƿ��� �۰� �ٽ� ã�ƿ��Գ�	// 118
	NPC_RESPONSE_GUILD_STARTING_FAIL_DENY,				// �źεǾ����ϴ�.	// 119

	NPC_RESPONSE_TOO_MANY_GUILD_REGISTERED,				// ��û�� ��尡 �ʹ� ���Ƽ� ��û�� �� �����ϴ�.	// 120
	NPC_RESPONSE_REINFORCE_DENYED,						// ������ ���� ��û�� �̹� �źδ��ؼ� ���û �� �� �����ϴ�.	// 121
	NPC_RESPONSE_ALREADY_REINFORCE_ACCEPTED,			// ������ ���� ��û�� �㰡�� ��尡 �̹� �־ ��û�� �� �����ϴ�.	// 122
	NPC_RESPONSE_NO_WAR_REGISTERED,						// ���� ��û�� ��尡 ��� ������ ���� ��û�� �� �� �����ϴ�.	// 123
	NPC_RESPONSE_CANNOT_ACCEPT,							// ������ ���� ��û�� ������ �� �����ϴ�.
	NPC_RESPONSE_ACCEPT_OK,								// ���� ��û�� �����Ͽ����ϴ�.
	NPC_RESPONSE_CANNOT_DENY,							// ������ ���� ��û�� �ź��� �� �����ϴ�.
	NPC_RESPONSE_DENY_OK,								// ���� ��û�� �ź��Ͽ����ϴ�.

	NPC_RESPONSE_SHOW_TAX_RATIO,						// ���� ������ �����ش�.
	NPC_RESPONSE_MODIFY_TAX_RATIO_OK,					// ���� ������ �����ߴ�.
	NPC_RESPONSE_MODIFY_TAX_RATIO_FAIL,					// ���� ������ �����ߴ�.

	NPC_RESPONSE_SWAP_ADVANCEMENT_ITEM,					// ���� ���������� ��ȯ���ش�.
	NPC_RESPONSE_NOT_ADVANCED,							// �������� �ʾƼ� ������ ��ȯ�� �ȵ˴ϴ�.

	NPC_RESPONSE_SHOW_DONATION_DIALOG,					// ���â�� ����.
	NPC_RESPONSE_SHOW_DONATION_COMPLETE_DIALOG,			// ������ֽ� �ݾ��� ������ �ձ��� �ʿ��� �ҿ��� �̿��� ���Ͽ� �����ϰ� ������ ���Դϴ�. ��ݿ� �������ּż� �����մϴ�.
	NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG,	// �̺�Ʈ ������ �ޱ� Ȯ�� ���̾�α׸� ����.
	NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG,			// ���� �޽��� ���̾�α׸� ����.

	NPC_RESPONSE_SHOW_DONATION_WEDDING_COMPLETE_DIALOG,	// 
	NPC_RESPONSE_SHOW_ALEADY_DONATED_DIALOG,			// �̹� ���Ǳ��� ���̽��ϴ�.

	NPC_RESPONSE_MAX	// 139
};

enum CoupleMessage
{
	COUPLE_MESSAGE_NOT_EVENT_TERM = 1,			// Ŀ�� �̺�Ʈ �Ⱓ�� �ƴմϴ�.
	COUPLE_MESSAGE_ALREADY_WAITING,				// �̹� ��븦 ��ٸ��� �ֽ��ϴ�.
	COUPLE_MESSAGE_LOGOFF,						// ������ �α��� ���� �ʾҽ��ϴ�.
	COUPLE_MESSAGE_DIFFERENT_RACE,				// ���� �ٸ� �����Դϴ�.
	COUPLE_MESSAGE_SAME_SEX,					// ���� ���̿��� Ŀ���� �����˴ϴ�.
	COUPLE_MESSAGE_NOT_PAY_PLAYER,				// ���� ����ڰ� �ƴմϴ�.
	COUPLE_MESSAGE_ALREADY_COUPLE,				// �̹� Ŀ���Դϴ�.
	COUPLE_MESSAGE_WAS_COUPLE,					// Ŀ���� ���� ���� �ֽ��ϴ�.
	COUPLE_MESSAGE_NOT_ENOUGH_GOLD,				// �������� �����մϴ�.
	COUPLE_MESSAGE_NOT_ENOUGH_ATTR,				// �ɷ�ġ�� �����մϴ�.
	COUPLE_MESSAGE_NOT_ENOUGH_LEVEL,			// ������ �����մϴ�.
	COUPLE_MESSAGE_INVENTORY_FULL,				// Ŀ�ø��� ���� ������ �����մϴ�.
	COUPLE_MESSAGE_NO_WAITING,					// ����� ��ٸ��� ��Ʈ�ʰ� �����ϴ�.
	COUPLE_MESSAGE_NOT_COUPLE,					// Ŀ���� �ƴմϴ�.

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
	YOU_CAN_GET_EVENT_200501_COMBACK_ITEM = 0,			// 0	�Ĺ� ����� �������� ���� �� �ֽ��ϴ�.
	YOU_CAN_GET_EVENT_200501_COMBACK_PREMIUM_ITEM,		// 1	�Ĺ� ����� ���� �������� ���� �� �ֽ��ϴ�.
	YOU_CAN_GET_EVENT_200501_COMBACK_RECOMMEND_ITEM,	// 2	�Ĺ� ����� ��õ �������� ���� �� �ֽ��ϴ�.
	YOU_GET_EVENT_ITEM,									// 3	�̺�Ʈ �������� �޾ҽ��ϴ�.
	NOT_ENOUGH_INVENTORY_SPACE,							// 4	�κ��丮�� ������ �����մϴ�.
	ALEADY_GET_EVENT_ITEM,								// 5	�̹� �̺�Ʈ �������� �����ϼ̽��ϴ�.
	FAIL_GET_EVENT_ITEM,								// 6	�̺�Ʈ ������ �ޱ� ����
	YOU_ARE_NOT_EVENT_TARGET,							// 7	�̺�Ʈ ����ڰ� �ƴϴ�.

	COMMON_MESSAGE_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponse
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponse : public Packet 
{

public:
	GCNPCResponse()  { m_Code = NPC_RESPONSE_MAX; m_Parameter = 0;}
	virtual ~GCNPCResponse()  {}

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;

	PacketID_t getPacketID() const  { return PACKET_GC_NPC_RESPONSE; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCNPCResponse"; }
	string toString() const ;
	
public:
	BYTE getCode(void) const  { return m_Code;}
	void setCode(WORD code)  { m_Code = code;}

	uint getParameter(void) const  { return m_Parameter; }
	void setParameter(uint parameter)  { m_Parameter = parameter; }

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
	Packet* createPacket()  { return new GCNPCResponse(); }
	string getPacketName() const  { return "GCNPCResponse"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_NPC_RESPONSE; }
	PacketSize_t getPacketMaxSize() const  { return szBYTE + szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNPCResponseHandler
//////////////////////////////////////////////////////////////////////////////

class GCNPCResponseHandler 
{
public:
	static void execute(GCNPCResponse* pPacket, Player* pPlayer) ;
};

#endif
