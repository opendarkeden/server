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
	ConditionFactoryManager() ;
	~ConditionFactoryManager() ;

public:
	void init() ;
	void addFactory(ConditionFactory* pFactory) ;
	Condition* createCondition(ConditionType_t conditionType) const ;
	string getConditionName(ConditionType_t conditionType) const ;
	ConditionType_t getConditionType(const string & contionname) const ;
	string toString() const ;

private:
	ConditionFactory** m_Factories;
	ushort             m_Size;

};

extern ConditionFactoryManager* g_pConditionFactoryManager;

#endif
