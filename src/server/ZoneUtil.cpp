//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneUtil.cpp
// Written by  : excel96
// Description : 
// 존과 관련된 특정한 작업들을 수행하는 함수들을 존 안에 넣으니까,
// 존 파일이 너무 커지는 경향이 있어서, 존 파일 외부로 꺼낸 함수들이다.
//////////////////////////////////////////////////////////////////////////////

#include "ZoneUtil.h"
#include "Assert.h"
#include "DB.h"
#include "Properties.h"
#include "Item.h"
#include "Relic.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Corpse.h"
#include "Effect.h"
#include "GamePlayer.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZonePlayerManager.h"
#include "IncomingPlayerManager.h"
#include "PacketUtil.h"
#include "CreatureUtil.h"
#include "MonsterManager.h"
#include "ResurrectLocationManager.h"
#include "EffectObservingEye.h"
#include "EffectGnomesWhisper.h"
#include "MonsterSummonInfo.h"
#include "MasterLairManager.h"
#include "VariableManager.h"
#include "EventTransport.h"
#include "MonsterCorpse.h"
#include "RelicUtil.h"
#include "ZoneUtil.h"
#include "CastleInfoManager.h"
#include "TimeManager.h"
#include "EffectPrecedence.h"
#include "EffectManager.h"
#include "StringPool.h"
#include "PKZoneInfoManager.h"
#include "VisionInfo.h"
#include "LevelWarZoneInfoManager.h"
#include "EffectDarknessForbidden.h"

#include "ctf/FlagManager.h"

#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCAddBurrowingCreature.h"
#include "Gpackets/GCAddVampireFromTransformation.h"
#include "Gpackets/GCAddMonsterFromTransformation.h"
#include "Gpackets/GCUntransformOK.h"
#include "Gpackets/GCUntransformFail.h"
#include "Gpackets/GCAddVampireFromBurrowing.h"
#include "Gpackets/GCAddMonsterFromBurrowing.h"
#include "Gpackets/GCMineExplosionOK1.h"
#include "Gpackets/GCMineExplosionOK2.h"
#include "Gpackets/GCAddInstalledMineToZone.h"
#include "Gpackets/GCFastMove.h"
#include "Gpackets/GCMove.h"
#include "Gpackets/GCMoveOK.h"
#include "Gpackets/GCMoveError.h"
#include "Gpackets/GCAddMonster.h"
#include "Gpackets/GCAddNewItemToZone.h"
#include "Gpackets/GCDropItemToZone.h"
#include "Gpackets/GCAddNPC.h"
#include "Gpackets/GCAddSlayer.h"
#include "Gpackets/GCAddVampire.h"
#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GCSetPosition.h"
#include "Gpackets/GCUnburrowOK.h"
#include "Gpackets/GCUnburrowFail.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "Gpackets/GCGetOffMotorCycle.h"

#include "item/Mine.h"
#include "skill/EffectTrapInstalled.h"
#include "skill/SummonGroundElemental.h"

#include "SkillUtil.h"
#include "SkillHandler.h"
#include "war/WarSystem.h"
#include "GameServerInfoManager.h"
//#include "skill/EffectRevealer.h"

string correctString( const string& str )
{
    __BEGIN_TRY

    string correct = str;

    unsigned int i = 0;
    unsigned int size = str.size();

    while( i < size )
    {
        if ( correct[i] == '\\' )
        {
            correct.replace( i, 1, "\\\\" );
            i = i + 2;
            size++;
        }
        else if ( correct[i] == '\'' )
        {
            correct.replace( i, 1, "\\'" );
            i = i + 2;
            size++;
        }
        else
        {
            i++;
        }
    }

    return correct;

    __END_CATCH

}


//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐를 더할 수 있는 위치를 찾는다.
// 
// Zone*       pZone        : 존에 대한 포인터
// ZoneCoord_t cx           : 더하고자 하는 초기 위치 x
// ZoneCoord_t cy           : 더하고자 하는 초기 위치 y
// Creature::MoveMode MMode : 크리쳐의 무브 모드
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePosition(Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, Creature::MoveMode MMode) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	int    x          = cx;
	int    y          = cy;
	int    sx         = 1;
	int    sy         = 0;
	int    maxCount   = 1;
	int    count      = 1;
	int    checkCount = 300;
	TPOINT pt; 

	do
	{
		if (x > 0 && y > 0 && x < pZone->getWidth() && y < pZone->getHeight()) 
		{
			Tile& rTile = pZone->getTile(x, y);
			/*
			if (rTile.isBlocked(MMode) == false && rTile.hasPortal() == false)
			{
				pt.x = x;
				pt.y = y;
				return pt;
			}
			*/
			if (rTile.isBlocked(MMode) == false && rTile.hasPortal() == false)
			{
				pt.x = x;
				pt.y = y;
				return pt;
			}

			/*
			if (rTile.isBlocked(MMode))
			{
				cout << "[" << checkCount << "] Block : (" << x << ", " << y << ")" << endl;
			}

			if (rTile.hasPortal())
			{
				cout << "[" << checkCount << "] Portal : (" << x << ", " << y << ")" << endl;
			}
			*/
		}

		x += sx;
		y += sy;

		if (--count==0)
		{
			if (sx==0) maxCount++;

			int temp = sx;
			sx = -sy;
			sy = temp;

			count = maxCount;
		}

	} while (--checkCount);

	pt.x = -1;
	pt.y = -1;
	return pt;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 특정 아이템을 더할 수 있는 위치를 찾는다.
//
// Zone*       pZone          : 존에 대한 포인터
// ZoneCoord_t cx             : 더하고자 하는 초기 위치 x
// ZoneCoord_t cy             : 더하고자 하는 초기 위치 y
// bool        bAllowCreature : 크리쳐가 존재하는 곳도 괜찮은가?
// bool        bAllowSafeZone : Safe Zone 도 괜찮은가?
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePositionForItem(Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature, bool bAllowSafeZone, bool bForce ) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	int    x          = cx;
	int    y          = cy;
	int    sx         = 1;
	int    sy         = 0;
	int    maxCount   = 1;
	int    count      = 1;
	int    checkCount = 300;
	TPOINT pt; 

	do
	{
		// 화면의 경계선에 아이템이 들어가는 것을 방지하기 위하여
		// 일정 옵셋을 주고 떨어뜨릴 수 있는지 체크를 한다.
		if (x > 2 && y > 2 && x < pZone->getWidth()-2 && y < pZone->getHeight()-2) 
		{
			Tile& rTile = pZone->getTile(x, y);

			// GroundBlock이 아니거나 (Block이더라도)지상 캐릭터가 있는 경우 by sigi
			if ((!rTile.isGroundBlocked() || rTile.hasWalkingCreature())
				&& rTile.hasItem() == false && rTile.hasPortal() == false)	
			{
				// Safe 존에 떨어뜨리면 안되는 아이템인 경우 체크
				if ( bAllowSafeZone || !(pZone->getZoneLevel( x, y ) & SAFE_ZONE) )
				{
					pt.x = x;
					pt.y = y;
					return pt;
				}
				// 모터사이클을 생성할 때, NPC 밑에 모터사이클이 생성되어서
				// 플레이어가 모터사이클을 클릭하지 못하는 경우가 있다.
				// 이 문제를 해결하기 위해, 타일에 크리쳐가 존재하는지 체크
				// 이거든 저거든 무조건 통과네...이상한 코드네.. 2003.03.12 by bezz
//				if (bAllowCreature == false && rTile.hasCreature() == false)
//				{
//					pt.x = x;
//					pt.y = y;
//					return pt;
//				}
//				else
//				{
//					pt.x = x;
//					pt.y = y;
//					return pt;
//				}
			}

			if ( bForce && rTile.hasItem() )
			{
				Item* pTileItem = rTile.getItem();

				if ( pTileItem != NULL )
				{
					if ( pTileItem->getItemClass()!=Item::ITEM_CLASS_CORPSE )
					{
						pZone->deleteItem( pTileItem, x, y );
						pTileItem->destroy();
						SAFE_DELETE(pTileItem);

						pt.x = x;
						pt.y = y;
						return pt;
					}
				}
			}
		}

		x += sx;
		y += sy;

		if (--count==0)
		{
			if (sx==0) maxCount++;

			int temp = sx;
			sx = -sy;
			sy = temp;

			count = maxCount;
		}

	} while (--checkCount);

	pt.x = -1;
	pt.y = -1;
	return pt;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 특정 이펙트를 더할 수 있는 위치를 찾는다.
//
// Zone*       pZone          : 존에 대한 포인터
// ZoneCoord_t cx             : 더하고자 하는 초기 위치 x
// ZoneCoord_t cy             : 더하고자 하는 초기 위치 y
// Effect::EffectClass EClass : 더하고자 하는 이펙트 클래스
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePositionForEffect(Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, Effect::EffectClass EClass) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	int    x          = cx;
	int    y          = cy;
	int    sx         = 1;
	int    sy         = 0;
	int    maxCount   = 1;
	int    count      = 1;
	int    checkCount = 300;
	TPOINT pt; 

	do
	{
		if (x > 0 && y > 0 && x < pZone->getWidth() && y < pZone->getHeight()) 
		{
			Tile& rTile = pZone->getTile(x, y);
			// 이펙트를 더할 수 있는 타일이어야 하고, 같은 종류의 이펙트 또한 없어야 한다.
			if (rTile.canAddEffect() && rTile.getEffect(EClass) == NULL)
			{
				bool bNearTileCheck = true;

				// 주위 8타일에 같은 이펙트가 없어야 한다.
				for (int i=0; i<8; i++)
				{
					int tileX = x + dirMoveMask[i].x;
					int tileY = y + dirMoveMask[i].y;

					if (pZone->getOuterRect()->ptInRect(tileX, tileY))
					{
						Tile& rTile2 = pZone->getTile(tileX, tileY);
						if (rTile2.getEffect(EClass) != NULL)
						{
							bNearTileCheck = false;
							break;
						}
					}
				}

				if (bNearTileCheck)
				{
					pt.x = x;
					pt.y = y;
					return pt;
				}
			}
		}

		x += sx;
		y += sy;

		if (--count == 0)
		{
			if (sx == 0) maxCount++;

			int temp = sx;
			sx = -sy;
			sy = temp;

			count = maxCount;
		}

	} while (--checkCount);

	pt.x = -1;
	pt.y = -1;

	return pt;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 특정 위치에서 지정된 무브모드의 크리쳐를 추가할 수 있는지 검사한다.
//
// Zone*              pZone : 존에 대한 포인터
// ZoneCoord_t        x     : 변신하고자 하는 좌표 x
// ZoneCoord_t        y     : 변신하고자 하는 좌표 y
// Creature::MoveMode MMode : 크리쳐의 무브 모드
//////////////////////////////////////////////////////////////////////////////
bool canAddCreature(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature::MoveMode MMode) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	if (x > 0 && y > 0 && 
		x < pZone->getWidth() && y < pZone->getHeight())
	{
		if (!pZone->getTile(x,y).isBlocked(MMode))
		{
			return true;
		}
	}

	return false;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 특정 위치에 버로우가 가능한지 체크를 한다. 
//
// Zone*       pZone : 존에 대한 포인터
// ZoneCoord_t x     : 버로우하고자 하는 좌표 x
// ZoneCoord_t y     : 버로우하고자 하는 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool canBurrow(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	return canAddCreature(pZone, x, y, Creature::MOVE_MODE_BURROWING);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 특정 위치에 언버로우가 가능한지 체크를 한다.
//
// Zone*       pZone : 존에 대한 포인터
// ZoneCoord_t x     : 버로우하고자 하는 좌표 x
// ZoneCoord_t y     : 버로우하고자 하는 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool canUnburrow(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	return canAddCreature(pZone, x, y, Creature::MOVE_MODE_WALKING);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 크리쳐를 뒤로 물러나게 한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 물러나게 할 크리쳐
// ZoneCoord_t originX   : pCreature를 물러나게 한 상대방의 좌표 x
// ZoneCoord_t originY   : pCreature를 물러나게 한 상대방의 좌표 y
//////////////////////////////////////////////////////////////////////////////
Dir_t knockbackCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t originX, ZoneCoord_t originY)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	if (pCreature->isDead() 
		|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
		|| pCreature->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE)
		|| pCreature->isFlag(Effect::EFFECT_CLASS_INSTALL_TURRET)
		)
	{
		return UP;
	}

	if ( pCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		if ( pMonster != NULL && pMonster->getMonsterType() == GROUND_ELEMENTAL_TYPE ) return UP;
//		if ( pMonster->getMonsterType() == 722 ) return UP;
		switch ( pMonster->getMonsterType() )
		{
			case 722:
			case 723:
			case 717:
			case 721:
			case 724:
			case 725:
			case 726:
			case 727:
			case 728:
			case 729:
			case 734:
			case 735:
			case 736:
			case 737:
			case 764:
			case 765:
				return UP;
			default:
				break;
		}

//		if ( pMonster->hasRelic() || pMonster->getBrain() == NULL ) return UP;
	}

	// 크리쳐가 물러날 좌표 및 방향을 계산한다.
	ZoneCoord_t nx     = pCreature->getX();
	ZoneCoord_t ny     = pCreature->getY();
	ZoneCoord_t cx     = nx;
	ZoneCoord_t cy     = ny;
	ZoneCoord_t height = pZone->getHeight();
	ZoneCoord_t width  = pZone->getWidth();
	Dir_t       dir    = calcDirection(originX, originY, nx, ny);

	Tile& rOriginTile = pZone->getTile(cx, cy);
	if ( rOriginTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION) != NULL ) return UP;

	// 물러날 좌표를 꼐산한다.
	switch (dir)
	{
		case UP:        if (                    ny > 0         ) {          ny -= 1; } break;
		case DOWN:      if (                    ny < (height-1)) {          ny += 1; } break;
		case LEFT:      if (nx > 0                             ) { nx -= 1;          } break;
		case RIGHT:     if (nx < (width - 1)                   ) { nx += 1;          } break;
		case LEFTUP:    if (nx > 0           && ny > 0         ) { nx -= 1; ny -= 1; } break;
		case RIGHTUP:   if (nx < (width - 1) && ny > 0         ) { nx += 1; ny -= 1; } break;
		case LEFTDOWN:  if (nx > 0           && ny < (height-1)) { nx -= 1; ny += 1; } break;
		case RIGHTDOWN: if (nx < (width - 1) && ny < (height-1)) { nx += 1; ny += 1; } break;
	}

	// 관 속에 있는 상태가 아니어야 하고
	// 도착지점은 비어 있어야하고, 크리쳐 역시 움직일 수 있는 상태여야 한다.
	Tile& rTargetTile = pZone->getTile(nx, ny);
	if (!pCreature->isFlag(Effect::EFFECT_CLASS_CASKET) &&
		!rTargetTile.isBlocked(pCreature->getMoveMode()) &&
		!pCreature->isFlag(Effect::EFFECT_CLASS_HIDE) && !rTargetTile.hasPortal())
	{
		pCreature->setX(nx);
		pCreature->setY(ny);

		try
		{
			// 이전 타일에서 크리쳐를 삭제한다.
			rOriginTile.deleteCreature(pCreature->getObjectID());

			// 새 타일에 크리쳐를 추가한다.
			if (!rTargetTile.addCreature(pCreature))
			{
				// Portal을 activate시킨 경우이다. by sigi. 2002.5.6
				return dir;
			}

			// 지뢰를 체크한다.
			try {
				checkMine(pZone, pCreature, nx, ny);
				checkTrap(pZone, pCreature);
			} catch ( Throwable & t ) {
				filelog("CheckMineBug.txt", "%s : %s", "KnockBackCreature", t.toString().c_str());
			}

			// GCMove/GCAddSlayer/GCAddVampire를 브로드캐스트.
			if (pCreature->isPC())
			{
				pZone->movePCBroadcast(pCreature, cx, cy, nx, ny, false, true);
			}
			else
			{
				pZone->moveCreatureBroadcast(pCreature, cx, cy, nx, ny, false, true);
			}
		}
		catch (NoSuchElementException& nsee)
		{
			throw Error("No creature on previous tile");
		}
		catch (DuplicatedException& de)
		{
			throw Error("Thers's a creature on new tile");
		}
		catch (PortalException&)
		{
			// 흐흐.. goto 다.
		}
		catch (Error& e)
		{
			filelog("assertTile.txt", "knockbackCreature : %s", e.toString().c_str());
			throw;
		}
	}

	return dir;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 하이드를 쓴 크리쳐를 존에다 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 하이드를 쓴 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addBurrowingCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy) 
	throw (EmptyTileNotExistException, Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);
	Assert(pCreature->isVampire() || pCreature->isMonster());

	TPOINT pt = findSuitablePosition(pZone, cx, cy, Creature::MOVE_MODE_BURROWING);

	if (pt.x != -1)
	{
		pCreature->setFlag(Effect::EFFECT_CLASS_HIDE);
		Assert(pCreature->getMoveMode() == Creature::MOVE_MODE_WALKING);

		Tile& oldTile = pZone->getTile(pCreature->getX(), pCreature->getY());
		Tile& newTile = pZone->getTile(pt.x, pt.y);

		try {
			oldTile.deleteCreature(pCreature->getObjectID());
		} catch (Error& e) {
			filelog("assertTile.txt", "addBurrowingCreature : %s", e.toString().c_str());
			throw;
		}

		pCreature->setMoveMode(Creature::MOVE_MODE_BURROWING);
		newTile.addCreature(pCreature);

		Assert(pCreature == newTile.getCreature(pCreature->getMoveMode()));

		// 크리쳐의 좌표를 변경한다.
		pCreature->setXYDir(pt.x, pt.y, pCreature->getDir());

		//scanPC(pCreature);
		//GCDeleteObject gcDO;		// 잠시 넣었던거.. 다시 없앴다. by sigi
		//gcDO.setObjectID(pCreature->getObjectID()); 

		// 주변의 PC들에게 알릴 GCAddBurrowingCreature
		GCAddBurrowingCreature gcABC;
		gcABC.setObjectID(pCreature->getObjectID());
		gcABC.setName(pCreature->getName());
		gcABC.setX(pt.x);
		gcABC.setY(pt.y);

		//--------------------------------------------------------------------------------
		//
		// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
		// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
		//
		//--------------------------------------------------------------------------------
		// 잠시 넣었던거 다시 없앴다. by sigi
		/*
		for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(pZone->getWidth() - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix ++) 
		{
			for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(pZone->getHeight() - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy ++) 
			{
				Tile& curTile = pZone->getTile(ix, iy);
				const slist<Object*> & objectList = curTile.getObjectList();

				slist<Object*>::const_iterator itr = objectList.begin();
				for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr ++) 
				{
					Assert(*itr != NULL);
					Creature* pViewer= dynamic_cast<Creature*>(*itr);

					if (pViewer != pCreature && pViewer->isPC() && 
						(pViewer->getVisionState(cx, cy) >= IN_SIGHT)) 
					{
						if (pViewer->isSlayer() && !pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN))
						{
							// slayer이고 detect_hidden도 없으면 GCDeleteObject
							pViewer->getPlayer()->sendPacket(&gcDO);
						}
						else
						{
							// vampire이거나.. detect_hidden이 있다면 GCAddBurrowingCreature
							pViewer->getPlayer()->sendPacket(&gcABC);
						}
					}//if
				}//for
			}//for
		}//for
		*/


		// broadcastPacket내부에서 볼수 있는지를 처리하더라..
		pZone->broadcastPacket(pt.x, pt.y, &gcABC, pCreature);
	} 
	else throw EmptyTileNotExistException("addBurrowingCreature() : Tile is not empty.");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 하이드를 푼 크리쳐를 존에다 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 하이드를 푼 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
// Dir_t       dir       : 나온 크리쳐가 향할 방향
//////////////////////////////////////////////////////////////////////////////
void addUnburrowCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) 
	throw (EmptyTileNotExistException, Error)
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);
	Assert(pCreature->isFlag(Effect::EFFECT_CLASS_HIDE));

	TPOINT pt = findSuitablePosition(pZone, cx, cy, Creature::MOVE_MODE_WALKING);

	if (pt.x != -1) 
	{
		ZoneCoord_t oldX    = pCreature->getX();
		ZoneCoord_t oldY    = pCreature->getY();
		Tile&       oldTile = pZone->getTile(oldX, oldY);
		Tile&       newTile = pZone->getTile(pt.x, pt.y);

		// 이전 위치에서 숨었는데도 볼 수 있는 놈은 Delete object를 보낸다.
		GCDeleteObject gcDO;
		gcDO.setObjectID(pCreature->getObjectID());
		pZone->broadcastPacket(oldX, oldY, &gcDO, pCreature); 

		// DeleteObject packet을 보낸후 set.
		pCreature->removeFlag(Effect::EFFECT_CLASS_HIDE);	

		// 옛날 타일에서 크리쳐를 지우고, 
		// 새 타일에 무브모드를 바꿔서 추가한다.
		try {
			oldTile.deleteCreature(pCreature->getObjectID());
		} catch (Error& e) {
			filelog("assertTile.txt", "addUnburrowCreature : %s", e.toString().c_str());
			throw;
		}
		pCreature->setMoveMode(Creature::MOVE_MODE_WALKING);
		newTile.addCreature(pCreature);

		Assert(pCreature == newTile.getCreature(pCreature->getMoveMode()));

		// 크리처의 좌표를 지정한다.
		pCreature->setXYDir(pt.x, pt.y, dir);
		
		//scanPC(pCreature);

		Creature::CreatureClass CClass = pCreature->getCreatureClass();
		if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
		{
			// 주변의 PC들에게 뱀파이어를 추가하도록 한다.
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			GCAddVampireFromBurrowing gcAVFB(pVampire->getVampireInfo3());
			gcAVFB.setEffectInfo(pVampire->getEffectInfo());
			pZone->broadcastPacket(pt.x, pt.y, &gcAVFB, pCreature);

			// 땅에서 잘 나왔다고, 본인에게 보내준다.
			GCUnburrowOK gcUnburrowOK(pt.x, pt.y, dir);
			Player* pPlayer = pCreature->getPlayer();
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
			pGamePlayer->sendPacket(&gcUnburrowOK);
		}
		else if (CClass == Creature::CREATURE_CLASS_MONSTER)
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			GCAddMonsterFromBurrowing gcAMFB;
			gcAMFB.setObjectID(pMonster->getObjectID());
			gcAMFB.setMonsterType(pMonster->getMonsterType());
			gcAMFB.setMonsterName(pMonster->getMonsterName());
			gcAMFB.setX(pt.x);
			gcAMFB.setY(pt.y);
			gcAMFB.setDir(dir);
			gcAMFB.setEffectInfo(pMonster->getEffectInfo());
			gcAMFB.setCurrentHP(pMonster->getHP());
			gcAMFB.setMaxHP(pMonster->getHP(ATTR_MAX));

			pZone->broadcastPacket(pt.x, pt.y, &gcAMFB);
		}
		else
		{
			throw Error("invalid creature type");
		}
	} 
	else 
	{
		// 적당한 자리를 찾지 못해, 
		// 땅에서 나오지 못했다고 본인에게 보내준다.
		if (pCreature->isPC())
		{
			GCUnburrowFail gcUnburrowFail;
			pCreature->getPlayer()->sendPacket(&gcUnburrowFail);
		}
		else
		{
			cerr << "addUnburrowCreature() : Cannot find suitable position" << endl;
			throw Error("Cannot unburrow monster.");
		}	
	}

	__END_CATCH
}
   

//////////////////////////////////////////////////////////////////////////////
// 변신을 푼 크리쳐를 존에다 추가한다.
//
// Zone*     pZone     : 존에 대한 포인터
// Creature* pCreature : 변신을 푼 크리쳐
// bool      bForce    : 이펙트의 duration이 만기가 되지 않았는데,
//                       강제로 푸는 것인가?
//////////////////////////////////////////////////////////////////////////////
void addUntransformCreature(Zone* pZone, Creature* pCreature, bool bForce) throw()
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	// 현재 변신 상태가 맞는지 체크를 한다.
	Assert(pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF) || 
           pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT) ||
		   pCreature->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH) ||
		   pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF));

	ZoneCoord_t cx = pCreature->getX();
	ZoneCoord_t cy = pCreature->getY();

	TPOINT pt = findSuitablePosition(pZone, cx, cy, Creature::MOVE_MODE_WALKING);

	if (pt.x != -1) 
	{
		Range_t rangeDiff = 0;

		if ( pt.x != cx || pt.y != cy )
		{
			rangeDiff = max( abs( (int)(pt.x) - (int)(cx) ) , abs( (int)(pt.y) - (int)(cy) ) );
		}

		ZoneCoord_t oldX = pCreature->getX();
		ZoneCoord_t oldY = pCreature->getY();

		GCDeleteObject gcDO;
		gcDO.setObjectID(pCreature->getObjectID());
		pZone->broadcastPacket(oldX, oldY, &gcDO, pCreature);

		// 이펙트를 삭제해 준다.
		EffectManager* pEffectManager = pCreature->getEffectManager();
		Assert(pEffectManager != NULL);

		if (pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF))
		{
			pCreature->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF); // DeleteObject packet을 보낸후 set.

			// 이펙트의 duraration이 만기가 되지 않았는데, 이펙트를 삭제하려면
			// 강제로 deleteEffect 함수를 불러줘야 한다.
			if (bForce)
			{
				// by sigi. 2002.7.2. RemoveEffect 날려준다.
				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pCreature->getObjectID());
				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);
				if (pCreature->isPC())
				{
					Player* pPlayer = pCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcRemoveEffect);
				}

				pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);
			}

			if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				VAMPIRE_RECORD prev;

				pVampire->getVampireRecord(prev);
				pVampire->initAllStat();
				pVampire->sendModifyInfo(prev);
			}
			else if (pCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);
				pMonster->initAllStat();
			}
		}
		if (pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF))
		{
			pCreature->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF); // DeleteObject packet을 보낸후 set.

			// 이펙트의 duraration이 만기가 되지 않았는데, 이펙트를 삭제하려면
			// 강제로 deleteEffect 함수를 불러줘야 한다.
			if (bForce)
			{
				// by sigi. 2002.7.2. RemoveEffect 날려준다.
				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pCreature->getObjectID());
				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF);
				if (pCreature->isPC())
				{
					Player* pPlayer = pCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcRemoveEffect);
				}

				pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF);
			}

			if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				VAMPIRE_RECORD prev;

				pVampire->getVampireRecord(prev);
				pVampire->initAllStat();
				pVampire->sendModifyInfo(prev);
			}
			else if (pCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);
				pMonster->initAllStat();
			}
		}
		else if (pCreature->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
		{
			pCreature->removeFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);  // DeleteObject packet을 보낸후 set.

			// 이펙트의 duraration이 만기가 되지 않았는데, 이펙트를 삭제하려면
			// 강제로 deleteEffect 함수를 불러줘야 한다.
			if (bForce)
			{
				// by sigi. 2002.7.2. RemoveEffect 날려준다.
				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pCreature->getObjectID());
				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);
				if (pCreature->isPC())
				{
					Player* pPlayer = pCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcRemoveEffect);
				}

				pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);
			}

			if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				VAMPIRE_RECORD prev;

				pVampire->getVampireRecord(prev);
				pVampire->initAllStat();
				pVampire->sendModifyInfo(prev);
			}
			else if (pCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);
				pMonster->initAllStat();
			}
		}

		// 기존 타일에서 크리쳐를 제거하고, 무브 모드를 바꿔준 다음에
		// 새 타일에 추가한다.
		Tile& oldTile = pZone->getTile(oldX, oldY);
		Tile& newTile = pZone->getTile(pt.x, pt.y);

		try {
			oldTile.deleteCreature(pCreature->getObjectID());
		} catch (Error& e) {
			filelog("assertTile.txt", "addUntransformCreature : %s", e.toString().c_str());
			throw;
		}
		pCreature->setMoveMode(Creature::MOVE_MODE_WALKING);
		newTile.addCreature(pCreature);

		Assert(pCreature == newTile.getCreature(pCreature->getMoveMode()));

		// 크리쳐의 좌표를 지정해 준다.
		pCreature->setXYDir(pt.x, pt.y, pCreature->getDir());

		// 크리쳐 클래스에 따라, 존에다 브로드캐스팅한다.
		Creature::CreatureClass CClass = pCreature->getCreatureClass();

		if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			GCAddVampireFromTransformation gcAVFT(pVampire->getVampireInfo3());
			gcAVFT.setEffectInfo(pVampire->getEffectInfo());

			pZone->broadcastPacket( pt.x, pt.y, &gcAVFT, pVampire, true, rangeDiff );

			// send to myself
			GCUntransformOK gcUntransformOK(pt.x, pt.y, pCreature->getDir());
			pCreature->getPlayer()->sendPacket(&gcUntransformOK);
		}
		else if (CClass == Creature::CREATURE_CLASS_MONSTER)
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			GCAddMonsterFromTransformation gcAMFT;
			gcAMFT.setObjectID(pMonster->getObjectID());
			gcAMFT.setMonsterType(pMonster->getMonsterType());
			gcAMFT.setMonsterName(pMonster->getMonsterName());
			gcAMFT.setX(pt.x);
			gcAMFT.setY(pt.y);
			gcAMFT.setDir(pMonster->getDir());
			gcAMFT.setEffectInfo(pMonster->getEffectInfo());
			gcAMFT.setCurrentHP(pMonster->getHP());
			gcAMFT.setMaxHP(pMonster->getHP(ATTR_MAX));

			pZone->broadcastPacket(pt.x, pt.y, &gcAMFT, NULL, true, rangeDiff);
		}
		else
		{
			throw Error("invalid creature type");
		}
	} 
	else 
	{
		if (pCreature->isPC())
		{
			GCUntransformFail gcUntransformFail;
			pCreature->getPlayer()->sendPacket(&gcUntransformFail);
		}
		else
		{
			//throw Error("Cannot unburrow monster.");
		}
	}

	// 변신을 푼 놈이 뱀파이어, 즉 플레이어라면 공격 속도를 보내준다.
	// 이는 클라이언트에서 박쥐로 변신을 했을 때 이전의 공격 속도를 
	// 저장할 수 없는 버그 때문이다. -- 김성민
	if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		GCModifyInformation gcMI;
		gcMI.addShortData(MODIFY_ATTACK_SPEED, pVampire->getAttackSpeed());
		pVampire->getPlayer()->sendPacket(&gcMI);
	}

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 안 보이는 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이는 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addInvisibleCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy)
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	// 뱀파이어나 몬스터만이 투명화가 가능하다.
	Assert(pCreature->isVampire() || pCreature->isMonster());
	
	ObjectID_t creatureID = pCreature->getObjectID();

	GCDeleteObject gcDO;
	gcDO.setObjectID(creatureID); 
		
	pCreature->setFlag(Effect::EFFECT_CLASS_INVISIBILITY);
	
	//Tile& rTile = pZone->getTile(cx, cy);

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(creatureID);
	gcAddEffect.setEffectID(Effect::EFFECT_CLASS_INVISIBILITY);
	gcAddEffect.setDuration(0);
	
	//--------------------------------------------------------------------------------
	//
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//
	//--------------------------------------------------------------------------------
	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(pZone->getWidth() - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix ++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(pZone->getHeight() - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy ++) 
		{
			Tile& curTile = pZone->getTile(ix, iy);
			const slist<Object*> & objectList = curTile.getObjectList();

			slist<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr ++) 
			{
				Assert(*itr != NULL);
				Creature* pViewer= dynamic_cast<Creature*>(*itr);

				if (pViewer != pCreature && pViewer->isPC() && 
					(pViewer->getVisionState(cx, cy) >= IN_SIGHT)) 
				{
					// Viewer 의 ObservingEye 이펙트를 가져온다.
					EffectObservingEye* pEffectObservingEye = NULL;
					if ( pViewer->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
					{
						pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pViewer->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
						//Assert( pEffectObservingEye != NULL );
					}

					// Viewer 의 Gnome's Whisper 이펙트를 가져온다.
					EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
					if ( pViewer->isFlag( Effect::EFFECT_CLASS_GNOMES_WHISPER ) )
					{
						pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pViewer->findEffect( Effect::EFFECT_CLASS_GNOMES_WHISPER ) );
						//Assert( pEffectGnomesWhisper != NULL );
					}

					//cout << "checking" << endl;
					if ( !pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)
							|| pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN)
							|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeHide() )
					   ) // || ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pCreature ) ) ))
					{
						if ( pViewer->isVampire()
							|| pViewer->isFlag( Effect::EFFECT_CLASS_DETECT_INVISIBILITY ) 
							|| ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pCreature  ) )
							|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeInvisibility() )
						)
						{
							pViewer->getPlayer()->sendPacket(&gcAddEffect);
							//cout << "send add invisible effect" << endl;
						}
						else
						{
							pViewer->getPlayer()->sendPacket(&gcDO);
							//cout << "send delete object" << endl;
						}
						// invisbility와 관련해서만, 볼 수 없는자..
/*						if (!pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) 
							&& pViewer->isSlayer()) 
						{
							pViewer->getPlayer()->sendPacket(&gcDO);
						}
						else
						{
							pViewer->getPlayer()->sendPacket(&gcAddEffect);
						}*/
					}
					else
					{
						// 원래 볼 수 없었으므로, 암것도 할 일이 없다.
					}
				}//if
			}//for
		}//for
	}//for

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 안 보이던 크리쳐가 보일 경우, 이 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이던 크리쳐
// bool        bForce    : 강제로 visible 상태가 되었나?
//////////////////////////////////////////////////////////////////////////////
void addVisibleCreature(Zone* pZone, Creature* pCreature, bool bForced)
	throw() 
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	// 뱀파이어나 몬스터만이 투명화가 가능하다.
	Assert(pCreature->isVampire() || pCreature->isMonster());

	// 플래그가 켜져있어야 한다.
	Assert(pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY));
	
	ZoneCoord_t cx          = pCreature->getX();
	ZoneCoord_t cy          = pCreature->getY();
	//Tile&       rTile       = pZone->getTile(cx, cy);

	Packet*                pGCAddXXX = NULL;
	GCAddMonster           gcAddMonster;
	GCAddVampire           gcAddVampire;
	GCAddBurrowingCreature gcABC;
	
	Creature::CreatureClass CClass = pCreature->getCreatureClass();

	if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))	// 사실 불가능
		{
			gcABC.setObjectID(pMonster->getObjectID());
			gcABC.setName(pMonster->getName());
			gcABC.setX(cx);
			gcABC.setY(cy);
			
			pGCAddXXX = &gcABC;
		}
		else
		{
			// 몹의 EffectManager에 들어가있는게 아니기 때문에...
			// 임시로 생성해서 보내준다.
			// 몹은 무한시간 Invisible - -;			by sigi
			EffectInfo* pEffectInfo = new EffectInfo;
			pEffectInfo->addListElement( Effect::EFFECT_CLASS_INVISIBILITY, 0xFFFF);

			// make packet
			gcAddMonster.setObjectID(pMonster->getObjectID());
			gcAddMonster.setMonsterType(pMonster->getMonsterType());
			gcAddMonster.setMonsterName(pMonster->getName());	// by sigi - -;
			gcAddMonster.setX(cx);
			gcAddMonster.setY(cy);
			gcAddMonster.setDir(pMonster->getDir());
			gcAddMonster.setEffectInfo( pEffectInfo );
			gcAddMonster.setCurrentHP(pMonster->getHP());
			gcAddMonster.setMaxHP(pMonster->getHP(ATTR_MAX));

			pGCAddXXX = &gcAddMonster;
		}
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))	// 사실 불가능
		{
			gcABC.setObjectID(pVampire->getObjectID());
			gcABC.setName(pVampire->getName());
			gcABC.setX(cx);
			gcABC.setY(cy);
			
			pGCAddXXX = &gcABC;
		}
		else
		{
//			gcAddVampire.setVampireInfo(pVampire->getVampireInfo3());
//			gcAddVampire.setEffectInfo(pVampire->getEffectInfo());
			makeGCAddVampire( &gcAddVampire, pVampire );
			pGCAddXXX = &gcAddVampire;
		}
	}
	else
	{
		throw Error();
	}

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_INVISIBILITY);
	if (pCreature->isPC())
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert(pPlayer != NULL);
		pPlayer->sendPacket(&gcRemoveEffect);
	}
	
	//--------------------------------------------------------------------------------
	//
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//
	//--------------------------------------------------------------------------------
	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(pZone->getWidth() - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix ++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(pZone->getHeight() - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy ++) 
		{
			Tile& curTile = pZone->getTile(ix, iy);
			const slist<Object*> & objectList = curTile.getObjectList();

			slist<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr ++) 
			{
				Assert(*itr != NULL);

				Creature* pViewer= dynamic_cast<Creature*>(*itr);

				// Viewer 의 Revealer 이펙트를 가져온다.
//				EffectRevealer* pEffectRevealer = NULL;
//				if ( pViewer->isFlag( Effect::EFFECT_CLASS_REVEALER ) )
//				{
//					pEffectRevealer = dynamic_cast<EffectRevealer*>(pViewer->findEffect( Effect::EFFECT_CLASS_REVEALER ) );
//					Assert( pEffectRevealer );
//				}

				// Viewer 의 Observing Eye 이펙트를 가져온다.
				EffectObservingEye* pEffectObservingEye = NULL;
				if ( pViewer->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
				{
					pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pViewer->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
					//Assert( pEffectObservingEye != NULL );
				}

				// Viewer 의 Gnome's Whisper 이펙트를 가져온다.
				EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
				if ( pViewer->isFlag( Effect::EFFECT_CLASS_GNOMES_WHISPER ) )
				{
					pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pViewer->findEffect( Effect::EFFECT_CLASS_GNOMES_WHISPER ) );
					//Assert( pEffectGnomesWhisper != NULL );
				}

				if (pViewer != pCreature 
					&& pViewer->isPC() 
					&& (pViewer->getVisionState(cx, cy) >= IN_SIGHT)) 
				{
					// 주석처리 by sigi
					//if ((!pCreature->isFlag(Effect::EFFECT_CLASS_HIDE) 
					//	|| pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN)))
					{
						// 이전에 이 캐릭을 못 보던 애들에 한해서 
						// 이 캐릭을 Add시켜준다.
						// invisbility와 관련해서만, 볼 수 없는자..
						if (!pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) 
							&& ( pViewer->isSlayer() || pViewer->isOusters() )
							&& !( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pCreature ) )
							&& !( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeInvisibility() )
						) 
						{
							pViewer->getPlayer()->sendPacket(pGCAddXXX);
						}
					}
					//else
					{
						// 원래 볼 수 없었으므로, 암것도 할 일이 없다.
					}

					// 어쨋거나 invisible풀린다는건 보내줘야한다. by sigi
					pViewer->getPlayer()->sendPacket(&gcRemoveEffect);
					
				}//if

			}//for

		}//for

	}//for

	
	//--------------------------------------------
	// effect manager에서 Effect를 강제 삭제한다.
	//--------------------------------------------
	if (bForced == true)
	{
        EffectManager* pEffectManager = pCreature->getEffectManager();
        Assert(pEffectManager);
        pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_INVISIBILITY);
	}

	/*
	GCRemoveEffect removeEffect;
	removeEffect.setObjectID(pCreature->getObjectID());
	removeEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_INVISIBILITY);
	pZone->broadcastPacket(cx, cy, &removeEffect);
	*/
	
	pCreature->removeFlag(Effect::EFFECT_CLASS_INVISIBILITY);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 안 보이는 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이는 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addSnipingModeCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy)
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	// 슬레이어만 이 기술을 쓸 수 있다.
	Assert(pCreature->isSlayer());
	
	ObjectID_t creatureID = pCreature->getObjectID();

	GCDeleteObject gcDO;
	gcDO.setObjectID(creatureID); 
		
	pCreature->setFlag(Effect::EFFECT_CLASS_SNIPING_MODE);
	
	//Tile& rTile = pZone->getTile(cx, cy);

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(creatureID);
	gcAddEffect.setEffectID(Effect::EFFECT_CLASS_SNIPING_MODE);
	gcAddEffect.setDuration(0);
	
	//--------------------------------------------------------------------------------
	//
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//
	//--------------------------------------------------------------------------------
	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(pZone->getWidth() - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix ++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(pZone->getHeight() - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy ++) 
		{
			Tile& curTile = pZone->getTile(ix, iy);
			const slist<Object*> & objectList = curTile.getObjectList();

			slist<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr ++) 
			{
				Assert(*itr != NULL);
				Creature* pViewer= dynamic_cast<Creature*>(*itr);

				if (pViewer != pCreature && pViewer->isPC() && 
					(pViewer->getVisionState(cx, cy) >= IN_SIGHT)) 
				{
					// Viewer 의 Revealer 이펙트를 가져온다.
//					EffectRevealer* pEffectRevealer = NULL;
//					if ( pViewer->isFlag( Effect::EFFECT_CLASS_REVEALER ) )
//					{
//						pEffectRevealer = dynamic_cast<EffectRevealer*>(pViewer->findEffect( Effect::EFFECT_CLASS_REVEALER ) );
//						Assert( pEffectRevealer );
//					}
					// Viewer 의 Gnome's Whisper 이펙트를 가져온다.
					EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
					if ( pViewer->isFlag( Effect::EFFECT_CLASS_GNOMES_WHISPER ) )
					{
						pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pViewer->findEffect( Effect::EFFECT_CLASS_GNOMES_WHISPER ) );
						//Assert( pEffectGnomesWhisper != NULL );
					}

					if ( !pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)
							|| pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN)
							|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeHide() )
					   )
//						|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pCreature ) ) ))
					{
						if ( pViewer->isFlag( Effect::EFFECT_CLASS_DETECT_INVISIBILITY )
								|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeSniping() )
						   ) 
//							|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping( pCreature ) ) )
						{
							pViewer->getPlayer()->sendPacket( &gcAddEffect );
						}
						else
						{
							pViewer->getPlayer()->sendPacket( &gcDO );
						}

						// invisbility와 관련해서만, 볼 수 없는자..
/*						if (!pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || pViewer->isVampire()) 
						{
							pViewer->getPlayer()->sendPacket(&gcDO);
						}
						else
						{
							pViewer->getPlayer()->sendPacket(&gcAddEffect);
						}*/
					}
					else
					{
						// 원래 볼 수 없었으므로, 암것도 할 일이 없다.
					}
				}//if
			}//for
		}//for
	}//for

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 안 보이던 크리쳐가 보일 경우, 이 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이던 크리쳐
// bool        bForce    : 강제로 visible 상태가 되었나?
//////////////////////////////////////////////////////////////////////////////
void addUnSnipingModeCreature(Zone* pZone, Creature* pCreature, bool bForced)
	throw() 
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	// 슬레이어만이 스나이핑이 가능하다.
	Assert(pCreature->isSlayer());

	// 플래그가 켜져있어야 한다.
	Assert(pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE));
	
	ZoneCoord_t cx          = pCreature->getX();
	ZoneCoord_t cy          = pCreature->getY();
	//Tile&       rTile       = pZone->getTile(cx, cy);

	Packet*                pGCAddXXX = NULL;
	GCAddSlayer		 	   gcAddSlayer;
	
	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
//	gcAddSlayer.setSlayerInfo(pSlayer->getSlayerInfo3());
//	gcAddSlayer.setEffectInfo(pSlayer->getEffectInfo());
	makeGCAddSlayer( &gcAddSlayer, pSlayer );
	pGCAddXXX = &gcAddSlayer;
	
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_SNIPING_MODE);

	if ( pCreature->isPC() )
	{
		Player* pPlayer = pCreature->getPlayer();
		Assert( pPlayer );
		pPlayer->sendPacket( &gcRemoveEffect );
	}

	//--------------------------------------------------------------------------------
	//
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//
	//--------------------------------------------------------------------------------
	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(pZone->getWidth() - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix ++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(pZone->getHeight() - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy ++) 
		{
			Tile& curTile = pZone->getTile(ix, iy);
			const slist<Object*> & objectList = curTile.getObjectList();

			slist<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr ++) 
			{
				Assert(*itr != NULL);

				Creature* pViewer= dynamic_cast<Creature*>(*itr);

				// Viewer 의 Revealer 이펙트를 가져온다.
//				EffectRevealer* pEffectRevealer = NULL;
//				if ( pViewer->isFlag( Effect::EFFECT_CLASS_REVEALER ) )
//				{
//					pEffectRevealer = dynamic_cast<EffectRevealer*>(pViewer->findEffect(Effect::EFFECT_CLASS_REVEALER));
//					Assert( pEffectRevealer );
//				}
				// Viewer 의 Gnome's Whisper 이펙트를 가져온다.
				EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
				if ( pViewer->isFlag( Effect::EFFECT_CLASS_GNOMES_WHISPER ) )
				{
					pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pViewer->findEffect( Effect::EFFECT_CLASS_GNOMES_WHISPER ) );
					//Assert( pEffectGnomesWhisper != NULL );
				}

				if (pViewer != pCreature && pViewer->isPC() && (pViewer->getVisionState(cx, cy) >= IN_SIGHT)) 
				{
					if ( !pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)
							|| pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN)
							|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeHide() )
					   )
//						|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pCreature ) ) ))
					{
						// invisbility와 관련해서만, 볼 수 없는자..
						if ( !pViewer->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY)
								|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeSniping() )
							)
//							&& !( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping( pCreature ) ) )
						{
							pViewer->getPlayer()->sendPacket(pGCAddXXX);
						}
					}
					else
					{
						// 원래 볼 수 없었으므로, 암것도 할 일이 없다.
					}
					
					// sniping mode 가 풀린다는 걸 보내준다.
					pViewer->getPlayer()->sendPacket( &gcRemoveEffect );
					
				}//if

			}//for

		}//for

	}//for

	
	//--------------------------------------------
	// effect manager에서 Effect를 강제 삭제한다.
	//--------------------------------------------
	if (bForced == true)
	{
        EffectManager* pEffectManager = pCreature->getEffectManager();
        Assert(pEffectManager);
        pEffectManager->deleteEffect(pCreature, Effect::EFFECT_CLASS_SNIPING_MODE);
	}

/*	GCRemoveEffect removeEffect;
	removeEffect.setObjectID(pCreature->getObjectID());
	removeEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_SNIPING_MODE);
	pZone->broadcastPacket(cx, cy, &removeEffect);
*/	
	pCreature->removeFlag(Effect::EFFECT_CLASS_SNIPING_MODE);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존에다 지뢰를 더한다.
//
// Zone*       pZone : 존에 대한 포인터
// Mine*       pMine : 지뢰 객체에 대한 포인터
// ZoneCoord_t cx    : 지뢰를 더할 좌표 x
// ZoneCoord_t cy    : 지뢰를 더할 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addInstalledMine(Zone* pZone, Mine* pMine, ZoneCoord_t cx, ZoneCoord_t cy) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pMine != NULL);
	Assert(pMine->isFlag(Effect::EFFECT_CLASS_INSTALL));

	//Tile& rTile = pZone->getTile(cx, cy);

	GCDeleteObject gcDO;
	gcDO.setObjectID(pMine->getObjectID());

	GCAddInstalledMineToZone gcAddMine;
	gcAddMine.setObjectID(pMine->getObjectID());
	gcAddMine.setX(cx);
	gcAddMine.setY(cy);
	gcAddMine.setItemClass(pMine->getItemClass());
	gcAddMine.setItemType(pMine->getItemType());
	gcAddMine.setOptionType(pMine->getOptionTypeList());
	gcAddMine.setDurability(pMine->getDurability());

	//--------------------------------------------------------------------------------
	//
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//
	//--------------------------------------------------------------------------------
	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(pZone->getWidth() - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix ++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(pZone->getHeight() - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy ++) 
		{
			Tile& rTile2 = pZone->getTile(ix, iy);
			const slist<Object*> & objectList = rTile2.getObjectList();

			for (slist<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr ++) 
			{
				Assert(*itr != NULL);

				Creature* pViewer= dynamic_cast<Creature*>(*itr);

				Assert(pViewer != NULL);

				if (pViewer->isPC() && (pViewer->getVisionState(cx, cy) >= IN_SIGHT))
				{
					Player* pPlayer = pViewer->getPlayer();
					Assert(pPlayer);
					pPlayer->sendPacket(&gcDO);

					if ( pViewer->isFlag(Effect::EFFECT_CLASS_REVEALER) ) 
					{
						pPlayer->sendPacket(&gcAddMine);
					}
				}//if
			}//for
		}//for
	}//for

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐가 지뢰를 밟지 않았는지 체크한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 검사할 크리쳐
// ZoneCoord_t X         : 검사할 좌표 x
// ZoneCoord_t Y         : 검사할 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool checkMine(Zone* pZone, Creature* pCreature, ZoneCoord_t X, ZoneCoord_t Y) 
	throw()
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	static bool bNonPK = g_pGameServerInfoManager->getGameServerInfo( 1, g_pConfig->getPropertyInt( "ServerID" ), g_pConfig->getPropertyInt( "WorldID" ) )->isNonPKServer();
	if ( bNonPK && pCreature->isPC() ) return false;

	// 슬레이어가 밟을 순 없다.
	if ( pCreature->isSlayer() ) return false;

	Assert(pZone != NULL);

	// 위에 있던걸 여기로 내림 by sigi. 2002.11.7
	// 만일 안전지대라면 폭파시키지 않는다.
	if (pZone->getZoneLevel(X, Y) & SAFE_ZONE) return false;

	Tile& rTile = pZone->getTile(X, Y);

	// 타일에 아이템이 없어도 폭파시키지 않는다.
	if (!rTile.hasItem()) return false;

	//cout << "Check Mine Start" << endl;

	Item* pItem = rTile.getItem();

	// 바닥에 있는 아이템이 인스톨된 지뢰가 아니거나,
	// 크리쳐가 걸어다니는 크리쳐가 아니라면 지뢰를 폭파시키지 않는다.
	if (pItem->getItemClass() != Item::ITEM_CLASS_MINE) return false;
	if (pItem->isFlag(Effect::EFFECT_CLASS_INSTALL) == false) return false;
	if (pCreature->isWalking() == false) return false;

	GCMineExplosionOK1 _GCMineExplosionOK1;
	GCMineExplosionOK2 _GCMineExplosionOK2;

	list<Creature*> cList;

	Mine* pMine = dynamic_cast<Mine*>(pItem);
	Assert(pMine != NULL);

	Dir_t      Dir           = pMine->getDir();
	Damage_t   Damage        = pMine->getDamage(); 
	ItemType_t Type          = pMine->getItemType();
	string	   InstallerName = pMine->getInstallerName();
	int		   PartyID       = pMine->getInstallerPartyID();

	BYTE explodeType = Type; // 폭발 형태

	// 지뢰가 폭발했으니, 일단 무조건 삭제해 준다.
	pZone->deleteItem(pMine, X, Y);

	GCDeleteObject gcDO;
	gcDO.setObjectID(pMine->getObjectID());
	pZone->broadcastPacket(X, Y, &gcDO);

	SAFE_DELETE(pMine);

	/*
	switch(Type)
	{
		case 0: // Viper
			explodeType = 0;
			break;
		case 1: // Diamond Back
			explodeType = 2;
			break;
		case 2: // Sidewinder
			explodeType = 5;
			break;
		case 3: // cobra
			explodeType = 3;
			break;
		default:
			Assert(false);
	};
	*/

	int tileX, tileY;

	const int* xOffsetByEType = NULL;
	const int* yOffsetByEType = NULL;
	int tiles = 0;
	
	// 지뢰 타입에 따른 폭발 offset 마스크를 가져온다.
	getExplosionTypeXYOffset(explodeType, Dir, xOffsetByEType, yOffsetByEType, tiles);

	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

	for (int tileI = 0; tileI < tiles; tileI++)
	{
		tileX = X + xOffsetByEType[ tileI];
		tileY = Y + yOffsetByEType[ tileI];
		//cout << "Check1 Tile X : " << (int)tileX << "," << " Tile Y : " << (int)tileY << endl;

		// 현재 좌표가 존 내부이고, 안전 지대가 아니라면...
		if (rect.ptInRect(tileX, tileY) && !(pZone->getZoneLevel(tileX, tileY) & SAFE_ZONE))
		{

//			if( tileX != X || tileY != Y ) checkMine( pZone, tileX, tileY );
			const Tile& tile = pZone->getTile(tileX, tileY);
			const slist<Object*>& oList = tile.getObjectList();
			
			// 타일 위의 모든 오브젝트에 대해서 조사를 한다.
			for (slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++)
			{
				// 조건을 확인
				Object* pObject = *itr;
				if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					// Damage를 입는 것들만 cList에 추가시킨다.
					Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
					if (pTargetCreature->isSlayer())
					{
						//Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
						cList.push_back(pTargetCreature);
					}
					else if (pTargetCreature->isVampire())
					{
						//Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
						cList.push_back(pTargetCreature);
					}
					else if (pTargetCreature->isOusters())
					{
						cList.push_back(pTargetCreature);
					}
					else if (pTargetCreature->isMonster())
					{
						//Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
						cList.push_back(pTargetCreature);
					}
					else continue;

					ObjectID_t targetObjectID = pTargetCreature->getObjectID();
					_GCMineExplosionOK1.addCListElement(targetObjectID);
					_GCMineExplosionOK2.addCListElement(targetObjectID);

				}
			}
		}
	}

	_GCMineExplosionOK1.setXYDir(X, Y, Dir);
	_GCMineExplosionOK1.setItemType(Type);

	_GCMineExplosionOK2.setXYDir(X, Y, Dir);
	_GCMineExplosionOK2.setItemType(Type);

	for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
	{
		Creature* pTargetCreature = *itr;
		_GCMineExplosionOK1.clearList();
		//cout << "Set Damage : " << (int)Damage << endl;

		if( pTargetCreature->isSlayer() ) Damage = max( 1, Damage / 2 );
		setDamage(pTargetCreature, Damage, NULL, 0, &_GCMineExplosionOK1);

		if (pTargetCreature->isPC())
		{
			pTargetCreature->getPlayer()->sendPacket(&_GCMineExplosionOK1);
		} else if( pTargetCreature->isMonster() ) {

			Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);

			// 지뢰 설치자의 데미지를 추가해 준다.
			// 맞는 놈이 몬스터이고, 공격자가 사람이라면,
			// 데미지에 따라서 변하는 우선권 테이블을 갱신해 주어야 한다.
			pMonster->addPrecedence(InstallerName, PartyID, Damage);
			pMonster->setLastHitCreatureClass(Creature::CREATURE_CLASS_SLAYER);

		}
	}

	pZone->broadcastPacket(X, Y, &_GCMineExplosionOK2, cList);

	//cout << "Check Mine End" << endl;
	return true;
 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 지뢰가 연쇄로 터지는지 아닌지 체크 한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 검사할 크리쳐
// ZoneCoord_t X         : 검사할 좌표 x
// ZoneCoord_t Y         : 검사할 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool checkMine( Zone * pZone, ZoneCoord_t X, ZoneCoord_t Y ) 
	throw()
{
	__BEGIN_TRY

	Assert(pZone != NULL);

	// 만일 안전지대라면 폭파시키지 않는다.
	if (pZone->getZoneLevel(X, Y) & SAFE_ZONE) return false;

	Tile& rTile = pZone->getTile(X, Y);

	// 타일에 아이템이 없어도 폭파시키지 않는다.
	if (rTile.hasItem() == false) return false;

	//cout << "Check Mine2 Start" << endl;

	Item* pItem = rTile.getItem();

	// 바닥에 있는 아이템이 인스톨된 지뢰가 아니거나,
	// 크리쳐가 걸어다니는 크리쳐가 아니라면 지뢰를 폭파시키지 않는다.
	if (pItem->getItemClass() != Item::ITEM_CLASS_MINE) return false;
	if (pItem->isFlag(Effect::EFFECT_CLASS_INSTALL) == false) return false;

	GCMineExplosionOK1 _GCMineExplosionOK1;
	GCMineExplosionOK2 _GCMineExplosionOK2;

	list<Creature*> cList;

	Mine* pMine = dynamic_cast<Mine*>(pItem);
	Assert(pMine != NULL);

	Dir_t      Dir           = pMine->getDir();
	Damage_t   Damage        = pMine->getDamage(); 
	ItemType_t Type          = pMine->getItemType();
	string     InstallerName = pMine->getInstallerName();
	int        PartyID       = pMine->getInstallerPartyID();

	BYTE explodeType = Type; // 폭발 형태
	/*
	switch(Type)
	{
		case 0: // Viper
			explodeType = 0;
			break;
		case 1: // Diamond Back
			explodeType = 2;
			break;
		case 2: // Sidewinder
			explodeType = 5;
			break;
		case 3: // cobra
			explodeType = 3;
			break;
		default:
			Assert(false);
	};
	*/

	// 지뢰가 폭발했으니, 일단 삭제해 준다.
	pZone->deleteItem(pMine, X, Y);

	GCDeleteObject gcDO;
	gcDO.setObjectID(pMine->getObjectID());
	pZone->broadcastPacket(X, Y, &gcDO);

	SAFE_DELETE(pMine);


	int tileX, tileY;

	const int* xOffsetByEType = NULL;
	const int* yOffsetByEType = NULL;
	int tiles = 0;
	
	// 지뢰 타입에 따른 폭발 offset 마스크를 가져온다.
	getExplosionTypeXYOffset(explodeType, Dir, xOffsetByEType, yOffsetByEType, tiles);

	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

	for (int tileI = 0; tileI < tiles; tileI++)
	{
		tileX = X + xOffsetByEType[ tileI];
		tileY = Y + yOffsetByEType[ tileI];
		//cout << "Check2 Tile X : " << (int)tileX << "," << " Tile Y : " << (int)tileY << endl;

		// 현재 좌표가 존 내부이고, 안전 지대가 아니라면...
		if (rect.ptInRect(tileX, tileY) && !(pZone->getZoneLevel(tileX, tileY) & SAFE_ZONE))
		{
//			if( tileX != X || tileY != Y ) checkMine( pZone, tileX, tileY );

			const Tile& tile = pZone->getTile(tileX, tileY);
			const slist<Object*>& oList = tile.getObjectList();
			
			// 타일 위의 모든 오브젝트에 대해서 조사를 한다.
			for (slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++)
			{
				// 조건을 확인
				Object* pObject = *itr;
				if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					// Damage를 입는 것들만 cList에 추가시킨다.
					Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
					if (pTargetCreature->isSlayer())
					{
						//Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
						cList.push_back(pTargetCreature);
					}
					else if (pTargetCreature->isVampire())
					{
						//Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
						cList.push_back(pTargetCreature);
					}
					else if (pTargetCreature->isOusters())
					{
						cList.push_back(pTargetCreature);
					}
					else if (pTargetCreature->isMonster())
					{
						//Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
						cList.push_back(pTargetCreature);
					}
					else continue;

					ObjectID_t targetObjectID = pTargetCreature->getObjectID();
					_GCMineExplosionOK1.addCListElement(targetObjectID);
					_GCMineExplosionOK2.addCListElement(targetObjectID);

				}
			}
		}
	}

	_GCMineExplosionOK1.setXYDir(X, Y, Dir);
	_GCMineExplosionOK1.setItemType(Type);

	_GCMineExplosionOK2.setXYDir(X, Y, Dir);
	_GCMineExplosionOK2.setItemType(Type);

	for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
	{
		Creature* pTargetCreature = *itr;
		_GCMineExplosionOK1.clearList();
		//cout << "Set Damage : " << (int)Damage << endl;

		if( pTargetCreature->isSlayer() ) Damage = max( 1, Damage / 2 );
		setDamage(pTargetCreature, Damage, NULL, 0, &_GCMineExplosionOK1);

		if (pTargetCreature->isPC())
		{
			pTargetCreature->getPlayer()->sendPacket(&_GCMineExplosionOK1);
		} else if( pTargetCreature->isMonster() ) {

			Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);

			// 지뢰 설치자의 데미지를 추가해 준다.
			// 맞는 놈이 몬스터이고, 공격자가 사람이라면,
			// 데미지에 따라서 변하는 우선권 테이블을 갱신해 주어야 한다.
			pMonster->addPrecedence(InstallerName, PartyID, Damage);
			pMonster->setLastHitCreatureClass(Creature::CREATURE_CLASS_SLAYER);

		}
	}

	pZone->broadcastPacket(X, Y, &_GCMineExplosionOK2, cList);

	//cout << "Check Mine2 End" << endl;
	return true;
 
	__END_CATCH
}

bool checkTrap( Zone* pZone, Creature* pCreature )
{
	if ( !isValidZoneCoord( pZone, pCreature->getX(), pCreature->getY() ) ) return false;

	Tile& rTile = pZone->getTile( pCreature->getX(), pCreature->getY() );
	Effect* pEffect = rTile.getEffect( Effect::EFFECT_CLASS_TRAP_INSTALLED );
	if ( pEffect == NULL ) return false;

	int ratio = 0;

	if ( pCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		ratio = 100 - (pMonster->getLevel()/10);
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		ratio = 100 - (pVampire->getINT()/8);
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		ratio = 100 - (pOusters->getINT()/8);
	}
	else return false;

	if ( rand()%100 > ratio ) return false;
	
	EffectTrapInstalled* pTrap = dynamic_cast<EffectTrapInstalled*>(pEffect);
	pTrap->affect(pCreature);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐를 다른 존으로 이동시킨다.
//
// Creature*   pCreature    : 이동할 크리쳐
// ZoneID_t    TargetZoneID : 이동할 존 ID
// ZoneCoord_t TargetX      : 이동할 존 좌표 X
// ZoneCoord_t TargetY      : 이동할 존 좌표 Y
// bool        bSendMoveOK  : GCMoveOK를 보내주는가에 대한 여부
//////////////////////////////////////////////////////////////////////////////
void transportCreature(Creature* pCreature, ZoneID_t TargetZoneID, ZoneCoord_t TX, ZoneCoord_t TY, bool bSendMoveOK) 
	throw()
{
	__BEGIN_TRY

	Assert(pCreature->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Zone* pZone = pCreature->getZone();

	// GPS_NORMAL인 경우만 transportCreature를 할 수 있다.
	// 다른 경우는 무시한다.
	// by sigi. 2002.12.10

	if (pGamePlayer->getPlayerStatus()!=GPS_NORMAL)
	{
		filelog("transportCreatureError.log", "PlayerStatus not GPS_NORMAL: %d, Current[%d, (%d,%d)] --> Target[%d, (%d,%d)]", 
					(int)pGamePlayer->getPlayerStatus(),
					(int)pZone->getZoneID(), (int)pCreature->getX(), (int)pCreature->getY(),
					(int)TargetZoneID, (int)TX, (int)TY);

		return;
	}

	cout << "ZoneUtil.cpp step 1" << endl;


	Assert(pGamePlayer != NULL);
	Assert(pZone != NULL);

	if (bSendMoveOK)
	{
		cout << "ZoneUtil.cpp step 2" << endl;
		// 일단 바보 클라이언트를 위해서 GCMoveOK 를 날려준다.
		GCMoveOK gcMoveOK(pCreature->getX(), pCreature->getY(), pCreature->getDir());
		pGamePlayer->sendPacket(&gcMoveOK);
	}


//#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
// ZoneInfo 의 OpenLevel에 따라 warp/zone이동을 막는다.
// add by inthesky 2004.07.26
	
	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(TargetZoneID);

	// add by Sonic 2006.10.21

		if(TargetZoneID==1013 )//각薑쟁갰뒈인
		{
			cout << "ZoneUtil.cpp step New1013" << endl;
			if(pZoneInfo->isNoPortalZone())
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
				ItemType_t fitItem = 0;
				Item* pItem=pPC->getInventory()->findItem(Item::ITEM_CLASS_MONEY,fitItem);
				GCSystemMessage gcSystemMessage1;
				if(pItem==NULL)
				{
					gcSystemMessage1.setMessage( "쏵흙맡뒈인극矜撻唐陵귑!" );
					pGamePlayer->sendPacket (&gcSystemMessage1);
					return;
				}
				if(pItem->getNum()==1)
					{
						if(pItem->isTimeLimitItem()==true && pItem->getHour() > 0)
						{
						}
						else
						{
							pPC->getInventory()->deleteItem(pItem->getObjectID());
							pItem->destroy();
							SAFE_DELETE(pItem);
						}
					}else
					{
						pItem->setNum((pItem->getNum()-1))
					}
			}
			GCSystemMessage gcSystemMessage1;
			gcSystemMessage1.setMessage( "뻑短윱돕'각薑쟁갰댔괜뒈인'，句寡댕소떼댔돕봤돨괜膠！" );
			pGamePlayer->sendPacket (&gcSystemMessage1);
		}
	// end by sonic

	//if(!pZoneInfo->isAvailable())
	//{
	//	GCSystemMessage gcSystemMessage;
	//	gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER) );
	//	pGamePlayer->sendPacket (&gcSystemMessage);
	//	return;
	//}
	
	cout << "ZoneUtil.cpp step 3" << endl;
//#endif
	
	bool bNoMoney = false;

	try {
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(TargetZoneID);

		// 유료화 존이고 유료사용중이 아니면..
		if (pZoneInfo!=NULL
			&& (pZoneInfo->isPayPlay() || pZoneInfo->isPremiumZone())
			&& !pGamePlayer->isPayPlaying()
			&& !(g_pWarSystem->hasActiveRaceWar() && pZoneInfo->isHolyLand())
		)
		{
			cout << "ZoneUtil.cpp step 4" << endl;

			bool bEnterZone = true;

			//Statement* pStmt = NULL;
			string connectIP = pGamePlayer->getSocket()->getHost();

			// 유료 서비스 사용이 가능한가?
			if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
			{
				cout << "ZoneUtil.cpp step 5" << endl;
			
				sendPayInfo(pGamePlayer);

				// 존을 찾는다.
				Zone* pZone = getZoneByZoneID(TargetZoneID);
				Assert(pZone!=NULL);

				// 마스터 레어라면 들어갈 수 있는가
				// PK존이라면 들어갈 수 있는가.
				bEnterZone = enterMasterLair( pZone, pCreature );
			}
			else if (pZoneInfo->isPayPlay() && !pGamePlayer->isFamilyFreePass() ) // 패밀리 프리 패스는 유료존으로 갈 수 있다.
			{
				cout << "ZoneUtil.cpp step 6" << endl;

				bEnterZone = false;
			}

			if (!bEnterZone)
			{

				cout << "ZoneUtil.cpp step 7" << endl;
			
				// 현재 존에 들어갈 수 없는 경우이다.
				// 유료 서비스 사용 불가인 경우
				// 마스터 레어인 경우
				// slayer : 에슬남동에서 부활하는 곳으로 간다.
				// vampire : 림보남동에서 부활하는 곳으로 간다.
				ZONE_COORD zoneCoord;
				bool bFindPos = false;

				if (pCreature->isSlayer())
					bFindPos = g_pResurrectLocationManager->getSlayerPosition(13, zoneCoord);
				else if ( pCreature->isVampire() )
					bFindPos = g_pResurrectLocationManager->getVampirePosition(23, zoneCoord);
				else if ( pCreature->isOusters() )
					bFindPos = g_pResurrectLocationManager->getOustersPosition(1311, zoneCoord);

				if (bFindPos)
				{
					TargetZoneID        = zoneCoord.id;
					TX					= zoneCoord.x;
					TY					= zoneCoord.y;

					bNoMoney = true;
				}
				else
				{
					// 아, 비상이닷...
					filelog("zoneUtilError.txt", "[ZoneUtil::transportCreature] ResurrectInfo is not esta..");
					throw Error("Critical Error : ResurrectInfo is not established!1");
				}
			}
		}
	} catch (NoSuchElementException& no) {
		filelog("zoneUtilError.txt", "[ZoneUtil::transportCreature] %s", no.toString().c_str());
		throw Error(no.toString());
	}


	// 우선 이전 존에서 PC 를 삭제하고, 플레이어를 ZPM -> IPM 으로 옮긴다.
	try 
	{
		// 요금 지불 안한 slayer가 오토바이를 타고 있는 경우는
		// 오토바이를 없앤다.
		if (bNoMoney && pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			if (pSlayer->hasRideMotorcycle())
			{
				pSlayer->getOffMotorcycle();

				GCGetOffMotorCycle _GCGetOffMotorCycle;
				_GCGetOffMotorCycle.setObjectID(pSlayer->getObjectID());
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCGetOffMotorCycle);
			}
		}

		cout << "ZoneUtil.cpp step 8" << endl;
		// 크리처의 정보를 저장한다.
		pCreature->save();

		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(TargetZoneID);
		Assert( pZoneInfo != NULL );

		// 피의 성서를 가지고 성지 밖으로 나갈 때는 피의 성서를 버린다.
		// 성의 지하던젼으로 가지고 나갈때도 버린다.
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE ) )
		{
			if ( pZone->isHolyLand() )
			{
				if ( !pZoneInfo->isHolyLand()
				  || ( !pZoneInfo->isCastle() && g_pCastleInfoManager->isSameCastleZone( pZone->getZoneID(), TargetZoneID ) ) )
					dropRelicToZone( pCreature );
			}
		}

		// 성 상징을 가지고 성 밖으로 나갈 때는 성 상징을 버린다.
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL ) )
		{
			if ( pZone->isHolyLand() && !pZoneInfo->isHolyLand() 
				|| !g_pCastleInfoManager->isSameCastleZone( pCreature->getZone()->getZoneID(), TargetZoneID )
				// 성 안으로 못 들어간다. 성 상징은 성 지하 맵에 있기 때문에..
				|| pZoneInfo->isCastle())
			{
				dropRelicToZone( pCreature );
			}
		}

		if ( pCreature->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) )
		{
			if ( g_pFlagManager->isFlagAllowedZone( pZone->getZoneID() ) && !g_pFlagManager->isFlagAllowedZone( pZoneInfo->getZoneID() ) )
			{
				dropFlagToZone( pCreature );
			}
		}

		if ( pCreature->isFlag( Effect::EFFECT_CLASS_HAS_SWEEPER ) );
			dropSweeperToZone( pCreature );
		
		// 성지에서 성지 밖으로 나가거나 성지 밖에서 성지 안으로 들어올때는 initAllStat을 불러준다.
		if ( pZone->isHolyLand() != pZoneInfo->isHolyLand() )
		{
			pCreature->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		}

		if ( g_pLevelWarZoneInfoManager->isCreatureBonusZone( pCreature, pZone->getZoneID() )
			!= g_pLevelWarZoneInfoManager->isCreatureBonusZone( pCreature, TargetZoneID ) )
		{
			pCreature->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		}

		if ( pZone->isLevelWarZone() != pZoneInfo->isLevelWarZone() )
		{
			pCreature->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		}

		// 이제, 존에서 PC를 삭제한다.
		//
		// *CAUTION*
		// pCreature의 좌표가 실제로 pCreature가 존재하는 타일의 좌표와 같아야 한다.
		// 따라서, 이 메쏘드를 호출하기 전에 좌표를 잘 바꿔놔야 한당..
		pZone->deleteCreature(pCreature, pCreature->getX(), pCreature->getY());

		// 존그룹의 ZPM에서 플레이어를 삭제한다.
		//pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(pGamePlayer->getSocket()->getSOCKET());
		//pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer_NOBLOCKED(pGamePlayer->getSocket()->getSOCKET());
		pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(pGamePlayer->getSocket()->getSOCKET());

		// 크리처의 새로운 좌표는 포탈의 도착 지점이다.
		//pCreature->setXY(TX, TY);
		//pCreature->setZone(NULL);
		cout << "ZoneUtil.cpp step 9" << endl;

		// IPM으로 플레이어를 옮긴다.
		//g_pIncomingPlayerManager->addPlayer(pGamePlayer);
		//g_pIncomingPlayerManager->pushPlayer(pGamePlayer);
		pZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(pGamePlayer);
	} 
	catch (NoSuchElementException & nsee) 
	{
		filelog("zoneUtilError.txt", "[ZoneUtil::transportCreature2] %s", nsee.toString().c_str());
		throw Error(nsee.toString());
	}

	// 크리처에다가 존을 지정해준다. 이는 OID 를 할당받기 위해서이다.
	// 이동할 존을 설정한다. by sigi. 2002.5.11
	Zone* pNewZone = getZoneByZoneID(TargetZoneID);
	Assert(pNewZone!=NULL);

	pCreature->setNewZone(pNewZone);
	pCreature->setNewXY(TX, TY);

	// 크리처 자신과 소유 아이템들의 OID를 할당받는다.

	// ZonePlayerManager의 heartbeat에서 한다.
	// 주석처리 by sigi. 2002.5.14
	//pCreature->registerObject();

	/*
	// GCUpdateInfo 패킷을 만들어둔다.
	GCUpdateInfo gcUpdateInfo;
	makeGCUpdateInfo(&gcUpdateInfo, pCreature);
	pGamePlayer->sendPacket(&gcUpdateInfo);
	*/

	// 아담의 성지가 아닌 곳에서 아담의 성지로 가거나 
	// 아담의 성지에서 딴 곳으로 가는 경우
	if (!pZone->isHolyLand() && pNewZone->isHolyLand()
		|| pZone->isHolyLand() && !pNewZone->isHolyLand())
	{
		sendHolyLandWarpEffect( pCreature );
		cout << "ZoneUtil.cpp step 10" << endl;
	}

	// change player status
	pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_CG_READY);

	cout << "ZoneUtil.cpp step 11" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 특정 존ID를 가진 존을 찾아서 포인터를 리턴한다.
// ZoneID_t ZID : 찾고자 하는 존 ID
//////////////////////////////////////////////////////////////////////////////
Zone* getZoneByZoneID(ZoneID_t ZID) 
	throw (Error)
{
	__BEGIN_TRY

	ZoneInfo* pZoneInfo = NULL;
	try 
	{
		pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZID);
	} 
	catch (NoSuchElementException&) 
	{
		//cerr << "getZoneByZoneID() : No Such ZoneInfo: " << (int)ZID << endl;
		StringStream msg;
		msg << "getZoneByZoneID() : No Such ZoneInfo [" << (int)ZID << "]";
		throw Error(msg.toString());
	}

	ZoneGroup* pZoneGroup = NULL;
	try 
	{
		pZoneGroup = g_pZoneGroupManager->getZoneGroup(pZoneInfo->getZoneGroupID());
	}
	catch (NoSuchElementException&) 
	{
		// 일단은 서버가 1대이므로.. 그대로 나간다...
		//cerr << "getZoneByZoneID() : No Such ZoneGroup" << endl;
		throw Error("getZoneByZoneID() : No Such ZoneGroup");

		/*
		//--------------------------------------------------------------------------------
		// 현재 게임 서버의 존그룹매니저에서 그런 존그룹을 발견할 수 없다는 소리는
		// 분명히 다른 게임 서버에 소속된 존그룹이라는 뜻이다. 따라서, 그 게임
		// 서버에게 GGIncomingConnection 패킷을 전송해야 한다. 즉 그 게임 서버의 IP/Port
		// 를 알아내야 한다.
		//--------------------------------------------------------------------------------
		GGIncomingConnection ggIncomingConnection;
		ggIncomingConnection.setClientIP(pCreature->getPlayer->getSocket()->getHost());
		ggIncomingConnection.setPlayerID(pCreature->getPlayer->getPlayerID());
		ggIncomingConnection.setPCName(pCreature->getName());

		g_pGameServerManager->sendPacket(_GameServerIP_, _GameServerPort_, &ggIncomingConnection);

		pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_GG_INCOMING_CONNECTION_OK);
		*/
	}

	Zone* pZone = pZoneGroup->getZone(ZID);
	Assert(pZone != NULL);

	return pZone;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 운영자 명령어로서, 특정 타입의 몬스터를 존에다 추가한다.
//////////////////////////////////////////////////////////////////////////////
void addMonstersToZone(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, SpriteType_t SType, MonsterType_t MType, int num, const SUMMON_INFO& summonInfo, list<Monster*>* pSummonedMonsters) 
	throw()
{
	__BEGIN_TRY

	try
	{
		MonsterManager* pMonsterManager = pZone->getMonsterManager();
		Assert(pMonsterManager != NULL);
		//pMonsterManager->addMonsters(x, y, MType, num, summonInfo);

		/*
		if (summonInfo.clanType == SUMMON_INFO::CLAN_TYPE_RANDOM_GROUP)
		{
			summonInfo.clanID = rand()%90+2;
		}
		*/

		if (SType!=0)
		{
			const vector<MonsterType_t>& monsterTypes = g_pMonsterInfoManager->getMonsterTypeBySprite( SType );

			if (!monsterTypes.empty())
			{
				// num 마리의 몬스터 생성
				for (int i=0; i<num; i++)
				{
					MonsterType_t monsterType = monsterTypes[rand()%monsterTypes.size()];

					pMonsterManager->addMonsters(x, y, monsterType, 1, summonInfo, pSummonedMonsters);
				}
			}
		}
		else if (MType!=0)
		{
			pMonsterManager->addMonsters(x, y, MType, num, summonInfo, pSummonedMonsters);
		}
	}
	catch (Throwable& t)
	{
		cerr << t.toString() << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 특정 타입의 몬스터를 존에다 추가한다.
//////////////////////////////////////////////////////////////////////////////
void addMonstersToZone(Zone* pZone, const SUMMON_INFO2& summonInfo, list<Monster*>* pSummonedMonsters) 
	throw()
{
	__BEGIN_TRY

	try
	{
		MonsterCollection* pCollection = summonInfo.pMonsters;

		if (pCollection==NULL)
			return;

		MonsterManager* pMonsterManager = pZone->getMonsterManager();
		Assert(pMonsterManager != NULL);

		/*
		if (summonInfo.clanType == SUMMON_INFO::CLAN_TYPE_RANDOM_GROUP)
		{
			summonInfo.clanID = rand()%90+2;
		}
		*/

		list<MonsterCollectionInfo>& Infos = pCollection->Infos;
		list<MonsterCollectionInfo>::const_iterator itr;
		for (itr=Infos.begin(); itr!=Infos.end(); itr++)
		{
			const MonsterCollectionInfo& monsterInfo = *itr;

			if ( monsterInfo.SpriteType!=0 )
			{
				const vector<MonsterType_t>& monsterTypes = g_pMonsterInfoManager->getMonsterTypeBySprite( monsterInfo.SpriteType );

				if (!monsterTypes.empty())
				{
					// Num 마리의 몬스터 생성
					for (int i=0; i<monsterInfo.Num; i++)
					{
						MonsterType_t monsterType = monsterTypes[rand()%monsterTypes.size()];

						pMonsterManager->addMonsters(summonInfo.X, 
														summonInfo.Y, 
														monsterType,
														1,
														summonInfo,
														pSummonedMonsters);
					}
				}
			}
			else if ( monsterInfo.MonsterType!=0 )
			{
				pMonsterManager->addMonsters(summonInfo.X, 
												summonInfo.Y, 
												monsterInfo.MonsterType,
												monsterInfo.Num,
												summonInfo,
												pSummonedMonsters);
			}
		}
	}
	catch (Throwable& t)
	{
		cerr << t.toString() << endl;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐가 현재 안전 지대 내부에 있는가를 검사하는 함수
// 교환할 때 쓰인다. 
//////////////////////////////////////////////////////////////////////////////
bool isInSafeZone(Creature* pCreature)
{
	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	ZoneLevel_t ZoneLevel = pZone->getZoneLevel(pCreature->getX(), pCreature->getY());

	if (pCreature->isSlayer() && (ZoneLevel & SLAYER_SAFE_ZONE)) return true;
	if (pCreature->isVampire() && (ZoneLevel & VAMPIRE_SAFE_ZONE)) return true;
	if (pCreature->isOusters() && (ZoneLevel & OUSTERS_SAFE_ZONE)) return true;
	if (ZoneLevel & COMPLETE_SAFE_ZONE) return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 좌표가 존의 범위 안인지를 체크한다.
//////////////////////////////////////////////////////////////////////////////
bool isValidZoneCoord(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, int offset)
{
	Assert(pZone != NULL);

	VSRect rect;
	rect.left   = 0 + offset;
	rect.top    = 0 + offset;
	rect.right  = pZone->getWidth() - offset - 1;
	rect.bottom = pZone->getHeight() - offset - 1;

	if (rect.ptInRect(x, y)) return true;

	return false;
}

bool enterMasterLair(Zone* pZone, Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY

	if (pZone==NULL || pCreature==NULL)
		return false;

	// 마스터 레어가 아니면 체크할 필요가 없는거다.
	if (!pZone->isMasterLair())
	{
		return true;
	}

	MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
	Assert(pMasterLairManager!=NULL);

	if (pMasterLairManager->enterCreature( pCreature ))
	{
		// 출입 가능
		return true;
	}

	__END_CATCH

	return false;
}

void
getNewbieTransportZoneInfo(Slayer* pSlayer, ZONE_COORD& zoneInfo)
{
	// 능력치 합이 40이고, 야전사령부이면 딴데로 보낸다.  by sigi. 2002.11.7
	zoneInfo.x = 30;
	zoneInfo.y = 42;

	switch (pSlayer->getHighestSkillDomain())
	{
		case SKILL_DOMAIN_HEAL :
		case SKILL_DOMAIN_ENCHANT :
			zoneInfo.id = 2010;
		break;

		case SKILL_DOMAIN_GUN :
			zoneInfo.id = 2000;
		break;

		//case SKILL_DOMAIN_SWORD :
		//case SKILL_DOMAIN_BLADE :
		default :
			zoneInfo.id = 2020;
		break;
	}
}


void
checkNewbieTransportToGuild(Slayer* pSlayer)
{
	try
	{
		if (pSlayer->isPLAYER()
			&& g_pVariableManager->isNewbieTransportToGuild())
		{
			// 능력치 합이 40이고, 야전사령부이면 딴데로 보낸다.  by sigi. 2002.11.7
			ZONE_COORD transportZone;

			getNewbieTransportZoneInfo(pSlayer, transportZone);

			ZoneID_t zoneID = pSlayer->getZone()->getZoneID();
			if (zoneID==2101)// || zoneID==2102)
			{
				Attr_t BasicSUM = pSlayer->getSTR(ATTR_BASIC)
								+ pSlayer->getDEX(ATTR_BASIC)
								+ pSlayer->getINT(ATTR_BASIC);

				if (BasicSUM>=39)
				{
					GCSystemMessage gcSystemMessage;
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NEWBIE_TRANSPORT_TO_GUILD ) );
					pSlayer->getPlayer()->sendPacket( &gcSystemMessage );
				}

				//else 
					if (BasicSUM>=40)
				{
					Player* pPlayer = pSlayer->getPlayer();
					Assert(pPlayer!=NULL);

					GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
					Event* pEvent = pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT);

					if (pEvent==NULL)
					{
						ZoneID_t ZoneID;
						ZoneCoord_t ZoneX = 30, ZoneY = 42;
						string ZoneName;

						switch (pSlayer->getHighestSkillDomain())
						{
							case SKILL_DOMAIN_HEAL :
							case SKILL_DOMAIN_ENCHANT :
								ZoneID = 2010;
								ZoneName = g_pStringPool->getString( STRID_CLERIC_GUILD );
							break;

							case SKILL_DOMAIN_GUN :
								ZoneID = 2000;
								ZoneName = g_pStringPool->getString( STRID_SOLDIER_GUILD );
							break;

							//case SKILL_DOMAIN_SWORD :
							//case SKILL_DOMAIN_BLADE :
							default :
								ZoneID = 2020;
								ZoneName = g_pStringPool->getString( STRID_KNIGHT_GUILD );
							break;
						}


						//transportCreature( pSlayer, ZoneID, ZoneX, ZoneY, false );

						Turn_t deadline = 600;	// 1분 후
						int timePenalty = (BasicSUM-40)*100;	// 능력치 1마다 10초씩
						deadline -= min(500, timePenalty);

						/*
						EffectTransportCreature* pEffect = new EffectTransportCreature(
															pSlayer, ZoneID, ZoneX, ZoneY, deadline);
						pEffect->setMessageTick(100);
						pEffect->setZoneName(ZoneName);

						Zone* pZone = pSlayer->getZone();
						Assert(pZone!=NULL);

						// CreatureManager 처리 중에 실행되기 때문에 Zone에 붙여야한다. 
						//pSlayer->addEffect( pEffect );

						ObjectRegistry & objectregister = pZone->getObjectRegistry();
						objectregister.registerObject(pEffect);
						pZone->addEffect(pEffect);
						*/

						Player* pPlayer = pSlayer->getPlayer();
						Assert(pPlayer != NULL);

						GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

						//pGamePlayer->deleteEvent(Event::EVENT_CLASS_TRANSPORT);

						EventTransport* pEventTransport = new EventTransport(pGamePlayer);

						pEventTransport->setDeadline(deadline);
						pEventTransport->setTargetZone(ZoneID, ZoneX, ZoneY);
						pEventTransport->setZoneName(ZoneName);

						// 몇 초후에 어디로 이동한다.고 보내준다.
						pEventTransport->sendMessage();

						pGamePlayer->addEvent(pEventTransport);
					}
					else
					{
						EventTransport* pEventTransport = dynamic_cast<EventTransport*>(pEvent);
						pEventTransport->sendMessage();
					}
				}
			}
		}
	} catch (Throwable& t) {
		filelog("newbieTransportBUG.log", "%s", t.toString().c_str());
	}
}

// Corpse가 
bool
addCorpseToZone(Corpse* pCorpse, Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCorpse!=NULL);
	Assert(pZone!=NULL);

	// 타일과 몬스터 매니저에서 크리처를 삭제한다.
//	Tile & tile = pZone->getTile(cx , cy);

	// 시체를 타일에 추가한다. 
/*	// 현재 타일에 아이템이 존재한다면, 
	if (tile.hasItem())
	{
		Item* pItem = tile.getItem();
		Assert(pItem != NULL);
		
		switch (pItem->getItemClass())
		{
			// 시체에 들어가지 않는 아이템 클래스
			case Item::ITEM_CLASS_CORPSE:
			case Item::ITEM_CLASS_MOTORCYCLE:
			case Item::ITEM_CLASS_MINE:
			case Item::ITEM_CLASS_MONEY:
			case Item::ITEM_CLASS_RELIC:
			case Item::ITEM_CLASS_BLOOD_BIBLE:
			case Item::ITEM_CLASS_CASTLE_SYMBOL:
			case Item::ITEM_CLASS_SWEEPER:
				break;

			default:
				// 이미 생성된 유니크 아이템은 시체에 들어가지 않으므로
				// 유니크 아이템이 아니라면 시체에 추가한다.
                if (!pItem->isUnique() && !pItem->isQuestItem() && !pItem->isFlagItem() && !pItem->isFlag( Effect::EFFECT_CLASS_PET_DISSECT ) )
				{
					// 바닥에 떨어져있다가 얼떨결에 들어가는 아이템은 다시 나올때도 우선권을 붙여줘선 안된다.
					if ( !pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE) )
					{
						EffectPrecedence* pEffect = new EffectPrecedence( pItem );
						pEffect->setHostName("");
						pEffect->setHostPartyID(0);
						pEffect->setDeadline(0);

						pItem->getEffectManager().addEffect(pEffect);
						pItem->setFlag( Effect::EFFECT_CLASS_PRECEDENCE );
					}
					pZone->deleteItem(pItem, cx, cy);

					// 시체에서 꺼낼때 create 하므로 DB에서 지워줘야 한다.
					// 나중에 최적화 할때는 다른 방법을 쓰도록..
					pItem->destroy();
					pCorpse->addTreasure(pItem);
				}
				break;
		}
	}*/

	// 시체를 추가한다.
	TPOINT pt = pZone->addItem(pCorpse, cx, cy);
	if (pt.x == -1) 
	{
		SAFE_DELETE(pCorpse);
		return false;
	}

	pCorpse->setX( pt.x );
	pCorpse->setY( pt.y );
	pCorpse->setZone( pZone );

	__END_CATCH

	return true;

}

// 범위 안에 특정한 몬스터 시체가 있는지 확인한다. 
// 있으면 true, 없으면 false
bool checkCorpse( Zone* pZone, MonsterType_t MType, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2 )
	throw()
{
	__BEGIN_TRY
	
	x1 = max ( 0, (int)x1 );
	y1 = max ( 0, (int)y1 );
	x2 = min ( pZone->getWidth()-1, (int)x2 );
	y2 = min ( pZone->getHeight()-1, (int)y2 );

	//Assert( x1 <= x2 && y1 <= y2 );
	// by sigi. 2002.12.25
	if (!isValidZoneCoord(pZone, x1, y1)
		|| !isValidZoneCoord(pZone, x2, y2))
	{
		return false;
	}

	ZoneCoord_t ix, iy;

	for ( ix = x1; ix <= x2; ix++ )
	{
		for ( iy = y1; iy <= y2; iy++ )
		{
			Tile& curTile = pZone->getTile( ix, iy );
			Item* pItem = curTile.getItem();

			if (pItem!=NULL
				&& pItem->getItemClass() == Item::ITEM_CLASS_CORPSE 
				&& pItem->getItemType() == MONSTER_CORPSE )
			{
				MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
				if ( pMonsterCorpse->getMonsterType() == MType )
				{
					return true;
				}
			}
		}
	}

	return false;

	__END_CATCH
}

// 몇개의 Zone 에만 메세지를 뿌리기 위해서 성에 속한 ZoneIDList가 필요함
void makeZoneIDList(const string& zoneIDs, list<ZoneID_t>& zoneIDList ) 
	throw(Error)
{

	__BEGIN_TRY

    uint a = 0, b = 0;

    //////////////////////////////////////////////
    // 12345,67890,
    // a    ba    b
    //////////////////////////////////////////////
    zoneIDList.clear();
    if (zoneIDs.size()<=1) return;

    do
    {
        b = zoneIDs.find_first_of(',', a);

        string zoneID = trim( zoneIDs.substr(a, b-a) );

		// 음 -_- 그냥 atoi 써도 될려나 ;;
        zoneIDList.push_back( atoi( zoneID.c_str() ) );

        a = b+1;

    } while (b!=string::npos && b < zoneIDs.size() -1);

	__END_CATCH

}

uint getZoneTimeband( Zone* pZone )
{
	if ( pZone == NULL )
	{
		return g_pTimeManager->getTimeband();
	}
	
	return pZone->getTimeband();
}

bool createBulletinBoard( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, MonsterType_t type, const string& msg, const VSDateTime& timeLimit )
{
	__BEGIN_TRY

	if (
		pZone->isMasterLair()
		|| checkCorpse( pZone, type, X-2, Y-2, X+2, Y+2 )
	)
		return false;

	MonsterCorpse* pCorpse = new MonsterCorpse( type, msg, 2 );
	Assert( pCorpse != NULL );

	pZone->registerObject( pCorpse );

	int delayTime = VSDateTime::currentDateTime().secsTo( timeLimit );
	TPOINT pt = pZone->addItem( pCorpse, X, Y, true, delayTime * 10 );

	if ( pt.x == -1 )
	{
		SAFE_DELETE( pCorpse );
		return false;
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		string dbmsg = correctString( msg );
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"INSERT INTO BulletinBoardObject VALUES (0, %u, %u, %u, %u, '%s', %u, '%s')",
					g_pConfig->getPropertyInt("ServerID"), pZone->getZoneID(), pt.x, pt.y, dbmsg.c_str(), (uint)type, timeLimit.toDateTime().c_str() );

		// UPDATE인 경우는 Result* 대신에.. pStmt->getAffectedRowCount()

		if ( pStmt->getAffectedRowCount() == 0 )
		{
			filelog( "BulletinBoard.log", "DB에 저장이 안되버렸습니다. : %u, %u, %u, [%u:%s]", pZone->getZoneID(), pt.x, pt.y, type, msg.c_str() );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return true;

	__END_CATCH
}

void loadBulletinBoard( Zone* pZone )
{
	__BEGIN_TRY

	VSDateTime currentDateTime = VSDateTime::currentDateTime();

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT ID, X, Y, Message, Type, TimeLimit FROM BulletinBoardObject WHERE ServerID = %u AND ZoneID = %u",
				g_pConfig->getPropertyInt("ServerID"), pZone->getZoneID() );

		// UPDATE인 경우는 Result* 대신에.. pStmt->getAffectedRowCount()

		while (pResult->next()) 
		{
			uint ID = pResult->getInt( 1 );
			ZoneCoord_t X = pResult->getInt(2);
			ZoneCoord_t Y = pResult->getInt(3);
			string msg = pResult->getString(4);
			MonsterType_t type = pResult->getInt(5);
			VSDateTime timeLimit(pResult->getString(6));

			if ( timeLimit < currentDateTime )
			{
				cout << "게시판 시간 다되서 지워버립니다." << ID << " : [" << X << "," << Y << "] " << msg << " [" << type << "] " << endl;
				Statement* pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt2->executeQuery("DELETE FROM BulletinBoardObject WHERE ID = %u", ID);
				continue;
			}

			int delayTime = currentDateTime.secsTo( timeLimit );

			MonsterCorpse* pCorpse = new MonsterCorpse( type, msg, 2 );
			Assert( pCorpse != NULL );

			pZone->registerObject( pCorpse );

			TPOINT pt = pZone->addItem( pCorpse, X, Y, true, delayTime * 10 );

			if ( pt.x == -1 )
			{
				filelog( "BulletinBoard.log", "DB에서 읽었는데 존에 안들어가버렸습니다. : %u, %u, %u, [%u:%s]", pZone->getZoneID(), X, Y, type, msg.c_str() );
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void forbidDarkness( Zone* pZone, ZoneCoord_t tX, ZoneCoord_t tY, int range )
{
	for ( int ti=-range; ti<=range; ++ti )
	for ( int tj=-range; tj<=range; ++tj )
	{
		ZoneCoord_t X = tX+ti;
		ZoneCoord_t Y = tY+tj;

		if ( !isValidZoneCoord( pZone, X, Y ) ) continue;

		Tile& rTile = pZone->getTile( X, Y );
		if ( !rTile.canAddEffect() || rTile.getEffect( Effect::EFFECT_CLASS_DARKNESS_FORBIDDEN ) != NULL ) continue;

		EffectDarknessForbidden* pEffect = new EffectDarknessForbidden( pZone, X, Y );
		pZone->registerObject( pEffect );
		rTile.addEffect( pEffect );
	}
}
