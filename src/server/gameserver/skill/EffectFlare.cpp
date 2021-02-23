//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFlare.cpp
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectFlare.h"
#include "Flare.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "DB.h"
#include "DarkLightInfo.h"
#include "MonsterInfo.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectFlare::EffectFlare(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(!pCreature->isSlayer()); // 슬레이어는 걸리지 않는다.
	Assert(!pCreature->isNPC()); // NPC도 걸리지 않는다.

	Sight_t OldSight = pCreature->getSight();
	pCreature->setSight(pCreature->getEffectedSight());

	Zone* pZone = pCreature->getZone();
	pZone->updateScan(pCreature, OldSight, FLARE_SIGHT);

	if (pCreature->isPC() && pCreature->getSight() == FLARE_SIGHT)
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert(pPlayer != NULL);

		GCChangeDarkLight gcChangeDarkLight;
		gcChangeDarkLight.setDarkLevel(15);
		gcChangeDarkLight.setLightLevel(1);
		pPlayer->sendPacket(&gcChangeDarkLight);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectFlare " << "unaffect BEGIN" << endl;

	if (pCreature == NULL)
	{
		//cout << "EffectFlare " << "unaffect END" << endl;
	}

	pCreature->removeFlag(Effect::EFFECT_CLASS_FLARE);

	Zone* pZone = pCreature->getZone();

	if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		Player* pPlayer = pVampire->getPlayer();

		Sight_t NewSight = getOldSight();
		pVampire->setSight(NewSight);

		GCModifyInformation _GCModifyInformation; 
		_GCModifyInformation.addShortData(MODIFY_VISION, NewSight);
		pPlayer->sendPacket(&_GCModifyInformation);
		pZone->updateScan(pVampire, FLARE_SIGHT, NewSight );

	//	DarkLightInfo* pDIInfo    = g_pDarkLightInfoManager->getCurrentDarkLightInfo( pZone );
		DarkLevel_t    darkLevel  = max(0, DARK_MAX - pZone->getDarkLevel());
		LightLevel_t   lightLevel = min(13, LIGHT_MAX - pZone->getLightLevel());

		GCChangeDarkLight gcChangeDarkLight;
		gcChangeDarkLight.setDarkLevel(darkLevel);
		gcChangeDarkLight.setLightLevel(lightLevel);
		pPlayer->sendPacket(&gcChangeDarkLight);

		destroy(pVampire->getName());
	}
	else if (pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		// 시야를 새로 세팅해준다.
		const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(pMonster->getMonsterType());
		pMonster->setSight(pMonsterInfo->getSight());

		// 시야를 새로 세팅했으니 주위의 적을 검색해야 하는데...
	}

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_FLARE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectFlare " << "unaffect END" << endl;
	
	__END_DEBUG
	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectFlare " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	//cout << "EffectFlare " << "unaffect END" << endl;
	
	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::create(const string & ownerID) 
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

		sql << "INSERT INTO EffectFlare"
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


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::destroy(const string & ownerID)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "DELETE FROM EffectFlare WHERE OwnerID = '" << ownerID << "'";

		pStmt->executeQuery(sql.toString());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlare::save(const string & ownerID) 
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

		sql << "UPDATE EffectFlare SET "
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

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectFlare::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectFlare("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFlareLoader::load(Creature* pCreature) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		StringStream sql;

		sql << "SELECT YearTime, DayTime, OldSight FROM EffectFlare"
			<< " WHERE OwnerID = '" << pCreature->getName() 
			<< "'";

		Result* pResult = pStmt->executeQuery(sql.toString());

		while(pResult->next())
		{
			if (pCreature->isVampire()) 
			{
				uint i = 0;

				Turn_t YearTime = pResult->getDWORD(++i);
				int DayTime = pResult->getDWORD(++i);

				Turn_t currentYearTime;

				Timeval currentTime;

				getCurrentYearTime(currentYearTime);

				getCurrentTime(currentTime);
				
                int leftTime =((YearTime-currentYearTime)*24*60*60 +(DayTime-currentTime.tv_sec))*10;
                EffectFlare* pEffect = new EffectFlare(pCreature);

                if (leftTime > 0)
                {
                    pEffect->setDeadline(leftTime);
                }
                else
                {
					pEffect->setDeadline(10);
 					//pEffect->destroy(pCreature->getName());
					//SAFE_DELETE(pEffect);
                }

				pEffect->setOldSight(13);
                pCreature->setFlag(Effect::EFFECT_CLASS_FLARE);
                pCreature->addEffect(pEffect);
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	
	__END_CATCH
}

EffectFlareLoader* g_pEffectFlareLoader = NULL;
