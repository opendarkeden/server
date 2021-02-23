//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFactoryManager.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONDITION_FACTORY_MANAGER_H__
#define __CONDITION_FACTORY_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Condition.h"
#include "ConditionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionFactoryManager
//////////////////////////////////////////////////////////////////////////////

class ConditionFactoryManager 
{
public:
	ConditionFactoryManager() throw();
	~ConditionFactoryManager() throw();

public:
	void init() throw(Error);
	void addFactory(ConditionFactory* pFactory) throw(Error);
	Condition* createCondition(ConditionType_t conditionType) const throw(Error);
	string getConditionName(ConditionType_t conditionType) const throw(Error);
	ConditionType_t getConditionType(const string & contionname) const throw(Error);
	string toString() const throw();

private:
	ConditionFactory** m_Factories;
	ushort             m_Size;

};

extern ConditionFactoryManager* g_pConditionFactoryManager;

#endif
