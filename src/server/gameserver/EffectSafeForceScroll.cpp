//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSafeForceScroll.cpp
// Written by  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSafeForceScroll.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "GCRemoveEffect.h"
#include "Timeval.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSafeForceScroll::EffectSafeForceScroll(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	pPC->initAllStatAndSend();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	pPC->removeFlag(getEffectClass());
	pPC->initAllStatAndSend();

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getEffectClass());
	pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcRemoveEffect);

	destroy(pPC->getName());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::create(const string& ownerID )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Timeval currentTime;
		getCurrentTime(currentTime);

		Timeval remainTime = timediff(m_Deadline, currentTime);
		Turn_t remainTurn = remainTime.tv_sec * 10 + remainTime.tv_usec / 100000;

		pStmt->executeQuery("INSERT INTO EffectSafeForceScroll (OwnerID, RemainTime ) VALUES('%s',%lu)",
								ownerID.c_str(), remainTurn);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::destroy(const string& ownerID )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("DELETE FROM EffectSafeForceScroll WHERE OwnerID = '%s'",
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScroll::save(const string& ownerID )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Timeval currentTime;
		getCurrentTime(currentTime);

		Timeval remainTime = timediff(m_Deadline, currentTime);
		Turn_t remainTurn = remainTime.tv_sec * 10 + remainTime.tv_usec / 100000;

		pStmt->executeQuery("UPDATE EffectSafeForceScroll SET RemainTime = %lu WHERE OwnerID = '%s'",
								remainTurn, ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSafeForceScroll::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSafeForceScroll("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSafeForceScrollLoader::load(Creature* pCreature )
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECt RemainTime FROM EffectSafeForceScroll WHERE OwnerID = '%s'",
													pCreature->getName().c_str());

		if (pResult->next() )
		{
			Turn_t remainTurn = pResult->getDWORD(1);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectSafeForceScroll* pEffect = new EffectSafeForceScroll(pCreature);

			pEffect->setDeadline(remainTurn);
			pCreature->addEffect(pEffect);
			pCreature->setFlag(pEffect->getEffectClass());
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

EffectSafeForceScrollLoader* g_pEffectSafeForceScrollLoader = NULL;

