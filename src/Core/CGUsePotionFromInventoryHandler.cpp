//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePotionFromInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUsePotionFromInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemUtil.h"
	#include <math.h>
	#include "EffectHPRecovery.h"
	#include "EffectMPRecovery.h"
	#include "Store.h"

	#include "item/Potion.h"
	#include "item/Serum.h"
	#include "item/Pupa.h"
	#include "item/ComposMei.h"
	#include "item/EventETC.h"

	#include "Gpackets/GCCannotUse.h"
	#include "Gpackets/GCUseOK.h"
	#include "Gpackets/GCStatusCurrentHP.h"
	#include "Gpackets/GCHPRecoveryStartToSelf.h"
	#include "Gpackets/GCHPRecoveryStartToOthers.h"
	#include "Gpackets/GCMPRecoveryStart.h"
#endif

#define	 DELAY_PROVIDER	 2
#define	 RECOVERY_QUANTITY 1


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUsePotionFromInventoryHandler::execute (CGUsePotionFromInventory* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	if (pGamePlayer == NULL) return;

	Creature* pCreature = pGamePlayer->getCreature();
	if (pCreature == NULL) return;

	// 코마 상태라면 사용할 수 없다.
	if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	if ( pPC == NULL ) return;

	Inventory* pInventory = pPC->getInventory();
	Zone*      pZone      = pPC->getZone();

	if (pZone == NULL || pInventory == NULL) return;

	CoordInven_t InvenX = pPacket->getX();
	CoordInven_t InvenY = pPacket->getY();

	if (InvenX >= pInventory->getWidth() || InvenY >= pInventory->getHeight())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	Item* pItem = pInventory->getItem(InvenX, InvenY);
	if (pItem == NULL)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	if ( pPC->getStore()->getItemIndex(pItem) != 0xff )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 인벤토리에 있는 아이템의 Object를 받는다.
	ObjectID_t ItemObjectID = pItem->getObjectID();

	if (ItemObjectID != pPacket->getObjectID() )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	if ( pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ETC )
	{
		if ( pItem->getItemType() >= 14 && !pCreature->isFlag( Effect::EFFECT_CLASS_PLEASURE_EXPLOSION ) )
		{
			EventETCInfo* pInfo = dynamic_cast<EventETCInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
			Assert( pInfo != NULL );

			int amount = pInfo->getFunction();

			GCModifyInformation gcMI;
			bool HPRegen=false, MPRegen=false;
			HP_t CurrentHP = 0, MaxHP = 0;
			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				CurrentHP = pSlayer->getHP();
				MaxHP = pSlayer->getHP(ATTR_MAX);
			}
			else if ( pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				CurrentHP = pVampire->getHP();
				MaxHP = pVampire->getHP(ATTR_MAX);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				CurrentHP = pOusters->getHP();
				MaxHP = pOusters->getHP(ATTR_MAX);
			}

			if ( CurrentHP < MaxHP )
			{
				CurrentHP += min(amount, MaxHP-CurrentHP);
				GCStatusCurrentHP gcHP;
				gcHP.setObjectID(pPC->getObjectID());
				gcHP.setCurrentHP(CurrentHP);
				pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcHP );

				gcMI.addLongData(MODIFY_CURRENT_HP, CurrentHP);
				HPRegen = true;

				if ( pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					pSlayer->setHP(CurrentHP);
				}
				else if ( pPC->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
					pVampire->setHP(CurrentHP);
				}
				else if ( pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					pOusters->setHP(CurrentHP);
				}
			}

			MP_t CurrentMP = 0, MaxMP = 0;
			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				CurrentMP = pSlayer->getMP();
				MaxMP = pSlayer->getMP(ATTR_MAX);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				CurrentMP = pOusters->getMP();
				MaxMP = pOusters->getMP(ATTR_MAX);
			}

			if ( CurrentMP < MaxMP )
			{
				CurrentMP += min(amount, MaxMP-CurrentMP);
				gcMI.addLongData(MODIFY_CURRENT_MP, CurrentMP);
				MPRegen = true;

				if ( pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					pSlayer->setMP(CurrentMP);
				}
				else if ( pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					pOusters->setMP(CurrentMP);
				}
			}

			if ( !HPRegen && !MPRegen )
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
			else
			{
				decreaseItemNum(pItem, pInventory, pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
				pPlayer->sendPacket( &gcMI );

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			}

			return;
		}
		else
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	}

	if (pCreature->isSlayer())
	{
		Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature);

		HP_t	MaxHP    = pSlayer->getHP(ATTR_MAX);
		HP_t	CurrentHP= pSlayer->getHP(ATTR_CURRENT);
		MP_t	MaxMP    = pSlayer->getMP(ATTR_MAX);
		MP_t	CurrentMP= pSlayer->getMP(ATTR_CURRENT);
		Potion* pPotion  = dynamic_cast<Potion*>(pItem);

		// 한턴에 회복되는 양
		int		HPQuantity = pPotion->getHPQuantity();
		int		MPQuantity = pPotion->getMPQuantity();

		// 한턴이 몇초 인가.
		int		HPDelayProvider = pPotion->getHPDelay();
		int		MPDelayProvider = pPotion->getMPDelay();

		Attr_t INT = pSlayer->getINT();

		HP_t    PotionHPAmount = 0, PotionMPAmount = 0;

		PotionHPAmount = pPotion->getHPAmount();
		PotionMPAmount = pPotion->getMPAmount();
		
		int     HPAmount = min(MaxHP - CurrentHP , (int)PotionHPAmount);
		int     MPAmount = min(MaxMP - CurrentMP , (int)(PotionMPAmount* (double)(1 + (double)((double)INT / 300.0))));
		bool	notRecoverHP = false;
		bool	notRecoverMP = false;

		// Activation Effect가 걸려있다면 회복속도가 2배가 된다.
		if (pSlayer->isFlag(Effect::EFFECT_CLASS_ACTIVATION))
		{
			if ( pPotion->getItemType() >= 14 && pPotion->getItemType() <= 17 )
			{
				// 쓸 수는 있다.
			}
			else
			{
				HPDelayProvider = (HPDelayProvider>>1);
				MPDelayProvider = (MPDelayProvider>>1);

				HPDelayProvider = max(HPDelayProvider, 1);
				MPDelayProvider = max(MPDelayProvider, 1);
			}
		}

		// HP 회복양이 존재한다면...
		if (HPAmount != 0 && HPQuantity != 0)
		{
			if (CurrentHP < MaxHP) 
			{
				EffectManager* pEffectManager = pSlayer->getEffectManager();

				double temp     = (double)((double)HPAmount/(double)HPQuantity);
				int    Period   = (uint)ceil(temp);
				Turn_t Deadline = Period* HPDelayProvider;

				if (pSlayer->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
				{
					Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
					EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

					// 기존의 단위양과 횟수로 채우는 HP양을 계산한다.
					// 그것을 현재 회복양에 더한다.
					int PrevHPAmount = pEffectHPRecoveryEffect->getHPQuantity()* pEffectHPRecoveryEffect->getPeriod();
					HPAmount = min((int)(HPAmount + PrevHPAmount), MaxHP - CurrentHP);

					// 둘 중에 큰 단위회복양과 작은 딜레이를 얻어낸다.
					HPQuantity      = max(HPQuantity,      (int)(pEffectHPRecoveryEffect->getHPQuantity()));
					HPDelayProvider = min(HPDelayProvider, (int)(pEffectHPRecoveryEffect->getDelay()));

					// 현재 회복양을 가지고, 얼마씩 몇번에 회복할 것인가를 결정한다.
					temp     = (double)((double)HPAmount/(double)HPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period* HPDelayProvider;

					// HP Recovery effect를 갱신한다.
					pEffectHPRecoveryEffect->setDeadline(Deadline);
					pEffectHPRecoveryEffect->setDelay(HPDelayProvider);
					pEffectHPRecoveryEffect->setHPQuantity(HPQuantity);
					pEffectHPRecoveryEffect->setPeriod(Period);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(pEffectHPRecoveryEffect->getPeriod());
					gcHPRecoveryStartToSelf.setDelay(pEffectHPRecoveryEffect->getDelay());
					gcHPRecoveryStartToSelf.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// 회복 시작하라는 패킷을 다른이들에게 보낸다.
					// 회복 갱신 패킷, 시작과 똑 같은 패킷을 보낸다.
					GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
					gcHPRecoveryStartToOthers.setObjectID(pSlayer->getObjectID());
					gcHPRecoveryStartToOthers.setPeriod(pEffectHPRecoveryEffect->getPeriod());
					gcHPRecoveryStartToOthers.setDelay(pEffectHPRecoveryEffect->getDelay());
					gcHPRecoveryStartToOthers.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

					pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHPRecoveryStartToOthers, pSlayer);
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				} 
				else 
				{
					EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

					pEffectHPRecovery->setTarget(pSlayer);
					pEffectHPRecovery->setDeadline(Deadline);
					pEffectHPRecovery->setDelay(HPDelayProvider);
					pEffectHPRecovery->setNextTime(0);
					pEffectHPRecovery->setHPQuantity(HPQuantity);
					pEffectHPRecovery->setPeriod(Period);

					pEffectManager->addEffect(pEffectHPRecovery);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(Period);
					gcHPRecoveryStartToSelf.setDelay(HPDelayProvider);
					gcHPRecoveryStartToSelf.setQuantity(HPQuantity);

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// 회복 시작하라는 패킷을 보는이들에게 보낸다.
					GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
					gcHPRecoveryStartToOthers.setObjectID(pSlayer->getObjectID());
					gcHPRecoveryStartToOthers.setPeriod(Period);
					gcHPRecoveryStartToOthers.setDelay(HPDelayProvider);
					gcHPRecoveryStartToOthers.setQuantity(HPQuantity);

					pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHPRecoveryStartToOthers, pSlayer);
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				}
			} 
			else 
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		} 
		else 
		{
			notRecoverHP = true;
		}

		// MP 회복양이 존재한다면...
		if (MPAmount != 0 && MPQuantity != 0 )
		{
			if (CurrentMP < MaxMP) 
			{
				EffectManager* pEffectManager = pSlayer->getEffectManager();

				double temp     = (double)((double)MPAmount/(double)MPQuantity);
				uint   Period   = (uint)ceil(temp);
				Turn_t Deadline = Period* MPDelayProvider;

				if (pSlayer->isFlag(Effect::EFFECT_CLASS_MP_RECOVERY)) 
				{
					Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_MP_RECOVERY);
					EffectMPRecovery* pEffectMPRecoveryEffect = dynamic_cast<EffectMPRecovery*>(pEffect);

					// 기존의 단위양과 횟수로 채우는 MP양을 계산한다.
					// 그것을 현재 회복양에 더한다.
					int PrevMPAmount = pEffectMPRecoveryEffect->getMPQuantity()* pEffectMPRecoveryEffect->getPeriod();
					MPAmount = min((int)(MPAmount + PrevMPAmount), MaxMP - CurrentMP);

					// 둘 중에 큰 단위회복양과 작은 딜레이를 얻어낸다.
					MPQuantity      = max(MPQuantity,      (int)(pEffectMPRecoveryEffect->getMPQuantity()));
					MPDelayProvider = min(MPDelayProvider, (int)(pEffectMPRecoveryEffect->getDelay()));

					// 현재 회복양을 가지고, 얼마씩 몇번에 회복할 것인가를 결정한다.
					temp     = (double)((double)MPAmount/(double)MPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period * MPDelayProvider;

					// MP Recovery effect를 갱신한다.
					pEffectMPRecoveryEffect->setDeadline(Deadline);
					pEffectMPRecoveryEffect->setDelay(MPDelayProvider);
					pEffectMPRecoveryEffect->setMPQuantity(MPQuantity);
					pEffectMPRecoveryEffect->setPeriod(Period);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCMPRecoveryStart gcMPRecoveryStart;
					gcMPRecoveryStart.setPeriod(pEffectMPRecoveryEffect->getPeriod());
					gcMPRecoveryStart.setDelay(pEffectMPRecoveryEffect->getDelay());
					gcMPRecoveryStart.setQuantity(pEffectMPRecoveryEffect->getMPQuantity());

					pGamePlayer->sendPacket(&gcMPRecoveryStart);

					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				} 
				else 
				{
					EffectMPRecovery* pEffectMPRecovery = new EffectMPRecovery();

					pEffectMPRecovery->setTarget(pSlayer);
					pEffectMPRecovery->setDeadline(Deadline);
					pEffectMPRecovery->setDelay(MPDelayProvider);
					pEffectMPRecovery->setNextTime(0);
					pEffectMPRecovery->setMPQuantity(MPQuantity);
					pEffectMPRecovery->setPeriod(Period);

					pEffectManager->addEffect(pEffectMPRecovery);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCMPRecoveryStart gcMPRecoveryStart;
					gcMPRecoveryStart.setPeriod(Period);
					gcMPRecoveryStart.setDelay(MPDelayProvider);
					gcMPRecoveryStart.setQuantity(MPQuantity);

					pGamePlayer->sendPacket(&gcMPRecoveryStart);

					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				}
			} 
			else 
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		} 
		else 
		{
			notRecoverMP = true;
		}

		if (notRecoverHP && notRecoverMP)
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
		else
		{
			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		}
	}
	else if (pCreature->isVampire())
	{
		Vampire*   pVampire   = dynamic_cast<Vampire*>(pCreature);

		if ( pItem->getItemClass() != Item::ITEM_CLASS_SERUM
			// Mephisto 이펙트가 걸려있으면 혈청 못 먹는다.
			|| pVampire->isFlag(Effect::EFFECT_CLASS_MEPHISTO)
			)
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}

		HP_t   MaxHP       = pVampire->getHP(ATTR_MAX);
		HP_t   CurrentHP   = pVampire->getHP(ATTR_CURRENT);
		Serum* pSerum      = dynamic_cast<Serum*>(pItem);

		int RegenHP = 0;

		RegenHP = pSerum->getHPAmount();
		
		int    RegenPeriod = pSerum->getPeriod();    // 단위 시간의 주기
		int    RegenCount  = pSerum->getCount();     // 몇번 단위 시간을 반복할 것인가?

		//int    RegenHPUnit = (int)((float)MaxHP* (float)RegenHP*0.01); // 한번에 회복하는 HP의 양
		int    RegenHPUnit = RegenHP;
		int    HPAmount    = min(MaxHP - CurrentHP , RegenHPUnit* RegenCount);

		// HP 회복양이 존재한다면...
		if (HPAmount != 0)
		{
			// 얼마씩 몇번 몇초마다.
			if (CurrentHP < MaxHP) 
			{
				EffectManager* pEffectManager = pVampire->getEffectManager(); 
				Turn_t 	       Period         = RegenCount; // 몇번 회복시키나?
				Turn_t	       Deadline       = RegenPeriod* Period;   // 언제 끝나나?

				if (pVampire->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
				{
					Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
					EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

					// 몇번 더 해야 한다는 것을 갱신해 준다.
					Turn_t OldCount  = pEffectHPRecoveryEffect->getPeriod();
					Turn_t NewPeriod = OldCount + Period;
					pEffectHPRecoveryEffect->setPeriod(NewPeriod);
					pEffectHPRecoveryEffect->setDeadline(NewPeriod* RegenPeriod);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(NewPeriod); // 몇번 회복하나?
					gcHPRecoveryStartToSelf.setDelay(RegenPeriod); // 몇 초 단위로 하나?
					gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit); // 한번에 얼마나 회복하나?

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// 회복 시작하라는 패킷을 다른이들에게 보낸다.
					// 회복 갱신 패킷, 시작과 똑 같은 패킷을 보낸다.
					GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
					gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
					gcHPRecoveryStartToOthers.setPeriod(NewPeriod);
					gcHPRecoveryStartToOthers.setDelay(RegenPeriod );
					gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

					pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				} 
				else 
				{
					EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

					pEffectHPRecovery->setTarget(pVampire);
					pEffectHPRecovery->setDeadline(Deadline);
					pEffectHPRecovery->setDelay(RegenPeriod);
					pEffectHPRecovery->setNextTime(0);
					pEffectHPRecovery->setHPQuantity(RegenHPUnit);
					pEffectHPRecovery->setPeriod(Period);

					pEffectManager->addEffect(pEffectHPRecovery);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(Period);
					gcHPRecoveryStartToSelf.setDelay(RegenPeriod);
					gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit);

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// 회복 시작하라는 패킷을 보는이들에게 보낸다.
					GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
					gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
					gcHPRecoveryStartToOthers.setPeriod(Period);
					gcHPRecoveryStartToOthers.setDelay(RegenPeriod);
					gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

					pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);

					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				}
			} 
			else 
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		}
		else
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}

		decreaseItemNum(pItem, pInventory, pVampire->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else if (pCreature->isOusters())
	{
		Ousters*    pOusters    = dynamic_cast<Ousters*>(pCreature);

		bool regenHP = false;
		bool regenMP = false;

		HP_t MaxHP = 0;
		HP_t CurrentHP = 0;
		int HPQuantity = 0;
		int HPDelayProvider = 0;
		HP_t PupaHPAmount = 0;
		int HPAmount = 0;

		if ( pItem->getItemClass() == Item::ITEM_CLASS_PUPA )
		{
			MaxHP    = pOusters->getHP(ATTR_MAX);
			CurrentHP= pOusters->getHP(ATTR_CURRENT);

			Pupa* pPupa = dynamic_cast<Pupa*>(pItem);

			// 한턴에 회복되는 양
			HPQuantity = pPupa->getHPQuantity();

			// 한턴이 몇초 인가.
			HPDelayProvider = pPupa->getHPDelay();

			PupaHPAmount = pPupa->getHPAmount();
			
			HPAmount = min(MaxHP - CurrentHP , (int)PupaHPAmount);
		}
		else if ( pItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI )
		{
			MaxHP    = pOusters->getHP(ATTR_MAX);
			CurrentHP= pOusters->getHP(ATTR_CURRENT);

			ComposMei* pComposMei = dynamic_cast<ComposMei*>(pItem);

			// 한턴에 회복되는 양
			HPQuantity = pComposMei->getHPQuantity();

			// 한턴이 몇초 인가.
			HPDelayProvider = pComposMei->getHPDelay();

			PupaHPAmount = pComposMei->getHPAmount();
			
			HPAmount = min(MaxHP - CurrentHP , (int)PupaHPAmount);
		}

		// HP 회복양이 존재한다면...
		if (HPAmount != 0 && HPQuantity != 0)
		{
			if (CurrentHP < MaxHP) 
			{
				EffectManager* pEffectManager = pOusters->getEffectManager();

				double temp     = (double)((double)HPAmount/(double)HPQuantity);
				int    Period   = (uint)ceil(temp);
				Turn_t Deadline = Period* HPDelayProvider;

				if (pOusters->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
				{
					Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
					EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

					// 기존의 단위양과 횟수로 채우는 HP양을 계산한다.
					// 그것을 현재 회복양에 더한다.
					int PrevHPAmount = pEffectHPRecoveryEffect->getHPQuantity()* pEffectHPRecoveryEffect->getPeriod();
					HPAmount = min((int)(HPAmount + PrevHPAmount), MaxHP - CurrentHP);

					// 둘 중에 큰 단위회복양과 작은 딜레이를 얻어낸다.
					HPQuantity      = max(HPQuantity,      (int)(pEffectHPRecoveryEffect->getHPQuantity()));
					HPDelayProvider = min(HPDelayProvider, (int)(pEffectHPRecoveryEffect->getDelay()));

					// 현재 회복양을 가지고, 얼마씩 몇번에 회복할 것인가를 결정한다.
					temp     = (double)((double)HPAmount/(double)HPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period* HPDelayProvider;

					// HP Recovery effect를 갱신한다.
					pEffectHPRecoveryEffect->setDeadline(Deadline);
					pEffectHPRecoveryEffect->setDelay(HPDelayProvider);
					pEffectHPRecoveryEffect->setHPQuantity(HPQuantity);
					pEffectHPRecoveryEffect->setPeriod(Period);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(pEffectHPRecoveryEffect->getPeriod());
					gcHPRecoveryStartToSelf.setDelay(pEffectHPRecoveryEffect->getDelay());
					gcHPRecoveryStartToSelf.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// 회복 시작하라는 패킷을 다른이들에게 보낸다.
					// 회복 갱신 패킷, 시작과 똑 같은 패킷을 보낸다.
					GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
					gcHPRecoveryStartToOthers.setObjectID(pOusters->getObjectID());
					gcHPRecoveryStartToOthers.setPeriod(pEffectHPRecoveryEffect->getPeriod());
					gcHPRecoveryStartToOthers.setDelay(pEffectHPRecoveryEffect->getDelay());
					gcHPRecoveryStartToOthers.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

					pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcHPRecoveryStartToOthers, pOusters);
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				} 
				else 
				{
					EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

					pEffectHPRecovery->setTarget(pOusters);
					pEffectHPRecovery->setDeadline(Deadline);
					pEffectHPRecovery->setDelay(HPDelayProvider);
					pEffectHPRecovery->setNextTime(0);
					pEffectHPRecovery->setHPQuantity(HPQuantity);
					pEffectHPRecovery->setPeriod(Period);

					pEffectManager->addEffect(pEffectHPRecovery);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(Period);
					gcHPRecoveryStartToSelf.setDelay(HPDelayProvider);
					gcHPRecoveryStartToSelf.setQuantity(HPQuantity);

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// 회복 시작하라는 패킷을 보는이들에게 보낸다.
					GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
					gcHPRecoveryStartToOthers.setObjectID(pOusters->getObjectID());
					gcHPRecoveryStartToOthers.setPeriod(Period);
					gcHPRecoveryStartToOthers.setDelay(HPDelayProvider);
					gcHPRecoveryStartToOthers.setQuantity(HPQuantity);

					pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcHPRecoveryStartToOthers, pOusters);
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				}

				regenHP = true;
			} 
//			decreaseItemNum(pItem, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		}

		MP_t MaxMP = 0;
		MP_t CurrentMP = 0;

		int MPQuantity = 0;
		int MPDelayProvider = 0;
		MP_t ComposMeiMPAmount = 0;
		int MPAmount = 0;

		if ( pItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI )
		{
			MaxMP    = pOusters->getMP(ATTR_MAX);
			CurrentMP= pOusters->getMP(ATTR_CURRENT);
			ComposMei* pComposMei  = dynamic_cast<ComposMei*>(pItem);

			// 한턴에 회복되는 양
			MPQuantity = pComposMei->getMPQuantity();

			// 한턴이 몇초 인가.
			MPDelayProvider = pComposMei->getMPDelay();

			Attr_t INT = pOusters->getINT();

			ComposMeiMPAmount = pComposMei->getMPAmount();
			
			MPAmount = min(MaxMP - CurrentMP , (int)(ComposMeiMPAmount* (double)(1 + (double)((double)INT / 300.0))));
		}
		else if ( pItem->getItemClass() == Item::ITEM_CLASS_PUPA )
		{
			MaxMP    = pOusters->getMP(ATTR_MAX);
			CurrentMP= pOusters->getMP(ATTR_CURRENT);
			Pupa* pPupa  = dynamic_cast<Pupa*>(pItem);

			// 한턴에 회복되는 양
			MPQuantity = pPupa->getMPQuantity();

			// 한턴이 몇초 인가.
			MPDelayProvider = pPupa->getMPDelay();

			Attr_t INT = pOusters->getINT();

			ComposMeiMPAmount = pPupa->getMPAmount();
			
			MPAmount = min(MaxMP - CurrentMP , (int)(ComposMeiMPAmount* (double)(1 + (double)((double)INT / 300.0))));
		}

		// MP 회복양이 존재한다면...
		if (MPAmount != 0 && MPQuantity != 0 )
		{
			if (CurrentMP < MaxMP) 
			{
				EffectManager* pEffectManager = pOusters->getEffectManager();

				double temp     = (double)((double)MPAmount/(double)MPQuantity);
				uint   Period   = (uint)ceil(temp);
				Turn_t Deadline = Period* MPDelayProvider;

				if (pOusters->isFlag(Effect::EFFECT_CLASS_MP_RECOVERY)) 
				{
					Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_MP_RECOVERY);
					EffectMPRecovery* pEffectMPRecoveryEffect = dynamic_cast<EffectMPRecovery*>(pEffect);

					// 기존의 단위양과 횟수로 채우는 MP양을 계산한다.
					// 그것을 현재 회복양에 더한다.
					int PrevMPAmount = pEffectMPRecoveryEffect->getMPQuantity()* pEffectMPRecoveryEffect->getPeriod();
					MPAmount = min((int)(MPAmount + PrevMPAmount), MaxMP - CurrentMP);

					// 둘 중에 큰 단위회복양과 작은 딜레이를 얻어낸다.
					MPQuantity      = max(MPQuantity,      (int)(pEffectMPRecoveryEffect->getMPQuantity()));
					MPDelayProvider = min(MPDelayProvider, (int)(pEffectMPRecoveryEffect->getDelay()));

					// 현재 회복양을 가지고, 얼마씩 몇번에 회복할 것인가를 결정한다.
					temp     = (double)((double)MPAmount/(double)MPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period * MPDelayProvider;

					// MP Recovery effect를 갱신한다.
					pEffectMPRecoveryEffect->setDeadline(Deadline);
					pEffectMPRecoveryEffect->setDelay(MPDelayProvider);
					pEffectMPRecoveryEffect->setMPQuantity(MPQuantity);
					pEffectMPRecoveryEffect->setPeriod(Period);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCMPRecoveryStart gcMPRecoveryStart;
					gcMPRecoveryStart.setPeriod(pEffectMPRecoveryEffect->getPeriod());
					gcMPRecoveryStart.setDelay(pEffectMPRecoveryEffect->getDelay());
					gcMPRecoveryStart.setQuantity(pEffectMPRecoveryEffect->getMPQuantity());

					pGamePlayer->sendPacket(&gcMPRecoveryStart);

					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				} 
				else 
				{
					EffectMPRecovery* pEffectMPRecovery = new EffectMPRecovery();

					pEffectMPRecovery->setTarget(pOusters);
					pEffectMPRecovery->setDeadline(Deadline);
					pEffectMPRecovery->setDelay(MPDelayProvider);
					pEffectMPRecovery->setNextTime(0);
					pEffectMPRecovery->setMPQuantity(MPQuantity);
					pEffectMPRecovery->setPeriod(Period);

					pEffectManager->addEffect(pEffectMPRecovery);

					// 회복 시작하라는 패킷을 자신에게 보낸다.
					GCMPRecoveryStart gcMPRecoveryStart;
					gcMPRecoveryStart.setPeriod(Period);
					gcMPRecoveryStart.setDelay(MPDelayProvider);
					gcMPRecoveryStart.setQuantity(MPQuantity);

					pGamePlayer->sendPacket(&gcMPRecoveryStart);

					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
				}

				regenMP = true;
			} 
//			decreaseItemNum(pItem, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		}

		if ( regenMP || regenHP )
		{
			decreaseItemNum(pItem, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		}
		else
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
		}
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

