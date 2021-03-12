//////////////////////////////////////////////////////////////////////////////
// Filename    : TriggerManager.h
// Written By  : 
// Description :
// 트리거들의 집합을 관리하는 클래스. 크리처/아이템/존 등 트리거를 가질
// 수 있는 객체들에 종속된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRIGGER_MANAGER_H__
#define __TRIGGER_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Trigger.h"

//////////////////////////////////////////////////////////////////////////////
// class TriggerManager;
//////////////////////////////////////////////////////////////////////////////

class TriggerManager 
{
public:
	TriggerManager() ;
	~TriggerManager() ;

public:
	void load(const string & name) ;
	void load(ZoneID_t zoneid, int left, int top, int right, int bottom) ;

	void refresh() ;

	void addTrigger(Trigger* pTrigger) ;

	void deleteTrigger(TriggerID_t triggerID) ;

	Trigger* getTrigger(TriggerID_t triggerID) ;

	bool hasCondition(ConditionType_t conditionType) const  { return m_ConditionSet.test(conditionType); }

	list<Trigger*> & getTriggers()  { return m_Triggers; }
	const list<Trigger*> & getTriggers() const  { return m_Triggers; }

	string toString() const ;

private:

	// bitset of condition for fastest reference
	ConditionSet m_ConditionSet;

	// list of triggers
	// 런타임에 트리거가 추가될 가능성이 있다.
    list<Trigger*> m_Triggers;

};

#endif
