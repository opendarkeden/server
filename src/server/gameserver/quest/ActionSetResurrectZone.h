//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSetResurrectZone.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SET_RESURRECT_ZONE_H__
#define __ACTION_SET_RESURRECT_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSetResurrectZone;
//////////////////////////////////////////////////////////////////////////////

class ActionSetResurrectZone : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_SET_RESURRECT_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ZoneID_t getZoneID(void) const  { return m_ZoneID; }
	void setZoneID(ZoneID_t id)  { m_ZoneID = id; }

private:
	ZoneID_t m_ZoneID;
};

////////////////////////////////////////////////////////////////////////////////
// class ActionSetResurrectZoneFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSetResurrectZoneFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType() const  { return Action::ACTION_SET_RESURRECT_ZONE; }
	virtual string getActionName() const  { return "SetResurrectZone"; }
	virtual Action* createAction() const  { return new ActionSetResurrectZone(); }
};

#endif
