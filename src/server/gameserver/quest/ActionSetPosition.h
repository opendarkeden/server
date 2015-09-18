//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSetPosition.h
// Written By  : 
// Description :
// NPC 의 초기 위치를 설정한다.  1회만 실행되어야 한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SET_POSITION_H__
#define __ACTION_SET_POSITION_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSetPosition;
//////////////////////////////////////////////////////////////////////////////

class ActionSetPosition : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SET_POSITION; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID) throw() { m_ZoneID = zoneID; }

	ZoneCoord_t getX() const throw() { return m_X; }
	ZoneCoord_t getY() const throw() { return m_Y; }
	Dir_t getDir() const throw() { return m_Dir; }

	void setX(ZoneCoord_t x) throw() { m_X = x; }
	void setY(ZoneCoord_t y) throw() { m_Y = y; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }

	Creature::MoveMode getMoveMode() const throw() { return m_MoveMode; }	
	void setMoveMode(Creature::MoveMode moveMode) throw() { m_MoveMode = moveMode; }

private:
	ZoneID_t           m_ZoneID;
	ZoneCoord_t        m_X;
	ZoneCoord_t        m_Y;
	Dir_t              m_Dir;
	Creature::MoveMode m_MoveMode;
};

////////////////////////////////////////////////////////////////////////////////
// class ActionSetPositionFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSetPositionFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_SET_POSITION; }
    virtual string getActionName() const throw() { return "SetPosition"; }
    virtual Action* createAction() const throw() { return new ActionSetPosition(); }
};

#endif
