//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRegenShop.h
// Written By  : 
// Description : 
// 상점 NPC를 제일 처음 로딩할 때, 상점 NPC가 팔게 될 아이템을
// 준비하는 액션이다. ShopTemplate 클래스와 매니저를 참고할 것.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REGEN_SHOP_H__
#define __ACTION_REGEN_SHOP_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRegenShop
//////////////////////////////////////////////////////////////////////////////

class ActionRegenShop : public Action 
{
public:
	ActionRegenShop() ;
	virtual ~ActionRegenShop() ;
	
public:
	virtual ActionType_t getActionType() const  { return ACTION_REGEN_SHOP; }
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
// class ActionRegenShopFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionRegenShopFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_REGEN_SHOP; }
	virtual string getActionName() const  { return "RegenShop"; }
	virtual Action* createAction() const  { return new ActionRegenShop(); }

};
#endif
