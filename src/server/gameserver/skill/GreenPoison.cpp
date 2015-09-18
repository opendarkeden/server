//////////////////////////////////////////////////////////////////////////////
// Filename    : GreenPoison.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GreenPoison.h"
#include "EffectGreenPoison.h"
#include "RankBonus.h"

#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToTileOK6.h"
#include "GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenPoison::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

    try
    {
		Zone* pZone = pVampire->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수가 없다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack(pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		execute(pVampire, pTargetCreature->getX(), pTargetCreature->getY(), pVampireSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenPoison::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

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

		SkillType_t SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// Knowledge of Poison 이 있다면 hit bonus 10
		int HitBonus = 0;
		if (pVampire->hasRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_POISON ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_POISON);
			Assert(pRankBonus != NULL);

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

			Tile&   tile  = pZone->getTile(X, Y);
			Range_t Range = 1;	// 항상 1이다.
			
			// 같은 이펙트가 이미 존재한다면 삭제한다.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GREEN_POISON);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}
			
			// 데미지와 지속 시간을 계산한다.
			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 오브젝트를 생성한다.
			EffectGreenPoison* pEffect = new EffectGreenPoison(pZone, X, Y);
			pEffect->setUserObjectID(pVampire->getObjectID());
			pEffect->setDeadline(output.Duration);
			pEffect->setDuration(output.Duration);
			pEffect->setDamage(output.Damage);
			pEffect->setLevel(pSkillInfo->getLevel()/2);
			pEffect->setVampire();

			// 타일에 붙은 이펙트는 OID를 받아야 한다.
			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);
		
			// 존 및 타일에다가 이펙트를 추가한다.
			pZone->addEffect(pEffect);	
			tile.addEffect(pEffect);

			// 타일 위에 크리쳐가 있다면 바로 영향을 주도록 한다.
			bool bEffected = false;
			Creature* pTargetCreature = NULL;

			if (tile.hasCreature(Creature::MOVE_MODE_WALKING)) 
				pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

			ZoneCoord_t myX = pVampire->getX();
			ZoneCoord_t myY = pVampire->getY();

			// 모든 크리쳐가 독에 중독될 수 있게 하라는 기획안에 따라, 
			// 뱀파이어 및 몬스터도 독에 중독될 수 있도록 변경한다.
			// 하지만 이렇게 되면 몬스터가 쓰는 그린 포이즌에 의해서 다른 몬스터가 중독되는
			// 현상이 발생하게 되는데...
			//if (pTargetCreature != NULL && pTargetCreature->isSlayer())
			if (pTargetCreature != NULL )
			{
				if (pEffect->affectCreature(pTargetCreature, false) == true)
				{
					bEffected = true;

					if (pTargetCreature->isPC())
					{
						Player* pTargetPlayer = pTargetCreature->getPlayer();
						bool bCanSee = canSee(pTargetCreature, pVampire);

						if (bCanSee)
						{
							_GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
							_GCSkillToTileOK2.setSkillType(SkillType);
							_GCSkillToTileOK2.setX(X);
							_GCSkillToTileOK2.setY(Y);
							_GCSkillToTileOK2.setDuration(output.Duration);
							_GCSkillToTileOK2.setRange(Range);
							pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
						} 
						else 
						{
							_GCSkillToTileOK6.setOrgXY(myX, myY);
							_GCSkillToTileOK6.setSkillType(SkillType);
							_GCSkillToTileOK6.setX(X);
							_GCSkillToTileOK6.setY(Y);
							_GCSkillToTileOK6.setDuration(output.Duration);
							_GCSkillToTileOK6.setRange(Range);
							pTargetPlayer->sendPacket(&_GCSkillToTileOK6);
						}
					}
				}
			}

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(Range);
		
			_GCSkillToTileOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);
		
			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);

			if (bEffected) 
			{
				_GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
				_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
				_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());
			}
		
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pVampire);
			if (bEffected) cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenPoison::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	//Zone* pZone = pMonster->getZone();
	//Assert(pZone != NULL);
  	//int monsterCount = pZone->getMonsterCount();

	execute(pMonster, pEnemy->getX(), pEnemy->getY());
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenPoison::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin(monster) " << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "Monster cannot use skill while hiding." << endl;
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = SKILL_GREEN_POISON;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pMonster, pSkillInfo);

		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bRangeCheck && bHitRoll && bTileCheck)
		{
			Tile&   tile  = pZone->getTile(X, Y);
			Range_t Range = 1;	// 항상 1이다.
			
			// 같은 이펙트가 이미 존재한다면 삭제한다.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GREEN_POISON);
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
			EffectGreenPoison* pEffect = new EffectGreenPoison(pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setDuration(output.Duration);
			pEffect->setDamage(output.Damage);
			pEffect->setLevel(pSkillInfo->getLevel()/2);

			// 타일에 붙은 이펙트는 OID를 받아야 한다.
			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);
		
			// 존 및 타일에다가 이펙트를 추가한다.
			pZone->addEffect(pEffect);	
			tile.addEffect(pEffect);

			// 타일 위에 크리쳐가 있다면 바로 영향을 주도록 한다.
			bool bEffected = false;
			Creature* pTargetCreature = NULL;

			if (tile.hasCreature(Creature::MOVE_MODE_WALKING)) 
				pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

			ZoneCoord_t myX = pMonster->getX();
			ZoneCoord_t myY = pMonster->getY();

			// 모든 크리쳐가 독에 중독될 수 있게 하라는 기획안에 따라, 
			// 뱀파이어 및 몬스터도 독에 중독될 수 있도록 변경한다.
			// 하지만 이렇게 되면 몬스터가 쓰는 그린 포이즌에 의해서 다른 몬스터가 중독되는
			// 현상이 발생하게 되는데...
			//if (pTargetCreature != NULL && pTargetCreature->isSlayer())
			if (pTargetCreature != NULL)
			{
				if (pEffect->affectCreature(pTargetCreature, false) == true)
				{
					bEffected = true;

					if (pTargetCreature->isPC())
					{
						Player* pTargetPlayer = pTargetCreature->getPlayer();
						bool bCanSee = canSee(pTargetCreature, pMonster);

						if (bCanSee)
						{
							_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
							_GCSkillToTileOK2.setSkillType(SkillType);
							_GCSkillToTileOK2.setX(X);
							_GCSkillToTileOK2.setY(Y);
							_GCSkillToTileOK2.setDuration(output.Duration);
							_GCSkillToTileOK2.setRange(Range);
							pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
						} 
						else 
						{
							_GCSkillToTileOK6.setOrgXY(myX, myY);
							_GCSkillToTileOK6.setSkillType(SkillType);
							_GCSkillToTileOK6.setX(X);
							_GCSkillToTileOK6.setY(Y);
							_GCSkillToTileOK6.setDuration(output.Duration);
							_GCSkillToTileOK6.setRange(Range);
							pTargetPlayer->sendPacket(&_GCSkillToTileOK6);
						}
					}
				}
			}

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(Range);
		
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(Range);

			if (bEffected) 
			{
				_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
				_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());
			}
		
			list<Creature*> cList;
			cList.push_back(pMonster);
			if (bEffected) cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(monster) " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void GreenPoison::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin(monster) " << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = SKILL_GREEN_POISON;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t X = pMonster->getX();
		ZoneCoord_t Y = pMonster->getY();

		// 몬스터의 시체가 있는 타일와 그 주변 타일 중 랜덤으로 하나에 뿌린다.
		int dir = rand()%8;	
		list<POINT> ptList;
		ptList.push_back(POINT(X, Y));
		ptList.push_back(POINT((X + dirMoveMask[dir].x), (Y + dirMoveMask[dir].y)));

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		list<POINT>::iterator itr = ptList.begin();
		for (; itr != ptList.end(); itr++)
		{
			int tileX = (*itr).x;
			int tileY = (*itr).y;

			bool bTileCheck = false;
			if (rect.ptInRect(tileX, tileY))
			{
				Tile& tile = pZone->getTile(tileX, tileY);
				if (tile.canAddEffect()) bTileCheck = true;
			}

			if (bTileCheck)
			{
				Tile& tile = pZone->getTile(tileX, tileY);
				
				// 같은 이펙트가 이미 존재한다면 삭제한다.
				Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GREEN_POISON);
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
				EffectGreenPoison* pEffect = new EffectGreenPoison(pZone, tileX, tileY);
				pEffect->setDeadline(output.Duration);
				pEffect->setDuration(output.Duration);
				pEffect->setDamage(output.Damage);
				pEffect->setLevel(pSkillInfo->getLevel()/2);

				// 타일에 붙은 이펙트는 OID를 받아야 한다.
				ObjectRegistry & OR = pZone->getObjectRegistry();
				OR.registerObject(pEffect);
			
				// 존 및 타일에다가 이펙트를 추가한다.
				pZone->addEffect(pEffect);	
				tile.addEffect(pEffect);

				GCAddEffectToTile gcAddEffectToTile;
				gcAddEffectToTile.setEffectID(pEffect->getEffectClass());
				gcAddEffectToTile.setObjectID(pEffect->getObjectID());
				gcAddEffectToTile.setXY(tileX, tileY);
				gcAddEffectToTile.setDuration(output.Duration);

				// list에 POINT가 두개 들어가 있으므로, 두번 브로드캐스팅을 하게 된다. 
				// 이 부분은 패킷의 리스트를 함수의 인자로 받는 브로드캐스팅 
				// 함수를 만들어서 한번에 끝내는 것이 서버의 기능 향상에 도움이
				// 될 것이다.
				// 2002-01-23 김성민
				pZone->broadcastPacket(tileX, tileY, &gcAddEffectToTile);
			} 
		}
	}
	catch (Throwable & t) 
	{
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(monster) " << endl;

	__END_CATCH
}

GreenPoison g_GreenPoison;
