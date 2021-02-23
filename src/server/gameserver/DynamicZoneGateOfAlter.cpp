/////////////////////////////////////////////////////////////////////////////
// DynamicZoneGateOfAlter.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneGateOfAlter.h"
#include "DynamicZoneInfo.h"
#include "PlayerCreature.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "PCManager.h"
#include "EffectManager.h"
#include "EffectDeleteTile.h"
#include "EffectTilePortal.h"
#include "GQuestManager.h"
#include "DB.h"
#include "Assert.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteEffectFromTile.h"

#include <stdio.h>
#include <stdlib.h>

const BYTE EffectMask[32][32] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

enum GATE_OF_ALTER_STATUS
{
	ADD_TILE_EFFECT_STATUS,
	WAIT_FOR_PC,
	DELETE_TILE_EFFECT_STATUS,
	OPEN_GATE_TO_ALTER,
	WAIT_FOR_CLEAR,
	REMOVE_TILE_EFFECT,
	WAIT_FOR_NO_EFFECT,
	GATE_OF_ALTER_STATUS_END,

	GATE_OF_ALTER_STATUS_MAX
};

DynamicZoneGateOfAlter::DynamicZoneGateOfAlter()
{
}

DynamicZoneGateOfAlter::~DynamicZoneGateOfAlter()
{
}

void DynamicZoneGateOfAlter::init()
{
	m_GOAStatus = ADD_TILE_EFFECT_STATUS;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
}

void DynamicZoneGateOfAlter::heartbeat()
{
	switch ( m_GOAStatus )
	{
	case ADD_TILE_EFFECT_STATUS:
		if ( addTileEffect() )
		{
			m_GOAStatus = WAIT_FOR_PC;
			cout << "WAIT_FOR_PC" << endl;
		}
		break;

	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			processEntering();
			addFakeEffect();
			m_GOAStatus = DELETE_TILE_EFFECT_STATUS;
			cout << "DELETE_TILE_EFFECT_STATUS" << endl;
		}
		break;

	case DELETE_TILE_EFFECT_STATUS:
		if ( checkNoEffect() )
		{
			m_GOAStatus = OPEN_GATE_TO_ALTER;
			cout << "OPEN_GATE_TO_ALTER" << endl;
		}
		break;

	case OPEN_GATE_TO_ALTER:
		if ( openGateToAlter() )
		{
			m_GOAStatus = WAIT_FOR_CLEAR;
			cout << "WAIT_FOR_CLEAR" << endl;
		}
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() )
		{
			m_GOAStatus = REMOVE_TILE_EFFECT;
			cout << "REMOVE_TILE_EFFECT" << endl;
		}
		break;

	case REMOVE_TILE_EFFECT:
		if ( removeTileEffect() )
		{
			m_GOAStatus = WAIT_FOR_NO_EFFECT;
			cout << "WAIT_FOR_NO_EFFECT" << endl;
		}
		break;

	case WAIT_FOR_NO_EFFECT:
		if ( checkNoEffect() )
		{
			m_GOAStatus = GATE_OF_ALTER_STATUS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "READY" << endl;
		}
		break;
	}

	if ( !checkPC() )
	{
		if ( m_GOAStatus == WAIT_FOR_PC || m_GOAStatus == ADD_TILE_EFFECT_STATUS )
		{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_Deadline )
			{
				cout << "----------------------------Wait Time Out" << endl;
				m_GOAStatus = WAIT_FOR_CLEAR;
			}
		}
		else if ( m_GOAStatus == DELETE_TILE_EFFECT_STATUS  )
		{
			m_GOAStatus = REMOVE_TILE_EFFECT;
		}
	}
}

bool DynamicZoneGateOfAlter::addTileEffect()
{
	Assert( m_pZone != NULL );

	// 바닥에 이펙트를 깐다.
	for ( ZoneCoord_t x = 0; x < m_pZone->getWidth(); ++x )
	//for ( ZoneCoord_t x = 15; x <= 17; ++x )
	{
		for ( ZoneCoord_t y = 0; y < m_pZone->getHeight(); ++y )
		//for ( ZoneCoord_t y = 15; y <= 17; ++y )
		{
			if ( EffectMask[y][x] != 0 )
			{
				// 타일을 가져와서 이펙트를 생성할 수 있는지 확인
				Tile& tile = m_pZone->getTile( x, y );

				if ( !tile.canAddEffect() || tile.hasEffect() )
					continue;

				// 이펙트 오브젝트 생성
				EffectDeleteTile* pEffect = new EffectDeleteTile( m_pZone, x, y );
				pEffect->setDeadline( 999999 );
				
				// 존에 OID 등록
				m_pZone->registerObject( pEffect );
				m_pZone->addEffect( pEffect );

				// 타일 에 붙이기
				tile.addEffect( pEffect );
			}
		}
	}

	return true;
}

bool DynamicZoneGateOfAlter::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneGateOfAlter::checkNoEffect()
{
	Assert( m_pZone != NULL );

	// 이펙트 수 체크
	uint size = m_pZone->getEffectManager()->getSize();

//		char msg[8];
//		sprintf( msg, "%u", size );
//		GCSystemMessage gcmsg;
//		gcmsg.setMessage( msg );
//		m_pZone->broadcastPacket( &gcmsg );

	return size == 0;
}

bool DynamicZoneGateOfAlter::openGateToAlter()
{
	Assert( m_pZone != NULL );

	// 퀘스트를 진행시킨다.
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

	// 포탈 위치를 찾아서 그 위에다 EffectTilePortal 을 보낸다.
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

bool DynamicZoneGateOfAlter::removeTileEffect()
{
	Assert( m_pZone != NULL );

	// 모든 이펙트를 지운다.
	m_pZone->getEffectManager()->setTimeOutAllEffect();

	return true;
}

void DynamicZoneGateOfAlter::removeEffect( ZoneCoord_t x, ZoneCoord_t y )
{
	Assert( m_pZone != NULL );

	VSRect rect(0,0,m_pZone->getWidth()-1,m_pZone->getHeight()-1);
	for ( int i = (int)x-1; i<=(int)x+1; i++ )
	{
		for ( int j = (int)y-1; j<=(int)y+1; j++ )
		{
			if ( !rect.ptInRect(i,j) )
				continue;

			Tile& tile = m_pZone->getTile(i,j);

			Effect* pEffect = tile.getEffect( Effect::EFFECT_CLASS_DELETE_TILE );

			if ( pEffect != NULL )
			{
				pEffect->setDeadline(0);
			}
		}
	}
}

void DynamicZoneGateOfAlter::addFakeEffect()
{
	Assert( m_pZone != NULL );

	// 모든 포탈위치로 FakeEffect 를 보낸다.
	for (int x=0; x<m_pZone->getWidth(); x++)
	{
		for (int y=0; y<m_pZone->getHeight(); y++)
		{
			Tile& tile = m_pZone->getTile(x,y);

			if (tile.hasPortal())
			{
				GCDeleteEffectFromTile gcDeleteEffectFromTile;
				gcDeleteEffectFromTile.setEffectID( Effect::EFFECT_CLASS_DELETE_TILE );
				gcDeleteEffectFromTile.setXY(x,y);
				m_pZone->broadcastPacket(&gcDeleteEffectFromTile);
			}
		}
	}
}

void DynamicZoneGateOfAlter::processEntering()
{
	// 퀘스트 존에 들어왔음을 알린다.
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


DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneGateOfAlter, DYNAMIC_ZONE_GATE_OF_ALTER )

