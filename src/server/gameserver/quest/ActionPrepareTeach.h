//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareTeach.h
// Written By  : 
// Description : 
// 교관 NPC가 가르쳐 줄 수 있는 기술의 종류를 정하는 액션이다.
// PrepareShop과 비슷하게 AtFirst 컨디션을 이용하여 처음
// 한번만 실행하고 다시는 실행하지 않는다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PREPARE_TEACH_H__
#define __ACTION_PREPARE_TEACH_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareTeach;
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareTeach : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_PREPARE_TEACH; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	SkillLevel_t getMaxLevel(void) const  { return m_MaxLevel;}
	void setMaxLevel(SkillLevel_t level)  { m_MaxLevel = level;}

private:
	SkillLevel_t m_MaxLevel; // 가르쳐 줄 스킬의 맥스 레벨

};


//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareTeachFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareTeachFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_PREPARE_TEACH; }
	virtual string getActionName() const  { return "PrepareTeach"; }
	virtual Action* createAction() const  { return new ActionPrepareTeach(); }

};

#endif
