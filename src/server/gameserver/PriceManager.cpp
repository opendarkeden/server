//////////////////////////////////////////////////////////////////////////////
// Filename    : PriceManager.cpp
// Written By  : 김성민
// Description :
// 아이템을 상점에서 사고 팔 때, 그 매매가격을 결정하는 클래스이다.
// 내부적으로는 ItemInfoManager의 원래 가격을 이용해 계산을 한다.
//////////////////////////////////////////////////////////////////////////////

#include "PriceManager.h"
#include "ItemInfoManager.h"
#include "OptionInfo.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "VariableManager.h"
#include "GamePlayer.h"

#include "item/Skull.h"
#include "item/SlayerPortalItem.h"
#include "item/VampirePortalItem.h"
#include "item/OustersSummonItem.h"

// global variable definition
PriceManager* g_pPriceManager = NULL;

// constants
const uint PORTAL_ITEM_CHARGE_PRICE = 5000;
const uint SUMMON_ITEM_CHARGE_PRICE = 1000;

//////////////////////////////////////////////////////////////////////////////
// getPrice()
// 아이템 정보를 참조해 실제 물건값을 정한다.
// nDiscount 변수(백분율)를 이용해 물건값을 컨트롤할 수 있다.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getPrice(Item* pItem, MarketCond_t nDiscount, ShopRackType_t shopType, Creature* pCreature) const
{
	// 첨에 공짜로 준 아이템은 팔아도 1원밖에 못 얻는다. 2003. 1. 15. Sequoia
	if (pItem->getCreateType() == Item::CREATE_TYPE_GAME ) return (Price_t)1;
	// 퀘스트 아이템은 오디번~~~ 2003. 4. 14. Sequoia
	if (pItem->isTimeLimitItem() ) return (Price_t)50;
	if (pItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 4 )
	{
		return (Price_t)g_pVariableManager->getVariable(CROWN_PRICE);
	}

	// 아이템의 원래 가격을 얻어낸다.
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	double originalPrice = pItemInfo->getPrice();
	double finalPrice    = 0;

	if (pItem->getGrade() != -1 )
	{
		double gradePercent = 80 + (5 * pItem->getGrade());
//		originalPrice = getPercentValue(originalPrice, gradePercent);
		originalPrice *= (gradePercent/100.0);
	}

	// 슬레이어 포탈 같은 경우에는 원래 가격에다 현재 차지 수만큼의 가격을 더해야 한다.
	if (pItem->getItemClass() == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
	{
		SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);
		originalPrice += (pSlayerPortalItem->getCharge() * PORTAL_ITEM_CHARGE_PRICE);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
	{
		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pItem);
		originalPrice += (pVampirePortalItem->getCharge() * PORTAL_ITEM_CHARGE_PRICE);
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM)
	{
		OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pItem);
		originalPrice += (pOustersSummonItem->getCharge() * SUMMON_ITEM_CHARGE_PRICE);

	}

	// 옵션이 있다면 옵션만큼의 가격을 곱해야 한다.
	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	if (!optionTypes.empty())
	{
		finalPrice = 0;

		// 가격 = (원래 가격 * 옵션의 PriceMultiplier / 100) + ..
		double priceMultiplier = 0;
		list<OptionType_t>::const_iterator itr;
		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(*itr);
			Assert(pOptionInfo != NULL);
			priceMultiplier = (double)(pOptionInfo->getPriceMultiplier());
			finalPrice += (originalPrice* priceMultiplier / 100);
		}

		originalPrice = finalPrice;
	}

	// 아이템이 손상되었다면 손상된 만큼의 가격을 깍아야 한다.
	double maxDurability = (double)computeMaxDurability(pItem);
	double curDurability = (double)(pItem->getDurability());

	// 아이템 중에 내구도가 없는 것들이 존재하기 때문에 처리해준다.
	if (maxDurability > 1) finalPrice = originalPrice* curDurability / maxDurability;
	else                   finalPrice = originalPrice;

	// 상점 시세에 따라 가격을 다시 조정해준다.
	finalPrice = finalPrice* nDiscount / 100;

	// 상점의 종류에 따라 가격을 다시 조정해준다.
	if (shopType == SHOP_RACK_MYSTERIOUS)
	{
		finalPrice *= 10;
	}

	// 크리쳐의 변화 요소에 따라 가격을 다시 조정해준다.
	if (pCreature != NULL)
	{
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Attr_t CSTR = pSlayer->getSTR(ATTR_CURRENT);
			Attr_t CDEX = pSlayer->getDEX(ATTR_CURRENT);
			Attr_t CINT = pSlayer->getINT(ATTR_CURRENT);

			if ((CSTR + CDEX + CINT <= 40) &&
				(pItem->getItemClass() == Item::ITEM_CLASS_POTION) && 
				(pItem->getItemType() == 0 || pItem->getItemType() == 5))
			{
				finalPrice = getPercentValue((int)finalPrice, 70);
			}
		}
		else if (pCreature->isVampire())
		{
			// 뱀파이어가 해골을 팔 경우에는 해골의 가격을 반으로 줄여준다. 
			if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
			{
				finalPrice = finalPrice / 2.0;
			}
		}
		else if (pCreature->isOusters())
		{
			// 아우스터즈가 해골을 팔 경우에는 해골의 가격의 75%.
			if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL)
			{
				finalPrice *= 0.75;
			}
		}
	}

	// 유료 사용자이고 유료존 이면
	if (g_pVariableManager->getVariable(PREMIUM_HALF_EVENT ) )
	{
		if (
			pItem->getItemClass() == Item::ITEM_CLASS_POTION || pItem->getItemClass() == Item::ITEM_CLASS_SERUM ||
			pItem->getItemClass() == Item::ITEM_CLASS_LARVA || pItem->getItemClass() == Item::ITEM_CLASS_PUPA ||
			pItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI
		)
		{
			if (pCreature->isPC() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
				if (pGamePlayer->isPayPlaying() )
				{
					// 반 값.
					finalPrice = finalPrice / 2;
				}
			}
		}
	}

	// Blood Bible 보너스 적용
	if (pItem->getItemClass() == Item::ITEM_CLASS_POTION || pItem->getItemClass() == Item::ITEM_CLASS_SERUM )
	{
		if (pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			int ratio = pPC->getPotionPriceRatio();
			if (ratio != 0 )
			{
				// ratio 값이 마이너스 값이다.
				finalPrice += getPercentValue((int)finalPrice, ratio);
			}
		}
	}

	return max(1, (int)finalPrice);
}

//////////////////////////////////////////////////////////////////////////////
// getRepairPrice()
// 아이템을 수리할 때 드는 비용을 리턴한다.
// 아이템 수리비는 완전히 박살난 아이템일 경우 
// 원래 아이템 가격의 10분의 1이다.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getRepairPrice(Item* pItem, Creature* pCreature) const
{
	// 아이템의 원래 가격을 얻어낸다.
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	double originalPrice = pItemInfo->getPrice();
	double finalPrice    = 0;

	if (pItem->getGrade() != -1 )
	{
		double gradePercent = 80 + (5 * pItem->getGrade());
//		originalPrice = getPercentValue(originalPrice, gradePercent);
		originalPrice *= (gradePercent/100.0);
	}

	// 슬레이어 포탈 같은 경우에는 수리를 할 수는 없지만, 차지를 늘릴 수가 있다.
	if (pItem->getItemClass() == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
	{
		SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);
		int MaxCharge = pSlayerPortalItem->getMaxCharge();
		int CurCharge = pSlayerPortalItem->getCharge();

		return (MaxCharge - CurCharge) * PORTAL_ITEM_CHARGE_PRICE;
	}

	if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM)
	{
		OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pItem);
		int MaxCharge = pOustersSummonItem->getMaxCharge();
		int CurCharge = pOustersSummonItem->getCharge();

		return (MaxCharge - CurCharge) * SUMMON_ITEM_CHARGE_PRICE;
	}

	// 옵션이 있다면 옵션만큼의 가격을 곱해야 한다.
	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	if (!optionTypes.empty())
	{
		finalPrice = 0;
		// 가격 = (원래 가격 * 옵션의 PriceMultiplier의 총합 / 100) * 옵션의 개수
		double priceMultiplier = 0;
		list<OptionType_t>::const_iterator itr;
		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(*itr);
			Assert(pOptionInfo != NULL);
			priceMultiplier = (double)(pOptionInfo->getPriceMultiplier());
			finalPrice += (originalPrice* priceMultiplier / 100);
		}

		originalPrice = finalPrice;
	}
	/*
	if (pItem->getOptionType() != 0)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(pItem->getOptionType());
		Assert(pOptionInfo != NULL);
		double priceMultiplier = (double)(pOptionInfo->getPriceMultiplier());
		originalPrice = originalPrice * priceMultiplier / 100;
	}
	*/

	// 아이템이 손상되었다면 손상된 만큼의 가격을 깍아야 한다.
	double maxDurability = (double)computeMaxDurability(pItem);
	double curDurability = (double)(pItem->getDurability());

	// 아이템 중에 내구도가 없는 것들이 존재하기 때문에 처리해준다.
	if (maxDurability != 0)
	{
		// 아이템의 현재 내구도가 맥스라면 리턴한다.
		if (curDurability == maxDurability)
		{
			return 0;
		}

		// 현재 내구도를 최내 내구도로 나누면 그 아이템의 손상된 정도가 나온다.
		// 이를 원래 가격에다 곱하면, 내구도가 깍인 만큼 아이템의 값이 떨어지게 된다.
		finalPrice = originalPrice * curDurability / maxDurability;
	}
	else
	{
		// 내구도가 없는 아이템은 손상되지가 않으므로, 
		// 내구도를 고려한 가격은 원래의 값과 똑같다.
		finalPrice = originalPrice;
	}

	// 수리 비용은 원래 값의 10분의 1이다.
	finalPrice = (originalPrice - finalPrice) / 10.0;

	if (finalPrice < 1.0)
	{
		return 1;
	}

	return max(0, (int)finalPrice);
}

//////////////////////////////////////////////////////////////////////////////
// getSilverCoatingPrice()
// 아이템을 은 도금할 때의 가격이다.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getSilverCoatingPrice(Item* pItem, Creature* pCreature) const
{
	if (pItem == NULL) return 0;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			break;
		default:
			return 0;
	}

	ItemInfo* pItemInfo  = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	double    maxSilver  = pItemInfo->getMaxSilver();
	double    finalPrice = 0;

	// 땜빵으로 집어넣은 은의 가격이다.
	finalPrice = maxSilver; 

	return max(0, (int)finalPrice);
}

//////////////////////////////////////////////////////////////////////////////
// getStashPrice()
// 보관함 가격을 리턴한다. 
// 그렇게 자주 변동될 가격이 아니기 때문에 코드에다 집어넣어 놓았다.
//////////////////////////////////////////////////////////////////////////////
Price_t PriceManager::getStashPrice(BYTE index, Creature* pCreature) const
{
	Price_t price = 0;

	switch (index)
	{
		case 1: price = 100000; break;
		case 2: price = 1000000; break;
		case 3: price = 10000000; break;
		default: 
			cerr << "PriceManager::getStashPrice() : Unknown Stash Index" << endl;
			Assert(false);
	}

	if (pCreature != NULL)
	{
		if (pCreature->isSlayer())
		{
		}
		else if (pCreature->isVampire())
		{
		}
		else if (pCreature->isOusters())
		{
		}
	}

	return price;
}


//////////////////////////////////////////////////////////////////////////////
// 이벤트용 가격 함수
// 2001년 크리스마스 이벤트때 사용하였던 별 아이템에 대한 정보이다.
// 2002년 어린이날에도 같은 이벤트를 사용하기로 하였기 때문에 주석을 해지
//
// 별 이벤트가 앞으로 일어날 수 있는 관계로,
// 이름을 STAR_EVENT_CODE로 변경하는 것을 고려해야 하겠다.
//////////////////////////////////////////////////////////////////////////////
int PriceManager::getStarPrice(Item* pItem, XMAS_STAR& star) const
{
	Assert(pItem != NULL);

	ItemType_t   IType = pItem->getItemType();
	OptionType_t OType = pItem->getFirstOptionType();

	Assert(OType != 0);

	OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(OType);
	Assert(pOptionInfo!=NULL);
	OptionClass OClass = pOptionInfo->getClass();

	switch (OClass)
	{
		case OPTION_DAMAGE:       star.color = STAR_COLOR_BLACK; break;
		case OPTION_STR:          star.color = STAR_COLOR_RED;   break;
		case OPTION_INT:          star.color = STAR_COLOR_BLUE;  break;
		case OPTION_DEX:          star.color = STAR_COLOR_GREEN; break;
		case OPTION_ATTACK_SPEED: star.color = STAR_COLOR_CYAN;  break;
		default: Assert(false); break;
	}

	star.amount = (IType - 1) * 20;

	return 0;
}

int PriceManager::getBallPrice(int price, XMAS_STAR& star) const
{
	star.amount = price;
	star.color = STAR_COLOR_PINK;

	return 0;
}

// Mysterious Item 가격
// itemClass와 pCreature의 능력치에 따라서 가격이 달라진다.
Price_t PriceManager::getMysteriousPrice(Item::ItemClass itemClass, Creature* pCreature) const
{
	int multiplier = 1;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		Attr_t CSTR = pSlayer->getSTR(ATTR_BASIC);
		Attr_t CDEX = pSlayer->getDEX(ATTR_BASIC);
		Attr_t CINT = pSlayer->getINT(ATTR_BASIC);
		Attr_t CSUM = CSTR + CDEX + CINT;

		// 0~20 사이
		multiplier = CSUM / 15;
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		Level_t CLevel = pVampire->getLevel();

		// 0~20 사이
		multiplier = CLevel / 5;
	}
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		Level_t CLevel = pOusters->getLevel();

		// 0~20 사이
		multiplier = CLevel / 5;
	}

	// 1~20사이
	multiplier = max(1, multiplier);

	// 가격 평균을 알아온다.
	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager(itemClass);
	Assert(pInfoClass!=NULL);

	// 가격 평균 * 능력치 비율?
	int finalPrice = (int)pInfoClass->getAveragePrice() * multiplier;

	// Blood Bible 보너스 적용
	if (pCreature->isPC() )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		int ratio = pPC->getGamblePriceRatio();
		if (ratio != 0 )
		{
			// ratio 값은 마이너스 값이다.
			finalPrice += getPercentValue(finalPrice, ratio);
		}
	}

	return finalPrice;
}

