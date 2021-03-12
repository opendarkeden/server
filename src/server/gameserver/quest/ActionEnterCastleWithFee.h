//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterCastleWithFee.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_CASTLE_WITH_FEE_H__
#define __ACTION_ENTER_CASTLE_WITH_FEE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterCastleWithFee
//////////////////////////////////////////////////////////////////////////////

class ActionEnterCastleWithFee : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_ENTER_CASTLE_WITH_FEE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ZoneID_t    getZoneID(void) const  { return m_ZoneID; }
	ZoneCoord_t getX(void) const  { return m_X; }
	ZoneCoord_t getY(void) const  { return m_Y; }

private:
	ZoneID_t    m_ZoneID;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterCastleWithFeeFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterCastleWithFeeFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_ENTER_CASTLE_WITH_FEE; }
	virtual string getActionName() const  { return "EnterCastleWithFee"; }
	virtual Action* createAction() const  { return new ActionEnterCastleWithFee(); }
};
#endif
