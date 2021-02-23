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
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_HAS_INVEN_SPACE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();
private:
	uint	m_Height, m_Width;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasInvenSpaceFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_HAS_INVEN_SPACE; }
    virtual Condition* createCondition() const throw() { return new ConditionHasInvenSpace(); }
    virtual string getConditionName() const throw() { return "HasInvenSpace"; }
};

#endif
