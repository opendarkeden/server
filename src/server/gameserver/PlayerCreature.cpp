//////////////////////////////////////////////////////////////////////////////
// Filename    : PlayerCreature.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "PlayerCreature.h"

#include "Belt.h"
#include "DB.h"
#include "EventKick.h"
#include "FlagSet.h"
#include "GCModifyInformation.h"
#include "GCModifyNickname.h"
#include "GCMonsterKillQuestInfo.h"
#include "GCNoticeEvent.h"
#include "GCOtherModifyInfo.h"
#include "GCPetStashList.h"
#include "GCRankBonusInfo.h"
#include "GCSystemMessage.h"
#include "GCTimeLimitItemInfo.h"
#include "GamePlayer.h"
#include "GameServerInfoManager.h"
#include "GoodsInventory.h"
#include "Guild.h"
#include "GuildManager.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Key.h"
#include "PKZoneInfoManager.h"
#include "ParkingCenter.h"
#include "Player.h"
#include "Properties.h"
#include "RankBonusInfo.h"
#include "RankExpTable.h"
#include "Stash.h"
#include "StringStream.h"
#include "TimeLimitItemManager.h"
#include "Zone.h"
#include "mission/QuestManager.h"
// #include "QuestManager.h"
// #include "QuestEvent.h"
// #include "Quest.h"
// #include "SimpleQuestLoader.h"
#include <list>

#include "AdvancementClassExpTable.h"
#include "BloodBibleSignInfo.h"
#include "CreatureUtil.h"
#include "DefaultOptionSetInfo.h"
#include "GQuestManager.h"
#include "NicknameBook.h"
#include "Pet.h"
#include "SMSAddressBook.h"
#include "Store.h"
#include "VariableManager.h"
#include "mofus/Mofus.h"

const int MAX_GOODS_INVENTORY_SIZE = 10;

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
PlayerCreature::PlayerCreature(ObjectID_t OID, Player* pPlayer)

    : Creature(OID, pPlayer), m_pAdvancementClass(NULL) {
    __BEGIN_TRY

    m_pInventory = new Inventory(10, 6);
    m_pExtraInventorySlot = new InventorySlot();

    m_pGoodsInventory = new GoodsInventory();

    m_pStash = new Stash;
    m_StashNum = 0;
    m_StashGold = 0;
    m_bStashStatus = false;

    m_pFlagSet = new FlagSet;
    m_isPK = false;
    m_GuildID = 0;

    m_pQuestManager = new QuestManager(this);
    m_pTimeLimitItemManager = new TimeLimitItemManager(this);

    m_bLotto = false;
    m_pQuestItem = NULL;
    m_pPetInfo = NULL;

    m_RankExpSaveCount = 0;
    m_pRank = NULL;
    m_pPet = NULL;
    //	m_pSMSAddressBook = NULL;
    m_pSMSAddressBook = new SMSAddressBook(this);
    m_SMSCharge = 0;
    //	m_pNicknameBook = NULL;
    m_pNicknameBook = new NicknameBook(this);
    m_pNickname = NULL;

    m_PetStash.reserve(MAX_PET_STASH);
    for (int i = 0; i < MAX_PET_STASH; ++i)
        m_PetStash.push_back(NULL);

    m_pGQuestManager = new GQuestManager(this);
    m_pBloodBibleSign = new BloodBibleSignInfo;
    m_BaseLuck = 0;
    m_pStore = new Store;
    m_bAdvanced = false;
    m_AdvancementClassExpSaveCount = 0;

    m_AdvancedAttrBonus = 0;
    m_AdvancedSTR = 0;
    m_AdvancedDEX = 0;
    m_AdvancedINT = 0;
    m_MasterEffectColor = 0;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
PlayerCreature::~PlayerCreature()

{
    __BEGIN_TRY

    // Delete inventories and pointer-held item.
    SAFE_DELETE(m_pInventory);

    SAFE_DELETE(m_pGoodsInventory);

    // Delete the item attached to the cursor.
    if (m_pExtraInventorySlot != NULL) {
        Item* pItem = m_pExtraInventorySlot->getItem();
        if (pItem != NULL) {
            if (pItem->getItemClass() == Item::ITEM_CLASS_KEY) {
                Key* pKey = dynamic_cast<Key*>(pItem);
                // Remove the motorcycle box directly from the zone here.
                if (g_pParkingCenter->hasMotorcycleBox(pKey->getTarget())) {
                    g_pParkingCenter->deleteMotorcycleBox(pKey->getTarget());
                }
            }

            m_pExtraInventorySlot->deleteItem();
            SAFE_DELETE(pItem);
        }

        SAFE_DELETE(m_pExtraInventorySlot);
    }

    // Delete stash.
    SAFE_DELETE(m_pStash);

    // Delete flag set.
    SAFE_DELETE(m_pFlagSet);

    // Delete rank bonus map entries.
    for (HashMapRankBonusItor itr = m_RankBonuses.begin(); itr != m_RankBonuses.end(); itr++) {
        SAFE_DELETE(itr->second);
    }
    m_RankBonuses.clear();

    if (m_pTimeLimitItemManager != NULL)
        SAFE_DELETE(m_pTimeLimitItemManager);

    if (m_pQuestManager != NULL)
        SAFE_DELETE(m_pQuestManager);

    /*	for ( list<ItemNameInfo*>::iterator itr = m_ItemNameInfoList.begin(); itr != m_ItemNameInfoList.end(); itr++ )
        {
            ItemNameInfo* pInfo = *itr;
            SAFE_DELETE( pInfo );
        }
        m_ItemNameInfoList.clear();*/

    if (m_pQuestItem != NULL)
        SAFE_DELETE(m_pQuestItem);

    SAFE_DELETE(m_pRank);

    for (int i = 0; i < MAX_PET_STASH; ++i) {
        SAFE_DELETE(m_PetStash[i]);
    }

    SAFE_DELETE(m_pSMSAddressBook);
    SAFE_DELETE(m_pNicknameBook);
    SAFE_DELETE(m_pGQuestManager);
    SAFE_DELETE(m_pBloodBibleSign);
    SAFE_DELETE(m_pStore);
    SAFE_DELETE(m_pAdvancementClass);

    __END_CATCH_NO_RETHROW
}

bool PlayerCreature::load() {
    __BEGIN_TRY

    m_pSMSAddressBook->load();

    m_PowerPoint = loadPowerPoint(getName());

    return true;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Register a single item into the object registry.
// NOTE: caller must lock the registry; this function does not lock internally.
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::registerItem(Item* pItem, ObjectRegistry& OR)

{
    __BEGIN_TRY

    Assert(pItem != NULL);

    // Assign object ID to the item.
    OR.registerObject_NOLOCKED(pItem);
    // Inform time-limit manager about the new OID.
    m_pTimeLimitItemManager->registerItem(pItem);

    // If the item is a belt, also register contained items.
    if (pItem->getItemClass() == Item::ITEM_CLASS_BELT) {
        Belt* pBelt = dynamic_cast<Belt*>(pItem);
        PocketNum_t PocketCount = pBelt->getPocketCount();
        Inventory* pInventory = pBelt->getInventory();

        for (int k = 0; k < PocketCount; k++) {
            Item* pBeltItem = pInventory->getItem(k, 0);
            if (pBeltItem != NULL) {
                OR.registerObject_NOLOCKED(pBeltItem);
                m_pTimeLimitItemManager->registerItem(pBeltItem);
            }
        }
    }

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Register all items inside the inventory.
// NOTE: caller must lock the registry; this function does not lock internally.
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::registerInventory(ObjectRegistry& OR)

{
    __BEGIN_TRY

    list<Item*> ItemList;
    int height = m_pInventory->getHeight();
    int width = m_pInventory->getWidth();

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Item* pItem = m_pInventory->getItem(i, j);
            if (pItem != NULL) {
                // Skip already-registered stacked items.
                list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

                if (itr == ItemList.end()) {
                    // Track to avoid double registration.
                    ItemList.push_back(pItem);

                    // Register and assign OID.
                    registerItem(pItem, OR);

                    i += pItem->getVolumeWidth() - 1;
                }
            }
        }
    }

    __END_CATCH
}

void PlayerCreature::registerInitInventory(ObjectRegistry& OR)

{
    __BEGIN_TRY

    list<Item*> ItemList;
    int height = m_pInventory->getHeight();
    int width = m_pInventory->getWidth();

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Item* pItem = m_pInventory->getItem(i, j);
            if (pItem != NULL) {
                list<Item*>::iterator itr = find(ItemList.begin(), ItemList.end(), pItem);

                if (itr == ItemList.end()) {
                    ItemList.push_back(pItem);

                    pItem->setTraceItem(bTraceLog(pItem));

                    registerItem(pItem, OR);

                    i += pItem->getVolumeWidth() - 1;
                }
            }
        }
    }

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::registerStash(void)

{
    __BEGIN_TRY

    Zone* pZone = getZone();
    ObjectRegistry& OR = pZone->getObjectRegistry();

    __ENTER_CRITICAL_SECTION(OR)

    for (int r = 0; r < STASH_RACK_MAX; r++) {
        for (int i = 0; i < STASH_INDEX_MAX; i++) {
            Item* pStashItem = m_pStash->get(r, i);
            if (pStashItem != NULL)
                registerItem(pStashItem, OR);
        }
    }

    __LEAVE_CRITICAL_SECTION(OR)

    m_bStashStatus = true;

    __END_CATCH
}

void PlayerCreature::registerGoodsInventory(ObjectRegistry& OR)

{
    __BEGIN_TRY

    GoodsInventory::ListItem& goods = m_pGoodsInventory->getGoods();
    GoodsInventory::ListItemItr itr = goods.begin();

    for (; itr != goods.end(); itr++) {
        registerItem((*itr).m_pItem, OR);
    }

    __END_CATCH
}


void PlayerCreature::loadTimeLimitItem() {
    __BEGIN_TRY

    Assert(m_pTimeLimitItemManager != NULL);

    m_pTimeLimitItemManager->load();

    __END_CATCH
}

void PlayerCreature::loadItem()

{
    __BEGIN_TRY

    loadTimeLimitItem();

    m_pNicknameBook->load();
    m_pGQuestManager->init();

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        Result* pResult = pStmt->executeQuery(
            "SELECT ItemType FROM BloodBibleSignObject WHERE OwnerID='%s' ORDER BY ItemType", getName().c_str());

        while (pResult->next()) {
            m_pBloodBibleSign->getList().push_back(pResult->getInt(1));
        }
    }
    END_DB(pStmt);

    __END_CATCH
}

bool PlayerCreature::wasteIfTimeLimitExpired(Item* pItem)

{
    __BEGIN_TRY

    if (pItem == NULL)
        return false;

    if (m_pTimeLimitItemManager->wasteIfTimeOver(pItem)) {
        pItem->waste(STORAGE_TIMEOVER);
        return true;
    }

    return false;

    __END_CATCH
}

void PlayerCreature::sendTimeLimitItemInfo()

{
    __BEGIN_TRY

    GCTimeLimitItemInfo gcTimeLimitItemInfo;

    if (m_pTimeLimitItemManager->makeTimeLimitItemInfo(gcTimeLimitItemInfo)) {
        getPlayer()->sendPacket(&gcTimeLimitItemInfo);
    }

    __END_CATCH
}

void PlayerCreature::addTimeLimitItem(Item* pItem, DWORD time) {
    m_pTimeLimitItemManager->addTimeLimitItem(pItem, time);
}

void PlayerCreature::sellItem(Item* pItem) {
    __BEGIN_TRY

    if (pItem->isTimeLimitItem())
        m_pTimeLimitItemManager->itemSold(pItem);

    __END_CATCH
}

void PlayerCreature::deleteItemByMorph(Item* pItem) {
    __BEGIN_TRY

    if (pItem->isTimeLimitItem())
        m_pTimeLimitItemManager->deleteItemByMorph(pItem);

    __END_CATCH
}

void PlayerCreature::updateItemTimeLimit(Item* pItem, DWORD time) {
    __BEGIN_TRY

    if (pItem->isTimeLimitItem())
        m_pTimeLimitItemManager->updateItemTimeLimit(pItem, time);

    __END_CATCH
}

void PlayerCreature::sendCurrentQuestInfo() const {
    m_pQuestManager->sendQuestInfo();
}

void PlayerCreature::whenQuestLevelUpgrade() {
    static bool bNonPK =
        g_pGameServerInfoManager
            ->getGameServerInfo(1, g_pConfig->getPropertyInt("ServerID"), g_pConfig->getPropertyInt("WorldID"))
            ->isNonPKServer();

    if (bNonPK && getLevel() > 80) {
        GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
        Assert(pGamePlayer != NULL);

        GCSystemMessage gcSM;
        gcSM.setMessage("This non-PK server is only for characters up to level 80."
                        " You will be disconnected in 10 seconds.");
        pGamePlayer->sendPacket(&gcSM);

        bool newEvent = false;
        EventKick* pEvent = dynamic_cast<EventKick*>(pGamePlayer->getEvent(Event::EVENT_CLASS_KICK));
        if (pEvent == NULL) {
            pEvent = new EventKick(pGamePlayer);
            newEvent = true;
        }

        pEvent->setDeadline(100);
        if (newEvent)
            pGamePlayer->addEvent(pEvent);
    }

    if (g_pVariableManager->getVariable(CHOBO_EVENT)) {
        Level_t level = getLevel();
        if (level < 40 && (level % 5) == 0) {
            getGQuestManager()->getGQuestInventory().saveOne(getName(), 13 + (level / 5));
            getPlayer()->sendPacket(getGQuestManager()->getGQuestInventory().getInventoryPacket());

            GCNoticeEvent gcNE;
            gcNE.setCode(NOTICE_EVENT_GIVE_PRESENT_1 + (level / 5));
            getPlayer()->sendPacket(&gcNE);
        }
        if (level == 40) {
            GCNoticeEvent gcNE;
            gcNE.setCode(NOTICE_EVENT_CAN_OPEN_PRESENT_8);
            getPlayer()->sendPacket(&gcNE);
        }
    }

    m_pGQuestManager->levelUp();

    if (getQuestLevel() == 40) {
        GCNoticeEvent gcNE;
        gcNE.setCode(NOTICE_EVENT_CAN_PET_QUEST);
        getPlayer()->sendPacket(&gcNE);
    }

    if (getLevel() >= 10) {
        NicknameInfo* pLevelNickInfo = m_pNicknameBook->getNicknameInfo(1);
        if (pLevelNickInfo == NULL) {
            pLevelNickInfo = new NicknameInfo;
            pLevelNickInfo->setNicknameID(1);
            pLevelNickInfo->setNicknameType(NicknameInfo::NICK_BUILT_IN);
            pLevelNickInfo->setNicknameIndex(0);
            m_pNicknameBook->setNicknameInfo(1, pLevelNickInfo);
        }

        if (pLevelNickInfo->getNicknameType() == NicknameInfo::NICK_BUILT_IN &&
            pLevelNickInfo->getNicknameIndex() != getLevel() / 10) {
            pLevelNickInfo->setNicknameIndex(getLevel() / 10);

            Packet* pNicknamePacket = m_pNicknameBook->getNicknameBookListPacket();
            getPlayer()->sendPacket(pNicknamePacket);
            SAFE_DELETE(pNicknamePacket);

            if (pLevelNickInfo == m_pNickname) {
                GCModifyNickname gcMN;
                gcMN.setObjectID(getObjectID());
                gcMN.setNicknameInfo(m_pNickname);
                getZone()->broadcastPacket(getX(), getY(), &gcMN);
            }
        }
    }

#ifdef __TEST_SERVER__
    if (getLevel() >= 150) {
        increaseAdvancementClassExp(1);
        GCModifyInformation gcMI;
        gcMI.addShortData(MODIFY_ADVANCEMENT_CLASS_LEVEL, getAdvancementClassLevel());
        gcMI.addLongData(MODIFY_ADVANCEMENT_CLASS_GOAL_EXP, getAdvancementClassGoalExp());
        getPlayer()->sendPacket(&gcMI);

        GCOtherModifyInfo gcOMI;
        gcOMI.addShortData(MODIFY_ADVANCEMENT_CLASS_LEVEL, getAdvancementClassLevel());
        getZone()->broadcastPacket(getX(), getY(), &gcOMI, this);
    }
#endif
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::setStashNumEx(BYTE num)

{
    __BEGIN_TRY

    Statement* pStmt = NULL;

    setStashNum(num);

    BEGIN_DB {
        StringStream sqlSlayer;
        StringStream sqlVampire;
        StringStream sqlOusters;

        sqlSlayer << "UPDATE Slayer set StashNum = " << (int)num << " WHERE Name = '" << getName() << "'";
        sqlVampire << "UPDATE Vampire set StashNum = " << (int)num << " WHERE Name = '" << getName() << "'";
        sqlOusters << "UPDATE Ousters set StashNum = " << (int)num << " WHERE Name = '" << getName() << "'";

        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQueryString(sqlSlayer.toString());
        if (!isOusters())
            pStmt->executeQueryString(sqlVampire.toString());
        else
            pStmt->executeQueryString(sqlOusters.toString());

        SAFE_DELETE(pStmt);
    }
    END_DB(pStmt)

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::setStashGoldEx(Gold_t gold)

{
    __BEGIN_TRY

    // cout << "setStashGoldEx Called" << "Name:" << getName() << " Gold: " << (int)gold << endl;
    Statement* pStmt = NULL;

    setStashGold(gold);

    BEGIN_DB {
        StringStream sqlSlayer;
        StringStream sqlVampire;
        StringStream sqlOusters;

        sqlSlayer << "UPDATE Slayer set StashGold = " << (int)gold << " WHERE Name = '" << getName() << "'";
        sqlVampire << "UPDATE Vampire set StashGold = " << (int)gold << " WHERE Name = '" << getName() << "'";
        sqlOusters << "UPDATE Ousters set StashGold = " << (int)gold << " WHERE Name = '" << getName() << "'";

        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQueryString(sqlSlayer.toString());
        if (!isOusters())
            pStmt->executeQueryString(sqlVampire.toString());
        else
            pStmt->executeQueryString(sqlOusters.toString());

        SAFE_DELETE(pStmt);
    }
    END_DB(pStmt)

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::increaseStashGoldEx(Gold_t gold)

{
    __BEGIN_TRY

    Statement* pStmt = NULL;

    setStashGold(m_StashGold + gold);

    BEGIN_DB {
        StringStream sqlSlayer;
        StringStream sqlVampire;
        StringStream sqlOusters;

        sqlSlayer << "UPDATE Slayer set StashGold = " << (int)m_StashGold << " WHERE Name = '" << getName() << "'";
        sqlVampire << "UPDATE Vampire set StashGold = " << (int)m_StashGold << " WHERE Name = '" << getName() << "'";
        sqlOusters << "UPDATE Ousters set StashGold = " << (int)m_StashGold << " WHERE Name = '" << getName() << "'";

        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQueryString(sqlSlayer.toString());
        if (!isOusters())
            pStmt->executeQueryString(sqlVampire.toString());
        else
            pStmt->executeQueryString(sqlOusters.toString());

        SAFE_DELETE(pStmt);
    }
    END_DB(pStmt)

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::decreaseStashGoldEx(Gold_t gold)

{
    __BEGIN_TRY

    Statement* pStmt = NULL;

    setStashGold(m_StashGold - gold);

    BEGIN_DB {
        StringStream sqlSlayer;
        StringStream sqlVampire;
        StringStream sqlOusters;

        sqlSlayer << "UPDATE Slayer set StashGold = " << (int)m_StashGold << " WHERE Name = '" << getName() << "'";
        sqlVampire << "UPDATE Vampire set StashGold = " << (int)m_StashGold << " WHERE Name = '" << getName() << "'";
        sqlOusters << "UPDATE Ousters set StashGold = " << (int)m_StashGold << " WHERE Name = '" << getName() << "'";

        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQueryString(sqlSlayer.toString());
        if (!isOusters())
            pStmt->executeQueryString(sqlVampire.toString());
        else
            pStmt->executeQueryString(sqlOusters.toString());

        SAFE_DELETE(pStmt);
    }
    END_DB(pStmt)

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Delete stash in memory.
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::deleteStash(void)

{
    __BEGIN_TRY

    SAFE_DELETE(m_pStash);
    m_StashNum = 0;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Delete flag set in memory.
//////////////////////////////////////////////////////////////////////////////
void PlayerCreature::deleteFlagSet(void)

{
    __BEGIN_TRY

    SAFE_DELETE(m_pFlagSet);

    __END_CATCH
}

//----------------------------------------------------------------------
// Add an aggressor to the aggressor list.
//----------------------------------------------------------------------
void PlayerCreature::addEnemy(const string& Name)

{
    __BEGIN_DEBUG

    list<string>::iterator itr = find(m_Enemies.begin(), m_Enemies.end(), Name);

    // Add if not already present.
    if (itr == m_Enemies.end()) {
        m_Enemies.push_back(Name);
    }

    __END_DEBUG
}

//----------------------------------------------------------------------
// Remove an aggressor from the aggressor list.
//----------------------------------------------------------------------
void PlayerCreature::deleteEnemy(const string& Name)

{
    __BEGIN_DEBUG

    list<string>::iterator itr = find(m_Enemies.begin(), m_Enemies.end(), Name);
    if (itr != m_Enemies.end()) {
        m_Enemies.erase(itr);
    }

    __END_DEBUG
}

//----------------------------------------------------------------------
// Check if an aggressor with a given name exists.
//----------------------------------------------------------------------
bool PlayerCreature::hasEnemy(const string& Name) const {
    __BEGIN_DEBUG

    list<string>::const_iterator itr = find(m_Enemies.begin(), m_Enemies.end(), Name);
    if (itr != m_Enemies.end()) {
        return true;
    } else {
        return false;
    }

    __END_DEBUG
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
string PlayerCreature::getGuildName() const

{
    Guild* pGuild = g_pGuildManager->getGuild(m_GuildID);

    if (pGuild != NULL)
        return pGuild->getName();

    return "";
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
GuildMemberRank_t PlayerCreature::getGuildMemberRank() const

{
    Guild* pGuild = g_pGuildManager->getGuild(m_GuildID);

    if (pGuild != NULL) {
        GuildMember* pGuildMember = pGuild->getMember(getName());
        if (pGuildMember != NULL) {
            return pGuildMember->getRank();
        }
    }

    return GuildMember::GUILDMEMBER_RANK_DENY;
}

Rank_t PlayerCreature::getRank() const {
    return m_pRank->getLevel();
}
RankExp_t PlayerCreature::getRankExp() const {
    return m_pRank->getTotalExp();
}
RankExp_t PlayerCreature::getRankGoalExp() const {
    return m_pRank->getGoalExp();
}

RankBonus* PlayerCreature::getRankBonus(RankBonus::RankBonusType type) const

{
    __BEGIN_TRY

    HashMapRankBonusConstItor itr = m_RankBonuses.find(type);

    if (itr == m_RankBonuses.end()) {
        return NULL;
    }

    return itr->second;

    __END_CATCH
}

void PlayerCreature::addRankBonus(RankBonus* rankBonus)

{
    __BEGIN_TRY

    HashMapRankBonusItor itr = m_RankBonuses.find(rankBonus->getType());

    if (itr == m_RankBonuses.end()) {
        m_RankBonuses[rankBonus->getType()] = rankBonus;
        m_RankBonusFlag.set(rankBonus->getType());
    } else {
        SAFE_DELETE(rankBonus);
    }

    __END_CATCH
}

void PlayerCreature::clearRankBonus()

{
    __BEGIN_TRY

    HashMapRankBonusItor itr = m_RankBonuses.begin();
    for (; itr != m_RankBonuses.end(); itr++) {
        SAFE_DELETE(itr->second);
    }

    m_RankBonuses.clear();
    m_RankBonusFlag.reset();

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQuery("DELETE FROM RankBonusData WHERE OwnerID = '%s'", getName().c_str());
    }
    END_DB(pStmt)

    __END_CATCH
}

RankBonus* PlayerCreature::getRankBonusByRank(Rank_t rank) const

{
    __BEGIN_TRY

    HashMapRankBonusConstItor itr = m_RankBonuses.begin();

    for (; itr != m_RankBonuses.end(); itr++) {
        RankBonus* pLearnedRankBonus = itr->second;

        if (rank == pLearnedRankBonus->getRank()) {
            return pLearnedRankBonus;
        }
    }

    return NULL;

    __END_CATCH
}

void PlayerCreature::clearRankBonus(Rank_t rank)

{
    __BEGIN_TRY

    RankBonus* pRankBonus = getRankBonusByRank(rank);
    if (pRankBonus == NULL)
        return;

    DWORD rankBonusType = pRankBonus->getType();

    HashMapRankBonusItor itr = m_RankBonuses.find(rankBonusType);
    if (itr != m_RankBonuses.end()) {
        m_RankBonusFlag.reset(rankBonusType);
        SAFE_DELETE(itr->second);
        m_RankBonuses.erase(itr);
    }

    Statement* pStmt = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt->executeQuery("DELETE FROM RankBonusData WHERE OwnerID = '%s' AND Type = %d", getName().c_str(),
                            (int)rankBonusType);
    }
    END_DB(pStmt)

    __END_CATCH
}

bool PlayerCreature::learnRankBonus(DWORD type)

{
    //__BEGIN_TRY
    try {
        HashMapRankBonusConstItor itr = m_RankBonuses.begin();

        RankBonusInfo* pRankBonusInfo = g_pRankBonusInfoManager->getRankBonusInfo(type);

        bool bValidRace = isSlayer() && pRankBonusInfo->getRace() == 0 ||
                          isVampire() && pRankBonusInfo->getRace() == 1 ||
                          isOusters() && pRankBonusInfo->getRace() == 2;

        if (getRank() < pRankBonusInfo->getRank())
            return false;

        if (!bValidRace)
            return false;

        for (; itr != m_RankBonuses.end(); itr++) {
            RankBonus* pLearnedRankBonus = itr->second;

            if (pRankBonusInfo->getRank() == pLearnedRankBonus->getRank()) {
                DWORD type = pLearnedRankBonus->getType();

                RankBonusInfo* pLearnedRankBonusInfo = g_pRankBonusInfoManager->getRankBonusInfo(type);

                if (pRankBonusInfo->getRace() == pLearnedRankBonusInfo->getRace()) {
                    return false;
                }
            }
        }

        RankBonus* rankBonus =
            new RankBonus(pRankBonusInfo->getType(), pRankBonusInfo->getPoint(), pRankBonusInfo->getRank());

        addRankBonus(rankBonus);

        Statement* pStmt = NULL;

        BEGIN_DB {
            pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
            pStmt->executeQuery("INSERT INTO RankBonusData ( OwnerID, Type )  VALUES ( '%s', %d )", getName().c_str(),
                                type);

            SAFE_DELETE(pStmt);
        }
        END_DB(pStmt)

        return true;
    } catch (Throwable& t) {
        filelog("PlayerCreature.txt", "PlayerCreature.cpp INSERT INTO RankBonusData error!");
        return false;
    }

    //__END_CATCH
}

void PlayerCreature::sendRankBonusInfo()

{
    __BEGIN_TRY

    HashMapRankBonusConstItor itr = m_RankBonuses.begin();

    GCRankBonusInfo gcRankBonusInfo;

    for (; itr != m_RankBonuses.end(); itr++) {
        gcRankBonusInfo.addListElement(itr->second->getType());
    }

    m_pPlayer->sendPacket(&gcRankBonusInfo);

    __END_CATCH
}

void PlayerCreature::loadRankBonus()

{
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pResult = pStmt->executeQuery("SELECT Type FROM RankBonusData WHERE OwnerID ='%s'", getName().c_str());

        while (pResult->next()) {
            DWORD rankBonusType = pResult->getInt(1);

            RankBonusInfo* pRankBonusInfo = g_pRankBonusInfoManager->getRankBonusInfo(rankBonusType);

            if (getRace() == pRankBonusInfo->getRace()) {
                RankBonus* pRankBonus = new RankBonus();

                pRankBonus->setType(rankBonusType);
                pRankBonus->setPoint(pRankBonusInfo->getPoint());
                pRankBonus->setRank(pRankBonusInfo->getRank());

                addRankBonus(pRankBonus);
            }
        }

        SAFE_DELETE(pStmt);
    }
    END_DB(pStmt)

    __END_CATCH
}

void PlayerCreature::increaseRankExp(RankExp_t Point) {
    if (Point <= 0)
        return;

    if (g_pPKZoneInfoManager->isPKZone(getZoneID()))
        return;

    if (m_pZone != NULL && m_pZone->isDynamicZone())
        return;

    if (isFlag(Effect::EFFECT_CLASS_BONUS_EXP))
        Point *= 2;

    if (m_pRank->increaseExp(Point)) {
        char pField[80];
        sprintf(pField, "`Rank`=%u, RankExp=%lu, RankGoalExp=%lu", getRank(), getRankExp(), getRankGoalExp());
        tinysave(pField);
        setRankExpSaveCount(0);

        GCModifyInformation gcModifyInformation;
        gcModifyInformation.addLongData(MODIFY_RANK, getRank());
        m_pPlayer->sendPacket(&gcModifyInformation);

        if (m_pZone != NULL) {
            GCOtherModifyInfo gcOtherModifyInfo;
            gcOtherModifyInfo.setObjectID(getObjectID());
            gcOtherModifyInfo.addShortData(MODIFY_RANK, getRank());

            m_pZone->broadcastPacket(m_X, m_Y, &gcOtherModifyInfo, this);
        }
    } else {
        WORD rankExpSaveCount = getRankExpSaveCount();
        if (rankExpSaveCount > RANK_EXP_SAVE_PERIOD) {
            char pField[80];
            sprintf(pField, "RankExp=%lu, RankGoalExp=%lu", getRankExp(), getRankGoalExp());
            tinysave(pField);

            rankExpSaveCount = 0;
        } else
            rankExpSaveCount++;
        setRankExpSaveCount(rankExpSaveCount);

        GCModifyInformation gcModifyInformation;
        gcModifyInformation.addLongData(MODIFY_RANK_EXP, getRankGoalExp());
        m_pPlayer->sendPacket(&gcModifyInformation);
    }
}

bool PlayerCreature::isBillingPlayAvaiable()

{
    __BEGIN_TRY

    if (m_pPlayer == NULL)
        return false;

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
    Assert(pGamePlayer != NULL);

    return pGamePlayer->isBillingPlayAvaiable();

    __END_CATCH
}


bool PlayerCreature::isPayPlayAvaiable()

{
    __BEGIN_TRY

    if (m_pPlayer == NULL)
        return false;

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
    return pGamePlayer->isPayPlaying();

    __END_CATCH
}


bool PlayerCreature::canPlayFree()

{
    return false;
}

void PlayerCreature::loadGoods()

{
    __BEGIN_TRY

    Statement* pStmt = NULL;
    Result* pResult = NULL;

    if (m_pGoodsInventory->getNum() != 0) {
        filelog("GoodsReload.log", "  ? : %s", getName().c_str());
        m_pGoodsInventory->clear();
    }

    BEGIN_DB {
        pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

        pResult =
            pStmt->executeQuery("SELECT ID, GoodsID, Num FROM GoodsListObject WHERE World = %d AND PlayerID = '%s' AND "
                                "Name = '%s' AND Status = 'NOT'",
                                g_pConfig->getPropertyInt("WorldID"), getPlayer()->getID().c_str(), getName().c_str());

        while (pResult->next()) {
            string ID = pResult->getString(1);
            DWORD goodsID = pResult->getInt(2);
            int num = pResult->getInt(3);

            for (int i = 0; i < max(1, min(50, num)); i++) {
                Item* pItem = createItemByGoodsID(goodsID);
                if (pItem != NULL) {
                    m_pGoodsInventory->addItem(ID, pItem);
                }
            }
        }

        SAFE_DELETE(pStmt);
    }
    END_DB(pStmt)

    __END_CATCH
}


/*void	PlayerCreature::loadQuest()

{
    __BEGIN_TRY

#ifdef __ACTIVE_QUEST__

    SimpleQuestLoader::getInstance()->load( this );

#endif

    __END_CATCH
}

bool    PlayerCreature::addQuest(Quest* pQuest)

{
    __BEGIN_TRY

#ifdef __ACTIVE_QUEST__
    if (m_pQuestManager==NULL)
    {
        m_pQuestManager = new QuestManager;
    }

    if (m_pQuestManager->addQuest( pQuest ))
    {
        return true;
    }

#endif
    __END_CATCH

    SAFE_DELETE(pQuest);

    return false;
}

bool    PlayerCreature::checkEvent(QuestEvent* pQuestEvent)

{
    __BEGIN_TRY

#ifdef __ACTIVE_QUEST__

    if (m_pQuestManager!=NULL)
    {
        Quest* pCompleteQuest = m_pQuestManager->checkEvent( pQuestEvent );

        if (pCompleteQuest!=NULL)
        {
            //cout << "[Complete] " << pCompleteQuest->toString().c_str() << endl;
            return true;
        }
    }

#endif

    return false;

    __END_CATCH
}

Quest*  PlayerCreature::removeCompleteQuest()

{
    __BEGIN_TRY

#ifdef __ACTIVE_QUEST__

    if (m_pQuestManager!=NULL)
    {
        Quest* pQuest = m_pQuestManager->removeCompleteQuest();

        return pQuest;
    }

#endif

    __END_CATCH

    return NULL;
}*/
/*
bool PlayerCreature::deleteItemNameInfoList( ObjectID_t objectID )

{
    __BEGIN_TRY

    list<ItemNameInfo*>::iterator itr = m_ItemNameInfoList.begin();

    for( ; itr != m_ItemNameInfoList.end() ; itr++ )
    {
        ItemNameInfo* pInfo = *itr;
        if( pInfo->getObjectID() == objectID )
        {
            SAFE_DELETE( pInfo );
            m_ItemNameInfoList.erase( itr );

            return true;
        }
    }

    return false;

    __END_CATCH
}

string PlayerCreature::getItemName( ObjectID_t objectID )

{
    __BEGIN_TRY

    list<ItemNameInfo*>::iterator itr = m_ItemNameInfoList.begin();

    for( ; itr != m_ItemNameInfoList.end() ; itr++ )
    {
        ItemNameInfo* pInfo = *itr;
        if( pInfo->getObjectID() == objectID )
        {
            return pInfo->getName();
        }
    }

    return NULL;

    __END_CATCH
}
*/

void PlayerCreature::addDefaultOptionSet(DefaultOptionSetType_t type)

{
    forward_list<DefaultOptionSetType_t>::iterator itr = m_DefaultOptionSet.begin();
    for (; itr != m_DefaultOptionSet.end(); itr++) {
        if ((*itr) == type)
            return;
    }

    m_DefaultOptionSet.push_front(type);
}

void PlayerCreature::removeDefaultOptionSet(DefaultOptionSetType_t type)

{
    forward_list<DefaultOptionSetType_t>::iterator before = m_DefaultOptionSet.end();
    forward_list<DefaultOptionSetType_t>::iterator current = m_DefaultOptionSet.begin();

    for (; current != m_DefaultOptionSet.end(); before = current++) {
        if ((*current) == type) {
            if (before == m_DefaultOptionSet.end()) {
                // delete first node
                m_DefaultOptionSet.pop_front();
            } else {
                m_DefaultOptionSet.erase_after(before);
            }

            return;
        }
    }
}

PetInfo* PlayerCreature::getPetInfo() const {
    return m_pPetInfo;
}

void PlayerCreature::setPetInfo(PetInfo* pPetInfo) {
    m_pPetInfo = pPetInfo;
    SAFE_DELETE(m_pPet);
    m_pPet = Pet::makePet(this, m_pPetInfo);
}

void PlayerCreature::heartbeat(const Timeval& currentTime) {
    if (m_pPet != NULL)
        m_pPet->heartbeat(currentTime);
    m_pGQuestManager->heartbeat();
}


GCMonsterKillQuestInfo::QuestInfo* PlayerCreature::getPetQuestInfo() const {
    GCMonsterKillQuestInfo::QuestInfo* pQI = new GCMonsterKillQuestInfo::QuestInfo;

    pQI->questID = PET_QUEST_ID;
    pQI->sType = m_TargetMonster;
    pQI->goal = m_TargetNum;
    pQI->timeLimit = m_TimeLimit;

    return pQI;
}

void PlayerCreature::addPetStashItem(int idx, Item* pPetItem) {
    Assert(pPetItem == NULL || pPetItem->getItemClass() == Item::ITEM_CLASS_PET_ITEM);
    Assert(idx >= 0 && idx <= MAX_PET_STASH);
    m_PetStash[idx] = pPetItem;
}

Item* PlayerCreature::getPetStashItem(int idx) {
    Assert(idx >= 0 && idx <= MAX_PET_STASH);
    return m_PetStash[idx];
}

bool PlayerCreature::canSee(Object* pObject) const {
    if (pObject->getObjectClass() == OBJECT_CLASS_CREATURE) {
        return ::canSee(this, dynamic_cast<Creature*>(pObject));
    } else {
        return true;
    }
}

Level_t PlayerCreature::getAdvancementClassLevel() const {
    return m_pAdvancementClass->getLevel();
}
Exp_t PlayerCreature::getAdvancementClassGoalExp() const {
    return m_pAdvancementClass->getGoalExp();
}
bool PlayerCreature::increaseAdvancementClassExp(Exp_t exp, bool bApplyExpBonus) {
    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(m_pPlayer);
    if (pGamePlayer != NULL) {
        if (bApplyExpBonus && (pGamePlayer->isPremiumPlay() || pGamePlayer->isFamilyFreePass())) {
            exp = getPercentValue(exp, g_pVariableManager->getPremiumExpBonusPercent());
        }

        if (bApplyExpBonus && g_pVariableManager->getExpRatio() > 100 && g_pVariableManager->getEventActivate() == 1) {
            exp = getPercentValue(exp, g_pVariableManager->getExpRatio());
        }

        if (bApplyExpBonus && isAffectExp2X()) {
            // Double EXP effect
            exp = exp * 2;
        }
        // chengh modify 2006-07-21: bonus EXP effect.
        if (isFlag(Effect::EFFECT_CLASS_BONUS_EXP)) {
            exp *= 2;
        }
    }

    cout << getName() << " gains " << static_cast<int>(exp) << " advancement EXP." << endl;
    Level_t prevLevel = getAdvancementClassLevel();
    bool ret = m_pAdvancementClass->increaseExp(exp, true, true);
    if (getAdvancementClassLevel() > 0)
        m_bAdvanced = true;
    Level_t nextLevel = getAdvancementClassLevel();
    cout << getName() << " advanced from " << static_cast<int>(prevLevel) << " to " << static_cast<int>(nextLevel)
         << "." << endl;

    if (prevLevel != nextLevel) {
        Bonus_t bonus = getBonus();
        Level_t _4pointstart = min((int)prevLevel, 50);
        Level_t _4pointend = min((int)nextLevel, 50);
        Level_t _5pointstart = max((int)prevLevel, 50);
        Level_t _5pointend = max((int)nextLevel, 50);

        Bonus_t bonusdiff = ((_4pointend - _4pointstart) * 4) + ((_5pointend - _5pointstart) * 5);
        cout << getName() << " receives " << static_cast<int>(bonusdiff) << " attribute points." << endl;
        bonus += bonusdiff;
        setBonus(bonus);

        StringStream sav;
        sav << "AdvancementClass = " << (int)nextLevel << ",AdvancementGoalExp = " << (int)getAdvancementClassGoalExp()
            << ",Bonus = " << (int)getBonus();

        tinysave(sav.toString());
        initAllStatAndSend();
    } else {
        m_AdvancementClassExpSaveCount++;
        if (m_AdvancementClassExpSaveCount > 100) {
            StringStream sav;
            sav << "AdvancementClass = " << (int)getAdvancementClassLevel()
                << ",AdvancementGoalExp = " << (int)getAdvancementClassGoalExp();
            tinysave(sav.toString());
            m_AdvancementClassExpSaveCount = 0;
        }
    }

    GCModifyInformation gcMI;
    gcMI.addLongData(MODIFY_ADVANCEMENT_CLASS_GOAL_EXP, getAdvancementClassGoalExp());
    if (ret) {
        gcMI.addShortData(MODIFY_ADVANCEMENT_CLASS_LEVEL, getAdvancementClassLevel());
        gcMI.addShortData(MODIFY_BONUS_POINT, getBonus());
        m_pGQuestManager->advancementClassLevelUp();
    }

    getPlayer()->sendPacket(&gcMI);

    return ret;
}

bool PlayerCreature::putAdvancedBonusToSTR() {
    if (m_AdvancedAttrBonus <= 0)
        return false;
    m_AdvancedAttrBonus--;
    m_AdvancedSTR++;
    return true;
}

bool PlayerCreature::putAdvancedBonusToDEX() {
    if (m_AdvancedAttrBonus <= 0)
        return false;
    m_AdvancedAttrBonus--;
    m_AdvancedDEX++;
    return true;
}

bool PlayerCreature::putAdvancedBonusToINT() {
    if (m_AdvancedAttrBonus <= 0)
        return false;
    m_AdvancedAttrBonus--;
    m_AdvancedINT++;
    return true;
}
bool PlayerCreature::canChangeMasterEffectColor() {
    // MasterEffectColor 5 is reserved for guild war champions;
    // it cannot be changed via shop conversion items.
    // 2005.05.17 by bezz
    return m_MasterEffectColor != 5;
}
