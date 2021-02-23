////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEffectFlag.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FLAG_H__
#define __EFFECT_FLAG_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Effect.h"

class Creature;

//////////////////////////////////////////////////////////////////////////////
// class ConditionEffectFlag;
//////////////////////////////////////////////////////////////////////////////

class ConditionEffectFlag : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_EFFECT_FLAG; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:
	Effect::EffectClass getIndex(void) const throw() { return m_Index; }
	void setIndex(Effect::EffectClass index) throw() { m_Index = index; }

private:
	Effect::EffectClass m_Index; // 플래그의 값

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEffectFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEffectFlagFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_EFFECT_FLAG; }
    virtual Condition* createCondition() const throw() { return new ConditionEffectFlag(); }
    virtual string getConditionName() const throw() { return "EffectFlag"; }
};

#endif
