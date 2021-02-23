//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterPKZone.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_PK_ZONE_H__
#define __ACTION_ENTER_PK_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterPKZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterPKZone : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ENTER_PK_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t    getZoneID(void) const throw() { return m_ZoneID; }

private:
	ZoneID_t    m_ZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterPKZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterPKZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ENTER_PK_ZONE; }
	virtual string getActionName() const throw() { return "EnterPKZone"; }
	virtual Action* createAction() const throw() { return new ActionEnterPKZone(); }
};
#endif
