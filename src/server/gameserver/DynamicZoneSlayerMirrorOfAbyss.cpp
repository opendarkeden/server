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
#include "Assert.h"

#include "Gpackets/GCSystemMessage.h"

#include <stdio.h>
#include <stdlib.h>

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
	Assert( m_pZone != NULL );

	m_SMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 10 * 60;
}

void DynamicZoneSlayerMirrorOfAbyss::heartbeat()
{
	switch ( m_SMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			processEntering();
			m_SMOAStatus = ADD_MONO;
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;

	case ADD_MONO:
		if ( addMono() )
		{
			m_SMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( checkComplete() )
		{
			openGateToOut();
			m_SMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		if ( !checkMono() )
		{
			killPC();
		}

		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			m_SMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() && !checkMono() )
		{
			m_SMOAStatus = SLAYER_MIRROR_OF_ABYSS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "-----------------------READY" << endl;
		}
		break;
	}

	if ( !checkPC() )
	{
		if ( m_SMOAStatus == WAIT_FOR_PC )
		{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_Deadline )
			{
				m_SMOAStatus = CLEAR_MONO;
				cout << "-----------------------Time out" << endl;
			}
		}
		else if ( m_SMOAStatus == WAIT_FOR_COMPLETE )
		{
			m_SMOAStatus = CLEAR_MONO;
		}
	}
}

bool DynamicZoneSlayerMirrorOfAbyss::checkPC()
{
	Assert( m_pZone != NULL );

	// PC ¼ö Ã¼Å©
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneSlayerMirrorOfAbyss::addMono()
{
	Assert( m_pZone != NULL );

	// ÀÌ¼ºÀÇ ºÀÀÎÀ» »ý¼ºÇÑ´Ù.
	Monster* pMonster = new Monster( 792 );
	Assert( pMonster != NULL );

	pMonster->setName( "ÀíÐÔÖ®·âÓ¡" );
	pMonster->setClanType(33);

	try
	{
		m_pZone->addCreature( pMonster, 15, 15, 2 );
		m_pZone->getMonsterManager()->addEnemy(NULL, pMonster);

		m_MonoObjectID = pMonster->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster );
	}

	return true;
}

bool DynamicZoneSlayerMirrorOfAbyss::clearMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	if ( pCreature != NULL )
	{
		if ( pCreature->isMonster() )
		{
			EffectKillTimer* pEffect = new EffectKillTimer( pCreature, true );
			pCreature->setFlag( pEffect->getEffectClass() );
			pEffect->setDeadline(50);
			pCreature->addEffect( pEffect );
		}
	}

	return true;
}

bool DynamicZoneSlayerMirrorOfAbyss::openGateToOut()
{
	Assert( m_pZone != NULL );

    // Äù½ºÆ®¸¦ ÁøÇà½ÃÅ²´Ù.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

            pPC->getGQuestManager()->clearDynamicZone(m_TemplateZoneID);
        }
    }

	return true;
}

bool DynamicZoneSlayerMirrorOfAbyss::checkComplete()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_EndTime )
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
	Assert( m_pZone != NULL );

    // Äù½ºÆ® Á¸¿¡ µé¾î¿ÔÀ½À» ¾Ë¸°´Ù.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

            pPC->getGQuestManager()->enterDynamicZone(m_TemplateZoneID);
        }
    }
}

bool DynamicZoneSlayerMirrorOfAbyss::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}

void DynamicZoneSlayerMirrorOfAbyss::killPC()
{
	Assert( m_pZone != NULL );

    // PC ¸¦ Á×ÀÎ´Ù.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				Assert( pSlayer != NULL );

				pSlayer->setHP(0);
			}
			else if ( pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				Assert( pVampire != NULL );

				pVampire->setHP(0);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				Assert( pOusters != NULL );

				pOusters->setHP(0);
			}
        }
    }
}

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneSlayerMirrorOfAbyss, DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS )

