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
VSHOME = ../..
BINDIR = $(VSHOME)/bin
LIBDIR = $(VSHOME)/lib
LOGDIR = $(VSHOME)/log
SERVDIR = $(VSHOME)/src/server
DBDIR   = $(SERVDIR)/database
GSDIR   = $(SERVDIR)/gameserver
LSDIR   = $(SERVDIR)/loginserver
SSDIR   = $(SERVDIR)/sharedserver
SKILLDIR= $(GSDIR)/skill
ITEMDIR = $(GSDIR)/item
BILLINGDIR = $(GSDIR)/billing

#----------------------------------------------------------------------
# Core Library
#----------------------------------------------------------------------
CORE_OBJS = WarInfo.o RaceWarInfo.o GuildWarInfo.o LevelWarInfo.o BloodBibleBonusInfo.o \
			Assert.o Datagram.o SerialDatagram.o DatagramSocket.o FileAPI.o GameTime.o \
			ScriptParameter.o \
			Player.o PCSlayerInfo.o PCVampireInfo.o PCSlayerInfo2.o \
			PCVampireInfo2.o PCSlayerInfo3.o PCVampireInfo3.o \
			Properties.o Resource.o ResourceManager.o \
			ServerSocket.o Socket.o SocketAPI.o SocketImpl.o \
			SocketInputStream.o SocketOutputStream.o StringStream.o \
			Update.o UpdateManager.o InventoryInfo.o InventorySlotInfo.o \
			RideMotorcycleInfo.o RideMotorcycleSlotInfo.o \
			GearSlotInfo.o GearInfo.o ExtraInfo.o \
			ExtraSlotInfo.o PCItemInfo.o SubItemInfo.o \
			ModifyInfo.o ModifyItemInfo.o \
			EffectInfo.o SlayerSkillInfo.o VampireSkillInfo.o \
			SubSlayerSkillInfo.o SubVampireSkillInfo.o Utility.o VSDateTime.o ServerGroupInfo.o TimeChecker.o\
			NPCInfo.o Shape.o Geometry.o WorldInfo.o GuildInfo.o GuildMemberInfo.o \
			GuildInfo2.o GuildMemberInfo2.o \
			Encrypter.o	SocketEncryptInputStream.o SocketEncryptOutputStream.o \
			OustersSkillInfo.o PCOustersInfo.o PCOustersInfo2.o PCOustersInfo3.o SubOustersSkillInfo.o \
			ItemNameInfo.o SweeperBonusInfo.o PetInfo.o NicknameInfo.o QuestStatusInfo.o \
			BloodBibleSignInfo.o StoreInfo.o SXml.o

CORE_SRCS = $(CORE_OBJS:.o=.cpp)
CORE_LIB = $(LIBDIR)/libCore.a

LC_PACKET_SRC = LCCreatePCError.cpp LCLoginOK.cpp LCRegisterPlayerError.cpp LCVersionCheckOK.cpp \
  LCDeletePCOK.cpp LCQueryResultPlayerID.cpp LCServerList.cpp \
  LCCreatePCOK.cpp LCPCList.cpp LCRegisterPlayerOK.cpp LCWorldList.cpp \
  LCLoginError.cpp LCReconnect.cpp LCVersionCheckError.cpp  \
  LCDeletePCError.cpp LCQueryResultCharacterName.cpp LCSelectPCError.cpp

LG_PACKET_SRC := LGIncomingConnection.cpp LGIncomingConnectionError.cpp LGIncomingConnectionOK.cpp LGKickCharacter.cpp

CL_PACKET_SRC := CLCreatePC.cpp CLGetPCList.cpp CLGetWorldList.cpp \
	CLLogout.cpp CLQueryPlayerID.cpp CLRegisterPlayer.cpp CLSelectServer.cpp \
	CLVersionCheck.cpp CLChangeServer.cpp CLDeletePC.cpp CLGetServerList.cpp \
	CLLogin.cpp CLQueryCharacterName.cpp CLReconnectLogin.cpp CLSelectPC.cpp CLSelectWorld.cpp

GL_PACKET_SRC := GLIncomingConnection.cpp  GLIncomingConnectionError.cpp GLIncomingConnectionOK.cpp GLKickVerify.cpp

SG_PACKET_SRC := SGAddGuildMemberOK.cpp SGExpelGuildMemberOK.cpp SGModifyGuildIntroOK.cpp SGQuitGuildOK.cpp \
	SGDeleteGuildOK.cpp           SGGuildMemberLogOnOK.cpp           SGModifyGuildOK.cpp               \
	SGAddGuildOK.cpp                 SGGuildInfo.cpp SGModifyGuildMemberOK.cpp

GS_PACKET_SRC := GSAddGuild.cpp GSAddGuildMember.cpp GSExpelGuildMember.cpp GSGuildMemberLogOn.cpp GSModifyGuildIntro.cpp \
	GSModifyGuildMember.cpp GSQuitGuild.cpp GSRequestGuildInfo.cpp

GC_PACKET_SRC := GCActiveGuildList.cpp \
	GCAddBat.cpp \
	GCAddBurrowingCreature.cpp \
	GCAddEffect.cpp \
	GCAddEffectToTile.cpp \
	GCAddGearToInventory.cpp \
	GCAddGearToZone.cpp \
	GCAddHelicopter.cpp \
	GCAddInjuriousCreature.cpp \
	GCAddInstalledMineToZone.cpp \
	GCAddItemToInventory.cpp \
	GCAddItemToItemVerify.cpp \
	GCAddItemToZone.cpp \
	GCAddMonsterCorpse.cpp \
	GCAddMonster.cpp \
	GCAddMonsterFromBurrowing.cpp \
	GCAddMonsterFromTransformation.cpp \
	GCAddNewItemToZone.cpp \
	GCAddNickname.cpp \
	GCAddNPC.cpp \
	GCAddOustersCorpse.cpp \
	GCAddOusters.cpp \
	GCAddressListVerify.cpp \
	GCAddSlayerCorpse.cpp \
	GCAddSlayer.cpp \
	GCAddStoreItem.cpp \
	GCAddVampireCorpse.cpp \
	GCAddVampire.cpp \
	GCAddVampireFromBurrowing.cpp \
	GCAddVampireFromTransformation.cpp \
	GCAddVampirePortal.cpp \
	GCAddWolf.cpp \
	GCAttackArmsOK1.cpp \
	GCAttackArmsOK1Handler.cpp \
	GCAttackArmsOK2.cpp \
	GCAttackArmsOK2Handler.cpp \
	GCAttackArmsOK3.cpp \
	GCAttackArmsOK3Handler.cpp \
	GCAttackArmsOK4.cpp \
	GCAttackArmsOK4Handler.cpp \
	GCAttackArmsOK5.cpp \
	GCAttackArmsOK5Handler.cpp \
	GCAttack.cpp \
	GCAttackMeleeOK1.cpp \
	GCAttackMeleeOK1Handler.cpp \
	GCAttackMeleeOK2.cpp \
	GCAttackMeleeOK2Handler.cpp \
	GCAttackMeleeOK3.cpp \
	GCAttackMeleeOK3Handler.cpp \
	GCAuthKey.cpp \
	GCBloodBibleList.cpp \
	GCBloodBibleSignInfo.cpp \
	GCBloodBibleStatus.cpp \
	GCBloodDrainOK1.cpp \
	GCBloodDrainOK1Handler.cpp \
	GCBloodDrainOK2.cpp \
	GCBloodDrainOK2Handler.cpp \
	GCBloodDrainOK3.cpp \
	GCBloodDrainOK3Handler.cpp \
	GCCannotAdd.cpp \
	GCCannotUse.cpp \
	GCCastingSkill.cpp \
	GCChangeDarkLight.cpp \
	GCChangeInventoryItemNum.cpp \
	GCChangeShape.cpp \
	GCChangeWeather.cpp \
	GCCreateItem.cpp \
	GCCreatureDied.cpp \
	GCCrossCounterOK1.cpp \
	GCCrossCounterOK1Handler.cpp \
	GCCrossCounterOK2.cpp \
	GCCrossCounterOK2Handler.cpp \
	GCCrossCounterOK3.cpp \
	GCCrossCounterOK3Handler.cpp \
	GCDeleteandPickUpOK.cpp \
	GCDeleteEffectFromTile.cpp \
	GCDeleteInventoryItem.cpp \
	GCDeleteObject.cpp \
	GCDisconnect.cpp \
	GCDownSkillFailed.cpp \
	GCDownSkillOK.cpp \
	GCDropItemToZone.cpp \
	GCEnterVampirePortal.cpp \
	GCExecuteElement.cpp \
	GCFakeMove.cpp \
	GCFastMove.cpp \
	GCFlagWarStatus.cpp \
	GCFriendChatting.cpp \
	GCGetDamage.cpp \
	GCGetOffMotorCycle.cpp \
	GCGetOffMotorCycleFailed.cpp \
	GCGetOffMotorCycleOK.cpp \
	GCGlobalChat.cpp \
	GCGoodsList.cpp \
	GCGQuestInventory.cpp \
	GCGQuestStatusInfo.cpp \
	GCGQuestStatusModify.cpp \
	GCGuildChat.cpp \
	GCGuildMemberList.cpp \
	GCGuildResponse.cpp \
	GCHolyLandBonusInfo.cpp \
	GCHPRecoveryEndToOthers.cpp \
	GCHPRecoveryEndToSelf.cpp \
	GCHPRecoveryStartToOthers.cpp \
	GCHPRecoveryStartToSelf.cpp \
	GCKickMessage.cpp \
	GCKnockBack.cpp \
	GCKnocksTargetBackOK1.cpp \
	GCKnocksTargetBackOK1Handler.cpp \
	GCKnocksTargetBackOK2.cpp \
	GCKnocksTargetBackOK2Handler.cpp \
	GCKnocksTargetBackOK4.cpp \
	GCKnocksTargetBackOK4Handler.cpp \
	GCKnocksTargetBackOK5.cpp \
	GCKnocksTargetBackOK5Handler.cpp \
	GCLearnSkillFailed.cpp \
	GCLearnSkillOK.cpp \
	GCLearnSkillReady.cpp \
	GCLightning.cpp \
	GCMakeItemFail.cpp \
	GCMakeItemOK.cpp \
	GCMineExplosionOK1.cpp \
	GCMineExplosionOK1Handler.cpp \
	GCMineExplosionOK2.cpp \
	GCMineExplosionOK2Handler.cpp \
	GCMiniGameScores.cpp \
	GCModifyGuildMemberInfo.cpp \
	GCModifyInformation.cpp \
	GCModifyMoney.cpp \
	GCModifyNickname.cpp \
	GCModyfyMoney.cpp \
	GCMonsterKillQuestInfo.cpp \
	GCMorph1.cpp \
	GCMorph1Handler.cpp \
	GCMorphSlayer2.cpp \
	GCMorphSlayer2Handler.cpp \
	GCMorphVampire2.cpp \
	GCMorphVampire2Handler.cpp \
	GCMove.cpp \
	GCMoveError.cpp \
	GCMoveOK.cpp \
	GCMPRecoveryEnd.cpp \
	GCMPRecoveryStart.cpp \
	GCMyStoreInfo.cpp \
	GCNicknameList.cpp \
	GCNicknameVerify.cpp \
	GCNoticeEvent.cpp \
	GCNotifyWin.cpp \
	GCNPCAsk.cpp \
	GCNPCAskDynamic.cpp \
	GCNPCAskVariable.cpp \
	GCNPCInfo.cpp \
	GCNPCResponse.cpp \
	GCNPCSay.cpp \
	GCNPCSayDynamic.cpp \
	GCOtherGuildName.cpp \
	GCOtherModifyInfo.cpp \
	GCOtherStoreInfo.cpp \
	GCPartyError.cpp \
	GCPartyInvite.cpp \
	GCPartyJoined.cpp \
	GCPartyLeave.cpp \
	GCPartyPosition.cpp \
	GCPartySay.cpp \
	GCPetInfo.cpp \
	GCPetStashList.cpp \
	GCPetStashVerify.cpp \
	GCPetUseSkill.cpp \
	GCPhoneConnected.cpp \
	GCPhoneConnectionFailed.cpp \
	GCPhoneDisconnected.cpp \
	GCPhoneSay.cpp \
	GCQuestStatus.cpp \
	GCRankBonusInfo.cpp \
	GCRealWearingInfo.cpp \
	GCReconnect.cpp \
	GCReconnectLogin.cpp \
	GCRegenZoneStatus.cpp \
	GCReloadOK.cpp \
	GCRemoveCorpseHead.cpp \
	GCRemoveEffect.cpp \
	GCRemoveFromGear.cpp \
	GCRemoveInjuriousCreature.cpp \
	GCRemoveStoreItem.cpp \
	GCRequestedIP.cpp \
	GCRequestFailed.cpp \
	GCRequestPowerPointResult.cpp \
	GCRideMotorCycle.cpp \
	GCRideMotorCycleFailed.cpp \
	GCRideMotorCycleOK.cpp \
	GCRing.cpp \
	GCSay.cpp \
	GCSearchMotorcycleFail.cpp \
	GCSearchMotorcycleOK.cpp \
	GCSelectQuestID.cpp \
	GCSelectRankBonusFailed.cpp \
	GCSelectRankBonusOK.cpp \
	GCSetPosition.cpp \
	GCShopBought.cpp \
	GCShopBuyFail.cpp \
	GCShopBuyOK.cpp \
	GCShopList.cpp \
	GCShopListMysterious.cpp \
	GCShopMarketCondition.cpp \
	GCShopSellFail.cpp \
	GCShopSellOK.cpp \
	GCShopSold.cpp \
	GCShopVersion.cpp \
	GCShowGuildInfo.cpp \
	GCShowGuildJoin.cpp \
	GCShowGuildMemberInfo.cpp \
	GCShowGuildRegist.cpp \
	GCShowMessageBox.cpp \
	GCShowUnionInfo.cpp \
	GCShowWaitGuildInfo.cpp \
	GCSkillFailed1.cpp \
	GCSkillFailed1Handler.cpp \
	GCSkillFailed2.cpp \
	GCSkillFailed2Handler.cpp \
	GCSkillInfo.cpp \
	GCSkillToInventoryOK1.cpp \
	GCSkillToInventoryOK1Handler.cpp \
	GCSkillToInventoryOK2.cpp \
	GCSkillToInventoryOK2Handler.cpp \
	GCSkillToObjectOK1.cpp \
	GCSkillToObjectOK1Handler.cpp \
	GCSkillToObjectOK2.cpp \
	GCSkillToObjectOK2Handler.cpp \
	GCSkillToObjectOK3.cpp \
	GCSkillToObjectOK3Handler.cpp \
	GCSkillToObjectOK4.cpp \
	GCSkillToObjectOK4Handler.cpp \
	GCSkillToObjectOK5.cpp \
	GCSkillToObjectOK5Handler.cpp \
	GCSkillToObjectOK6.cpp \
	GCSkillToObjectOK6Handler.cpp \
	GCSkillToSelfOK1.cpp \
	GCSkillToSelfOK1Handler.cpp \
	GCSkillToSelfOK2.cpp \
	GCSkillToSelfOK2Handler.cpp \
	GCSkillToSelfOK3.cpp \
	GCSkillToSelfOK3Handler.cpp \
	GCSkillToTileOK1.cpp \
	GCSkillToTileOK1Handler.cpp \
	GCSkillToTileOK2.cpp \
	GCSkillToTileOK2Handler.cpp \
	GCSkillToTileOK3.cpp \
	GCSkillToTileOK3Handler.cpp \
	GCSkillToTileOK4.cpp \
	GCSkillToTileOK4Handler.cpp \
	GCSkillToTileOK5.cpp \
	GCSkillToTileOK5Handler.cpp \
	GCSkillToTileOK6.cpp \
	GCSkillToTileOK6Handler.cpp \
	GCSMSAddressList.cpp \
	GCStashList.cpp \
	GCStashSell.cpp \
	GCStatusCurrentHP.cpp \
	GCSubInventoryInfo.cpp \
	GCSweeperBonusInfo.cpp \
	GCSystemAvailabilities.cpp \
	GCSystemMessage.cpp \
	GCTakeOff.cpp \
	GCTakeOutFail.cpp \
	GCTakeOutOK.cpp \
	GCTeachSkillInfo.cpp \
	GCThrowBombOK1.cpp \
	GCThrowBombOK1Handler.cpp \
	GCThrowBombOK2.cpp \
	GCThrowBombOK2Handler.cpp \
	GCThrowBombOK3.cpp \
	GCThrowBombOK3Handler.cpp \
	GCThrowItemOK1.cpp \
	GCThrowItemOK1Handler.cpp \
	GCThrowItemOK2.cpp \
	GCThrowItemOK2Handler.cpp \
	GCThrowItemOK3.cpp \
	GCThrowItemOK3Handler.cpp \
	GCTimeLimitItemInfo.cpp \
	GCTradeAddItem.cpp \
	GCTradeError.cpp \
	GCTradeFinish.cpp \
	GCTradeMoney.cpp \
	GCTradePrepare.cpp \
	GCTradeRemoveItem.cpp \
	GCTradeVerify.cpp \
	GCUnburrowFail.cpp \
	GCUnburrowOK.cpp \
	GCUnionOfferList.cpp \
	GCUntransformFail.cpp \
	GCUntransformOK.cpp \
	GCUpdateInfo.cpp \
	GCUseBonusPointFail.cpp \
	GCUseBonusPointOK.cpp \
	GCUseOK.cpp \
	GCUsePowerPointResult.cpp \
	GCVisibleFail.cpp \
	GCVisibleOK.cpp \
	GCWaitGuildList.cpp \
	GCWarList.cpp \
	GCWarScheduleList.cpp \
	GCWhisper.cpp \
	GCWhisperFailed.cpp

CG_PACKET_SRC :=  CGAbsorbSoul.cpp \
	CGAcceptUnion.cpp \
	CGAddGearToMouse.cpp \
	CGAddInventoryToMouse.cpp \
	CGAddItemToCodeSheet.cpp \
	CGAddItemToItem.cpp \
	CGAddMouseToGear.cpp \
	CGAddMouseToInventory.cpp \
	CGAddMouseToQuickSlot.cpp \
	CGAddMouseToZone.cpp \
	CGAddQuickSlotToMouse.cpp \
	CGAddSMSAddress.cpp \
	CGAddZoneToInventory.cpp \
	CGAddZoneToMouse.cpp \
	CGAppointSubmaster.cpp \
	CGAttack.cpp \
	CGAuthKey.cpp \
	CGBloodDrain.cpp \
	CGBuyStoreItem.cpp \
	CGCastingSkill.cpp \
	CGConnect.cpp \
	CGCrashReport.cpp \
	CGDeleteSMSAddress.cpp \
	CGDenyUnion.cpp \
	CGDepositPet.cpp \
	CGDialUp.cpp \
	CGDisplayItem.cpp \
	CGDissectionCorpse.cpp \
	CGDonationMoney.cpp \
	CGDownSkill.cpp \
	CGDropMoney.cpp \
	CGExpelGuild.cpp \
	CGExpelGuildMember.cpp \
	CGFailQuest.cpp \
	CGGetEventItem.cpp \
	CGGetOffMotorCycle.cpp \
	CGGlobalChat.cpp \
	CGGQuestAccept.cpp \
	CGGQuestCancel.cpp \
	CGGuildChat.cpp \
	CGJoinGuild.cpp \
	CGLearnSkill.cpp \
	CGLogout.cpp \
	CGLotterySelect.cpp \
	CGMakeItem.cpp \
	CGMixItem.cpp \
	CGModifyGuildIntro.cpp \
	CGModifyGuildMember.cpp \
	CGModifyGuildMemberIntro.cpp \
	CGModifyNickname.cpp \
	CGModifyTaxRatio.cpp \
	CGMouseToStash.cpp \
	CGMove.cpp \
	CGNPCAskAnswer.cpp \
	CGNPCTalk.cpp \
	CGPartyInvite.cpp \
	CGPartyLeave.cpp \
	CGPartyPosition.cpp \
	CGPartySay.cpp \
	CGPetGamble.cpp \
	CGPhoneDisconnect.cpp \
	CGPhoneSay.cpp \
	CGPickupMoney.cpp \
	CGPortCheck.cpp \
	CGQuitGuild.cpp \
	CGQuitUnionAccept.cpp \
	CGQuitUnion.cpp \
	CGQuitUnionDeny.cpp \
	CGRangerSay.cpp \
	CGReady.cpp \
	CGRegistGuild.cpp \
	CGRelicToObject.cpp \
	CGReloadFromInventory.cpp \
	CGReloadFromQuickSlot.cpp \
	CGRequestGuildList.cpp \
	CGRequestGuildMemberList.cpp \
	CGRequestInfo.cpp \
	CGRequestIP.cpp \
	CGRequestNewbieItem.cpp \
	CGRequestPowerPoint.cpp \
	CGRequestRepair.cpp \
	CGRequestStoreInfo.cpp \
	CGRequestUnion.cpp \
	CGRequestUnionInfo.cpp \
	CGResurrect.cpp \
	CGRideMotorCycle.cpp \
	CGSay.cpp \
	CGSelectBloodBible.cpp \
	CGSelectGuild.cpp \
	CGSelectGuildMember.cpp \
	CGSelectNickname.cpp \
	CGSelectPortal.cpp \
	CGSelectQuest.cpp \
	CGSelectRankBonus.cpp \
	CGSelectRegenZone.cpp \
	CGSelectTileEffect.cpp \
	CGSelectWayPoint.cpp \
	CGSetSlayerHotKey.cpp \
	CGSetVampireHotKey.cpp \
	CGShopRequestBuy.cpp \
	CGShopRequestList.cpp \
	CGShopRequestSell.cpp \
	CGSilverCoating.cpp \
	CGSkillToInventory.cpp \
	CGSkillToNamed.cpp \
	CGSkillToObject.cpp \
	CGSkillToSelf.cpp \
	CGSkillToTile.cpp \
	CGSMSAddressList.cpp \
	CGSMSSend.cpp \
	CGStashDeposit.cpp \
	CGStashList.cpp \
	CGStashRequestBuy.cpp \
	CGStashToMouse.cpp \
	CGStashWithdraw.cpp \
	CGStoreClose.cpp \
	CGStoreOpen.cpp \
	CGStoreSign.cpp \
	CGSubmitScore.cpp \
	CGTakeOutGood.cpp \
	CGTameMonster.cpp \
	CGThrowBomb.cpp \
	CGThrowItem.cpp \
	CGTradeAddItem.cpp \
	CGTradeFinish.cpp \
	CGTradeMoney.cpp \
	CGTradePrepare.cpp \
	CGTradeRemoveItem.cpp \
	CGTryJoinGuild.cpp \
	CGTypeStringList.cpp \
	CGUnburrow.cpp \
	CGUndisplayItem.cpp \
	CGUntransform.cpp \
	CGUseBonusPoint.cpp \
	CGUseItemFromGear.cpp \
	CGUseItemFromGQuestInventory.cpp \
	CGUseItemFromInventory.cpp \
	CGUseMessageItemFromInventory.cpp \
	CGUsePotionFromInventory.cpp \
	CGUsePotionFromQuickSlot.cpp \
	CGUsePowerPoint.cpp \
	CGVerifyTime.cpp \
	CGVisible.cpp \
	CGWhisper.cpp \
	CGWithdrawPet.cpp \
	CGWithdrawTax.cpp

S_HANDLER_SRC := GSAddGuildHandler.cpp  GSAddGuildMemberHandler.cpp  GSExpelGuildMemberHandler.cpp  GSGuildMemberLogOnHandler.cpp  \
	GSModifyGuildIntroHandler.cpp GSModifyGuildMemberHandler.cpp  GSQuitGuildHandler.cpp  GSRequestGuildInfoHandler.cpp

L_HANDLER_SRC := CLDeletePCHandler.cpp CLGetWorldListHandler.cpp  CLQueryCharacterNameHandler.cpp \
	CLRegisterPlayerHandler.cpp  CLSelectWorldHandler.cpp              GLIncomingConnectionHandler.cpp \
	CLChangeServerHandler.cpp  CLGetPCListHandler.cpp      CLLoginHandler.cpp         CLQueryPlayerIDHandler.cpp \
	CLSelectPCHandler.cpp        CLVersionCheckHandler.cpp             GLIncomingConnectionOKHandler.cpp \
	CLCreatePCHandler.cpp      CLGetServerListHandler.cpp  CLLogoutHandler.cpp        CLReconnectLoginHandler.cpp \
	CLSelectServerHandler.cpp    GLIncomingConnectionErrorHandler.cpp  GLKickVerifyHandler.cpp

G_HANDLER_SRC :=  CGAbsorbSoulHandler.cpp            CGDenyUnionHandler.cpp         CGModifyGuildMemberHandler.cpp       CGRelicToObjectHandler.cpp           CGSelectTileEffectHandler.cpp  CGTakeOutGoodHandler.cpp                  CGWhisperHandler.cpp \
	CGAcceptUnionHandler.cpp           CGDepositPetHandler.cpp        CGModifyGuildMemberIntroHandler.cpp  CGReloadFromInventoryHandler.cpp     CGSelectWayPointHandler.cpp    CGTameMonsterHandler.cpp                  CGWithdrawPetHandler.cpp \
	CGAddGearToMouseHandler.cpp        CGDialUpHandler.cpp            CGModifyNicknameHandler.cpp          CGReloadFromQuickSlotHandler.cpp     CGSetSlayerHotKeyHandler.cpp   CGThrowBombHandler.cpp                    CGWithdrawTaxHandler.cpp \
	CGDisplayItemHandler.cpp       CGModifyTaxRatioHandler.cpp          CGRequestGuildListHandler.cpp        CGSetVampireHotKeyHandler.cpp  CGThrowItemHandler.cpp                    GGCommandHandler.cpp \
	CGAddInventoryToMouseHandler.cpp   CGDissectionCorpseHandler.cpp  CGMouseToStashHandler.cpp            CGRequestGuildMemberListHandler.cpp  CGShopRequestBuyHandler.cpp    CGTradeAddItemHandler.cpp                 GGGuildChatHandler.cpp \
	CGAddItemToCodeSheetHandler.cpp    CGDonationMoneyHandler.cpp     CGMoveHandler.cpp                    CGRequestInfoHandler.cpp             CGShopRequestListHandler.cpp   CGTradeFinishHandler.cpp                  GGServerChatHandler.cpp \
	CGAddItemToItemHandler.cpp         CGDownSkillHandler.cpp         CGNPCAskAnswerHandler.cpp            CGRequestIPHandler.cpp               CGShopRequestSellHandler.cpp   CGTradeMoneyHandler.cpp                   LGIncomingConnectionErrorHandler.cpp \
	CGAddMouseToGearHandler.cpp        CGDropMoneyHandler.cpp         CGNPCTalkHandler.cpp                 CGRequestNewbieItemHandler.cpp       CGSilverCoatingHandler.cpp     CGTradePrepareHandler.cpp                 LGIncomingConnectionHandler.cpp \
	CGAddMouseToInventoryHandler.cpp   CGExpelGuildHandler.cpp        CGPartyInviteHandler.cpp             CGRequestPowerPointHandler.cpp       CGSkillToInventoryHandler.cpp  CGTradeRemoveItemHandler.cpp              LGIncomingConnectionOKHandler.cpp \
	CGAddMouseToQuickSlotHandler.cpp   CGExpelGuildMemberHandler.cpp  CGPartyLeaveHandler.cpp              CGRequestRepairHandler.cpp           CGSkillToNamedHandler.cpp      CGTryJoinGuildHandler.cpp                 LGKickCharacterHandler.cpp \
	CGAddMouseToZoneHandler.cpp        CGFailQuestHandler.cpp         CGPartyPositionHandler.cpp           CGRequestStoreInfoHandler.cpp        CGSkillToObjectHandler.cpp     CGTypeStringListHandler.cpp               SGAddGuildMemberOKHandler.cpp \
	CGAddQuickSlotToMouseHandler.cpp   CGGetEventItemHandler.cpp      CGPartySayHandler.cpp                CGRequestUnionHandler.cpp            CGSkillToSelfHandler.cpp       CGUnburrowHandler.cpp                     SGAddGuildOKHandler.cpp \
	CGAddSMSAddressHandler.cpp         CGGetOffMotorCycleHandler.cpp  CGPetGambleHandler.cpp               CGRequestUnionInfoHandler.cpp        CGSkillToTileHandler.cpp       CGUndisplayItemHandler.cpp                SGDeleteGuildOKHandler.cpp \
	CGAddZoneToInventoryHandler.cpp    CGGlobalChatHandler.cpp        CGPhoneDisconnectHandler.cpp         CGResurrectHandler.cpp               CGSMSAddressListHandler.cpp    CGUntransformHandler.cpp                  SGExpelGuildMemberOKHandler.cpp \
	CGAddZoneToMouseHandler.cpp        CGGQuestAcceptHandler.cpp      CGPhoneSayHandler.cpp                CGRideMotorCycleHandler.cpp          CGSMSSendHandler.cpp           CGUseBonusPointHandler.cpp                SGGuildInfoHandler.cpp \
	CGAppointSubmasterHandler.cpp      CGGQuestCancelHandler.cpp      CGPickupMoneyHandler.cpp             CGSayHandler.cpp                     CGStashDepositHandler.cpp      CGUseItemFromGearHandler.cpp              SGGuildMemberLogOnOKHandler.cpp \
	CGAttackHandler.cpp                CGGuildChatHandler.cpp         CGPortCheckHandler.cpp               CGSelectBloodBibleHandler.cpp        CGStashListHandler.cpp         CGUseItemFromGQuestInventoryHandler.cpp   SGModifyGuildIntroOKHandler.cpp \
	CGAuthKeyHandler.cpp               CGJoinGuildHandler.cpp         CGQuitGuildHandler.cpp               CGSelectGuildHandler.cpp             CGStashRequestBuyHandler.cpp   CGUseItemFromInventoryHandler.cpp         SGModifyGuildMemberOKHandler.cpp \
	CGBloodDrainHandler.cpp            CGLearnSkillHandler.cpp        CGQuitUnionAcceptHandler.cpp         CGSelectGuildMemberHandler.cpp       CGStashToMouseHandler.cpp      CGUseMessageItemFromInventoryHandler.cpp  SGModifyGuildOKHandler.cpp \
	CGBuyStoreItemHandler.cpp          CGLogoutHandler.cpp            CGQuitUnionDenyHandler.cpp           CGSelectNicknameHandler.cpp          CGStashWithdrawHandler.cpp     CGUsePotionFromInventoryHandler.cpp       SGQuitGuildOKHandler.cpp \
	CGCastingSkillHandler.cpp          CGLotterySelectHandler.cpp     CGQuitUnionHandler.cpp               CGSelectPortalHandler.cpp            CGStoreCloseHandler.cpp        CGUsePotionFromQuickSlotHandler.cpp \
	CGConnectHandler.cpp               CGMakeItemHandler.cpp          CGRangerSayHandler.cpp               CGSelectQuestHandler.cpp             CGStoreOpenHandler.cpp         CGUsePowerPointHandler.cpp \
	CGCrashReportHandler.cpp           CGMixItemHandler.cpp           CGReadyHandler.cpp                   CGSelectRankBonusHandler.cpp         CGStoreSignHandler.cpp         CGVerifyTimeHandler.cpp \
	CGDeleteSMSAddressHandler.cpp      CGModifyGuildIntroHandler.cpp  CGRegistGuildHandler.cpp             CGSelectRegenZoneHandler.cpp         CGSubmitScoreHandler.cpp       CGVisibleHandler.cpp

#----------------------------------------------------------------------
# Packet Library for LoginServer
#----------------------------------------------------------------------
LS_PACKET_OBJS = PacketFactoryManager.ls.o PacketIDSet.ls.o PacketValidator.ls.o
LS_LIB_OBJS := $(LC_PACKET_SRC:.cpp=.o) $(LG_PACKET_SRC:.cpp=.o) $(CL_PACKET_SRC:.cpp=.o) $(GL_PACKET_SRC:.cpp=.o) $(L_HANDLER_SRC:.cpp=.ls.o) $(LS_PACKET_OBJS)
LS_PACKET_LIB  = $(LIBDIR)/libLoginServerPackets.a

#----------------------------------------------------------------------
# Packet Library for SharedServer
#----------------------------------------------------------------------
SS_PACKET_OBJS = PacketFactoryManager.ss.o PacketIDSet.ss.o PacketValidator.ss.o
SS_LIB_OBJS := $(SG_PACKET_SRC:.cpp=.o) $(GS_PACKET_SRC:.cpp=.o) $(S_HANDLER_SRC:.cpp=.ss.o) $(SS_PACKET_OBJS)
SS_PACKET_LIB  = $(LIBDIR)/libSharedServerPackets.a

#----------------------------------------------------------------------
# Packet Library for GameServer
#----------------------------------------------------------------------
GS_PACKET_OBJS = PacketFactoryManager.gs.o PacketIDSet.gs.o PacketValidator.gs.o
GS_LIB_OBJS := $(CG_PACKET_SRC:.cpp=.o) $(GC_PACKET_SRC:.cpp=.o) $(SG_PACKET_SRC:.cpp=.o) $(GS_PACKET_SRC:.cpp=.o) $(LG_PACKET_SRC:.cpp=.o) $(GL_PACKET_SRC:.cpp=.o) $(G_HANDLER_SRC:.cpp=.gs.o) $(GS_PACKET_OBJS)
GS_PACKET_LIB  = $(LIBDIR)/libGameServerPackets.a


SRCS = $(CORE_SRCS) $(LC_PACKET_SRC) $(LG_PACKET_SRC) $(CL_PACKET_SRC) $(GL_PACKET_SRC) $(L_HANDLER_SRC) $(SG_PACKET_SRC) $(GS_PACKET_SRC) $(S_HANDLER_SRC) $(GC_PACKET_SRC) $(CG_PACKET_SRC)

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o .gs.o .ls.o .us.o .ss.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I./loki -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR) -I.
CCFLAGS  = -Wall -c -g  

# .cpp.o : 
# 	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

DEPDIR = .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
DEPS = $(SRCS:%.cpp=$(DEPDIR)/%.d)
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CCFLAGS) $(TARGET_ARCH) $(DEFS) $(INCLUDES) -c
%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.cpp.gs.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -o $*.gs.o $<

.cpp.ls.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__LOGIN_SERVER__ $(INCLUDES) -I$(LSDIR) -o $*.ls.o $<

.cpp.us.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_SERVER__ $(INCLUDES) -o $*.us.o $<

.cpp.ss.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__SHARED_SERVER__ -I$(SSDIR) $(INCLUDES) -o $*.ss.o $<


#----------------------------------------------------------------------
# Packet Library for Updateserver 
#----------------------------------------------------------------------
US_PACKET_OBJS = PacketFactoryManager.us.o PacketIDSet.us.o PacketValidator.us.o
US_PACKET_SRCS = $(US_PACKET_OBJS:.us.o=.cpp)
US_PACKET_LIB  = $(LIBDIR)/libUpdateServerPackets.a


#----------------------------------------------------------------------
# All Targets
#----------------------------------------------------------------------
#TARGETS = $(CORE_LIB) $(LS_PACKET_LIB) $(GS_PACKET_LIB) $(LCC_PACKET_LIB) 
#SRCS = $(CORE_SRCS) $(LS_PACKET_SRCS) $(GS_PACKET_SRCS) $(LCC_PACKET_SRCS) $(US_PACKET_SRCS) $(SS_PACKET_SRCS)
TARGETS = $(CORE_LIB) $(LS_PACKET_LIB) $(GS_PACKET_LIB) $(SS_PACKET_LIB)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------

all : $(TARGETS)

core : $(CORE_LIB)

allloginserver : $(TARGETS)
	$(MAKE) -C Lpackets allloginserver
	$(MAKE) -C Gpackets allloginserver
	$(MAKE) -C Cpackets allloginserver
	$(MAKE) -C Upackets allloginserver
	$(MAKE) -C Spackets allloginserver

allgameserver : $(TARGETS)
	$(MAKE) -C Lpackets allgameserver
	$(MAKE) -C Gpackets allgameserver
	$(MAKE) -C Cpackets allgameserver
	$(MAKE) -C Upackets allgameserver
	$(MAKE) -C Spackets allgameserver
	$(MAKE) -C TOpackets allgameserver

allsharedserver : $(TARGETS)
	$(MAKE) -C Lpackets allsharedserver
	$(MAKE) -C Gpackets allsharedserver
	$(MAKE) -C Cpackets allsharedserver
	$(MAKE) -C Spackets allsharedserver
#	$(MAKE) -C Upackets allsharedserver

alltheoneserver : $(CORE_LIB)
	$(MAKE) -C TOpackets alltheoneserver

$(CORE_LIB) : $(CORE_OBJS)
	ar rc $@ $^

$(LS_PACKET_LIB) : $(LS_LIB_OBJS)
	ar rc $@ $^

$(SS_PACKET_LIB) : $(SS_LIB_OBJS)
	ar rc $@ $^

$(GS_PACKET_LIB) : $(GS_PACKET_OBJS)
	ar rc $@ $^

$(LCC_PACKET_LIB) : $(LCC_PACKET_OBJS)
	ar rc $@ $^

$(US_PACKET_LIB) : $(US_PACKET_OBJS)
	ar rc $@ $^

clean :
	# $(MAKE) -C Lpackets clean
	# $(MAKE) -C Gpackets clean
	# $(MAKE) -C Cpackets clean
	# $(MAKE) -C Upackets clean
	# $(MAKE) -C Spackets clean
	# $(MAKE) -C TOpackets clean
	rm -rf *.o

cleanall :
	$(MAKE) -C Lpackets cleanall
	$(MAKE) -C Gpackets cleanall
	$(MAKE) -C Cpackets cleanall
	$(MAKE) -C Upackets cleanall
	$(MAKE) -C Spackets cleanall
	$(MAKE) -C TOpackets cleanall
	rm -rf *.o $(TARGETS)

cleangameserver :
	$(MAKE) -C Lpackets cleangameserver
	$(MAKE) -C Gpackets cleangameserver
	$(MAKE) -C Cpackets cleangameserver
	$(MAKE) -C Upackets cleangameserver
	$(MAKE) -C Spackets cleangameserver
	$(MAKE) -C TOpackets cleangameserver
	rm -rf *.o $(TARGETS)

cleanloginserver :
	$(MAKE) -C Lpackets cleanloginserver
	$(MAKE) -C Gpackets cleanloginserver
	$(MAKE) -C Cpackets cleanloginserver
	$(MAKE) -C Upackets cleanloginserver
	$(MAKE) -C Spackets cleanloginserver
	rm -rf *.o $(TARGETS)

cleansharedserver :
	$(MAKE) -C Lpackets cleansharedserver
	$(MAKE) -C Gpackets cleansharedserver
	$(MAKE) -C Cpackets cleansharedserver
	$(MAKE) -C Upackets cleansharedserver
	$(MAKE) -C Spackets cleansharedserver
	rm -rf *.o $(TARGETS)

$(DEPDIR):
	@mkdir -p $@

$(DEPS):

include $(wildcard $(DEPS))
