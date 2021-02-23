//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEnemyErase.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectEnemyErase.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveInjuriousCreature.h"
#include "DB.h"

EffectEnemyErase::EffectEnemyErase(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectEnemyErase::~EffectEnemyErase()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectEnemyErase::affect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectEnemyErase::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

    __END_CATCH
}

void EffectEnemyErase::unaffect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	if (pCreature->isSlayer())
	{
		Slayer*       pTargetSlayer = dynamic_cast<Slayer*>(pCreature);
		pTargetSlayer->deleteEnemy(m_EnemyName);

		GCRemoveInjuriousCreature gcRemoveInjuriousCreature;
		gcRemoveInjuriousCreature.setName( m_EnemyName );

		pTargetSlayer->getPlayer()->sendPacket(&gcRemoveInjuriousCreature);

	}
	else if (pCreature->isVampire())
	{
		Vampire*       pTargetVampire = dynamic_cast<Vampire*>(pCreature);
		pTargetVampire->deleteEnemy(m_EnemyName);

		GCRemoveInjuriousCreature gcRemoveInjuriousCreature;
		gcRemoveInjuriousCreature.setName( m_EnemyName );

		pTargetVampire->getPlayer()->sendPacket(&gcRemoveInjuriousCreature);

	}
	else if (pCreature->isOusters())
	{
		Ousters*       pTargetOusters = dynamic_cast<Ousters*>(pCreature);
		pTargetOusters->deleteEnemy(m_EnemyName);

		GCRemoveInjuriousCreature gcRemoveInjuriousCreature;
		gcRemoveInjuriousCreature.setName( m_EnemyName );

		pTargetOusters->getPlayer()->sendPacket(&gcRemoveInjuriousCreature);

	}
	else
	{
	}
	destroy( pCreature->getName() );

	__END_DEBUG
	__END_CATCH
}

void EffectEnemyErase::create (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();


		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		/*
		StringStream sql;
		sql << "INSERT INTO EnemyErase "
			<< "(OwnerID , YearTime, DayTime, EnemyName)"
			<< " VALUES ('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< " , '" << m_EnemyName
			<< "')";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("INSERT INTO EnemyErase (OwnerID , YearTime, DayTime, EnemyName) VALUES ('%s', %ld, %ld, '%s')",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec, m_EnemyName.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectEnemyErase::destroy (const string & ownerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "DELETE FROM EnemyErase WHERE OwnerID = '" << ownerID << "' AND EnemyName = '" << m_EnemyName << "'";
		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("DELETE FROM EnemyErase WHERE OwnerID = '%s' AND EnemyName = '%s'", 
								ownerID.c_str(), m_EnemyName.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectEnemyErase::save (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();


		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		/*
		StringStream sql;
		sql << "UPDATE EnemyErase SET "
			<< "YearTime = " << currentYearTime
			<< ",DayTime = " << m_Deadline.tv_sec
			<< ", EnemyName = '" << m_EnemyName
			<< "' WHERE OwnerID = '" << ownerID << "'";

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery("UPDATE EnemyErase SET YearTime = %ld, DayTime = %ld, EnemyName = '%s' WHERE OwnerID = '%s'",
								currentYearTime, m_Deadline.tv_sec, m_EnemyName.c_str(), ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EffectEnemyErase::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectEnemyErase("
		<< "EnemyName:" << getEnemyName()
		<< ")";
	return msg.toString();

	__END_CATCH
}

void EffectEnemyEraseLoader::load (Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	//Assert(pCreature != NULL);
	if (pCreature == NULL)
	{
		return;
	}

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT DayTime, EnemyName FROM EnemyErase"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		Result* pResult = pStmt->executeQuery( "SELECT DayTime, EnemyName FROM EnemyErase WHERE OwnerID = '%s'",
												pCreature->getName().c_str() );

		while (pResult->next())
		{

			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectEnemyErase* pEffectEnemyErase = new EffectEnemyErase(pCreature);

			EffectManager* pEffectManager = pCreature->getEffectManager();

			if (currentTime.tv_sec < DayTime) {
				pEffectEnemyErase->setDeadline((DayTime - currentTime.tv_sec)* 10);
				pEffectEnemyErase->setEnemyName(pResult->getString(++i));
			} else {
				pEffectEnemyErase->setDeadline(100);
				pEffectEnemyErase->setEnemyName(pResult->getString(++i));
			}

			pEffectManager->addEffect(pEffectEnemyErase);

			if (pCreature->isSlayer()) {
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->addEnemy(pEffectEnemyErase->getEnemyName());
			} else if (pCreature->isVampire()) {
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->addEnemy(pEffectEnemyErase->getEnemyName());
			} else if (pCreature->isOusters()) {
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->addEnemy(pEffectEnemyErase->getEnemyName());
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectEnemyEraseLoader* g_pEffectEnemyEraseLoader = NULL;

