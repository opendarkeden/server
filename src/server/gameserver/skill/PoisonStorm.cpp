//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonStorm.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PoisonStorm.h"
#include "EffectPoisonStorm.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void PoisonStorm::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Vampire Object Assertion
	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

    try
    {
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
		    
			return;
		}

		execute(pVampire, pTargetCreature->getX(), pTargetCreature->getY(), pVampireSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void PoisonStorm::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	try
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = pVampireSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pVampire->getX();
		ZoneCoord_t myY = pVampire->getY();

		// Knowledge of Poison 이 있다면 hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_POISON ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_POISON );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());
		bool bHitRoll = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);

		bool bTileCheck = false;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if(rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

			// calculate damage and duration time
			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// Disruption Storm 이 있다면 데미지 20% 증가
			if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_DISRUPTION_STORM ) )
			{
				RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_DISRUPTION_STORM );
				Assert( pRankBonus != NULL );

				output.Damage += getPercentValue( output.Damage, pRankBonus->getPoint() );
			}

			Range_t Range = 3;

			// 기존에 같은 이펙트가 타일에 있다면 지우고 새로 설정한다.
			Tile& tile = pZone->getTile(X, Y);
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_POISON_STORM);
			if(pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 이펙트 오브젝트를 생성해서 타일에 붙인다. 
			EffectPoisonStorm* pEffect = new EffectPoisonStorm(pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(0);
			pEffect->setTick(output.Tick);
			pEffect->setDamage(output.Damage);
			pEffect->setUserObjectID( pVampire->getObjectID() );
			pEffect->setLevel(pSkillInfo->getLevel()/2);
			pEffect->setVampire();

			//
			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			//
			//
			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);


			// 이펙트 범위내의 모든 Creature에게 effect를 붙여준다.
			// Vampire가 기술을 사용한 경우 같은 Vampire에게는
			// 해당하지 않는다.
			bool bEffected = false;
			Creature* pTargetCreature;


			list<Creature*> cList;
			cList.push_back(pVampire);

			int oX, oY;
			int edge = 1;

			// Wide Storm 이 있다면 범위가 5*5 로 수정. skill type 을 수정한다.
			if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_WIDE_STORM ) )
			{
				RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_WIDE_STORM );
				Assert( pRankBonus != NULL );

				Range = pRankBonus->getPoint();
				edge = ( pRankBonus->getPoint() - 1 ) / 2;

				SkillType = SKILL_POISON_STORM_WIDE;
			}

			for(oX = -edge; oX <= edge; oX++)
			for(oY = -edge; oY <= edge; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				// 만약 이펙트를 추가하려는 곳이 Zone에 속해 있지 않다면 넘어간다.
				if(!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				// 해당 타일에 이펙트를 추가할 수 없다면 넘어간다.
				if(!tile.canAddEffect()) continue;

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
					pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL)
				{
					// 2003. 1. 10. Sequoia
					if( !checkZoneLevelToHitTarget( pTargetCreature ) ) continue;

					if(pTargetCreature->isSlayer()||pTargetCreature->isOusters())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							Player* pTargetPlayer = pTargetCreature->getPlayer();
							bEffected = true;

							bool bCanSee = canSee(pTargetCreature, pVampire);

							_GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

							cList.push_back(pTargetCreature);

							if (bCanSee)
							{
								// 공격을 당한 사람에게 
								_GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
								_GCSkillToTileOK2.setSkillType(SkillType);
								_GCSkillToTileOK2.setX(X);
								_GCSkillToTileOK2.setY(Y);
								_GCSkillToTileOK2.setDuration(output.Duration);
								_GCSkillToTileOK2.setRange(Range);
								pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
							}
						}
					}
					else if(pTargetCreature->isMonster())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							pMonster->addEnemy(pVampire);

							// 마지막 때린 애가 뱀파이어라고 설정한다. by sigi. 2002.6.21
							pMonster->setLastHitCreatureClass(Creature::CREATURE_CLASS_VAMPIRE);
						}
					}
				} // if(pTargetCreature!= NULL)
			}

			// 기술을 사용한 사람들에게
			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);
		
			// 기술을 쓴 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			// 기술을 당한 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//기술을 쓴 사람과 당한 사람을 모두 볼 수 있는 사람들에게
			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
			// 기술을 사용한 사람에게 packet 전달
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			// 기술을 쓸 사람과 당한 사람을 모두 볼 수 있는 사람들에게 broadcasing
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// 기술을 쓴 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// 기술을 당한 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

			// 기술 delay setting
			pVampireSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void PoisonStorm::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;
	try
	{
		Zone* pZone = pMonster->getZone();

		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType = SKILL_POISON_STORM;
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pMonster->getX();
		ZoneCoord_t myY = pMonster->getY();

		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());
		bool bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);

		bool bTileCheck = false;

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if(rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bRangeCheck && bHitRoll && bTileCheck)
		{
			// calculate damage and duration time
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			Range_t Range = 3;

			// 기존에 같은 이펙트가 타일에 있다면 지우고 새로 설정한다.
			Tile& tile = pZone->getTile(X, Y);
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_POISON_STORM);
			if(pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// 이펙트 오브젝트를 생성해서 타일에 붙인다. 
			EffectPoisonStorm* pEffect = new EffectPoisonStorm(pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setNextTime(0);
			pEffect->setTick(output.Tick);
			pEffect->setDamage(output.Damage);
			pEffect->setUserObjectID( pMonster->getObjectID() );
			pEffect->setLevel(pSkillInfo->getLevel()/2);

			//
			ObjectRegistry& objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			//
			//
			pZone->addEffect(pEffect);
			tile.addEffect(pEffect);


			// 이펙트 범위내의 모든 Creature에게 effect를 붙여준다.
			// Vampire가 기술을 사용한 경우 같은 Vampire에게는
			// 해당하지 않는다.
			bool bEffected = false;
			Creature* pTargetCreature;


			list<Creature*> cList;
			cList.push_back(pMonster);

			int oX, oY;

			for(oX = -1; oX <= 1; oX++)
			for(oY = -1; oY <= 1; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				if(!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				if(!tile.canAddEffect()) continue;

				pTargetCreature = NULL;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
					pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

				if(pTargetCreature != NULL
					&& pMonster->isEnemyToAttack( pTargetCreature ))
				{
					// 2003.1.10 by Sequoia
					if( !checkZoneLevelToHitTarget( pTargetCreature ) ) continue;

					if(pTargetCreature->isPC())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							Player* pTargetPlayer = pTargetCreature->getPlayer();
							bEffected = true;

							bool bCanSee = canSee(pTargetCreature, pMonster);

							_GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
							_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

							cList.push_back(pTargetCreature);

							if (bCanSee)
							{
								// 공격을 당한 사람에게 
								_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
								_GCSkillToTileOK2.setSkillType(SkillType);
								_GCSkillToTileOK2.setX(X);
								_GCSkillToTileOK2.setY(Y);
								_GCSkillToTileOK2.setDuration(output.Duration);
								_GCSkillToTileOK2.setRange(Range);
								pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
							}
						}
					}
					else if(pTargetCreature->isMonster())
					{
						if(pEffect->affectCreature(pTargetCreature, false) == true)
						{
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							pMonster->addEnemy(pMonster);
						}
					}
				} // if(pTargetCreature!= NULL)
			}

			// 기술을 쓴 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(myX);
			_GCSkillToTileOK3.setY(myY);

			// 기술을 당한 사람만 볼 수 있는 사람들에게
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);

			//기술을 쓴 사람과 당한 사람을 모두 볼 수 있는 사람들에게
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);
	
			// 기술을 쓸 사람과 당한 사람을 모두 볼 수 있는 사람들에게 broadcasing
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);
			
			// 기술을 쓴 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

			// 기술을 당한 사람을 볼 수 있는 사람들에게 broadcasting
			pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

		}
		else
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}
PoisonStorm g_PoisonStorm;
