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

	#include "GCCannotUse.h"
	#include "GCUseOK.h"
	#include "GCStatusCurrentHP.h"
	#include "GCHPRecoveryStartToSelf.h"
	#include "GCHPRecoveryStartToOthers.h"
	#include "GCMPRecoveryStart.h"
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

	// �ڸ� ���¶�� ����� �� ����.
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

	// �κ��丮�� �ִ� �������� Object�� �޴´�.
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

		// ���Ͽ� ȸ���Ǵ� ��
		int		HPQuantity = pPotion->getHPQuantity();
		int		MPQuantity = pPotion->getMPQuantity();

		// ������ ���� �ΰ�.
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

		// Activation Effect�� �ɷ��ִٸ� ȸ���ӵ��� 2�谡 �ȴ�.
		if (pSlayer->isFlag(Effect::EFFECT_CLASS_ACTIVATION))
		{
			if ( pPotion->getItemType() >= 14 && pPotion->getItemType() <= 17 )
			{
				// �� ���� �ִ�.
			}
			else
			{
				HPDelayProvider = (HPDelayProvider>>1);
				MPDelayProvider = (MPDelayProvider>>1);

				HPDelayProvider = max(HPDelayProvider, 1);
				MPDelayProvider = max(MPDelayProvider, 1);
			}
		}

		// HP ȸ������ �����Ѵٸ�...
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

					// ������ ������� Ƚ���� ä��� HP���� ����Ѵ�.
					// �װ��� ���� ȸ���翡 ���Ѵ�.
					int PrevHPAmount = pEffectHPRecoveryEffect->getHPQuantity()* pEffectHPRecoveryEffect->getPeriod();
					HPAmount = min((int)(HPAmount + PrevHPAmount), MaxHP - CurrentHP);

					// �� �߿� ū ����ȸ����� ���� �����̸� ����.
					HPQuantity      = max(HPQuantity,      (int)(pEffectHPRecoveryEffect->getHPQuantity()));
					HPDelayProvider = min(HPDelayProvider, (int)(pEffectHPRecoveryEffect->getDelay()));

					// ���� ȸ������ ������, �󸶾� ����� ȸ���� ���ΰ��� �����Ѵ�.
					temp     = (double)((double)HPAmount/(double)HPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period* HPDelayProvider;

					// HP Recovery effect�� �����Ѵ�.
					pEffectHPRecoveryEffect->setDeadline(Deadline);
					pEffectHPRecoveryEffect->setDelay(HPDelayProvider);
					pEffectHPRecoveryEffect->setHPQuantity(HPQuantity);
					pEffectHPRecoveryEffect->setPeriod(Period);

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(pEffectHPRecoveryEffect->getPeriod());
					gcHPRecoveryStartToSelf.setDelay(pEffectHPRecoveryEffect->getDelay());
					gcHPRecoveryStartToSelf.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// ȸ�� �����϶�� ��Ŷ�� �ٸ��̵鿡�� ������.
					// ȸ�� ���� ��Ŷ, ���۰� �� ���� ��Ŷ�� ������.
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

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(Period);
					gcHPRecoveryStartToSelf.setDelay(HPDelayProvider);
					gcHPRecoveryStartToSelf.setQuantity(HPQuantity);

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// ȸ�� �����϶�� ��Ŷ�� �����̵鿡�� ������.
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

		// MP ȸ������ �����Ѵٸ�...
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

					// ������ ������� Ƚ���� ä��� MP���� ����Ѵ�.
					// �װ��� ���� ȸ���翡 ���Ѵ�.
					int PrevMPAmount = pEffectMPRecoveryEffect->getMPQuantity()* pEffectMPRecoveryEffect->getPeriod();
					MPAmount = min((int)(MPAmount + PrevMPAmount), MaxMP - CurrentMP);

					// �� �߿� ū ����ȸ����� ���� �����̸� ����.
					MPQuantity      = max(MPQuantity,      (int)(pEffectMPRecoveryEffect->getMPQuantity()));
					MPDelayProvider = min(MPDelayProvider, (int)(pEffectMPRecoveryEffect->getDelay()));

					// ���� ȸ������ ������, �󸶾� ����� ȸ���� ���ΰ��� �����Ѵ�.
					temp     = (double)((double)MPAmount/(double)MPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period * MPDelayProvider;

					// MP Recovery effect�� �����Ѵ�.
					pEffectMPRecoveryEffect->setDeadline(Deadline);
					pEffectMPRecoveryEffect->setDelay(MPDelayProvider);
					pEffectMPRecoveryEffect->setMPQuantity(MPQuantity);
					pEffectMPRecoveryEffect->setPeriod(Period);

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
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

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
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
			// Mephisto ����Ʈ�� �ɷ������� ��û �� �Դ´�.
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
		
		int    RegenPeriod = pSerum->getPeriod();    // ���� �ð��� �ֱ�
		int    RegenCount  = pSerum->getCount();     // ��� ���� �ð��� �ݺ��� ���ΰ�?

		//int    RegenHPUnit = (int)((float)MaxHP* (float)RegenHP*0.01); // �ѹ��� ȸ���ϴ� HP�� ��
		int    RegenHPUnit = RegenHP;
		int    HPAmount    = min(MaxHP - CurrentHP , RegenHPUnit* RegenCount);

		// HP ȸ������ �����Ѵٸ�...
		if (HPAmount != 0)
		{
			// �󸶾� ��� ���ʸ���.
			if (CurrentHP < MaxHP) 
			{
				EffectManager* pEffectManager = pVampire->getEffectManager(); 
				Turn_t 	       Period         = RegenCount; // ��� ȸ����Ű��?
				Turn_t	       Deadline       = RegenPeriod* Period;   // ���� ������?

				if (pVampire->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
				{
					Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
					EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

					// ��� �� �ؾ� �Ѵٴ� ���� ������ �ش�.
					Turn_t OldCount  = pEffectHPRecoveryEffect->getPeriod();
					Turn_t NewPeriod = OldCount + Period;
					pEffectHPRecoveryEffect->setPeriod(NewPeriod);
					pEffectHPRecoveryEffect->setDeadline(NewPeriod* RegenPeriod);

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(NewPeriod); // ��� ȸ���ϳ�?
					gcHPRecoveryStartToSelf.setDelay(RegenPeriod); // �� �� ������ �ϳ�?
					gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit); // �ѹ��� �󸶳� ȸ���ϳ�?

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// ȸ�� �����϶�� ��Ŷ�� �ٸ��̵鿡�� ������.
					// ȸ�� ���� ��Ŷ, ���۰� �� ���� ��Ŷ�� ������.
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

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(Period);
					gcHPRecoveryStartToSelf.setDelay(RegenPeriod);
					gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit);

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// ȸ�� �����϶�� ��Ŷ�� �����̵鿡�� ������.
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

			// ���Ͽ� ȸ���Ǵ� ��
			HPQuantity = pPupa->getHPQuantity();

			// ������ ���� �ΰ�.
			HPDelayProvider = pPupa->getHPDelay();

			PupaHPAmount = pPupa->getHPAmount();
			
			HPAmount = min(MaxHP - CurrentHP , (int)PupaHPAmount);
		}
		else if ( pItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI )
		{
			MaxHP    = pOusters->getHP(ATTR_MAX);
			CurrentHP= pOusters->getHP(ATTR_CURRENT);

			ComposMei* pComposMei = dynamic_cast<ComposMei*>(pItem);

			// ���Ͽ� ȸ���Ǵ� ��
			HPQuantity = pComposMei->getHPQuantity();

			// ������ ���� �ΰ�.
			HPDelayProvider = pComposMei->getHPDelay();

			PupaHPAmount = pComposMei->getHPAmount();
			
			HPAmount = min(MaxHP - CurrentHP , (int)PupaHPAmount);
		}

		// HP ȸ������ �����Ѵٸ�...
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

					// ������ ������� Ƚ���� ä��� HP���� ����Ѵ�.
					// �װ��� ���� ȸ���翡 ���Ѵ�.
					int PrevHPAmount = pEffectHPRecoveryEffect->getHPQuantity()* pEffectHPRecoveryEffect->getPeriod();
					HPAmount = min((int)(HPAmount + PrevHPAmount), MaxHP - CurrentHP);

					// �� �߿� ū ����ȸ����� ���� �����̸� ����.
					HPQuantity      = max(HPQuantity,      (int)(pEffectHPRecoveryEffect->getHPQuantity()));
					HPDelayProvider = min(HPDelayProvider, (int)(pEffectHPRecoveryEffect->getDelay()));

					// ���� ȸ������ ������, �󸶾� ����� ȸ���� ���ΰ��� �����Ѵ�.
					temp     = (double)((double)HPAmount/(double)HPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period* HPDelayProvider;

					// HP Recovery effect�� �����Ѵ�.
					pEffectHPRecoveryEffect->setDeadline(Deadline);
					pEffectHPRecoveryEffect->setDelay(HPDelayProvider);
					pEffectHPRecoveryEffect->setHPQuantity(HPQuantity);
					pEffectHPRecoveryEffect->setPeriod(Period);

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(pEffectHPRecoveryEffect->getPeriod());
					gcHPRecoveryStartToSelf.setDelay(pEffectHPRecoveryEffect->getDelay());
					gcHPRecoveryStartToSelf.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// ȸ�� �����϶�� ��Ŷ�� �ٸ��̵鿡�� ������.
					// ȸ�� ���� ��Ŷ, ���۰� �� ���� ��Ŷ�� ������.
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

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
					GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
					gcHPRecoveryStartToSelf.setPeriod(Period);
					gcHPRecoveryStartToSelf.setDelay(HPDelayProvider);
					gcHPRecoveryStartToSelf.setQuantity(HPQuantity);

					pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

					// ȸ�� �����϶�� ��Ŷ�� �����̵鿡�� ������.
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

			// ���Ͽ� ȸ���Ǵ� ��
			MPQuantity = pComposMei->getMPQuantity();

			// ������ ���� �ΰ�.
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

			// ���Ͽ� ȸ���Ǵ� ��
			MPQuantity = pPupa->getMPQuantity();

			// ������ ���� �ΰ�.
			MPDelayProvider = pPupa->getMPDelay();

			Attr_t INT = pOusters->getINT();

			ComposMeiMPAmount = pPupa->getMPAmount();
			
			MPAmount = min(MaxMP - CurrentMP , (int)(ComposMeiMPAmount* (double)(1 + (double)((double)INT / 300.0))));
		}

		// MP ȸ������ �����Ѵٸ�...
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

					// ������ ������� Ƚ���� ä��� MP���� ����Ѵ�.
					// �װ��� ���� ȸ���翡 ���Ѵ�.
					int PrevMPAmount = pEffectMPRecoveryEffect->getMPQuantity()* pEffectMPRecoveryEffect->getPeriod();
					MPAmount = min((int)(MPAmount + PrevMPAmount), MaxMP - CurrentMP);

					// �� �߿� ū ����ȸ����� ���� �����̸� ����.
					MPQuantity      = max(MPQuantity,      (int)(pEffectMPRecoveryEffect->getMPQuantity()));
					MPDelayProvider = min(MPDelayProvider, (int)(pEffectMPRecoveryEffect->getDelay()));

					// ���� ȸ������ ������, �󸶾� ����� ȸ���� ���ΰ��� �����Ѵ�.
					temp     = (double)((double)MPAmount/(double)MPQuantity);
					Period   = (uint)ceil(temp);
					Deadline = Period * MPDelayProvider;

					// MP Recovery effect�� �����Ѵ�.
					pEffectMPRecoveryEffect->setDeadline(Deadline);
					pEffectMPRecoveryEffect->setDelay(MPDelayProvider);
					pEffectMPRecoveryEffect->setMPQuantity(MPQuantity);
					pEffectMPRecoveryEffect->setPeriod(Period);

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
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

					// ȸ�� �����϶�� ��Ŷ�� �ڽſ��� ������.
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

