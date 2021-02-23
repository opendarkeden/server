//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMute.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectMute.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "EventMorph.h"
#include "PCManager.h"
#include "GamePlayer.h"
#include "Gpackets/GCMorph1.h"
#include "Gpackets/GCMorphVampire2.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCRemoveEffect.h"
#include "PCFinder.h"
#include "EventRegeneration.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectMute::EffectMute(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::unaffect(Creature* pFromCreature)
	throw(Error)
{
	__BEGIN_TRY 

	Assert(pFromCreature != NULL);

	pFromCreature->removeFlag(Effect::EFFECT_CLASS_MUTE);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pFromCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_MUTE );
	pFromCreature->getPlayer()->sendPacket( &gcRemoveEffect );

	destroy( pFromCreature->getName() );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectMute" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectMute" << "unaffect END" << endl;
						
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::create(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();


		Turn_t currentYearTime;

		getCurrentYearTime(currentYearTime);

		pStmt->executeQuery( "INSERT INTO EffectMute (OwnerID , YearTime, DayTime) VALUES('%s', %ld, %ld)",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "DELETE FROM EffectMute WHERE OwnerID = '" << ownerID << "'";
		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery("DELETE FROM EffectMute WHERE OwnerID = '%s'", 
								ownerID.c_str());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMute::save(const string & ownerID) 
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

		sql << "UPDATE EffectMute SET "
			<< "YearTime = " << currentYearTime
			<< ",DayTime = " << m_Deadline.tv_sec
			<< ", Level = " <<(int)m_Level
			<< " WHERE OwnerID = '" << ownerID << "'";

		pStmt->executeQuery(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE EffectMute SET YearTime=%ld, DayTime=%ld WHERE OwnerID='%s'", 
								currentYearTime, m_Deadline.tv_sec, ownerID.c_str() );
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMute::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectMute("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMuteLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery( "SELECT DayTime FROM EffectMute WHERE OwnerID='%s'", 
												pCreature->getName().c_str());

		while(pResult->next())
		{
			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectMute* pEffectMute = new EffectMute(pCreature);
	
			if (currentTime.tv_sec < DayTime) 
			{
				pEffectMute->setDeadline((DayTime - currentTime.tv_sec)* 10);

				pCreature->addEffect(pEffectMute);
				pCreature->setFlag(Effect::EFFECT_CLASS_MUTE);
			} 
			else 
			{
				pEffectMute->destroy( pCreature->getName() );
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectMuteLoader* g_pEffectMuteLoader = NULL;
