//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionClearRankBonus.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CLEAR_RANK_BONUS_H__
#define __ACTION_CLEAR_RANK_BONUS_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionClearRankBonus;
//////////////////////////////////////////////////////////////////////////////

class ActionClearRankBonus : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_CLEAR_RANK_BONUS; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	Rank_t m_Rank;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionClearRankBonusFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionClearRankBonusFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_CLEAR_RANK_BONUS; }
	virtual string getActionName() const throw() { return "ClearRankBonus"; }
    virtual Action* createAction() const throw() { return new ActionClearRankBonus(); }
};

#endif
