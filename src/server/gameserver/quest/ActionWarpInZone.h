//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpInZone.h
// Written By  : 
// Description :
// 현재 위치에서 왔다갔다 방황하는 크리처를 표현할때 사용하는 액션이다.
// 크리처가 현재 위치를 중심으로 반경 r 안의 사각 영역에서 
// M 퍼센트의 확률로 이동하게 된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_IN_ZONE_H__
#define __ACTION_WARP_IN_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpInZone;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpInZone : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_WARP_IN_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public :
	BYTE getMovePercentage() const  { return m_MovePercentage; }
	void setMovePercentage(BYTE movePercentage)  { m_MovePercentage = movePercentage; }

private :
	BYTE        m_MovePercentage;	
	
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpInZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpInZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_WARP_IN_ZONE; }
	virtual string getActionName() const  { return "WarpInZone"; }
	virtual Action* createAction() const  { return new ActionWarpInZone(); }

};

#endif
