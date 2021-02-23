////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionIsGuildMember.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __IS_GUILD_MEMBER_H__
#define __IS_GUILD_MEMBER_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionIsGuildMember;
//////////////////////////////////////////////////////////////////////////////

class ConditionIsGuildMember : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_IS_GUILD_MEMBER; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionIsGuildMemberFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionIsGuildMemberFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_IS_GUILD_MEMBER; }
    virtual Condition* createCondition() const throw() { return new ConditionIsGuildMember(); }
    virtual string getConditionName() const throw() { return "IsGuildMember"; }
};

#endif
