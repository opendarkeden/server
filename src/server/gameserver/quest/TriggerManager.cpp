////////////////////////////////////////////////////////////////////////////////
// Filename    : TriggerManager.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "TriggerManager.h"
#include "Assert.h"
#include "DB.h"
#include <stdio.h>
#include "TriggerParser.h"
#include "Properties.h"
#include "ScriptManager.h"

class isSameTriggerID {
public :
	isSameTriggerID(TriggerID_t triggerID) throw () : m_TriggerID(triggerID) {}
	bool operator () (Trigger * pTrigger)
	{
		return pTrigger->getTriggerID() == m_TriggerID;
	}
private :
	TriggerID_t m_TriggerID;
};

////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
TriggerManager::TriggerManager () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
TriggerManager::~TriggerManager () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// NPC 이름을 파라미터로 주면, NPC와 관련된 트리거들을 DB에서 로딩한다.
////////////////////////////////////////////////////////////////////////////////
void TriggerManager::load (const string & name)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

//	TriggerParser parser;

	BEGIN_DB
	{
		StringStream sql;

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
		"SELECT TriggerID, TriggerType, Conditions, Actions FROM Triggers WHERE NPC = '%s'", name.c_str());

		while (pResult->next())
		{
			Trigger* pTrigger = new Trigger();

			pTrigger->setTriggerID(pResult->getInt(1));

			//cout << "Trigger[" << pTrigger->getTriggerID() << "] loading > ";
			//cout << "CONDITIONS:\n" << trim(pResult->getString(3)) << endl;
			//cout << "ACTIONS:\n" << trim(pResult->getString(4)) << endl;

			pTrigger->setTriggerType(trim(pResult->getString(2)));
			pTrigger->setConditions(trim(pResult->getString(3)));
			pTrigger->setActions(trim(pResult->getString(4)));

			addTrigger(pTrigger);

//			parser.parseTrigger(trim(pResult->getString(2)), trim(pResult->getString(3)), trim(pResult->getString(4)));

			//cout << "Trigger[" << pTrigger->getTriggerID() << "] loaded" <<  endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

//	XMLTree* pXML = parser.getResult();
//	if ( pXML != NULL )
//	{
//		pXML->SaveToFile((g_pConfig->getProperty("HomePath") + "/data/" + name + ".xml").c_str());
//		SAFE_DELETE( pXML );
//	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 존 좌표를 파라미터로 주면, 그 좌표와 관련된 트리거들을 DB에서 로딩한다.
////////////////////////////////////////////////////////////////////////////////
void TriggerManager::load (ZoneID_t zoneid, int left, int top, int right, int bottom)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(
			"SELECT TriggerID, TriggerType, Conditions, Actions, CounterActions FROM ZoneTriggers WHERE ZoneID=%d AND X1=%d AND Y1=%d AND X2=%d AND Y2=%d", 
			(int)zoneid, left, top, right, bottom);

		while (pResult->next())
		{
			uint     i        = 0;
			Trigger* pTrigger = new Trigger();

			pTrigger->setTriggerID(pResult->getInt(++i));

			//printf("ZoneTrigger[%d] loading > \n", (int)pTrigger->getTriggerID());

			pTrigger->setTriggerType(trim(pResult->getString(++i)));
			pTrigger->setConditions(trim(pResult->getString(++i)));
			pTrigger->setActions(trim(pResult->getString(++i)));
			pTrigger->setCounterActions(trim(pResult->getString(++i)));

			//printf("ZoneTrigger[%d] loaded > \n", (int)pTrigger->getTriggerID());

			addTrigger(pTrigger);
		}

		delete pStmt;
	}
	END_DB(pStmt)

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// refresh condition set
////////////////////////////////////////////////////////////////////////////////
void TriggerManager::refresh ()
	throw (Error)
{
	__BEGIN_TRY

	// 소속된 모든 트리거들의 ConditionSet 을 m_ConditionSet 에 OR 연산한다.
	for (list<Trigger*>::const_iterator itr = m_Triggers.begin() ; itr != m_Triggers.end() ; itr ++)
	{
		m_ConditionSet |= (*itr)->getConditionSet();
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// add trigger
////////////////////////////////////////////////////////////////////////////////
void TriggerManager::addTrigger (Trigger * pTrigger) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	Assert(pTrigger != NULL);

	list<Trigger*>::iterator itr = find(m_Triggers.begin() , m_Triggers.end(), pTrigger);

	if (itr != m_Triggers.end())
		throw DuplicatedException("duplicated trigger");

	m_Triggers.push_back(pTrigger);

	m_ConditionSet |= pTrigger->getConditionSet();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// delete trigger
////////////////////////////////////////////////////////////////////////////////
void TriggerManager::deleteTrigger (TriggerID_t triggerID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	list<Trigger*>::iterator itr = find_if(m_Triggers.begin() , m_Triggers.end() , isSameTriggerID(triggerID));

	if (itr != m_Triggers.end())
		throw NoSuchElementException();

	// delete trigger object
	delete *itr;

	// delete node
	m_Triggers.erase(itr);

	// condition set 을 새로 구성한다.
	refresh();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get trigger
////////////////////////////////////////////////////////////////////////////////
Trigger * TriggerManager::getTrigger (TriggerID_t triggerID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	list<Trigger*>::iterator itr = find_if(m_Triggers.begin() , m_Triggers.end() , isSameTriggerID(triggerID));

	if (itr != m_Triggers.end())
		throw NoSuchElementException();

	return *itr;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string TriggerManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	return msg.toString();

	__END_CATCH
}
