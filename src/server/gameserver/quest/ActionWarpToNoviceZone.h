//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpToNoviceZone.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_TO_NOVICE_ZONE_H__
#define __ACTION_WARP_TO_NOVICE_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpToNoviceZone
//////////////////////////////////////////////////////////////////////////////

class ActionWarpToNoviceZone : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_WARP_TO_NOVICE_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t    getNoviceZoneID(void) const throw() { return m_NoviceZoneID; }
	ZoneCoord_t getNoviceX(void) const throw() { return m_NoviceX; }
	ZoneCoord_t getNoviceY(void) const throw() { return m_NoviceY; }

	ZoneID_t    getBeginnerZoneID(void) const throw() { return m_BeginnerZoneID; }
	ZoneCoord_t getBeginnerX(void) const throw() { return m_BeginnerX; }
	ZoneCoord_t getBeginnerY(void) const throw() { return m_BeginnerY; }

private:
	ZoneID_t    m_NoviceZoneID;
	ZoneCoord_t m_NoviceX;
	ZoneCoord_t m_NoviceY;

	ZoneID_t    m_BeginnerZoneID;
	ZoneCoord_t m_BeginnerX;
	ZoneCoord_t m_BeginnerY;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpToNoviceZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpToNoviceZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_WARP_TO_NOVICE_ZONE; }
	virtual string getActionName() const throw() { return "WarpToNoviceZone"; }
	virtual Action* createAction() const throw() { return new ActionWarpToNoviceZone(); }
};
#endif
