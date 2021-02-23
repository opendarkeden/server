//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasBloodBible.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHasBloodBible.h"
#include "Creature.h"
#include "Slayer.h"
#include "BloodBible.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "Player.h"
#include "WarSystem.h"
#include "CastleInfoManager.h"
#include "ZoneInfoManager.h"
#include "HolyLandManager.h"
#include "ZoneGroupManager.h"
#include "ShrineInfoManager.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCBloodBibleStatus.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasBloodBible::EffectHasBloodBible(Creature* pCreature)
	throw(Error)
: EffectHasRelic( pCreature )
{
	__BEGIN_TRY

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasBloodBible::EffectHasBloodBible(Item* pItem)
	throw(Error)
: EffectHasRelic( pItem )
{
	__BEGIN_TRY

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasBloodBible::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//Timeval      nextTime   = getNextTime();
	//Timeval      deadLine   = getDeadline();
	//Turn_t       RemainTime = deadLine.tv_sec - nextTime.tv_sec;
		/*
	StringStream msg;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		msg << pSlayer->getName();
	}
	else
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		msg << pVampire->getName();
	}

	msg << " 님이 슬레이어 성물을 가졌습니다.";

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg.toString());

	g_pZoneGroupManager->broadcast( &gcSystemMessage );
	*/

	// 존 정보를 얻는다.
	Zone* pZone = pCreature->getZone();
	Assert(pZone!=NULL);

	/*
	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( pZone->getZoneID() );
	Assert( pZoneInfo != NULL );

	// 위치를 알린다.
	StringStream msg;
	msg << pCreature->getName() << " 님(" << ( pCreature->isSlayer() ? "슬레이어" : "뱀파이어" ) << ")이 " 
	    << pZoneInfo->getFullName() << "(" << (int)pCreature->getX() << ", " << (int)pCreature->getY()
		<< ")에서 피의 성서 조각(" << m_PartName << ")을 가지고 있습니다.";

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg.toString());

	g_pZoneGroupManager->broadcast( &gcSystemMessage );
	*/

	ShrineSet* pShrineSet = g_pShrineInfoManager->getShrineSet( m_Part );
	Assert(pShrineSet!=NULL);
	Race_t ShrineRace = pShrineSet->getOwnerRace();

	GCBloodBibleStatus* pGCBBS = new GCBloodBibleStatus;
	pGCBBS->setItemType( m_Part );
	pGCBBS->setZoneID( pZone->getZoneID() );
	pGCBBS->setStorage( STORAGE_INVENTORY );
	pGCBBS->setOwnerName( pCreature->getName() );
	pGCBBS->setRace( pCreature->getRace() );
	pGCBBS->setShrineRace( ShrineRace );
	pGCBBS->setX( pCreature->getX() );
	pGCBBS->setY( pCreature->getY() );

//	g_pHolyLandManager->broadcast( pGCBBS );
	g_pZoneGroupManager->broadcast( pGCBBS );
	g_pShrineInfoManager->registerBloodBibleStatus( m_Part, pGCBBS );

	setNextTime(m_Tick);
																															    	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasBloodBible::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	if (m_pZone==NULL) return;

		/*
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() );
		Assert( pZoneInfo != NULL );

		// 위치를 알린다.
		StringStream msg;
		msg << pZoneInfo->getFullName() << "(" << (int)m_X << ", " << (int)m_Y
			<< ")의 성단에 피의 성서 조각(" << m_PartName << ")이 있습니다.";

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg.toString());

		g_pZoneGroupManager->broadcast( &gcSystemMessage );
		*/

	ShrineSet* pShrineSet = g_pShrineInfoManager->getShrineSet( m_Part );
	Assert(pShrineSet!=NULL);

	GCBloodBibleStatus* pGCBBS = new GCBloodBibleStatus;
	pGCBBS->setItemType( m_Part );
	pGCBBS->setZoneID( m_pZone->getZoneID() );
	pGCBBS->setStorage( STORAGE_CORPSE );
	//pGCBBS->setOwnerName( m_PartName );
	pGCBBS->setRace( pShrineSet->getOwnerRace() ); 
	pGCBBS->setShrineRace( pShrineSet->getOwnerRace() ); 
	pGCBBS->setX( m_X );
	pGCBBS->setY( m_Y );

	// 성에 전쟁이 진행중인 경우만 메세지를 보내준다.
	if (g_pWarSystem->hasActiveRaceWar())
	{
		g_pHolyLandManager->broadcast( pGCBBS );
	}

	g_pShrineInfoManager->registerBloodBibleStatus( m_Part, pGCBBS );

	setNextTime(999999);

	__END_CATCH
}

void EffectHasBloodBible::setPart( int part )
	throw()
{
	__BEGIN_TRY

	const BloodBibleInfo* pBloodBibleInfo = dynamic_cast<const BloodBibleInfo*>(g_pBloodBibleInfoManager->getItemInfo( part ) );

	if ( pBloodBibleInfo != NULL )
	{
		m_Part = part;
		m_PartName = pBloodBibleInfo->getName();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHasBloodBible::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHasBloodBible("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
