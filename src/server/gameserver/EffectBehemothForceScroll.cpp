//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBehemothForceScroll.cpp
// Written by  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectBehemothForceScroll.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "GCRemoveEffect.h"
#include "Timeval.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBehemothForceScroll::EffectBehemothForceScroll(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBehemothForceScroll::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBehemothForceScroll::affect(Creature* pCreature)
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
void EffectBehemothForceScroll::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBehemothForceScroll::unaffect(Creature* pCreature)
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
void EffectBehemothForceScroll::create(const string& ownerID )
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

		pStmt->executeQuery("INSERT INTO EffectBehemothForceScroll (OwnerID, RemainTime ) VALUES('%s',%lu)",
								ownerID.c_str(), remainTurn);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBehemothForceScroll::destroy(const string& ownerID )
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery("DELETE FROM EffectBehemothForceScroll WHERE OwnerID = '%s'",
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBehemothForceScroll::save(const string& ownerID )
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

		pStmt->executeQuery("UPDATE EffectBehemothForceScroll SET RemainTime = %lu WHERE OwnerID = '%s'",
								remainTurn, ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBehemothForceScroll::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectBehemothForceScroll("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBehemothForceScrollLoader::load(Creature* pCreature )
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECt RemainTime FROM EffectBehemothForceScroll WHERE OwnerID = '%s'",
													pCreature->getName().c_str());

		if (pResult->next() )
		{
			Turn_t remainTurn = pResult->getDWORD(1);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectBehemothForceScroll* pEffect = new EffectBehemothForceScroll(pCreature);

			pEffect->setDeadline(remainTurn);
			pCreature->addEffect(pEffect);
			pCreature->setFlag(pEffect->getEffectClass());
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

EffectBehemothForceScrollLoader* g_pEffectBehemothForceScrollLoader = NULL;

