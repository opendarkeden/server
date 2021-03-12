////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAS_INVEN_SPACE_H__
#define __HAS_INVEN_SPACE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasInvenSpace : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_HAS_INVEN_SPACE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;
private:
	uint	m_Height, m_Width;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasInvenSpaceFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_HAS_INVEN_SPACE; }
    virtual Condition* createCondition() const  { return new ConditionHasInvenSpace(); }
    virtual string getConditionName() const  { return "HasInvenSpace"; }
};

#endif
