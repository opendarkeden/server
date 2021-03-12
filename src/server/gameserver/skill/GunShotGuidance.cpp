//////////////////////////////////////////////////////////////////////////////
// Filename    : GunShotGuidance.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GunShotGuidance.h"
#include "EffectGunShotGuidanceAim.h"
#include "EffectGunShotGuidancePoint.h"

#include "ItemUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void GunShotGuidance::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC()
			)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void GunShotGuidance::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 총을 들고 있는지 확인한다.
		Item* pItem = pSlayer->getWearItem( Slayer::WEAR_RIGHTHAND );
		if ( pItem == NULL || isArmsWeapon( pItem ) == false )
		{
			executeSkillFailException( pSlayer, getSkillType() );
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		//SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());
		bool bEffected	 = pSlayer->isFlag( Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM );

		bool bTileCheck = false;
		VSRect rect( 0, 0, pZone->getWidth()-1, pZone->getHeight()-1 );
		if ( rect.ptInRect( X, Y ) )
		{
			Tile& tile = pZone->getTile(X,Y);
			if ( tile.canAddEffect() ) bTileCheck = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected && bTileCheck )
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// 데미지와 지속 시간을 계산한다.
			SkillInput input(pSlayer, pSkillSlot); // pSkillSlot 추가 by Sequoia 2002.12.28
			SkillOutput output;
			computeOutput(input, output);

			Tile& tile = pZone->getTile( X, Y );

			// 같은 이펙트가 이미 존재한다면 삭제한다.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_POINT);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 이펙트 오브젝트를 생성한다.
			EffectGunShotGuidanceAim* pEffect = new EffectGunShotGuidanceAim(pSlayer, pZone, X, Y);
			pEffect->setDamage(output.Damage);
			pEffect->setDeadline(output.Duration);

			pSlayer->addEffect( pEffect );
			pSlayer->setFlag( Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM );

			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(output.Range);
		
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(output.Range);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(output.Range);

			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// GunShotGuidanceAim 이펙트를 브로드캐스팅 한다.
			GCAddEffect gcAddAimEffect;
			gcAddAimEffect.setObjectID( pSlayer->getObjectID() );
			gcAddAimEffect.setEffectID( Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM );
			gcAddAimEffect.setDuration( output.Duration );
			pZone->broadcastPacket( myX, myY, &gcAddAimEffect );

			///////////////////////////////////////////////////////////////////
			// GunShotGuidancePoint 이펙트를 만들어서 붙이고 브로드캐스팅 한다.
			///////////////////////////////////////////////////////////////////
			EffectGunShotGuidancePoint* pPointEffect = new EffectGunShotGuidancePoint( pZone, X, Y );
			pPointEffect->setDeadline( output.Duration );

			ObjectRegistry & objectRegister = pZone->getObjectRegistry();
			objectRegister.registerObject( pPointEffect );

			pZone->addEffect( pPointEffect );
			tile.addEffect( pPointEffect );

			GCAddEffectToTile gcAddEffectToTile;
			gcAddEffectToTile.setObjectID( pPointEffect->getObjectID() );
			gcAddEffectToTile.setEffectID( pPointEffect->getEffectClass() );
			gcAddEffectToTile.setXY( X, Y );
			gcAddEffectToTile.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffectToTile );

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	__END_CATCH
}

void GunShotGuidance::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) 
{
	__BEGIN_TRY

	try 
	{
		cout << pMonster->getName() << " use gunshotguiadance" << endl;
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = getSkillType();
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bTileCheck)
		{
			Tile& tile = pZone->getTile(X, Y);
		
			ZoneCoord_t myX = pMonster->getX();
			ZoneCoord_t myY = pMonster->getY();

			// 같은 이펙트가 이미 존재한다면 삭제한다.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_POINT);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 데미지와 지속 시간을 계산한다.
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);
		
			// 이펙트 오브젝트를 생성한다.
			EffectGunShotGuidanceAim* pEffect = new EffectGunShotGuidanceAim(pMonster, pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamage(output.Damage);

			pMonster->setFlag( Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM );
			pMonster->addEffect( pEffect );

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(1);
		
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(1);
	
			list<Creature*> cList;
			cList.push_back(pMonster);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// GunShotGuidanceAim 이펙트를 브로드캐스팅 한다.
			GCAddEffect gcAddAimEffect;
			gcAddAimEffect.setObjectID( pMonster->getObjectID() );
			gcAddAimEffect.setEffectID( Effect::EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM );
			gcAddAimEffect.setDuration( output.Duration );
			pZone->broadcastPacket( myX, myY, &gcAddAimEffect );

			EffectGunShotGuidancePoint* pPointEffect = new EffectGunShotGuidancePoint( pZone, X, Y );
			pPointEffect->setDeadline( output.Duration );

			ObjectRegistry & objectRegister = pZone->getObjectRegistry();
			objectRegister.registerObject( pPointEffect );

			pZone->addEffect( pPointEffect );
			tile.addEffect( pPointEffect );

			GCAddEffectToTile gcAddEffectToTile;
			gcAddEffectToTile.setObjectID( pPointEffect->getObjectID() );
			gcAddEffectToTile.setEffectID( pPointEffect->getEffectClass() );
			gcAddEffectToTile.setXY( X, Y );
			gcAddEffectToTile.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffectToTile );
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	__END_CATCH
}

GunShotGuidance g_GunShotGuidance;
