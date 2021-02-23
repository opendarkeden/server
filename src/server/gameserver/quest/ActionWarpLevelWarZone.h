//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpLevelWarZone.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_LEVEL_WAR_ZONE_H__
#define __ACTION_WARP_LEVEL_WAR_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpLevelWarZone;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpLevelWarZone : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_WARP_LEVEL_WAR_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public :

private :
	
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpLevelWarZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpLevelWarZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_WARP_LEVEL_WAR_ZONE; }
	virtual string getActionName() const throw() { return "WarpLevelWarZone"; }
	virtual Action* createAction() const throw() { return new ActionWarpLevelWarZone(); }

};

#endif
