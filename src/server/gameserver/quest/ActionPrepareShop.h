//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPrepareShop.h
// Written By  : 
// Description : 
// 상점 NPC를 제일 처음 로딩할 때, 상점 NPC가 팔게 될 아이템을
// 준비하는 액션이다. ShopTemplate 클래스와 매니저를 참고할 것.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PREPARE_SHOP_H__
#define __ACTION_PREPARE_SHOP_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareShop
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareShop : public Action 
{
public:
	ActionPrepareShop() throw();
	virtual ~ActionPrepareShop() throw();
	
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_PREPARE_SHOP; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	BYTE getListNum() const throw() { return m_ListNum;}
	void setListNum(BYTE num) throw() { m_ListNum = num;}

	void addListElement(ShopTemplateID_t id) throw();
	void clearList() throw() { m_List.clear(); m_ListNum = 0; }

private :
	BYTE                   m_ListNum;
	list<ShopTemplateID_t> m_List;
	MarketCond_t           m_MarketCondBuy;
	MarketCond_t           m_MarketCondSell;
	ZoneID_t			   m_TaxingCastleZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPrepareShopFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPrepareShopFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_PREPARE_SHOP; }
	virtual string getActionName() const throw() { return "PrepareShop"; }
	virtual Action* createAction() const throw() { return new ActionPrepareShop(); }
};

#endif
