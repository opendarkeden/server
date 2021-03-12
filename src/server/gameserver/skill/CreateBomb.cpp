//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateBomb.cpp
// Written by  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CreateBomb.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"

#include "item/Bomb.h"

#include "Gpackets/GCSkillToInventoryOK1.h"
#include "Gpackets/GCSkillToInventoryOK2.h"

int MaterialType2BombTypeMap[] =
{
	0,  // 0
	1,  // 1
	2,  // 2
	3,  // 3
	4,  // 4
	-1, // 5
	-1, // 6
	-1, // 7
	-1, // 8
	-1  // 9
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CreateBomb::execute(Slayer * pSlayer , ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot * pSkillSlot)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(CreateBomb)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Inventory* pInventory = pSlayer->getInventory();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);
		Assert(pInventory != NULL);

		// 폭탄을 만들 대상이 널이거나, 보통 폭탄 재료가 아니거나, 
		// OID가 틀리다면 사용할 수 없다.
		Item* pBombMaterial = pInventory->getItem(X, Y);
		if (pBombMaterial == NULL || pBombMaterial->getItemClass() != Item::ITEM_CLASS_BOMB_MATERIAL || 
			pBombMaterial->getObjectID() != InvenObjectID)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		bool bSamePosition = false;
		if (X == TargetX && Y == TargetY) bSamePosition = true;

		// 대상 위치와 타겟 위치가 같게 날아오는 경우는
		// 폭탄로 변환하고자 하는 C4의 숫자가 1인 경우이다.
		// (이전의 C4을 삭제하고, 같은 위치에 폭탄를 생성한다는 의미이다.)
		// 1이 아니라면 리턴해야한다.
		if (bSamePosition && pBombMaterial->getNum() != 1)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		// 아이템 타입과 이에 대응하는 폭탄의 타입을 구한다.
		ItemType_t MaterialType = pBombMaterial->getItemType();
		int BombType = MaterialType2BombTypeMap[MaterialType];
		if (BombType == -1)
		{
			// 폭탄 재료가 아니라, 지뢰 재료라면, 스킬 실패다.
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
			return;
		}

		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;
		GCSkillToInventoryOK2 _GCSkillToInventoryOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillGrade        Grade      = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bCanMake    = canMake(BombType, pSlayer->getSkillDomainLevel(DomainType), SkillLevel);

		if (bManaCheck && bTimeCheck && bRangeCheck && bCanMake)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			list<OptionType_t> optionNULL;
			Item* pBomb = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_BOMB, BombType, optionNULL);

			// 폭탄재료의 갯수를 줄여준다.
			// 이 함수 안에서 폭탄재료의 갯수가 자동적으로 하나 줄어들고, 
			// 만일 1개인 폭탄재료이었다면 인벤토리 및 DB에서 삭제되게 된다.
			decreaseItemNum(pBombMaterial, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, X, Y);

			Item* pPrevBomb = pInventory->getItem(TargetX, TargetY);

			// 기존의 폭탄 객체가 있다는 말은 쌓아야 한다는 말이다.
			if (pPrevBomb != NULL)
			{
				if (canStack(pPrevBomb, pBomb) == false)
				{
					// 같은 타입의 폭탄가 아닐 때인데... 이런 경우가 어떻게 하면 생길까...
					SAFE_DELETE(pBomb);

					executeSkillFailException(pSlayer, getSkillType());

					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerinventory)" << endl;
					return;
				}

				// 갯수를 하나 증가시키고 저장한다.
				pPrevBomb->setNum(pPrevBomb->getNum() + 1);
				pPrevBomb->save(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);
				
				// 위부분의 decreaseItemNum() 함수 부분에서 아이템 숫자를 감소시키므로, 
				// 여기서 다시 인벤토리의 아이템 숫자를 증가시킨다.
				pInventory->increaseNum();

				// 방금 만들어진 폭탄는 기존의 폭탄에 더해졌으므로 삭제한다.
				SAFE_DELETE(pBomb);

				_GCSkillToInventoryOK1.setObjectID(pPrevBomb->getObjectID());
			}
			// 기존의 폭탄 객체가 없다는 말은 폭탄 객체를 DB에 생성해야 한다는 말이다.
			else
			{
				ObjectRegistry& OR = pZone->getObjectRegistry();
				OR.registerObject(pBomb);

				// 폭탄를 Inventory로 집어 넣고 DB에다가 생성한다.
				pBomb->setNum(1);
				pInventory->addItem(TargetX, TargetY, pBomb);
				pBomb->create(pSlayer->getName(), STORAGE_INVENTORY, 0, TargetX, TargetY);

				_GCSkillToInventoryOK1.setObjectID(pBomb->getObjectID());
			}

			// 패킷을 보낸다.
			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setItemType(BombType);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setX(TargetX);
			_GCSkillToInventoryOK1.setY(TargetY);

			_GCSkillToInventoryOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToInventoryOK2.setSkillType(SkillType);
			
			// EXP UP!
			Exp_t ExpUp = 10 * (Grade + 1);
			shareAttrExp(pSlayer, ExpUp , 1, 8, 1, _GCSkillToInventoryOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToInventoryOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToInventoryOK1);

			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToInventoryOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		}
		else
		{
			//executeSkillFailNormal(pSlayer, getSkillType(), NULL);
			// 폭탄 만들기 같은 경우에는, 실패했을 때 딜레이가 없기 때문에,
			// 클라이언트에게서 패킷이 상당히 빠르게 연속적으로 날아온다.
			// 이 때, 실패 패킷을 브로드 캐스팅하게 되면, 옆에 있는 사람이 보기에는
			// 캐스팅 동작이 매우 빠르게 연속적으로 표시된다. (스피드핵 쓰는 것처럼...)
			// 그래서 이 부분에서 브로드캐스팅을 하지 않고, 본인에게만 패킷을 날려준다.
			// 2002-02-06 김성민
			executeSkillFailException(pSlayer, getSkillType());
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(CreateBomb)" << endl;

	__END_CATCH
}

bool CreateBomb::canMake(ItemType_t BombType, int DomainLevel, int SkillLevel)
	throw()
{
	__BEGIN_TRY

	int ratio = 10 * ((SkillLevel/10) - BombType) + 40;
	if ((rand()%100) < ratio) return true;
	return false;

	__END_CATCH
}

CreateBomb g_CreateBomb;
