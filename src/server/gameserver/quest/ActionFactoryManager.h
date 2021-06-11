//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionFactoryManager.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_FACTORY_MANAGER_H__
#define __ACTION_FACTORY_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionFactoryManager
//////////////////////////////////////////////////////////////////////////////

class ActionFactoryManager 
{
public:
	ActionFactoryManager() ;
	~ActionFactoryManager() ;

public:
	void init() ;
	void addFactory(ActionFactory* pFactory) ;
	Action* createAction(ActionType_t conditionType) const ;
	string getActionName(ActionType_t conditionType) const ;
	ActionType_t getActionType(const string & actionname) const ;
	string toString() const ;

private:
	ActionFactory** m_Factories;
	ushort          m_Size;
};

extern ActionFactoryManager* g_pActionFactoryManager;

#endif
