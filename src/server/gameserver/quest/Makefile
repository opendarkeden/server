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
VSHOME   = ../../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../../..
COREDIR  = ../../../Core
SERVDIR  = ../..
DBDIR    = ../../database
MYSQLDIR = /usr/local/lib/mysql
GSDIR    = ..
SKILLDIR = ../skill
ITEMDIR  = ../item
WARDIR  = ../war
#SIMPLEQUESTDIR  = ./Squest
LUASCRIPTDIR  = ./luaScript

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(WARDIR) -I$(LUASCRIPTDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

QUEST_OBJS = Trigger.o PropertyBuffer.o VariableBuffer.o VariableInfo.o TriggerParser.o TriggerManager.o

CONDITION_OBJS = \
	ConditionFactoryManager.o \
	ConditionEveryTime.o \
	ConditionAnsweredBy.o \
	ConditionFlagOn.o \
	ConditionFlagOff.o \
	ConditionAttrComp.o \
	ConditionRaceComp.o \
	ConditionSameClan.o \
	ConditionPayPlay.o \
	ConditionEnterMasterLair.o \
	ConditionEnterCastle.o \
	ConditionEnterHolyLand.o \
	ConditionEnterCastleDungeon.o \
	ConditionHasQuest.o \
	ConditionHasInvenSpace.o \
	ConditionCanEnterPayZone.o \
	ConditionCanEnterBeginnerZone.o \
	ConditionCanWarpGate.o \
	ConditionCanEnterLevelWarZone.o \
	ConditionCanPetQuest.o \
	ConditionCanEnterEventZone.o \
	ConditionEffectFlag.o \
	ConditionCanEnterGDRLair.o \
	ConditionExistReinforce.o \
	ConditionSiegeDefenderSide.o \
	ConditionSiegeAttackerSide.o \
	ConditionNotGuildMember.o \
	ConditionIsGuildMember.o \
	ConditionCanEnterQuestZone.o

ACTION_OBJS = \
	ActionFactoryManager.o \
	ActionSetPosition.o \
	ActionWander.o \
	ActionSay.o \
	ActionRandomSay.o \
	ActionAsk.o \
	ActionQuitDialogue.o \
	ActionPrepareShop.o \
	ActionSell.o \
	ActionBuy.o \
	ActionRegenShop.o \
	ActionTeachSkill.o \
	ActionHeal.o \
	ActionRedeemMotorcycle.o \
	ActionSearchMotorcycle.o \
	ActionRepair.o \
	ActionStashSell.o \
	ActionStashOpen.o \
	ActionRestore.o \
	ActionSetResurrectZone.o \
	ActionSilverCoating.o \
	ActionCreateGuild.o \
	ActionDestroyGuild.o \
	ActionTutorial.o \
	ActionGiveNewbieItem.o \
	ActionActivatePortal.o \
	ActionTurnOnFlag.o \
	ActionTurnOffFlag.o \
	ActionSystemMessage.o \
	ActionTakeDonation.o \
	ActionCallHelicopter.o \
	ActionRegenEventShop.o \
	ActionAskDynamic.o \
	ActionSayDynamic.o \
	ActionGiveSpecialEventItem.o \
	ActionRedistributeAttr.o \
	ActionTradeEventItem.o \
	ActionTradeLairItem.o \
	ActionShowGuildDialog.o \
	ActionSimpleQuestList.o \
	ActionSimpleQuestComplete.o \
	ActionSimpleQuestRegen.o \
	ActionTradeGiftBox.o \
	ActionGiveTestServerReward.o \
	ActionEnterCastleWithFee.o \
	ActionShowTaxBalance.o \
	ActionAskVariable.o \
	ActionWarRegistration.o \
	ActionShowWarSchedule.o \
	ActionJoinRaceWar.o \
	ActionGiveEventItem.o \
	ActionGiveAccountEventItem.o \
	ActionInitPartnerWaitingManager.o \
	ActionWaitForMeetCouple.o \
	ActionWaitForApartCouple.o \
	ActionAcceptCoupleRequest.o \
	ActionAcceptApartCouple.o \
	ActionForceApartCouple.o \
	ActionEnterPKZone.o \
	ActionWarpToResurrectPosition.o \
	ActionSelectQuest.o \
	ActionQuestReward.o \
	ActionWarpToNoviceZone.o \
	ActionCancelQuest.o \
	ActionInitSimpleQuest.o \
	ActionWanderZone.o \
	ActionInitEventQuest.o \
	ActionAskByQuestLevel.o \
	ActionGiveEventQuest.o \
	ActionAdvanceEventQuest.o \
	ActionCancelEventQuestScript.o \
	ActionRewardEventQuest.o \
	ActionGiveLotto.o \
	ActionGiveEventQuestScript.o \
	ActionStartEventQuest.o \
	ActionWarpInZone.o \
	ActionEventMeet.o \
	ActionGiveFinalLottoScript.o \
	ActionGiveQuestItem.o \
	ActionTakeOutGoods.o \
	ActionClearRankBonus.o \
	ActionContractGnomesHorn.o \
	ActionDownSkill.o \
	ActionMiniGame.o \
	ActionGiveItem.o \
	ActionActivateMazeExit.o \
	ActionActivateMazeEnter.o \
	ActionActivateMazeReturn.o \
	ActionSystemMessagePerRace.o \
	ActionWarpLevelWarZone.o \
	ActionCheckPartnerName.o \
	ActionStartPetQuest.o \
	ActionPetWithdraw.o \
	ActionPetDeposit.o \
	ActionEnterEventZone.o \
	ActionEnterGDRLair.o \
	ActionTradeGQuestEventItem.o \
	ActionRegisterSiege.o \
	ActionRegisterReinforce.o \
	ActionAcceptReinforce.o \
	ActionDenyReinforce.o \
	ActionEnterSiege.o \
	ActionRecallSiege.o \
	ActionSelectBloodBible.o \
	ActionClearBloodBible.o \
	ActionModifyTaxRatio.o \
	ActionSwapAdvancementItem.o \
	ActionShowDonationDialog.o \
	ActionEnterQuestZone.o \
	ActionShowConfirmGetEventItemDialog.o

OBJS = $(CONDITION_OBJS) $(ACTION_OBJS) $(QUEST_OBJS)

SRCS = $(OBJS:.o=.cpp)

DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)

TARGET   = $(LIBDIR)/libQuest.a


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all :
	$(MAKE) -C luaScript 
	$(MAKE) $(TARGET)
#$(MAKE) -C Squest

$(TARGET) : $(OBJS)
	ar rc $@ $^

clean :
	rm -rf *.o
	$(MAKE) -C luaScript clean
	$(MAKE) -C Squest clean

cleanall :
	rm -rf *.o $(TARGET)
	$(MAKE) -C luaScript cleanall
#	$(MAKE) -C Squest cleanll

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
