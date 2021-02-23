//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAcceptReinforce.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACCEPT_REINFORCE_H__
#define __ACTION_ACCEPT_REINFORCE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptReinforce
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptReinforce : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ACCEPT_REINFORCE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t	getZoneID() const { return m_ZoneID; }
	void		setZoneID( ZoneID_t ZoneID ) { m_ZoneID = ZoneID; }

private:
	ZoneID_t	m_ZoneID;	// 전쟁을 신청한 성의 ZoneID
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptReinforceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptReinforceFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ACCEPT_REINFORCE; }
	virtual string getActionName() const throw() { return "AcceptReinforce"; }
	virtual Action* createAction() const throw() { return new ActionAcceptReinforce(); }
};
#endif
