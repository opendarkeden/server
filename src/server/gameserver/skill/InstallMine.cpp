//////////////////////////////////////////////////////////////////////////////
// Filename    : InstallMine.cpp
// Written by  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "InstallMine.h"
#include "Assert.h"
#include "SkillInfo.h"
#include "ItemUtil.h"

#include "item/Mine.h"

#include "Gpackets/GCSkillToInventoryOK1.h"
//#include "Gpackets/GCSkillToTileOK1.h"
//#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillFailed1.h"
#include "Gpackets/GCSkillFailed2.h"
#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCDeleteObject.h"
#include "ItemInfoManager.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void InstallMine::execute(Slayer* pSlayer, ObjectID_t, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) 
	
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;
//		GCSkillToTileOK1 _GCSkillToTileOK1;
//		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo( SkillType );
		SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

		// 명중률.
		//ToHit_t ToHit = pSlayer->getToHit();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		ZoneCoord_t slayerX = pSlayer->getX(), slayerY = pSlayer->getY();
		bool bInstallAction = false;

		Mine* pMine = NULL;

		Inventory * pInventory = pSlayer->getInventory();
		Assert( pInventory != NULL );

		if( bManaCheck && bTimeCheck &&bRangeCheck ) {
			// mine을 찾는다.
			Item* pItem = pInventory->getItem( X, Y);
			if( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_MINE)
			{
				bInstallAction = true;
				pMine = dynamic_cast<Mine*>(pItem);
			}
		}


		// 기술의 성패를 따진다.
		if ( bInstallAction ) 
		{
			//Range_t Range = 1; 

			GCSkillToInventoryOK1 _GCSkillToInventoryOK1;
//			GCSkillToInventoryOK5 _GCSkillToInventoryOK5;
		
			ItemInfo*       pItemInfo = g_pItemInfoManager->getItemInfo(Item::ITEM_CLASS_MINE, pMine->getItemType());

			Damage_t MinDamage = pItemInfo->getMinDamage();
			Damage_t MaxDamage = pItemInfo->getMaxDamage();

			Damage_t RealDamage = MinDamage + ( max ( 0, ( (int)MaxDamage * (int)SkillLevel / 100 ) - MinDamage ) );

			Mine * pInstallMine = new Mine();
			ObjectRegistry& OR = pZone->getObjectRegistry();
			OR.registerObject(pInstallMine);

			Assert( pInstallMine != NULL );
			pInstallMine->setItemType( pMine->getItemType() ); 
			pInstallMine->setDir( TargetX ); 
			pInstallMine->setDamage( RealDamage ); 
			pInstallMine->setInstallerName( pSlayer->getName() );
			pInstallMine->setInstallerPartyID( pSlayer->getPartyID() );
			pInstallMine->setFlag( Effect::EFFECT_CLASS_INSTALL);

			// 아이템 사라지는게 3분인거 때문에 지뢰도 사라졌는데.. 
			// 10분으로 고정. by sigi. 2002.11.3
			TPOINT pt = pZone->addItem(pInstallMine, slayerX, slayerY, true, 6000);

			// EXP up
			Exp_t Point = pSkillInfo->getPoint();

			shareAttrExp(pSlayer, 100, 1, 8, 1, _GCSkillToInventoryOK1);
			increaseDomainExp(pSlayer, SKILL_DOMAIN_GUN, Point, _GCSkillToInventoryOK1);
			increaseSkillExp(pSlayer, SKILL_DOMAIN_GUN, pSkillSlot, pSkillInfo, _GCSkillToInventoryOK1);

			decreaseMana(pSlayer, RequiredMP, _GCSkillToInventoryOK1);
			decreaseItemNum(pMine, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, X, Y);


			_GCSkillToInventoryOK1.setObjectID( pInstallMine->getObjectID() );
			_GCSkillToInventoryOK1.setSkillType( SkillType );
			_GCSkillToInventoryOK1.setCEffectID( 0 );
			_GCSkillToInventoryOK1.setX( X );
			_GCSkillToInventoryOK1.setY( Y );
			_GCSkillToInventoryOK1.setDuration( 0 );

			/*
			_GCSkillToInventoryOK5.setObjectID( pSlayer->getObjectID());
			_GCSkillToInventoryOK5.setSkillType( SkillType);
			_GCSkillToInventoryOK5.setX( X);
			_GCSkillToInventoryOK5.setY( Y);
			_GCSkillToInventoryOK5.setRange( Range);
			_GCSkillToInventoryOK5.setDuration( 0);
			*/

			pPlayer->sendPacket( &_GCSkillToInventoryOK1 );

			// mine을 볼 수 없게 된 자들에게는 삭제 
			addInstalledMine( pZone, pInstallMine, pt.x, pt.y);

//			pZone->broadcastPacket( slayerX, slayerY, &_GCSkillToInventoryOK5, pSlayer);

	//        cout << "Run Skill : " << (int)SkillType << endl;
			// Set NextTime
			pSkillSlot->setRunTime();

		} 
		else 
		{
			GCSkillFailed1 _GCSkillFailed1;
			GCSkillFailed2 _GCSkillFailed2;

			executeSkillFailException(pSlayer, getSkillType());
		}

	}
	catch(Throwable & t)
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	__END_CATCH
}

/*
void InstallMine::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY


	try
	{

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK5 _GCSkillToTileOK5;




	
    SkillType_t SkillType = pSkillSlot->getSkillType();
    SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo( SkillType );
    SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

	// 명중률.
	ToHit_t ToHit = pSlayer->getToHit();

    int RemainMP = (int)pSlayer->getMP( ATTR_CURRENT) - (int)pSkillInfo->getConsumeMP();
    bool bModifyMP = false;
    if( RemainMP >= 0 && verifyRunTime(pSkillSlot) && 
		pZone->getZoneLevel(pSlayer->getX(), pSlayer->getY()) != 0)
    {
        pSlayer->setMP( RemainMP , ATTR_CURRENT );
        bModifyMP = true;

    }

	// Installed mine을 찾는다.
	Mine* pMine = NULL;
	bool bInstallAction = false;	// install or disarm
	Item* pItem = pZone->getTile( X, Y).getItem();
	if( pItem && pItem->getItemClass() == Item::ITEM_CLASS_MINE)
	{
		if( pItem->isFlag( Effect::EFFECT_CLASS_INSTALL))
		{
			if( pSlayer->isFlag( Effect::EFFECT_CLASS_DETECT_MINE)) 	// 현재 볼 수 있는상태인지 확인.
			{
				bInstallAction = false;// disarm이닷
				pMine = dynamic_cast<Mine*>(pItem);
			}
		}
		else
		{
			bInstallAction = true;
			pMine = dynamic_cast<Mine*>(pItem);
		}
	}

	ZoneCoord_t slayerX = pSlayer->getX(), slayerY = pSlayer->getY();

    // 기술의 성패를 따진다.
    if ( pMine && bModifyMP && (ToHit + SkillLevel) > Random(0, 100) ) 
	{
		Range_t Range = 1; 

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK5 _GCSkillToTileOK5;
	
		if( bInstallAction)
		{
			pMine->setDir( calcDirection( slayerX, slayerY, X, Y)); 
			pMine->setFlag( Effect::EFFECT_CLASS_INSTALL);
			// mine을 볼 수 없게 된 자들에게는 삭제 
			addInstalledMine( pZone, pMine, X, Y);

		}
		else
		{	
			// 삭제한다.
			pZone->deleteItem( pMine, X, Y );
			GCDeleteObject gcDeleteObject;
			gcDeleteObject.setObjectID( pMine->getObjectID() );
			pZone->broadcastPacket( X, Y , &gcDeleteObject );
			pMine->destroy();
			delete pMine;
		}
	
		
		// EXP up
        Exp_t Point = pSkillInfo->getPoint();

		shareAttrExp(pSlayer, 100, 1, 8, 1, _GCSkillToTileOK1);
		increaseDomainExp(pSlayer, SKILL_DOMAIN_GUN, Point, _GCSkillToTileOK1);
		increaseSkillExp(pSlayer, SKILL_DOMAIN_GUN, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);

        _GCSkillToTileOK1.addLongData( MODIFY_CURRENT_MP , RemainMP );

        _GCSkillToTileOK1.setSkillType( SkillType );
        _GCSkillToTileOK1.setCEffectID( CEffectID );
        _GCSkillToTileOK1.setX( X );
        _GCSkillToTileOK1.setY( Y );
        _GCSkillToTileOK1.setDuration( 0 );


        _GCSkillToTileOK5.setObjectID( pSlayer->getObjectID());
        _GCSkillToTileOK5.setSkillType( SkillType);
        _GCSkillToTileOK5.setX( X);
        _GCSkillToTileOK5.setY( Y);
        _GCSkillToTileOK5.setRange( Range);
        _GCSkillToTileOK5.setDuration( 0);
		

        pPlayer->sendPacket( &_GCSkillToTileOK1 );
        pZone->broadcastPacket( slayerX, slayerY, &_GCSkillToTileOK5, pSlayer);

//        cout << "Run Skill : " << (int)SkillType << endl;
		// Set NextTime
		pSkillSlot->setRunTime();

	} 
	else 
	{
		GCSkillFailed1 _GCSkillFailed1;
		GCSkillFailed2 _GCSkillFailed2;

        if( bModifyMP)
            _GCSkillFailed1.addLongData( MODIFY_CURRENT_MP, RemainMP);
        pPlayer->sendPacket( &_GCSkillFailed1 );
	}


	} catch( Throwable & t )  {
		GCSkillFailed1 _GCSkillFailed1;
		pSlayer->getPlayer()->sendPacket( &_GCSkillFailed1);
		cout << t.toString() << endl;
	}

	__END_CATCH
}
*/

InstallMine g_InstallMine;
