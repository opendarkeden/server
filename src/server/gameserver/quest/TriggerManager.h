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
	TriggerManager() throw(Error);
	~TriggerManager() throw(Error);

public:
	void load(const string & name) throw(Error);
	void load(ZoneID_t zoneid, int left, int top, int right, int bottom) throw(Error);

	void refresh() throw(Error);

	void addTrigger(Trigger* pTrigger) throw(DuplicatedException, Error);

	void deleteTrigger(TriggerID_t triggerID) throw(NoSuchElementException, Error);

	Trigger* getTrigger(TriggerID_t triggerID) throw(NoSuchElementException, Error);

	bool hasCondition(ConditionType_t conditionType) const throw() { return m_ConditionSet.test(conditionType); }

	list<Trigger*> & getTriggers() throw() { return m_Triggers; }
	const list<Trigger*> & getTriggers() const throw() { return m_Triggers; }

	string toString() const throw();

private:

	// bitset of condition for fastest reference
	ConditionSet m_ConditionSet;

	// list of triggers
	// 런타임에 트리거가 추가될 가능성이 있다.
    list<Trigger*> m_Triggers;

};

#endif
