////////////////////////////////////////////////////////////////////////////////
// Filename    : TradeManager.h
// Written by  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __TRADE_MANAGER__
#define __TRADE_MANAGER__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include <list>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////
// 교환 상태 플래그
////////////////////////////////////////////////////////////////////////////////

enum
{
	// 아이템을 옮기고 있는 상태
	TRADE_TRADING,

	// 아이템을 다 옮기고, 교환을 기다리고 있는 상태
	TRADE_FINISH,

	TRADE_MAX
};

////////////////////////////////////////////////////////////////////////////////
// class TradeInfo
////////////////////////////////////////////////////////////////////////////////

class Item;

class TradeInfo
{
///// Member methods /////
public:
	TradeInfo() ;
	~TradeInfo() ;

public:
	const string getMainName(void) const  { return m_MainName; }
	void setMainName(const string & Name)  { m_MainName = Name; }

	const string getTargetName(void) const  { return m_TargetName; }
	void setTargetName(const string & Name)  { m_TargetName = Name; }

	list<Item*> getItemList(void)  { return m_ItemList; }
	void setItemList(list<Item*> itemList)  { m_ItemList = itemList; }

	Gold_t getGold(void) const  { return m_Gold; }
	void setGold(Gold_t gold) { m_Gold = gold; }

	int getStatus(void) const  { return m_Status; }
	void setStatus(int status)  { m_Status = status; }

	bool hasItem(Item* pItem) ;
	bool addItem(Item* pItem) ;
	bool removeItem(Item* pItem) ;

	void clearAll(void) ;

	Timeval getLastOKTime(void) const { return m_LastOKTime; }
	void setLastOKTime(const Timeval& lastOKTime) { m_LastOKTime = lastOKTime; }
	void setNextTime(const Timeval& currentTime);
	bool isValidOKTime(const Timeval& currentTime);

protected:
	string 		m_MainName;
	string 		m_TargetName;
	list<Item*> m_ItemList;
	Gold_t      m_Gold;
	int         m_Status;
	Timeval     m_LastOKTime;
};


////////////////////////////////////////////////////////////////////////////////
// class TradeManager
////////////////////////////////////////////////////////////////////////////////

class Creature;

class TradeManager
{
///// Member methods /////
public:
	TradeManager() ;
	~TradeManager() ;

public:
	void init() ;

	bool hasTradeInfo(const string & Name) ;

	TradeInfo* getTradeInfo(const string & Name) ;

	void addTradeInfo(TradeInfo* pInfo) ;

	void removeTradeInfo(const string & Name) ;

public:

	void initTrade(Creature* pCreature1, Creature* pCreature2) ;
	// 트레이드 할 수 없으면 0, 선물 상자 조건 때문에 못하면 2, 할 수 있으면 1
	int canTrade(Creature* pCreature1, Creature* pCreature2) ;
	void processTrade(Creature* pCreature1, Creature* pCreature2) ;
	void cancelTrade(Creature* pCreature1, Creature* pCreature2) ;
	void cancelTrade(Creature* pCreature1) ;
	bool isTrading(Creature* pCreature1, Creature* pCreature2) ;

///// Member data /////
protected:
	unordered_map<string, TradeInfo*> m_InfoMap;
};

#endif

