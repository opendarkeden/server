//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRecallSiege.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_RECALL_SIEGE_H__
#define __ACTION_RECALL_SIEGE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRecallSiege
//////////////////////////////////////////////////////////////////////////////

class ActionRecallSiege : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_RECALL_SIEGE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private:
	ZoneID_t    m_ZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRecallSiegeFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRecallSiegeFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_RECALL_SIEGE; }
	virtual string getActionName() const  { return "RecallSiege"; }
	virtual Action* createAction() const  { return new ActionRecallSiege(); }
};
#endif
