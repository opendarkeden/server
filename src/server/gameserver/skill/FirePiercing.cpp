//////////////////////////////////////////////////////////////////////////////
// Filename    : FirePiercing.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "FirePiercing.h"
#include "ZoneUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void FirePiercing::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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


		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pOusters, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void FirePiercing::execute(Ousters* pOusters, ZoneCoord_t tX, ZoneCoord_t tY, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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

		Dir_t dir = computeDirection( pOusters->getX(), pOusters->getY(), tX, tY );
		int X = (int)pOusters->getX() + dirMoveMask[dir].x * 2;
		int Y = (int)pOusters->getY() + dirMoveMask[dir].y * 2;

		if ( X<0 || Y<0 || !isValidZoneCoord( pZone, X, Y ) )
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL, Grade);
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

		// 데미지와 지속 시간을 계산한다.
		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bSatisfyRequire)
		{
			list<Creature*> cList;

			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

			int oX, oY;

			_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK2.setSkillType( SKILL_FIRE_PIERCING );
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setGrade(Grade);

			Damage_t Damage = output.Damage;

			bool bCritical = false;
			computeCriticalBonus(pOusters, getSkillType(), Damage, bCritical);

			for ( oX = (int)X - 1 ; oX <= (int)X + 1 ; ++oX )
			for ( oY = (int)Y - 1 ; oY <= (int)Y + 1 ; ++oY )
			{
				if (!isValidZoneCoord( pZone, oX, oY )) continue;

				Tile&   tile  = pZone->getTile(oX, oY);

				// 타일 안에 존재하는 오브젝트들을 검색한다.
				const slist<Object*>& oList = tile.getObjectList();
				slist<Object*>::const_iterator itr = oList.begin();
				for (; itr != oList.end(); itr++) 
				{
					Assert(*itr != NULL);

					Object* pObject = *itr;
					Assert(pObject != NULL);

					if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pCreature = dynamic_cast<Creature*>(pObject);
						Assert(pCreature != NULL);

						// 무적상태 체크. by sigi. 2002.9.5
						// 산 면역. by sigi. 2002.9.13
						if ( pCreature->getObjectID() == pOusters->getObjectID()
							|| !canAttack( pOusters, pCreature )
							|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
							|| !canHit( pOusters, pCreature, SKILL_FIRE_PIERCING, pOustersSkillSlot->getExpLevel() )
							)
						{
							continue;
						}

						// 2003.1.10 by Sequoia
						// 안전지대 체크
						if( !checkZoneLevelToHitTarget( pCreature ) ) continue;

						if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
						{
							if (pCreature->isSlayer()) 
							{
								Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

								::setDamage( pSlayer, Damage, pOusters, SKILL_FIRE_PIERCING, &_GCSkillToTileOK2, &_GCSkillToTileOK1 );

								Player* pPlayer = pSlayer->getPlayer();
								Assert(pPlayer != NULL);
								pPlayer->sendPacket(&_GCSkillToTileOK2);
							} 
							else if (pCreature->isVampire())
							{
								Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

								::setDamage( pVampire, Damage, pOusters, SKILL_FIRE_PIERCING, &_GCSkillToTileOK2, &_GCSkillToTileOK1 );

								Player* pPlayer = pVampire->getPlayer();
								Assert(pPlayer != NULL);
								pPlayer->sendPacket(&_GCSkillToTileOK2);
							}
							else if (pCreature->isMonster())
							{
								Monster* pMonster = dynamic_cast<Monster*>(pCreature);
							
								::setDamage( pMonster, Damage, pOusters, SKILL_FIRE_PIERCING, NULL, &_GCSkillToTileOK1 );
							}
							else continue; // 아우스터즈나 NPC 상대로... -_-

							// 죽었으면 경험치준다. 음.....
							if ( pOusters != NULL )
							{
								if (pCreature->isDead() && pOusters->isOusters())
								{
									Ousters* pCastOusters = dynamic_cast<Ousters*>( pOusters );
									Assert( pCastOusters != NULL );

//									int exp = computeCreatureExp(pCreature, 100, pCastOusters);
									int exp = computeCreatureExp(pCreature, 70, pCastOusters);
									shareOustersExp(pCastOusters, exp, _GCSkillToTileOK1);
								}
							}

							cList.push_back( pCreature );
							if ( pCreature->isPC() )
							{
								pCreature->getPlayer()->sendPacket( &_GCSkillToTileOK2 );
							}

							_GCSkillToTileOK2.clearList();

//							if ( _GCSkillToTileOK1.getShortCount() != 0 || _GCSkillToTileOK1.getLongCount() != 0 ) pOusters->getPlayer()->sendPacket(&_GCSkillToTileOK1);
						}
					}
				}
			}

			if ( bCritical )
			{
				cout << "크리티컬 발동" << endl;

				list<Creature*>::iterator itr = cList.begin();
				list<Creature*>::iterator endItr = cList.end();

				for ( ; itr != endItr ; ++itr )
				{
					Creature* pTargetCreature = *itr;
					if ( pTargetCreature != NULL )
					{
						cout << pTargetCreature->getName() << " 낙백~" << endl;
						knockbackCreature( pZone, pTargetCreature, pOusters->getX(), pOusters->getY() );
					}
				}
			}

			ZoneCoord_t myX = pOusters->getX();
			ZoneCoord_t myY = pOusters->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setGrade(Grade);
		
			_GCSkillToTileOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			_GCSkillToTileOK3.setGrade(Grade);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setGrade(Grade);
		
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setGrade(Grade);

			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			cList.push_back(pOusters);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

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
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

FirePiercing g_FirePiercing;
