//////////////////////////////////////////////////////////////////////////////
// Filename    : HellFire.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "HellFire.h"
#include "EffectHellFire.h"
#include "Creature.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCSkillFailed1.h"

HellFire::HellFire()
	throw()
{
	m_HellFireMask[0][0].set( 0, 0 );
	m_MaskNum[0] = 1;

	m_HellFireMask[1][0].set( -1, 0 );
	m_HellFireMask[1][1].set( 0, 0 );
	m_HellFireMask[1][2].set( 1, 0 );
	m_MaskNum[1] = 3;

	m_HellFireMask[2][0].set( -1, 0 );
	m_HellFireMask[2][1].set( 1, 0 );
	m_HellFireMask[2][2].set( 0, 0 );
	m_HellFireMask[2][3].set( 0, 1 );
	m_HellFireMask[2][4].set( 0, -1 );
	m_MaskNum[2] = 5;

	m_HellFireMask[3][0].set( -1, -1 );
	m_HellFireMask[3][1].set( -1, 0 );
	m_HellFireMask[3][2].set( -1, 1 );
	m_HellFireMask[3][3].set( 0, -1 );
	m_HellFireMask[3][4].set( 0, 0 );
	m_HellFireMask[3][5].set( 0, 1 );
	m_HellFireMask[3][6].set( 1, -1 );
	m_HellFireMask[3][7].set( 1, 0 );
	m_HellFireMask[3][8].set( 1, 1 );
	m_MaskNum[3] = 9;

};

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void HellFire::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try
	{
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pOusters, pTargetCreature )
			)
		{
			executeSkillFailException(pOusters, getSkillType());
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void HellFire::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType());
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

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel();
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

			int grade = 0;

			if ( input.SkillLevel <= 10 ) grade = 0;
			else if ( input.SkillLevel <= 20 ) grade = 1;
			else if ( input.SkillLevel < 30 ) grade = 2;
			else grade = 3;

			list<Creature*> cList;	// denier list
			
			for (int i=0; i<m_MaskNum[grade]; i++)
			{
				POINT& pt = m_HellFireMask[grade][i];

				int tileX = X+pt.x;
				int tileY = Y+pt.y;

				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);
					if ( tile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION) ) continue;
					if ( tile.getEffect(Effect::EFFECT_CLASS_HEAVEN_GROUND) ) continue;

					// 현재 타일에다 이펙트를 추가할 수 있다면...
					if (tile.canAddEffect())
					{
						// 같은 effect가 있으면 지운다.
						Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_HELLFIRE);
						if (pOldEffect != NULL)
						{
							ObjectID_t effectID = pOldEffect->getObjectID();
							pZone->deleteEffect(effectID);// fix me
						}

						// 이펙트 클래스를 생성한다.
						EffectHellFire* pEffect = new EffectHellFire(pZone , tileX, tileY);
						pEffect->setCasterName( pOusters->getName() );
						pEffect->setCasterID( pOusters->getObjectID() );
						pEffect->setDeadline(output.Duration);
						pEffect->setDuration(output.Range);
						pEffect->setDamage(output.ToHit);
						pEffect->setNextTime(0);
						pEffect->setTick(output.Tick);

						// Tile에 붙이는 Effect는 ObjectID를 등록받아야 한다.
						ObjectRegistry & objectregister = pZone->getObjectRegistry();
						objectregister.registerObject(pEffect);
						pZone->addEffect(pEffect);
						tile.addEffect(pEffect);

						const slist<Object*>& oList = tile.getObjectList();
						for(slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++) 
						{
							Object* pTarget = *itr;
							Creature* pTargetCreature = NULL;
							if ( pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE 
								&& ( (pTargetCreature = dynamic_cast<Creature*>(pTarget))->isSlayer() || pTargetCreature->isVampire() )
								&& checkZoneLevelToHitTarget( pTargetCreature ) && canAttack( pOusters, pTargetCreature )
							) 
							{
								GCModifyInformation gcMI;
								setDamage( pTargetCreature, output.Damage, pOusters, pOustersSkillSlot->getSkillType(), &gcMI, NULL, true, false );

								if (pTargetCreature->isDead())
								{
									int exp = computeCreatureExp(pTargetCreature, 70, pOusters);
									shareOustersExp(pOusters, exp, _GCSkillToTileOK1);
								}

								Player* pTargetPlayer = pTargetCreature->getPlayer();
								pTargetPlayer->sendPacket(&gcMI);

								cList.push_back(pTargetCreature);
								_GCSkillToTileOK2.addCListElement(pTargetCreature->getObjectID());
								_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
								_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

								pEffect->affect(pTargetCreature);
							}
//								pEffect->affect(pTarget);
						}
					}	
				}	
			}

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(grade);

			_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(output.Duration);
			_GCSkillToTileOK2.setRange(grade);
			//_GCSkillToTileOK2.addShortData(MODIFY_VISION, HELLFIRE_SIGHT);

			_GCSkillToTileOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(grade);
			_GCSkillToTileOK4.setDuration(output.Duration);

			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(grade);
			_GCSkillToTileOK5.setDuration(output.Duration);

			_GCSkillToTileOK6.setOrgXY(myX, myY);
			_GCSkillToTileOK6.setSkillType(SkillType);
			_GCSkillToTileOK6.setX(X);
			_GCSkillToTileOK6.setY(Y);
			_GCSkillToTileOK6.setDuration(output.Duration);
			_GCSkillToTileOK6.setRange(grade);
			//_GCSkillToTileOK6.addShortData(MODIFY_VISION, HELLFIRE_SIGHT);

			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				if (canSee(pTargetCreature, pOusters)) pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				else pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK6);
			}

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			cList.push_back(pOusters);

			list<Creature*> watcherList = pZone->getWatcherList(myX, myY, pOusters);

			// watcherList에서 cList에 속하지 않고, caster(pOusters)를 볼 수 없는 경우는
			// OK4를 보내고.. cList에 추가한다.
			for(list<Creature*>::const_iterator itr = watcherList.begin(); itr != watcherList.end(); itr++)
			{
				bool bBelong = false;
				for(list<Creature*>::const_iterator tItr = cList.begin(); tItr != cList.end(); tItr++)
					if (*itr == *tItr)
						bBelong = true;

				Creature* pWatcher = (*itr);
				if (bBelong == false && canSee(pWatcher, pOusters) == false)
				{
					//Assert(pWatcher->isPC());	// 당연 PC다.. Zone::getWatcherList는 PC만 return한다
					if (!pWatcher->isPC())
					{
						//cout << "HellFire : 왓처 리스트가 PC가 아닙니다." << endl;
//						GCSkillFailed1 _GCSkillFailed1;
//						_GCSkillFailed1.setSkillType(getSkillType());
//						pOusters->getPlayer()->sendPacket(&_GCSkillFailed1);

						//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
//						return;
						continue;
					}
					pWatcher->getPlayer()->sendPacket(&_GCSkillToTileOK4);
					cList.push_back(*itr);
				}
			}
					
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList, false);
			
			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

HellFire g_HellFire;
