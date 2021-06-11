//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_QUEST_ZONE_H__
#define __ACTION_ENTER_QUEST_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterQuestZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterQuestZone : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_ENTER_QUEST_ZONE; }
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
// class ActionEnterQuestZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterQuestZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_ENTER_QUEST_ZONE; }
	virtual string getActionName() const  { return "EnterQuestZone"; }
	virtual Action* createAction() const  { return new ActionEnterQuestZone(); }
};
#endif
