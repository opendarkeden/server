////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionNotGuildMember.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __NOT_GUILD_MEMBER_H__
#define __NOT_GUILD_MEMBER_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionNotGuildMember;
//////////////////////////////////////////////////////////////////////////////

class ConditionNotGuildMember : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_NOT_GUILD_MEMBER; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionNotGuildMemberFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionNotGuildMemberFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_NOT_GUILD_MEMBER; }
    virtual Condition* createCondition() const throw() { return new ConditionNotGuildMember(); }
    virtual string getConditionName() const throw() { return "NotGuildMember"; }
};

#endif
