//////////////////////////////////////////////////////////////////////////////
// Filename    : Creature.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Creature.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "Slayer.h"
#include "Party.h"
#include "ZoneUtil.h"
#include "VisionInfo.h"

#include "Gpackets/GCSay.h"
#include "Effect.h"
//#include "EffectHPRecovery.h"


//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
Creature::Creature (ObjectID_t objectID , Player* pPlayer) 
	 
: Object(objectID)
{
	__BEGIN_TRY

	m_pPlayer        = pPlayer;
	m_MoveMode       = MOVE_MODE_WALKING;
	m_pZone          = NULL;
	m_pEffectManager = new EffectManager();
	m_PartyID        = 0;

	m_pNewZone       = NULL;

	m_bDeriveDestructed = false;
	m_Value = 999;

	m_CClass = CREATURE_CLASS_MAX;

	Assert(m_pEffectManager != NULL);

	m_LastTarget = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////
Creature::~Creature () 
    
{
	__BEGIN_TRY

	m_pPlayer = NULL;	// delete는 외부에서 한다.
	SAFE_DELETE(m_pEffectManager);

	if ( m_CClass == CREATURE_CLASS_SLAYER || m_CClass == CREATURE_CLASS_VAMPIRE )
	{
		if ( !m_bDeriveDestructed )
		{
			filelog( "destructor.log", "Name : %s Class : %d value : %d" , m_Owner.c_str(), (int)m_CClass, m_Value );
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get object priority
// 타일의 Object List 상의 우선순위값을 리턴한다.
// 크리처의 경우, 이동 모드에 따라서 이 우선순위가 결정된다.
//////////////////////////////////////////////////////////////////////////////
ObjectPriority Creature::getObjectPriority () const
	
{
	__BEGIN_TRY

	switch (m_MoveMode) 
	{
		case MOVE_MODE_WALKING:   return OBJECT_PRIORITY_WALKING_CREATURE;
		case MOVE_MODE_FLYING:    return OBJECT_PRIORITY_FLYING_CREATURE;
		case MOVE_MODE_BURROWING: return OBJECT_PRIORITY_BURROWING_CREATURE;
		default : throw Error("invalid move mode");
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// vision state 관련 메쏘드
//////////////////////////////////////////////////////////////////////////////
VisionState Creature::getVisionState (ZoneCoord_t x , ZoneCoord_t y) 
	
{
	__BEGIN_DEBUG

	// 주석처리 by sigi
	//if (isFlag(Effect::EFFECT_CLASS_DARKNESS))
	//	return g_pVisionInfoManager->getVisionInfo(DARKNESS_SIGHT,m_Dir)->getVisionState(m_X,m_Y,x,y);
	//return g_pVisionInfoManager->getVisionInfo(m_Sight,m_Dir)->getVisionState(m_X,m_Y,x,y);
	return VisionInfoManager::getVisionState( m_X, m_Y, x, y );

	__END_DEBUG
}

VisionState Creature::getVisionState (Coord_t x , Coord_t y, Sight_t sight) 
	
{
	__BEGIN_DEBUG

//	return g_pVisionInfoManager->getVisionInfo(sight,m_Dir)->getVisionState(m_X,m_Y,x,y);
	return VisionInfoManager::getVisionState( m_X, m_Y, x, y );

	__END_DEBUG
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
ZoneID_t Creature::getZoneID () const
	
{
	return (m_pZone) ? m_pZone->getZoneID() : 0 ;
}

ZoneID_t Creature::getNewZoneID () const
	
{
	return (m_pNewZone) ? m_pNewZone->getZoneID() : 0 ;
}

//////////////////////////////////////////////////////////////////////////////
// set zone id
//
// (1) ZoneInfoManager 에서 ZoneID 를 사용해서 ZoneInfo 객체에 접근한다.�
// (2) ZoneInfo 객체에서 ZoneGroupID 를 알아낸다.
// (3) ZoneGroupManager 에서 ZoneGroupID 를 사용해서 ZoneGroup 에 접근한다.
// (4) ZoneGroup 에서 ZoneID 를 사용해서 Zone 에 접근한다.
//////////////////////////////////////////////////////////////////////////////
void Creature::setZoneID (ZoneID_t zoneID)
	
{
	__BEGIN_TRY

	try 
	{
		ZoneInfo* m_pZoneInfo = g_pZoneInfoManager->getZoneInfo(zoneID);
		Assert(m_pZoneInfo != NULL);

		ZoneGroupID_t zoneGroupID = m_pZoneInfo->getZoneGroupID();

		m_pZone = g_pZoneGroupManager->getZoneGroup(zoneGroupID)->getZone(zoneID);
		Assert(m_pZone != NULL);
	} 
	catch (NoSuchElementException & nsee) 
	{
		StringStream msg;
		msg << "data intergrity broken : "
			<< "ZoneID - Zone - ZoneGroupID - ZoneGroup - ZoneInfo 간의 무결성이 깨졌당.\n"
			<< nsee.toString();

		cerr << msg.toString() << endl;

		throw Error(msg.toString());
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// (nx,ny)로 이동할 수 있는가?
//////////////////////////////////////////////////////////////////////////////
bool Creature::canMove (ZoneCoord_t nx , ZoneCoord_t ny) const
	
{
	Assert(m_pZone != NULL);

	// 올바른 좌표인가?
	// 막혀있지는 않은가?
	if (//isFlag(Effect::EFFECT_CLASS_SANCTUARY)
		// m_Flag.test(Effect::EFFECT_CLASS_SANCTUARY)
		m_Flag.test(Effect::EFFECT_CLASS_POISON_MESH)
		|| m_Flag.test(Effect::EFFECT_CLASS_TENDRIL)
		|| m_Flag.test(Effect::EFFECT_CLASS_BLOODY_WALL_BLOCKED)
		|| m_Flag.test(Effect::EFFECT_CLASS_CASKET)
		|| !isValidZoneCoord(m_pZone, nx, ny)) return false;

	/*
	// 성물을 가지고 있는 경우라면..
	if (m_Flag.test(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC)
		|| m_Flag.test(Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC))
	{
		ZoneLevel_t ZoneLevel = m_pZone->getZoneLevel(nx, ny);

		// 슬레이어이면 슬레이어 안전지대에 못 들어간다.
		// 뱀파이어이면  뱀파이어안전지대에 못 들어간다.
		// 공통 안전지대이면 못 들어간다.
		if (isSlayer() && (ZoneLevel & SLAYER_SAFE_ZONE)
			|| isVampire() && (ZoneLevel & VAMPIRE_SAFE_ZONE)
			|| (ZoneLevel & COMPLETE_SAFE_ZONE))
		{
			return false;
		}
	}
	*/

	Tile& rTile = m_pZone->getTile(nx,ny);

	if (rTile.isBlocked(m_MoveMode)
		// BloodyWallBlock나
		// Sanctuary 이펙트가 걸려있다면 못 간다.
		|| rTile.hasEffect() 
			&& (rTile.getEffect(Effect::EFFECT_CLASS_BLOODY_WALL_BLOCKED)
				|| rTile.getEffect(Effect::EFFECT_CLASS_SANCTUARY))
		)
	{
		return false;
	}

	Tile& rNewTile = m_pZone->getTile(getX(), getY());

	if ( rNewTile.getEffect(Effect::EFFECT_CLASS_SANCTUARY) )
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
// (nx,ny)이 맵에 의해 막히는가?
//////////////////////////////////////////////////////////////////////////////
bool Creature::isBlockedByCreature (ZoneCoord_t nx , ZoneCoord_t ny) const
	
{
	Assert(m_pZone != NULL);

	// 올바른 좌표인가?
	// 같은 무드 모드의 크리쳐가 존재하지 않는가?
	if (!isValidZoneCoord(m_pZone, nx, ny)
		|| !m_pZone->getTile(nx,ny).hasCreature(m_MoveMode)) return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Creature::recoverHP(HP_t addHP) 
{
/*
    if (isSlayer())
    {
		Slayer* pSlayer = dynamic_cast<Slayer*>(this);
		HP_t destHP = min((int)pSlayer->getHP(ATTR_MAX), pSlayer->getHP(ATTR_CURRENT)+addHP);
		
        EffectHPRecovery* pEffect = NULL;
        if (isFlag(Effect::EFFECT_CLASS_HP_RECOVERY))
        {
            m_pEffectManager->deleteEffect(this, Effect::EFFECT_CLASS_HP_RECOVERY);
        }

        setFlag(Effect::EFFECT_CLASS_HP_RECOVERY);
        pEffect = new EffectHPRecovery(this);
		pEffect->setDestPoint(destHP);
//        pEffect->setPoint(10);
//        pEffect->setDelay(2);  // 0.2초 마다..
//        pEffect->setDeadline(10000);    // 적당한 값. deadline은 무의미..
        pEffect->setDeadline(10);    // delay 


        m_pEffectManager->addEffect(pEffect);

    }
    else
    {
    }
*/
}

//////////////////////////////////////////////////////////////////////////////
// 거리 계산 함수
//////////////////////////////////////////////////////////////////////////////
Distance_t Creature::getDistance (ZoneCoord_t x1 , ZoneCoord_t y1 , ZoneCoord_t x2 , ZoneCoord_t y2) const 
	
{
	__BEGIN_TRY

    return max(abs(x1-x2) , abs(y1-y2));

	__END_CATCH
}

Distance_t Creature::getDistance (ZoneCoord_t x1 , ZoneCoord_t y1) const 
	
{
	__BEGIN_TRY

    return max(abs(m_X-x1) , abs(m_Y-y1));

	__END_CATCH
}

bool Creature::isEffect(Effect::EffectClass EClass) 
	
{
	__BEGIN_TRY
	
	Assert(m_pEffectManager != NULL);
	return m_pEffectManager->isEffect(EClass);
	
	__END_CATCH
}

void Creature::deleteEffect(Effect::EffectClass EClass) 
	
{
	__BEGIN_TRY

	Assert(m_pEffectManager != NULL);
	m_pEffectManager->deleteEffect(this, EClass);

	__END_CATCH
}

Effect* Creature::findEffect(Effect::EffectClass EClass) const
	
{
	__BEGIN_TRY

	Assert(m_pEffectManager != NULL);
	return m_pEffectManager->findEffect(EClass);

	__END_CATCH
}

void Creature::addEffect(Effect* pEffect) 
	
{
	__BEGIN_TRY

	Assert(m_pEffectManager != NULL);
	m_pEffectManager->addEffect(pEffect);

	__END_CATCH
}

LocalPartyManager* Creature::getLocalPartyManager(void) const 
	
{
	__BEGIN_TRY

	if (m_pZone != NULL)
	{
		return m_pZone->getLocalPartyManager();
	}

	return NULL;

	__END_CATCH
}

bool Creature::hasRelicItem() const
{
	return m_Flag.test(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC)
			|| m_Flag.test(Effect::EFFECT_CLASS_HAS_VAMPIRE_RELIC) 
			|| m_Flag.test(Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE)
			|| m_Flag.test(Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL)
			|| m_Flag.test(Effect::EFFECT_CLASS_DRAGON_EYE);
}

Sight_t Creature::getEffectedSight()
	
{
	if ( isFlag( Effect::EFFECT_CLASS_LIGHTNESS ) )
		return LIGHTNESS_SIGHT;

	if ( isFlag( Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE ) )
		return YELLOW_POISON_SIGHT;

	if ( isFlag( Effect::EFFECT_CLASS_FLARE ) )
		return FLARE_SIGHT;

	return DEFAULT_SIGHT;
}

