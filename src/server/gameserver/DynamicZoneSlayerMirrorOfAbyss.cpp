/////////////////////////////////////////////////////////////////////////////
// DynamicZoneSlayerMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneSlayerMirrorOfAbyss.h"
#include "DynamicZoneInfo.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "PCManager.h"
#include "MonsterManager.h"
#include "EffectKillTimer.h"
#include "GQuestManager.h"
#include "Assert1.h"

#include "GCSystemMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <map>

enum SLAYER_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	SLAYER_MIRROR_OF_ABYSS_END,

	SLAYER_MIRROR_OF_ABYSS_MAX
};

DynamicZoneSlayerMirrorOfAbyss::DynamicZoneSlayerMirrorOfAbyss()
{
	m_MonoObjectID = 0;
}

DynamicZoneSlayerMirrorOfAbyss::~DynamicZoneSlayerMirrorOfAbyss()
{
}

void DynamicZoneSlayerMirrorOfAbyss::init()
{
	Assert(m_pZone != NULL);

	m_SMOAStatus = WAIT_FOR_PC;
	getCurrentTime(m_Deadline);
	m_Deadline.tv_sec += 60;
	getCurrentTime(m_EndTime);
	m_EndTime.tv_sec += 10 * 60;
}

void DynamicZoneSlayerMirrorOfAbyss::heartbeat()
{
	switch (m_SMOAStatus )
	{
	case WAIT_FOR_PC:
		if (checkPC() )
		{
			processEntering();
			m_SMOAStatus = ADD_MONO;
		}
		break;

	case ADD_MONO:
		if (addMono() )
			m_SMOAStatus = WAIT_FOR_COMPLETE;
		break;

	case WAIT_FOR_COMPLETE:
		if (checkComplete() )
		{
			openGateToOut();
			m_SMOAStatus = CLEAR_MONO;
		}

		if (!checkMono() )
		{
			killPC();
		}

		break;

	case CLEAR_MONO:
		if (clearMono() )
			m_SMOAStatus = WAIT_FOR_CLEAR;
		break;

	case WAIT_FOR_CLEAR:
		if (!checkPC() && !checkMono() )
		{
			m_SMOAStatus = SLAYER_MIRROR_OF_ABYSS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
		}
		break;
	}

	if (!checkPC() )
	{
		if (m_SMOAStatus == WAIT_FOR_PC )
		{
			Timeval current;
			getCurrentTime(current);

			if (current > m_Deadline )
				m_SMOAStatus = CLEAR_MONO;
		}
		else if (m_SMOAStatus == WAIT_FOR_COMPLETE )
			m_SMOAStatus = CLEAR_MONO;
	}
}

bool DynamicZoneSlayerMirrorOfAbyss::checkPC()
{
	Assert(m_pZone != NULL);

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneSlayerMirrorOfAbyss::addMono()
{
	Assert(m_pZone != NULL);

	// 이성의 봉인을 생성한다.
	Monster* pMonster = new Monster(792);
	Assert(pMonster != NULL);

	pMonster->setName("이성의 봉인");
	pMonster->setClanType(33);

	try
	{
		m_pZone->addCreature(pMonster, 15, 15, 2);
		m_pZone->getMonsterManager()->addEnemy(NULL, pMonster);

		m_MonoObjectID = pMonster->getObjectID();
	}
	catch (EmptyTileNotExistException& )
	{
		SAFE_DELETE(pMonster);
	}

	return true;
}

bool DynamicZoneSlayerMirrorOfAbyss::clearMono()
{
	Assert(m_pZone != NULL);

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert(pMonsterManager != NULL);

	Creature* pCreature = pMonsterManager->getCreature(m_MonoObjectID);
	if (pCreature != NULL )
	{
		if (pCreature->isMonster() )
		{
			EffectKillTimer* pEffect = new EffectKillTimer(pCreature, true);
			pCreature->setFlag(pEffect->getEffectClass());
			pEffect->setDeadline(50);
			pCreature->addEffect(pEffect);
		}
	}

	return true;
}

bool DynamicZoneSlayerMirrorOfAbyss::openGateToOut()
{
	Assert(m_pZone != NULL);

    // 퀘스트를 진행시킨다.
    map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for (; itr != endItr; ++itr )
    {
        Assert(itr->second != NULL);

        if (itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert(pPC != NULL);

            pPC->getGQuestManager()->clearDynamicZone(m_TemplateZoneID);
        }
    }

	return true;
}

bool DynamicZoneSlayerMirrorOfAbyss::checkComplete()
{
	Timeval current;
	getCurrentTime(current);
	if (current > m_EndTime )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DynamicZoneSlayerMirrorOfAbyss::processEntering()
{
	Assert(m_pZone != NULL);

    // 퀘스트 존에 들어왔음을 알린다.
    map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for (; itr != endItr; ++itr )
    {
        Assert(itr->second != NULL);

        if (itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert(pPC != NULL);

            pPC->getGQuestManager()->enterDynamicZone(m_TemplateZoneID);
        }
    }
}

bool DynamicZoneSlayerMirrorOfAbyss::checkMono()
{
	Assert(m_pZone != NULL);

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert(pMonsterManager != NULL);

	Creature* pCreature = pMonsterManager->getCreature(m_MonoObjectID);
	return pCreature != NULL;
}

void DynamicZoneSlayerMirrorOfAbyss::killPC()
{
	Assert(m_pZone != NULL);

    // PC 를 죽인다.
    map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for (; itr != endItr; ++itr )
    {
        Assert(itr->second != NULL);

        if (itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert(pPC != NULL);

			if (pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				Assert(pSlayer != NULL);

				pSlayer->setHP(0);
			}
			else if (pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				Assert(pVampire != NULL);

				pVampire->setHP(0);
			}
			else if (pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				Assert(pOusters != NULL);

				pOusters->setHP(0);
			}
        }
    }
}

DEFINE_DYNAMIC_ZONE_FACTORY(DynamicZoneSlayerMirrorOfAbyss, DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS )

