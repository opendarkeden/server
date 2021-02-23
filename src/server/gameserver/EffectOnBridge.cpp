//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectOnBridge.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectOnBridge.h"
#include "Zone.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Player.h"
#include "StringStream.h"
#include "ZoneUtil.h"
#include "skill/EffectBloodDrain.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectOnBridge::EffectOnBridge(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	setXY( x, y );
	setBroadcastingEffect(false);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectOnBridge::affect()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectOnBridge::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectOnBridge::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectOnBridge::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectOnBridge::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectOnBridge("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
void EffectOnBridgeLoader::load(Zone* pZone)
    throw(Error)
{
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB
    {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pResult = pStmt->executeQuery( "SELECT LeftX, TopY, RightX, BottomY, Value1, Value2, Value3 FROM ZoneEffectInfo WHERE ZoneID = %d AND EffectID = %d", pZone->getZoneID(), (int)Effect::EFFECT_CLASS_ON_BRIDGE);

        while (pResult->next())
        {
            int count = 0;

            ZoneCoord_t left    = pResult->getInt( ++count );
            ZoneCoord_t top     = pResult->getInt( ++count );
            ZoneCoord_t right   = pResult->getInt( ++count );
            ZoneCoord_t bottom  = pResult->getInt( ++count );
//          int         value1  = pResult->getInt( ++count );
//          int         value2  = pResult->getInt( ++count );
//          int         value3  = pResult->getInt( ++count );

            VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

            for ( int X = left ; X <= right ; X++ )
            for ( int Y = top ; Y <= bottom ; Y++ )
            {
                if ( rect.ptInRect(X, Y) )
                {
                    Tile& tile = pZone->getTile(X,Y);
                    if ( tile.canAddEffect() )
                    {
                        EffectOnBridge* pEffect = new EffectOnBridge(pZone, X, Y);

                        // 존 및 타일에다가 이펙트를 추가한다.
                        pZone->registerObject(pEffect);
                        pZone->addEffect(pEffect);
                        tile.addEffect(pEffect);
                    }
                }
            }
        }
    }
    END_DB(pStmt)

    __END_CATCH
}

EffectOnBridgeLoader* g_pEffectOnBridgeLoader = NULL;
