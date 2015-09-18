//////////////////////////////////////////////////////////////////////////////
// Filename    : Condition.h
// Written By  : 
// Description :
// 트리거의 액션이 실행되기 위해서 만족해야 하는 조건을 나타내는 클래스.
// 이 클래스를 상속받아서 다른 구체적인 조건들을 구현한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "Types.h"
#include "Exception.h"
#include <bitset>
#include "PropertyBuffer.h"

//////////////////////////////////////////////////////////////////////////////
// 컨디션의 체크를 위한 부가적인 파라미터를 전달하기 위한 구조체들.
//////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	ScriptID_t ScriptID;
	AnswerID_t AnswerID;
} COND_ANSWERED_BY;


////////////////////////////////////////////////////////////////////////////////
//
// class Condition;
//
////////////////////////////////////////////////////////////////////////////////
//
//* isActive() | isPassive() | isNeutral()
//
// ZoneGroupThread가 특정 존에 있는 몬스터 혹은 NPC를 처리할 때, 현재 갖고 있는
// 트리거들의 모든 컨디션이 만족하는지 체크한다. 그런데, 몬스터 혹은 NPC들은 
// 패킷 핸들러에서만 의미를 가지는 passive 컨디션을 가진 트리거를 여전히 포함
// 하고 있다. passive 컨디션들은 isSatisfied()에서 특별히 체크할 건덕지..가 없기
// 때문에 웬만하면 true 를 리턴하게 된다. 
//
// 따라서, ZGT의 처리시 passive 컨디션들은 체크될 필요가 없으며 체크되어서도 안된다.
// 이를 위해서 추가된 메쏘드들이 isActive(), isPassive() 이다.
//
// neutral 컨디션은 active | passive 둘 다와 함께 사용될 수 있는 조건들이다.
//(ex: PC_HAS_SKILL, PC_HAS_ITEM ...)
//
////////////////////////////////////////////////////////////////////////////////

class Creature;

class Condition 
{
public:

	enum ConditionTypes 
	{
		// active conditions
		CONDITION_AT_FIRST,
		CONDITION_AT_TIME,
		CONDITION_FROM_TIME_TO_TIME,
		CONDITION_IDLE,
		CONDITION_EVERY_TIME,

		// passive conditions
		CONDITION_TALKED_BY,
		CONDITION_ANSWERED_BY, // 2000.10.13 김성민이 추가
		CONDITION_BLOOD_DRAINED,
		CONDITION_FLAG_ON,
		CONDITION_FLAG_OFF,
		CONDITION_ATTR_COMP,
		CONDITION_RACE_COMP,
		CONDITION_SAME_CLAN,

		CONDITION_ATTACKED_BY,
		CONDITION_DIED_BY,
		CONDITION_RESCUED_BY,
		CONDITION_PC_ATTRIBUTE_COMP,
		CONDITION_PC_HAS_SKILL,
		CONDITION_PC_SKILL_COMP,
		CONDITION_PC_HAS_ITEM,
		CONDITION_PC_DONE_QUEST,
		CONDITION_PC_UNDER_QUEST,
		CONDITION_QUEST_COMPLETED,
		CONDITION_QUEST_STATE,

		// 2002.6.3 by sigi
		CONDITION_PAY_PLAY,
		
		// 2002.9.2 by sigi
		CONDITION_ENTER_MASTER_LAIR,	// condition체크후 action요소를 같이 처리한다. 처리의 편의를 위해서-_-;

		// 2003.1.20 by bezz, Sequoia
		CONDITION_ENTER_CASTLE,		// 포탈을 통해 성에 들어가려고 할 때
		CONDITION_HAS_ENOUGH_CASTLE_ENTRANCE_FEE,	// 성에 들어갈 입장료를 지불할 수 있는지

		// 2003.2.18 by sigi
		CONDITION_ENTER_HOLY_LAND,			// 아담의 성지에 들어갈려고 할 때
		CONDITION_ENTER_CASTLE_DUNGEON,		// (아담의 성지) 성 지하 맵에 들어갈려고할때

		CONDITION_HAS_QUEST,
		CONDITION_HAS_INVEN_SPACE,

		CONDITION_CAN_ENTER_PAY_ZONE,		// 유료존으로 들어갈 때

		CONDITION_CAN_ENTER_BEGINNER_ZONE,	// 테메리에 성지로 들어갈 때
		CONDITION_CAN_WARP_GATE,			// 워프 게이트 지나갈 수 있남?
		CONDITION_CAN_ENTER_LEVEL_WAR_ZONE,			// 워프 게이트 지나갈 수 있남?

		CONDITION_CAN_PET_QUEST,
		CONDITION_CAN_ENTER_EVENT_ZONE,

		CONDITION_EFFECT_FLAG,				// 특정 이펙트 플래그가 켜져 있는가
		CONDITION_CAN_ENTER_GDR_LAIR,		// 질드레 레어 들어갈 수 있냐

		CONDITION_EXIST_REINFORCE,			// 공성 원군 신청한 넘이 있나

		CONDITION_SIEGE_DEFENDER_SIDE,		// 수성측인가
		CONDITION_SIEGE_ATTACKER_SIDE,		// 공성측인가

		CONDITION_NOT_GUILD_MEMBER,			// 길드에 속해 있지 않은가?
		CONDITION_IS_GUILD_MEMBER,			// 길드에 속해 있는가?

		CONDITION_CAN_ENTER_QUEST_ZONE,		// 퀘스트존에 들어갈 수 있는가
		CONDITION_HAS_ENOUGH_FAMILY_COIN,	// 패밀리 코인이 충분히 있는가?

		CONDITION_MAX
	};

public :
	virtual ~Condition() throw(Error) {}
	virtual ConditionType_t getConditionType() const throw() = 0;

	virtual bool isActive() const throw() { return false; }
	virtual bool isPassive() const throw() { return false; }
	virtual bool isNeutral() const throw() { return false; }

	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL) const throw() = 0;

	virtual void read(PropertyBuffer & propertyBuffer) throw(Error) = 0;

	virtual string toString() const throw() = 0;

};

// Condition Set 
#define ConditionSet bitset<Condition::CONDITION_MAX>

#endif
