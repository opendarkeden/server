//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestRegen.h
// Written By  : 
// Description : 
// 상점 NPC를 제일 처음 로딩할 때, 상점 NPC가 팔게 될 아이템을
// 준비하는 액션이다. ShopTemplate 클래스와 매니저를 참고할 것.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SIMPLE_QUEST_REGEN_H__
#define __ACTION_SIMPLE_QUEST_REGEN_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestRegen
//////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestRegen : public Action 
{
public:
	ActionSimpleQuestRegen() ;
	virtual ~ActionSimpleQuestRegen() ;
	
public:
	virtual ActionType_t getActionType() const  { return ACTION_SIMPLE_QUEST_REGEN; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private :
	Timeval                m_Period;    // 상점을 리젠할 주기
	Timeval                m_NextRegen; // 다음 상점 리젠 시간

};


////////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestRegenFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestRegenFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_SIMPLE_QUEST_REGEN; }
	virtual string getActionName() const  { return "SimpleQuestRegen"; }
	virtual Action* createAction() const  { return new ActionSimpleQuestRegen(); }

};
#endif
