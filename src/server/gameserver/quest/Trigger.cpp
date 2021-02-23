////////////////////////////////////////////////////////////////////////////////
// Filename    : Trigger.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "Trigger.h"
#include "Condition.h"
#include "ConditionFactoryManager.h"
#include "Action.h"
#include "ActionFactoryManager.h"
#include "Assert.h"
#include "Utility.h"
#include "PropertyBuffer.h"


////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
Trigger::Trigger () 
	throw (Error)
{
	__BEGIN_TRY

	m_TriggerType = NPC_TRIGGER;
	m_TriggerID   = 0;
	m_QuestID     = 0;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
Trigger::~Trigger () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// add condition
////////////////////////////////////////////////////////////////////////////////
void Trigger::addCondition (Condition * pCondition)
	throw (Error)
{
	__BEGIN_TRY

	m_Conditions.push_back(pCondition);

	// set condition set
	m_ConditionSet.set(pCondition->getConditionType());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// add action
////////////////////////////////////////////////////////////////////////////////
void Trigger::addAction (Action * pAction)
	throw (Error)
{
	__BEGIN_TRY

	m_Actions.push_back(pAction);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// add counter action
////////////////////////////////////////////////////////////////////////////////
void Trigger::addCounterAction (Action * pAction)
	throw (Error)
{
	__BEGIN_TRY

	m_CounterActions.push_back(pAction);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// is all conditions satisfied?
////////////////////////////////////////////////////////////////////////////////
bool Trigger::isAllSatisfied (TriggerMode triggerMode , Creature * pCreature1 , Creature * pCreature2, void* pParam) const
	throw (Error)
{
	__BEGIN_TRY

	uint nConditions = m_Conditions.size();

	for (uint i = 0 ; i < nConditions ; i ++)
	{
		Assert(m_Conditions[i] != NULL);

		if ((triggerMode == ACTIVE_TRIGGER  && m_Conditions[i]->isPassive())  ||
			   (triggerMode == PASSIVE_TRIGGER && m_Conditions[i]->isActive())   ||
			   (triggerMode == NEUTRAL_TRIGGER && !m_Conditions[i]->isNeutral()) ||
			   (!m_Conditions[i]->isSatisfied(pCreature1 , pCreature2, pParam)))
		{
			return false;
		}
	}

	return true;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// activate trigger
////////////////////////////////////////////////////////////////////////////////
bool Trigger::activate (Creature * pCreature1 , Creature * pCreature2) const
	throw (Error)
{
	__BEGIN_TRY

	uint nActions = m_Actions.size();

	if (nActions == 0) return false;

	for (uint i = 0 ; i < nActions ; i ++)
	{
		Assert(m_Actions[i] != NULL);
		
		m_Actions[i]->execute(pCreature1 , pCreature2);
	}

	return true;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// activate trigger
////////////////////////////////////////////////////////////////////////////////
bool Trigger::activateCounter (Creature * pCreature1 , Creature * pCreature2) const
	throw (Error)
{
	__BEGIN_TRY

	uint nActions = m_CounterActions.size();

	if (nActions == 0) return false;

	for (uint i = 0 ; i < nActions ; i ++)
	{
		Assert(m_CounterActions[i] != NULL);

		m_CounterActions[i]->execute(pCreature1 , pCreature2);
	}

	return true;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// set condition string
// * FORMAT *
//            str = <nConditions><Condition-List>
//    nConditions = "nConditions : N"<EOL>
// Condition-List = (<Condition><WS>)*
//      Condition = <Condition-Type><ParamPair>*
// Condition-Type = "Condition-Type : CONDITION_XXX"<EOL>
//      ParamPair = (<ParamName><ST><Sep><ST><ParamValue><EOL>)*
//             WS = (' ' | '\n' | '\t')*
//             ST = (' ' | '\t')*
//            EOL = '\n'
//            Sep = ':'
////////////////////////////////////////////////////////////////////////////////
void Trigger::setConditions (const string & str)
	throw (Error)
{
	__BEGIN_TRY

	PropertyBuffer propertyBuffer(str);

	try
	{
		bool bRead = true;

		while (true)
		{
			string ConditionTypeString;

			bRead = propertyBuffer.getProperty("ConditionType", ConditionTypeString);

			if (!bRead) break;

			// read ConditionType
			ConditionType_t conditionType = g_pConditionFactoryManager->getConditionType(ConditionTypeString);

			// create condition object
			Condition * pCondition = g_pConditionFactoryManager->createCondition(conditionType);
	
			// read condition parameters
			pCondition->read(propertyBuffer);

			addCondition(pCondition);
		}
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

	/*
	try
	{
		// read nConditions
		uint nConditions = propertyBuffer.getPropertyInt("nConditions");

		m_Conditions.reserve(nConditions);
	
		// read condition body
		for (uint i = 0 ; i < nConditions ; i ++)
		{
			// read ConditionType
			ConditionType_t conditionType = g_pConditionFactoryManager->getConditionType(propertyBuffer.getProperty("ConditionType"));

			// create condition object
			Condition * pCondition = g_pConditionFactoryManager->createCondition(conditionType);
	
			// read condition parameters
			pCondition->read(propertyBuffer);

			addCondition(pCondition);
		}
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	*/
		
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// set action string
//
// * FORMAT *
//         str = <nActions><Action-List>
//    nActions = "nActions : N"<EOL>
// Action-List = (<Action><WS>)*
//      Action = <Action-Type><ParamPair>*
// Action-Type = "Action-Type : ACTION_XXX"<EOL>
//   ParamPair = (<ParamName><ST><Sep><ST><ParamValue><EOL>)*
//          WS = (' ' | '\n' | '\t')*
//          ST = (' ' | '\t')*
//         EOL = '\n'
//         Sep = ':'
////////////////////////////////////////////////////////////////////////////////
void Trigger::setActions (const string & str)
	throw (Error)
{
	__BEGIN_TRY

	if (str.size() == 0) return;

	PropertyBuffer propertyBuffer(str);

	try
	{
		bool bRead = true;

		while (true)
		{
			string ActionTypeString;

			bRead = propertyBuffer.getProperty("ActionType", ActionTypeString);

			if (!bRead) break;

			// read Action-Type
			ActionType_t actionType = g_pActionFactoryManager->getActionType(ActionTypeString);
	
			// create action object
			Action * pAction = g_pActionFactoryManager->createAction(actionType);
	
			// read action parameters
			pAction->read(propertyBuffer);

			addAction(pAction);
		}

	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}

	/*
	try
	{
		// read nActions
		uint nActions = propertyBuffer.getPropertyInt("nActions");
	
		m_Actions.reserve(nActions);

		// read action body
		for (uint i = 0 ; i < nActions ; i ++)
		{
			// read Action-Type
			ActionType_t actionType = g_pActionFactoryManager->getActionType(propertyBuffer.getProperty("ActionType"));
	
			// create action object
			Action * pAction = g_pActionFactoryManager->createAction(actionType);
	
			// read action parameters
			pAction->read(propertyBuffer);

			addAction(pAction);
		}

	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}
	*/
	
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// set counter action string
//
// * FORMAT *
//         str = <nActions><Action-List>
//    nActions = "nActions : N"<EOL>
// Action-List = (<Action><WS>)*
//      Action = <Action-Type><ParamPair>*
// Action-Type = "Action-Type : ACTION_XXX"<EOL>
//   ParamPair = (<ParamName><ST><Sep><ST><ParamValue><EOL>)*
//          WS = (' ' | '\n' | '\t')*
//          ST = (' ' | '\t')*
//         EOL = '\n'
//         Sep = ':'
////////////////////////////////////////////////////////////////////////////////
void Trigger::setCounterActions (const string & str)
	throw (Error)
{
	__BEGIN_TRY

	if (str.size() == 0) return;

	PropertyBuffer propertyBuffer(str);

	try
	{
		bool bRead = true;

		while (true)
		{
			string ActionTypeString;

			bRead = propertyBuffer.getProperty("ActionType", ActionTypeString);

			if (!bRead) break;

			// read Action-Type
			ActionType_t actionType = g_pActionFactoryManager->getActionType(ActionTypeString);
	
			// create action object
			Action * pAction = g_pActionFactoryManager->createAction(actionType);
	
			// read action parameters
			pAction->read(propertyBuffer);

			addCounterAction(pAction);
		}

	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}

	/*
	try
	{
		// read nActions
		uint nActions = propertyBuffer.getPropertyInt("nActions");
	
		m_Actions.reserve(nActions);

		// read action body
		for (uint i = 0 ; i < nActions ; i ++)
		{
			// read Action-Type
			ActionType_t actionType = g_pActionFactoryManager->getActionType(propertyBuffer.getProperty("ActionType"));
	
			// create action object
			Action * pAction = g_pActionFactoryManager->createAction(actionType);
	
			// read action parameters
			pAction->read(propertyBuffer);

			addCounterAction(pAction);
		}

	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}
	*/
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string Trigger::toString () const
	throw ()
{

	__BEGIN_TRY

	StringStream msg;

	msg << "Trigger("
			<< "TriggerType:" << TriggerType2String[m_TriggerType]
			<< ",TriggerID:"  << (int)m_TriggerID
			<< ",QuestID:"    << (int)m_QuestID	
			<< ",Comment:"    << m_Comment;

	
	msg	<< " Actions(";
	for (uint i = 0 ; i < m_Conditions.size() ; i ++)
	{
		msg << m_Conditions[i]->toString();
	}
	msg << ")";

	msg << " Actions(";
	for (vector<Action*>::const_iterator itr = m_Actions.begin() ; itr != m_Actions.end() ; itr ++)
	{
		msg << (*itr)->toString();
	}
	msg << ")";

	msg << ")";

	return msg.toString();

	__END_CATCH
}
