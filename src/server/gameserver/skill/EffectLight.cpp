//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLight.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectLight.h"
#include "Creature.h"
#include "Slayer.h"
#include "Player.h"
#include "DB.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLight member methods
//////////////////////////////////////////////////////////////////////////////

EffectLight::EffectLight(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectLight::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectLight::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectLight::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectLight " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	if (pSlayer != NULL) 
	{
		Zone* pZone = pSlayer->getZone();

		Sight_t NewSight = 0;

		if (pSlayer->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			NewSight = 3;
		}
		else 
		{
			NewSight = 13;
		}

		pZone->updateScan(pSlayer, pSlayer->getSight(), NewSight);
		pSlayer->setSight(NewSight);
		
		pSlayer->removeFlag(Effect::EFFECT_CLASS_LIGHT);
	
		Player* pPlayer = pSlayer->getPlayer();
	
		GCModifyInformation _GCModifyInformation; 
	
		_GCModifyInformation.addShortData(MODIFY_VISION, NewSight);
	
		pPlayer->sendPacket(&_GCModifyInformation);

		// 이펙트가 사라졌다고 알려준다.
		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pSlayer->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_LIGHT);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);

		destroy(pSlayer->getName());
	}

	//cout << "EffectLight " << "unaffect END" << endl;
	
	__END_CATCH
}

void EffectLight::unaffect()
	
{
	__BEGIN_TRY

	Slayer* pSlayer = dynamic_cast<Slayer*>(m_pTarget);
	unaffect(pSlayer);
	
	__END_CATCH
}

void EffectLight::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectLight::create(const string & ownerID) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	Timeval currentTime;
	getCurrentTime(currentTime);

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		Turn_t currentYearTime;
		getCurrentYearTime(currentYearTime);

		sql << "INSERT INTO EffectLight"
			<< "(OwnerID , YearTime, DayTime, OldSight)"
			<< " VALUES('" << ownerID
			<< "' , " << currentYearTime
			<< " , " << m_Deadline.tv_sec
			<< "," <<(int)m_OldSight
			<< ")";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectLight::destroy(const string & ownerID)
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;
		sql << "DELETE FROM EffectLight WHERE OwnerID = '" << ownerID << "'";
		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

void EffectLight::save(const string & ownerID) 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		Turn_t currentYearTime;
		getCurrentYearTime(currentYearTime);

		sql << "UPDATE EffectLight SET "
			<< "YearTime = " << currentYearTime
			<< ", DayTime = " << m_Deadline.tv_sec
			<< ", OldSight = " <<(int)m_OldSight
			<< " WHERE OwnerID = '" << ownerID 
			<< "'";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

string EffectLight::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectLight("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

void EffectLightLoader::load(Creature* pCreature) 
	
{
	__BEGIN_TRY

	if (pCreature == NULL)
	{
		//cout << "EffectLightLoader : 크리쳐가 널입니다." << endl;
		return;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT YearTime, DayTime, OldSight FROM EffectLight"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());

		while(pResult->next())
		{
			if (pCreature->isSlayer()) 
			{
				uint i = 0;

				Turn_t YearTime = pResult->getDWORD(++i);
				int DayTime = pResult->getDWORD(++i);

				Turn_t currentYearTime;

				Timeval currentTime;

				getCurrentYearTime(currentYearTime);

				getCurrentTime(currentTime);

				int leftTime =((YearTime-currentYearTime)*24*60*60 +(DayTime-currentTime.tv_sec))*10;
				EffectLight* pEffect = new EffectLight(pCreature);
				if (leftTime > 0)
				{
					pEffect->setDeadline(leftTime);
					pCreature->setFlag(Effect::EFFECT_CLASS_LIGHT);
					pCreature->addEffect(pEffect);
				}
				else
				{
					pEffect->destroy(pCreature->getName());
					SAFE_DELETE(pEffect);
				}
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectLightLoader* g_pEffectLightLoader = NULL;
