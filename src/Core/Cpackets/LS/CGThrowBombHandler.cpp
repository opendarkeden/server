//////////////////////////////////////////////////////////////////////////////
// Filename    : CGThrowBombHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGThrowBomb.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "ZoneUtil.h"
	#include "SkillUtil.h"
	#include "ItemUtil.h"
	#include <list>

	#include "item/Bomb.h"
	#include "skill/Sniping.h"

	#include "Gpackets/GCThrowBombOK1.h"
	#include "Gpackets/GCThrowBombOK2.h"
	#include "Gpackets/GCThrowBombOK3.h"
	#include "Gpackets/GCSkillFailed1.h"
	#include "Gpackets/GCSkillFailed2.h"
	#include "Gpackets/GCStatusCurrentHP.h"
#endif	// __GAME_SERVER__

#ifdef __GAME_SERVER__

// 타입
// 방향
// 마스크
int BombMask[5][9][9] =
{
	// 0번 타입 폭탄
	{
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	// 1번 타입 폭탄
	{
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	// 2번 타입 폭탄
	{
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 100, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	// 3번 타입 폭탄
	{
		{ 0, 50, 0, 0, 100, 0, 0, 50, 0 },
		{ 50, 0, 0, 0, 100, 0, 0, 0, 50 },
		{ 0, 0, 0, 50, 100, 50, 0, 0, 0 },
		{ 0, 0, 50, 0, 100, 0, 50, 0, 0 },
		{ 0, 50, 0, 0, 100, 0, 0, 50, 0 },
		{ 50, 0, 0, 0, 100, 0, 0, 0, 50 },
		{ 0, 0, 0, 50, 100, 50, 0, 0, 0 },
		{ 0, 0, 50, 0, 100, 0, 50, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	// 4번 타입 폭탄
	{
		{ 0, 50, 0, 50, 100, 50, 0, 50, 0 },
		{ 50, 0, 50, 0, 100, 0, 50, 0, 50 },
		{ 0, 50, 0, 50, 100, 50, 0, 50, 0 },
		{ 50, 0, 50, 0, 100, 0, 50, 0, 50 },
		{ 0, 50, 0, 50, 100, 50, 0, 50, 0 },
		{ 50, 0, 50, 0, 100, 0, 50, 0, 50 },
		{ 0, 50, 0, 50, 100, 50, 0, 50, 0 },
		{ 50, 0, 50, 0, 100, 0, 50, 0, 50 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	}
};

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGThrowBombHandler::execute(CGThrowBomb* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 게임 플레이어의 상태가 정상이 아니라면 걍 리턴한다.
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	// 플레이어가 슬레이어가 아니라면 걍 리턴한다.
	if (!pCreature->isSlayer()) return;

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	int ZoneX = pPacket->getZoneX();
	int ZoneY = pPacket->getZoneY();
	int BombX = pPacket->getBombX();
	int BombY = pPacket->getBombY();

	Inventory* pInventory = pSlayer->getInventory();
	Assert(pInventory != NULL);


	// 완전 안전지대라면 기술 사용 불가. by sigi. 2002.11.14
	ZoneLevel_t ZoneLevel = pZone->getZoneLevel(pSlayer->getX(), pSlayer->getY());
	if ((ZoneLevel & COMPLETE_SAFE_ZONE)
		|| (BombX >= pInventory->getWidth() || BombY >= pInventory->getHeight()))
	{
		GCSkillFailed1 _GCSkillFailed1;
		_GCSkillFailed1.setSkillType(SKILL_THROW_BOMB);
		pPlayer->sendPacket(&_GCSkillFailed1);
		return;
	}

	ObjectID_t slayerObjectID = pCreature->getObjectID();

	bool bAttackSlayer = (pPacket->getAttackSlayerFlag() != 0) ? true : false;

	try
	{
		if (pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
		{
			g_Sniping.checkRevealRatio(pCreature, 20, 10);
		}

		Item* pItem = pInventory->getItem(BombX, BombY);
		
		// 아이템이 널이거나 폭탄이 아니라면...
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_BOMB)
		{
			GCSkillFailed1 _GCSkillFailed1;
			//_GCSkillFailed1.setSkillType(SKILL_THROW_BOMB);
			pPlayer->sendPacket(&_GCSkillFailed1);
			return;
		}

		/*
		// 6은 임의의 사정 거리다...
		// 사정 거리보다 멀리 던지려고 하면, 어떻게 하는 것이 좋을까?
		if (!verifyDistance(pSlayer, ZoneX, ZoneY, 6))
		{
			GCSkillFailed1 _GCSkillFailed1;
			//_GCSkillFailed1.setSkillType(SKILL_THROW_BOMB);
			pPlayer->sendPacket(&_GCSkillFailed1);
			return;
		}
		*/

		// 폭탄의 각종 정보를 얻어온다.
		Bomb* pBomb = dynamic_cast<Bomb*>(pItem);
		ItemType_t BombType = pBomb->getItemType();
		Damage_t MinDamage = pBomb->getMinDamage();
		Damage_t MaxDamage = pBomb->getMaxDamage();
		SkillSlot * pSkillSlot = pSlayer->hasSkill(SKILL_THROW_BOMB);
		SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo(SKILL_THROW_BOMB);
		Level_t SkillLevel = pSkillSlot->getExpLevel();
		Damage_t RealDamage = MinDamage + ( max ( 0, ( (int)MaxDamage * (int)SkillLevel / 100 ) - MinDamage ) );

		// 사용자의 위치와 던질 곳의 위치로 방향을 계산한다.
		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();
		Dir_t dir = calcDirection(myX, myY, ZoneX, ZoneY);
		int count = 0;
		bool bHit = false;
		bool bRaceCheck = true;;

		list<Creature*> cList;
		GCThrowBombOK1 _GCThrowBombOK1;
		GCThrowBombOK2 _GCThrowBombOK2;
		GCThrowBombOK3 _GCThrowBombOK3;

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, ZoneX, ZoneY, 6);

		// 맞든 맞지 않았든 폭탄의 숫자는 줄여주어야 한다.
		decreaseItemNum(pBomb, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, BombX, BombY);

		if( bManaCheck && bTimeCheck && bRangeCheck ) {
		} else {
			GCSkillFailed1 _GCSkillFailed1;
			//_GCSkillFailed1.setSkillType(SKILL_THROW_BOMB);
			pPlayer->sendPacket(&_GCSkillFailed1);
			return;
		}

		decreaseMana(pSlayer, RequiredMP, _GCThrowBombOK1);

		// 각각의 타일을 돌면서 히트 체크를 한다.
		for (int tileY = ZoneY-1; tileY <= ZoneY+1; tileY++)
		{
			for (int tileX = ZoneX-1; tileX <= ZoneX+1; tileX++, count++)
			{
				// 올바른 존 좌표가 아니라면, continue
				if (!isValidZoneCoord(pZone, tileX, tileY)) continue;

				// mask가 0이라면, 즉 히트롤을 할 필요가 없다면 continue
				int Mask = BombMask[BombType][dir][count];
				if (Mask == 0) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				checkMine( pZone, tileX, tileY );
				
				list<Creature*> targetList;
				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

					// NoSuch제거. by sigi. 2002.5.2
					if (pCreature!=NULL && !pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
						targetList.push_back(pCreature);
				}
				if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);

					// NoSuch제거. by sigi. 2002.5.2
					if (pCreature!=NULL && !pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
						targetList.push_back(pCreature);
				}

				list<Creature*>::iterator itr = targetList.begin();
				for(; itr != targetList.end(); itr++)
				{
					Creature* pTargetCreature = (*itr);
					Assert(pTargetCreature != NULL);

					bool bHitRoll = true;
					if (pTargetCreature->isSlayer() && !bAttackSlayer) bHitRoll = false;
					else if (pTargetCreature->isNPC()) bHitRoll = false;

					if ( !canAttack( pSlayer, pTargetCreature ) ) continue;

					if (!bHitRoll) continue;
					bool bPK         = verifyPK(pSlayer, pTargetCreature);
					bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

					// 사용자가 타겟이라면 경험치를 안올릴려구 노력 한다.
					// 몸빵이 생겨날 수 있기 때문이다.
					if( tileX == ZoneX && tileY == ZoneY ) {
						if( pTargetCreature->isSlayer() ) {
							bRaceCheck      = false;
						}
					}

					if (HitRoll::isSuccess(pSlayer, pTargetCreature, 50) && bPK && bZoneLevelCheck )
					{

						Damage_t Damage = getPercentValue(RealDamage, Mask);
						setDamage(pTargetCreature, Damage, pSlayer, 0, NULL, &_GCThrowBombOK1);
						computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCThrowBombOK1);
						increaseAlignment(pSlayer, pTargetCreature, _GCThrowBombOK1);

						bHit = true;

						cList.push_back(pTargetCreature);
						ObjectID_t targetObjectID = pTargetCreature->getObjectID();
						_GCThrowBombOK1.addCListElement(targetObjectID);
						_GCThrowBombOK2.addCListElement(targetObjectID);
						_GCThrowBombOK3.addCListElement(targetObjectID);

				
					}
				}
			}
		} // for (int tileY = ZoneY-1; tileY <= ZoneY+1; tileY++)

		// 모든 타일 체크가 끝났으니, 경험치를 약간 올리고, 아이템 숫자를 줄여준다.
		if (bHit && bRaceCheck )
		{

			shareAttrExp(pSlayer, RealDamage, 1, 8, 1, _GCThrowBombOK1);
			increaseDomainExp(pSlayer, SKILL_DOMAIN_GUN, pSkillInfo->getPoint(), _GCThrowBombOK1);
			
			// 스킬을 사용할 수 있을 때만 스킬 경험치를 올려준다.
			// 2003. 1. 12 by bezz
			if ( pSkillSlot->canUse() )
				increaseSkillExp(pSlayer, SKILL_DOMAIN_GUN, pSkillSlot, pSkillInfo, _GCThrowBombOK1);
//			increaseAlignment(pSlayer, SKILL_DOMAIN_GUN, _GCThrowBombOK1);
			//shareAttrExp(pSlayer, RealDamage, 1, 8, 1, _GCSkillToTileOK1);
			// 이 부분에서 패킷을 보내줘야 하는데..
		}

		_GCThrowBombOK1.setXYDir(ZoneX, ZoneY, dir);
		_GCThrowBombOK1.setItemType(BombType);
		_GCThrowBombOK2.setXYDir(ZoneX, ZoneY, dir);
		_GCThrowBombOK2.setObjectID(slayerObjectID);
		_GCThrowBombOK2.setItemType(BombType);
		_GCThrowBombOK3.setXYDir(ZoneX, ZoneY, dir);
		_GCThrowBombOK3.setObjectID(slayerObjectID);
		_GCThrowBombOK3.setItemType(BombType);

		for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
		{
			Creature* pTargetCreature = *itr;
			_GCThrowBombOK2.clearList();

			HP_t targetHP = 0;
			if (pTargetCreature->isSlayer())
			{
				targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP();
			}
			else if (pTargetCreature->isVampire())
			{
				targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP();
			}
			else if (pTargetCreature->isOusters())
			{
				targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP();
			}

			_GCThrowBombOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

			// 아이템의 내구력을 떨어뜨린다.
			decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCThrowBombOK2);


			if (pTargetCreature->isPC())
			{
				pTargetCreature->getPlayer()->sendPacket(&_GCThrowBombOK2);
			}
		}

		pPlayer->sendPacket(&_GCThrowBombOK1);

		cList.push_back(pSlayer);

		pZone->broadcastPacket(ZoneX, ZoneY, &_GCThrowBombOK3, cList);
	}
	catch (Throwable& t)
	{
		GCSkillFailed1 _GCSkillFailed1;
		GCSkillFailed2 failpkt2;

		failpkt2.setObjectID(slayerObjectID);
		failpkt2.setSkillType(SKILL_THROW_BOMB); 
		pZone->broadcastPacket(ZoneX, ZoneY, &failpkt2, pSlayer);

		pPlayer->sendPacket(&_GCSkillFailed1);
	}


#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
