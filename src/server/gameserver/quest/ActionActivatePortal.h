//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivatePortal.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACTIVATE_PORTAL_H__
#define __ACTION_ACTIVATE_PORTAL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionActivatePortal
//////////////////////////////////////////////////////////////////////////////

class ActionActivatePortal : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_ACTIVATE_PORTAL; }
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
// class ActionActivatePortalFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionActivatePortalFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_ACTIVATE_PORTAL; }
	virtual string getActionName() const  { return "ActivatePortal"; }
	virtual Action* createAction() const  { return new ActionActivatePortal(); }
};
#endif
