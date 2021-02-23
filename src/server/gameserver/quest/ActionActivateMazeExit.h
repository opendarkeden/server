//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivateMazeExit.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACTIVATE_MAZE_EXIT_H__
#define __ACTION_ACTIVATE_MAZE_EXIT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionActivateMazeExit
//////////////////////////////////////////////////////////////////////////////

class ActionActivateMazeExit : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ACTIVATE_MAZE_EXIT; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t    getGoodZoneID(void) const throw() { return m_GoodZoneID; }
	ZoneCoord_t getGoodX(void) const throw() { return m_GoodX; }
	ZoneCoord_t getGoodY(void) const throw() { return m_GoodY; }
	ZoneID_t    getBadZoneID(void) const throw() { return m_BadZoneID; }
	ZoneCoord_t getBadX(void) const throw() { return m_BadX; }
	ZoneCoord_t getBadY(void) const throw() { return m_BadY; }
	int			getExitID() const throw() { return m_ExitID; }

private:
	ZoneID_t    m_GoodZoneID;
	ZoneCoord_t m_GoodX;
	ZoneCoord_t m_GoodY;
	ZoneID_t    m_BadZoneID;
	ZoneCoord_t m_BadX;
	ZoneCoord_t m_BadY;
	int			m_ExitID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionActivateMazeExitFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionActivateMazeExitFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ACTIVATE_MAZE_EXIT; }
	virtual string getActionName() const throw() { return "ActivateMazeExit"; }
	virtual Action* createAction() const throw() { return new ActionActivateMazeExit(); }
};
#endif
