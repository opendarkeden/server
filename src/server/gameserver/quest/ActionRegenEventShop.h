//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRegenEventShop.h
// Written By  : excel96
// Description : 
// 크리스마스 이벤트용 상점을 갱신하는 액션
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REGEN_EVENT_SHOP_H__
#define __ACTION_REGEN_EVENT_SHOP_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRegenEventShop
//////////////////////////////////////////////////////////////////////////////

class ActionRegenEventShop : public Action 
{
public:
	ActionRegenEventShop() ;
	virtual ~ActionRegenEventShop() ;
	
public:
	virtual ActionType_t getActionType() const  { return ACTION_REGEN_EVENT_SHOP; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	void addListElement(ShopTemplateID_t id)  { m_List.push_back(id); }
	void clearList()  { m_List.clear(); }

private :
	list<ShopTemplateID_t> m_List;      // Shop template ID list
	Timeval                m_Period;    // 상점을 리젠할 주기
	Timeval                m_NextRegen; // 다음 상점 리젠 시간

};


////////////////////////////////////////////////////////////////////////////////
// class ActionRegenEventShopFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionRegenEventShopFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_REGEN_EVENT_SHOP; }
	virtual string getActionName() const  { return "RegenEventShop"; }
	virtual Action* createAction() const  { return new ActionRegenEventShop(); }
};

#endif
