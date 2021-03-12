//////////////////////////////////////////////////////////////////////////////
// Filename    : AbsorbSoul.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "AbsorbSoul.h"

#include "item/Larva.h"
#include "item/Pupa.h"
#include "Corpse.h"
#include "OustersCorpse.h"
#include "PCOustersInfo3.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"
#include "Properties.h"
#include "GQuestManager.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillFailed1.h"

//////////////////////////////////////////////////////////////////////////////
// 아우스터스 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
// 스킬의 결과를 2번 날려줘야 된다.
// 라바 만들기에 대한 것 하나 하고
// 흡영에 관한 것 하나.
// 그래서 처음에 조건 체크하다가 실패할 경우에
// SkillFail 패킷을 2번 보내준다.
// ///////////////////////////////////////////////////////////////////////////
void AbsorbSoul::execute(Ousters* pOusters, ObjectID_t TargetObjectID, ZoneCoord_t TargetZoneX, ZoneCoord_t TargetZoneY, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY, CoordInven_t TargetInvenX, CoordInven_t TargetInvenY )
	
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	// 클라이언트에 락이 걸려있으면 검증 패킷을 2번 보내줘야 된다.
	bool bClientLocked = InvenX != 255;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 죽은 시체가 Creature 일 수도 있고 Item 일 수도 있다.. 
		Item* pTargetItem = pZone->getItem(TargetObjectID);
		Creature* pTargetCreature = NULL;

		if ( pTargetItem == NULL )
		{
			pTargetCreature = pZone->getCreature(TargetObjectID);
		}

		if (pTargetCreature == NULL && pTargetItem == NULL)
		{
			executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
			return;
		}
		// NPC는 공격할 수가 없다.
		// 무적상태 체크. by sigi.2002.9.5
		// 안 죽은 애는 영 빨 수 없다. by Sequoia.2003. 3. 20
		if ( pTargetCreature != NULL )
		{
			if ( pTargetCreature->isNPC()
				|| !canAttack( pOusters, pTargetCreature )
				|| !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)
			)
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
				return;
			}
			if ( pTargetCreature->isFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL) )
			{
				//
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, true, bClientLocked);
				return;
			}
		}
		else if ( pTargetItem != NULL )
		{
			if ( pTargetItem->getItemClass() != Item::ITEM_CLASS_CORPSE )
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
				return;
			}
			if ( pTargetItem->isFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL) )
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, true, bClientLocked);
				return;
			}
		}
		else 
		{
			executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		//bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, 2);

		// 타 종족의 시체에 흡영을 한 경우 (아직 시체가 Creature 인 경우)
		if ( pTargetCreature != NULL ) //&& bRangeCheck)
		{
			int targetLevel = 0;
			if (pTargetCreature->isSlayer())
			{
				Slayer* pTargetSlayer  = dynamic_cast<Slayer*>(pTargetCreature);
				targetLevel = pTargetSlayer->getHighestSkillDomainLevel();
			}
			else if (pTargetCreature->isVampire()) 
			{
				Vampire* pTargetVampire  = dynamic_cast<Vampire*>(pTargetCreature);
				targetLevel = pTargetVampire->getLevel();
			}
			else if (pTargetCreature->isOusters()) 
			{
				Ousters* pTargetOusters  = dynamic_cast<Ousters*>(pTargetCreature);
				targetLevel = pTargetOusters->getLevel();
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				targetLevel = pMonster->getLevel();
			}
			
			// 푸파 만들기에 대한 처리가 먼저 되어야 한다.
			// 라바를 푸파로 만들어줘야 한다
			// 따로 함수로 때서 밑에서 구현 할 것임
			// SkillOK를 보내기 전에 아이템에 대한 처리 패킷을 먼저 보내야 한다. 반!드!시!
			if ( InvenX != 255 ) makeLarvaToPupa( pOusters, targetLevel, ItemObjectID, InvenX, InvenY, TargetInvenX, TargetInvenY );

			// 흡영에 대한 경험치는?? - 나중에 수정 ??
//			Exp_t Exp = computeCreatureExp(pTargetCreature, BLOODDRAIN_EXP);

			// 흡영을 하게 되면 흡영한 사람의 EP가 올라간다.
			// 올라가는 양은 Creature Exp에 비례한다.
			MP_t CurrentMP = pOusters->getMP();
			MP_t MaxMP	   = pOusters->getMP(ATTR_MAX);
			MP_t HealPoint = 0;

			if ( CurrentMP < MaxMP )
			{
				HealPoint = computeCreatureExp(pTargetCreature, 60);
			}
			else
			{
				//MP_t ExtraMP = CurrentMP - MaxMP;
				float ExtraMP = (float)(CurrentMP - MaxMP) / (float)(MaxMP*2) * 100;
				float ftemp = 1.1 - ( (float)ExtraMP / ((float)ExtraMP+10.0) );
				int ratio = (int)(ftemp * 100);
//				cout << "AbsorbSoul : " << ratio << endl;
				HealPoint = computeCreatureExp(pTargetCreature, ratio);
			}

			MP_t NewMP     = min((int)MaxMP*3 , (int)CurrentMP + (int)HealPoint);

//			cout << NewMP << endl;
			// 아우스터즈의 MP를 세팅한다.
			pOusters->setMP(NewMP);
//			cout << pOusters->getMP(ATTR_CURRENT) << endl;

            GCModifyInformation gcMI;
            gcMI.addShortData( MODIFY_CURRENT_MP, pOusters->getMP(ATTR_CURRENT) );

//			cout << gcMI.toString() << endl;

			pOusters->getPlayer()->sendPacket( &gcMI );

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.addCListElement(TargetObjectID);
			_GCSkillToTileOK1.setDuration(0);
			_GCSkillToTileOK1.setX(TargetZoneX);
			_GCSkillToTileOK1.setY(TargetZoneY);
			_GCSkillToTileOK1.setRange(0);

			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.addCListElement(TargetObjectID);
			_GCSkillToTileOK5.setX(TargetZoneX);
			_GCSkillToTileOK5.setY(TargetZoneY);
			_GCSkillToTileOK5.setRange(0);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			if (pTargetCreature != NULL && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();

				if (pTargetPlayer != NULL) 
				{ 
					_GCSkillToTileOK2.setSkillType(getSkillType());
					_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
					_GCSkillToTileOK2.addCListElement(TargetObjectID);
					_GCSkillToTileOK2.setX(TargetZoneX);
					_GCSkillToTileOK2.setY(TargetZoneY);
					_GCSkillToTileOK2.setRange(0);
					_GCSkillToTileOK2.setDuration(0);

					pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pOusters);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToTileOK5 , cList);

			// 아음 -_- 흡영 당한 후에 또 흡영 못하게 막아야 되고
			// 흡영 당한 후에 부활 안 되도록 막아야함
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL);

			pOusters->getGQuestManager()->blooddrain();
		}
		else if ( pTargetItem != NULL ) //&& bRangeCheck)
		{
			Corpse* pTargetCorpse = dynamic_cast<Corpse*>(pTargetItem);

			int targetLevel = 0;
			Exp_t Exp = 0;

			if ( pTargetCorpse->getItemType() == OUSTERS_CORPSE )
			{
				OustersCorpse* pOustersCorpse = dynamic_cast<OustersCorpse*>(pTargetCorpse);
				Assert( pOustersCorpse != NULL );

				if ( pOustersCorpse->getOustersInfo().getName() == pOusters->getName() )
				{
					executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, true, bClientLocked);
					return;
				}
			}

			if ( pTargetCorpse->getItemType() == MONSTER_CORPSE 
				|| pTargetCorpse->getItemType() == SLAYER_CORPSE
				|| pTargetCorpse->getItemType() == VAMPIRE_CORPSE
				|| pTargetCorpse->getItemType() == OUSTERS_CORPSE
			)
			{
				targetLevel = (int)(pTargetCorpse->getLevel());
				Exp = (Exp_t)(pTargetCorpse->getExp());
			}
			else 
			{
				executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
				return;
			}

			// 푸파 만들기에 대한 처리가 먼저 되어야 한다.
			// 라바를 푸파로 만들어줘야 한다
			// 따로 함수로 때서 밑에서 구현 할 것임
			// SkillOK를 보내기 전에 아이템에 대한 처리 패킷을 먼저 보내야 한다. 반!드!시!
			if ( bClientLocked ) makeLarvaToPupa( pOusters, targetLevel, ItemObjectID, InvenX, InvenY, TargetInvenX, TargetInvenY );

			// 흡영을 하게 되면 흡영한 사람의 SP가 올라간다.
			// 이거 어떻게 될지 나중에 더 봐야될듯
			// HealPoint == Exp 임 -_-
//			MP_t HealPoint = Exp;
			MP_t CurrentMP = pOusters->getMP();
			MP_t MaxMP	   = pOusters->getMP(ATTR_MAX);
			MP_t HealPoint = 0;

			if ( CurrentMP < MaxMP )
			{
//				HealPoint = computeCreatureExp(pTargetCreature, 60);
				HealPoint = getPercentValue(Exp, 60);
			}
			else
			{
//				MP_t ExtraMP = CurrentMP - MaxMP;
				float ExtraMP = (float)(CurrentMP - MaxMP) / (float)(MaxMP*2) * 100;
				float ftemp = 1.1 - ( (float)ExtraMP / ((float)ExtraMP+10.0) );
				int ratio = (int)(ftemp * 100);
//				cout << "AbsorbSoul : " << ratio << endl;
//				HealPoint = computeCreatureExp(pTargetCreature, ratio);
				HealPoint = getPercentValue(Exp, ratio);
			}

			MP_t NewMP     = min((int)MaxMP*3 , (int)CurrentMP + (int)HealPoint);
//			cout << NewMP << endl;

			// 아우스터즈의 MP를 세팅한다.
			pOusters->setMP(NewMP);
//			cout << pOusters->getMP(ATTR_CURRENT) << endl;

            GCModifyInformation gcMI;
            gcMI.addShortData( MODIFY_CURRENT_MP, pOusters->getMP(ATTR_CURRENT) );

//			cout << gcMI.toString() << endl;

			pOusters->getPlayer()->sendPacket( &gcMI );

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.addCListElement(TargetObjectID);
			_GCSkillToTileOK1.setDuration(0);
			_GCSkillToTileOK1.setX(TargetZoneX);
			_GCSkillToTileOK1.setY(TargetZoneY);
			_GCSkillToTileOK1.setRange(0);

			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.addCListElement(TargetObjectID);
			_GCSkillToTileOK5.setX(TargetZoneX);
			_GCSkillToTileOK5.setY(TargetZoneY);
			_GCSkillToTileOK5.setRange(0);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			list<Creature *> cList;
			cList.push_back(pOusters);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToTileOK5 , cList);

			// 아음 -_- 흡영 당한 후에 또 흡영 못하게 막아야 됨
			pTargetItem->setFlag(Effect::EFFECT_CLASS_CANNOT_ABSORB_SOUL);

			pOusters->getGQuestManager()->blooddrain();
		}
		else 
		{
			executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
		}
	} 
	catch (Throwable & t) 
	{
		executeAbsorbSoulSkillFail(pOusters, getSkillType(), TargetObjectID, false, bClientLocked);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH

}

void AbsorbSoul::makeLarvaToPupa(Ousters* pOusters, int TargetLevel, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY, CoordInven_t TargetInvenX, CoordInven_t TargetInvenY )
	throw()
{
	__BEGIN_TRY

	Inventory* pInventory = pOusters->getInventory();
	Assert(pInventory != NULL);
	Zone* pZone = pOusters->getZone();
	Assert(pZone != NULL );

	if ( InvenX >= pInventory->getWidth()
		|| InvenY >= pInventory->getHeight()
		|| TargetInvenX >= pInventory->getWidth()
		|| TargetInvenY >= pInventory->getHeight()
	   )
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	Item* pLarva = pInventory->getItem( InvenX, InvenY );
	if ( pLarva == NULL
		|| pLarva->getItemClass() != Item::ITEM_CLASS_LARVA 
		|| pLarva->getObjectID() != ItemObjectID
	)
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	ItemType_t LarvaType = pLarva->getItemType();
	
//	int ratio = ( 100 * TargetLevel ) / ( (pOusters->getLevel() * 2) * ( pLarva->getItemType() + 1 ) );
//  확률 4배로 증가 
	int ratio = ( 200 * TargetLevel ) / ( pOusters->getLevel() * ( pLarva->getItemType() + 1 ) );

	// 푸파 만들기 실패
	if ( (rand()%100) > ratio )
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	// 확률은 넘었으니 -_- 푸파를 만들어볼까
	list<OptionType_t> optionNULL;
	Item* pPupa = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_PUPA, pLarva->getItemType(), optionNULL );
			
	// 라바의 갯수를 줄여준다.
	// 이 함수 안에서 라바의 갯수가 자동적으로 하나 줄어들고, 
	// 만일 1개인 라바였다면 인벤토리 및 DB에서 삭제되게 된다.
	decreaseItemNum(pLarva, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

	// 기존의 푸파를 가져온다.
	Item* pPrevPupa = pInventory->getItem( TargetInvenX, TargetInvenY );

	GCSkillToInventoryOK1 gcSkillToInventoryOK1;

	if ( pPrevPupa != NULL )
	{
		// 기존에 더할 푸파가 있다면

		if ( !canStack( pPrevPupa, pPupa ) || pPrevPupa->getNum() >= ItemMaxStack[ (int)pPrevPupa->getItemClass() ] )
		{
			executeSkillFailException( pOusters, getSkillType() );
			return;
		}

		// 갯수를 하나 증가시키고 저장한다.
		pPrevPupa->setNum( pPrevPupa->getNum() + 1 );
		pPrevPupa->save( pOusters->getName(), STORAGE_INVENTORY, 0, TargetInvenX, TargetInvenY );

		// 위부분의 decreaseItemNum() 함수 부분에서 아이템 숫자를 감소시키므로,
		// 여기서 다시 인벤토리의 아이템 숫자를 증가시킨다.
		pInventory->increaseNum();

		// 만들어진 푸파는 기존의 푸파에 더해졌으므로 삭제한다.
		SAFE_DELETE( pPupa );

		gcSkillToInventoryOK1.setObjectID( pPrevPupa->getObjectID() );
	}
	else
	{
		ObjectRegistry& OR = pZone->getObjectRegistry();
		OR.registerObject( pPupa );

		// 푸파를 Inventory 에 집어넣고 DB에다가 생성한다.
		pInventory->addItem( TargetInvenX, TargetInvenY, pPupa );
		pPupa->create( pOusters->getName(), STORAGE_INVENTORY, 0, TargetInvenX, TargetInvenY );

		gcSkillToInventoryOK1.setObjectID( pPupa->getObjectID() );
	}

	gcSkillToInventoryOK1.setSkillType( getSkillType() );
	gcSkillToInventoryOK1.setItemType( LarvaType );
	gcSkillToInventoryOK1.setCEffectID( 0 );
	gcSkillToInventoryOK1.setX( TargetInvenX );
	gcSkillToInventoryOK1.setY( TargetInvenY );

	pOusters->getPlayer()->sendPacket( &gcSkillToInventoryOK1 );

	__END_CATCH
}

AbsorbSoul g_AbsorbSoul;
