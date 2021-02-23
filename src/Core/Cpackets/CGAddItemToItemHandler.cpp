//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToItemHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////
/*

// ÇÑ ¾ÆÀÌÅÛÀ» µé¾î¼­ ´Ù¸¥ ¾ÆÀÌÅÛ¿¡ ³Ö´Â´Ù.
 [Client]                                               [Server]
           -- CGAddItemToItem
              (mouseItem_ObjectID, invenX, invenY) 
			  =(¸¶¿ì½º¿¡ µé°íÀÖ´Â º°, upgradeÇÒ item XY) -->

            <-- GCAddItemToItemVerify(°á°úÄÚµå, °ü·Ã°ª) ---
   
//-------------+---------------------------------------------
// »ç¿ë packet | client Ã³¸®
//-------------+---------------------------------------------
// ºÒ°¡ packet | ºÒ°¡ message Ãâ·Â
// ½ÇÆÐ packet | ½ÇÆÐ message Ãâ·Â, º° »èÁ¦, [¾ÆÀÌÅÛ Á¦°Å]
// ¼º°ø packet | º° »èÁ¦, optionº¯°æ
//-------------+---------------------------------------------
*/


#include "CGAddItemToItem.h"

#ifdef __GAME_SERVER__
	#include <stdio.h>
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfoManager.h"
	#include "OptionInfo.h"
	#include "ItemUtil.h"
	#include "EventStar.h"
	#include "PetItem.h"
	#include "PetEnchantItem.h"
	#include "PetInfo.h"
	#include "PetAttrInfo.h"
	#include "PetTypeInfo.h"
	#include "CreatureUtil.h"
	#include "MixingItem.h"
	#include "PacketUtil.h"

	#include "Gpackets/GCAddItemToItemVerify.h"
	#include "Gpackets/GCDeleteInventoryItem.h"
	#include "Gpackets/GCCreateItem.h"

	#include "SystemAvailabilitiesManager.h"

	void executeUpGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error);
	void executeEnchantOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeEnchantRareThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY) throw(Error);
	void executeAddOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType) throw(Error);
	void executeTransKit(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error);
	extern bool isPossibleOptionItemClass(Item::ItemClass IClass);

	OptionInfo* getOptionInfo(OptionType_t optionType);

	void    	processUpgradeOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo) throw (Error);
	void		crashItem(Item* pItem, Inventory* pInventory, CoordInven_t invenX, CoordInven_t invenY) throw (Error);
	void    	downgradeOptionType(Item* pItem, OptionType_t currentOptionType, OptionInfo* pOptionInfo) throw (Error);

	void		sendEnchantImpossible(GamePlayer* pGamePlayer) throw (Error);
	void		sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange) throw (Error);
	// add by sonic ³åÈýÊôÐÔ·µ»ØµÄ·â°ü
	void		sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange, DWORD optionCHange2) throw (Error);

#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddItemToItemHandler::execute (CGAddItemToItem* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//cout << pPacket->toString().c_str() << endl;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Assert(pGamePlayer != NULL);	// by sigi

	if (pGamePlayer->getPlayerStatus() == GPS_NORMAL) 
	{
		SYSTEM_ASSERT( SYSTEM_ENCHANT );

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		ObjectID_t      objectID    = pPacket->getObjectID();
		Inventory* 		pInventory  = pPC->getInventory();
		CoordInven_t 	invenX      = pPacket->getX();
		CoordInven_t 	invenY      = pPacket->getY();

		// ÀÎº¥Åä¸®¿¡ ¾ÆÀÌÅÛÀÌ ¾øÀ»¶§(ÁÂÇ¥Ã¼Å©µµ ÇÏ°Ô µÈ´Ù.)
		if (!pInventory->hasItem(invenX, invenY))
		{
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}

		// ¸¶¿ì½º ¾ÆÀÌÅÛ
		Item*           pMouseItem  = pPC->getExtraInventorySlotItem();

		// ÀÎº¥Åä¸®¿¡ ÀÖ´Â ¾ÆÀÌÅÛ
		Item*      		pItem       = pInventory->getItem(invenX, invenY);

		// ¾ÆÀÌÅÛÀÌ ¾ø°Å³ª
		// objectID°¡ Àß¸øµÈ °æ¿ì
		if (pMouseItem==NULL
			|| pItem==NULL
			|| pMouseItem->getObjectID()!=objectID
			|| pMouseItem->getNum() != 1 )
		{
			//cout << "Wrong Item" << endl;

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}


		switch (pMouseItem->getItemClass())
		{
			//---------------------------------------------------------
			//
			// 				ITEM_CLASS_EVENT_STAR
			//
			//---------------------------------------------------------
			// ¾ÆÀÌÅÛÀÇ ¿É¼ÇÀ» upgrade ½ÃÅ²´Ù.
			//---------------------------------------------------------
			case Item::ITEM_CLASS_EVENT_STAR : 
			{
				ItemInfo* pItemInfo = g_pEventStarInfoManager->getItemInfo( pMouseItem->getItemType() );
				Assert(pItemInfo!=NULL);

				EventStarInfo* pEventStarInfo = dynamic_cast<EventStarInfo*>(pItemInfo);
				Assert(pEventStarInfo!=NULL);

				int optionSize = pItem->getOptionTypeSize();
				//Éý¼¶×°±¸µÈ¼¶
				if ( (pEventStarInfo->getFunctionFlag() & EventStarInfo::FUNCTION_UP_GRADE) != 0 )
				{
					executeUpGrade(pGamePlayer, pMouseItem, pItem);
				}
				else if (pEventStarInfo->isFunctionTransKit())
				{
					executeTransKit(pGamePlayer, pMouseItem, pItem);
				}
				// Enchant Option
				else if (optionSize>1)	// by sigi. 2002.10.21
				{
					if (pEventStarInfo->isFunctionEnchantRareOption())
					{
						if(pMouseItem->getItemType()==6)// ³åÈýÊôÐÔ×°±¸
							executeEnchantRareThreeOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
						else
							executeEnchantRareOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
					}
					else
					{
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
				}
				else if (pEventStarInfo->isFunctionEnchantOption())
				{
					executeEnchantOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
				}
				// Add Option
				else if (pEventStarInfo->isFunctionAddOption())
				{
					int addOptionType = pEventStarInfo->getFunctionValue();
					executeAddOption(pGamePlayer, pMouseItem, pItem, addOptionType);
				}
			}
			break;

			case Item::ITEM_CLASS_PET_ENCHANT_ITEM :
			{
				//cout << "Trying Pet Enchant... " << endl;
				if ( pItem->getItemClass() != Item::ITEM_CLASS_PET_ITEM )
				{
					//cout << "Æê ¾ÆÀÌÅÛ¿¡´Ù°¡ ÇÑ°Ô ¾Æ´Ô´Ù." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				PetEnchantItemInfo* pItemInfo = dynamic_cast<PetEnchantItemInfo*>(g_pPetEnchantItemInfoManager->getItemInfo( pMouseItem->getItemType() ));
				Assert( pItemInfo != NULL );

				PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
				PetInfo* pPetInfo = NULL;
				if ( pPetItem == NULL || ( pPetInfo = pPetItem->getPetInfo() ) == NULL )
				{
					//cout << "Æê ¾ÆÀÌÅÛÀÌ ¾Æ´Ï°Å³ª Æê ¾ÆÀÌÅÛ¿¡ Æê »óÅÂ°¡ ¾ø½À´Ï´Ù." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				/*
					ENCHANT_FUNCTION = 0,
					SPEC_OPTION_FUNCTION = 1,
					REVIVAL_FUNCTION = 13,
					RARE_FUNCTION = 14
				*/
				switch ( pItemInfo->getFunction() )
				{
					case PetEnchantItemInfo::ENCHANT_FUNCTION :
					{
						if ( pPetInfo->getPetAttr() != 0xff )
						{
							//cout << "ÀÌ¹Ì ÀÎÃ¦Æ®µÈ ¾ÆÀÌÅÛÀÔ´Ï´Ù." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
						//cout << "Ç¥ÁØ ÀÎÃ¦Æ® ½ÃµµÁßÀÔ´Ï´Ù." << endl;
						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						if ( PetAttrInfoManager::Instance().enchantRandomAttr( pPetInfo, pItemInfo->getFunctionGrade() ) )
						{
							//cout << "ÀÎÃ¦Æ® ¼º°ø." << endl;
							pPetItem->savePetInfo();

							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
							gcAddItemToItemVerify.setParameter( ((uint)pPetInfo->getPetAttr())<<16 | (uint)pPetInfo->getPetAttrLevel() );

							pGamePlayer->sendPacket( &gcAddItemToItemVerify );

							if ( pPC->getPetInfo() == pPetInfo )
							{
								//cout << "ÀÌ¹Ì ºÒ·¯Á®ÀÖ¾î¼­ ÆÐÅ¶ º¸³»´Â ÁßÀÔ´Ï´Ù." << endl;
								sendPetInfo( pGamePlayer, true );
								pPC->initAllStatAndSend();
							}
							return;
						}
						else
						{
							//cout << "ÀÎÃ¦Æ® ½ÇÆÐ" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
					}
					break;
					case PetEnchantItemInfo::SPEC_OPTION_FUNCTION :
					{
						if ( pPetInfo->getPetAttr() != 0xff )
						{
							//cout << "ÀÌ¹Ì ÀÎÃ¦Æ®µÈ ¾ÆÀÌÅÛÀÔ´Ï´Ù." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						if ( PetAttrInfoManager::Instance().enchantSpecAttr( pPetInfo, (PetAttr_t)pItemInfo->getFunctionGrade() ) )
						{
							pPetItem->savePetInfo();
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
							gcAddItemToItemVerify.setParameter( ((uint)pPetInfo->getPetAttr())<<16 | (uint)pPetInfo->getPetAttrLevel() );
//							gcAddItemToItemVerify.setParameter( pPetInfo->getPetAttr() );

							pGamePlayer->sendPacket( &gcAddItemToItemVerify );

							if ( pPC->getPetInfo() == pPetInfo )
							{
								sendPetInfo( pGamePlayer, true );
								pPC->initAllStatAndSend();
							}
							return;
						}
						else
						{
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}
					}
					break;
					case PetEnchantItemInfo::RARE_FUNCTION:
					{
						//cout << "Æê ·¹¾î ÀÎÃ¦Æ® ÁßÀÔ´Ï´Ù." << endl;
						if ( pPetInfo->getPetLevel() != 49 )
						{
							//cout << "·¹º§µµ ¾ÈµÈ ³Ñ ÀÎÃ¦Æ®ÇÏÁö ¸¶¼À" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						/*
						OptionType_t targetOption = rand()%87;
						targetOption++;
						*/

						OptionType_t targetOption = 0;
						int ratio = rand() % 100000;
						const list<PetEnchantOption*>& petEnchantOptions = g_pOptionInfoManager->getPetEnchantOptionList();
						list<PetEnchantOption*>::const_iterator itr = petEnchantOptions.begin();
						list<PetEnchantOption*>::const_iterator endItr = petEnchantOptions.end();

						for ( ; itr != endItr ; itr++ )
						{
							PetEnchantOption* pPetEnchantOption = *itr;
							if ( pPetEnchantOption->getRatio() > ratio )
							{
								targetOption = pPetEnchantOption->getOptionType();
								break;
							}
						}

						pPetInfo->setPetOption( targetOption );
						sendPetInfo( pGamePlayer );

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( targetOption );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						char query[100];
						sprintf(query, "PetOption=%u", (uint)targetOption);
						pItem->tinysave(query);
					}
					break;
					case PetEnchantItemInfo::REVIVAL_FUNCTION:
					{
						//cout << "ºÎÈ° ½ÃµµÁß ÀÔ´Ï´Ù."  << endl;
						if ( pPetInfo->getPetHP() != 0 )
						{
							//cout << "¾È Á×Àº ¾Ö ºÎÈ°½ÃÅ°Áö ¸¶¼À" << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						VSDateTime current = VSDateTime::currentDateTime();
						int Days = pPetInfo->getLastFeedTime().daysTo(current);
						if ( Days < 0 ) Days = 0;

						if ( pItemInfo->getItemType() != 14 )
						{
							int value = rand()%100;
							if ( Days >= 8 || value >= (10-Days/2)*10 )
							{
								GCAddItemToItemVerify gcAddItemToItemVerify;
								gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
								pGamePlayer->sendPacket( &gcAddItemToItemVerify );
								return;
							}
						}

						pPetInfo->setPetHP( pItemInfo->getFunctionGrade() );
						pPetInfo->setFeedTime( VSDateTime::currentDateTime() );
						pPetInfo->getPetItem()->savePetInfo();

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK );
						gcAddItemToItemVerify.setParameter( pPetInfo->getPetHP() );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					}
					break;
					case PetEnchantItemInfo::MUTANT_FUNCTION:
					{
						if ( pPetInfo->getPetType() != 1 )
						{
							cout << "¿ïÇÁµ¶ÀÌ ¾Æ´Ï¶ø´Ï´Ù." << endl;
							GCAddItemToItemVerify gcAddItemToItemVerify;
							gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
							pGamePlayer->sendPacket( &gcAddItemToItemVerify );
							return;
						}

						bool summonPet = pPC->getPetInfo() == pPetInfo;

						pPC->deleteItemFromExtraInventorySlot();
						pMouseItem->destroy();
						SAFE_DELETE( pMouseItem );

						PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(2);
						Assert( pPetTypeInfo != NULL );

						pPetInfo->setPetType(2);
						pPetInfo->setPetCreatureType( pPetTypeInfo->getPetCreatureType( pPetInfo->getPetLevel() ) );
						pPetItem->setItemType(2);

						pPetItem->tinysave( "ItemType=2" );

//						if ( pPC->getPetInfo() == pPetInfo ) sendPetInfo( pGamePlayer );
						if ( summonPet )
						{
							pPC->setPetInfo( NULL );
							sendPetInfo( pGamePlayer );
						}

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
						gcAddItemToItemVerify.setParameter( 0 );

						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						GCDeleteInventoryItem gcDI;
						gcDI.setObjectID( pPetItem->getObjectID() );
						pGamePlayer->sendPacket( &gcDI );

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pPetItem->getObjectID(), X, Y );
						Assert( X != -1 );

						GCCreateItem gcCI;
						makeGCCreateItem( &gcCI, pPetItem, X, Y );
						pGamePlayer->sendPacket( &gcCI );

						if ( summonPet )
						{
							pPC->setPetInfo( pPetInfo );
							sendPetInfo( pGamePlayer );
						}
					}
					break;
					default:
					{
						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );
						return;
					}
				}
			}
			break;

			case Item::ITEM_CLASS_MIXING_ITEM :
			{
				if ( pItem->getItemClass() != Item::ITEM_CLASS_PET_ITEM )
				{
					//cout << "Æê ¾ÆÀÌÅÛ¿¡´Ù°¡ ÇÑ°Ô ¾Æ´Ô´Ù." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				MixingItemInfo* pItemInfo = dynamic_cast<MixingItemInfo*>(g_pMixingItemInfoManager->getItemInfo( pMouseItem->getItemType() ));
				Assert( pItemInfo != NULL );

				if ( pItemInfo->getType() != MixingItemInfo::TYPE_DETACH )
				{
					//cout << "Æê ¾ÆÀÌÅÛ¿¡´Ù°¡ ÇÑ°Ô ¾Æ´Ô´Ù." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
				PetInfo* pPetInfo = NULL;
				if ( pPetItem == NULL || ( pPetInfo = pPetItem->getPetInfo() ) == NULL || pPetInfo->getPetOption() == 0 )
				{
					//cout << "Æê ¾ÆÀÌÅÛÀÌ ¾Æ´Ï°Å³ª Æê ¾ÆÀÌÅÛ¿¡ Æê »óÅÂ°¡ ¾ø½À´Ï´Ù." << endl;
					GCAddItemToItemVerify gcAddItemToItemVerify;
					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
					pGamePlayer->sendPacket( &gcAddItemToItemVerify );
					return;
				}

				pPC->deleteItemFromExtraInventorySlot();
				pMouseItem->destroy();
				SAFE_DELETE( pMouseItem );

				pPetInfo->setPetOption(0);
				pPetItem->tinysave("PetOption=0");

				GCAddItemToItemVerify gcAddItemToItemVerify;
				gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
				gcAddItemToItemVerify.setParameter(0);

				pGamePlayer->sendPacket( &gcAddItemToItemVerify );

				if ( pPC->getPetInfo() == pPetInfo )
				{
					//cout << "ÀÌ¹Ì ºÒ·¯Á®ÀÖ¾î¼­ ÆÐÅ¶ º¸³»´Â ÁßÀÔ´Ï´Ù." << endl;
					sendPetInfo( pGamePlayer, true );
					pPC->initAllStatAndSend();
				}
				return;
			}
			break;

			default:
			{
				//cout << "upgrade error" << endl;

				GCAddItemToItemVerify gcAddItemToItemVerify;
				gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ERROR );
				pGamePlayer->sendPacket( &gcAddItemToItemVerify );
				return;
			}
		}
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}


#ifdef __GAME_SERVER__
	void executeUpGrade(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem)
		throw(Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* 		pInventory  = pPC->getInventory();

		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() ); 

		int Ratio = 50;

		if ( pPC->getLevel() >= 100 && pMouseItem->getNum() == 1 && pItem->getGrade() < 10 && rand()%100 < Ratio )
		{
			pItem->setGrade( pItem->getGrade() + 1 );
			char buffer[80];
			snprintf(buffer, 80, "Grade=%u", pItem->getGrade() );
			pItem->tinysave(buffer);

			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy();
			SAFE_DELETE(pMouseItem);

			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK );
			gcAddItemToItemVerify.setParameter( pItem->getGrade() );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
		}
		else
		{
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}

		__END_CATCH
	}
	void executeEnchantRareThreeOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
//		Inventory* 		pInventory  = pPC->getInventory();

		// ½ÇÆÐÇÒ È®·üÀº itemType¿¡ ÀÇÇØ¼­ °áÁ¤µÈ´Ù.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

		// ÀÎÃ¦Æ® ÇÒ·Á´Â ¾ÆÀÌÅÛÀÇ ÇöÀç ¿É¼ÇÀÌ 2°³°¡ ¾Æ´Ï°Å³ª
		// À¯´ÏÅ© ¾ÆÀÌÅÛÀÎ °æ¿ì
		// È¤Àº º°À» 2°³ ÀÌ»ó µé°í ÀÎÃ¦Æ®ÇÒ¶ó°í ÇÒ ¶§
		if (pItem->getOptionTypeSize()!=3
			|| pItemInfo->isUnique()
			|| pMouseItem->getNum() != 1
		)
		{
			//cout << "no Option " << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstSucceed = false;
		uint optionChange = 0;
		uint optionChange2 = 0;
		int  shiftValue = 16;
		int  diceValue = 3500;

		list<OptionType_t> optionList = pItem->getOptionTypeList();
		list<OptionType_t>::const_iterator itr = optionList.begin();
		
		OptionType_t thirdOption  = *itr;
		itr++;
		OptionType_t secondOption = *itr;
		itr++;
		OptionType_t firstOption  = *itr;
		itr--;
		itr--;
		
		/*
		OptionType_t thirdOption  = *itr++;
		OptionType_t secondOption = *itr;
		OptionType_t firstOption  = *itr++;
		*/

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );
		OptionInfo* pThirdOptionInfo = getOptionInfo( thirdOption );
//		cout << "firstOption : " << pFirstOptionInfo->getName() <<  endl;
//		cout << "secondOption : " << pSecondOptionInfo->getName() <<  endl;
//		cout << "thirdOption : " << pThirdOptionInfo->getName() <<  endl;
		//Éý¼¶ÎïÆ·ÊôÐÔ¼ì²é
		if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL || pThirdOptionInfo== NULL)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}
		//¼ì²âÊÇ·ñÊÇ¿ÉÉý¼¶ÎïÆ·
		bool bFirstUpgradePossible =  pFirstOptionInfo->isUpgradePossible();
		bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();
		bool bThirdUpgradePossible =  pThirdOptionInfo->isUpgradePossible();
		//¼ì²âÊôÐÔÉý¼¶¿ÉÄÜ
		if ( !bFirstUpgradePossible && !bSecondUpgradePossible && !bThirdUpgradePossible)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}
		//if ((rand() %6000) > diceValue)
			//diceValue*=2;
		if ( bFirstUpgradePossible )
		{
			// Ã¹¹øÂ° ¿É¼ÇÀÇ ÀÎÃ¦Æ® È®·üÀº ºí·çµå·Ó 2ÀÇ È®·ü¿¡ µû¸¥´Ù.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			//int dice = rand()%10000;
			int dice = rand() % diceValue;
			cout << "dice : " << (int)dice <<  endl;
			cout << "diceValue : " << (int)diceValue <<  endl;

			//cout << "Ã¹¹øÂ° ¿É¼Ç : " << pFirstOptionInfo->getHName() << " ÀÎÃ¦Æ® È®·ü " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio ) //Èç¹ûÍ¨¹ý£¬ÔòÉý¼¶×°±¸
			{
				//cout << "ÀÎÃ¦Æ® ¼º°ø" << endl;
				processUpgradeOptionType( pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
				optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
				goto EnOK;
			}
			else
			{
				if (pFirstOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " ¿É¼Ç¶³¾îÁú È®·ü " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// º¯È­¾øÀ½
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// ¿É¼Ç¶³¾îÁü
						downgradeOptionType( pItem, firstOption, pFirstOptionInfo );

						OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
						optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
		shiftValue -= 16;

		if ( bSecondUpgradePossible )
		{
			// µÎ¹øÂ° ¿É¼ÇÀÇ ÀÎÃ¦Æ® È®·üÀº Ã¹¹øÂ° ¿É¼ÇÀÇ ¼º°ø¿©ºÎ¿¡ µû¸¥´Ù.

			int succeedRatio= g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );

			//int dice = rand() %10000;
			int dice = rand() % diceValue;

			//cout << "µÎ¹øÂ° ¿É¼Ç : " << pSecondOptionInfo->getHName() << " ÀÎÃ¦Æ® È®·ü " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				//cout << "ÀÎÃ¦Æ® ¼º°ø" << endl;
				processUpgradeOptionType( pItem, secondOption, pSecondOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
				goto EnOK;
			}
			else
			{
				if (pSecondOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " ¿É¼Ç¶³¾îÁú È®·ü " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// º¯È­¾øÀ½
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// ¿É¼Ç¶³¾îÁü
						downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

						OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
						optionChange = (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
		shiftValue=0;
		if ( bThirdUpgradePossible )
		{
			// µÎ¹øÂ° ¿É¼ÇÀÇ ÀÎÃ¦Æ® È®·üÀº Ã¹¹øÂ° ¿É¼ÇÀÇ ¼º°ø¿©ºÎ¿¡ µû¸¥´Ù.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( thirdOption, bFirstSucceed ) * ( pItemInfo->getUpgradeRatio() +( rand() %50) );
			//int dice = rand() %10000;

			int dice = rand() % diceValue;
			//cout << "µÎ¹øÂ° ¿É¼Ç : " << pSecondOptionInfo->getHName() << " ÀÎÃ¦Æ® È®·ü " << succeedRatio << endl;
			//dice =succeedRatio-1;
			if ( dice < succeedRatio )
			{
				//cout << "ÀÎÃ¦Æ® ¼º°ø" << endl;
				processUpgradeOptionType( pItem, thirdOption, pThirdOptionInfo );

				OptionType_t upgradeOptionType = pThirdOptionInfo->getUpgradeType();
				optionChange2 |= (thirdOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				if (pThirdOptionInfo->getUpgradeSecondRatio() < 5)
				{
					int noChangeRatio = 33;
					int downgradeRatio = 46;
					dice = rand() % 100;

					cout << "downgradeRatio" << pItemInfo->getName() << " ¿É¼Ç¶³¾îÁú È®·ü " << downgradeRatio << endl;

					if ( dice < noChangeRatio )
					{
						// º¯È­¾øÀ½
					}
					else if ( dice < noChangeRatio + downgradeRatio )
					{
						// ¿É¼Ç¶³¾îÁü
						downgradeOptionType( pItem, thirdOption, pThirdOptionInfo );

						OptionType_t previousOptionType = pThirdOptionInfo->getPreviousType();
						optionChange2 |= (thirdOption << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
		}
EnOK:
		//{
			// µé°í ÀÖ´Â º° »èÁ¦
			pPC->deleteItemFromExtraInventorySlot();

			// DB¿¡¼­ »èÁ¦
			pMouseItem->destroy();

			// ¸Þ¸ð¸®¿¡¼­ »èÁ¦
			SAFE_DELETE(pMouseItem);

			// °á°ú ÆÐÅ¶ º¸³»±â
			cout << "optionChange : " << optionChange <<  endl;
			sendEnchantOK(pGamePlayer, optionChange,optionChange2);

		//}

		__END_CATCH
	}
	void executeEnchantRareOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
//		Inventory* 		pInventory  = pPC->getInventory();

		// ½ÇÆÐÇÒ È®·üÀº itemType¿¡ ÀÇÇØ¼­ °áÁ¤µÈ´Ù.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

		// ÀÎÃ¦Æ® ÇÒ·Á´Â ¾ÆÀÌÅÛÀÇ ÇöÀç ¿É¼ÇÀÌ 2°³°¡ ¾Æ´Ï°Å³ª
		// À¯´ÏÅ© ¾ÆÀÌÅÛÀÎ °æ¿ì
		// È¤Àº º°À» 2°³ ÀÌ»ó µé°í ÀÎÃ¦Æ®ÇÒ¶ó°í ÇÒ ¶§
/*		// add by Coffee 2006.11.2  ÅÐ¶ÏÊÇ·ñÎªÈýÊôÐÔÎïÆ·£¬Èç¹ûÊÇ¾Íµ÷ÓÃÐÂ¼ÓµÄ³äÈýÊôÐÔº¯Êý
		if (pItem->getOptionTypeSize() ==3);
		{
			//³åÈýÊôÐÔ×°±¸
			executeEnchantRareThreeOption(pGamePlayer, pMouseItem, pItem, invenX, invenY);
			return;
		}
		// end */
		if (pItem->getOptionTypeSize()!=2
			|| pItemInfo->isUnique()
			|| pMouseItem->getNum() != 1
		)
		{
			cout << "no Option 1" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstSucceed = false;
		uint optionChange = 0;
		int  shiftValue = 16;

		list<OptionType_t> optionList = pItem->getOptionTypeList();
		list<OptionType_t>::const_iterator itr = optionList.begin();

		OptionType_t firstOption = *itr++;
		OptionType_t secondOption = *itr;

		OptionInfo* pFirstOptionInfo = getOptionInfo( firstOption );
		OptionInfo* pSecondOptionInfo = getOptionInfo( secondOption );

		if ( pFirstOptionInfo == NULL || pSecondOptionInfo == NULL )
		{
			cout << "no Option 2" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		bool bFirstUpgradePossible = pFirstOptionInfo->isUpgradePossible();
		bool bSecondUpgradePossible = pSecondOptionInfo->isUpgradePossible();

		if ( !bFirstUpgradePossible && !bSecondUpgradePossible )
		{
			cout << "no Option 3" << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		if ( bFirstUpgradePossible )
		{
			// Ã¹¹øÂ° ¿É¼ÇÀÇ ÀÎÃ¦Æ® È®·üÀº ºí·çµå·Ó 2ÀÇ È®·ü¿¡ µû¸¥´Ù.
			int succeedRatio = pFirstOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			int dice = rand()%10000;

			//cout << "Ã¹¹øÂ° ¿É¼Ç : " << pFirstOptionInfo->getHName() << " ÀÎÃ¦Æ® È®·ü " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "ÀÎÃ¦Æ® ¼º°ø" << endl;
				processUpgradeOptionType( pItem, firstOption, pFirstOptionInfo );

				OptionType_t upgradeOptionType = pFirstOptionInfo->getUpgradeType();
				optionChange = (firstOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "ÀÎÃ¦Æ® ¾ÆÅÛ : " << pItemInfo->getName() << " ¿É¼Ç¶³¾îÁú È®·ü " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// º¯È­¾øÀ½
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// ¿É¼Ç¶³¾îÁü
					downgradeOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// ¿É¼Ç¾ø¾îÁü
					pItem->removeOptionType( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DBº¯°æ
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pFirstOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//¿É¼Ç¶³¾îÁú È®·ü °è»êÇØ¾ß µÈ´Ù.

				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "Ã¹¹øÂ° ¿É¼Ç : " << pFirstOptionInfo->getHName() << " ¿É ¶³¾îÁú È®·ü : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// º¯È­¾øÀ½
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// ¿É¼Ç¶³¾îÁü
					downgradeOptionType( pItem, firstOption, pFirstOptionInfo );

					OptionType_t previousOptionType = pFirstOptionInfo->getPreviousType();
					optionChange = (firstOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// ¿É¼Ç¾ø¾îÁü
					pItem->removeOptionType( firstOption );
					optionChange = (firstOption << (shiftValue+8));

					// DBº¯°æ
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);

				}
			}
		}

		shiftValue -= 16;

		if ( bSecondUpgradePossible )
		{
			// µÎ¹øÂ° ¿É¼ÇÀÇ ÀÎÃ¦Æ® È®·üÀº Ã¹¹øÂ° ¿É¼ÇÀÇ ¼º°ø¿©ºÎ¿¡ µû¸¥´Ù.
			int succeedRatio = g_pOptionInfoManager->getRareUpgradeRatio( secondOption, bFirstSucceed ) * pItemInfo->getUpgradeRatio();
			int dice = rand() %10000;

			//cout << "µÎ¹øÂ° ¿É¼Ç : " << pSecondOptionInfo->getHName() << " ÀÎÃ¦Æ® È®·ü " << succeedRatio << endl;

			if ( dice < succeedRatio )
			{
				//cout << "ÀÎÃ¦Æ® ¼º°ø" << endl;
				processUpgradeOptionType( pItem, secondOption, pSecondOptionInfo );

				OptionType_t upgradeOptionType = pSecondOptionInfo->getUpgradeType();
				optionChange |= (secondOption << (shiftValue+8)) | (upgradeOptionType << shiftValue);

				bFirstSucceed = true;
			}
			else
			{
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				dice = rand() % 100;

				//cout << "ÀÎÃ¦Æ® ¾ÆÅÛ : " << pItemInfo->getName() << " ¿É¼Ç¶³¾îÁú È®·ü " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// º¯È­¾øÀ½
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// ¿É¼Ç¶³¾îÁü
					downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// ¿É¼Ç¾ø¾îÁü
					pItem->removeOptionType( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DBº¯°æ
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}
		else
		{
			OptionType_t prev = pSecondOptionInfo->getPreviousType();

			if ( prev != 0 )
			{
				//¿É¼Ç¶³¾îÁú È®·ü °è»êÇØ¾ß µÈ´Ù.
				int noChangeRatio = 33;
				int downgradeRatio = pItemInfo->getDowngradeRatio();
				int dice = rand() % 100;

				//cout << "µÎ¹øÂ° ¿É¼Ç : " << pSecondOptionInfo->getHName() << " ¿É ¶³¾îÁú È®·ü : " << downgradeRatio << endl;

				if ( dice < noChangeRatio )
				{
					// º¯È­¾øÀ½
				}
				else if ( dice < noChangeRatio + downgradeRatio )
				{
					// ¿É¼Ç¶³¾îÁü
					downgradeOptionType( pItem, secondOption, pSecondOptionInfo );

					OptionType_t previousOptionType = pSecondOptionInfo->getPreviousType();
					optionChange |= (secondOption << (shiftValue+8)) | (previousOptionType << shiftValue);
				}
				else
				{
					// ¿É¼Ç¾ø¾îÁü
					pItem->removeOptionType( secondOption );
					optionChange |= (secondOption << (shiftValue+8));

					// DBº¯°æ
					string optionField;
					setOptionTypeToField( pItem->getOptionTypeList(), optionField );

					char pField[80];
					sprintf(pField, "OptionType='%s'", optionField.c_str());
					pItem->tinysave(pField);
				}
			}
		}

/*		// ¿É¼ÇÀÌ ¿©·¯°³ÀÎ °æ¿ì´Â ºÒ°¡´ÉÇÏÁö´Â ¾Ê´Ù°í º¸°í..
		// µé°í ÀÖ´Â ¾ÆÀÌÅÛÀÌ ¸Â´ÂÁö È®ÀÎÇÏ°í
		// upgrade°¡´ÉÇÑ optionÀÎ °æ¿ì¿¡...


		//const list<OptionType_t>& optionList = pItem->getOptionTypeList();
		// º¹»çÇØ¼­ ¾´´Ù.. 
		list<OptionType_t>::const_iterator itr = optionList.begin();

		for (; itr!=optionList.end(); itr++)
		{
			OptionType_t currentOptionType = *itr;

			OptionInfo* pOptionInfo = getOptionInfo( currentOptionType );

			if (pOptionInfo==NULL)
			{
				sendEnchantImpossible( pGamePlayer );
				return;
			}

			bool bUpgradePossible = pOptionInfo->isUpgradePossible();

			if (bUpgradePossible)
			{
				//---------------------------------------------------------
				// item°³¼ö°¡ 1°³ÀÎ °æ¿ì¸¸ ÇÒ ¼ö ÀÖµµ·Ï ÇØµÐ´Ù.
				// ¿©·¯°³ÀÎ °æ¿ìµµ °¡´ÉÇÏ°Ô ÇÏ·Á¸é
				// ¾ÆÀÌÅÛ °³¼ö¸¦ ÁÙ¿©¾ß°ÚÁö.. clientµµ ¼öÁ¤ÇØ¾ß ÇÑ´Ù.
				// upgrade ¼º°øÇÒ±î?
				//---------------------------------------------------------
				// ¿É¼ÇÈ®·ü * Å¸ÀÙÈ®·ü / 10000
				//---------------------------------------------------------
				// Ã¹¹øÂ° ¿É¼Ç
				//---------------------------------------------------------
	
				// Ã¹¹øÂ° ¿É¼ÇÀÌ ¼º°øÇÏ¸é µÎ¹øÂ° ¿É¼ÇÈ®·ü·Î °è»êÇÑ´Ù.
				int upgradeRatio = (bFirstSucceed? pOptionInfo->getUpgradeSecondRatio() 
												: pOptionInfo->getUpgradeRatio());


				int succeedRatio = upgradeRatio * pItemInfo->getUpgradeRatio();
				
				int dice = rand()%10000;
				bool bSucceed = (dice < succeedRatio);

				//cout << "EnchantCheck = " 
				//	<< pOptionInfo->getUpgradeRatio() << " * "
				//	<< pItemInfo->getUpgradeRatio() << " = "
				//	<< succeedRatio << ", dice = " << dice << " , succeed=" << (int)bSucceed << endl;

				//cout << "Before = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
				//cout << "CurrentOptionType = " << (int)currentOptionType << endl;


				if (pMouseItem->getNum()==1
					&& bSucceed)
				{
					processUpgradeOptionType( pItem, currentOptionType, pOptionInfo );

					OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();
					optionChange = (currentOptionType << (shiftValue+8)) | (upgradeOptionType << shiftValue);

					bFirstSucceed = true;
					//cout << gcAddItemToItemVerify.toString().c_str() << endl;
				}
				//---------------------------------------------------------
				// upgrade ½ÇÆÐ
				//---------------------------------------------------------
				else
				{
					//cout << "Failed!" << endl;
					bool bCrashItem = pItemInfo->isUpgradeCrash();

					if ( bCrashItem )
					{
						// ¾ÆÀÌÅÛ ºÎ¼ö±â Àü¿¡ ItemTrace Log ³²±âÀÚ ¤Ñ.¤Ñ; 
						if ( pItem != NULL && pItem->isTraceItem() )
						{
							remainTraceLog( pItem, pCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_ENCHANT);
						}
						crashItem(pItem, pInventory, invenX, invenY);

						GCAddItemToItemVerify gcAddItemToItemVerify;
						gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH );
						pGamePlayer->sendPacket( &gcAddItemToItemVerify );

						return;
					}
					else
					{
						// À§¿¡¼­ list¸¦ reference·Î ¾²¸é ¿©±â¿¡¼­ ¿É¼ÇÀÌ Á¦°ÅµÉ ¼ö ÀÖÀ¸¹Ç·Î
						// list iterator°¡ ´ÙÀÌ~µÉ¼öµµ ÀÖ´Ù.
						downgradeOptionType( pItem, currentOptionType, pOptionInfo );

						OptionType_t previousOptionType = pOptionInfo->getPreviousType();
						optionChange = (currentOptionType << (shiftValue+8)) | (previousOptionType << shiftValue);
					}
				}
			}
			else
			{
				impossibleCount ++;
			}

			shiftValue -= 16;
		}*/

		{
			// µé°í ÀÖ´Â º° »èÁ¦
			pPC->deleteItemFromExtraInventorySlot();

			// DB¿¡¼­ »èÁ¦
			pMouseItem->destroy();

			// ¸Þ¸ð¸®¿¡¼­ »èÁ¦
			SAFE_DELETE(pMouseItem);

			// °á°ú ÆÐÅ¶ º¸³»±â
			sendEnchantOK(pGamePlayer, optionChange);
		}

		__END_CATCH
	}

	void executeEnchantOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* 		pInventory  = pPC->getInventory();

		// ItemÀÇ OptionInfo¸¦ ¾ò¾î¿Â´Ù.
		OptionType_t currentOptionType = //pItem->getFirstOptionType();
										pItem->getRandomOptionType();

		int optionSize = pItem->getOptionTypeSize();

		// ½ÇÆÐÇÒ È®·üÀº itemType¿¡ ÀÇÇØ¼­ °áÁ¤µÈ´Ù.
		const ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( 
													pItem->getItemClass(), 
													pItem->getItemType() );

		// ÀÎÃ¦Æ® ÇÒ·Á´Â ¾ÆÀÌÅÛÀÌ ¹«¿ÉÀÌ°Å³ª
		// ·¹¾î ¾ÆÀÌÅÛÀÌ°Å³ª
		// À¯´ÏÅ© ¾ÆÀÌÅÛÀÎ °æ¿ì
		if (optionSize!=1
			|| pItemInfo->isUnique())
		{
			//cout << "no Option " << endl;
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		OptionInfo* pOptionInfo = getOptionInfo( currentOptionType );

		if (pOptionInfo==NULL)
		{
			sendEnchantImpossible( pGamePlayer );
			return;
		}

		// ¿É¼ÇÀÌ ¿©·¯°³ÀÎ °æ¿ì´Â ºÒ°¡´ÉÇÏÁö´Â ¾Ê´Ù°í º¸°í..
		// µé°í ÀÖ´Â ¾ÆÀÌÅÛÀÌ ¸Â´ÂÁö È®ÀÎÇÏ°í
		// upgrade°¡´ÉÇÑ optionÀÎ °æ¿ì¿¡...
		bool bUpgradePossible = pOptionInfo->isUpgradePossible();
		if (optionSize>1 || bUpgradePossible)
		{
			//---------------------------------------------------------
			// item°³¼ö°¡ 1°³ÀÎ °æ¿ì¸¸ ÇÒ ¼ö ÀÖµµ·Ï ÇØµÐ´Ù.
			// ¿©·¯°³ÀÎ °æ¿ìµµ °¡´ÉÇÏ°Ô ÇÏ·Á¸é
			// ¾ÆÀÌÅÛ °³¼ö¸¦ ÁÙ¿©¾ß°ÚÁö.. clientµµ ¼öÁ¤ÇØ¾ß ÇÑ´Ù.
			// upgrade ¼º°øÇÒ±î?
			//---------------------------------------------------------
			// ¿É¼ÇÈ®·ü * Å¸ÀÙÈ®·ü / 10000
			int succeedRatio = 0;

			if ( pMouseItem->getItemType() == 15 )
			{
				// ºí·ç µå·Ó 2~ 2003.5.11
				succeedRatio = pOptionInfo->getUpgradeSecondRatio() * pItemInfo->getUpgradeRatio();
			}
			else
			{
				// ±âÁ¸ ÀÎÃ¦Æ® ¾ÆÅÛµé
				succeedRatio = pOptionInfo->getUpgradeRatio() * pItemInfo->getUpgradeRatio();
			}

//			cout << "¿É¼Ç " << pOptionInfo->getHName() << " ÀÎÃ¦Æ® È®·ü : " << succeedRatio << endl;
			
			int dice = rand()%10000;
			bool bSucceed = (dice < succeedRatio);

			/*
			cout << "EnchantCheck = " 
				<< pOptionInfo->getUpgradeRatio() << " * "
				<< pItemInfo->getUpgradeRatio() << " = "
				<< succeedRatio << ", dice = " << dice << " , succeed=" << (int)bSucceed << endl;
			*/

			//cout << "Before = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
			//cout << "CurrentOptionType = " << (int)currentOptionType << endl;

			// ¿É¼ÇÀÌ ¿©·¯°³ ºÙ¾îÀÖ´Â °æ¿ì¿¡ ÇöÀç ÁöÁ¤ÇÑ ¿É¼ÇÀÌ upgrade°¡ ºÒ°¡´ÉÇÏ´Ù¸é ½ÇÆÐ·Î º»´Ù.
			// À§ÀÇ if¿¡¼­ optionSize>1 À» Ã¼Å©Çß±â ¶§¹®¿¡.. bUpgradePossibleÀÎ °æ¿ì°¡ ¾Æ´Ï¸é,
			// optionSize>1 ÀÌ¶ó°í ÆÇ´ÜÇÒ ¼ö ÀÖ´Ù.
			if (bUpgradePossible
				&& pMouseItem->getNum()==1
				&& bSucceed)
			{
//				cout << "ÀÎÃ¦Æ® ¼º°ø" << endl;
				processUpgradeOptionType( pItem, currentOptionType, pOptionInfo );

				OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();
				uint optionChange = (currentOptionType << 24) | (upgradeOptionType << 16);

				sendEnchantOK( pGamePlayer, optionChange );

				//cout << gcAddItemToItemVerify.toString().c_str() << endl;
			}
			//---------------------------------------------------------
			// upgrade ½ÇÆÐ
			//---------------------------------------------------------
			else
			{
				//cout << "Failed!" << endl;
				bool bCrashItem = pItemInfo->isUpgradeCrash();

				// ½ÇÆÐ packet : ¾ÆÀÌÅÛÀÌ ºÎ¼­Áö´ÂÁö ¾Æ´ÑÁö °áÁ¤
				GCAddItemToItemVerify gcAddItemToItemVerify;

				if ( bCrashItem )
				{
					// ¾ÆÀÌÅÛ ºÎ¼ö±â Àü¿¡ ItemTrace Log ³²±âÀÚ ¤Ñ.¤Ñ; 
					if ( pItem != NULL && pItem->isTraceItem() )
					{
						remainTraceLog( pItem, pCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_ENCHANT);
					}

					crashItem( pItem, pInventory, invenX, invenY );

					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH );

					//cout << "Broken" << endl;
				}
				else
				{
					downgradeOptionType( pItem, currentOptionType, pOptionInfo );

					OptionType_t previousOptionType = pOptionInfo->getPreviousType();
					uint optionChange = (currentOptionType << 24) | (previousOptionType << 16);

					gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE );
					gcAddItemToItemVerify.setParameter( optionChange );
				}

				pGamePlayer->sendPacket( &gcAddItemToItemVerify );

				//cout << "Upgrade Failed " << (bCrashItem? ": Crash!":" ") << endl;
			}

			// µé°í ÀÖ´Â º° »èÁ¦
			pPC->deleteItemFromExtraInventorySlot();

			// DB¿¡¼­ »èÁ¦
			pMouseItem->destroy();

			// ¸Þ¸ð¸®¿¡¼­ »èÁ¦
			SAFE_DELETE(pMouseItem);
		}
		else
		{
			sendEnchantImpossible( pGamePlayer );
			//cout << "upgrade impossible" << endl;
		}

		__END_CATCH
	}

	// ¹«¿É ¾ÆÀÌÅÛ¿¡ ¿É¼ÇÀ» Ãß°¡½ÃÅ²´Ù.
	void executeAddOption(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem, OptionType_t addOptionType)
		throw (Error)
	{
		__BEGIN_TRY

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		// ÇÁ¸®¹Ì¾ö ¼­ºñ½º°¡ ¾Æ´Ñ °æ¿ì´Â ¾ÈµÇÁö..
/*		if (!pGamePlayer->isPayPlaying()
			&& !pGamePlayer->isPremiumPlay())
		{
			//cout << "no Option " << endl;
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );
			return;
		}
*/

		// ÀÌ Å¬·¡½º¿¡ ºÙÀ» ¼ö ÀÖ´Â ¿É¼ÇÅ¬·¡½ºÀÌ°í..
		// ¿É¼ÇÀÌ ¾ø°í
		// À¯´ÏÅ©°¡ ¾Æ´Ï°í
		// ¸¶¿ì½º¿¡ ÇÑ°³¸¸ µé°í ÇÏ´Â °æ¿ì¿¡ ¿É¼Ç Ãß°¡°¡ °¡´ÉÇÏ´Ù.
		if (isPossibleOptionItemClass(pItem->getItemClass())
			&& pItem->getOptionTypeSize()==0 
			&& !pItem->isUnique()
			&& pMouseItem->getNum()==1)
		{
			// ¿É¼Ç º¯°æ
			pItem->addOptionType( addOptionType );
			
			string optionField;
			setOptionTypeToField( pItem->getOptionTypeList(), optionField );

			// DBº¯°æ
			char pField[80];
			sprintf(pField, "OptionType='%s'", optionField.c_str());
			pItem->tinysave(pField);

			uint optionChange = addOptionType;

			// µé°í ÀÖ´Â º° »èÁ¦
			pPC->deleteItemFromExtraInventorySlot();
			pMouseItem->destroy(); 					// DB¿¡¼­ »èÁ¦
			SAFE_DELETE(pMouseItem); 				// ¸Þ¸ð¸®¿¡¼­ »èÁ¦


			// ¼º°øpacket : upgradeµÉ optionÀ» ³Ö¾îÁØ´Ù.
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
			gcAddItemToItemVerify.setParameter( optionChange );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << gcAddItemToItemVerify.toString().c_str() << endl;
		}
		else
		{
			//cout << "Enchant Impossible" << endl;
			//cout << "impossibleOption : " << (int)currentOptionType << endl;
			// upgrade ÇÒ ¼ö ¾ø´Â optionÀÌ´Ù.
			// ºÒ°¡ packet
			GCAddItemToItemVerify gcAddItemToItemVerify;
			gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
			pGamePlayer->sendPacket( &gcAddItemToItemVerify );

			//cout << "upgrade impossible" << endl;
		}

		__END_CATCH
	}

	void executeTransKit(GamePlayer* pGamePlayer, Item* pMouseItem, Item* pItem) throw(Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcResult;
		uint optionChange;

		ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
		if ( pItemInfo->getReqGender() == GENDER_BOTH || pItemInfo->getReqGender() == GENDER_MAX
			|| pItemInfo->isUnique() 
			|| pMouseItem->getNum() != 1 )
		{
			gcResult.setCode( ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE );
			pGamePlayer->sendPacket(&gcResult);
			return;
		}

		ItemType_t newItemType = pItem->getItemType() ^ 1;
		optionChange = ( pItem->getItemType() << 16 ) | newItemType;
		pItem->setItemType( newItemType );

		char query[50];
		sprintf(query, "ItemType=%u", newItemType );
		pItem->tinysave(query);

		gcResult.setCode( ADD_ITEM_TO_ITEM_VERIFY_TRANS_OK );
		gcResult.setParameter( optionChange );
		pGamePlayer->sendPacket(&gcResult);

		Creature*  		pCreature   = pGamePlayer->getCreature();
		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);

		pPC->deleteItemFromExtraInventorySlot();
		pMouseItem->destroy();
		SAFE_DELETE(pMouseItem);

		__END_CATCH
	}

	OptionInfo* getOptionInfo(OptionType_t optionType)
	{
		OptionInfo* pOptionInfo = NULL;

		try {
			pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );

			if (pOptionInfo==NULL)
			{
				filelog("optionError.txt", "CGAddItemToItemHandler: no option [%d]", optionType);

				return NULL;
			}
		} catch (NoSuchElementException& t) {
			filelog("optionError.txt", "CGAddItemToItemHandler: no option [%d]", optionType);

			return NULL;
		}

		return pOptionInfo;
	}


	void	processUpgradeOptionType(
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		//cout << "Succeed!" << endl;
		// upgrageµÉ option
		OptionType_t upgradeOptionType = pOptionInfo->getUpgradeType();

		// ¿É¼Ç º¯°æ
		pItem->changeOptionType( currentOptionType, upgradeOptionType );

		//cout << "Succeed = " << getOptionTypeToString( pItem->getOptionTypeList() );
		
		string optionField;
		setOptionTypeToField( pItem->getOptionTypeList(), optionField );

		//list<OptionType_t> op;
		//setOptionTypeFromField( op, optionField );
		//cout << "Check = " << getOptionTypeToString( op ) << endl;

		// DBº¯°æ
		char pField[80];
		sprintf(pField, "OptionType='%s'", optionField.c_str());
		pItem->tinysave(pField);

		__END_CATCH
	}

	void	crashItem(Item* pItem, Inventory* pInventory, CoordInven_t invenX, CoordInven_t invenY)
		throw (Error)
	{
		__BEGIN_TRY

		// inventory¿¡¼­ ¾ÆÀÌÅÛ Á¦°Å
		pInventory->deleteItem( invenX, invenY );

		// DB¿¡¼­ Á¦°Å
		pItem->destroy();

		// ¸Þ¸ð¸®¿¡¼­ Á¦°Å
		SAFE_DELETE(pItem);

		__END_CATCH
	}

	void	downgradeOptionType(
					Item* pItem,
					OptionType_t currentOptionType,
					OptionInfo* pOptionInfo)
		throw (Error)
	{
		__BEGIN_TRY

		// ¾ÆÀÌÅÛÀÇ ¿É¼ÇÀ» ÇÑ´Ü°è ¶³¾î¶ß¸°´Ù.
		OptionType_t previousOptionType = pOptionInfo->getPreviousType();

		//cout << "FailBefore : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		// ¿É¼Ç º¯°æ
		// ÀÌÀü ¿É¼ÇÀÌ ¾ø´Ù¸é ¾Æ¿¹ ¿É¼ÇÀ» ¾ø¾Ø´Ù.
		if (previousOptionType==0)
		{
			pItem->removeOptionType( currentOptionType );
			//cout << "Remove = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}
		else
		{
			pItem->changeOptionType( currentOptionType, previousOptionType );
			//cout << "Down = " << getOptionTypeToString( pItem->getOptionTypeList() ) << endl;
		}

		// DBº¯°æ
		string optionField;
		setOptionTypeToField( pItem->getOptionTypeList(), optionField );

		//cout << "FailAfter : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

		char pField[80];
		sprintf(pField, "OptionType='%s'", optionField.c_str());
		pItem->tinysave(pField);


		__END_CATCH
	}


	void	sendEnchantImpossible(GamePlayer* pGamePlayer)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

	void	sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK );
		gcAddItemToItemVerify.setParameter( optionChange );
		gcAddItemToItemVerify.setParameter2( 0 );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

	void	sendEnchantOK(GamePlayer* pGamePlayer, DWORD optionChange , DWORD optionChange2)
		throw (Error)
	{
		__BEGIN_TRY

		GCAddItemToItemVerify gcAddItemToItemVerify;
		gcAddItemToItemVerify.setCode( ADD_ITEM_TO_ITEM_VERIFY_THREE_ENCHANT_OK );
		gcAddItemToItemVerify.setParameter( optionChange );
		gcAddItemToItemVerify.setParameter2( optionChange2 );
		pGamePlayer->sendPacket( &gcAddItemToItemVerify );

		__END_CATCH
	}

#endif
