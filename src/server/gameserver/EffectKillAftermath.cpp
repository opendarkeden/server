//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKillAftermath.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectKillAftermath.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "GamePlayer.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectKillAftermath::EffectKillAftermath(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectKillAftermath::~EffectKillAftermath()
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::unaffect(Creature* pFromCreature)
	throw(Error)
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	//cout << "EffectKillAftermath" << "unaffect BEGIN" << endl;

	Assert(pFromCreature != NULL);
	pFromCreature->removeFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	destroy(pFromCreature->getName());

	//cout << "EffectKillAftermath" << "unaffect END" << endl;

	__END_DEBUG 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectKillAftermath" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectKillAftermath" << "unaffect END" << endl;
						
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::create(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();


		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("INSERT INTO EffectKillAftermath (OwnerID , YearTime, DayTime) VALUES('%s', %ld, %ld)",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec);	

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "DELETE FROM EffectKillAftermath WHERE OwnerID = '" << ownerID << "'";
		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("DELETE FROM EffectKillAftermath WHERE OwnerID = '%s'", 
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermath::save(const string & ownerID) 
	throw(Error)
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

		sql << "UPDATE EffectKillAftermath SET "
			<< "YearTime = " << currentYearTime
			<< ",DayTime = " << m_Deadline.tv_sec
			<< " WHERE OwnerID = '" << ownerID << "'";
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery( "UPDATE EffectKillAftermath SET YearTime = %ld, DayTime = %ld WHERE OwnerID = '%s'",
		 						currentYearTime, m_Deadline.tv_sec, ownerID.c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectKillAftermath::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectKillAftermath("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectKillAftermathLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	if (pCreature == NULL)
	{
		//cout << "EffectKillAftermathLoader : 크리쳐가 널입니다." << endl;
		return;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT DayTime FROM EffectKillAftermath"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		Result* pResult = pStmt->executeQuery( "SELECT DayTime FROM EffectKillAftermath WHERE OwnerID = '%s'", 
												pCreature->getName().c_str() );

		while(pResult->next())
		{
			if (pCreature->isSlayer()) 
			{
				uint i = 0;

				int DayTime = pResult->getDWORD(++i);

				Timeval currentTime;
				getCurrentTime(currentTime);

				EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pCreature);
		
				if (currentTime.tv_sec < DayTime) 
				{
					pEffectKillAftermath->setDeadline((DayTime - currentTime.tv_sec)* 10);
	
					Slayer* pSlayer = dynamic_cast<Slayer *>(pCreature);
					pSlayer->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	
					EffectManager* pEffectManager = pSlayer->getEffectManager();
					pEffectManager->addEffect(pEffectKillAftermath);
				} 
				else 
				{
					pEffectKillAftermath->setDeadline(0);
	
					Slayer* pSlayer = dynamic_cast<Slayer *>(pCreature);
					pSlayer->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	
					EffectManager* pEffectManager = pSlayer->getEffectManager();
					pEffectManager->addEffect(pEffectKillAftermath);
				}
			}
			else if (pCreature->isVampire()) 
			{
				uint i = 0;

				int DayTime = pResult->getDWORD(++i);

				Timeval currentTime;
				getCurrentTime(currentTime);

				EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pCreature);
		
				if (currentTime.tv_sec < DayTime) 
				{
					pEffectKillAftermath->setDeadline((DayTime - currentTime.tv_sec)* 10);
	
					Vampire* pVampire = dynamic_cast<Vampire *>(pCreature);
					pVampire->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	
					EffectManager* pEffectManager = pVampire->getEffectManager();
					pEffectManager->addEffect(pEffectKillAftermath);
				} 
				else 
				{
					pEffectKillAftermath->setDeadline(0);
	
					Vampire* pVampire = dynamic_cast<Vampire *>(pCreature);
					pVampire->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	
					EffectManager* pEffectManager = pVampire->getEffectManager();
					pEffectManager->addEffect(pEffectKillAftermath);
				}
			}
			else if (pCreature->isOusters()) 
			{
				uint i = 0;

				int DayTime = pResult->getDWORD(++i);

				Timeval currentTime;
				getCurrentTime(currentTime);

				EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pCreature);
		
				if (currentTime.tv_sec < DayTime) 
				{
					pEffectKillAftermath->setDeadline((DayTime - currentTime.tv_sec)* 10);
	
					Ousters* pOusters = dynamic_cast<Ousters *>(pCreature);
					pOusters->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	
					EffectManager* pEffectManager = pOusters->getEffectManager();
					pEffectManager->addEffect(pEffectKillAftermath);
				} 
				else 
				{
					pEffectKillAftermath->setDeadline(0);
	
					Ousters* pOusters = dynamic_cast<Ousters *>(pCreature);
					pOusters->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
	
					EffectManager* pEffectManager = pOusters->getEffectManager();
					pEffectManager->addEffect(pEffectKillAftermath);
				}
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectKillAftermathLoader* g_pEffectKillAftermathLoader = NULL;
