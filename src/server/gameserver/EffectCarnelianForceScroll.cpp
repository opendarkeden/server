//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCarnelianForceScroll.cpp
// Written by  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectCarnelianForceScroll.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "GCRemoveEffect.h"
#include "Timeval.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectCarnelianForceScroll::EffectCarnelianForceScroll(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScroll::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScroll::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	ObjectRegistry& objectregister = pZone->getObjectRegistry();
	objectregister.registerObject(this);

	// 葛历 9可记 利侩
	pPC->addEffectOption(getObjectID(), 182);
	pPC->initAllStatAndSend();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScroll::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScroll::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	pPC->removeFlag(getEffectClass());
	pPC->removeEffectOption(getObjectID());
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
void EffectCarnelianForceScroll::create(const string& ownerID )
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

		pStmt->executeQuery("INSERT INTO EffectCarnelianForceScroll (OwnerID, RemainTime ) VALUES('%s',%lu)",
								ownerID.c_str(), remainTurn);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScroll::destroy(const string& ownerID )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("DELETE FROM EffectCarnelianForceScroll WHERE OwnerID = '%s'",
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScroll::save(const string& ownerID )
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

		pStmt->executeQuery("UPDATE EffectCarnelianForceScroll SET RemainTime = %lu WHERE OwnerID = '%s'",
								remainTurn, ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectCarnelianForceScroll::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCarnelianForceScroll("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCarnelianForceScrollLoader::load(Creature* pCreature )
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECt RemainTime FROM EffectCarnelianForceScroll WHERE OwnerID = '%s'",
													pCreature->getName().c_str());

		if (pResult->next() )
		{
			Turn_t remainTurn = pResult->getDWORD(1);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectCarnelianForceScroll* pEffect = new EffectCarnelianForceScroll(pCreature);

			pEffect->setDeadline(remainTurn);
			pCreature->addEffect(pEffect);
			pCreature->setFlag(pEffect->getEffectClass());

			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert(pPC != NULL);

			Zone* pZone = pPC->getZone();
			Assert(pZone != NULL);

			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			// 葛历 9可记 利侩
			pPC->addEffectOption(pEffect->getObjectID(), 182);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

EffectCarnelianForceScrollLoader* g_pEffectCarnelianForceScrollLoader = NULL;

