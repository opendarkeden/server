//////////////////////////////////////////////////////////////////////////////
// Filename    : CreatureTypes.h
// Written By  : Reiot
//////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_TYPES_H__
#define __CREATURE_TYPES_H__

#include "SystemTypes.h"
#ifdef __GAME_CLIENT__
	#include "ModifyDef.h"
	#include "PacketItemDef.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Player Character Type
//////////////////////////////////////////////////////////////////////////////
enum PCType 
{ 
	PC_SLAYER,
	PC_VAMPIRE,
	PC_OUSTERS
};
const string PCType2String[] = 
{
	"PC_SLAYER",
	"PC_VAMPIRE",
	"PC_OUSTERS"
};
const uint szPCType = szBYTE;

enum RaceType
{
	RACE_SLAYER,
	RACE_VAMPIRE,
	RACE_OUSTERS
};

//////////////////////////////////////////////////////////////////////////////
// 종족
//////////////////////////////////////////////////////////////////////////////
typedef BYTE Race_t;
const int szRace = sizeof(Race_t);

//////////////////////////////////////////////////////////////////////////////
// 권한
//////////////////////////////////////////////////////////////////////////////
enum Competence 
{
	GOD = 0,
	DM,
	HELPER,
	PLAYER
};

//////////////////////////////////////////////////////////////////////////////
// 클라이언트와 복장 공유를 위한...
//////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
enum ADDON
{
	ADDON_HAIR,			// 머리
	ADDON_HELM,			// 모자
	ADDON_COAT,			// 상의
	ADDON_TROUSER,		// 하의
	ADDON_LEFTHAND,		// 왼손			
	ADDON_RIGHTHAND,	// 오른손
	ADDON_MOTOR,		// 오토바이
	ADDON_SHOULDER,		// 어깨
	ADDON_MAX
};
#endif

enum HelmetType 
{ 
	HELMET_NONE , 
	HELMET1 ,
	HELMET2 ,
	HELMET3 ,
	HELMET_MAX
};

const string HelmetType2String[] = 
{ 
	"HELMET_NONE" , 
	"HELMET1" ,
	"HELMET2" ,
	"HELMET3"
};

enum JacketType 
{ 
	JACKET_BASIC , 
	JACKET1 , 
	JACKET2 ,
	JACKET3 ,
	JACKET4 ,
	JACKET_MAX
};

const string JacketType2String[] = 
{ 
	"JACKET_BASIC" , 
	"JACKET1", 
	"JACKET2" ,
	"JACKET3" ,
	"JACKET4"
};

enum PantsType 
{ 
	PANTS_BASIC , 
	PANTS1 , 
	PANTS2 ,
	PANTS3 ,
	PANTS4 ,
	PANTS_MAX
};

const string PantsType2String[] = 
{ 
	"PANTS_BASIC", 
	"PANTS1", 
	"PANTS2",
	"PANTS3",
	"PANTS4"
};

enum WeaponType 
{ 
	WEAPON_NONE ,
	WEAPON_SWORD ,
	WEAPON_BLADE ,
	WEAPON_SR ,
	WEAPON_AR ,
	WEAPON_SG ,
	WEAPON_SMG ,
	WEAPON_CROSS ,
	WEAPON_MACE ,
	WEAPON_MAX
//	WEAPON_SHIELD ,
//	WEAPON_SWORD_SHIELD ,
};

const string WeaponType2String[] = 
{ 
	"WEAPON_NONE",
	"WEAPON_SWORD",
	"WEAPON_BLADE",
	"WEAPON_SR",
	"WEAPON_AR",
	"WEAPON_SG",
	"WEAPON_SMG",
	"WEAPON_CROSS"
	"WEAPON_MACE"
//	"WEAPON_SHIELD",
//	"WEAPON_SWORD_SHIELD",
};

enum ShieldType 
{ 
	SHIELD_NONE ,
	SHIELD1 ,
	SHIELD2 ,
	SHIELD_MAX
};

const string ShieldType2String[] = 
{ 
	"SHIELD_NONE",
	"SHIELD1",
	"SHIELD2"
};

enum MotorcycleType 
{
	MOTORCYCLE_NONE ,
	MOTORCYCLE1 ,
	MOTORCYCLE2 ,
	MOTORCYCLE3 ,
	MOTORCYCLE_MAX
};

const string MotorcycleType2String[] = 
{
	"MOTORCYCLE_NONE" ,
	"MOTORCYCLE1" ,
	"MOTORCYCLE2" ,
	"MOTORCYCLE3"
};

enum VampireCoatType 
{ 
	VAMPIRE_COAT_BASIC , 
	VAMPIRE_COAT1 , 
	VAMPIRE_COAT2 ,
	VAMPIRE_COAT3 ,
	VAMPIRE_COAT4 ,
	VAMPIRE_COAT_MAX
};

const string VampireCoatType2String[] = 
{ 
	"VAMPIRE_COAT_BASIC" , 
	"VAMPIRE_COAT1" , 
	"VAMPIRE_COAT2" ,
	"VAMPIRE_COAT3" ,
	"VAMPIRE_COAT4" ,
	"VAMPIRE_COAT_MAX"
};

enum OustersCoatType 
{ 
	OUSTERS_COAT_BASIC , 
	OUSTERS_COAT1 , 
	OUSTERS_COAT2 ,
	OUSTERS_COAT3 ,
	OUSTERS_COAT4 ,
	OUSTERS_COAT_MAX
};

const string OustersCoatType2String[] = 
{ 
	"OUSTERS_COAT_BASIC" , 
	"OUSTERS_COAT1" , 
	"OUSTERS_COAT2" ,
	"OUSTERS_COAT3" ,
	"OUSTERS_COAT4" ,
	"OUSTERS_COAT_MAX"
};

enum OustersArmType
{
	OUSTERS_ARM_GAUNTLET,
	OUSTERS_ARM_CHAKRAM,
	OUSTERS_ARM_MAX
};

const string OustersArmType2String[] =
{
	"OUSTERS_ARM_GAUNTLET",
	"OUSTERS_ARM_CHAKRAM",
	"OUSTERS_ARM_MAX"
};

enum OustersSylphType
{
	OUSTERS_SYLPH_NONE,
	OUSTERS_SYLPH1,
	OUSTERS_SYLPH_MAX
};

const string OustersSylphType2String[] =
{
	"OUSTERS_SYLPH_NONE",
	"OUSTERS_SYLPH1",
	"OUSTERS_SYLPH_MAX"
};


//////////////////////////////////////////////////////////////////////////////
// 성별
//////////////////////////////////////////////////////////////////////////////
enum Sex 
{ 
	FEMALE ,	// female == 0   -_-; why? don't know?
	MALE		// male == 1     -_-;
};
const string Sex2String [] = 
{ 
	"FEMALE" ,
	"MALE"
};
const uint szSex = szBYTE;


//////////////////////////////////////////////////////////////////////////////
// 헤어스타일
//////////////////////////////////////////////////////////////////////////////
enum HairStyle 
{ 
	HAIR_STYLE1 , 
	HAIR_STYLE2 , 
	HAIR_STYLE3 
};
const string HairStyle2String [] = 
{
	"HAIR_STYLE1" ,
	"HAIR_STYLE2" ,
	"HAIR_STYLE3"
};
const uint szHairStyle = szBYTE;


//////////////////////////////////////////////////////////////////////////////
// Slot ( MAX == 3 )
//////////////////////////////////////////////////////////////////////////////
enum Slot 
{ 
	SLOT1 , 
	SLOT2 , 
	SLOT3 ,
	SLOT_MAX
};
const string Slot2String [] = 
{
	"SLOT1" ,
	"SLOT2" ,
	"SLOT3"
};
const uint szSlot = szBYTE;


//////////////////////////////////////////////////////////////////////////////
// 색상 정보 
//////////////////////////////////////////////////////////////////////////////
typedef WORD Color_t;
const uint szColor = sizeof(Color_t);
enum ColorType 
{ 
	MAIN_COLOR , 
	SUB_COLOR 
};


//////////////////////////////////////////////////////////////////////////////
// STR/DEX/INT/HP/MP/AC/Damage...
//////////////////////////////////////////////////////////////////////////////

#define VAMP_REGENERATION_POINT 10

typedef BYTE Rank_t;
const uint szRank = sizeof(Rank_t);

typedef DWORD RankExp_t;
const uint szRankExp = sizeof(RankExp_t);

enum AttrType 
{
	ATTR_CURRENT = 0,
	ATTR_MAX,
	ATTR_BASIC
};

typedef WORD Attr_t;
const uint szAttr = sizeof(Attr_t);

// 능력치 오버로 서버 다운이 가끔 있어서..
// 둘다 350으로 돼있던걸 2000으로 수정한당. 
// (!) 이건 적당한 수준에 잡아두고 Error를 catch해서 log만 남기는게 더 좋겠지만...
// by sigi. 2002.9.16
const uint maxSlayerAttr = 2000;
const uint maxVampireAttr = 2000;
const uint maxOustersAttr = 2000;

typedef WORD HP_t;
const uint szHP = sizeof(HP_t);

typedef WORD MP_t;
const uint szMP = sizeof(MP_t);

// 방어력
typedef WORD Defense_t;
const uint szDefense = sizeof(Defense_t);

// 프로텍션
typedef WORD Protection_t;
const uint szProtection = sizeof(Protection_t);

// 명중률
typedef WORD ToHit_t;
const uint szToHit = sizeof(ToHit_t);

typedef WORD Damage_t;
const uint szDamage = sizeof(Damage_t);

typedef BYTE SkillPoint_t;
const uint szSkillPoint = sizeof(SkillPoint_t);


//////////////////////////////////////////////////////////////////////////////
// defines for MODIFY bit flag //abcd
// 기본치수 str, int, dex등의 변화에 따라서 변화된 값들이 어떤 값인가를 
// 나타냄
//////////////////////////////////////////////////////////////////////////////
#define MF_STR          0x01
#define MF_DEX          0x02
#define MF_INT          0x04
#define MF_MAX_HP       0x08
#define MF_MAX_MP       0x10
#define MF_DAM          0x20
#define MF_DEFENSE      0x40
#define MF_TOHIT        0x80

enum Attribute 
{ 
	STR = 0, 
	DEX, 
	INTE, 
	MP, 
	HP, 
	DEFENSE, 
	TOHIT, 
	PROTECT, 
	DAM, 
	SD, 
	DUR, 
	LEV, 
	MAX_ATTR 
};
	 
//////////////////////////////////////////////////////////////////////////////
// Skill 관련
//////////////////////////////////////////////////////////////////////////////
// Skill의 Type 갯수.
typedef WORD SkillType_t;
const uint szSkillType = sizeof(SkillType_t);

// Client 에서 날려주는 EffectID.
typedef WORD CEffectID_t;
const uint szCEffectID = sizeof(CEffectID_t);

// Skill Effect ID
typedef WORD EffectID_t;
const uint szEffectID = sizeof(EffectID_t);

// Slot의 갯수
typedef BYTE SlotID_t;
const uint szSlotID = sizeof(SlotID_t);

// Skill Domain
typedef BYTE SkillDomainType_t;
const uint szSkillDomainType = sizeof( SkillDomainType_t );

typedef BYTE SkillLevel_t;
const uint szSkillLevel = sizeof(SkillLevel_t);

typedef DWORD SkillExp_t;
const uint szSkillExp = sizeof(SkillExp_t);

typedef WORD ExpLevel_t;
const uint szExpLevel = sizeof(ExpLevel_t);

enum SkillDomain 
{
	SKILL_DOMAIN_BLADE = 0, // 0
	SKILL_DOMAIN_SWORD,     // 1
	SKILL_DOMAIN_GUN,       // 2
	SKILL_DOMAIN_HEAL,      // 4
	SKILL_DOMAIN_ENCHANT,   // 3
	SKILL_DOMAIN_ETC,       // 5
	SKILL_DOMAIN_VAMPIRE,   // 6
	SKILL_DOMAIN_OUSTERS,   // 6
	SKILL_DOMAIN_MAX        // 7
//	SKILL_DOMAIN_RIFLE ,    // 2...3번은 쓰이지 않쥐...
};

enum SkillGrade 
{
	SKILL_GRADE_APPRENTICE = 0, // 0
	SKILL_GRADE_ADEPT,			// 1
	SKILL_GRADE_EXPERT,			// 2
	SKILL_GRADE_MASTER,			// 3
	SKILL_GRADE_GRAND_MASTER,	// 4
	SKILL_GRADE_MAX				// 5
};

#define GRADE_APPRENTICE_LIMIT_LEVEL	24
#define GRADE_ADEPT_LIMIT_LEVEL			49
#define GRADE_EXPERT_LIMIT_LEVEL		74
#define GRADE_MASTER_LIMIT_LEVEL		99
#define GRADE_GRAND_MASTER_LIMIT_LEVEL	100

const string SkillDomain2String [] = 
{
	"SKILL_DOMAIN_BLADE",
	"SKILL_DOMAIN_SWORD",
	"SKILL_DOMAIN_GUN",
//	"SKILL_DOMAIN_RIFLE" ,
	"SKILL_DOMAIN_HEAL",	
	"SKILL_DOMAIN_ENCHANT",
	"SKILL_DOMAIN_ETC",
	"SKILL_DOMAIN_VAMPIRE"
};

//////////////////////////////////////////////////////////////////////////////
// NPC로부터 기술을 배울 때 쓰이는 상수이다.
// 모든 레벨의 기술을 다 배워서 더 이상 배울 수 없음을 나타날 때
// 패킷에다 넣어서 보내는 상수이다.
//////////////////////////////////////////////////////////////////////////////
const SkillLevel_t ALL_SKILL_LEARNED = 100;

//////////////////////////////////////////////////////////////////////////////
// PC 기타 정보 타입
//////////////////////////////////////////////////////////////////////////////
typedef DWORD Fame_t;
const uint szFame = sizeof(Fame_t);

typedef DWORD Exp_t;
const uint szExp = sizeof(Exp_t);

typedef BYTE Level_t;
const uint szLevel = sizeof(Level_t);

typedef WORD Bonus_t;
const uint szBonus = sizeof(Bonus_t);

typedef WORD SkillBonus_t;
const uint szSkillBonus = sizeof(SkillBonus_t);

typedef DWORD Gold_t;
const uint szGold = sizeof(Gold_t);

const Gold_t MAX_MONEY = 2000000000;

//////////////////////////////////////////////////////////////////////////////
// 좌표와 방향
//////////////////////////////////////////////////////////////////////////////
typedef BYTE Coord_t;
const uint szCoord = sizeof(Coord_t);

typedef BYTE Dir_t;
const uint szDir = sizeof(Dir_t);

enum Directions 
{ 
	LEFT ,
	LEFTDOWN ,
	DOWN ,
	RIGHTDOWN ,
	RIGHT ,
	RIGHTUP ,
	UP ,
	LEFTUP ,
	DIR_MAX ,
	DIR_NONE = DIR_MAX
};
const string Dir2String [] = 
{
	"LEFT" ,
	"LEFTDOWN" ,
	"DOWN" ,
	"RIGHTDOWN" ,
	"RIGHT" ,
	"RIGHTUP" ,
	"UP" ,
	"LEFTUP"
};


//////////////////////////////////////////////////////////////////////////////
// 시야 관련
//////////////////////////////////////////////////////////////////////////////

typedef BYTE Vision_t;
const uint szVision = sizeof(Vision_t);

// 캐릭터의 가로/세로 시야 범위의 최대값. 시야 범위는 상하가 비대칭이다.
//const Coord_t maxViewportWidth  = 9;
//const Coord_t maxViewportUpperHeight = 10;
//const Coord_t maxViewportLowerHeight = 10;
//
//const Coord_t maxViewportWidth  = 12;
//const Coord_t maxViewportUpperHeight = 13;
//const Coord_t maxViewportLowerHeight = 13;
//const Coord_t maxViewportWidth  = 14;
//const Coord_t maxViewportUpperHeight = 14;
//const Coord_t maxViewportLowerHeight = 14;

// 시야사각형(vision)의 가로/세로 크기
//const Coord_t maxVisionWidth = maxViewportWidth * 2 + 1;
//const Coord_t maxVisionHeight = maxViewportUpperHeight + maxViewportLowerHeight + 1;

// 시야 레벨
typedef BYTE Sight_t;
const uint szSight = sizeof(Sight_t); 
const Sight_t minSight = 0;
const Sight_t maxSight = 13;


//////////////////////////////////////////////////////////////////////////////
// 게임 내에서의 턴(0.1초)을 계산할 때 사용한다.
//////////////////////////////////////////////////////////////////////////////
typedef DWORD Turn_t;
const uint szTurn = sizeof(Turn_t);


//////////////////////////////////////////////////////////////////////////////
// 몬스터
//////////////////////////////////////////////////////////////////////////////
typedef WORD MonsterType_t;
const uint szMonsterType = sizeof(MonsterType_t);

typedef WORD SpriteType_t;
const uint szSpriteType = sizeof(SpriteType_t);

typedef BYTE Moral_t;
const uint szMoral = sizeof(Moral_t);


//////////////////////////////////////////////////////////////////////////////
// NPC
//////////////////////////////////////////////////////////////////////////////
typedef WORD NPCType_t;
const uint szNPCType = sizeof(NPCType_t);

typedef WORD NPCID_t;
const uint szNPCID = sizeof(NPCID_t);

//////////////////////////////////////////////////////////////////////////////
// 핸드폰&슬랏 관련
//////////////////////////////////////////////////////////////////////////////
#define MAX_PHONE_SLOT  3
typedef DWORD PhoneNumber_t;
const uint szPhoneNumber = sizeof(PhoneNumber_t);

enum Alignment {
	LESS_EVIL,
	EVIL,
	NEUTRAL,
	GOOD,
	MORE_GOOD
};

typedef int Alignment_t;
const uint szAlignment= sizeof(Alignment_t);

//////////////////////////////////////////////////////////////////////////////
// hp, mp steal & regeneration
//////////////////////////////////////////////////////////////////////////////
typedef BYTE Steal_t;
const uint szSteal = sizeof(Steal_t);

typedef BYTE Regen_t;
const uint szRegen = sizeof(Regen_t);

//////////////////////////////////////////////////////////////////////////////
// Luck
//////////////////////////////////////////////////////////////////////////////
typedef short Luck_t;
const uint szLuck = sizeof(Luck_t);

//////////////////////////////////////////////////////////////////////////////
// 마법 저항력
//////////////////////////////////////////////////////////////////////////////
typedef short Resist_t;
const uint szResist = sizeof(Resist_t);

enum MagicDomain
{
	MAGIC_DOMAIN_NO_DOMAIN = 0, // 무속성 마법
	MAGIC_DOMAIN_POISON    = 1, // 독 계열 마법
	MAGIC_DOMAIN_ACID      = 2, // 산 계열 마법
	MAGIC_DOMAIN_CURSE     = 3, // 저주 계열 마법
	MAGIC_DOMAIN_BLOOD     = 4, // 피 계열 마법

	MAGIC_DOMAIN_MAX
};

const string MagicDomain2String[] = 
{
	"NO_DOMAIN", // 무속성 마법
	"POISON",    // 독 계열 마법
	"ACID",      // 산 계열 마법
	"CURSE",     // 저주 계열 마법
	"BLOOD",     // 피 계열 마법
	"MAGIC_DOMAIN_MAX"
};

const int MAX_RESIST = 90;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
typedef BYTE Shape_t;
const uint szShape = sizeof(Shape_t);
enum Shape
{
	SHAPE_NORMAL = 0,
	SHAPE_WOLF,
	SHAPE_BAT,
	SHAPE_WERWOLF,
	SHAPE_MAX
};

//////////////////////////////////////////////////////////////////////////////
// 기술의 타겟 타입
// 비트 플래그로써, 맞출 수 있는 타입을 결정한다.
//////////////////////////////////////////////////////////////////////////////
const uint TARGET_UNDERGROUND = 0x01;
const uint TARGET_GROUND      = 0x02;
const uint TARGET_AIR         = 0x04;

//////////////////////////////////////////////////////////////////////////////
// 클랜 타입
//////////////////////////////////////////////////////////////////////////////
typedef WORD ClanType_t;	// BYTE에서 WORD로 바꿈. by sigi. 2002.12.27
const uint szClanType = sizeof(ClanType_t);

//////////////////////////////////////////////////////////////////////////////
// 경험치 관련 세이브 주기
//////////////////////////////////////////////////////////////////////////////
const WORD ATTR_EXP_SAVE_PERIOD    = 100;
const WORD DOMAIN_EXP_SAVE_PERIOD  = 100;
const WORD SKILL_EXP_SAVE_PERIOD   = 100;
const WORD VAMPIRE_EXP_SAVE_PERIOD = 100;
const WORD ALIGNMENT_SAVE_PERIOD   = 150;
const WORD FAME_SAVE_PERIOD        = 200;
const WORD RANK_EXP_SAVE_PERIOD    = 100;
const WORD OUSTERS_EXP_SAVE_PERIOD = 100;

////////////////////////////////////////////////////////////////////////////////
//
// 시야 영역 상수들
//
// VisionState >= IN_SIGHT     : 이미 보고 있다.
// VisionState == OUT_OF_SIGHT : 보이지 않는다.
//
////////////////////////////////////////////////////////////////////////////////
enum VisionState {
	OUT_OF_SIGHT ,      // 시야 8각형의 외부 영역. 보이지 않는다.
	IN_SIGHT ,          // 시야 8각형의 내부 영역. 보인다. 이미 보고 있다.
	ON_SIGHT,           // 시야 8각형의 경계 영역. 보인다. 이미 보고 있다.
	NEW_SIGHT           // 시야 8각형의 경계 영역. 스캐닝영역. 보인다. 처음 본다.
};

const string VisionState2String [] =
{
	"OUT_OF_SIGHT" ,
	"IN_SIGHT" ,
	"ON_SIGHT" ,
	"NEW_SIGHT"
};

////////////////////////////////////////////////////////////////////////////////
// 아우스터스 엘리멘탈 속성
////////////////////////////////////////////////////////////////////////////////
enum ElementalType 
{
	ELEMENTAL_ANY = -1,
	ELEMENTAL_FIRE = 0,
	ELEMENTAL_WATER,
	ELEMENTAL_EARTH,
	ELEMENTAL_WIND,

	ELEMENTAL_SUM,

	ELEMENTAL_MAX
};

const string Elemental2SimpleString[] =
{
	"Fire",
	"Water",
	"Earth",
	"Wind",

	"Sum",
};

typedef WORD Elemental_t;
const uint szElemental = sizeof(Elemental_t);

enum ElementalDomain
{
	ELEMENTAL_DOMAIN_NO_DOMAIN = -1,	// 무속성
	ELEMENTAL_DOMAIN_FIRE = 0,			// 불계열
	ELEMENTAL_DOMAIN_WATER,				// 물계열
	ELEMENTAL_DOMAIN_EARTH,				// 대지계열
	ELEMENTAL_DOMAIN_WIND,				// 바람계열
	ELEMENTAL_DOMAIN_COMBAT,			// 전투 일반 계열
	ELEMENTAL_DOMAIN_ELEMENTAL_COMBAT,	// 전투 정령 계열
	ELEMENTAL_DOMAIN_ETC,				// 기타(계열구분없음)

	ELEMENTAL_DOMAIN_MAX
};

#endif
