////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFlagOff.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __FLAG_OFF_H__
#define __FLAG_OFF_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionFlagOff;
//////////////////////////////////////////////////////////////////////////////

class ConditionFlagOff : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_FLAG_OFF; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:
	int getIndex(void) const  { return m_Index; }
	void setIndex(int index)  { m_Index = index; }

private:
	int m_Index; // 플래그의 값

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionFlagOffFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionFlagOffFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_FLAG_OFF; }
    virtual Condition* createCondition() const  { return new ConditionFlagOff(); }
    virtual string getConditionName() const  { return "FlagOff"; }
};

#endif
