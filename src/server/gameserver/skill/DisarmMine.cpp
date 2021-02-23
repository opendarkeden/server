//////////////////////////////////////////////////////////////////////////////
// Filename    : DisarmMine.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DisarmMine.h"
#include "Assert.h"
#include "SkillInfo.h"
#include "EffectDarkness.h"
#include "item/Mine.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillFailed1.h"
#include "Gpackets/GCSkillFailed2.h"
#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void DisarmMine::execute( Slayer  * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	/*
	try
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
	}
	catch (Throwable & t)
	{
	}
	*/

	__END_CATCH
}

/*

void DisarmMine::execute( Slayer  * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	try
	{

	//Assert( pSkillSlot != NULL );
	if (pSkillSlot == NULL)
	{
		cout << "DisarmMine : 스킬 슬랏이 널입니다." << endl;
		GCSkillFailed1 _GCSkillFailed1;
		pSlayer->getPlayer()->sendPacket( &_GCSkillFailed1);
		return;
	}
	
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

DisarmMine g_DisarmMine;
