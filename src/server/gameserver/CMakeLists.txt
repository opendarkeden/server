ADD_DEFINITIONS(-D__LINUX__ -D__GAME_SERVER__)
INCLUDE_DIRECTORIES(. ./war ./quest ./skill ./mission ./ctf ./mofus ./billing ./couple ./item ./test)
SET(MONSTER_SRC Monster.cpp MonsterInfo.cpp MonsterManager.cpp 
	MonsterAI.cpp Directive.cpp MonsterNameManager.cpp MonsterCounter.cpp )

SET(ITEM_SRC Item.cpp ItemInfo.cpp ItemUtil.cpp 
	ItemFactoryManager.cpp ItemInfoManager.cpp ItemLoaderManager.cpp 
	SlayerCorpse.cpp VampireCorpse.cpp OustersCorpse.cpp MonsterCorpse.cpp)

SET(GUILD_SRC Party.cpp Guild.cpp GuildManager.cpp GuildUnion.cpp)

SET(EVENT_SRC Event.cpp EventManager.cpp EventShutdown.cpp 
	EventRegeneration.cpp EventSave.cpp EventMorph.cpp EventResurrect.cpp EventReloadInfo.cpp 
	EventTransport.cpp EventKick.cpp EventSystemMessage.cpp EventRefreshHolyLandPlayer.cpp EventHeadCount.cpp 
	EventCBilling.cpp EventAuth.cpp)

SET(EFFECT_SRC Effect.cpp EffectManager.cpp EffectSchedule.cpp EffectLoaderManager.cpp 
	EffectShutDown.cpp EffectHPRecovery.cpp EffectMPRecovery.cpp 
	EffectAlignmentRecovery.cpp EffectEnemyErase.cpp 
	EffectDecayCorpse.cpp EffectDecayItem.cpp EffectAftermath.cpp EffectComa.cpp 
	EffectPrecedence.cpp EffectTransportItem.cpp EffectAddItem.cpp EffectRelicTable.cpp 
	EffectHasSlayerRelic.cpp EffectHasVampireRelic.cpp EffectIncreaseAttr.cpp 
	EffectDeleteItem.cpp EffectSlayerRelic.cpp EffectVampireRelic.cpp EffectRelicPosition.cpp 
	EffectRelicLock.cpp EffectMasterLairPass.cpp EffectContinualGroundAttack.cpp 
	EffectGhost.cpp EffectTransportCreature.cpp EffectGrandMasterSlayer.cpp 
	EffectGrandMasterVampire.cpp EffectKillAftermath.cpp EffectHasBloodBible.cpp 
	EffectShrineHoly.cpp EffectShrineGuard.cpp EffectShrineShield.cpp 
	EffectTransportItemToCorpse.cpp EffectAddItemToCorpse.cpp 
	EffectHasRelic.cpp EffectHasCastleSymbol.cpp EffectLoveChain.cpp 
	EffectPKZoneRegen.cpp EffectPKZoneResurrection.cpp EffectGrandMasterOusters.cpp 
	EffectTranslation.cpp EffectLoud.cpp EffectMute.cpp 
	SimpleCreatureEffect.cpp EffectRefiniumTicket.cpp EffectFlagInsert.cpp EffectHasSweeper.cpp EffectKeepSweeper.cpp 
	EffectRegenZone.cpp EffectTryingPosition.cpp EffectTrying.cpp EffectTryRegenZone.cpp EffectOnBridge.cpp EffectHasPet.cpp 
	EffectPacketSend.cpp EffectDarknessForbidden.cpp EffectCastingTrap.cpp EffectWithWarning.cpp EffectKickOut.cpp EffectGDRLairClose.cpp 
	EffectEventQuestReset.cpp EffectShareHP.cpp EffectCanEnterGDRLair.cpp 
	EffectAutoTurret.cpp EffectTurretLaser.cpp EffectKillTimer.cpp EffectDragonEye.cpp EffectRegenerate.cpp EffectRecallMotorcycle.cpp 
	EffectRideMotorcycle.cpp EffectDonation200501.cpp SimpleTileEffect.cpp EffectDeleteTile.cpp 
	EffectBehemothForceScroll.cpp EffectSafeForceScroll.cpp EffectCarnelianForceScroll.cpp)

SET(GQUEST_SRC
	GQuestInfo.cpp GQuestManager.cpp GQuestElement.cpp GQuestStatus.cpp GQuestInventory.cpp 
	GQuestLevelElement.cpp GQuestTimeElement.cpp GQuestGiveVampireExpElement.cpp GQuestBloodDrainElement.cpp GQuestSayNPCElement.cpp GQuestExecuteElement.cpp 
	GQuestGiveQuestItemElement.cpp GQuestLoseQuestItemElement.cpp GQuestGiveItemElement.cpp GQuestTamePetElement.cpp GQuestRaceElement.cpp GQuestKilledElement.cpp 
	GQuestGiveDomainExpElement.cpp GQuestGiveMoneyElement.cpp GQuestSkillLevelElement.cpp GQuestRideMotorcycleElement.cpp GQuestGiveOustersExpElement.cpp 
	GQuestTouchWayPointElement.cpp GQuestHasQuestItemElement.cpp GQuestPartyDissectElement.cpp GQuestKillMonsterElement.cpp GQuestGiveEventQuestItemElement.cpp 
	GQuestEventPartyElement.cpp GQuestEventPartyCrashElement.cpp GQuestCompleteQuestElement.cpp GQuestFastMoveElement.cpp GQuestIllegalWarpElement.cpp 
	GQuestCheckPoint.cpp GQuestTravelElement.cpp GQuestORElement.cpp GQuestNOTElement.cpp GQuestRandomElement.cpp GQuestAdvancementClassLevelElement.cpp 
	GQuestClearDynamicZoneElement.cpp GQuestAddEffectElement.cpp GQuestRemoveEffectElement.cpp GQuestSetEnterDynamicZoneElement.cpp 
	GQuestEnterDynamicZoneElement.cpp GQuestStartOtherQuestElement.cpp GQuestGiveAdvancementClassExpElement.cpp GQuestAdvanceClassElement.cpp 
	GQuestWarpElement.cpp)

SET(SRCS main.cpp Zone.cpp Slayer.cpp Vampire.cpp Ousters.cpp OustersEXPInfo.cpp 
	ClientManager.cpp ConnectionInfoManager.cpp 
	Creature.cpp CreatureManager.cpp DarkLightInfo.cpp Corpse.cpp 
	GamePlayer.cpp GameServer.cpp IncomingPlayerManager.cpp SharedServerClient.cpp 
	InfoClassManager.cpp Inventory.cpp LoginServerManager.cpp SharedServerManager.cpp
	NPC.cpp NPCManager.cpp ResurrectLocationManager.cpp PCFinder.cpp 
	TelephoneCenter.cpp ParkingCenter.cpp PCManager.cpp Portal.cpp 
	Script.cpp ScriptManager.cpp ThreadManager.cpp ThreadPool.cpp 
	Tile.cpp Sector.cpp TimeManager.cpp GoodsInventory.cpp GoodsInfoManager.cpp 
	VisionInfo.cpp WeatherInfo.cpp WeatherManager.cpp 
	ZoneInfo.cpp ZoneGroup.cpp ZoneGroupManager.cpp ZoneInfoManager.cpp 
	ZonePlayerManager.cpp ZoneGroupThread.cpp 
	ObjectManager.cpp AbilityBalance.cpp 
	PlayerCreature.cpp ZoneUtil.cpp Treasure.cpp  
	PacketUtil.cpp ConnectionInfo.cpp InventorySlot.cpp  
	ObjectRegistry.cpp WayPoint.cpp OptionInfo.cpp 
	VolumeInfo.cpp VampEXPInfo.cpp ItemRack.cpp ShopRack.cpp Stash.cpp Garbage.cpp 
	ShopTemplate.cpp PriceManager.cpp CreatureUtil.cpp ItemMap.cpp 
	TradeManager.cpp FlagSet.cpp AlignmentManager.cpp 
	SkillInfo.cpp SkillDomainInfoManager.cpp SkillParentInfo.cpp InitAllStat.cpp 
	PrecedenceTable.cpp VariableManager.cpp CombatInfoManager.cpp 
	UniqueItemManager.cpp 
	MasterLairInfoManager.cpp MasterLairManager.cpp 
	MonsterSummonInfo.cpp LuckInfo.cpp 
	LogNameManager.cpp RankBonusInfo.cpp RankBonus.cpp 
	CastleInfoManager.cpp HolyLandRaceBonus.cpp 
	ShrineInfoManager.cpp GlobalItemPositionLoader.cpp 
	RelicUtil.cpp HolyLandManager.cpp 
	BloodBibleBonus.cpp BloodBibleBonusManager.cpp 
	CastleShrineInfoManager.cpp SkillPropertyManager.cpp 
	StringPool.cpp PKZoneInfoManager.cpp 
	GameServerGroupInfoManager.cpp DefaultOptionSetInfo.cpp 
	CastleSkillInfo.cpp TimeLimitItemManager.cpp ItemMineInfo.cpp 
	EventItemUtil.cpp SweeperSet.cpp SweeperBonus.cpp SweeperBonusManager.cpp 
	LevelWar.cpp LevelWarManager.cpp LevelWarZoneInfoManager.cpp 
	RegenZoneManager.cpp PetTypeInfo.cpp PetUtil.cpp PetAttrInfo.cpp PetExpInfo.cpp 
	RankExpTable.cpp SlayerAttrExpTable.cpp 
	Pet.cpp SystemAvailabilitiesManager.cpp LocalIP.cpp 
	ItemGradeManager.cpp EventZoneInfo.cpp SMSServiceThread.cpp 
	SMSAddressBook.cpp FiniteStateMachine.cpp GDRLairManager.cpp GDRLairAbstractStates.cpp 
	NicknameBook.cpp LevelNickInfoManager.cpp SiegeManager.cpp 
	BroadcastFilter.cpp Store.cpp AdvancementClassExpTable.cpp DynamicZoneManager.cpp 
	DynamicZoneInfo.cpp DynamicZone.cpp DynamicZoneGroup.cpp DynamicZoneGateOfAlter.cpp 
	DynamicZoneAlterOfBlood.cpp DynamicZoneFactoryManager.cpp DynamicZoneSlayerMirrorOfAbyss.cpp 
	DynamicZoneVampireMirrorOfAbyss.cpp DynamicZoneOustersMirrorOfAbyss.cpp 
	NewYear2005ItemUtil.cpp BalloonHeadbandUtil.cpp 
	${MONSTER_OBJS} ${TEM_OBJS} ${GUILD_OBJS} ${EFFECT_OBJS} ${EVENT_OBJS} ${COMBAT_OBJS} ${GQUEST_OBJS})
	
ADD_SUBDIRECTORY(skill)
ADD_SUBDIRECTORY(item)
ADD_SUBDIRECTORY(mission)
ADD_SUBDIRECTORY(couple)
ADD_SUBDIRECTORY(war)
ADD_SUBDIRECTORY(quest)
ADD_SUBDIRECTORY(billing)
ADD_SUBDIRECTORY(ctf)
ADD_SUBDIRECTORY(mofus)

SET(GAMESERVERCBILLING_SRC
	../chinabilling/CBillingPacketErrorBody.cpp
	../chinabilling/CBillingPacketHeader.cpp
	../chinabilling/CBillingPacketRequestIntervalValidationBody.cpp
	../chinabilling/CBillingPacketRequestLoginBody.cpp
	../chinabilling/CBillingPacketRequestLogoutBody.cpp
	../chinabilling/CBillingPacketRequestMinusMinuteBody.cpp
	../chinabilling/CBillingPacketRequestMinusPointBody.cpp
	../chinabilling/CBillingPacketResponseIntervalValidationBody.cpp
	../chinabilling/CBillingPacketResponseLoginBody.cpp
	../chinabilling/CBillingPacketResponseLogoutBody.cpp
	../chinabilling/CBillingPacketResponseMinusMinuteBody.cpp
	../chinabilling/CBillingPacketResponseMinusPointBody.cpp
	../chinabilling/CBillingPlayer.cpp
	../chinabilling/CBillingPlayerInfo.cpp
	../chinabilling/CBillingPlayerManager.cpp
)
ADD_LIBRARY(GameServerCBilling STATIC ${GAMESERVERCBILLING_SRC})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)

ADD_EXECUTABLE(gameserver ${SRCS} ${MONSTER_SRC} ${ITEM_SRC} ${GUILD_SRC} ${EVENT_SRC} ${EFFECT_SRC} ${GQUEST_SRC})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
TARGET_LINK_LIBRARIES(gameserver Database ServerCore GameServerPackets Skill Core GameServerBilling LuaScript War Mofus Items Quest Couple Mission CTF GameServerCBilling xerces-c pthread util dl mysqlclient zlog lua z)

INSTALL(TARGETS gameserver DESTINATION bin)
