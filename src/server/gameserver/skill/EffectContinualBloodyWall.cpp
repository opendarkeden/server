//----------------------------------------------------------------------
//
// Filename    : EffectContinualBloodyWall.cpp
// Written by  : elca
//
//----------------------------------------------------------------------

// include files
#include "DB.h"
#include "Assert.h"
#include "EffectBloodyWall.h"
#include "EffectContinualBloodyWall.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "SkillUtil.h"
#include "Gpackets/GCAddEffectToTile.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectContinualBloodyWall::EffectContinualBloodyWall (Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);

	m_pZone = pZone;
	m_Tick = 30;
	m_Duration = 10;
	m_Damage = 1000;

	setNextTime(10);	// 1초 후 시작

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectContinualBloodyWall::~EffectContinualBloodyWall () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectContinualBloodyWall::affect()
	
{
	__BEGIN_TRY

	Assert(m_pZone!=NULL);

	VSRect rect(0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1);

	for ( int X = m_Left ; X <= m_Right ; X++ )
	for ( int Y = m_Top ; Y <= m_Bottom ; Y++ )
	{
		if ( rect.ptInRect(X, Y) )
		{
			Tile& tile = m_pZone->getTile( X, Y );
			if ( tile.canAddEffect() )
			{
				EffectBloodyWall* pEffect = new EffectBloodyWall(m_pZone, X, Y);
				pEffect->setDamage( getDamage() );
				pEffect->setDeadline( getDuration() );
				pEffect->setTick( getDuration() );
				pEffect->setNextTime(0);
				pEffect->setForce( true );

				m_pZone->registerObject(pEffect);
				m_pZone->addEffect(pEffect);
				tile.addEffect(pEffect);

				GCAddEffectToTile gcAddEffectToTile;
				gcAddEffectToTile.setEffectID( pEffect->getEffectClass() );
				gcAddEffectToTile.setXY(X, Y);
				gcAddEffectToTile.setDuration( getDuration() );

				m_pZone->broadcastPacket(X, Y, &gcAddEffectToTile);
			}

		}

	}

	setNextTime(m_Tick);
	
	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect()
//--------------------------------------------------------------------
void EffectContinualBloodyWall::unaffect()
	
{
	__BEGIN_TRY

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectContinualBloodyWall::toString () const 
	throw ()
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectContinualBloodyWall("
				<< "ZoneID:" << (int)m_pZone->getZoneID();
	}

	msg << ",Delay:" << (int)m_Tick
		<< ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}

void EffectContinualBloodyWallLoader::load(Zone* pZone)
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT LeftX, TopY, RightX, BottomY, Value1, Value2, Value3 FROM ZoneEffectInfo WHERE ZoneID = %d AND EffectID = %d", pZone->getZoneID(), (int)Effect::EFFECT_CLASS_CONTINUAL_BLOODY_WALL);

		while (pResult->next())
		{
			int count = 0;
			
			ZoneCoord_t left 	= pResult->getInt( ++count );
			ZoneCoord_t top 	= pResult->getInt( ++count );
			ZoneCoord_t right 	= pResult->getInt( ++count );
			ZoneCoord_t	bottom	= pResult->getInt( ++count );
			int 		value1	= pResult->getInt( ++count );
			int 		value2	= pResult->getInt( ++count );
			int 		value3	= pResult->getInt( ++count );

			EffectContinualBloodyWall* pEffect = new EffectContinualBloodyWall(pZone);
			pEffect->setRect(left, right, top, bottom);
			pEffect->setTick( value1 );
			pEffect->setDuration( value2 );
			pEffect->setDamage( value3 );

			// 존 및 타일에다가 이펙트를 추가한다.
			pZone->registerObject(pEffect);
			pZone->addEffect(pEffect);
		}
	}
	END_DB(pStmt)

	__END_CATCH
}

EffectContinualBloodyWallLoader* g_pEffectContinualBloodyWallLoader = NULL;
