//////////////////////////////////////////////////////////////////////////////
// Filename    : ThrowHolyWater.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ThrowHolyWater.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/HolyWater.h"

#include "Gpackets/GCThrowItemOK1.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCThrowItemOK2.h"
#include "Gpackets/GCThrowItemOK3.h"
#include "Gpackets/GCModifyInformation.h"


//////////////////////////////////////////////////////////////////////
//
// ThrowHolyWater::execute()
//
//////////////////////////////////////////////////////////////////////
void ThrowHolyWater::execute(Slayer* pSlayer , ObjectID_t TargetObjectID, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Inventory* pInventory = pSlayer->getInventory();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);
		Assert(pInventory != NULL);
		Assert(InvenX < pInventory->getWidth());
		Assert(InvenY < pInventory->getHeight());

		Item* pItem = pInventory->getItem(InvenX, InvenY);

		if (pItem == NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		ObjectID_t ObjectID        = pItem->getObjectID();
		Creature*  pTargetCreature = NULL;

		// 패킷에 온 거랑, 아이템 아이디가 틀리거나, 
		// 성수가 아니라면 실패했다고 보내준다.
		if (ObjectID != ItemObjectID || pItem->getItemClass() != Item::ITEM_CLASS_HOLYWATER)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCThrowItemOK2 _GCThrowItemOK2;
		GCModifyInformation gcAttackerMI;

		// 존에서 타겟 크리쳐를 찾는다.
		/*
		try 
		{ 
			pTargetCreature = pZone->getCreature(TargetObjectID); 
		}
		catch (NoSuchElementException) 
		{ 
			pTargetCreature = NULL; 
		}
		*/

		pTargetCreature = pZone->getCreature(TargetObjectID); 

		// 클라이언트와의 동기화 문제로 인해, 포인터가 널일 수 있다.
		// 성수병 두개를 연속으로 던졌는데, 먼저 던진 성수병으로 인해,
		// 타겟이 죽고 난 뒤, 클라이언트가 미처 그 패킷을 받지 못하고,
		// 다시 한번 성수를 던질 경우, 걍 리턴하면 곤란하다.
		if (pTargetCreature == NULL)
		{
			// 먼저 아이템 숫자를 줄여주어야 한다.
			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		} 
		else 
		{
			HolyWater* pHolyWater = dynamic_cast<HolyWater*>(pItem);

			Damage_t MinDamage = pHolyWater->getMinDamage();
			Damage_t MaxDamage = pHolyWater->getMaxDamage();
			Damage_t Damage    = max(1, Random(MinDamage, MaxDamage));

			// 일반 지역이 아니라면 데미지를 0으로 세팅해 준다. 
			// 밑 부분에서 checkZoneLevelToHitTarget 함수를 부르기 때문에
			// 여기서 안전지대 관련 검사를 할 필요가 없다.
			// -- 2002-01-31 김성민
			//if (!(pZone->getZoneLevel() & NO_SAFE_ZONE)) Damage = 0;

			list<Creature*> cList;
			cList.push_back(pSlayer);

			bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature);
			bool bPK             = verifyPK(pSlayer, pTargetCreature);
			bool bRangeCheck     = verifyDistance(pSlayer, pTargetCreature, 10);
			bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature) && canAttack( pSlayer, pTargetCreature );

			// 명중 되었다면, 데미지를 준다..
			// 명중이 되지 않아도 성수는 한번 던지면 끝이다.
			if (bHitRoll && bPK && bRangeCheck && bZoneLevelCheck)
			{
				// 상대방이 슬레이어가 아닌 경우에만 경험치를 올려준다.
				if (!pTargetCreature->isSlayer())
				{
					shareAttrExp(pSlayer, Damage, 1, 1, 8, gcAttackerMI);

					// 인첸 도메은도 올려준다.
					// 2003. 1. 12 by bezz
					// Throw Holy Water 의 SkillInfo 가 없다.
					// 그래서 Create Holy Water 의 Point 를 쓴다.
					SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_CREATE_HOLY_WATER );
					increaseDomainExp( pSlayer, SKILL_DOMAIN_ENCHANT, pSkillInfo->getPoint(), gcAttackerMI, pTargetCreature->getLevel() );
				}

				if (pTargetCreature->isSlayer()) 
				{
					/*
					GCModifyInformation gcModifyInfo;

					Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
					setDamage(pTargetSlayer, Damage, NULL, 0, &_GCThrowItemOK2);
					computeAlignmentChange(pTargetSlayer, Damage, pSlayer, &_GCThrowItemOK2, &gcAttackerMI);

					Player* pTargetPlayer = pTargetSlayer->getPlayer();
					pTargetPlayer->sendPacket(&_GCThrowItemOK2);
					*/
				} 
				else if (pTargetCreature->isVampire()) 
				{
					Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);

					setDamage(pTargetVampire, Damage, NULL, 0, &_GCThrowItemOK2);

					// 받은 데미지만큼의 홀리 데미지를 준다.
					Silver_t silverDamage    = max(1, getPercentValue(Damage, 10));
					Silver_t newSilverDamage = pTargetVampire->getSilverDamage() + silverDamage;
					pTargetVampire->saveSilverDamage(newSilverDamage);

					Player* pTargetPlayer = pTargetVampire->getPlayer();
					pTargetPlayer->sendPacket(&_GCThrowItemOK2);

					GCModifyInformation gcModifyInfo;
					gcModifyInfo.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);
					pTargetPlayer->sendPacket(&gcModifyInfo);
				} 
				else if (pTargetCreature->isOusters()) 
				{
					Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);

					setDamage(pTargetOusters, Damage, NULL, 0, &_GCThrowItemOK2);

					// 받은 데미지만큼의 홀리 데미지를 준다.
					Silver_t silverDamage    = max(1, getPercentValue(Damage, 10));
					Silver_t newSilverDamage = pTargetOusters->getSilverDamage() + silverDamage;
					pTargetOusters->saveSilverDamage(newSilverDamage);

					Player* pTargetPlayer = pTargetOusters->getPlayer();
					pTargetPlayer->sendPacket(&_GCThrowItemOK2);

					GCModifyInformation gcModifyInfo;
					gcModifyInfo.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);
					pTargetPlayer->sendPacket(&gcModifyInfo);
				} 
				else if (pTargetCreature->isMonster()) 
				{
					Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
					setDamage(pTargetMonster, Damage, pSlayer, getSkillType(), NULL, NULL);

					Silver_t silverDamage = max(1, getPercentValue(Damage, 10));
					Silver_t newSilverDamage = pTargetMonster->getSilverDamage() + silverDamage;
					pTargetMonster->setSilverDamage(newSilverDamage);
				}

				cList.push_back(pTargetCreature);

				// 주변 사람들에게 OK3 Packet을 보낸다.
				GCThrowItemOK3 _GCThrowItemOK3;
				_GCThrowItemOK3.setObjectID(pSlayer->getObjectID()); 
				_GCThrowItemOK3.setTargetObjectID(TargetObjectID);
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCThrowItemOK3, cList);

				// 던진 사람에게 OK Packet을 보낸다.
				GCThrowItemOK1 _GCThrowItemOK1;
				_GCThrowItemOK1.setObjectID(TargetObjectID);

				pPlayer->sendPacket(&_GCThrowItemOK1);
				pPlayer->sendPacket(&gcAttackerMI);
			}
			else // 성수 던지기에 실패했을 경우...
			{
				executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
			}

			// 맞든 맞지 않았든 성수의 숫자는 줄여주어야 한다.
			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ThrowHolyWater g_ThrowHolyWater;
