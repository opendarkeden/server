//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyWall.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyWall.h"
#include "EffectBloodyWall.h"
#include "Creature.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillFailed1.h"

BloodyWall::BloodyWall()
	throw()
{
	// LEFT
	m_BloodyWallMask[0][0].set( 0, -2 );
	m_BloodyWallMask[0][1].set( 0, -1 );
	m_BloodyWallMask[0][2].set( 0, 0 );
	m_BloodyWallMask[0][3].set( 0, 1 );
	m_BloodyWallMask[0][4].set( 0, 2 );

	// LEFTDOWN
	m_BloodyWallMask[1][0].set( -1, -1 );
	m_BloodyWallMask[1][1].set( -1, 0 );
	m_BloodyWallMask[1][2].set( 0, 0 );
	m_BloodyWallMask[1][3].set( 0, 1 );
	m_BloodyWallMask[1][4].set( 1, 1 );

	// DOWN
	m_BloodyWallMask[2][0].set( -2, 0 );
	m_BloodyWallMask[2][1].set( -1, 0 );
	m_BloodyWallMask[2][2].set( 0, 0 );
	m_BloodyWallMask[2][3].set( 1, 0 );
	m_BloodyWallMask[2][4].set( 2, 0 );

	// RIGHTDOWN
	m_BloodyWallMask[3][4].set( 1, -1 );
	m_BloodyWallMask[3][4].set( 1, 0 );
	m_BloodyWallMask[3][4].set( 0, 0 );
	m_BloodyWallMask[3][4].set( 0, 1 );
	m_BloodyWallMask[3][4].set( -1, 1 );

	// RIGHT
	m_BloodyWallMask[4][0].set( 0, -2 );
	m_BloodyWallMask[4][1].set( 0, -1 );
	m_BloodyWallMask[4][2].set( 0, 0 );
	m_BloodyWallMask[4][3].set( 0, 1 );
	m_BloodyWallMask[4][4].set( 0, 2 );

	// RIGHTUP
	m_BloodyWallMask[5][0].set( -1, -1 );
	m_BloodyWallMask[5][1].set( 0, -1 );
	m_BloodyWallMask[5][2].set( 0, 0 );
	m_BloodyWallMask[5][3].set( 1, 0 );
	m_BloodyWallMask[5][4].set( 1, 1 );

	// UP
	m_BloodyWallMask[6][0].set( -2, 0 );
	m_BloodyWallMask[6][1].set( -1, 0 );
	m_BloodyWallMask[6][2].set( 0, 0 );
	m_BloodyWallMask[6][3].set( 1, 0 );
	m_BloodyWallMask[6][4].set( 2, 0 );

	// LEFTUP
	m_BloodyWallMask[7][0].set( -1, 1 );
	m_BloodyWallMask[7][1].set( -1, 0 );
	m_BloodyWallMask[7][2].set( 0, 0 );
	m_BloodyWallMask[7][3].set( 0, -1 );
	m_BloodyWallMask[7][4].set( 1, -1 );
};

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyWall::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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
			)
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}

		execute(pVampire, pTargetCreature->getX(), pTargetCreature->getY(), pVampireSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyWall::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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

		ZoneCoord_t myX = pVampire->getX();
		ZoneCoord_t myY = pVampire->getY();

		// Knowledge of Blood 가 있다면 hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);
		
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y)) bTileCheck = true;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

			// 이펙트의 지속시간을 계산한다.
			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			Dir_t 	   Dir		= getDirectionToPosition( myX, myY, X, Y );

			list<Creature*> cList;	// denier list
			
			for (int i=0; i<5; i++)
			{
				POINT& pt = m_BloodyWallMask[Dir][i];

				int tileX = X+pt.x;
				int tileY = Y+pt.y;

				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);
					if ( tile.getEffect( Effect::EFFECT_CLASS_TRYING_POSITION )!=NULL ) continue;
					if ( tile.getEffect( Effect::EFFECT_CLASS_HEAVEN_GROUND )!=NULL ) continue;

					// 현재 타일에다 이펙트를 추가할 수 있다면...
					if (tile.canAddEffect())
					{
						// 같은 effect가 있으면 지운다.
						Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_BLOODY_WALL);
						if (pOldEffect != NULL)
						{
							ObjectID_t effectID = pOldEffect->getObjectID();
							pZone->deleteEffect(effectID);// fix me
						}
					
						// 이펙트 클래스를 생성한다.
						EffectBloodyWall* pEffect = new EffectBloodyWall(pZone , tileX, tileY);
						pEffect->setCasterName( pVampire->getName() );
						pEffect->setCasterID( pVampire->getObjectID() );
						pEffect->setClan( Creature::CREATURE_CLASS_VAMPIRE, pVampire->getClanType() );
						pEffect->setDamage( output.Damage );
						pEffect->setDeadline(output.Duration);
						pEffect->setLevel(pVampire->getINT());
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
								&& ( (pTargetCreature = dynamic_cast<Creature*>(pTarget))->isSlayer() || pTargetCreature->isOusters() )
								&& !checkZoneLevelToHitTarget( pTargetCreature )
							) 
							{
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
			_GCSkillToTileOK1.setRange(Dir);

			_GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(output.Duration);
			_GCSkillToTileOK2.setRange(Dir);
			//_GCSkillToTileOK2.addShortData(MODIFY_VISION, BLOODY_WALL_SIGHT);

			_GCSkillToTileOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(Dir);
			_GCSkillToTileOK4.setDuration(output.Duration);

			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(Dir);
			_GCSkillToTileOK5.setDuration(output.Duration);

			_GCSkillToTileOK6.setOrgXY(myX, myY);
			_GCSkillToTileOK6.setSkillType(SkillType);
			_GCSkillToTileOK6.setX(X);
			_GCSkillToTileOK6.setY(Y);
			_GCSkillToTileOK6.setDuration(output.Duration);
			_GCSkillToTileOK6.setRange(Dir);
			//_GCSkillToTileOK6.addShortData(MODIFY_VISION, BLOODY_WALL_SIGHT);

			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				if (canSee(pTargetCreature, pVampire)) pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				else pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK6);
			}

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			cList.push_back(pVampire);

			list<Creature*> watcherList = pZone->getWatcherList(myX, myY, pVampire);

			// watcherList에서 cList에 속하지 않고, caster(pVampire)를 볼 수 없는 경우는
			// OK4를 보내고.. cList에 추가한다.
			for(list<Creature*>::const_iterator itr = watcherList.begin(); itr != watcherList.end(); itr++)
			{
				bool bBelong = false;
				for(list<Creature*>::const_iterator tItr = cList.begin(); tItr != cList.end(); tItr++)
					if (*itr == *tItr)
						bBelong = true;

				Creature* pWatcher = (*itr);
				if (bBelong == false && canSee(pWatcher, pVampire) == false)
				{
					//Assert(pWatcher->isPC());	// 당연 PC다.. Zone::getWatcherList는 PC만 return한다
					if (!pWatcher->isPC())
					{
						//cout << "BloodyWall : 왓처 리스트가 PC가 아닙니다." << endl;
						GCSkillFailed1 _GCSkillFailed1;
						_GCSkillFailed1.setSkillType(getSkillType());
						pVampire->getPlayer()->sendPacket(&_GCSkillFailed1);

						//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
						return;
					}
					pWatcher->getPlayer()->sendPacket(&_GCSkillToTileOK4);
					cList.push_back(*itr);
				}
			}
					
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList, false);
			
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void BloodyWall::execute(Monster* pMonster, Creature* pEnemy) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);
	execute(pMonster, pEnemy->getX(), pEnemy->getY());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyWall::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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

		SkillType_t SkillType  = SKILL_BLOODY_WALL;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX = pMonster->getX();
		ZoneCoord_t myY = pMonster->getY();

		// 마스터는 무조건~~
		bool bRangeCheck = pMonster->isMaster()
#ifdef __UNDERWORLD__
			|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
							|| verifyDistance(pMonster, X, Y, pSkillInfo->getRange());

		bool bHitRoll    = pMonster->isMaster() 
#ifdef __UNDERWORLD__
			|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
							|| HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y)) bTileCheck = true;

		if (bRangeCheck && bHitRoll && bTileCheck)
		{
			// 이펙트의 지속시간을 계산한다.
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			//Range_t    Range    = 3;
			Dir_t 	   Dir		= getDirectionToPosition( myX, myY, X, Y );

			list<Creature*> cList;	// denier list

			for (int i=0; i<5; i++)
			{
				POINT& pt = m_BloodyWallMask[Dir][i];

				int tileX = X+pt.x;
				int tileY = Y+pt.y;

				if (rect.ptInRect(tileX, tileY))
				{
					Tile& tile = pZone->getTile(tileX, tileY);
					if ( tile.getEffect( Effect::EFFECT_CLASS_HEAVEN_GROUND )!=NULL ) continue;
					// 현재 타일에다 이펙트를 추가할 수 있다면...
					if (tile.canAddEffect())
					{
						// 같은 effect가 있으면 지운다.
						Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_BLOODY_WALL);
						if (pOldEffect != NULL)
						{
							ObjectID_t effectID = pOldEffect->getObjectID();
							pZone->deleteEffect(effectID);// fix me
						}
					
						// 이펙트 클래스를 생성한다.
						EffectBloodyWall* pEffect = new EffectBloodyWall(pZone , tileX, tileY);
						pEffect->setCasterName( pMonster->getName() );
						pEffect->setCasterID( pMonster->getObjectID() );
						pEffect->setClan( Creature::CREATURE_CLASS_MONSTER, pMonster->getClanType() );
						pEffect->setDamage( output.Damage );
						pEffect->setDeadline(output.Duration);
						pEffect->setLevel(pMonster->getINT());
						pEffect->setNextTime(0);
						pEffect->setTick(output.Tick);

						// Tile에 붙이는 Effect는 ObjectID를 등록받아야 한다.
						ObjectRegistry & objectregister = pZone->getObjectRegistry();
						objectregister.registerObject(pEffect);

						pZone->addEffect(pEffect);
						tile.addEffect(pEffect);

						GCAddEffectToTile gcAE;
						gcAE.setObjectID( pEffect->getObjectID() );
						gcAE.setEffectID( pEffect->getSendEffectClass() );
						gcAE.setDuration( output.Duration );
						gcAE.setXY( tileX, tileY );
						pZone->broadcastPacket( tileX, tileY, &gcAE );

						const slist<Object*>& oList = tile.getObjectList();
						for(slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++) 
						{
							Object* pTarget = *itr;
							Creature* pTargetCreature = NULL;
							if (pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE 
								&& ( (pTargetCreature = dynamic_cast<Creature*>(pTarget))->isSlayer() || pTargetCreature->isOusters() )
							) 
							{
								cList.push_back(pTargetCreature);
								_GCSkillToTileOK2.addCListElement(pTargetCreature->getObjectID());
								_GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
								_GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());
								
								pEffect->affect(pTargetCreature);
							}

							//pEffect->affectObject(pTarget, false);
						}
					}	
				}	
			}

			_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setDuration(output.Duration);
			_GCSkillToTileOK2.setRange(Dir);
			//_GCSkillToTileOK2.addShortData(MODIFY_VISION, BLOODY_WALL_SIGHT);

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(Dir);
			_GCSkillToTileOK4.setDuration(output.Duration);

			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(Dir);
			_GCSkillToTileOK5.setDuration(output.Duration);

			_GCSkillToTileOK6.setOrgXY(myX, myY);
			_GCSkillToTileOK6.setSkillType(SkillType);
			_GCSkillToTileOK6.setX(X);
			_GCSkillToTileOK6.setY(Y);
			_GCSkillToTileOK6.setDuration(output.Duration);
			_GCSkillToTileOK6.setRange(Dir);
			//_GCSkillToTileOK6.addShortData(MODIFY_VISION, BLOODY_WALL_SIGHT);

			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				if (canSee(pTargetCreature, pMonster)) pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				else pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK6);
			}

			cList.push_back(pMonster);

			list<Creature*> watcherList = pZone->getWatcherList(myX, myY, pMonster);

			// watcherList에서 cList에 속하지 않고, caster(pMonster)를 볼 수 없는 경우는
			// OK4를 보내고.. cList에 추가한다.
			for(list<Creature*>::const_iterator itr = watcherList.begin(); itr != watcherList.end(); itr++)
			{
				bool bBelong = false;
				for(list<Creature*>::const_iterator tItr = cList.begin(); tItr != cList.end(); tItr++)
					if (*itr == *tItr)
						bBelong = true;

				Creature* pWatcher = (*itr);
				if (bBelong == false && canSee(pWatcher, pMonster) == false)
				{
					//Assert(pWatcher->isPC());	// 당연 PC다.. Zone::getWatcherList는 PC만 return한다
					if (!pWatcher->isPC())
					{
						//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
						return;
					}

					pWatcher->getPlayer()->sendPacket(&_GCSkillToTileOK4);
					cList.push_back(*itr);
				}
			}
					
			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList, false);
			
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

BloodyWall g_BloodyWall;
