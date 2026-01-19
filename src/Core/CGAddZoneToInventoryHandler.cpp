//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddZoneToInventory.h"

#ifdef __GAME_SERVER__
#include <stdio.h>

#include "Belt.h"
#include "BloodBible.h"
#include "CombatInfoManager.h"
#include "CreatureUtil.h"
#include "EffectHasSlayerRelic.h"
#include "EffectHasSweeper.h"
#include "EffectHasVampireRelic.h"
#include "EffectManager.h"
#include "EffectPrecedence.h"
#include "EffectRelicPosition.h"
#include "GCAddEffect.h"
#include "GCCannotAdd.h"
#include "GCCreateItem.h"
#include "GCDeleteInventoryItem.h"
#include "GCDeleteObject.h"
#include "GCDeleteandPickUpOK.h"
#include "GCNoticeEvent.h"
#include "GCSystemMessage.h"
#include "GamePlayer.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemFactoryManager.h"
#include "ItemUtil.h"
#include "LogClient.h"
#include "OustersArmsband.h"
#include "PacketUtil.h"
#include "PlayerCreature.h"
#include "Relic.h"
#include "RelicUtil.h"
#include "ShrineInfoManager.h"
#include "StringPool.h"
#include "Sweeper.h"
#include "Timeval.h"
#include "VariableManager.h"
#include "Zone.h"
#include "ZoneGroupManager.h"
#include "ZoneUtil.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddZoneToInventoryHandler::execute(CGAddZoneToInventory* pPacket, Player* pPlayer) {
    __BEGIN_TRY __BEGIN_DEBUG_EX __BEGIN_DEBUG

#ifdef __GAME_SERVER__

        Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

    try {
        GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
        Creature* pCreature = pGamePlayer->getCreature();

        if (pCreature == NULL)
            return;

        PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
        bool Merge = false;   // Track whether items were merged during pickup
        bool Success = false; // Whether the pickup/add operation succeeded
        Zone* pZone = pPC->getZone();
        Coord_t ZoneX = pPacket->getZoneX();
        Coord_t ZoneY = pPacket->getZoneY();

        // Ensure the target coordinates are within the zone.
        if (!isValidZoneCoord(pZone, ZoneX, ZoneY))
            goto ERROR;

        Tile& _Tile = pZone->getTile(ZoneX, ZoneY);

        // The tile must contain an item.
        if (!_Tile.hasItem())
            goto ERROR;

        // Item must exist and be portable.
        Item* pItem = _Tile.getItem();
        if (pItem == NULL || !isPortableItem(pItem))
            goto ERROR;

        // Do not allow pickup when carrying is restricted.
        if (!isAbleToPickupItem(pPC, pItem))
            goto ERROR;

        // Verify the object ID matches the packet payload.
        ObjectID_t ItemObjectID = pItem->getObjectID();
        if (ItemObjectID != pPacket->getObjectID())
            goto ERROR;

        // Load inventory and target coordinates.
        Inventory* pInventory = pPC->getInventory();
        CoordInven_t InvenX = pPacket->getInvenX();
        CoordInven_t InvenY = pPacket->getInvenY();

        // Guard against out-of-bounds inventory coordinates.
        if (InvenX >= 10 || InvenY >= 6)
            goto ERROR;

        // Ensure the target slot can accept this item.
        if (!pInventory->canAdding(InvenX, InvenY, pItem))
            goto ERROR;

        // Redundant double-check for overweight state (handled in isAbleToPickup).

        // If a relic has precedence but the picker is not the rightful owner,
        // clear the precedence effect; otherwise block pickup.
        if (isRelicItem(pItem) && pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE)) {
            EffectManager& effectManager = pItem->getEffectManager();

            effectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
            pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
        }

        if (pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE)) {
            Timeval currentTime;
            getCurrentTime(currentTime);

            EffectManager& rEffectManager = pItem->getEffectManager();

            EffectPrecedence* pEffectPrecedence =
                dynamic_cast<EffectPrecedence*>(rEffectManager.findEffect(Effect::EFFECT_CLASS_PRECEDENCE));
            Assert(pEffectPrecedence != NULL);

            if (pEffectPrecedence->getDeadline() < currentTime) {
                // Expired precedence; remove and allow pickup.
                rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
                pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
            } else {
                // Active precedence; only the owner or their party can pick it up.
                if ((pEffectPrecedence->getHostName() == pPC->getName()) ||
                    (pPC->getPartyID() != 0 && pPC->getPartyID() == pEffectPrecedence->getHostPartyID())) {
                    // Authorized; remove the effect and proceed.
                    rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
                    pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
                } else {
                    // Not authorized to pick up.
                    goto ERROR;
                }
            }
        }

        /*
        #ifdef __XMAS_EVENT_CODE__
                // If the inventory already contains the gift box, do not allow another.
                if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX &&
                    pItem->getItemType() == 0 &&
                    pInventory->hasGreenGiftBox()) goto ERROR;
        #endif
        */

        // Stacking logic: if an existing item can absorb this one, move it.
        // Otherwise drop the original and regenerate a new item on the ground.


        // Prefer stacking with an existing item when possible; otherwise create
        // a new inventory slot entry.
        Item::ItemClass itemclass = pItem->getItemClass();
        // ItemType_t itemtype = pItem->getItemType();

        TPOINT pt;
        pt.x = 99;
        pt.y = 99;
        // Find an overlapping item already occupying that slot.
        Item* pPrevItem = pInventory->searchItem(InvenX, InvenY, pItem, pt);

        if (pPrevItem != NULL) {
            if (canStack(pItem, pPrevItem)) {
                // add by sonic 2006.10.30  Prevent stacking time-limited items together
                if (pItem->isTimeLimitItem() || pPrevItem->isTimeLimitItem()) {
                    // cout << "cannot add" << endl;
                    GCCannotAdd _GCCannotAdd;
                    _GCCannotAdd.setObjectID(pPacket->getObjectID());
                    pPlayer->sendPacket(&_GCCannotAdd);
                    return;
                }
                int MaxStack = ItemMaxStack[pItem->getItemClass()];

                if (pt.x == InvenX && pt.y == InvenY) {
                    if (pItem->getNum() + pPrevItem->getNum() > MaxStack) {
                        ItemNum_t CurrentNum = pPrevItem->getNum();
                        ItemNum_t AddNum = pItem->getNum();

                        // If stacking would exceed the cap, fill the existing stack and
                        // leave the remainder in the temp slot. TODO: find a better
                        // target slot instead of splitting here.
                        // pInventory->increaseNum(pItem->getNum());
                        // pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

                        pPrevItem->setNum(MaxStack);
                        pItem->setNum(AddNum + CurrentNum - MaxStack);

                        // pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
                        //  Use tinysave for a lightweight update.
                        char pField[80];
                        sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d, X=%d, Y=%d", pPC->getName().c_str(),
                                MaxStack, STORAGE_INVENTORY, InvenX, InvenY);
                        pPrevItem->tinysave(pField);

                        // pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
                        //  Use tinysave for a lightweight update.
                        sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d", pPC->getName().c_str(), pItem->getNum(),
                                STORAGE_EXTRASLOT);
                        pItem->tinysave(pField);

                    } else {
                        pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());

                        pInventory->increaseNum(pItem->getNum());
                        pInventory->increaseWeight(pItem->getWeight() * pItem->getNum());

                        // pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
                        //  Use tinysave for a lightweight update.
                        char pField[80];
                        sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d, X=%d, Y=%d", pPC->getName().c_str(),
                                pPrevItem->getNum(), STORAGE_INVENTORY, InvenX, InvenY);
                        pPrevItem->tinysave(pField);

                        pItem->destroy();
                        Merge = true;
                        Success = true;
                    }

                    if (g_pVariableManager->getVariable(NETMARBLE_CARD_EVENT) != 0 &&
                        pPrevItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pPrevItem->getItemType() == 2 &&
                        pPrevItem->getNum() == 99) {
                        GCNoticeEvent gcNE;
                        gcNE.setCode(NOTICE_EVENT_NETMARBLE_CARD_FULL);
                        pGamePlayer->sendPacket(&gcNE);
                        cout << "gcNE sent" << endl;
                    }

                    if (pPrevItem->getItemClass() == Item::ITEM_CLASS_LUCKY_BAG && pPrevItem->getItemType() == 3 &&
                        pPrevItem->getNum() == 50) {
                        GCDeleteInventoryItem gcDI;
                        gcDI.setObjectID(pPrevItem->getObjectID());
                        pGamePlayer->sendPacket(&gcDI);

                        pInventory->deleteItem(pPrevItem->getObjectID());
                        pPrevItem->destroy();
                        SAFE_DELETE(pPrevItem);

                        Item* pNewItem =
                            g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_ITEM, 28, list<OptionType_t>());
                        pZone->registerObject(pNewItem);

                        if (!pInventory->addItem(pt.x, pt.y, pNewItem)) {
                            cout << "-_-;" << endl;
                            return;
                        }

                        pNewItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

                        if (pNewItem != NULL) {
                            GCCreateItem gcCI;
                            makeGCCreateItem(&gcCI, pNewItem, pt.x, pt.y);
                            pGamePlayer->sendPacket(&gcCI);
                        }
                    }
                }
            }
        } else {
            pInventory->addItem(InvenX, InvenY, pItem);
            // pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
            //  Use tinysave for a lightweight update.
            char pField[80];
            sprintf(pField, "OwnerID='%s', Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, InvenX,
                    InvenY);
            pItem->tinysave(pField);

            // Belt slot items also need their owner updated. 2003.3.22 by Sequoia
            if (pItem->getItemClass() == Item::ITEM_CLASS_BELT) {
                sprintf(pField, "OwnerID='%s'", pPC->getName().c_str());

                Belt* pBelt = dynamic_cast<Belt*>(pItem);
                Assert(pBelt != NULL);

                Inventory* pBeltInventory = pBelt->getInventory();
                PocketNum_t num = pBelt->getPocketCount();

                for (SlotID_t count = 0; count < num; ++count) {
                    Item* pBeltItem = pBeltInventory->getItem(count, 0);
                    if (pBeltItem != NULL) {
                        pBeltItem->tinysave(pField);
                    }
                }
            }
            // Ousters armband contents also need their owner updated. 2003.3.22 by Sequoia
            if (pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND) {
                sprintf(pField, "OwnerID='%s'", pPC->getName().c_str());

                OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
                Assert(pOustersArmsband != NULL);

                Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
                PocketNum_t num = pOustersArmsband->getPocketCount();

                for (SlotID_t count = 0; count < num; ++count) {
                    Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem(count, 0);
                    if (pOustersArmsbandItem != NULL) {
                        pOustersArmsbandItem->tinysave(pField);
                    }
                }
            }

            Success = true;
        }

        if (Success) {
            // Remove the item from the ground. 2002.12.23
            pZone->deleteItem(pItem, ZoneX, ZoneY);

            GCDeleteandPickUpOK _GCDeleteandPickUpOK;
            GCDeleteObject _GCDeleteObject;
            _GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
            pPlayer->sendPacket(&_GCDeleteandPickUpOK);
            // Notify nearby players that the ground item vanished.
            _GCDeleteObject.setObjectID(pItem->getObjectID());
            //			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);
            //			pZone->broadcastPacket(ZoneX , ZoneY, &_GCDeleteObject , pPC);
            pZone->broadcastPacket(ZoneX, ZoneY, &_GCDeleteObject);

            log(LOG_PICKUP_ITEM, pPC->getName(), "", pItem->toString());

            pItem->whenPCTake(pPC);

            // Apply relic effects if needed.
            if (isRelicItem(itemclass)) {
                addRelicEffect(pPC, pItem);

                deleteEffectRelicPosition(pItem);
            }

            // If this is a flag item, add the flag effect.
            if (pItem->isFlagItem()) {
                addSimpleCreatureEffect(pPC, Effect::EFFECT_CLASS_HAS_FLAG);
            }

            if (pItem->getItemClass() == Item::ITEM_CLASS_SWEEPER) {
                EffectHasSweeper* pEffect = new EffectHasSweeper(pPC);
                pEffect->setPart(pItem->getItemType());

                pPC->setFlag(pEffect->getEffectClass());
                pPC->addEffect(pEffect);
                //	addSimpleCreatureEffect( pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_HAS_SWEEPER +
                // pItem->getItemType()) );

                GCAddEffect gcAddEffect;
                gcAddEffect.setObjectID(pPC->getObjectID());
                gcAddEffect.setEffectID(pEffect->getSendEffectClass());

                pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddEffect);

                // Broadcast a system message about the sweeper pickup
                char race[15];
                if (pCreature->isSlayer()) {
                    sprintf(race, g_pStringPool->c_str(STRID_SLAYER));
                } else if (pCreature->isVampire()) {
                    sprintf(race, g_pStringPool->c_str(STRID_VAMPIRE));
                } else if (pCreature->isOusters()) {
                    sprintf(race, g_pStringPool->c_str(STRID_OUSTERS));
                } else {
                    Assert(false);
                }

                const SweeperInfo* pSweeperInfo =
                    dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pItem->getItemType()));

                char msg[100];
                sprintf(msg, g_pStringPool->c_str(STRID_PICK_UP_SWEEPER), pSweeperInfo->getName().c_str(),
                        pCreature->getName().c_str(), race);
                GCSystemMessage gcSystemMessage;
                gcSystemMessage.setMessage(msg);
                pZone->broadcastPacket(&gcSystemMessage);
            }

            if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 30) {
                unsigned long timeLimit = 3600 * 24;

                pPC->addTimeLimitItem(pItem, timeLimit);
                pPC->sendTimeLimitItemInfo();
                pPC->setBaseLuck(10);
                pPC->initAllStatAndSend();
            }

            /*			else if (itemclass == Item::ITEM_CLASS_EVENT_TREE)
                        {
                        // If this is a small event tree piece
                            if ( itemtype <= 11 )
                            {
                                TPOINT pt = checkEventTree( pPC, InvenX, InvenY );
                            // If a large event tree can be completed, assemble it.
                                if ( pt.x != -1 && pt.y != -1 )
                                {
                                // Remove the small tree pieces that were combined.
                                    deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );
                                    pItem = NULL;	// consumed

                                // Create the completed tree.
                                    list<OptionType_t> optionType;
                                    Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE,
               12, optionType ); pZone->getObjectRegistry().registerObject( pTreeItem ); pInventory->addItem( pt.x,
               pt.y, pTreeItem ); pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

                                // Inform the client that the completed tree has appeared.
                                    GCCreateItem gcCreateItem;
                                    makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
                                    pGamePlayer->sendPacket(&gcCreateItem);
                                }
                            }
                        }
            */
            if (Merge) {
                // Delete the redundant item instance when stacking merged it.
                SAFE_DELETE(pItem);
            }
        } else {
            goto ERROR;
        }

        if (pItem != NULL && pItem->isTraceItem()) {
            char zoneName[15];
            sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), ZoneX, ZoneY);
            remainTraceLog(pItem, zoneName, pCreature->getName(), ITEM_LOG_MOVE, DETAIL_PICKUP);
        }
    } catch (Throwable& t) {
        // cerr << t.toString() << endl;
    }

ERROR:
    GCCannotAdd _GCCannotAdd;
    _GCCannotAdd.setObjectID(pPacket->getObjectID());
    pPlayer->sendPacket(&_GCCannotAdd);
    return;

#endif // __GAME_SERVER__

    __END_DEBUG
    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Legacy event-handling code remains below.
// If you do not fully understand it, avoid modifying it. -- by Rewster
//////////////////////////////////////////////////////////////////////////////
/* Legacy alternate implementation removed for brevity. */
