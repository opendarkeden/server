//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCanEnterGDRLair.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectCanEnterGDRLair.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "GCModifyInformation.h"
#include "GCRemoveEffect.h"
#include "DB.h"

EffectCanEnterGDRLair::EffectCanEnterGDRLair(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

EffectCanEnterGDRLair::~EffectCanEnterGDRLair()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectCanEnterGDRLair::affect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectCanEnterGDRLair::unaffect()
	    throw(Error)
{
    __BEGIN_TRY

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
    unaffect(pCreature);

    __END_CATCH
}

void EffectCanEnterGDRLair::unaffect (Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	pCreature->removeFlag(getEffectClass());

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());

	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	destroy(pCreature->getName());

	__END_CATCH
}

void EffectCanEnterGDRLair::create (const string & ownerID) 
	throw(Error)
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
		sql << "INSERT INTO CanEnterGDRLair "
			<< "(OwnerID , YearTime, DayTime, EnemyName)"
			<< " VALUES ('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< " , '" << m_EnemyName
			<< "')";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("INSERT INTO CanEnterGDRLair (OwnerID , YearTime, DayTime) VALUES ('%s', %ld, %ld)",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectCanEnterGDRLair::destroy (const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("DELETE FROM CanEnterGDRLair WHERE OwnerID = '%s'",
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectCanEnterGDRLair::save (const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		pStmt->executeQuery("UPDATE CanEnterGDRLair SET YearTime = %ld, DayTime = %ld WHERE OwnerID = '%s'",
								currentYearTime, m_Deadline.tv_sec, ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EffectCanEnterGDRLair::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCanEnterGDRLair("
		<< ")";
	return msg.toString();

	__END_CATCH
}

void EffectCanEnterGDRLairLoader::load (Creature* pCreature) 
	throw(Error)
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

		sql << "SELECT DayTime, EnemyName FROM CanEnterGDRLair"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		Result* pResult = pStmt->executeQuery("SELECT DayTime FROM CanEnterGDRLair WHERE OwnerID = '%s'",
												pCreature->getName().c_str());

		while (pResult->next())
		{

			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectCanEnterGDRLair* pEffectCanEnterGDRLair = new EffectCanEnterGDRLair(pCreature);

			EffectManager* pEffectManager = pCreature->getEffectManager();

			if (currentTime.tv_sec < DayTime) {
				pEffectCanEnterGDRLair->setDeadline((DayTime - currentTime.tv_sec)* 10);
			} else {
				pEffectCanEnterGDRLair->setDeadline(100);
			}

			pEffectManager->addEffect(pEffectCanEnterGDRLair);
			pCreature->setFlag(pEffectCanEnterGDRLair->getEffectClass());
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectCanEnterGDRLairLoader* g_pEffectCanEnterGDRLairLoader = NULL;
