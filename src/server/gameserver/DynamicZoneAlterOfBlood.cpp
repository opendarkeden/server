/////////////////////////////////////////////////////////////////////////////
// DynamicZoneAlterOfBlood.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneAlterOfBlood.h"
#include "DynamicZoneInfo.h"
#include "Zone.h"
#include "PlayerCreature.h"
#include "GQuestManager.h"
#include "PCManager.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "EffectKillTimer.h"
#include "EffectCauseCriticalWounds.h"
#include "Timeval.h"
#include "Assert.h"
#include "NPCInfo.h"

#include "GCSystemMessage.h"
#include "GCAddEffectToTile.h"

#include <stdio.h>
#include <stdlib.h>

enum ALTER_OF_BLOOD_STATUS
{
	WAIT_FOR_PC,
	ADD_OFFERING,
	WAIT_FOR_CLEAR_OFFERING,
	CLEAR_OFFERING,
	WAIT_FOR_CLEAR,
	ALTER_OF_BLOOD_STATUS_END,

	ALTER_OF_BLOOD_STATUS_MAX
};

struct OFFERING_TEMPLATE
{
	MonsterType_t	MonsterType;
	string			Name[5];
};

const OFFERING_TEMPLATE OfferingTemplate[3] =
{
	{ 793, { "Ô¼º²Ñ·", "±ÈÁ¦", "Àí²éµÂ", "°£Ë¹¿¨Ì¹", "Â·Ò×Ë¹" } },
	{ 794, { "Õ²Ä·Ë¹", "¿­Éª", "ÅÂÒ×", "ÄáÄÇÂ¬Ë¹", "Â¬" } },
	{ 795, { "ÅåË¹ÌØ", "Ð¤", "°¢Â¬Ë¹", "Õ²ç÷", "¸ñÅ¬" } }
};

struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

const OFFERING_COORDINATE OfferingCoordinate[5] =
{
	{ 66, 20 },
	{ 88, 77 },
	{ 29, 100 },
	{ 53, 88 },
	{ 11, 65 }
};

DynamicZoneAlterOfBlood::DynamicZoneAlterOfBlood()
{
	for ( int i=0; i<5; ++i )
	{
		m_OfferingObjectID[i] = 0;
	}
}

DynamicZoneAlterOfBlood::~DynamicZoneAlterOfBlood()
{
}

void DynamicZoneAlterOfBlood::init()
{
	Assert( m_pZone != NULL );

	m_AOBStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
}

void DynamicZoneAlterOfBlood::heartbeat()
{
	switch ( m_AOBStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			processEntering();
			m_AOBStatus = ADD_OFFERING;
			cout << "--------------------------------------------ADD_OFFERING" << endl;
		}
		break;

	case ADD_OFFERING:
		if ( addOffering() )
		{
			m_AOBStatus = WAIT_FOR_CLEAR_OFFERING;
			cout << "--------------------------------------------WAIT_FOR_CLEAR_OFFERING" << endl;
		}
		break;

	case WAIT_FOR_CLEAR_OFFERING:
		if ( checkNoOffering() )
		{
			openGateToOut();
			m_AOBStatus = CLEAR_OFFERING;
			cout << "--------------------------------------------WAIT_FOR_CLEAR" << endl;
		}
		break;

	case CLEAR_OFFERING:
		if ( clearOffering() )
		{
			m_AOBStatus = WAIT_FOR_CLEAR;
			cout << "--------------------------------------------WAIT_FOR_CLEAR" << endl;
		}
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() && checkNoOffering() )
		{
			m_AOBStatus = ALTER_OF_BLOOD_STATUS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "--------------------------------------------READY" << endl;
		}
		break;
	}

	if ( !checkPC() )
	{
		if ( m_AOBStatus == WAIT_FOR_PC )
		{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_Deadline )
			{
				cout << "--------------------------------------------TIME_OUT" << endl;
				m_AOBStatus = CLEAR_OFFERING;
			}
		}
		else if ( m_AOBStatus == WAIT_FOR_CLEAR_OFFERING )
		{
			m_AOBStatus = CLEAR_OFFERING;
			cout << "--------------------------------------------FAIL" << endl;
		}
	}
}

bool DynamicZoneAlterOfBlood::checkPC()
{
	Assert( m_pZone != NULL );

	// PC ¼ö Ã¼Å©
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneAlterOfBlood::addOffering()
{
	Assert( m_pZone != NULL );

	for ( int i = 0; i < 5; ++i )
	{
		// Á¦¹°À» »ý¼ºÇÏ¿© Ãß°¡ÇÑ´Ù. Á¦¹°Àº ³ú°¡ ¾ø´Â ¸ó½ºÅÍ´Ù
		Monster* pMonster = new Monster( OfferingTemplate[m_Race].MonsterType );
		Assert( pMonster != NULL );

		pMonster->setName( OfferingTemplate[m_Race].Name[i] );
		pMonster->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );

		EffectCauseCriticalWounds* pEffect = new EffectCauseCriticalWounds( pMonster );
		pEffect->setDeadline( 999999 );
		pMonster->addEffect( pEffect );
		pMonster->setFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );

		try
		{
			m_pZone->addCreature( pMonster, OfferingCoordinate[i].X, OfferingCoordinate[i].Y, 2 );

/*			NPCInfo* pNPCInfo = new NPCInfo;
			pNPCInfo->setName( pMonster->getName() );
			pNPCInfo->setNPCID( pMonster->getMonsterType() );
			pNPCInfo->setX( pMonster->getX() );
			pNPCInfo->setY( pMonster->getY() );

			m_pZone->addNPCInfo( pNPCInfo );*/

			m_OfferingObjectID[i] = pMonster->getObjectID();
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
	}

	return true;
}

bool DynamicZoneAlterOfBlood::checkNoOffering()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	for ( int i=0; i<5; ++i )
	{
		if ( pMonsterManager->getCreature( m_OfferingObjectID[i] ) != NULL )
			return false;
	}

	return true;
}

bool DynamicZoneAlterOfBlood::clearOffering()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	for ( int i=0; i<5; ++i )
	{
		Creature* pCreature = pMonsterManager->getCreature( m_OfferingObjectID[i] );
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
	}

	return true;
}

bool DynamicZoneAlterOfBlood::openGateToOut()
{
    // Äù½ºÆ®¸¦ ÁøÇà½ÃÅ²´Ù.
    unordered_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    unordered_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

            pPC->getGQuestManager()->clearDynamicZone(m_TemplateZoneID);
			cout << "---------------------------------Clear Alter of Blood" << endl;
        }
    }

	// Æ÷Å» À§Ä¡¸¦ Ã£¾Æ¼­ ±× À§¿¡´Ù EffectTilePortal À» º¸³½´Ù.
	int tx = -1;
	int ty = -1;
	for (int x=0; x<m_pZone->getWidth(); x++)
	{
		for (int y=0; y<m_pZone->getHeight(); y++)
		{
			Tile& tile = m_pZone->getTile(x,y);

			if (tile.hasPortal())
			{
				tx = x;
				ty = y;
			}
		}
	}

	if ( tx != -1 )
	{
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setEffectID( Effect::EFFECT_CLASS_TILE_PORTAL );
		gcAddEffectToTile.setDuration( 999999 );
		gcAddEffectToTile.setXY( tx, ty );

		m_pZone->broadcastPacket( &gcAddEffectToTile );
	}

	return true;
}

void DynamicZoneAlterOfBlood::processEntering()
{
    // Äù½ºÆ® Á¸¿¡ µé¾î¿ÔÀ½À» ¾Ë¸°´Ù
    unordered_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    unordered_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneAlterOfBlood, DYNAMIC_ZONE_ALTER_OF_BLOOD )

