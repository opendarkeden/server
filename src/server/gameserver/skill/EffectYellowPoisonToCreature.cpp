//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectYellowPoisonToCreature.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectYellowPoisonToCreature.h"
#include "Slayer.h"
#include "Player.h"
#include "DB.h"
#include "DarkLightInfo.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectYellowPoisonToCreature::EffectYellowPoisonToCreature(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	m_Level = 0;
	setTarget(pCreature);
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

//	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	if (pCreature != NULL) 
	{

		Zone*   pZone   = pCreature->getZone();
		Player* pPlayer = pCreature->getPlayer();

		// Light등의 마법으로 인하여 시야가 밝아져 있을 수 있으므로..
		// OldSight가 현재의 Sight보다 어두우면 Setting 하지 않는다.
		Sight_t NewSight = 13;
		pCreature->setSight(NewSight);

		// 클라이언트에 Vision 정보를 전송한다.
		GCModifyInformation _GCModifyInformation; 
		_GCModifyInformation.addShortData(MODIFY_VISION, NewSight);
		pPlayer->sendPacket(&_GCModifyInformation);

		pCreature->removeFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);




		pZone->updateScan(pCreature, YELLOW_POISON_SIGHT, NewSight);

		// Yellow Poison의 효과가 풀릴때 Update Scan은 물론 밝기의 조절까지 해준다.
	//	DarkLightInfo* pDIInfo    = g_pDarkLightInfoManager->getCurrentDarkLightInfo( pZone );
		//DarkLevel_t    darkLevel  = pDIInfo->getDarkLevel();
		//LightLevel_t   lightLevel = pDIInfo->getLightLevel();

		GCChangeDarkLight gcChangeDarkLight;
		gcChangeDarkLight.setDarkLevel(pZone->getDarkLevel());
		gcChangeDarkLight.setLightLevel(pZone->getLightLevel());

		pPlayer->sendPacket(&gcChangeDarkLight);
	
		/*
		if (!pSlayer->isFlag(Effect::EFFECT_CLASS_DARKNESS)) 
		{
			pZone->updateScan(pSlayer, YELLOW_POISON_SIGHT, NewSight);

			// Yellow Poison의 효과가 풀릴때 Update Scan은 물론 밝기의 조절까지 해준다.
			DarkLightInfo* pDIInfo    = g_pDarkLightInfoManager->getCurrentDarkLightInfo();
			DarkLevel_t    darkLevel  = pDIInfo->getDarkLevel();
			LightLevel_t   lightLevel = pDIInfo->getLightLevel();
	
			GCChangeDarkLight gcChangeDarkLight;
			gcChangeDarkLight.setDarkLevel(darkLevel);
			gcChangeDarkLight.setLightLevel(lightLevel);
	
			pPlayer->sendPacket(&gcChangeDarkLight);
		}
		*/

		// 풀릴때 Sight를 저장해준다.
		//pSlayer->tinysave("Sight = 13");

		// 이펙트가 사라졌다고 알려준다.
		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID(pCreature->getObjectID());
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

		//destroy(pSlayer->getName());
	}
	
	__END_DEBUG
	__END_CATCH
}
void EffectYellowPoisonToCreature::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::create(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	Timeval currentTime;

	getCurrentTime(currentTime);

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		Turn_t currentYearTime;
		getCurrentYearTime(currentYearTime);

		sql << "INSERT INTO EffectYellowPoisonToCreature"
			<< "(OwnerID , YearTime, DayTime, Level, OldSight)"
			<< " VALUES('" << ownerID
			<< "' , " << currentYearTime
			<< "," << m_Deadline.tv_sec
			<< "," <<(int)m_Level
			<< "," <<(int)m_OldSight
			<< ")";

		pStmt->executeQuery(sql.toString());

		delete pStmt;
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "DELETE FROM EffectYellowPoisonToCreature WHERE OwnerID = '" << ownerID << "'";

		pStmt->executeQuery(sql.toString());

		delete pStmt;
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreature::save(const string & ownerID) 
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		Turn_t currentYearTime;
		getCurrentYearTime(currentYearTime);

		sql << "UPDATE EffectYellowPoisonToCreature SET "
			<< "YearTime = " << currentYearTime
			<< ", DayTime = " << m_Deadline.tv_sec
			<< ", Level = " <<(int)m_Level
			<< ", OldSight = " <<(int)m_OldSight
			<< " WHERE OwnerID = '" << ownerID 
			<< "'";

		pStmt->executeQuery(sql.toString());

		delete pStmt;
	}
	END_DB(pStmt)
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectYellowPoisonToCreature::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectYellowPoisonToCreature("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectYellowPoisonToCreatureLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	//Assert(pCreature != NULL);
	if (pCreature == NULL)
	{
		//cout << "EffectYellowPoisonToCreatureLoader : 크리쳐가 널입니다." << endl;
		return;
	}
		

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT YearTime, DayTime, Level, OldSight FROM EffectYellowPoisonToCreature"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());

		while(pResult->next())
		{
			if (pCreature->isSlayer()||pCreature->isOusters()) 
			{
				uint i = 0;

				Turn_t YearTime = pResult->getDWORD(++i);
				int DayTime = pResult->getDWORD(++i);

				Turn_t currentYearTime;

				Timeval currentTime;

				getCurrentYearTime(currentYearTime);

				getCurrentTime(currentTime);
				
                int leftTime =((YearTime-currentYearTime)*24*60*60 +(DayTime-currentTime.tv_sec))*10;
                EffectYellowPoisonToCreature* pEffect = new EffectYellowPoisonToCreature(pCreature);

                if (leftTime > 0)
                {
                    pEffect->setDeadline(leftTime);
                }
                else
                {
					pEffect->setDeadline(10);
					//pEffect->destroy(pCreature->getName());
					//delete pEffect;
                }

				pEffect->setLevel(pResult->getInt(++i));

				pEffect->setOldSight(13);
                pCreature->setFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
                pCreature->addEffect(pEffect);
			}
		}

		delete pStmt;
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectYellowPoisonToCreatureLoader* g_pEffectYellowPoisonToCreatureLoader = NULL;
