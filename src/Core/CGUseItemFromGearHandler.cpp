//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromGearHandler.cpp
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseItemFromGear.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Creature.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "ItemUtil.h"
	#include "CreatureUtil.h"
	#include "PCFinder.h"
	#include "EffectLoveChain.h"
	#include "PKZoneInfoManager.h"
	#include <stdio.h>

	#include "VariableManager.h"
	#include "DB.h"

	#include "item/CoupleRingBase.h"

	#include "GCCannotUse.h"
	#include "GCUseOK.h"

	#include "SystemAvailabilitiesManager.h"
	#include "war/WarSystem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromGearHandler::execute(CGUseItemFromGear* pPacket, Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << "CGUseItemFromGearHandler " << endl;
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Zone*      pZone      = pPC->getZone();

	Assert(pZone != NULL);

	Item* pItem;

	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		pItem = pSlayer->getWearItem( (Slayer::WearPart)(pPacket->getPart()) );
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		pItem = pVampire->getWearItem( (Vampire::WearPart)(pPacket->getPart()) );
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		pItem = pOusters->getWearItem( (Ousters::WearPart)(pPacket->getPart()) );
	}
	else
	{
		Assert(false);
	}

	if ( pItem == NULL )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}


	ObjectID_t ItemObjectID = pItem->getObjectID();

	// OID�� ��ġ���� �ʰų�, ����� �� ���� �������̶�� ������.
	if (ItemObjectID != pPacket->getObjectID() || !isUsableItem(pItem, pCreature))
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// �������� ������ ����, ó�� �Լ��� �б���� �ش�.
	//cout << pItem->getItemClass() << endl;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
			SYSTEM_ASSERT( SYSTEM_COUPLE );
			executeCoupleRing(pPacket, pGamePlayer);
			break;
		default:
			Assert(false);
			break;
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromGearHandler::executeCoupleRing(CGUseItemFromGear* pPacket, GamePlayer* pGamePlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << pPacket->toString().c_str() << endl;

	Assert(pPacket != NULL);
	Assert(pGamePlayer != NULL);

	// ���� �Լ����� ���� üũ�� ���� �߱� ������,
	// ���� üũ�� ���� ����Ѵ�.
	Creature*       pCreature			= pGamePlayer->getCreature();
	PlayerCreature* pPC					= dynamic_cast<PlayerCreature*>(pCreature);
	CoupleRingBase*	pCoupleRing			= NULL;

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		pCoupleRing = dynamic_cast<CoupleRingBase*>(pSlayer->getWearItem( (Slayer::WearPart)(pPacket->getPart()) ));
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		pCoupleRing = dynamic_cast<CoupleRingBase*>(pVampire->getWearItem( (Vampire::WearPart)(pPacket->getPart()) ));
	}
	else
	{
		Assert(false);
	}

	if ( pCreature->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) 
		|| pCreature->isFlag( Effect::EFFECT_CLASS_HAS_SWEEPER) ) return;

	Assert( pCoupleRing != NULL );

	string 			targetName			= pCoupleRing->getName();
	Creature*		pTargetCreature		= NULL;

	bool bValidZone = false;

	// trace �ϴ� �κ�
    __ENTER_CRITICAL_SECTION((*g_pPCFinder))

    pTargetCreature = g_pPCFinder->getCreature_LOCKED(targetName);
    if (pTargetCreature==NULL)
    {
   		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);

     	g_pPCFinder->unlock();
        return;
    }

	Zone* pTargetZone = pTargetCreature->getZone();
	if ( pTargetZone != NULL )
	{
		// ������ɺ�, �ÿܰ�����, �̺�Ʈ�����, �̺�ƮOX ��, �����ͷ���, ����, PK��, ���̳��� �����δ� �� �� ����.
		bValidZone = pTargetZone->getZoneID() != 2101 && pTargetZone->getZoneID() != 2102 &&
					 pTargetZone->getZoneID() != 1005 && pTargetZone->getZoneID() != 1006 &&
					 pTargetZone->getZoneID() != 1122 && pTargetZone->getZoneID() != 1131 &&
					 pTargetZone->getZoneID() != 1132 && pTargetZone->getZoneID() != 1133 &&
					 pTargetZone->getZoneID() != 1134 && !pTargetZone->isCastleZone() &&
					 !pTargetZone->isMasterLair() &&
					 (!g_pWarSystem->hasActiveRaceWar() || !pTargetZone->isHolyLand()) && !pTargetZone->isCastle() &&
					 !g_pPKZoneInfoManager->isPKZone( pTargetZone->getZoneID() ) &&
					 !pTargetZone->isDynamicZone();
	}
    __LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	// �� �� ���� ���̶�� ���д�.
	if ( !bValidZone )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 10 �� ���� ������ �� ������ ����Ʈ�� ���δ�.
	EffectLoveChain* pEffect= new EffectLoveChain(pPC);
	pEffect->setItemObjectID( pPacket->getObjectID() );
	pEffect->setDeadline(100);
	pEffect->setTargetName( targetName );
	pEffect->setZone( pZone );

	ObjectRegistry & objectregister = pZone->getObjectRegistry();
	objectregister.registerObject(pEffect);

	pZone->addEffect(pEffect);
	pPC->setFlag(Effect::EFFECT_CLASS_LOVE_CHAIN);

	GCUseOK gcUseOK;
	gcUseOK.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_LOVE_CHAIN);
	pGamePlayer->sendPacket( &gcUseOK );

#endif
    __END_DEBUG_EX __END_CATCH
}

