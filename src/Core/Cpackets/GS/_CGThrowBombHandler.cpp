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

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	int ZoneX = pPacket->getZoneX();
	int ZoneY = pPacket->getZoneY();
	int BombX = pPacket->getBombX();
	int BombY = pPacket->getBombY();
	bool bAttackSlayer = (pPacket->getAttackSlayerFlag() != 0) ? true : false;

	try
	{
		if (pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
		{
			g_Sniping.checkRevealRatio(pCreature, 20, 10);
		}

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Inventory* pInventory = pSlayer->getInventory();
		Item* pItem = pInventory->getItem(BombX, BombY);
		
		// 아이템이 널이거나 폭탄이 아니라면...
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_BOMB)
		{
			GCSkillFailed1 _GCSkillFailed1;
			//_GCSkillFailed1.setSkillType(SKILL_THROW_BOMB);
			pPlayer->sendPacket(&_GCSkillFailed1);
			return;
		}

		// 6은 임의의 사정 거리다...
		// 사정 거리보다 멀리 던지려고 하면, 어떻게 하는 것이 좋을까?
		if (!verifyDistance(pSlayer, ZoneX, ZoneY, 6))
		{
			GCSkillFailed1 _GCSkillFailed1;
			//_GCSkillFailed1.setSkillType(SKILL_THROW_BOMB);
			pPlayer->sendPacket(&_GCSkillFailed1);
			return;
		}

		// 폭탄의 각종 정보를 얻어온다.
		Bomb* pBomb = dynamic_cast<Bomb*>(pItem);
		ItemType_t BombType = pBomb->getItemType();
		Damage_t MinDamage = pBomb->getMinDamage();
		Damage_t MaxDamage = pBomb->getMaxDamage();
		Damage_t RealDamage = max(1, Random(MinDamage, MaxDamage)) + pSlayer->getDEX(ATTR_CURRENT)/10;

		// 사용자의 위치와 던질 곳의 위치로 방향을 계산한다.
		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();
		Dir_t dir = calcDirection(myX, myY, ZoneX, ZoneY);
		int count = 0;
		bool bHit = false;

		list<Creature*> cList;
		GCThrowBombOK1 _GCThrowBombOK1;
		GCThrowBombOK2 _GCThrowBombOK2;
		GCThrowBombOK3 _GCThrowBombOK3;

		// 맞든 맞지 않았든 폭탄의 숫자는 줄여주어야 한다.
		decreaseItemNum(pBomb, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, BombX, BombY);

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
				
				list<Creature*> targetList;
				if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					targetList.push_back(pCreature);
				}
				if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
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

					if (!bHitRoll) continue;

					if (HitRoll::isSuccess(pSlayer, pTargetCreature, 0))
					{
						Damage_t Damage = getPercentValue(RealDamage, Mask);

						//setDamage(pTargetCreature, Damage, pSlayer, param.SkillType, NULL, &_GCSkillToTileOK1);
						//setDamage(pTargetCreature, Damage, pSlayer, 0, NULL, &_GCSkillToTileOK1);
						//computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

						//increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

						bHit = true;

						cList.push_back(pTargetCreature);
					}
				}
			}
		} // for (int tileY = ZoneY-1; tileY <= ZoneY+1; tileY++)

		// 모든 타일 체크가 끝났으니, 경험치를 약간 올리고, 아이템 숫자를 줄여준다.
		if (bHit)
		{
			//shareAttrExp(pSlayer, RealDamage, 1, 8, 1, _GCSkillToTileOK1);
		}

		// 이 부분에서 패킷을 보내줘야 하는데..
	}
	catch (Throwable& t)
	{
	}


	/*
	try 
	{
		ObjectID_t slayerObjectID = pSlayer->getObjectID();

		ZoneCoord_t slayerX = pSlayer->getX(), slayerY = pSlayer->getY();
		// 명중 되었다면, 데미지를 준다..
		if (ToHit > Random(0, 100))
		{
			int explosionType = 0;
			switch(itemType)
			{
				case 0://ACER
					explosionType = 0;
					break;
				case 1://Bulls
					explosionType = 0;
					break;
				case 2://Cyclone
					explosionType = 1;
					break;
				case 3://Pylone
					explosionType = 2;
					break;
				case 4://Crossbow
					explosionType = 1;
					break;
				case 5://Twister
					explosionType = 3;
					break;
			}

			Dir_t Dir = calcDirection(slayerX, slayerY, X, Y);
			int tileX, tileY;

			const int* xOffsetEType = NULL, *yOffsetEType = NULL;
			int tiles = 0;
			getExplosionTypeXYOffset(explosionType, Dir, xOffsetEType, yOffsetEType, tiles);
			
			for(int tileI = 0; tileI < tiles; tileI++)
			{
				tileX = X + xOffsetEType[ tileI];
				tileY = Y + yOffsetEType[ tileI];
				
				if (isValidZoneCoord(pZone, tileX, tileY) && pZone->getZoneLevel(tileX, tileY)) 
				{
					Tile& tile = pZone->getTile(tileX, tileY);

					const slist<Object*>& oList = tile.getObjectList();
					// tile위의 모든 오브젝트에 대해서 조사를 한다.
					for(slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++)
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
							}	
							else if (pTargetCreature->isVampire()) 
							{
								//Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
								cList.push_back(pTargetCreature);
							} 
							else if (pTargetCreature->isMonster()) 
							{
								//Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
								cList.push_back(pTargetCreature);
							}
							else
								continue;

							ObjectID_t targetObjectID = pTargetCreature->getObjectID();
							_GCThrowBombOK1.addCListElement(targetObjectID);
							_GCThrowBombOK2.addCListElement(targetObjectID);
							_GCThrowBombOK3.addCListElement(targetObjectID);

						}
					}
				}
			}

			_GCThrowBombOK1.setXYDir(X, Y, Dir);
			_GCThrowBombOK1.setItemType(itemType);
			_GCThrowBombOK2.setXYDir(X, Y, Dir);
			_GCThrowBombOK2.setObjectID(slayerObjectID);
			_GCThrowBombOK2.setItemType(itemType);
			_GCThrowBombOK3.setXYDir(X, Y, Dir);
			_GCThrowBombOK3.setObjectID(slayerObjectID);
			_GCThrowBombOK3.setItemType(itemType);

			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				_GCThrowBombOK2.clearList();
				setDamage(pTargetCreature, Damage, NULL, 0, &_GCThrowBombOK2);
				if (pTargetCreature->isPC())
				{
					pTargetCreature->getPlayer()->sendPacket(&_GCThrowBombOK2);
				}
			}

			pPlayer->sendPacket(&_GCThrowBombOK1);

			cList.push_back(pSlayer);

			pZone->broadcastPacket(slayerX, slayerY, &_GCThrowBombOK3, cList);

		}
		else // 던지기에 실패했을 경우...
		{
			GCSkillFailed1 _GCSkillFailed1;
			GCSkillFailed2 failpkt2;

			failpkt2.setObjectID(slayerObjectID);
			failpkt2.setSkillType(SKILL_INVISIBILITY+19); 
			pZone->broadcastPacket(slayerX, slayerY, &failpkt2, pSlayer);

			pPlayer->sendPacket(&_GCSkillFailed1);
		}

		pInventory->deleteItem(bombObjectID);
		pBomb->destroy();
		SAFE_DELETE(pBomb);
	} 
	catch (Throwable & t) 
	{ 
		//cout << t.toString() << endl; 
	}
	*/

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
