#ifndef __MONSTER_INFO_TYPES__
#define __MONSTER_INFO_TYPES__


//////////////////////////////////////////////////////////////////////////////
// Class Monster;
// AI 에 의해서 조종을 받으며, 주로 PC 들의 전투 대상이 되는 크리처들이다.
//////////////////////////////////////////////////////////////////////////////
enum
{
	CLAN_NONE,							// 어디에도 속하지 않는 애덜.. 0
	CLAN_VAMPIRE_MONSTER,				// 떠돌이 뱀파 몬스터 -_-;     1
	CLAN_VAMPIRE_BATHORY_MONSTER,		// 바토리 소속 몬스터          2
	CLAN_VAMPIRE_TEPEZ_MONSTER,			// 테페즈 소속 몬스터          3
	CLAN_SLAYER_MONSTER,				// 슬레이어 몬스터 - -;;       4

	CLAN_MAX
};

extern int DefaultClanID[CLAN_MAX];

//////////////////////////////////////////////////////////////////////////////
// RegenType - 몬스터가 나타나는 방법
//
// 체크하는 순서의 의미도 있는데, 
// Hide가 default라서 가장 큰 값이므로 가장 나중에 체크해야한다.
//////////////////////////////////////////////////////////////////////////////
enum RegenType
{
	REGENTYPE_PORTAL,		// 포탈을 타고 나타나는 모습
	REGENTYPE_INVISIBLE,	// invisible상태로 나타나는 모습
	REGENTYPE_BAT,			// 박쥐 상태로 나타나는 모습
	REGENTYPE_HIDE,			// 땅 속에 숨어 있는 상태로
	
	REGENTYPE_MAX
};

#endif
