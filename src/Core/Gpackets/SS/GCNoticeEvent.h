//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNoticeEvent.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NOTICE_EVENT_H__
#define __GC_NOTICE_EVENT_H__

#include "Packet.h"
#include "PacketFactory.h"

#ifndef __GAME_CLIENT__
	#include "Utility.h"
#endif

enum 
{
	NOTICE_EVENT_KICK_OUT_FROM_ZONE,			// 존에서 추방하는 시간(초)
	NOTICE_EVENT_CONTINUAL_GROUND_ATTACK,		// 존에서 지속적인 공격이 일어나는 경우(초)
 	NOTICE_EVENT_CONTINUAL_GROUND_ATTACK_END,	// 존에서 지속적인 공격이 끝났다.
	NOTICE_EVENT_MASTER_COMBAT_TIME,			// 마스터와 싸울 수 있는 남은 시간(초)
	NOTICE_EVENT_MASTER_COMBAT_END,				// 마스터와 싸우는게 끝났다.
	NOTICE_EVENT_METEOR_STRIKE,					// 메테오 공격(초)
	NOTICE_EVENT_METEOR_STRIKE_END,				// 메테오 끝
	NOTICE_EVENT_PREMIUM_HALF_START,			// 프리미엄 사용자는 포션/혈청 반값
	NOTICE_EVENT_PREMIUM_HALF_END,				// 이벤트 끝
	NOTICE_EVENT_SHOP_TAX_CHANGE,				// 상점 세금 바꼈다.(세율)

	// 전쟁관련
	NOTICE_EVENT_WAR_OVER,						// 전쟁끝(CastleZoneID)
	NOTICE_EVENT_RACE_WAR_OVER,					// 종족 전쟁끝

	// 처음 캐릭터 생성했을 때
	NOTICE_EVENT_WELCOME_MESSAGE,

	// 퀘스트 할머니 만나기 -_-;
	NOTICE_EVENT_MEET_GRANDMA,
	NOTICE_EVENT_MEET_FISHSHOP_MASTER,

	NOTICE_EVENT_START_QUEST_ENDING,
	NOTICE_EVENT_RESULT_LOTTERY,

	NOTICE_EVENT_RUN_HORN,

	NOTICE_EVENT_MASTER_LAIR_OPEN,				// 마스터 레어(바토리레어)가 열렸습니다.
	NOTICE_EVENT_MASTER_LAIR_CLOSED,			// 마스터 레어(바토리레어)가 닫혔습니다.
	NOTICE_EVENT_MASTER_LAIR_COUNT,				// 마스터 레어(바토리레어) 출입 가능 시간이 5분 남았습니다.

	NOTICE_EVENT_CONTRACT_GNOMES_HORN,			// 시오람에게 가서 계약을 맺으셔야 사용하실 수 있습니다.
	NOTICE_EVENT_NOT_ENOUGH_MONEY,				// 돈이 모자랍니다.

	NOTICE_EVENT_MINI_GAME,					// 지뢰찾기~

	NOTICE_EVENT_GET_RIFINIUM,					// 리피니움을 획득하였습니다.
	NOTICE_EVENT_INVENTORY_FULL,				// 인벤토리 내의 여유 공간이 부족합니다.

	NOTICE_EVENT_FLAG_WAR_READY,				// Capture the Flag! 이벤트를 실시합니다.
	NOTICE_EVENT_FLAG_WAR_START,				// 이벤트를 시작합니다.
	NOTICE_EVENT_FLAG_WAR_FINISH,				// 이벤트가 끝났습니다. 3분 뒤 아이템이 터집니다.
	NOTICE_EVENT_FLAG_POURED_ITEM,				// Capture the Flag 이벤트 아이템이 나왔습니다.

	NOTICE_EVENT_ENTER_BEGINNER_ZONE,				// 초보자존으로 들어가시겠습니까?
	NOTICE_EVENT_LOGIN_JUST_NOW,				// 방금 로그인했습니다.

	NOTICE_EVENT_LEVEL_WAR_ARRANGED,			// 곧 레벨별 전쟁이 시작됩니다.
	NOTICE_EVENT_LEVEL_WAR_STARTED,				// 레벨별 전쟁이 시작되었습니다.

	NOTICE_EVENT_RACE_WAR_SOON,					// 3일안에 종족전을 합니다.

	NOTICE_EVENT_LEVEL_WAR_OVER,				// 레벨별 전쟁이 끝났다.
	NOTICE_EVENT_NETMARBLE_CARD_FULL,           // 99개의 넷마블 카드를 다 모았다.

	NOTICE_EVENT_HOLYDAY,						// 오늘은 국경일이다.
	NOTICE_EVENT_CAN_PET_QUEST,					// 펫 퀘스트를 할 수 있다.

	NOTICE_EVENT_SEND_SMS,						// SMS보내게 인터페이스 띄워주셈

	NOTICE_EVENT_GDR_LAIR_ENDING_1,				// 1차 엔딩 :)

	NOTICE_EVENT_GOLD_MEDALS,					// 금메달 개수~
	NOTICE_EVENT_CROWN_PRICE,					// 월계관 가격

	NOTICE_EVENT_GIVE_PRESENT_1,				// 레벨 1 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_2,				// 레벨 2 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_3,				// 레벨 3 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_4,				// 레벨 4 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_5,				// 레벨 5 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_6,				// 레벨 6 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_7,				// 레벨 7 선물상자 줬습니다.
	NOTICE_EVENT_GIVE_PRESENT_8,				// 레벨 8 선물상자 줬습니다.
	NOTICE_EVENT_CAN_OPEN_PRESENT_8,			// 레벨 8 선물상자 열 수 있습니다.

	NOTICE_EVENT_RACE_WAR_IN_20,				// 20분안에 전쟁이 시작됩니다.
	NOTICE_EVENT_RACE_WAR_IN_5,					// 5분안에 전쟁이 시작됩니다.

	NOTICE_EVENT_RACE_WAR_STARTED_IN_OTHER_SERVER,	// 첫번째 서버에서 종족전이 시작됐습니다.

	NOTICE_EVENT_CANNOT_FIND_STORE,				// 해당 판매자를 찾을 수 없습니다.
	NOTICE_EVENT_STORE_CLOSED,					// 상점이 이미 닫혔습니다.
	NOTICE_EVENT_ITEM_NOT_FOUND,				// 해당 아이템이 이미 판매되었거나 판매자에 의해 철회되었습니다.
//	NOTICE_EVENT_NOT_ENOUGH_MONEY,				// 돈이 모자라서 못 사겠습니다.
	NOTICE_EVENT_TOO_MUCH_MONEY,				// 판매자가 너무 많은 돈을 가지고 있어서 살 수 없습니다.
	NOTICE_EVENT_NO_INVENTORY_SPACE,			// 인벤토리에 빈 자리가 없습니다.

	NOTICE_EVENT_ALREADY_DISPLAYED,				// 이미 진열된 아이템입니다.
	NOTICE_EVENT_CANNOT_SELL,					// 팔 수 없는 아이템입니다.

	NOTICE_EVENT_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCNoticeEvent
//////////////////////////////////////////////////////////////////////////////

class GCNoticeEvent : public Packet 
{

public:
	GCNoticeEvent() throw() { m_Code = NOTICE_EVENT_MAX; m_Parameter = 0;}
	virtual ~GCNoticeEvent() throw() {}

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t getPacketID() const throw() { return PACKET_GC_NOTICE_EVENT; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCNoticeEvent"; }
	string toString() const throw();
	
public:
	BYTE getCode(void) const throw() { return m_Code;}
	void setCode(WORD code) throw() { m_Code = code;}

	uint getParameter(void) const throw() { return m_Parameter; }
	void setParameter(uint parameter) throw() { m_Parameter = parameter; }

#ifndef __GAME_CLIENT__
	void setParameter(WORD hiWord, WORD loWord) throw() { m_Code = makeDWORD(hiWord, loWord); }
#endif

private: 
	WORD m_Code;
	uint m_Parameter;

};


//////////////////////////////////////////////////////////////////////////////
// class GCNoticeEventFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNoticeEventFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNoticeEvent(); }
	string getPacketName() const throw() { return "GCNoticeEvent"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NOTICE_EVENT; }
	PacketSize_t getPacketMaxSize() const throw() { return szWORD + szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNoticeEventHandler
//////////////////////////////////////////////////////////////////////////////

class GCNoticeEventHandler 
{
public:
	static void execute( GCNoticeEvent* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
