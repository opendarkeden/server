# ============================================================================
# Core 库 - 基础核心代码，不依赖服务器类型
# ============================================================================

set(CORE_SOURCES
    SXml.cpp
    WarInfo.cpp
    RaceWarInfo.cpp
    GuildWarInfo.cpp
    LevelWarInfo.cpp
    BloodBibleBonusInfo.cpp
    Assert1.cpp
    Datagram.cpp
    SerialDatagram.cpp
    DatagramSocket.cpp
    FileAPI.cpp
    GameTime.cpp
    ScriptParameter.cpp
    Player.cpp
    PCSlayerInfo.cpp
    PCVampireInfo.cpp
    PCSlayerInfo2.cpp
    PCVampireInfo2.cpp
    PCSlayerInfo3.cpp
    PCVampireInfo3.cpp
    Properties.cpp
    Resource.cpp
    ResourceManager.cpp
    ServerSocket.cpp
    Socket.cpp
    SocketAPI.cpp
    SocketImpl.cpp
    SocketInputStream.cpp
    SocketOutputStream.cpp
    StringStream.cpp
    Update.cpp
    UpdateManager.cpp
    InventoryInfo.cpp
    InventorySlotInfo.cpp
    RideMotorcycleInfo.cpp
    RideMotorcycleSlotInfo.cpp
    GearSlotInfo.cpp
    GearInfo.cpp
    ExtraInfo.cpp
    ExtraSlotInfo.cpp
    PCItemInfo.cpp
    SubItemInfo.cpp
    ModifyInfo.cpp
    ModifyItemInfo.cpp
    EffectInfo.cpp
    SlayerSkillInfo.cpp
    VampireSkillInfo.cpp
    SubSlayerSkillInfo.cpp
    SubVampireSkillInfo.cpp
    Utility.cpp
    VSDateTime.cpp
    ServerGroupInfo.cpp
    TimeChecker.cpp
    NPCInfo.cpp
    Shape.cpp
    Geometry.cpp
    WorldInfo.cpp
    GuildInfo.cpp
    GuildMemberInfo.cpp
    GuildInfo2.cpp
    GuildMemberInfo2.cpp
    Encrypter.cpp
    SocketEncryptInputStream.cpp
    SocketEncryptOutputStream.cpp
    OustersSkillInfo.cpp
    PCOustersInfo.cpp
    PCOustersInfo2.cpp
    PCOustersInfo3.cpp
    SubOustersSkillInfo.cpp
    ItemNameInfo.cpp
    SweeperBonusInfo.cpp
    PetInfo.cpp
    NicknameInfo.cpp
    QuestStatusInfo.cpp
    BloodBibleSignInfo.cpp
    StoreInfo.cpp
    md5.cpp
)

add_library(Core STATIC ${CORE_SOURCES})
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ============================================================================
# 通用 Packet 源文件定义
# ============================================================================

# GC Packets (Game -> Client)
set(GC_PACKET_SOURCES
    GCActiveGuildList.cpp GCActiveGuildListHandler.cpp
    GCAddBat.cpp GCAddBatHandler.cpp
    GCAddBurrowingCreature.cpp GCAddBurrowingCreatureHandler.cpp
    GCAddEffect.cpp GCAddEffectHandler.cpp
    GCAddEffectToTile.cpp GCAddEffectToTileHandler.cpp
    GCAddGearToInventory.cpp GCAddGearToInventoryHandler.cpp
    GCAddGearToZone.cpp GCAddGearToZoneHandler.cpp
    GCAddHelicopter.cpp GCAddHelicopterHandler.cpp
    GCAddInjuriousCreature.cpp GCAddInjuriousCreatureHandler.cpp
    GCAddInstalledMineToZone.cpp GCAddInstalledMineToZoneHandler.cpp
    GCAddItemToInventory.cpp
    GCAddItemToItemVerify.cpp GCAddItemToItemVerifyHandler.cpp
    GCAddItemToZone.cpp
    GCAddMonster.cpp GCAddMonsterHandler.cpp
    GCAddMonsterCorpse.cpp GCAddMonsterCorpseHandler.cpp
    GCAddMonsterFromBurrowing.cpp GCAddMonsterFromBurrowingHandler.cpp
    GCAddMonsterFromTransformation.cpp GCAddMonsterFromTransformationHandler.cpp
    GCAddNewItemToZone.cpp GCAddNewItemToZoneHandler.cpp
    GCAddNickname.cpp GCAddNicknameHandler.cpp
    GCAddNPC.cpp GCAddNPCHandler.cpp
    GCAddOusters.cpp GCAddOustersHandler.cpp
    GCAddOustersCorpse.cpp GCAddOustersCorpseHandler.cpp
    GCAddSlayer.cpp GCAddSlayerHandler.cpp
    GCAddSlayerCorpse.cpp GCAddSlayerCorpseHandler.cpp
    GCAddStoreItem.cpp GCAddStoreItemHandler.cpp
    GCAddVampire.cpp GCAddVampireHandler.cpp
    GCAddVampireCorpse.cpp GCAddVampireCorpseHandler.cpp
    GCAddVampireFromBurrowing.cpp GCAddVampireFromBurrowingHandler.cpp
    GCAddVampireFromTransformation.cpp GCAddVampireFromTransformationHandler.cpp
    GCAddVampirePortal.cpp GCAddVampirePortalHandler.cpp
    GCAddWolf.cpp GCAddWolfHandler.cpp
    GCAddressListVerify.cpp GCAddressListVerifyHandler.cpp
    GCAttack.cpp GCAttackHandler.cpp
    GCAttackArmsOK1.cpp GCAttackArmsOK1Handler.cpp
    GCAttackArmsOK2.cpp GCAttackArmsOK2Handler.cpp
    GCAttackArmsOK3.cpp GCAttackArmsOK3Handler.cpp
    GCAttackArmsOK4.cpp GCAttackArmsOK4Handler.cpp
    GCAttackArmsOK5.cpp GCAttackArmsOK5Handler.cpp
    GCAttackMeleeOK1.cpp GCAttackMeleeOK1Handler.cpp
    GCAttackMeleeOK2.cpp GCAttackMeleeOK2Handler.cpp
    GCAttackMeleeOK3.cpp GCAttackMeleeOK3Handler.cpp
    GCAuthKey.cpp GCAuthKeyHandler.cpp
    GCBloodBibleList.cpp GCBloodBibleListHandler.cpp
    GCBloodBibleSignInfo.cpp GCBloodBibleSignInfoHandler.cpp
    GCBloodBibleStatus.cpp GCBloodBibleStatusHandler.cpp
    GCBloodDrainOK1.cpp GCBloodDrainOK1Handler.cpp
    GCBloodDrainOK2.cpp GCBloodDrainOK2Handler.cpp
    GCBloodDrainOK3.cpp GCBloodDrainOK3Handler.cpp
    GCCannotAdd.cpp GCCannotAddHandler.cpp
    GCCannotUse.cpp GCCannotUseHandler.cpp
    GCCastingSkill.cpp GCCastingSkillHandler.cpp
    GCChangeDarkLight.cpp GCChangeDarkLightHandler.cpp
    GCChangeInventoryItemNum.cpp
    GCChangeShape.cpp GCChangeShapeHandler.cpp
    GCChangeWeather.cpp GCChangeWeatherHandler.cpp
    GCCreateItem.cpp GCCreateItemHandler.cpp
    GCCreatureDied.cpp GCCreatureDiedHandler.cpp
    GCCrossCounterOK1.cpp GCCrossCounterOK1Handler.cpp
    GCCrossCounterOK2.cpp GCCrossCounterOK2Handler.cpp
    GCCrossCounterOK3.cpp GCCrossCounterOK3Handler.cpp
    GCDeleteandPickUpOK.cpp GCDeleteandPickUpOKHandler.cpp
    GCDeleteEffectFromTile.cpp GCDeleteEffectFromTileHandler.cpp
    GCDeleteInventoryItem.cpp GCDeleteInventoryItemHandler.cpp
    GCDeleteObject.cpp GCDeleteObjectHandler.cpp
    GCDisconnect.cpp GCDisconnectHandler.cpp
    GCDownSkillFailed.cpp GCDownSkillFailedHandler.cpp
    GCDownSkillOK.cpp GCDownSkillOKHandler.cpp
    GCDropItemToZone.cpp GCDropItemToZoneHandler.cpp
    GCEnterVampirePortal.cpp GCEnterVampirePortalHandler.cpp
    GCExecuteElement.cpp GCExecuteElementHandler.cpp
    GCFakeMove.cpp GCFakeMoveHandler.cpp
    GCFastMove.cpp GCFastMoveHandler.cpp
    GCFlagWarStatus.cpp GCFlagWarStatusHandler.cpp
    GCFriendChatting.cpp GCFriendChattingHandler.cpp
    GCGetDamage.cpp GCGetDamageHandler.cpp
    GCGetOffMotorCycle.cpp GCGetOffMotorCycleHandler.cpp
    GCGetOffMotorCycleFailed.cpp GCGetOffMotorCycleFailedHandler.cpp
    GCGetOffMotorCycleOK.cpp GCGetOffMotorCycleOKHandler.cpp
    GCGlobalChat.cpp GCGlobalChatHandler.cpp
    GCGoodsList.cpp GCGoodsListHandler.cpp
    GCGQuestInventory.cpp GCGQuestInventoryHandler.cpp
    GCGQuestStatusInfo.cpp GCGQuestStatusInfoHandler.cpp
    GCGQuestStatusModify.cpp GCGQuestStatusModifyHandler.cpp
    GCGuildChat.cpp GCGuildChatHandler.cpp
    GCGuildMemberList.cpp GCGuildMemberListHandler.cpp
    GCGuildResponse.cpp GCGuildResponseHandler.cpp
    GCHolyLandBonusInfo.cpp GCHolyLandBonusInfoHandler.cpp
    GCHPRecoveryEndToOthers.cpp GCHPRecoveryEndToOthersHandler.cpp
    GCHPRecoveryEndToSelf.cpp GCHPRecoveryEndToSelfHandler.cpp
    GCHPRecoveryStartToOthers.cpp GCHPRecoveryStartToOthersHandler.cpp
    GCHPRecoveryStartToSelf.cpp GCHPRecoveryStartToSelfHandler.cpp
    GCKickMessage.cpp GCKickMessageHandler.cpp
    GCKnockBack.cpp GCKnockBackHandler.cpp
    GCKnocksTargetBackOK1.cpp GCKnocksTargetBackOK1Handler.cpp
    GCKnocksTargetBackOK2.cpp GCKnocksTargetBackOK2Handler.cpp
    GCKnocksTargetBackOK4.cpp GCKnocksTargetBackOK4Handler.cpp
    GCKnocksTargetBackOK5.cpp GCKnocksTargetBackOK5Handler.cpp
    GCLearnSkillFailed.cpp GCLearnSkillFailedHandler.cpp
    GCLearnSkillOK.cpp GCLearnSkillOKHandler.cpp
    GCLearnSkillReady.cpp GCLearnSkillReadyHandler.cpp
    GCLightning.cpp GCLightningHandler.cpp
    GCMakeItemFail.cpp GCMakeItemFailHandler.cpp
    GCMakeItemOK.cpp GCMakeItemOKHandler.cpp
    GCMineExplosionOK1.cpp GCMineExplosionOK1Handler.cpp
    GCMineExplosionOK2.cpp GCMineExplosionOK2Handler.cpp
    GCMiniGameScores.cpp GCMiniGameScoresHandler.cpp
    GCModifyGuildMemberInfo.cpp GCModifyGuildMemberInfoHandler.cpp
    GCModifyInformation.cpp GCModifyInformationHandler.cpp
    GCModifyMoney.cpp GCModifyMoneyHandler.cpp
    GCModifyNickname.cpp GCModifyNicknameHandler.cpp
    GCModyfyMoney.cpp GCModyfyMoneyHandler.cpp
    GCMonsterKillQuestInfo.cpp GCMonsterKillQuestInfoHandler.cpp
    GCMonsterKillQuestStatus.cpp GCMonsterKillQuestStatusHandler.cpp
    GCMorph1.cpp GCMorph1Handler.cpp
    GCMorphSlayer2.cpp GCMorphSlayer2Handler.cpp
    GCMorphVampire2.cpp GCMorphVampire2Handler.cpp
    GCMove.cpp GCMoveHandler.cpp
    GCMoveError.cpp GCMoveErrorHandler.cpp
    GCMoveOK.cpp GCMoveOKHandler.cpp
    GCMPRecoveryEnd.cpp GCMPRecoveryEndHandler.cpp
    GCMPRecoveryStart.cpp GCMPRecoveryStartHandler.cpp
    GCMyStoreInfo.cpp GCMyStoreInfoHandler.cpp
    GCNicknameList.cpp GCNicknameListHandler.cpp
    GCNicknameVerify.cpp GCNicknameVerifyHandler.cpp
    GCNoticeEvent.cpp GCNoticeEventHandler.cpp
    GCNotifyWin.cpp GCNotifyWinHandler.cpp
    GCNPCAsk.cpp GCNPCAskHandler.cpp
    GCNPCAskDynamic.cpp GCNPCAskDynamicHandler.cpp
    GCNPCAskVariable.cpp GCNPCAskVariableHandler.cpp
    GCNPCInfo.cpp GCNPCInfoHandler.cpp
    GCNPCResponse.cpp GCNPCResponseHandler.cpp
    GCNPCSay.cpp GCNPCSayHandler.cpp
    GCNPCSayDynamic.cpp GCNPCSayDynamicHandler.cpp
    GCOtherGuildName.cpp GCOtherGuildNameHandler.cpp
    GCOtherModifyInfo.cpp GCOtherModifyInfoHandler.cpp
    GCOtherStoreInfo.cpp GCOtherStoreInfoHandler.cpp
    GCPartyError.cpp GCPartyErrorHandler.cpp
    GCPartyInvite.cpp GCPartyInviteHandler.cpp
    GCPartyJoined.cpp GCPartyJoinedHandler.cpp
    GCPartyLeave.cpp GCPartyLeaveHandler.cpp
    GCPartyPosition.cpp GCPartyPositionHandler.cpp
    GCPartySay.cpp GCPartySayHandler.cpp
    GCPetInfo.cpp GCPetInfoHandler.cpp
    GCPetStashList.cpp GCPetStashListHandler.cpp
    GCPetStashVerify.cpp GCPetStashVerifyHandler.cpp
    GCPetUseSkill.cpp GCPetUseSkillHandler.cpp
    GCPhoneConnected.cpp GCPhoneConnectedHandler.cpp
    GCPhoneConnectionFailed.cpp GCPhoneConnectionFailedHandler.cpp
    GCPhoneDisconnected.cpp GCPhoneDisconnectedHandler.cpp
    GCPhoneSay.cpp GCPhoneSayHandler.cpp
    GCQuestStatus.cpp GCQuestStatusHandler.cpp
    GCRankBonusInfo.cpp GCRankBonusInfoHandler.cpp
    GCRealWearingInfo.cpp GCRealWearingInfoHandler.cpp
    GCReconnect.cpp GCReconnectHandler.cpp
    GCReconnectLogin.cpp GCReconnectLoginHandler.cpp
    GCRegenZoneStatus.cpp GCRegenZoneStatusHandler.cpp
    GCReloadOK.cpp GCReloadOKHandler.cpp
    GCRemoveCorpseHead.cpp GCRemoveCorpseHeadHandler.cpp
    GCRemoveEffect.cpp GCRemoveEffectHandler.cpp
    GCRemoveFromGear.cpp GCRemoveFromGearHandler.cpp
    GCRemoveInjuriousCreature.cpp GCRemoveInjuriousCreatureHandler.cpp
    GCRemoveStoreItem.cpp GCRemoveStoreItemHandler.cpp
    GCRequestedIP.cpp GCRequestedIPHandler.cpp
    GCRequestFailed.cpp GCRequestFailedHandler.cpp
    GCRequestPowerPointResult.cpp GCRequestPowerPointResultHandler.cpp
    GCRideMotorCycle.cpp GCRideMotorCycleHandler.cpp
    GCRideMotorCycleFailed.cpp GCRideMotorCycleFailedHandler.cpp
    GCRideMotorCycleOK.cpp GCRideMotorCycleOKHandler.cpp
    GCRing.cpp GCRingHandler.cpp
    GCSay.cpp GCSayHandler.cpp
    GCSearchMotorcycleFail.cpp GCSearchMotorcycleFailHandler.cpp
    GCSearchMotorcycleOK.cpp GCSearchMotorcycleOKHandler.cpp
    GCSelectQuestID.cpp GCSelectQuestIDHandler.cpp
    GCSelectRankBonusFailed.cpp GCSelectRankBonusFailedHandler.cpp
    GCSelectRankBonusOK.cpp GCSelectRankBonusOKHandler.cpp
    GCSetPosition.cpp GCSetPositionHandler.cpp
    GCShopBought.cpp GCShopBoughtHandler.cpp
    GCShopBuyFail.cpp GCShopBuyFailHandler.cpp
    GCShopBuyOK.cpp GCShopBuyOKHandler.cpp
    GCShopList.cpp GCShopListHandler.cpp
    GCShopListMysterious.cpp GCShopListMysteriousHandler.cpp
    GCShopMarketCondition.cpp GCShopMarketConditionHandler.cpp
    GCShopSellFail.cpp GCShopSellFailHandler.cpp
    GCShopSellOK.cpp GCShopSellOKHandler.cpp
    GCShopSold.cpp GCShopSoldHandler.cpp
    GCShopVersion.cpp GCShopVersionHandler.cpp
    GCShowGuildInfo.cpp GCShowGuildInfoHandler.cpp
    GCShowGuildJoin.cpp GCShowGuildJoinHandler.cpp
    GCShowGuildMemberInfo.cpp GCShowGuildMemberInfoHandler.cpp
    GCShowGuildRegist.cpp GCShowGuildRegistHandler.cpp
    GCShowMessageBox.cpp GCShowMessageBoxHandler.cpp
    GCShowUnionInfo.cpp GCShowUnionInfoHandler.cpp
    GCShowWaitGuildInfo.cpp GCShowWaitGuildInfoHandler.cpp
    GCSkillFailed1.cpp GCSkillFailed1Handler.cpp
    GCSkillFailed2.cpp GCSkillFailed2Handler.cpp
    GCSkillInfo.cpp GCSkillInfoHandler.cpp
    GCSkillToInventoryOK1.cpp GCSkillToInventoryOK1Handler.cpp
    GCSkillToInventoryOK2.cpp GCSkillToInventoryOK2Handler.cpp
    GCSkillToObjectOK1.cpp GCSkillToObjectOK1Handler.cpp
    GCSkillToObjectOK2.cpp GCSkillToObjectOK2Handler.cpp
    GCSkillToObjectOK3.cpp GCSkillToObjectOK3Handler.cpp
    GCSkillToObjectOK4.cpp GCSkillToObjectOK4Handler.cpp
    GCSkillToObjectOK5.cpp GCSkillToObjectOK5Handler.cpp
    GCSkillToObjectOK6.cpp GCSkillToObjectOK6Handler.cpp
    GCSkillToSelfOK1.cpp GCSkillToSelfOK1Handler.cpp
    GCSkillToSelfOK2.cpp GCSkillToSelfOK2Handler.cpp
    GCSkillToSelfOK3.cpp GCSkillToSelfOK3Handler.cpp
    GCSkillToTileOK1.cpp GCSkillToTileOK1Handler.cpp
    GCSkillToTileOK2.cpp GCSkillToTileOK2Handler.cpp
    GCSkillToTileOK3.cpp GCSkillToTileOK3Handler.cpp
    GCSkillToTileOK4.cpp GCSkillToTileOK4Handler.cpp
    GCSkillToTileOK5.cpp GCSkillToTileOK5Handler.cpp
    GCSkillToTileOK6.cpp GCSkillToTileOK6Handler.cpp
    GCSMSAddressList.cpp GCSMSAddressListHandler.cpp
    GCStashList.cpp GCStashListHandler.cpp
    GCStashSell.cpp GCStashSellHandler.cpp
    GCStatusCurrentHP.cpp GCStatusCurrentHPHandler.cpp
    GCSubInventoryInfo.cpp GCSubInventoryInfoHandler.cpp
    GCSweeperBonusInfo.cpp GCSweeperBonusInfoHandler.cpp
    GCSystemAvailabilities.cpp GCSystemAvailabilitiesHandler.cpp
    GCSystemMessage.cpp GCSystemMessageHandler.cpp
    GCTakeOff.cpp GCTakeOffHandler.cpp
    GCTakeOutFail.cpp GCTakeOutFailHandler.cpp
    GCTakeOutOK.cpp GCTakeOutOKHandler.cpp
    GCTeachSkillInfo.cpp GCTeachSkillInfoHandler.cpp
    GCThrowBombOK1.cpp GCThrowBombOK1Handler.cpp
    GCThrowBombOK2.cpp GCThrowBombOK2Handler.cpp
    GCThrowBombOK3.cpp GCThrowBombOK3Handler.cpp
    GCThrowItemOK1.cpp GCThrowItemOK1Handler.cpp
    GCThrowItemOK2.cpp GCThrowItemOK2Handler.cpp
    GCThrowItemOK3.cpp GCThrowItemOK3Handler.cpp
    GCTimeLimitItemInfo.cpp GCTimeLimitItemInfoHandler.cpp
    GCTradeAddItem.cpp GCTradeAddItemHandler.cpp
    GCTradeError.cpp GCTradeErrorHandler.cpp
    GCTradeFinish.cpp GCTradeFinishHandler.cpp
    GCTradeMoney.cpp GCTradeMoneyHandler.cpp
    GCTradePrepare.cpp GCTradePrepareHandler.cpp
    GCTradeRemoveItem.cpp GCTradeRemoveItemHandler.cpp
    GCTradeVerify.cpp GCTradeVerifyHandler.cpp
    GCUnburrowFail.cpp GCUnburrowFailHandler.cpp
    GCUnburrowOK.cpp GCUnburrowOKHandler.cpp
    GCUnionOfferList.cpp GCUnionOfferListHandler.cpp
    GCUntransformFail.cpp GCUntransformFailHandler.cpp
    GCUntransformOK.cpp GCUntransformOKHandler.cpp
    GCUpdateInfo.cpp GCUpdateInfoHandler.cpp
    GCUseBonusPointFail.cpp GCUseBonusPointFailHandler.cpp
    GCUseBonusPointOK.cpp GCUseBonusPointOKHandler.cpp
    GCUseOK.cpp GCUseOKHandler.cpp
    GCUsePowerPointResult.cpp GCUsePowerPointResultHandler.cpp
    GCVisibleFail.cpp GCVisibleFailHandler.cpp
    GCVisibleOK.cpp GCVisibleOKHandler.cpp
    GCWaitGuildList.cpp GCWaitGuildListHandler.cpp
    GCWarList.cpp GCWarListHandler.cpp
    GCWarScheduleList.cpp GCWarScheduleListHandler.cpp
    GCWhisper.cpp GCWhisperHandler.cpp
    GCWhisperFailed.cpp GCWhisperFailedHandler.cpp
)


# CG Packets (Client -> Game)
set(CG_PACKET_SOURCES
    CGAbsorbSoul.cpp CGAbsorbSoulHandler.cpp
    CGAcceptUnion.cpp CGAcceptUnionHandler.cpp
    CGAddGearToMouse.cpp CGAddGearToMouseHandler.cpp
    CGAddInjuriousCreature.cpp CGAddInjuriousCreatureHandler.cpp
    CGAddInventoryToMouse.cpp CGAddInventoryToMouseHandler.cpp
    CGAddItemToCodeSheet.cpp CGAddItemToCodeSheetHandler.cpp
    CGAddItemToItem.cpp CGAddItemToItemHandler.cpp
    CGAddMouseToGear.cpp CGAddMouseToGearHandler.cpp
    CGAddMouseToInventory.cpp CGAddMouseToInventoryHandler.cpp
    CGAddMouseToQuickSlot.cpp CGAddMouseToQuickSlotHandler.cpp
    CGAddMouseToZone.cpp CGAddMouseToZoneHandler.cpp
    CGAddQuickSlotToMouse.cpp CGAddQuickSlotToMouseHandler.cpp
    CGAddSMSAddress.cpp CGAddSMSAddressHandler.cpp
    CGAddZoneToInventory.cpp CGAddZoneToInventoryHandler.cpp
    CGAddZoneToMouse.cpp CGAddZoneToMouseHandler.cpp
    CGAppointSubmaster.cpp CGAppointSubmasterHandler.cpp
    CGAttack.cpp CGAttackHandler.cpp
    CGAuthKey.cpp CGAuthKeyHandler.cpp
    CGBloodDrain.cpp CGBloodDrainHandler.cpp
    CGBuyStoreItem.cpp CGBuyStoreItemHandler.cpp
    CGCastingSkill.cpp CGCastingSkillHandler.cpp
    CGConnect.cpp CGConnectHandler.cpp
    CGConnectSetKey.cpp CGConnectSetKeyHandler.cpp
    CGCrashReport.cpp CGCrashReportHandler.cpp
    CGDeleteSMSAddress.cpp CGDeleteSMSAddressHandler.cpp
    CGDenyUnion.cpp CGDenyUnionHandler.cpp
    CGDepositPet.cpp CGDepositPetHandler.cpp
    CGDialUp.cpp CGDialUpHandler.cpp
    CGDisplayItem.cpp CGDisplayItemHandler.cpp
    CGDissectionCorpse.cpp CGDissectionCorpseHandler.cpp
    CGDonationMoney.cpp CGDonationMoneyHandler.cpp
    CGDownSkill.cpp CGDownSkillHandler.cpp
    CGDropMoney.cpp CGDropMoneyHandler.cpp
    CGExpelGuild.cpp CGExpelGuildHandler.cpp
    CGExpelGuildMember.cpp CGExpelGuildMemberHandler.cpp
    CGFailQuest.cpp CGFailQuestHandler.cpp
    CGGetEventItem.cpp CGGetEventItemHandler.cpp
    CGGetOffMotorCycle.cpp CGGetOffMotorCycleHandler.cpp
    CGGlobalChat.cpp CGGlobalChatHandler.cpp
    CGGQuestAccept.cpp CGGQuestAcceptHandler.cpp
    CGGQuestCancel.cpp CGGQuestCancelHandler.cpp
    CGGuildChat.cpp CGGuildChatHandler.cpp
    CGJoinGuild.cpp CGJoinGuildHandler.cpp
    CGLearnSkill.cpp CGLearnSkillHandler.cpp
    CGLogout.cpp CGLogoutHandler.cpp
    CGLotterySelect.cpp CGLotterySelectHandler.cpp
    CGMakeItem.cpp CGMakeItemHandler.cpp
    CGMixItem.cpp CGMixItemHandler.cpp
    CGModifyGuildIntro.cpp CGModifyGuildIntroHandler.cpp
    CGModifyGuildMember.cpp CGModifyGuildMemberHandler.cpp
    CGModifyGuildMemberIntro.cpp CGModifyGuildMemberIntroHandler.cpp
    CGModifyNickname.cpp CGModifyNicknameHandler.cpp
    CGModifyTaxRatio.cpp CGModifyTaxRatioHandler.cpp
    CGMouseToStash.cpp CGMouseToStashHandler.cpp
    CGMove.cpp CGMoveHandler.cpp
    CGNPCAskAnswer.cpp CGNPCAskAnswerHandler.cpp
    CGNPCTalk.cpp CGNPCTalkHandler.cpp
    CGPartyInvite.cpp CGPartyInviteHandler.cpp
    CGPartyLeave.cpp CGPartyLeaveHandler.cpp
    CGPartyPosition.cpp CGPartyPositionHandler.cpp
    CGPartySay.cpp CGPartySayHandler.cpp
    CGPetGamble.cpp CGPetGambleHandler.cpp
    CGPhoneDisconnect.cpp CGPhoneDisconnectHandler.cpp
    CGPhoneSay.cpp CGPhoneSayHandler.cpp
    CGPickupMoney.cpp CGPickupMoneyHandler.cpp
    CGPortCheck.cpp CGPortCheckHandler.cpp
    CGQuitGuild.cpp CGQuitGuildHandler.cpp
    CGQuitUnion.cpp CGQuitUnionHandler.cpp
    CGQuitUnionAccept.cpp CGQuitUnionAcceptHandler.cpp
    CGQuitUnionDeny.cpp CGQuitUnionDenyHandler.cpp
    CGRangerSay.cpp CGRangerSayHandler.cpp
    CGReady.cpp CGReadyHandler.cpp
    CGRegistGuild.cpp CGRegistGuildHandler.cpp
    CGRelicToObject.cpp CGRelicToObjectHandler.cpp
    CGReloadFromInventory.cpp CGReloadFromInventoryHandler.cpp
    CGReloadFromQuickSlot.cpp CGReloadFromQuickSlotHandler.cpp
    CGRequestGuildList.cpp CGRequestGuildListHandler.cpp
    CGRequestGuildMemberList.cpp CGRequestGuildMemberListHandler.cpp
    CGRequestInfo.cpp CGRequestInfoHandler.cpp
    CGRequestIP.cpp CGRequestIPHandler.cpp
    CGRequestNewbieItem.cpp CGRequestNewbieItemHandler.cpp
    CGRequestPowerPoint.cpp CGRequestPowerPointHandler.cpp
    CGRequestRepair.cpp CGRequestRepairHandler.cpp
    CGRequestStoreInfo.cpp CGRequestStoreInfoHandler.cpp
    CGRequestUnion.cpp CGRequestUnionHandler.cpp
    CGRequestUnionInfo.cpp CGRequestUnionInfoHandler.cpp
    CGResurrect.cpp CGResurrectHandler.cpp
    CGRideMotorCycle.cpp CGRideMotorCycleHandler.cpp
    CGSay.cpp CGSayHandler.cpp
    CGSelectBloodBible.cpp CGSelectBloodBibleHandler.cpp
    CGSelectGuild.cpp CGSelectGuildHandler.cpp
    CGSelectGuildMember.cpp CGSelectGuildMemberHandler.cpp
    CGSelectNickname.cpp CGSelectNicknameHandler.cpp
    CGSelectPortal.cpp CGSelectPortalHandler.cpp
    CGSelectQuest.cpp CGSelectQuestHandler.cpp
    CGSelectRankBonus.cpp CGSelectRankBonusHandler.cpp
    CGSelectRegenZone.cpp CGSelectRegenZoneHandler.cpp
    CGSelectTileEffect.cpp CGSelectTileEffectHandler.cpp
    CGSelectWayPoint.cpp CGSelectWayPointHandler.cpp
    CGSetSlayerHotKey.cpp CGSetSlayerHotKeyHandler.cpp
    CGSetVampireHotKey.cpp CGSetVampireHotKeyHandler.cpp
    CGShopRequestBuy.cpp CGShopRequestBuyHandler.cpp
    CGShopRequestList.cpp CGShopRequestListHandler.cpp
    CGShopRequestSell.cpp CGShopRequestSellHandler.cpp
    CGSilverCoating.cpp CGSilverCoatingHandler.cpp
    CGSkillToInventory.cpp CGSkillToInventoryHandler.cpp
    CGSkillToNamed.cpp CGSkillToNamedHandler.cpp
    CGSkillToObject.cpp CGSkillToObjectHandler.cpp
    CGSkillToSelf.cpp CGSkillToSelfHandler.cpp
    CGSkillToTile.cpp CGSkillToTileHandler.cpp
    CGSMSAddressList.cpp CGSMSAddressListHandler.cpp
    CGSMSSend.cpp CGSMSSendHandler.cpp
    CGStashDeposit.cpp CGStashDepositHandler.cpp
    CGStashList.cpp CGStashListHandler.cpp
    CGStashRequestBuy.cpp CGStashRequestBuyHandler.cpp
    CGStashToMouse.cpp CGStashToMouseHandler.cpp
    CGStashWithdraw.cpp CGStashWithdrawHandler.cpp
    CGStoreClose.cpp CGStoreCloseHandler.cpp
    CGStoreOpen.cpp CGStoreOpenHandler.cpp
    CGStoreSign.cpp CGStoreSignHandler.cpp
    CGSubmitScore.cpp CGSubmitScoreHandler.cpp
    CGTakeOutGood.cpp CGTakeOutGoodHandler.cpp
    CGTameMonster.cpp CGTameMonsterHandler.cpp
    CGThrowBomb.cpp CGThrowBombHandler.cpp
    CGThrowItem.cpp CGThrowItemHandler.cpp
    CGTradeAddItem.cpp CGTradeAddItemHandler.cpp
    CGTradeFinish.cpp CGTradeFinishHandler.cpp
    CGTradeMoney.cpp CGTradeMoneyHandler.cpp
    CGTradePrepare.cpp CGTradePrepareHandler.cpp
    CGTradeRemoveItem.cpp CGTradeRemoveItemHandler.cpp
    CGTryJoinGuild.cpp CGTryJoinGuildHandler.cpp
    CGTypeStringList.cpp CGTypeStringListHandler.cpp
    CGUnburrow.cpp CGUnburrowHandler.cpp
    CGUndisplayItem.cpp CGUndisplayItemHandler.cpp
    CGUntransform.cpp CGUntransformHandler.cpp
    CGUseBonusPoint.cpp CGUseBonusPointHandler.cpp
    CGUseItemFromGear.cpp CGUseItemFromGearHandler.cpp
    CGUseItemFromGQuestInventory.cpp CGUseItemFromGQuestInventoryHandler.cpp
    CGUseItemFromInventory.cpp CGUseItemFromInventoryHandler.cpp
    CGUseMessageItemFromInventory.cpp CGUseMessageItemFromInventoryHandler.cpp
    CGUsePotionFromInventory.cpp CGUsePotionFromInventoryHandler.cpp
    CGUsePotionFromQuickSlot.cpp CGUsePotionFromQuickSlotHandler.cpp
    CGUsePowerPoint.cpp CGUsePowerPointHandler.cpp
    CGVerifyTime.cpp CGVerifyTimeHandler.cpp
    CGVisible.cpp CGVisibleHandler.cpp
    CGWhisper.cpp CGWhisperHandler.cpp
    CGWithdrawPet.cpp CGWithdrawPetHandler.cpp
    CGWithdrawTax.cpp CGWithdrawTaxHandler.cpp
)

# CL Packets (Client -> Login)
set(CL_PACKET_SOURCES
    CLAgreement.cpp CLAgreementHandler.cpp
    CLChangeServer.cpp CLChangeServerHandler.cpp
    CLCreatePC.cpp CLCreatePCHandler.cpp
    CLDeletePC.cpp CLDeletePCHandler.cpp
    CLGetPCList.cpp CLGetPCListHandler.cpp
    CLGetServerList.cpp CLGetServerListHandler.cpp
    CLGetWorldList.cpp CLGetWorldListHandler.cpp
    CLLogin.cpp CLLoginHandler.cpp
    CLLogout.cpp CLLogoutHandler.cpp
    CLQueryCharacterName.cpp CLQueryCharacterNameHandler.cpp
    CLQueryPlayerID.cpp CLQueryPlayerIDHandler.cpp
    CLReconnectLogin.cpp CLReconnectLoginHandler.cpp
    CLRegisterPlayer.cpp CLRegisterPlayerHandler.cpp
    CLSelectPC.cpp CLSelectPCHandler.cpp
    CLSelectServer.cpp CLSelectServerHandler.cpp
    CLSelectWorld.cpp CLSelectWorldHandler.cpp
    CLVersionCheck.cpp CLVersionCheckHandler.cpp
)

# LC Packets (Login -> Client)
set(LC_PACKET_SOURCES
    LCCreatePCError.cpp LCCreatePCErrorHandler.cpp
    LCCreatePCOK.cpp LCCreatePCOKHandler.cpp
    LCDeletePCError.cpp LCDeletePCErrorHandler.cpp
    LCDeletePCOK.cpp LCDeletePCOKHandler.cpp
    LCLoginError.cpp LCLoginErrorHandler.cpp
    LCLoginOK.cpp LCLoginOKHandler.cpp
    LCPCList.cpp LCPCListHandler.cpp
    LCQueryResultCharacterName.cpp LCQueryResultCharacterNameHandler.cpp
    LCQueryResultPlayerID.cpp LCQueryResultPlayerIDHandler.cpp
    LCReconnect.cpp LCReconnectHandler.cpp
    LCRegisterPlayerError.cpp LCRegisterPlayerErrorHandler.cpp
    LCRegisterPlayerOK.cpp LCRegisterPlayerOKHandler.cpp
    LCSelectPCError.cpp LCSelectPCErrorHandler.cpp
    LCServerList.cpp LCServerListHandler.cpp
    LCVersionCheckError.cpp LCVersionCheckErrorHandler.cpp
    LCVersionCheckOK.cpp LCVersionCheckOKHandler.cpp
    LCWorldList.cpp LCWorldListHandler.cpp
)

# GL Packets (Game -> Login)
set(GL_PACKET_SOURCES
    GLIncomingConnection.cpp GLIncomingConnectionHandler.cpp
    GLIncomingConnectionError.cpp GLIncomingConnectionErrorHandler.cpp
    GLIncomingConnectionOK.cpp GLIncomingConnectionOKHandler.cpp
    GLKickVerify.cpp GLKickVerifyHandler.cpp
)

# LG Packets (Login -> Game)
set(LG_PACKET_SOURCES
    LGIncomingConnection.cpp LGIncomingConnectionHandler.cpp
    LGIncomingConnectionError.cpp LGIncomingConnectionErrorHandler.cpp
    LGIncomingConnectionOK.cpp LGIncomingConnectionOKHandler.cpp
    LGKickCharacter.cpp LGKickCharacterHandler.cpp
)

# GS Packets (Game -> Shared)
set(GS_PACKET_SOURCES
    GSAddGuild.cpp GSAddGuildHandler.cpp
    GSAddGuildMember.cpp GSAddGuildMemberHandler.cpp
    GSExpelGuildMember.cpp GSExpelGuildMemberHandler.cpp
    GSGuildMemberLogOn.cpp GSGuildMemberLogOnHandler.cpp
    GSModifyGuildIntro.cpp GSModifyGuildIntroHandler.cpp
    GSModifyGuildMember.cpp GSModifyGuildMemberHandler.cpp
    GSQuitGuild.cpp GSQuitGuildHandler.cpp
    GSRequestGuildInfo.cpp GSRequestGuildInfoHandler.cpp
)

# SG Packets (Shared -> Game)
set(SG_PACKET_SOURCES
    SGAddGuildMemberOK.cpp SGAddGuildMemberOKHandler.cpp
    SGAddGuildOK.cpp SGAddGuildOKHandler.cpp
    SGDeleteGuildOK.cpp SGDeleteGuildOKHandler.cpp
    SGExpelGuildMemberOK.cpp SGExpelGuildMemberOKHandler.cpp
    SGGuildInfo.cpp SGGuildInfoHandler.cpp
    SGGuildMemberLogOnOK.cpp SGGuildMemberLogOnOKHandler.cpp
    SGModifyGuildIntroOK.cpp SGModifyGuildIntroOKHandler.cpp
    SGModifyGuildMemberOK.cpp SGModifyGuildMemberOKHandler.cpp
    SGModifyGuildOK.cpp SGModifyGuildOKHandler.cpp
    SGQuitGuildOK.cpp SGQuitGuildOKHandler.cpp
)

# GG Packets (Game -> Game)
set(GG_PACKET_SOURCES
    GGCommand.cpp GGCommandHandler.cpp
    GGGuildChat.cpp GGGuildChatHandler.cpp
    GGServerChat.cpp GGServerChatHandler.cpp
)

# GM Packets
set(GM_PACKET_SOURCES
    GMServerInfo.cpp GMServerInfoHandler.cpp
)

# 通用 Packet 管理
set(PACKET_COMMON_SOURCES
    PacketFactoryManager.cpp
    PacketIDSet.cpp
    PacketValidator.cpp
)

# ============================================================================
# GameServerPackets 库 - 使用 __GAME_SERVER__ 宏编译
# ============================================================================
add_library(GameServerPackets STATIC
    ${GC_PACKET_SOURCES}
    ${CG_PACKET_SOURCES}
    ${GL_PACKET_SOURCES}
    ${LG_PACKET_SOURCES}
    ${GS_PACKET_SOURCES}
    ${SG_PACKET_SOURCES}
    ${GG_PACKET_SOURCES}
    ${GM_PACKET_SOURCES}
    ${PACKET_COMMON_SOURCES}
)
target_compile_definitions(GameServerPackets PRIVATE __GAME_SERVER__ __COMBAT__)
target_include_directories(GameServerPackets PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/gameserver
    ${CMAKE_SOURCE_DIR}/src/server/gameserver/item
    ${CMAKE_SOURCE_DIR}/src/server/gameserver/skill
    ${CMAKE_SOURCE_DIR}/src/server/gameserver/billing
)

# ============================================================================
# LoginServerPackets 库 - 使用 __LOGIN_SERVER__ 宏编译
# ============================================================================
add_library(LoginServerPackets STATIC
    ${CL_PACKET_SOURCES}
    ${LC_PACKET_SOURCES}
    ${GL_PACKET_SOURCES}
    ${LG_PACKET_SOURCES}
    ${GM_PACKET_SOURCES}
    ${PACKET_COMMON_SOURCES}
)
target_compile_definitions(LoginServerPackets PRIVATE __LOGIN_SERVER__)
target_include_directories(LoginServerPackets PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/loginserver
    ${CMAKE_SOURCE_DIR}/src/server/gameserver
)

# ============================================================================
# SharedServerPackets 库 - 使用 __SHARED_SERVER__ 宏编译
# ============================================================================
add_library(SharedServerPackets STATIC
    ${GS_PACKET_SOURCES}
    ${SG_PACKET_SOURCES}
    ${LG_PACKET_SOURCES}
    ${PACKET_COMMON_SOURCES}
)
target_compile_definitions(SharedServerPackets PRIVATE __SHARED_SERVER__)
target_include_directories(SharedServerPackets PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/server/database
    ${CMAKE_SOURCE_DIR}/src/server/sharedserver
    ${CMAKE_SOURCE_DIR}/src/server/gameserver
)
