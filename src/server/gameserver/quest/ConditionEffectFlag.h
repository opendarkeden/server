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
	virtual ConditionType_t getConditionType() const  { return CONDITION_EFFECT_FLAG; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:
	Effect::EffectClass getIndex(void) const  { return m_Index; }
	void setIndex(Effect::EffectClass index)  { m_Index = index; }

private:
	Effect::EffectClass m_Index; // 플래그의 값

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEffectFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEffectFlagFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_EFFECT_FLAG; }
    virtual Condition* createCondition() const  { return new ConditionEffectFlag(); }
    virtual string getConditionName() const  { return "EffectFlag"; }
};

#endif
