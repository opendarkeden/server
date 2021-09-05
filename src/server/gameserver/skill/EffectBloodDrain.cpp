//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodDrain.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectBloodDrain.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "EventMorph.h"
#include "PCManager.h"
#include "GamePlayer.h"
#include "GCMorph1.h"
#include "GCMorphVampire2.h"
#include "GCModifyInformation.h"
#include "GCChangeDarkLight.h"
#include "PCFinder.h"
#include "EventRegeneration.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBloodDrain::EffectBloodDrain(Creature* pCreature)
	
{
	__BEGIN_TRY 

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::affect(Creature* pCreature)
	
{
	__BEGIN_TRY 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::unaffect(Creature* pFromCreature)
	
{
	__BEGIN_TRY 

	//cout << "EffectBloodDrain" << "unaffect BEGIN" << endl;
	Assert(pFromCreature != NULL);

	if ( pFromCreature->isSlayer() )
	{

		Player* pPlayer = pFromCreature->getPlayer();

		Assert(pPlayer != NULL);

		// GamePlayer�� Event�� �ٿ��� heartbeat�� �� �������� �����ش�.
		// ����ȭ ������ ������? -_-; ���̾�׷� ������ ������ ���㸸 -_-;
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		pGamePlayer->deleteEvent(Event::EVENT_CLASS_REGENERATION);

		EventMorph* pEventMorph = new EventMorph(pGamePlayer);

		pEventMorph->setCreature(pFromCreature);
		pEventMorph->setDeadline(0);

		pGamePlayer->addEvent(pEventMorph);

		EventRegeneration* pEventRegeneration = new EventRegeneration(pGamePlayer);

		pEventRegeneration->setDeadline(10* 10);
		pGamePlayer->addEvent(pEventRegeneration);

		destroy(pFromCreature->getName());
	}
	else
	{
		// �þ� ����.
		Assert(pFromCreature->isOusters());

		Player* pPlayer = pFromCreature->getPlayer();
		Assert(pPlayer != NULL);

		pFromCreature->removeFlag( Effect::EFFECT_CLASS_BLOOD_DRAIN );

		Sight_t oldSight = pFromCreature->getSight();
		Sight_t newSight = pFromCreature->getEffectedSight();

		if ( oldSight != newSight )
		{
			GCModifyInformation gcMI;
			pFromCreature->setSight(newSight);
			pFromCreature->getZone()->updateScan(pFromCreature, oldSight, pFromCreature->getSight());
			gcMI.addShortData(MODIFY_VISION, pFromCreature->getSight());
			pFromCreature->getPlayer()->sendPacket(&gcMI);

			GCChangeDarkLight gcChangeDarkLight;
			gcChangeDarkLight.setDarkLevel(13);
			gcChangeDarkLight.setLightLevel(min(6,(int)newSight));
			pFromCreature->getPlayer()->sendPacket(&gcChangeDarkLight);
		}

		// DB���� �����Ӵ�.
		destroy( pFromCreature->getName() );
	}

	//cout << "EffectBloodDrain" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectBloodDrain" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectBloodDrain" << "unaffect END" << endl;
						
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::create(const string & ownerID) 
	
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

		sql << "INSERT INTO EffectBloodDrain "
			<< "(OwnerID , YearTime, DayTime, Level)"
			<< " VALUES('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< " , " <<(int)m_Level
			<< ")";

		pStmt->executeQueryString(sql.toString());
		*/

		pStmt->executeQuery( "INSERT INTO EffectBloodDrain (OwnerID , YearTime, DayTime, Level) VALUES('%s', %ld, %ld, %d)",
								ownerID.c_str(), currentYearTime, m_Deadline.tv_sec, (int)m_Level );


		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::destroy(const string & ownerID)
	
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;
		sql << "DELETE FROM EffectBloodDrain WHERE OwnerID = '" << ownerID << "'";
		pStmt->executeQueryString(sql.toString());
		*/

		pStmt->executeQuery("DELETE FROM EffectBloodDrain WHERE OwnerID = '%s'", 
								ownerID.c_str());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrain::save(const string & ownerID) 
	
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

		sql << "UPDATE EffectBloodDrain SET "
			<< "YearTime = " << currentYearTime
			<< ",DayTime = " << m_Deadline.tv_sec
			<< ", Level = " <<(int)m_Level
			<< " WHERE OwnerID = '" << ownerID << "'";

		pStmt->executeQueryString(sql.toString());
		*/

		pStmt->executeQuery( "UPDATE EffectBloodDrain SET YearTime=%ld, DayTime=%ld, Level=%d WHERE OwnerID='%s'", 
								currentYearTime, m_Deadline.tv_sec, m_Level, ownerID.c_str() );
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBloodDrain::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectBloodDrain("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodDrainLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	if ( !pCreature->isSlayer() && !pCreature->isOusters() ) return;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		/*
		StringStream sql;

		sql << "SELECT DayTime, Level FROM EffectBloodDrain"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQueryString(sql.toString());
		*/

		Result* pResult = pStmt->executeQuery( "SELECT DayTime, Level FROM EffectBloodDrain WHERE OwnerID='%s'", 
												pCreature->getName().c_str());

		while(pResult->next())
		{
			uint i = 0;

			int DayTime = pResult->getDWORD(++i);

			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pCreature);
	
			if (currentTime.tv_sec + 600 < DayTime) 
			{
				pEffectBloodDrain->setDeadline((DayTime - currentTime.tv_sec)* 10);
				pEffectBloodDrain->setLevel(pResult->getBYTE(++i));

				pCreature->addEffect(pEffectBloodDrain);
				pCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			} 
			else 
			{
				//pEffectBloodDrain->setDeadline(6000);
				pEffectBloodDrain->setDeadline(6000);
				pEffectBloodDrain->setLevel(pResult->getBYTE(++i));

				pCreature->addEffect(pEffectBloodDrain);
				pCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectBloodDrainLoader* g_pEffectBloodDrainLoader = NULL;
