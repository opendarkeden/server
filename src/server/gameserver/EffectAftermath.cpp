//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAftermath.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectAftermath.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "GamePlayer.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectAftermath::EffectAftermath(Creature* pCreature)
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
EffectAftermath::~EffectAftermath()
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::unaffect(Creature* pFromCreature)
	throw(Error)
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	//cout << "EffectAftermath" << "unaffect BEGIN" << endl;

	Assert(pFromCreature != NULL);
	pFromCreature->removeFlag(Effect::EFFECT_CLASS_AFTERMATH);
	destroy(pFromCreature->getName());

	//cout << "EffectAftermath" << "unaffect END" << endl;

	__END_DEBUG 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectAftermath" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectAftermath" << "unaffect END" << endl;
						
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::create(const string & ownerID) 
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
		sql << "INSERT INTO EffectAftermath "
			<< "(OwnerID , YearTime, DayTime) VALUES("
			<< "'" << ownerID           << "', "
			<< " " << currentYearTime   << " , "
			<< " " << m_Deadline.tv_sec << "   "
			<< ")";

		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("INSERT INTO EffectAftermath (OwnerID , YearTime, DayTime) VALUES('%s', %ld, %ld)",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec);	

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "DELETE FROM EffectAftermath WHERE OwnerID = '" << ownerID << "'";
		pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery("DELETE FROM EffectAftermath WHERE OwnerID = '%s'", 
								ownerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermath::save(const string & ownerID) 
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

		sql << "UPDATE EffectAftermath SET "
			<< "YearTime = " << currentYearTime
			<< ",DayTime = " << m_Deadline.tv_sec
			<< " WHERE OwnerID = '" << ownerID << "'";
		*/

		// StringStream제거. by sigi. 2002.5.8
		pStmt->executeQuery( "UPDATE EffectAftermath SET YearTime = %ld, DayTime = %ld WHERE OwnerID = '%s'",
		 						currentYearTime, m_Deadline.tv_sec, ownerID.c_str() );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectAftermath::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectAftermath("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectAftermathLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	if (pCreature == NULL ||
		( !pCreature->isSlayer() && !pCreature->isOusters() )
	)
	{
		//cout << "EffectAftermathLoader : 크리쳐가 널입니다." << endl;
		return;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT DayTime FROM EffectAftermath"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());
		*/

		// StringStream제거. by sigi. 2002.5.8
		Result* pResult = pStmt->executeQuery( "SELECT DayTime FROM EffectAftermath WHERE OwnerID = '%s'", 
												pCreature->getName().c_str() );

		while(pResult->next())
		{
			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectAftermath* pEffectAftermath = new EffectAftermath(pCreature);
	
			if (currentTime.tv_sec < DayTime) 
			{
				pEffectAftermath->setDeadline((DayTime - currentTime.tv_sec)* 10);

				pCreature->setFlag(Effect::EFFECT_CLASS_AFTERMATH);

				EffectManager* pEffectManager = pCreature->getEffectManager();
				pEffectManager->addEffect(pEffectAftermath);
			} 
			else 
			{
				pEffectAftermath->setDeadline(0);

				pCreature->setFlag(Effect::EFFECT_CLASS_AFTERMATH);

				EffectManager* pEffectManager = pCreature->getEffectManager();
				pEffectManager->addEffect(pEffectAftermath);
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectAftermathLoader* g_pEffectAftermathLoader = NULL;
