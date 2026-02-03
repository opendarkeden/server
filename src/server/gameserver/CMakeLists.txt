# ============================================================================
# GameServer 模块
# ============================================================================

# 通用编译定义和包含目录
set(GAMESERVER_COMPILE_DEFS __GAME_SERVER__ __COMBAT__)
set(GAMESERVER_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_CURRENT_SOURCE_DIR}/skill
    ${CMAKE_CURRENT_SOURCE_DIR}/item
    ${CMAKE_CURRENT_SOURCE_DIR}/billing
    ${CMAKE_CURRENT_SOURCE_DIR}/war
    ${CMAKE_CURRENT_SOURCE_DIR}/couple
    ${CMAKE_CURRENT_SOURCE_DIR}/mission
    ${CMAKE_CURRENT_SOURCE_DIR}/ctf
    ${CMAKE_CURRENT_SOURCE_DIR}/quest
    ${CMAKE_CURRENT_SOURCE_DIR}/quest/luaScript
    ${CMAKE_CURRENT_SOURCE_DIR}/mofus
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)

# ============================================================================
# 子目录库
# ============================================================================
add_subdirectory(skill)
add_subdirectory(item)
add_subdirectory(billing)
add_subdirectory(war)
add_subdirectory(couple)
add_subdirectory(mission)
add_subdirectory(ctf)
add_subdirectory(quest)
add_subdirectory(mofus)

# ============================================================================
# Monster 相关源文件
# ============================================================================
set(MONSTER_SOURCES
    Monster.cpp
    MonsterInfo.cpp
    MonsterManager.cpp
    MonsterAI.cpp
    Directive.cpp
    MonsterNameManager.cpp
    MonsterCounter.cpp
)

# ============================================================================
# Item 相关源文件（gameserver 目录下的）
# ============================================================================
set(ITEM_SOURCES
    Item.cpp
    ItemInfo.cpp
    ItemUtil.cpp
    ItemFactoryManager.cpp
    ItemInfoManager.cpp
    ItemLoaderManager.cpp
    SlayerCorpse.cpp
    VampireCorpse.cpp
    OustersCorpse.cpp
    MonsterCorpse.cpp
)

# ============================================================================
# Guild 相关源文件
# ============================================================================
set(GUILD_SOURCES
    Party.cpp
    Guild.cpp
    GuildManager.cpp
    GuildUnion.cpp
)

# ============================================================================
# Event 相关源文件
# ============================================================================
set(EVENT_SOURCES
    Event.cpp
    EventManager.cpp
    EventShutdown.cpp
    EventRegeneration.cpp
    EventSave.cpp
    EventMorph.cpp
    EventResurrect.cpp
    EventReloadInfo.cpp
    EventTransport.cpp
    EventKick.cpp
    EventSystemMessage.cpp
    EventRefreshHolyLandPlayer.cpp
    EventHeadCount.cpp
    EventCBilling.cpp
    EventAuth.cpp
)

# ============================================================================
# Effect 相关源文件
# ============================================================================
set(EFFECT_SOURCES
    Effect.cpp
    EffectManager.cpp
    EffectSchedule.cpp
    EffectLoaderManager.cpp
    EffectShutDown.cpp
    EffectHPRecovery.cpp
    EffectMPRecovery.cpp
    EffectAlignmentRecovery.cpp
    EffectEnemyErase.cpp
    EffectDecayCorpse.cpp
    EffectDecayItem.cpp
    EffectAftermath.cpp
    EffectComa.cpp
    EffectPrecedence.cpp
    EffectTransportItem.cpp
    EffectAddItem.cpp
    EffectRelicTable.cpp
    EffectHasSlayerRelic.cpp
    EffectHasVampireRelic.cpp
    EffectIncreaseAttr.cpp
    EffectDeleteItem.cpp
    EffectSlayerRelic.cpp
    EffectVampireRelic.cpp
    EffectRelicPosition.cpp
    EffectRelicLock.cpp
    EffectMasterLairPass.cpp
    EffectContinualGroundAttack.cpp
    EffectGhost.cpp
    EffectTransportCreature.cpp
    EffectGrandMasterSlayer.cpp
    EffectGrandMasterVampire.cpp
    EffectKillAftermath.cpp
    EffectHasBloodBible.cpp
    EffectShrineHoly.cpp
    EffectShrineGuard.cpp
    EffectShrineShield.cpp
    EffectTransportItemToCorpse.cpp
    EffectAddItemToCorpse.cpp
    EffectHasRelic.cpp
    EffectHasCastleSymbol.cpp
    EffectLoveChain.cpp
    EffectPKZoneRegen.cpp
    EffectPKZoneResurrection.cpp
    EffectGrandMasterOusters.cpp
    EffectTranslation.cpp
    EffectLoud.cpp
    EffectMute.cpp
    SimpleCreatureEffect.cpp
    EffectRefiniumTicket.cpp
    EffectFlagInsert.cpp
    EffectHasSweeper.cpp
    EffectKeepSweeper.cpp
    EffectRegenZone.cpp
    EffectTryingPosition.cpp
    EffectTrying.cpp
    EffectTryRegenZone.cpp
    EffectOnBridge.cpp
    EffectHasPet.cpp
    EffectPacketSend.cpp
    EffectDarknessForbidden.cpp
    EffectCastingTrap.cpp
    EffectWithWarning.cpp
    EffectKickOut.cpp
    EffectGDRLairClose.cpp
    EffectEventQuestReset.cpp
    EffectShareHP.cpp
    EffectCanEnterGDRLair.cpp
    EffectAutoTurret.cpp
    EffectTurretLaser.cpp
    EffectKillTimer.cpp
    EffectDragonEye.cpp
    EffectRegenerate.cpp
    EffectRecallMotorcycle.cpp
    EffectRideMotorcycle.cpp
    EffectDonation200501.cpp
    SimpleTileEffect.cpp
    EffectDeleteTile.cpp
)

# ============================================================================
# GQuest 相关源文件
# ============================================================================
set(GQUEST_SOURCES
    GQuestInfo.cpp
    GQuestManager.cpp
    GQuestElement.cpp
    GQuestStatus.cpp
    GQuestInventory.cpp
    GQuestLevelElement.cpp
    GQuestTimeElement.cpp
    GQuestGiveVampireExpElement.cpp
    GQuestBloodDrainElement.cpp
    GQuestSayNPCElement.cpp
    GQuestExecuteElement.cpp
    GQuestGiveQuestItemElement.cpp
    GQuestLoseQuestItemElement.cpp
    GQuestGiveItemElement.cpp
    GQuestTamePetElement.cpp
    GQuestRaceElement.cpp
    GQuestKilledElement.cpp
    GQuestGiveDomainExpElement.cpp
    GQuestGiveMoneyElement.cpp
    GQuestSkillLevelElement.cpp
    GQuestRideMotorcycleElement.cpp
    GQuestGiveOustersExpElement.cpp
    GQuestTouchWayPointElement.cpp
    GQuestHasQuestItemElement.cpp
    GQuestPartyDissectElement.cpp
    GQuestKillMonsterElement.cpp
    GQuestGiveEventQuestItemElement.cpp
    GQuestEventPartyElement.cpp
    GQuestEventPartyCrashElement.cpp
    GQuestCompleteQuestElement.cpp
    GQuestFastMoveElement.cpp
    GQuestIllegalWarpElement.cpp
    GQuestCheckPoint.cpp
    GQuestTravelElement.cpp
    GQuestORElement.cpp
    GQuestNOTElement.cpp
    GQuestRandomElement.cpp
    GQuestAdvancementClassLevelElement.cpp
    GQuestClearDynamicZoneElement.cpp
    GQuestAddEffectElement.cpp
    GQuestRemoveEffectElement.cpp
    GQuestSetEnterDynamicZoneElement.cpp
    GQuestEnterDynamicZoneElement.cpp
    GQuestStartOtherQuestElement.cpp
    GQuestGiveAdvancementClassExpElement.cpp
    GQuestAdvanceClassElement.cpp
    GQuestWarpElement.cpp
)


# ============================================================================
# 主要源文件
# ============================================================================
set(GAMESERVER_MAIN_SOURCES
    main.cpp
    Zone.cpp
    Slayer.cpp
    Vampire.cpp
    Ousters.cpp
    OustersEXPInfo.cpp
    ClientManager.cpp
    ConnectionInfoManager.cpp
    Creature.cpp
    CreatureManager.cpp
    DarkLightInfo.cpp
    Corpse.cpp
    GamePlayer.cpp
    GameServer.cpp
    IncomingPlayerManager.cpp
    SharedServerClient.cpp
    InfoClassManager.cpp
    Inventory.cpp
    LoginServerManager.cpp
    SharedServerManager.cpp
    NPC.cpp
    NPCManager.cpp
    ResurrectLocationManager.cpp
    PCFinder.cpp
    TelephoneCenter.cpp
    ParkingCenter.cpp
    PCManager.cpp
    Portal.cpp
    Script.cpp
    ScriptManager.cpp
    ThreadManager.cpp
    ThreadPool.cpp
    Tile.cpp
    Sector.cpp
    TimeManager.cpp
    GoodsInventory.cpp
    GoodsInfoManager.cpp
    VisionInfo.cpp
    WeatherInfo.cpp
    WeatherManager.cpp
    ZoneInfo.cpp
    ZoneGroup.cpp
    ZoneGroupManager.cpp
    ZoneInfoManager.cpp
    ZonePlayerManager.cpp
    ZoneGroupThread.cpp
    ObjectManager.cpp
    AbilityBalance.cpp
    PlayerCreature.cpp
    ZoneUtil.cpp
    Treasure.cpp
    PacketUtil.cpp
    ConnectionInfo.cpp
    InventorySlot.cpp
    ObjectRegistry.cpp
    WayPoint.cpp
    OptionInfo.cpp
    VolumeInfo.cpp
    VampEXPInfo.cpp
    ItemRack.cpp
    ShopRack.cpp
    Stash.cpp
    Garbage.cpp
    ShopTemplate.cpp
    PriceManager.cpp
    CreatureUtil.cpp
    ItemMap.cpp
    TradeManager.cpp
    FlagSet.cpp
    AlignmentManager.cpp
    SkillInfo.cpp
    SkillDomainInfoManager.cpp
    SkillParentInfo.cpp
    InitAllStat.cpp
    PrecedenceTable.cpp
    VariableManager.cpp
    CombatInfoManager.cpp
    UniqueItemManager.cpp
    MasterLairInfoManager.cpp
    MasterLairManager.cpp
    MonsterSummonInfo.cpp
    LuckInfo.cpp
    LogNameManager.cpp
    RankBonusInfo.cpp
    RankBonus.cpp
    CastleInfoManager.cpp
    HolyLandRaceBonus.cpp
    ShrineInfoManager.cpp
    GlobalItemPositionLoader.cpp
    RelicUtil.cpp
    HolyLandManager.cpp
    BloodBibleBonus.cpp
    BloodBibleBonusManager.cpp
    CastleShrineInfoManager.cpp
    SkillPropertyManager.cpp
    StringPool.cpp
    PKZoneInfoManager.cpp
    GameServerGroupInfoManager.cpp
    DefaultOptionSetInfo.cpp
    CastleSkillInfo.cpp
    TimeLimitItemManager.cpp
    ItemMineInfo.cpp
    EventItemUtil.cpp
    SweeperSet.cpp
    SweeperBonus.cpp
    SweeperBonusManager.cpp
    LevelWar.cpp
    LevelWarManager.cpp
    LevelWarZoneInfoManager.cpp
    RegenZoneManager.cpp
    PetTypeInfo.cpp
    PetUtil.cpp
    PetAttrInfo.cpp
    PetExpInfo.cpp
    RankExpTable.cpp
    SlayerAttrExpTable.cpp
    Pet.cpp
    SystemAvailabilitiesManager.cpp
    LocalIP.cpp
    ItemGradeManager.cpp
    EventZoneInfo.cpp
    SMSServiceThread.cpp
    SMSAddressBook.cpp
    FiniteStateMachine.cpp
    GDRLairManager.cpp
    GDRLairAbstractStates.cpp
    NicknameBook.cpp
    LevelNickInfoManager.cpp
    SiegeManager.cpp
    BroadcastFilter.cpp
    Store.cpp
    AdvancementClassExpTable.cpp
    DynamicZoneManager.cpp
    DynamicZoneInfo.cpp
    DynamicZone.cpp
    DynamicZoneGroup.cpp
    DynamicZoneGateOfAlter.cpp
    DynamicZoneAlterOfBlood.cpp
    DynamicZoneFactoryManager.cpp
    DynamicZoneSlayerMirrorOfAbyss.cpp
    DynamicZoneVampireMirrorOfAbyss.cpp
    DynamicZoneOustersMirrorOfAbyss.cpp
    NewYear2005ItemUtil.cpp
)

# ============================================================================
# Exchange System 相关源文件
# ============================================================================
set(EXCHANGE_SOURCES
    exchange/ExchangeService.cpp
    exchange/ExchangeDB.cpp
)

# ============================================================================
# GameServer 可执行文件
# ============================================================================
add_executable(gameserver
    ${GAMESERVER_MAIN_SOURCES}
    ${MONSTER_SOURCES}
    ${ITEM_SOURCES}
    ${GUILD_SOURCES}
    ${EFFECT_SOURCES}
    ${EVENT_SOURCES}
    ${GQUEST_SOURCES}
    ${EXCHANGE_SOURCES}
)

# 编译定义
target_compile_definitions(gameserver PRIVATE ${GAMESERVER_COMPILE_DEFS})

# 包含目录
target_include_directories(gameserver PRIVATE ${GAMESERVER_INCLUDE_DIRS})

# 链接库（注意顺序，被依赖的库放后面）
if(APPLE)
    set(EXTRA_LIBS util z)
elseif(UNIX)
    set(EXTRA_LIBS nsl util dl z)
endif()

target_link_libraries(gameserver PRIVATE
    Items
    Quest
    Mofus
    GameServerDatabase
    ServerCore
    GameServerPackets
    Skill
    Core
    GameServerBilling
    LuaScript
    War
    Couple
    Mission
    CTF
    GameServerCBilling
    ${MYSQL_LIBRARY}
    ${LUA51_LIBRARIES}
    ${XERCES_LIBRARY}
    Threads::Threads
    ${EXTRA_LIBS}
)

# 导出符号（用于动态加载）
set_target_properties(gameserver PROPERTIES ENABLE_EXPORTS ON)

# ============================================================================
# Exchange System Test Program
# ============================================================================
# Temporarily disabled - test_exchange.cpp is broken
# add_executable(test_exchange
#     exchange/test_exchange.cpp
#     exchange/ExchangeDB.cpp
#     ${EXTRA_SOURCES}
# )
#
# target_compile_definitions(test_exchange PRIVATE ${GAMESERVER_COMPILE_DEFS})
# target_include_directories(test_exchange PRIVATE ${GAMESERVER_INCLUDE_DIRS})
#
# target_link_libraries(test_exchange PRIVATE
#     GameServerDatabase
#     ServerCore
#     Core
#     ${MYSQL_LIBRARY}
#     ${EXTRA_LIBS}
# )
