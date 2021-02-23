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
	ActionRegenShop() throw();
	virtual ~ActionRegenShop() throw();
	
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_REGEN_SHOP; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	void addListElement(ShopTemplateID_t id) throw() { m_List.push_back(id); }
	void clearList() throw() { m_List.clear(); }

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_REGEN_SHOP; }
	virtual string getActionName() const throw() { return "RegenShop"; }
	virtual Action* createAction() const throw() { return new ActionRegenShop(); }

};
#endif
