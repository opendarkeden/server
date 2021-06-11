////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRedeemMotorcycle.h
// Written By  : 
// Description : 
// 플레이어가 게임에 들어왔을 때, 오토바이가 어디 있건, 플레이어의 앞에
// 오토바이 객체를 생성해 주는 역할을 한다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REDEEM_MOTORCYCLE_H__
#define __ACTION_REDEEM_MOTORCYCLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRedeemMotorcycle;
//////////////////////////////////////////////////////////////////////////////

class Item;
class Zone;
class Slayer;

class ActionRedeemMotorcycle : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_REDEEM_MOTORCYCLE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2=NULL) ;
	virtual string toString() const ;

protected:
	bool load(Item* pItem, Slayer* pSlayer, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) const ;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionRedeemMotorcycleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRedeemMotorcycleFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType() const  { return Action::ACTION_REDEEM_MOTORCYCLE; }
	virtual string getActionName() const  { return "RedeemMotorcycle"; }
	virtual Action* createAction() const  { return new ActionRedeemMotorcycle(); }
};



#endif
