
//////////////////////////////////////////////////////////////////////////////
// Filename    : RefusalEther.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RefusalEther.h"
#include "Creature.h"
#include "RankBonus.h"
#include "EffectDarkness.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCSkillFailed1.h"

RefusalEther::RefusalEther()
	throw()
{
};

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void RefusalEther::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try
	{
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void RefusalEther::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType(), Grade);
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pOusters->getX();
		ZoneCoord_t myY = pOusters->getY();

		// 이펙트의 지속시간을 계산한다.
		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );
		
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y)) bTileCheck = true;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck && bSatisfyRequire)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);
			list<Creature*> cList;

			for ( int ox = X-output.Range; ox <= X+output.Range; ++ox )
			for ( int oy = Y-output.Range; oy <= Y+output.Range; ++oy )
			{
				if ( !rect.ptInRect(ox,oy) ) continue;

				Tile& rTile = pZone->getTile(ox,oy);
				EffectDarkness* pEffect = dynamic_cast<EffectDarkness*>(rTile.getEffect(Effect::EFFECT_CLASS_DARKNESS));
				int ratio = 0;

				if ( pEffect != NULL )
				{
					if ( input.SkillLevel <= 15 )
					{
						ratio = pOusters->getLevel() + ( input.SkillLevel * 8.0 / 3.0 ) - pEffect->getLevel();
					}
					else
					{
						ratio = pOusters->getLevel() + 20 + ( input.SkillLevel * 4.0 / 3.0 ) - pEffect->getLevel();
						if ( input.SkillLevel == 30 ) ratio *= 1.1;
					}

					ratio = max( 20, ratio );
				}
				else
				{
					continue;
				}

				bool bHitRoll2	= (rand()%100) < ratio;

				if (bHitRoll2)
				{
					pZone->deleteEffect(pEffect->getObjectID());
					
					Creature* pTargetCreature = NULL;
					if (rTile.hasCreature(Creature::MOVE_MODE_WALKING))
						pTargetCreature = rTile.getCreature(Creature::MOVE_MODE_WALKING);

					GCDeleteEffectFromTile gcDeleteEffectFromTile;
					gcDeleteEffectFromTile.setXY(ox, oy);
					gcDeleteEffectFromTile.setObjectID(pEffect->getObjectID());
					gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_DARKNESS);
					pZone->broadcastPacket(ox, oy, &gcDeleteEffectFromTile);

					if ( pTargetCreature != NULL && pTargetCreature->isPC() && pTargetCreature->getObjectID() != pOusters->getObjectID() )
						cList.push_back( pTargetCreature );
				}
			}

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(0);
			_GCSkillToTileOK1.setGrade(Grade);

			_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(output.Duration);
			_GCSkillToTileOK2.setRange(0);
			//_GCSkillToTileOK2.addShortData(MODIFY_VISION, ICE_FIELD_SIGHT);
			_GCSkillToTileOK2.setGrade(Grade);

			_GCSkillToTileOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			_GCSkillToTileOK3.setGrade(Grade);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(0);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setGrade(Grade);

			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(0);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setGrade(Grade);

			_GCSkillToTileOK6.setOrgXY(myX, myY);
			_GCSkillToTileOK6.setSkillType(SkillType);
			_GCSkillToTileOK6.setX(X);
			_GCSkillToTileOK6.setY(Y);
			_GCSkillToTileOK6.setDuration(output.Duration);
			_GCSkillToTileOK6.setRange(0);
			//_GCSkillToTileOK6.addShortData(MODIFY_VISION, ICE_FIELD_SIGHT);
			_GCSkillToTileOK6.setGrade(Grade);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			list<Creature*>::iterator itr = cList.begin();
			list<Creature*>::iterator endItr = cList.end();

			for ( ; itr != endItr ; ++itr )
			{
				if ( (*itr)->isPC() )
				{
					(*itr)->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
			}

			cList.push_back(pOusters);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList, false);
			
			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);

			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL, Grade);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

RefusalEther g_RefusalEther;
