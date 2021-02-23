//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemTypes.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ITEM_TYPES_H__
#define __ITEM_TYPES_H__

#include "SystemTypes.h"

// ItemType : 아이템 클래스 하위의 세부 아이템 타입들
typedef WORD ItemType_t;
const uint szItemType = sizeof(ItemType_t);

// Item의 OptionType
typedef BYTE OptionType_t;
const uint szOptionType = sizeof( OptionType_t );

// DefaultOptionSetType
typedef BYTE DefaultOptionSetType_t;
const uint szDefaultOptionSetType = sizeof( DefaultOptionSetType_t );

// Item의 DB 용 아이디
typedef DWORD ItemID_t;
const uint szItemID_t = sizeof( ItemID_t );

// StorageID : 아이템이 저장된 곳을 지정하는 변수
typedef DWORD StorageID_t;
const uint szStorageID = sizeof(StorageID_t);

// ItemClass : 아이템 class	
typedef BYTE ItemClass_t;
const uint szItemClass = sizeof(ItemClass_t);

// 아이템의 가격
typedef DWORD Price_t;
const uint szPrice= sizeof( Price_t );

// volume
typedef BYTE VolumeType_t;
const uint szVolumeType = sizeof( VolumeType_t );

typedef BYTE VolumeWidth_t;
const uint szVolumeWidth = sizeof( VolumeWidth_t );

typedef BYTE VolumeHeight_t;
const uint szVolumeHeight = sizeof( VolumeHeight_t );

const string Volume2String [] = 
{
	"0x0",
	"1x1",
	"1x2",
	"1x3",
	"2x1",
	"2x2",
	"2x3"
};

// weight
typedef WORD Weight_t;
const uint szWeight= sizeof( Weight_t );

// Storage - 아이템이 저장되는 위치를 나타낸다.
enum Storage 
{
	STORAGE_INVENTORY,			//  0
	STORAGE_GEAR,				//  1
	STORAGE_BELT,				//  2
	STORAGE_EXTRASLOT,			//  3
	STORAGE_MOTORCYCLE,			//  4
	STORAGE_ZONE,				//  5
	STORAGE_STORE,				//  6
	STORAGE_BOX,				//  7
	STORAGE_CORPSE,				//  8
	STORAGE_STASH,				//  9
	STORAGE_GARBAGE,			// 10
	STORAGE_TIMEOVER,			// 11
	STORAGE_GOODSINVENTORY,		// 12
	STORAGE_PET_STASH			// 13	// pet 보관함
};

typedef BYTE Storage_t;
const uint szStorage = sizeof(Storage_t);

// Durability
typedef DWORD Durability_t;
const uint szDurability = sizeof(Durability_t);

// 사정거리
typedef BYTE Range_t;
const uint szRange = sizeof(Range_t);

// Inventory 좌표
typedef BYTE CoordInven_t;
const uint szCoordInven = sizeof( CoordInven_t );

// 아이템 생성 확률 (상점 및 몬스터 해치웠을 때)
typedef uint Ratio_t;
const uint szRatio = sizeof(Ratio_t);

// Item의 FlagType
typedef BYTE FlagType_t;
const uint szFlagType = sizeof( FlagType_t );

// Inventory의 Item갯수
typedef BYTE ItemNum_t;
const uint szItemNum = sizeof( ItemNum_t );

// 내구성, 유지시간
typedef WORD Duration_t;
const uint szDuration = sizeof( Duration_t );

// 탄환수
typedef BYTE Bullet_t;
const uint szBullet = sizeof( Bullet_t );

// 사정거리 나중에 지울 것임.. 현재는 이걸로 돼 있는게 넘 많아서..
typedef BYTE Distance_t;
const uint szDistance = sizeof( Distance_t );

// 상승부위
typedef BYTE AscentPart_t;
const uint szAscentPart = sizeof( AscentPart_t );

// 변화수치
typedef BYTE PlusValue_t;
const uint szPlusValue = sizeof( PlusValue_t );

// 스피드
typedef BYTE Speed_t;
const uint szSpeed = sizeof( Speed_t );

// 벨트 포켓숫자
typedef BYTE PocketNum_t;
const uint szPocketNum = sizeof(PocketNum_t);

// 폭탄 재료 숫자
typedef BYTE MaterialNum_t;
const uint szMaterialNum = sizeof(MaterialNum_t);

// 보관함 랙의 최대 숫자
const int STASH_RACK_MAX = 3;

// 보관함 한 랙에 들어갈 수 있는 최대 아이템의 숫자
const int STASH_INDEX_MAX = 20;

// 은 코팅 타입
typedef unsigned short Silver_t ;
const uint szSilver = sizeof(Silver_t);

// 아이템 등급
typedef int Grade_t;
const uint szGrade = sizeof(Grade_t);

// 인첸트 레벨 
typedef char EnchantLevel_t;
const uint szEnchantLevel = sizeof(EnchantLevel_t);

// 성별 관련 제한 요소
enum GenderRestriction
{
	GENDER_BOTH = 0,
	GENDER_MALE,
	GENDER_FEMALE,
	GENDER_MAX
};

// 크리스마스 이벤트 관련 클래스
enum
{
	STAR_COLOR_BLACK = 0,
	STAR_COLOR_RED,
	STAR_COLOR_BLUE,
	STAR_COLOR_GREEN,
	STAR_COLOR_CYAN,
	STAR_COLOR_WHITE,
	STAR_COLOR_PINK,
	STAR_COLOR_MAX
};

class XMAS_STAR
{
public:
	XMAS_STAR() { color = STAR_COLOR_MAX; amount = 0; }

public:
	int color;
	int amount;
};

enum
{
	SHRINE_ARMEGA,		// 0
	SHRINE_MIHOLE,		// 1
	SHRINE_KIRO,		// 2
	SHRINE_INI,			// 3
	SHRINE_GREGORI,		// 4
	SHRINE_CONCILIA,	// 5
	SHRINE_LEGIOS,		// 6
	SHRINE_HILLEL,		// 7
	SHRINE_JAVE,		// 8
	SHRINE_NEMA,		// 9
	SHRINE_AROSA,		// 10
	SHRINE_CHASPA		// 11
};

typedef WORD ShrineID_t;
const uint szShrineID = sizeof(ShrineID_t);

typedef BYTE BloodBibleBonusType_t;
const uint szBloodBibleBonusType = sizeof(BloodBibleBonusType_t);

typedef BYTE SweeperBonusType_t;
const uint szSweeperBonusType = sizeof(SweeperBonusType_t);

#endif
