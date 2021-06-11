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
	virtual ActionType_t getActionType() const  { return ACTION_SET_POSITION; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ZoneID_t getZoneID() const  { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID)  { m_ZoneID = zoneID; }

	ZoneCoord_t getX() const  { return m_X; }
	ZoneCoord_t getY() const  { return m_Y; }
	Dir_t getDir() const  { return m_Dir; }

	void setX(ZoneCoord_t x)  { m_X = x; }
	void setY(ZoneCoord_t y)  { m_Y = y; }
	void setDir(Dir_t dir)  { m_Dir = dir; }

	Creature::MoveMode getMoveMode() const  { return m_MoveMode; }	
	void setMoveMode(Creature::MoveMode moveMode)  { m_MoveMode = moveMode; }

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
    virtual ActionType_t getActionType() const  { return Action::ACTION_SET_POSITION; }
    virtual string getActionName() const  { return "SetPosition"; }
    virtual Action* createAction() const  { return new ActionSetPosition(); }
};

#endif
