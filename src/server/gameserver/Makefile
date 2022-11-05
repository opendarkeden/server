#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
# Description :
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Directories Setting
#----------------------------------------------------------------------
VSHOME   = ../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../..
COREDIR  = ../../Core
SERVDIR  = ..
DBDIR    = ../database
SKILLDIR = ./skill
ITEMDIR  = ./item
BILLINGDIR  = ./billing
WARDIR  = ./war
COUPLEDIR = ./couple
TESTDIR  = ./test
MISSIONDIR = ./mission
CTFDIR = ./ctf
PYLIBDIR = /usr/local/lib/python2.2/config
PYINCDIR = /usr/local/include/python2.2
#GQUESTDIR = ./gq
#SIMPLEQUESTDIR  = ./quest/Squest

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__  -D__COMBAT__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR) -I$(WARDIR) -I$(COUPLEDIR) -I$(TESTDIR) -I$(MISSIONDIR) -I.
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 
#LIBS     = -L$(LIBDIR) -lItems -lQuest -lMofus -lGameServerDatabase -lServerCore -lGameServerPackets -lSkill -lCore -lGameServerBilling -lLuaScript -lGameServerTest -lWar -lCouple -lMission -lCTF -lGameServerCBilling -lxerces-c -lsicuuc -lsicudata -lCSAuth
LIBS     = -L$(LIBDIR) -lItems -lQuest -lMofus -lGameServerDatabase -lServerCore -lGameServerPackets -lSkill -lCore -lGameServerBilling -lLuaScript -lWar -lCouple -lMission -lCTF -lGameServerCBilling
#SYSLIBS  = -L$(MYSQLDIR) -static -lpthread -lnsl -lutil -ldl -lmysqlclient -llua -llualib -lz -lcppunit
SYSLIBS  = -lpthread -lnsl -lutil -lmysqlclient -llua5.1 -lxerces-c -ldl -lz

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

MONSTER_OBJS = Monster.o MonsterInfo.o MonsterManager.o \
	MonsterAI.o Directive.o MonsterNameManager.o MonsterCounter.o 

ITEM_OBJS = Item.o ItemInfo.o ItemUtil.o \
	ItemFactoryManager.o ItemInfoManager.o ItemLoaderManager.o \
	SlayerCorpse.o VampireCorpse.o OustersCorpse.o MonsterCorpse.o

GUILD_OBJS = Party.o Guild.o GuildManager.o GuildUnion.o

EVENT_OBJS = Event.o EventManager.o EventShutdown.o \
	EventRegeneration.o EventSave.o EventMorph.o EventResurrect.o EventReloadInfo.o \
	EventTransport.o EventKick.o EventSystemMessage.o EventRefreshHolyLandPlayer.o EventHeadCount.o \
	EventCBilling.o EventAuth.o

EFFECT_OBJS = Effect.o EffectManager.o EffectSchedule.o EffectLoaderManager.o \
	EffectShutDown.o EffectHPRecovery.o EffectMPRecovery.o \
	EffectAlignmentRecovery.o EffectEnemyErase.o \
	EffectDecayCorpse.o EffectDecayItem.o EffectAftermath.o EffectComa.o \
	EffectPrecedence.o EffectTransportItem.o EffectAddItem.o EffectRelicTable.o \
	EffectHasSlayerRelic.o EffectHasVampireRelic.o EffectIncreaseAttr.o \
	EffectDeleteItem.o EffectSlayerRelic.o EffectVampireRelic.o EffectRelicPosition.o \
	EffectRelicLock.o EffectMasterLairPass.o EffectContinualGroundAttack.o \
	EffectGhost.o EffectTransportCreature.o EffectGrandMasterSlayer.o \
	EffectGrandMasterVampire.o EffectKillAftermath.o EffectHasBloodBible.o \
	EffectShrineHoly.o EffectShrineGuard.o EffectShrineShield.o \
	EffectTransportItemToCorpse.o EffectAddItemToCorpse.o \
	EffectHasRelic.o EffectHasCastleSymbol.o EffectLoveChain.o \
	EffectPKZoneRegen.o EffectPKZoneResurrection.o EffectGrandMasterOusters.o \
	EffectTranslation.o EffectLoud.o EffectMute.o \
	SimpleCreatureEffect.o EffectRefiniumTicket.o EffectFlagInsert.o EffectHasSweeper.o EffectKeepSweeper.o \
	EffectRegenZone.o EffectTryingPosition.o EffectTrying.o EffectTryRegenZone.o EffectOnBridge.o EffectHasPet.o \
	EffectPacketSend.o EffectDarknessForbidden.o EffectCastingTrap.o EffectWithWarning.o EffectKickOut.o EffectGDRLairClose.o \
	EffectEventQuestReset.o EffectShareHP.o EffectCanEnterGDRLair.o \
	EffectAutoTurret.o EffectTurretLaser.o EffectKillTimer.o EffectDragonEye.o EffectRegenerate.o EffectRecallMotorcycle.o \
	EffectRideMotorcycle.o EffectDonation200501.o SimpleTileEffect.o EffectDeleteTile.o
	#EffectDropBloodBible.o

GQUEST_OBJS = \
	GQuestInfo.o GQuestManager.o GQuestElement.o GQuestStatus.o GQuestInventory.o \
	GQuestLevelElement.o GQuestTimeElement.o GQuestGiveVampireExpElement.o GQuestBloodDrainElement.o GQuestSayNPCElement.o GQuestExecuteElement.o \
	GQuestGiveQuestItemElement.o GQuestLoseQuestItemElement.o GQuestGiveItemElement.o GQuestTamePetElement.o GQuestRaceElement.o GQuestKilledElement.o \
	GQuestGiveDomainExpElement.o GQuestGiveMoneyElement.o GQuestSkillLevelElement.o GQuestRideMotorcycleElement.o GQuestGiveOustersExpElement.o \
	GQuestTouchWayPointElement.o GQuestHasQuestItemElement.o GQuestPartyDissectElement.o GQuestKillMonsterElement.o GQuestGiveEventQuestItemElement.o \
	GQuestEventPartyElement.o GQuestEventPartyCrashElement.o GQuestCompleteQuestElement.o GQuestFastMoveElement.o GQuestIllegalWarpElement.o \
	GQuestCheckPoint.o GQuestTravelElement.o GQuestORElement.o GQuestNOTElement.o GQuestRandomElement.o GQuestAdvancementClassLevelElement.o \
	GQuestClearDynamicZoneElement.o GQuestAddEffectElement.o GQuestRemoveEffectElement.o GQuestSetEnterDynamicZoneElement.o \
	GQuestEnterDynamicZoneElement.o GQuestStartOtherQuestElement.o GQuestGiveAdvancementClassExpElement.o GQuestAdvanceClassElement.o \
	GQuestWarpElement.o

OBJS = main.o Zone.o Slayer.o Vampire.o Ousters.o OustersEXPInfo.o \
	ClientManager.o ConnectionInfoManager.o \
	Creature.o CreatureManager.o DarkLightInfo.o Corpse.o \
	GamePlayer.o GameServer.o IncomingPlayerManager.o SharedServerClient.o \
	InfoClassManager.o Inventory.o LoginServerManager.o SharedServerManager.o\
	NPC.o NPCManager.o ResurrectLocationManager.o PCFinder.o \
	TelephoneCenter.o ParkingCenter.o PCManager.o Portal.o \
	Script.o ScriptManager.o ThreadManager.o ThreadPool.o \
	Tile.o Sector.o TimeManager.o GoodsInventory.o GoodsInfoManager.o \
	VisionInfo.o WeatherInfo.o WeatherManager.o \
	ZoneInfo.o ZoneGroup.o ZoneGroupManager.o ZoneInfoManager.o \
	ZonePlayerManager.o ZoneGroupThread.o \
	ObjectManager.o AbilityBalance.o \
	PlayerCreature.o ZoneUtil.o Treasure.o  \
	PacketUtil.o ConnectionInfo.o InventorySlot.o  \
	ObjectRegistry.o WayPoint.o OptionInfo.o \
	VolumeInfo.o VampEXPInfo.o ItemRack.o ShopRack.o Stash.o Garbage.o \
	ShopTemplate.o PriceManager.o CreatureUtil.o ItemMap.o \
	TradeManager.o FlagSet.o AlignmentManager.o \
	SkillInfo.o SkillDomainInfoManager.o SkillParentInfo.o InitAllStat.o \
	PrecedenceTable.o VariableManager.o CombatInfoManager.o \
	UniqueItemManager.o \
	MasterLairInfoManager.o MasterLairManager.o \
	MonsterSummonInfo.o LuckInfo.o \
	LogNameManager.o RankBonusInfo.o RankBonus.o \
	CastleInfoManager.o HolyLandRaceBonus.o \
	ShrineInfoManager.o GlobalItemPositionLoader.o \
	RelicUtil.o HolyLandManager.o \
	BloodBibleBonus.o BloodBibleBonusManager.o \
	CastleShrineInfoManager.o SkillPropertyManager.o \
	StringPool.o PKZoneInfoManager.o \
	GameServerGroupInfoManager.o DefaultOptionSetInfo.o \
	CastleSkillInfo.o TimeLimitItemManager.o ItemMineInfo.o \
	EventItemUtil.o SweeperSet.o SweeperBonus.o SweeperBonusManager.o \
	LevelWar.o LevelWarManager.o LevelWarZoneInfoManager.o \
	RegenZoneManager.o PetTypeInfo.o PetUtil.o PetAttrInfo.o PetExpInfo.o \
	RankExpTable.o SlayerAttrExpTable.o \
	Pet.o SystemAvailabilitiesManager.o LocalIP.o \
	ItemGradeManager.o EventZoneInfo.o SMSServiceThread.o \
	SMSAddressBook.o FiniteStateMachine.o GDRLairManager.o GDRLairAbstractStates.o \
	NicknameBook.o LevelNickInfoManager.o SiegeManager.o \
	BroadcastFilter.o Store.o AdvancementClassExpTable.o DynamicZoneManager.o \
	DynamicZoneInfo.o DynamicZone.o DynamicZoneGroup.o DynamicZoneGateOfAlter.o \
	DynamicZoneAlterOfBlood.o DynamicZoneFactoryManager.o DynamicZoneSlayerMirrorOfAbyss.o \
	DynamicZoneVampireMirrorOfAbyss.o DynamicZoneOustersMirrorOfAbyss.o \
	NewYear2005ItemUtil.o \
	$(MONSTER_OBJS) $(ITEM_OBJS) $(GUILD_OBJS) $(EFFECT_OBJS) $(EVENT_OBJS) $(COMBAT_OBJS) $(GQUEST_OBJS)

SRCS = $(OBJS:.o=.cpp)

DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

TARGET = $(BINDIR)/gameserver


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all :
	$(MAKE) -C mission
	$(MAKE) -C couple
	$(MAKE) -C war
	$(MAKE) -C item
	$(MAKE) -C skill
	$(MAKE) -C quest
	$(MAKE) -C billing
	$(MAKE) -C ctf
	$(MAKE) -C mofus
	$(MAKE) $(TARGET)
	# $(MAKE) -C test

gameserver :
	$(MAKE) -C mission
	$(MAKE) -C couple
	$(MAKE) -C war
	$(MAKE) -C item
	$(MAKE) -C skill
	$(MAKE) -C quest
	$(MAKE) -C billing
	$(MAKE) -C ctf
	$(MAKE) -C mofus
	$(MAKE) $(TARGET)
	# $(MAKE) -C test

#$(TARGET) : $(OBJS) $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libSkill.a $(LIBDIR)/libGameServerPackets.a $(LIBDIR)/libItems.a $(LIBDIR)/libQuest.a $(LIBDIR)/libMofus.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a $(LIBDIR)/libSharedServerPackets.a $(LIBDIR)/libGameServerBilling.a $(LIBDIR)/libLuaScript.a $(LIBDIR)/libGameServerTest.a $(LIBDIR)/libWar.a $(LIBDIR)/libCouple.a $(LIBDIR)/libMission.a $(LIBDIR)/libCTF.a $(LIBDIR)/libGameServerCBilling.a

$(TARGET) : $(OBJS) $(LIBDIR)/libGameServerDatabase.a $(LIBDIR)/libSkill.a $(LIBDIR)/libGameServerPackets.a $(LIBDIR)/libItems.a $(LIBDIR)/libQuest.a $(LIBDIR)/libMofus.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a $(LIBDIR)/libSharedServerPackets.a $(LIBDIR)/libGameServerBilling.a $(LIBDIR)/libLuaScript.a $(LIBDIR)/libWar.a $(LIBDIR)/libCouple.a $(LIBDIR)/libMission.a $(LIBDIR)/libCTF.a $(LIBDIR)/libGameServerCBilling.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS) -rdynamic

clean :
	rm -rf *.o
	$(MAKE) -C mission clean
	$(MAKE) -C couple clean
	$(MAKE) -C war clean
	$(MAKE) -C skill clean
	$(MAKE) -C item clean
	$(MAKE) -C quest clean
	$(MAKE) -C billing clean
	$(MAKE) -C test clean
	$(MAKE) -C ctf clean
	$(MAKE) -C mofus clean

cleanall :
	rm -rf *.o $(TARGET)
	$(MAKE) -C mission cleanall
	$(MAKE) -C couple cleanall
	$(MAKE) -C war cleanall
	$(MAKE) -C skill cleanall
	$(MAKE) -C item cleanall
	$(MAKE) -C quest cleanall
	$(MAKE) -C billing cleanall
	$(MAKE) -C test cleanall
	$(MAKE) -C ctf cleanall
	$(MAKE) -C mofus cleanall

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
