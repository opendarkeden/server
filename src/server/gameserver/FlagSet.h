//////////////////////////////////////////////////////////////////////////////
// Filename    : FlagSet.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __FLAGSET_H__
#define __FLAGSET_H__

#include "Types.h"
#include "Exception.h"
#include <string>

#define FLAG_SIZE_MAX 3*8

enum FlagSetType
{
	FLAGSET_RECEIVE_NEWBIE_ITEM,				// 0 - 초보자용 아이템 받은 경우
	FLAGSET_RECEIVE_NEWBIE_ITEM_FIGHTER,		// 1 - sword, blade
	FLAGSET_RECEIVE_NEWBIE_ITEM_CLERIC,			// 2 - heal, enchant
	FLAGSET_RECEIVE_NEWBIE_ITEM_GUNNER,			// 3 - gun

	FLAGSET_TRADE_GIFT_BOX_2002_12,				// 4 - 2002.12 크리스마스 이벤트 빨간 선물 상자 교환 여부
	FLAGSET_RECEIVE_GREEN_GIFT_BOX,				// 5 - 다른 사람으로부터 녹색 선물 상자를 받았나

	FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO,			// 6 - 초보자용 아이템을 자동으로 받아야 하는지

	FLAGSET_RECEIVE_PREMIUM_EVENT_ITEM_2003_3,	// 7 - 2003.3.1 프리미엄 사용자들에게 선물 준다.

	FLAGSET_IS_COUPLE,							// 7 - 이미 커플인가.
	FLAGSET_WAS_COUPLE,							// 8 - 커플 이었다.		- 2003.3 월 커플이벤트용

	FLAGSET_NOT_JUST_CREATED,					// 9 - 막 생성된 캐릭터가 아닌가.

	FLAGSET_CLEAR_RANK_BONUS_5,					// 10 - 5 레벨 계급 스킬을 초기화 한 적이 있는가?
	FLAGSET_CLEAR_RANK_BONUS_10,				// 11 - 10 레벨 계급 스킬을 초기화 한 적이 있는가?
	FLAGSET_CLEAR_RANK_BONUS_15,				// 12 - 15 레벨 계급 스킬을 초기화 한 적이 있는가?
	FLAGSET_CLEAR_RANK_BONUS_20,				// 13 - 20 레벨 계급 스킬을 초기화 한 적이 있는가?

	FLAGSET_GNOMES_HORN,						// 14 - 대지정령의 뿔 계약을 맺었는가

	FLAGSET_SWAP_COAT,							// 15 - 방어구 상의를 바꿨는거
	FLAGSET_SWAP_TROUSER,						// 16 - 방어구 하의를 바꿨는거
	FLAGSET_SWAP_WEAPON,						// 17 - 무기를 바꿨는가

	FLAGSET_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class Flag
//////////////////////////////////////////////////////////////////////////////

class FlagSet
{

///// Member methods /////
	
public:
	FlagSet() throw();
	~FlagSet() throw();

public:
	void create(const string& owner) throw();
	void load(const string& owner) throw();
	void save(const string& owner) throw();
	void destroy(const string& owner) throw();

public:
	bool isOn(int index) throw();
	bool turnOn(int index) throw();
	bool turnOff(int index) throw();

public:
	string toString(void) throw();
	static FlagSet fromString(const string& text) throw();

	static void initialize(void) throw();

protected:
	bool isValidIndex(int index) throw();
	BYTE* getData() throw() { return &m_pData[0]; }
	

///// Member data /////
	
protected:
	BYTE m_pData[FLAG_SIZE_MAX/8];

	static string m_pLookup[256];
	static bool   m_bInit;
};


#endif



