//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUsePotionFromQuickSlotHandler.cc
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUsePotionFromQuickSlot.h"

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
	#include "item/Key.h"
	#include "VariableManager.h"
	#include "ctf/FlagManager.h"

    #include "ParkingCenter.h"
	#include "GDRLairManager.h"
	#include "SiegeManager.h"

	#include <math.h>
	#include "EffectHPRecovery.h"
	#include "EffectMPRecovery.h"
	#include "EffectTransportItem.h"
	#include "EffectRecallMotorcycle.h"

	#include "item/Belt.h"
	#include "item/OustersArmsband.h"
	#include "item/Potion.h"
	#include "item/Pupa.h"
	#include "item/ComposMei.h"
	#include "item/EventETC.h"

	#include "GCHPRecoveryStartToSelf.h"
	#include "GCHPRecoveryStartToOthers.h"
	#include "GCMPRecoveryStart.h"
	#include "GCUseOK.h"
	#include "GCCannotUse.h"
	#include "GCModifyInformation.h"
	#include "GCStatusCurrentHP.h"
	#include "Cpackets/CGRideMotorCycle.h"

bool UseYellowCandy(PlayerCreature* pPC, Item* pItem)
{
	if ( pPC->isFlag( Effect::EFFECT_CLASS_PLEASURE_EXPLOSION ) ) return false;
	if ( pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ETC )
	{
		if ( pItem->getItemType() >= 14 )
		{
			EventETCInfo* pInfo = dynamic_cast<EventETCInfo*>(g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ));
			Assert( pInfo != NULL );

			int amount = pInfo->getFunction();

			Zone* pZone = pPC->getZone();
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
				return false;
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUsePotionFromQuickSlotHandler::execute (CGUsePotionFromQuickSlot* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature   = pGamePlayer->getCreature();

	// �ڸ� ���¶�� ����� �� ����.
	if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	try 
	{
		if ( pCreature->isSlayer() )
		{
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
			Creature*   pCreature   = pGamePlayer->getCreature();

			if (!pCreature->isSlayer()) return;

			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Zone*   pZone   = pSlayer->getZone();
			Item*   pBelt   = pSlayer->getWearItem(Slayer::WEAR_BELT);
			
			
			if (pBelt == NULL)
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}

			// ��Ʈ�� �κ��丮�� �޾ƿ´�.
			Inventory* pBeltInventory = ((Belt*)pBelt)->getInventory();
			
			// SlotID�� �޴´�.
			SlotID_t SlotID = pPacket->getSlotID();

			// ������ ������ �ʰ��ϸ� ����� �� ����.
			if (SlotID >= pBeltInventory->getWidth())
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
			
			// ��Ʈ�� ���� ������ �������� �޾ƿ´�.
			Item* pBeltItem = pBeltInventory->getItem(SlotID, 0);
			
			// �������� ������ �翬�� ����� �� ����.
			if (pBeltItem == NULL)
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
			
			// ������ �ִ� �������� Object�� �޴´�.
			ObjectID_t ItemObjectID = pBeltItem->getObjectID();

			// �����Ͱ� ��ġ���� �ʰų�, ������ �ƴ϶�� ����� �� ����.
			if (ItemObjectID != pPacket->getObjectID() || (pBeltItem->getItemClass() != Item::ITEM_CLASS_POTION && pBeltItem->getItemClass() != Item::ITEM_CLASS_KEY))
			{
				
				if ( ItemObjectID != pPacket->getObjectID() )
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
				}
				else if ( UseYellowCandy(pSlayer, pBeltItem) )
				{
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
					decreaseItemNum(pBeltItem, pBeltInventory, pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), SlotID, 0);
				}
				else
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
				}

				return;
			}
		
			
			if( pBeltItem->getItemClass() == Item::ITEM_CLASS_KEY)
			{
				if (!g_pVariableManager->isSummonMotorcycle()
			        || pSlayer->hasRideMotorcycle()
		    	    || pBeltItem->getItemClass() != Item::ITEM_CLASS_KEY
		        	|| pSlayer->isFlag(Effect::EFFECT_CLASS_COMA)
			        || (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & SAFE_ZONE)
			        || pZone->isMasterLair() || pZone->isNoPortalZone()
			        || (!pGamePlayer->isPremiumPlay() && !pGamePlayer->isPayPlaying())
			        || g_pFlagManager->isInPoleField( ZONE_COORD( pZone->getZoneID(), pCreature->getX(), pCreature->getY() ) )
			        || GDRLairManager::Instance().isGDRLairZone( pZone->getZoneID() )    )
			    {
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
					return;
				}
			   	
				if ( SiegeManager::Instance().isSiegeZone(pSlayer->getZoneID()) )
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
					return;
				}

				// ������ �������� �����Ǿ� �ִ����� Ȯ���Ѵ�.
				ItemID_t targetID = dynamic_cast<Key*>(pBeltItem)->getTarget();

				Statement* pStmt   = NULL;
				Result*    pResult = NULL;
				
				if (targetID==0)
				{
					Key* pKey = dynamic_cast<Key*>(pBeltItem);
					Assert( pKey != NULL );

					targetID = pKey->setNewMotorcycle(pSlayer);

				}
				else
				{
					// �ѹ� ���ͻ���Ŭ�̶� Ű�� ����ƴµ� ���ͻ���Ŭ�� ���� �ڲ� ���쳪����.
					// Ű�� ����� ���ͻ���Ŭ�� ������ ��� �ִ��� üũ�ϰ� ������ ���� ���� �־��ش�.
					BEGIN_DB
					{
						pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
						pResult = pStmt->executeQuery("SELECT ItemID FROM MotorcycleObject WHERE ItemID=%lu", targetID);

						if ( !pResult->next() )
						{
							Key* pKey = dynamic_cast<Key*>(pBeltItem);
							Assert( pKey != NULL );

							targetID = pKey->setNewMotorcycle(pSlayer);
						}

						SAFE_DELETE(pStmt);
					}
					END_DB(pStmt);
				}
				  // �ʻ� ��� �ڵ� -_-;
				if (targetID==0)
				{
					filelog("errorLog.txt", "[ActionRedeemMotorcycle] itemID=%lu, motorItemID=%lu", (int)pBeltItem->getItemID(), (int)targetID);
					return;
				}



				if (g_pParkingCenter->hasMotorcycleBox(targetID))
				{
					cout << "������ �ҷ��� ������̰� �ֽ��ϴ�" << endl;

					MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox(targetID);

					if (pMotorcycleBox!=NULL
						&& !pMotorcycleBox->isTransport())
					{
						Zone* pMotorZone = pMotorcycleBox->getZone();
						ZoneCoord_t motorX = pMotorcycleBox->getX();
						ZoneCoord_t motorY = pMotorcycleBox->getY();
						Motorcycle* pMotorcycle = pMotorcycleBox->getMotorcycle();

						// ���� ���� �ִ� ���
						// �Ÿ��� �ʹ� ������ �θ��� ����~
						if (pMotorZone!=pZone
							|| pSlayer->getDistance(motorX, motorY) > 15)
						{
							// �ٸ� zone���� �̵����̶�� ǥ���Ѵ�.
							pMotorcycleBox->setTransport();

							// motorcycle�� slayer�� zone���� �ű��.
/*							pMotorZone->transportItem( motorX, motorY, pMotorcycle,
														pZone, pSlayer->getX(), pSlayer->getY() );*/
							EffectRecallMotorcycle* pEffectRecallMotorcycle =
								new EffectRecallMotorcycle(pMotorZone, motorX, motorY, pZone, pSlayer->getX(), pSlayer->getY(), pMotorcycle, pSlayer->getObjectID(), 0);
							pMotorZone->registerObject( pEffectRecallMotorcycle );
							pMotorZone->addEffect_LOCKING( pEffectRecallMotorcycle );

							// Use OK ����̴�.
							// Use�ϸ� �������� ��������� �׷��� �ʹ�. - -;
							/*
							GCCannotUse _GCCannotUse;
							_GCCannotUse.setObjectID(pPacket->getObjectID());
							*/

							// �ѵ��� delay�� ����ϴµ�..
						}
					}

					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);

					return;
				}
				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pResult = pStmt->executeQuery("SELECT ItemID, ItemType, OptionType, Durability FROM MotorcycleObject WHERE ItemID=%lu", targetID);

					ItemID_t     itemID;
					ItemType_t   itemType;
					list<OptionType_t> optionTypes;
					Durability_t durability;

					bool bFound = false;

					if (pResult->next())
					{
						bFound = true;

						itemID     = pResult->getInt(1);
						itemType   = pResult->getInt(2);

						string optionField = pResult->getString(3);
						setOptionTypeFromField(optionTypes, optionField);

						durability = pResult->getInt(4);
					}
					else
					{
						itemID     = targetID;
						itemType   = 0;
						durability = 300;
					}

					// ���ο� ������� ��ü�� �����Ѵ�.
					Motorcycle* pMotorcycle = new Motorcycle(itemType, optionTypes);

					Assert(pMotorcycle != NULL);

					pMotorcycle->setItemID(itemID);
					pMotorcycle->setDurability(durability);

					// Object ID �Ҵ�ޱ�
					(pZone->getObjectRegistry()).registerObject(pMotorcycle);


					// ������̸� ���� �߰��Ѵ�.
					cout << "������̸� ���� �߰��մϴ�" << pSlayer->getX() << " " << pSlayer->getY() << endl;
					TPOINT pt = pZone->addItem(pMotorcycle, pSlayer->getX(), pSlayer->getY(), false);

				   if(pt.x == -1)
					{
						StringStream msg;
						msg << "������̸� ���� ���� �� �����ϴ�: "
							<< "ZoneID=" << (int)pZone->getZoneID()
							<< ", X=" << (int)pSlayer->getX()
							<< ", Y=" << (int)pSlayer->getY();

						filelog("motorError.txt", "%s", msg.toString().c_str());
						//throw Error("������̸� ���� ���� �� �����ϴ�");

						SAFE_DELETE(pMotorcycle);
					}
					else
					{
						if (!bFound)
						{
							// by sigi. 2002.10.14
							pStmt->executeQuery(
							"INSERT INTO MotorcycleObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Durability) Values (%d, %d, %d, '', %d, %d, %d, %d, '', %d)",
								itemID, pMotorcycle->getObjectID(), itemType, STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y, durability);
						}

						// ������̸� Parking Center�� ����Ѵ�.
						MotorcycleBox* pBox = new MotorcycleBox(pMotorcycle, pZone, pt.x, pt.y);
						Assert(pBox != NULL);
						g_pParkingCenter->addMotorcycleBox(pBox);

						// Ÿ������.
						CGRideMotorCycle cgRide;
						cgRide.setObjectID( pMotorcycle->getObjectID() );
						cgRide.setX(pt.x);
						cgRide.setY(pt.y);
						cgRide.execute( pGamePlayer );
					}


					// ���� ��Ŷ�̴�.
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);

					SAFE_DELETE(pStmt);
				}
				END_DB(pStmt);

				return;
			}

			HP_t    MaxHP        = pSlayer->getHP(ATTR_MAX);
			HP_t    CurrentHP    = pSlayer->getHP(ATTR_CURRENT);
			MP_t    MaxMP        = pSlayer->getMP(ATTR_MAX);
			MP_t    CurrentMP    = pSlayer->getMP(ATTR_CURRENT);
			Potion* pPotion      = dynamic_cast<Potion*>(pBeltItem);

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

			int     HPAmount     = min(MaxHP - CurrentHP , (int)PotionHPAmount);
			int     MPAmount     = min(MaxMP - CurrentMP , (int)(pPotion->getMPAmount()* (1 + (double)((double)INT / 300.0))));
			bool    notRecoverHP = false;
			bool    notRecoverMP = false;

			// Activation Effect�� �ɷ��ִٸ� ȸ���ӵ��� 2�谡 �ȴ�.
			if (pSlayer->isFlag(Effect::EFFECT_CLASS_ACTIVATION))
			{
				if ( pPotion->getItemType() >= 14 && pPotion->getItemType() <= 17 )
				{
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
					uint   Period   = (uint)ceil(temp);
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
				// �󸶾� ��� ���ʸ���.
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
						Deadline = Period* MPDelayProvider;

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
				decreaseItemNum(pBeltItem, pBeltInventory, pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), SlotID, 0);
			}
		}
		else if ( pCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			Zone*   pZone   = pOusters->getZone();

			// SlotID�� �޴´�.
			SlotID_t SlotID = pPacket->getSlotID();

			Ousters::WearPart part = ( SlotID > 2 ? Ousters::WEAR_ARMSBAND2 : Ousters::WEAR_ARMSBAND1 );
			if ( SlotID > 2 ) SlotID -= 3;

			Item* pOustersArmsband = pOusters->getWearItem(part);
			
			if (pOustersArmsband == NULL)
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}

			// ��Ʈ�� �κ��丮�� �޾ƿ´�.
			Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pOustersArmsband)->getInventory();
			
			// ������ ������ �ʰ��ϸ� ����� �� ����.
			if (SlotID >= pOustersArmsbandInventory->getWidth())
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
			
			// ��Ʈ�� ���� ������ �������� �޾ƿ´�.
			Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(SlotID, 0);
			
			// �������� ������ �翬�� ����� �� ����.
			if (pOustersArmsbandItem == NULL)
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
			
			// ������ �ִ� �������� Object�� �޴´�.
			ObjectID_t ItemObjectID = pOustersArmsbandItem->getObjectID();

			// �����Ͱ� ��ġ���� �ʰų�, Ǫ�ĳ� ���������̰� �ƴ϶�� ����� �� ����.
			if (ItemObjectID != pPacket->getObjectID()
				|| ( pOustersArmsbandItem->getItemClass() != Item::ITEM_CLASS_PUPA && pOustersArmsbandItem->getItemClass() != Item::ITEM_CLASS_COMPOS_MEI )
				)
			{
				if ( ItemObjectID != pPacket->getObjectID() )
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
				}
				else if ( UseYellowCandy(pOusters, pOustersArmsbandItem) )
				{
					GCUseOK _GCUseOK;
					pGamePlayer->sendPacket(&_GCUseOK);
					decreaseItemNum(pOustersArmsbandItem, pOustersArmsbandInventory, pOusters->getName(), STORAGE_BELT, pOustersArmsband->getItemID(), SlotID, 0);
				}
				else
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
				}

				return;
			}

			bool regenHP = false;
			bool regenMP = false;

			HP_t MaxHP = 0;
			HP_t CurrentHP = 0;
			int HPQuantity = 0;
			int HPDelayProvider = 0;
			HP_t PupaHPAmount = 0;
			int HPAmount = 0;

			if ( pOustersArmsbandItem->getItemClass() == Item::ITEM_CLASS_PUPA )
			{
				MaxHP    = pOusters->getHP(ATTR_MAX);
				CurrentHP= pOusters->getHP(ATTR_CURRENT);

				Pupa* pPupa = dynamic_cast<Pupa*>(pOustersArmsbandItem);

				// ���Ͽ� ȸ���Ǵ� ��
				HPQuantity = pPupa->getHPQuantity();

				// ������ ���� �ΰ�.
				HPDelayProvider = pPupa->getHPDelay();

				PupaHPAmount = pPupa->getHPAmount();
				
				HPAmount = min(MaxHP - CurrentHP , (int)PupaHPAmount);
			}
			else if ( pOustersArmsbandItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI )
			{
				MaxHP    = pOusters->getHP(ATTR_MAX);
				CurrentHP= pOusters->getHP(ATTR_CURRENT);

				ComposMei* pComposMei = dynamic_cast<ComposMei*>(pOustersArmsbandItem);

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
	//			decreaseItemNum(pOustersArmsbandItem, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			}

			MP_t MaxMP = 0;
			MP_t CurrentMP = 0;

			int MPQuantity = 0;
			int MPDelayProvider = 0;
			MP_t ComposMeiMPAmount = 0;
			int MPAmount = 0;

			if ( pOustersArmsbandItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI )
			{
				MaxMP    = pOusters->getMP(ATTR_MAX);
				CurrentMP= pOusters->getMP(ATTR_CURRENT);
				ComposMei* pComposMei  = dynamic_cast<ComposMei*>(pOustersArmsbandItem);

				// ���Ͽ� ȸ���Ǵ� ��
				MPQuantity = pComposMei->getMPQuantity();

				// ������ ���� �ΰ�.
				MPDelayProvider = pComposMei->getMPDelay();

				Attr_t INT = pOusters->getINT();

				ComposMeiMPAmount = pComposMei->getMPAmount();
				
				MPAmount = min(MaxMP - CurrentMP , (int)(ComposMeiMPAmount* (double)(1 + (double)((double)INT / 300.0))));
			}
			else if ( pOustersArmsbandItem->getItemClass() == Item::ITEM_CLASS_PUPA )
			{
				MaxMP    = pOusters->getMP(ATTR_MAX);
				CurrentMP= pOusters->getMP(ATTR_CURRENT);
				Pupa* pPupa  = dynamic_cast<Pupa*>(pOustersArmsbandItem);

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
	//			decreaseItemNum(pOustersArmsbandItem, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			}

			if ( regenMP || regenHP )
			{
				decreaseItemNum(pOustersArmsbandItem, pOustersArmsbandInventory, pOusters->getName(), STORAGE_BELT, pOustersArmsband->getItemID(), SlotID, 0);
//				decreaseItemNum(pOustersArmsbandItem, pInventory, pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			}
			else
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
			}
/*			if ( pOustersArmsbandItem->getItemClass() == Item::ITEM_CLASS_PUPA )
			{
				HP_t  MaxHP     = pOusters->getHP(ATTR_MAX);
				HP_t  CurrentHP = pOusters->getHP(ATTR_CURRENT);
				Pupa* pPupa     = dynamic_cast<Pupa*>(pOustersArmsbandItem);

				// ���Ͽ� ȸ���Ǵ� ��
				int		HPQuantity = pPupa->getHPQuantity();

				// ������ ���� �ΰ�.
				int		HPDelayProvider = pPupa->getHPDelay();

				HP_t    PupaHPAmount = 0;

				PupaHPAmount = pPupa->getHPAmount();

				int     HPAmount     = min(MaxHP - CurrentHP , (int)PupaHPAmount);
				bool    notRecoverHP = false;


				// HP ȸ������ �����Ѵٸ�...
				if (HPAmount != 0 && HPQuantity != 0)
				{
					if (CurrentHP < MaxHP) 
					{
						EffectManager* pEffectManager = pOusters->getEffectManager();

						double temp     = (double)((double)HPAmount/(double)HPQuantity);
						uint   Period   = (uint)ceil(temp);
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

				if (notRecoverHP) 
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
					return;
				}
				else
				{
					decreaseItemNum(pOustersArmsbandItem, pOustersArmsbandInventory, pOusters->getName(), STORAGE_BELT, pOustersArmsband->getItemID(), SlotID, 0);
				}
			}
			else if ( pOustersArmsbandItem->getItemClass() == Item::ITEM_CLASS_COMPOS_MEI )
			{
				MP_t    MaxMP        = pOusters->getMP(ATTR_MAX);
				MP_t    CurrentMP    = pOusters->getMP(ATTR_CURRENT);
				ComposMei* pComposMei      = dynamic_cast<ComposMei*>(pOustersArmsbandItem);

				// ���Ͽ� ȸ���Ǵ� ��
				int		MPQuantity = pComposMei->getMPQuantity();

				// ������ ���� �ΰ�.
				int		MPDelayProvider = pComposMei->getMPDelay();

				Attr_t INT = pOusters->getINT();

				MP_t    ComposMeiMPAmount = 0;

				ComposMeiMPAmount = pComposMei->getMPAmount();

				int     MPAmount     = min(MaxMP - CurrentMP , (int)(pComposMei->getMPAmount()* (1 + (double)((double)INT / 300.0))));
				bool    notRecoverMP = false;

				// MP ȸ������ �����Ѵٸ�...
				if (MPAmount != 0 && MPQuantity != 0 )
				{
					// �󸶾� ��� ���ʸ���.
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
							Deadline = Period* MPDelayProvider;

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

				if (notRecoverMP) 
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
					return;
				}
				else
				{
					decreaseItemNum(pOustersArmsbandItem, pOustersArmsbandInventory, pOusters->getName(), STORAGE_BELT, pOustersArmsband->getItemID(), SlotID, 0);
				}
			}*/
		}
	} 
	catch (Throwable & t) 
	{
			//cout << t.toString();
	}
	
#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
