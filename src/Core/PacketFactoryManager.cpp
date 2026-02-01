//--------------------------------------------------------------------------------
//
// Filename    : PacketFactoryManager.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "PacketFactoryManager.h"

#include "Assert.h"
#include "CGAddGearToMouse.h"
#include "CGAddInventoryToMouse.h"
#include "CGAddMouseToGear.h"
#include "CGAddMouseToInventory.h"
#include "CGAddMouseToQuickSlot.h"
#include "CGAddMouseToZone.h"
#include "CGAddQuickSlotToMouse.h"
#include "CGAddZoneToInventory.h"
#include "CGAddZoneToMouse.h"
#include "CGAttack.h"
#include "CGBloodDrain.h"
#include "CGCastingSkill.h"
#include "CGConnect.h"
#include "CGDissectionCorpse.h"
#include "CGDropMoney.h"
#include "CGGetOffMotorCycle.h"
#include "CGGlobalChat.h"
#include "CGLearnSkill.h"
#include "CGLogout.h"
#include "CGMakeItem.h"
#include "CGMove.h"
#include "CGNPCAskAnswer.h"
#include "CGNPCTalk.h"
#include "CGPickupMoney.h"
#include "CGReady.h"
#include "CGReloadFromInventory.h"
#include "CGReloadFromQuickSlot.h"
#include "CGRequestNewbieItem.h"
#include "CGRequestRepair.h"
#include "CGRideMotorCycle.h"
#include "CGSay.h"
#include "CGShopRequestBuy.h"
#include "CGShopRequestList.h"
#include "CGShopRequestSell.h"
#include "CGSkillToInventory.h"
#include "CGThrowBomb.h"
#include "CGThrowItem.h"
#include "CGTypeStringList.h"
#include "CGUnburrow.h"
#include "CGUntransform.h"
#include "CGUseBonusPoint.h"
#include "CGUseItemFromGear.h"
#include "CGUsePotionFromInventory.h"
#include "CGUsePotionFromQuickSlot.h"
#include "CGVerifyTime.h"
#include "CGVisible.h"
#include "CGWithdrawTax.h"
#include "CLChangeServer.h"
#include "CLCreatePC.h"
#include "CLDeletePC.h"
#include "CLGetPCList.h"
#include "CLGetServerList.h"
#include "CLGetWorldList.h"
#include "CLLogin.h"
#include "CLLogout.h"
#include "CLQueryCharacterName.h"
#include "CLQueryPlayerID.h"
#include "CLReconnectLogin.h"
#include "CLRegisterPlayer.h"
#include "CLSelectPC.h"
#include "CLSelectServer.h"
#include "CLSelectWorld.h"
#include "CLVersionCheck.h"
#include "GCAddBat.h"
#include "GCAddBurrowingCreature.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"
#include "GCAddGearToInventory.h"
#include "GCAddGearToZone.h"
#include "GCAddInjuriousCreature.h"
#include "GCAddInstalledMineToZone.h"
#include "GCAddMonster.h"
#include "GCAddMonsterCorpse.h"
#include "GCAddMonsterFromBurrowing.h"
#include "GCAddMonsterFromTransformation.h"
#include "GCAddNPC.h"
#include "GCAddNewItemToZone.h"
#include "GCAddSlayer.h"
#include "GCAddSlayerCorpse.h"
#include "GCAddVampire.h"
#include "GCAddVampireCorpse.h"
#include "GCAddVampireFromBurrowing.h"
#include "GCAddVampireFromTransformation.h"
#include "GCAddWolf.h"
#include "GCAttack.h"
#include "GCAttackArmsOK1.h"
#include "GCAttackArmsOK2.h"
#include "GCAttackArmsOK3.h"
#include "GCAttackArmsOK4.h"
#include "GCAttackArmsOK5.h"
#include "GCAttackMeleeOK1.h"
#include "GCAttackMeleeOK2.h"
#include "GCAttackMeleeOK3.h"
#include "GCBloodDrainOK1.h"
#include "GCBloodDrainOK2.h"
#include "GCBloodDrainOK3.h"
#include "GCCannotAdd.h"
#include "GCCannotUse.h"
#include "GCCastingSkill.h"
#include "GCChangeDarkLight.h"
#include "GCChangeShape.h"
#include "GCChangeWeather.h"
#include "GCCreateItem.h"
#include "GCCreatureDied.h"
#include "GCCrossCounterOK1.h"
#include "GCCrossCounterOK2.h"
#include "GCCrossCounterOK3.h"
#include "GCDeleteEffectFromTile.h"
#include "GCDeleteInventoryItem.h"
#include "GCDeleteObject.h"
#include "GCDeleteandPickUpOK.h"
#include "GCDisconnect.h"
#include "GCDropItemToZone.h"
#include "GCFakeMove.h"
#include "GCFastMove.h"
#include "GCGetDamage.h"
#include "GCGetOffMotorCycle.h"
#include "GCGetOffMotorCycleFailed.h"
#include "GCGetOffMotorCycleOK.h"
#include "GCGlobalChat.h"
#include "GCHPRecoveryEndToOthers.h"
#include "GCHPRecoveryEndToSelf.h"
#include "GCHPRecoveryStartToOthers.h"
#include "GCHPRecoveryStartToSelf.h"
#include "GCKnockBack.h"
#include "GCKnocksTargetBackOK1.h"
#include "GCKnocksTargetBackOK2.h"
#include "GCKnocksTargetBackOK4.h"
#include "GCKnocksTargetBackOK5.h"
#include "GCLearnSkillFailed.h"
#include "GCLearnSkillOK.h"
#include "GCLearnSkillReady.h"
#include "GCLightning.h"
#include "GCMPRecoveryEnd.h"
#include "GCMPRecoveryStart.h"
#include "GCMakeItemFail.h"
#include "GCMakeItemOK.h"
#include "GCMineExplosionOK1.h"
#include "GCMineExplosionOK2.h"
#include "GCModifyInformation.h"
#include "GCMorph1.h"
#include "GCMorphSlayer2.h"
#include "GCMorphVampire2.h"
#include "GCMove.h"
#include "GCMoveError.h"
#include "GCMoveOK.h"
#include "GCNPCAsk.h"
#include "GCNPCSay.h"
#include "GCRealWearingInfo.h"
#include "GCReconnect.h"
#include "GCReconnectLogin.h"
#include "GCReloadOK.h"
#include "GCRemoveCorpseHead.h"
#include "GCRemoveEffect.h"
#include "GCRemoveFromGear.h"
#include "GCRemoveInjuriousCreature.h"
#include "GCRideMotorCycle.h"
#include "GCRideMotorCycleFailed.h"
#include "GCRideMotorCycleOK.h"
#include "GCSay.h"
#include "GCSearchMotorcycleFail.h"
#include "GCSearchMotorcycleOK.h"
#include "GCSetPosition.h"
#include "GCThrowBombOK1.h"
#include "GCThrowBombOK2.h"
#include "GCThrowBombOK3.h"
#include "StringStream.h"
// Shop Interface
#include "GCNPCAskVariable.h"
#include "GCNPCInfo.h"
#include "GCShopBought.h"
#include "GCShopBuyFail.h"
#include "GCShopBuyOK.h"
#include "GCShopList.h"
#include "GCShopListMysterious.h"
#include "GCShopMarketCondition.h"
#include "GCShopSellFail.h"
#include "GCShopSellOK.h"
#include "GCShopSold.h"
#include "GCShopVersion.h"
#include "GCSkillFailed1.h"
#include "GCSkillFailed2.h"
#include "GCSkillToInventoryOK1.h"
#include "GCSkillToInventoryOK2.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK3.h"
#include "GCSkillToObjectOK4.h"
#include "GCSkillToObjectOK5.h"
#include "GCSkillToObjectOK6.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCSkillToSelfOK3.h"
#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToTileOK6.h"
#include "GCSystemMessage.h"
#include "GCTakeOff.h"
#include "GCTeachSkillInfo.h"
#include "GCThrowItemOK1.h"
#include "GCThrowItemOK2.h"
#include "GCThrowItemOK3.h"
#include "GCUnburrowFail.h"
#include "GCUnburrowOK.h"
#include "GCUntransformFail.h"
#include "GCUntransformOK.h"
#include "GCUpdateInfo.h"
#include "GCUseBonusPointFail.h"
#include "GCUseBonusPointOK.h"
#include "GCUseOK.h"
#include "GCVisibleFail.h"
#include "GCVisibleOK.h"
#include "GCWarList.h"
#include "GCWarScheduleList.h"

#if defined(__GAME_SERVER__) || defined(__LOGIN_SERVER__)
#include "GLIncomingConnection.h"
#include "GLIncomingConnectionError.h"
#include "GLIncomingConnectionOK.h"
#include "GLKickVerify.h"
#include "GMServerInfo.h"
#endif

#include "LCCreatePCError.h"
#include "LCCreatePCOK.h"
#include "LCDeletePCError.h"
#include "LCDeletePCOK.h"
#include "LCLoginError.h"
#include "LCLoginOK.h"
#include "LCPCList.h"
#include "LCQueryResultCharacterName.h"
#include "LCQueryResultPlayerID.h"
#include "LCReconnect.h"
#include "LCRegisterPlayerError.h"
#include "LCRegisterPlayerOK.h"
#include "LCSelectPCError.h"

#ifndef __GAME_CLIENT__
#include "LGIncomingConnection.h"
#include "LGIncomingConnectionError.h"
#include "LGIncomingConnectionOK.h"
#include "LGKickCharacter.h"
#endif

#include "LCServerList.h"
#include "LCVersionCheckError.h"
#include "LCVersionCheckOK.h"
#include "LCWorldList.h"

// added by elcastle 2000-11-29
// #include "CGDialUp.h"
// #include "CGPhoneDisconnect.h"
// #include "CGPhoneSay.h"
#include "CGWhisper.h"

// #include "GCPhoneConnected.h"
// #include "GCRing.h"
// #include "GCPhoneDisconnected.h"
// #include "GCPhoneConnectionFailed.h"
// #include "GCPhoneSay.h"
#include "GCWhisper.h"
#include "GCWhisperFailed.h"

// added by elca 2000-11-29
#include "GCSkillInfo.h"

// added by elca 2000-12-09
#include "GCStatusCurrentHP.h"

// added by elca 2000-12-09
#include "CGSetSlayerHotKey.h"
#include "CGSetVampireHotKey.h"


// added by elca 2001-06-26
#include "CGSelectPortal.h"

// 2001-01-08 stash feature
#include "CGMouseToStash.h"
#include "CGPartyInvite.h"
#include "CGPartyLeave.h"
#include "CGRequestIP.h"
#include "CGResurrect.h"
#include "CGSelectTileEffect.h"
#include "CGSelectWayPoint.h"
#include "CGSilverCoating.h"
#include "CGSkillToObject.h"
#include "CGSkillToSelf.h"
#include "CGSkillToTile.h"
#include "CGStashDeposit.h"
#include "CGStashList.h"
#include "CGStashRequestBuy.h"
#include "CGStashToMouse.h"
#include "CGStashWithdraw.h"
#include "CGTradeAddItem.h"
#include "CGTradeFinish.h"
#include "CGTradeMoney.h"
#include "CGTradePrepare.h"
#include "CGTradeRemoveItem.h"
#include "CGUseItemFromInventory.h"
#include "GCAddHelicopter.h"
#include "GCAddVampirePortal.h"
#include "GCEnterVampirePortal.h"
#include "GCNPCAskDynamic.h"
#include "GCNPCResponse.h"
#include "GCNPCSayDynamic.h"
#include "GCOtherModifyInfo.h"
#include "GCPartyError.h"
#include "GCPartyInvite.h"
#include "GCPartyJoined.h"
#include "GCPartyLeave.h"
#include "GCRequestFailed.h"
#include "GCRequestedIP.h"
#include "GCStashList.h"
#include "GCStashSell.h"
#include "GCTradeAddItem.h"
#include "GCTradeError.h"
#include "GCTradeFinish.h"
#include "GCTradeMoney.h"
#include "GCTradePrepare.h"
#include "GCTradeRemoveItem.h"
#include "GCTradeVerify.h"

#ifndef __GAME_CLIENT__
#include "GGCommand.h"
#endif


#ifdef __GAME_CLIENT__
#include "Rpackets/CRConnect.h"
#include "Rpackets/CRDisconnect.h"
#include "Rpackets/CRRequest.h"
#include "Rpackets/CRWhisper.h"
#include "Rpackets/RCCharacterInfo.h"
#include "Rpackets/RCConnectVerify.h"
#include "Rpackets/RCPositionInfo.h"
#include "Rpackets/RCRequestVerify.h"
#include "Rpackets/RCRequestedFile.h"
#include "Rpackets/RCSay.h"
#include "Rpackets/RCStatusHP.h"
#endif

// Guild feature update - 2002.05.31 (bezz)
// #include "GCShowGuildRegist.h"
#include "CGJoinGuild.h"
#include "CGRegistGuild.h"
#include "CGSelectGuild.h"
#include "CGTryJoinGuild.h"
#include "GCShowGuildInfo.h"
#include "GCShowGuildJoin.h"
#include "GCShowMessageBox.h"
#include "GCShowWaitGuildInfo.h"
#include "GCWaitGuildList.h"
// #include "GCModifyMoney.h"
// #include "CGQuitGuild.h"
#include "CGRequestGuildMemberList.h"
#include "CGSelectGuildMember.h"
// #include "CGExpelGuildMember.h"
#include "CGModifyGuildMember.h"
#include "GCActiveGuildList.h"
#include "GCGuildMemberList.h"
#include "GCModifyGuildMemberInfo.h"
#include "GCShowGuildMemberInfo.h"

#ifndef __GAME_CLIENT__
#include "GSAddGuild.h"
#include "GSAddGuildMember.h"
#include "GSExpelGuildMember.h"
#include "GSModifyGuildMember.h"
#include "GSQuitGuild.h"
#include "SGAddGuildMemberOK.h"
#include "SGAddGuildOK.h"
#include "SGDeleteGuildOK.h"
#include "SGExpelGuildMemberOK.h"
#include "SGModifyGuildMemberOK.h"
#include "SGModifyGuildOK.h"
#include "SGQuitGuildOK.h"
#endif

#include "CGGuildChat.h"
#include "CGPortCheck.h"
#include "CGRelicToObject.h"
#include "GCGuildChat.h"

#ifndef __GAME_CLIENT__
#include "GGGuildChat.h"
#include "GSRequestGuildInfo.h"
#include "SGGuildInfo.h"
#endif

#include "CGAddItemToItem.h"
#include "CGModifyGuildIntro.h"
#include "CGModifyGuildMemberIntro.h"
#include "CGRequestInfo.h"
#include "GCAddItemToItemVerify.h"
#include "GCNoticeEvent.h"

#ifndef __GAME_CLIENT__
#include "GSGuildMemberLogOn.h"
#include "GSModifyGuildIntro.h"
#include "SGGuildMemberLogOnOK.h"
#include "SGModifyGuildIntroOK.h"
#endif

#include "CGAbsorbSoul.h"
#include "CGAcceptUnion.h"
#include "CGAddItemToCodeSheet.h"
#include "CGAddSMSAddress.h"
#include "CGAppointSubmaster.h"
#include "CGAuthKey.h"
#include "CGBuyStoreItem.h"
#include "CGCrashReport.h"
#include "CGDeleteSMSAddress.h"
#include "CGDenyUnion.h"
#include "CGDepositPet.h"
#include "CGDisplayItem.h"
#include "CGDonationMoney.h"
#include "CGDownSkill.h"
#include "CGExpelGuild.h"

// Exchange System Packets
#include "CGExchangeList.h"
#include "CGExchangeBuy.h"
#include "GCExchangeList.h"
#include "GCExchangeBuy.h"
#include "CGFailQuest.h"
#include "CGGQuestAccept.h"
#include "CGGQuestCancel.h"
#include "CGGetEventItem.h"
#include "CGLotterySelect.h"
#include "CGMixItem.h"
#include "CGModifyNickname.h"
#include "CGModifyTaxRatio.h"
#include "CGPartyPosition.h"
#include "CGPartySay.h"
#include "CGPetGamble.h"
#include "CGQuitUnion.h"
#include "CGQuitUnionAccept.h"
#include "CGQuitUnionDeny.h"
#include "CGRangerSay.h"
#include "CGRequestGuildList.h"
#include "CGRequestPowerPoint.h"
#include "CGRequestStoreInfo.h"
#include "CGRequestUnion.h"
#include "CGRequestUnionInfo.h"
#include "CGSMSAddressList.h"
#include "CGSMSSend.h"
#include "CGSelectBloodBible.h"
#include "CGSelectNickname.h"
#include "CGSelectQuest.h"
#include "CGSelectRankBonus.h"
#include "CGSelectRegenZone.h"
#include "CGSkillToNamed.h"
#include "CGStoreClose.h"
#include "CGStoreOpen.h"
#include "CGStoreSign.h"
#include "CGSubmitScore.h"
#include "CGTakeOutGood.h"
#include "CGTameMonster.h"
#include "CGUndisplayItem.h"
#include "CGUseItemFromGQuestInventory.h"
#include "CGUseMessageItemFromInventory.h"
#include "CGUsePowerPoint.h"
#include "CGWithdrawPet.h"
#include "GCAddNickname.h"
#include "GCAddOusters.h"
#include "GCAddOustersCorpse.h"
#include "GCAddStoreItem.h"
#include "GCAddressListVerify.h"
#include "GCAuthKey.h"
#include "GCBloodBibleList.h"
#include "GCBloodBibleSignInfo.h"
#include "GCBloodBibleStatus.h"
#include "GCDownSkillFailed.h"
#include "GCDownSkillOK.h"
#include "GCExecuteElement.h"
#include "GCFlagWarStatus.h"
#include "GCGQuestInventory.h"
#include "GCGQuestStatusInfo.h"
#include "GCGQuestStatusModify.h"
#include "GCGoodsList.h"
#include "GCGuildResponse.h"
#include "GCHolyLandBonusInfo.h"
#include "GCKickMessage.h"
#include "GCMiniGameScores.h"
#include "GCModifyNickname.h"
#include "GCMonsterKillQuestInfo.h"
#include "GCMyStoreInfo.h"
#include "GCNicknameList.h"
#include "GCNicknameVerify.h"
#include "GCNotifyWin.h"
#include "GCOtherGuildName.h"
#include "GCOtherStoreInfo.h"
#include "GCPartyPosition.h"
#include "GCPartySay.h"
#include "GCPetInfo.h"
#include "GCPetStashList.h"
#include "GCPetStashVerify.h"
#include "GCPetUseSkill.h"
#include "GCQuestStatus.h"
#include "GCRankBonusInfo.h"
#include "GCRegenZoneStatus.h"
#include "GCRemoveStoreItem.h"
#include "GCRequestPowerPointResult.h"
#include "GCSMSAddressList.h"
#include "GCSelectQuestID.h"
#include "GCSelectRankBonusFailed.h"
#include "GCSelectRankBonusOK.h"
#include "GCSweeperBonusInfo.h"
#include "GCSystemAvailabilities.h"
#include "GCTakeOutFail.h"
#include "GCTakeOutOK.h"
#include "GCTimeLimitItemInfo.h"
#include "GCUnionOfferList.h"
#include "GCUsePowerPointResult.h"
#include "GGServerChat.h"
// add by viva 2008-12-31
#include "CGConnectSetKey.h"
#include "GCFriendChatting.h"
// end
#ifndef __GAME_CLIENT__
// #include "GSGuildAction.h"
// #include "SGGuildResponse.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
PacketFactoryManager::PacketFactoryManager() : m_Factories(NULL), m_Size(Packet::PACKET_MAX) {
    __BEGIN_TRY

    Assert(m_Size > 0);

    // Allocate the packet factory array.
    m_Factories = new PacketFactory*[m_Size];

    // Initialize every slot to NULL.
    for (int i = 0; i < m_Size; i++)
        m_Factories[i] = NULL;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
PacketFactoryManager::~PacketFactoryManager() noexcept {
    Assert(m_Factories != NULL);

    // Delete any instantiated packet factories.
    for (int i = 0; i < m_Size; i++) {
#ifdef __GAME_CLIENT__
        if (m_Factories[i] != NULL) {
            delete m_Factories[i];
            m_Factories[i] = NULL;
        }
#else
        SAFE_DELETE(m_Factories[i]);
#endif
    }

    // Release the packet factory array itself.
#ifdef __GAME_CLIENT__
    if (m_Factories != NULL) {
        delete[] m_Factories;
        m_Factories = NULL;
    }
#else
    SAFE_DELETE_ARRAY(m_Factories);
#endif
}


//////////////////////////////////////////////////////////////////////
//
// Register every supported packet factory here.
//
//////////////////////////////////////////////////////////////////////
void PacketFactoryManager::init() {
    __BEGIN_TRY

#if defined(__GAME_SERVER__)
    addFactory(new CGAttackFactory());
    addFactory(new CGAddGearToMouseFactory());
    addFactory(new CGAddInventoryToMouseFactory());
    addFactory(new CGAddMouseToGearFactory());
    addFactory(new CGAddMouseToInventoryFactory());
    addFactory(new CGAddMouseToQuickSlotFactory());
    addFactory(new CGAddMouseToZoneFactory());
    addFactory(new CGAddQuickSlotToMouseFactory());
    addFactory(new CGAddZoneToInventoryFactory());
    addFactory(new CGAddZoneToMouseFactory());
    addFactory(new CGBloodDrainFactory());
    addFactory(new CGCastingSkillFactory());
    addFactory(new CGConnectFactory());
    addFactory(new CGDissectionCorpseFactory());
    addFactory(new CGDropMoneyFactory());
    addFactory(new CGGetOffMotorCycleFactory());
    addFactory(new CGGlobalChatFactory());
    addFactory(new CGLearnSkillFactory());
    addFactory(new CGLogoutFactory());
    addFactory(new CGMakeItemFactory());
    addFactory(new CGMoveFactory());
    addFactory(new CGNPCAskAnswerFactory());
    addFactory(new CGNPCTalkFactory());
    addFactory(new CGPickupMoneyFactory());
    addFactory(new CGReadyFactory());
    addFactory(new CGReloadFromInventoryFactory());
    addFactory(new CGReloadFromQuickSlotFactory());
    addFactory(new CGRideMotorCycleFactory());
    addFactory(new CGSayFactory());
    addFactory(new CGSetSlayerHotKeyFactory());
    addFactory(new CGSetVampireHotKeyFactory());
    addFactory(new CGSelectPortalFactory());
    addFactory(new CGShopRequestBuyFactory());
    addFactory(new CGShopRequestListFactory());
    addFactory(new CGShopRequestSellFactory());
    addFactory(new CGSkillToInventoryFactory());
    addFactory(new CGThrowBombFactory());
    addFactory(new CGThrowItemFactory());
    addFactory(new CGUnburrowFactory());
    addFactory(new CGUntransformFactory());
    addFactory(new CGUseBonusPointFactory());
    addFactory(new CGUsePotionFromInventoryFactory());
    addFactory(new CGUsePotionFromQuickSlotFactory());
    addFactory(new CGRequestRepairFactory());
    addFactory(new CGVisibleFactory());
    addFactory(new CGVerifyTimeFactory());
#endif

#if defined(__LOGIN_SERVER__)
    addFactory(new CLCreatePCFactory());
    addFactory(new CLDeletePCFactory());
    addFactory(new CLGetPCListFactory());
    addFactory(new CLLoginFactory());
    addFactory(new CLLogoutFactory());
    addFactory(new CLQueryPlayerIDFactory());
    addFactory(new CLQueryCharacterNameFactory());
    addFactory(new CLRegisterPlayerFactory);
    addFactory(new CLSelectPCFactory());
    addFactory(new CLVersionCheckFactory());
    addFactory(new CLGetServerListFactory());
    addFactory(new CLGetWorldListFactory());
    addFactory(new CLChangeServerFactory());
    addFactory(new CLReconnectLoginFactory());
    addFactory(new CLSelectWorldFactory());
    addFactory(new CLSelectServerFactory());
    // By tiancaiamao: This one is required by the LoginServer to handle Encryption.
    // If client use encryption, it send this packet and pass the encryption key.
    // After that, the communication is encrypted using that key.
    addFactory(new CGConnectSetKeyFactory());
#endif

#if defined(__GAME_SERVER__)
    // 2002.6.28
    addFactory(new CGPortCheckFactory());

    // added by elcastle 2000-11-29
    /*
    addFactory(new CGDialUpFactory());
    addFactory(new CGPhoneDisconnectFactory());
    addFactory(new CGPhoneSayFactory());
    */
    addFactory(new CGWhisperFactory());

    addFactory(new CGMouseToStashFactory());
    addFactory(new CGStashToMouseFactory());
    addFactory(new CGStashListFactory());
    addFactory(new CGStashDepositFactory());
    addFactory(new CGStashWithdrawFactory());

    addFactory(new CGStashRequestBuyFactory());

    addFactory(new CGTradePrepareFactory());
    addFactory(new CGTradeAddItemFactory());
    addFactory(new CGTradeRemoveItemFactory());
    addFactory(new CGTradeMoneyFactory());
    addFactory(new CGTradeFinishFactory());

    addFactory(new CGSkillToObjectFactory());
    addFactory(new CGSkillToSelfFactory());
    addFactory(new CGSkillToTileFactory());

    addFactory(new CGSilverCoatingFactory());
    addFactory(new CGRequestNewbieItemFactory());
    addFactory(new CGUseItemFromInventoryFactory());
    addFactory(new CGSelectWayPointFactory());
    addFactory(new CGSelectTileEffectFactory());

    addFactory(new CGPartyInviteFactory());
    addFactory(new CGPartyLeaveFactory());

    addFactory(new CGResurrectFactory());

    addFactory(new CGRequestIPFactory());

    // Relic system
    addFactory(new CGRelicToObjectFactory());

    addFactory(new CGRegistGuildFactory());
    addFactory(new CGSelectGuildFactory());
    addFactory(new CGTryJoinGuildFactory());
    addFactory(new CGJoinGuildFactory());
    //	addFactory( new CGQuitGuildFactory() );
    addFactory(new CGRequestGuildMemberListFactory());
    addFactory(new CGSelectGuildMemberFactory());
    //	addFactory( new CGExpelGuildMemberFactory() );
    addFactory(new CGModifyGuildMemberFactory());
    addFactory(new CGGuildChatFactory());

    // Inventory item-to-item merge: source item -> destination item
    addFactory(new CGAddItemToItemFactory());

    // Information request packet - 2002.9.2
    addFactory(new CGRequestInfoFactory());

    addFactory(new CGModifyGuildIntroFactory());
    addFactory(new CGModifyGuildMemberIntroFactory());

    addFactory(new CGUseMessageItemFromInventoryFactory());

    // 2003. 1. 21
    addFactory(new CGWithdrawTaxFactory());

    addFactory(new CGTypeStringListFactory());

    addFactory(new CGUseItemFromGearFactory());

    addFactory(new CGSkillToNamedFactory());

    addFactory(new CGSelectRankBonusFactory());
    addFactory(new CGSelectQuestFactory());
    addFactory(new CGLotterySelectFactory());
    addFactory(new CGTakeOutGoodFactory());
    addFactory(new CGMixItemFactory());
    addFactory(new CGAbsorbSoulFactory());
    addFactory(new CGDownSkillFactory());
    addFactory(new CGSubmitScoreFactory());
    addFactory(new CGFailQuestFactory());
    addFactory(new CGAddItemToCodeSheetFactory());
    addFactory(new CGSelectRegenZoneFactory());
    addFactory(new CGTameMonsterFactory());
    addFactory(new CGPetGambleFactory());
    addFactory(new CGCrashReportFactory());


    addFactory(new GCAddBatFactory());
    addFactory(new GCAddBurrowingCreatureFactory());
    addFactory(new GCAddEffectFactory());
    addFactory(new GCAddEffectToTileFactory());
    addFactory(new GCAddGearToInventoryFactory());
    addFactory(new GCAddGearToZoneFactory());
    addFactory(new GCAddInstalledMineToZoneFactory());
    addFactory(new GCAddMonsterFactory());
    addFactory(new GCAddMonsterCorpseFactory());
    addFactory(new GCAddMonsterFromBurrowingFactory());
    addFactory(new GCAddMonsterFromTransformationFactory());
    addFactory(new GCAddNewItemToZoneFactory());
    addFactory(new GCAddNPCFactory());
    addFactory(new GCAddSlayerFactory());
    addFactory(new GCAddSlayerCorpseFactory());
    addFactory(new GCAddVampireFactory());
    addFactory(new GCAddVampireCorpseFactory());
    addFactory(new GCAddVampireFromBurrowingFactory());
    addFactory(new GCAddVampireFromTransformationFactory());
    addFactory(new GCAddWolfFactory());
    addFactory(new GCAttackFactory());
    addFactory(new GCAttackArmsOK1Factory());
    addFactory(new GCAttackArmsOK2Factory());
    addFactory(new GCAttackArmsOK3Factory());
    addFactory(new GCAttackArmsOK4Factory());
    addFactory(new GCAttackArmsOK5Factory());
    addFactory(new GCAttackMeleeOK1Factory());
    addFactory(new GCAttackMeleeOK2Factory());
    addFactory(new GCAttackMeleeOK3Factory());
    addFactory(new GCBloodDrainOK1Factory());
    addFactory(new GCBloodDrainOK2Factory());
    addFactory(new GCBloodDrainOK3Factory());
    addFactory(new GCCastingSkillFactory());
    addFactory(new GCCannotAddFactory());
    addFactory(new GCCannotUseFactory());
    addFactory(new GCChangeShapeFactory());
    addFactory(new GCChangeDarkLightFactory());
    addFactory(new GCChangeWeatherFactory());
    addFactory(new GCCreateItemFactory());
    addFactory(new GCCreatureDiedFactory());
    addFactory(new GCCrossCounterOK1Factory());
    addFactory(new GCCrossCounterOK2Factory());
    addFactory(new GCCrossCounterOK3Factory());
    addFactory(new GCDeleteandPickUpOKFactory());
    addFactory(new GCDeleteInventoryItemFactory());
    addFactory(new GCDeleteObjectFactory());
    addFactory(new GCRemoveCorpseHeadFactory());
    addFactory(new GCRemoveInjuriousCreatureFactory());
    addFactory(new GCDeleteEffectFromTileFactory());
    addFactory(new GCDisconnectFactory());
    addFactory(new GCDropItemToZoneFactory());
    addFactory(new GCFastMoveFactory());
    addFactory(new GCFakeMoveFactory());
    addFactory(new GCGetDamageFactory());
    addFactory(new GCGetOffMotorCycleFactory());
    addFactory(new GCGetOffMotorCycleOKFactory());
    addFactory(new GCGetOffMotorCycleFailedFactory());
    addFactory(new GCGlobalChatFactory());
    addFactory(new GCHPRecoveryStartToSelfFactory());
    addFactory(new GCHPRecoveryStartToOthersFactory());
    addFactory(new GCHPRecoveryEndToSelfFactory());
    addFactory(new GCHPRecoveryEndToOthersFactory());
    addFactory(new GCLightningFactory());
    addFactory(new GCLearnSkillFailedFactory());
    addFactory(new GCLearnSkillOKFactory());
    addFactory(new GCLearnSkillReadyFactory());
    addFactory(new GCKnockBackFactory());
    addFactory(new GCKnocksTargetBackOK1Factory());
    addFactory(new GCKnocksTargetBackOK2Factory());
    addFactory(new GCKnocksTargetBackOK4Factory());
    addFactory(new GCKnocksTargetBackOK5Factory());
    addFactory(new GCMakeItemOKFactory());
    addFactory(new GCMakeItemFailFactory());
    addFactory(new GCMineExplosionOK1Factory());
    addFactory(new GCMineExplosionOK2Factory());
    addFactory(new GCModifyInformationFactory());
    addFactory(new GCMorph1Factory());
    addFactory(new GCMorphSlayer2Factory());
    addFactory(new GCMorphVampire2Factory());
    addFactory(new GCMoveFactory());
    addFactory(new GCMoveErrorFactory());
    addFactory(new GCMoveOKFactory());
    addFactory(new GCMPRecoveryStartFactory());
    addFactory(new GCMPRecoveryEndFactory());
    addFactory(new GCNPCAskFactory());
    addFactory(new GCNPCSayFactory());
    addFactory(new GCRealWearingInfoFactory());
    addFactory(new GCReconnectFactory());
    addFactory(new GCReconnectLoginFactory());
    addFactory(new GCRemoveEffectFactory());
    addFactory(new GCRemoveFromGearFactory());
    addFactory(new GCRideMotorCycleFactory());
    addFactory(new GCRideMotorCycleOKFactory());
    addFactory(new GCRideMotorCycleFailedFactory());
    addFactory(new GCReloadOKFactory());
    addFactory(new GCUnburrowOKFactory());
    addFactory(new GCUnburrowFailFactory());
    addFactory(new GCUntransformOKFactory());
    addFactory(new GCUntransformFailFactory());
    addFactory(new GCUseBonusPointFailFactory());
    addFactory(new GCUseBonusPointOKFactory());
    addFactory(new GCSayFactory());
    addFactory(new GCSearchMotorcycleOKFactory());
    addFactory(new GCSearchMotorcycleFailFactory());
    addFactory(new GCSetPositionFactory());
    // shop interface
    addFactory(new GCShopVersionFactory());
    addFactory(new GCShopListFactory());
    addFactory(new GCShopListMysteriousFactory());
    addFactory(new GCShopBuyOKFactory());
    addFactory(new GCShopBuyFailFactory());
    addFactory(new GCShopSoldFactory());
    addFactory(new GCShopSellFailFactory());
    addFactory(new GCShopSellOKFactory());
    addFactory(new GCShopBoughtFactory());
    addFactory(new GCShopMarketConditionFactory());

    addFactory(new GCSkillFailed1Factory());
    addFactory(new GCSkillFailed2Factory());
    addFactory(new GCSkillToInventoryOK1Factory());
    addFactory(new GCSkillToInventoryOK2Factory());
    addFactory(new GCSkillToObjectOK1Factory());
    addFactory(new GCSkillToObjectOK2Factory());
    addFactory(new GCSkillToObjectOK3Factory());
    addFactory(new GCSkillToObjectOK4Factory());
    addFactory(new GCSkillToObjectOK5Factory());
    addFactory(new GCSkillToObjectOK6Factory());
    addFactory(new GCSkillToSelfOK1Factory());
    addFactory(new GCSkillToSelfOK2Factory());
    addFactory(new GCSkillToSelfOK3Factory());
    addFactory(new GCSkillToTileOK1Factory());
    addFactory(new GCSkillToTileOK2Factory());
    addFactory(new GCSkillToTileOK3Factory());
    addFactory(new GCSkillToTileOK4Factory());
    addFactory(new GCSkillToTileOK5Factory());
    addFactory(new GCSkillToTileOK6Factory());
    addFactory(new GCSystemMessageFactory());
    addFactory(new GCTakeOffFactory());
    addFactory(new GCTeachSkillInfoFactory());
    addFactory(new GCThrowItemOK1Factory());
    addFactory(new GCThrowItemOK2Factory());
    addFactory(new GCThrowItemOK3Factory());
    addFactory(new GCUpdateInfoFactory());
    addFactory(new GCUseOKFactory());

    // Add by elcastle 2000-11-29
    //	addFactory(new GCPhoneConnectedFactory());
    //	addFactory(new GCRingFactory());
    //	addFactory(new GCPhoneDisconnectedFactory());
    //	addFactory(new GCPhoneConnectionFailedFactory());
    //	addFactory(new GCPhoneSayFactory());
    addFactory(new GCWhisperFactory());
    addFactory(new GCWhisperFailedFactory());

    // Add by elcastle 2000-12-2
    addFactory(new GCSkillInfoFactory());

    // Add by elcastle 2000-12-9
    addFactory(new GCStatusCurrentHPFactory());

    addFactory(new GCStashListFactory());
    addFactory(new GCStashSellFactory());

    addFactory(new GCTradePrepareFactory());
    addFactory(new GCTradeAddItemFactory());
    addFactory(new GCTradeRemoveItemFactory());
    addFactory(new GCTradeMoneyFactory());
    addFactory(new GCTradeFinishFactory());
    addFactory(new GCTradeErrorFactory());
    addFactory(new GCTradeVerifyFactory());
    addFactory(new GCVisibleOKFactory());
    addFactory(new GCVisibleFailFactory());

    addFactory(new GCNPCResponseFactory());

    addFactory(new GCNPCSayDynamicFactory());
    addFactory(new GCNPCAskDynamicFactory());

    addFactory(new GCAddHelicopterFactory());
    addFactory(new GCAddVampirePortalFactory());
    addFactory(new GCAddInjuriousCreatureFactory());
    addFactory(new GCEnterVampirePortalFactory());

    addFactory(new GCPartyInviteFactory());
    addFactory(new GCPartyLeaveFactory());
    addFactory(new GCPartyJoinedFactory());
    addFactory(new GCPartyErrorFactory());

    addFactory(new GCRequestedIPFactory());
    addFactory(new GCRequestFailedFactory());

    addFactory(new GCOtherModifyInfoFactory());
    addFactory(new GCThrowBombOK1Factory());
    addFactory(new GCThrowBombOK2Factory());
    addFactory(new GCThrowBombOK3Factory());

    //	addFactory( new GCShowGuildRegistFactory() );
    addFactory(new GCWaitGuildListFactory());
    addFactory(new GCShowGuildInfoFactory());
    addFactory(new GCShowGuildJoinFactory());
    addFactory(new GCShowMessageBoxFactory());
    //	addFactory( new GCModifyMoneyFactory() );
    addFactory(new GCShowWaitGuildInfoFactory());
    addFactory(new GCActiveGuildListFactory());

    addFactory(new GCShowGuildMemberInfoFactory());
    addFactory(new GCGuildChatFactory());
    addFactory(new GCGuildMemberListFactory());
    addFactory(new GCModifyGuildMemberInfoFactory());
    addFactory(new GCAddItemToItemVerifyFactory());

    // 2002.9.2
    addFactory(new GCNoticeEventFactory());

    addFactory(new GCSelectRankBonusOKFactory());
    addFactory(new GCSelectRankBonusFailedFactory());
    addFactory(new GCRankBonusInfoFactory());

    addFactory(new GCNPCInfoFactory());
    addFactory(new GCNPCAskVariableFactory());
    addFactory(new GCWarScheduleListFactory());
    addFactory(new GCWarListFactory());

    addFactory(new GCHolyLandBonusInfoFactory());
    addFactory(new GCBloodBibleStatusFactory());
    addFactory(new GCKickMessageFactory());
    addFactory(new GCTimeLimitItemInfoFactory());
    addFactory(new GCSelectQuestIDFactory());
    addFactory(new GCQuestStatusFactory());
    addFactory(new GCMonsterKillQuestInfoFactory());
    addFactory(new GCNotifyWinFactory());
    addFactory(new GCGoodsListFactory());
    addFactory(new GCTakeOutOKFactory());
    addFactory(new GCTakeOutFailFactory());
    addFactory(new GCAddOustersFactory());
    addFactory(new GCAddOustersCorpseFactory());
    addFactory(new GCDownSkillOKFactory());
    addFactory(new GCDownSkillFailedFactory());

    addFactory(new GCMiniGameScoresFactory());
    addFactory(new GCFlagWarStatusFactory());
    addFactory(new GCOtherGuildNameFactory());
    addFactory(new GCSweeperBonusInfoFactory());
    addFactory(new GCRegenZoneStatusFactory());
    addFactory(new GCPetInfoFactory());
    addFactory(new GCPetUseSkillFactory());
    addFactory(new GCSystemAvailabilitiesFactory());

    addFactory(new GCPartyPositionFactory());
    addFactory(new CGPartyPositionFactory());
    addFactory(new CGPartySayFactory());
    addFactory(new GCPartySayFactory());

    addFactory(new GGServerChatFactory());

    addFactory(new GCPetStashListFactory());
    addFactory(new CGWithdrawPetFactory());
    addFactory(new CGDepositPetFactory());
    addFactory(new GCPetStashVerifyFactory());

    addFactory(new CGSMSSendFactory());

    addFactory(new CGAddSMSAddressFactory());
    addFactory(new CGDeleteSMSAddressFactory());
    addFactory(new CGSMSAddressListFactory());
    addFactory(new GCSMSAddressListFactory());
    addFactory(new GCAddressListVerifyFactory());

    addFactory(new GCNicknameListFactory());
    addFactory(new GCAddNicknameFactory());
    addFactory(new CGModifyNicknameFactory());
    addFactory(new CGSelectNicknameFactory());
    addFactory(new GCNicknameVerifyFactory());
    addFactory(new GCModifyNicknameFactory());

    addFactory(new GCGQuestStatusInfoFactory());
    addFactory(new GCGQuestStatusModifyFactory());
    addFactory(new CGGQuestAcceptFactory());
    addFactory(new CGGQuestCancelFactory());
    addFactory(new GCExecuteElementFactory());
    addFactory(new GCGQuestInventoryFactory());

    addFactory(new GCAuthKeyFactory());
    addFactory(new CGAuthKeyFactory());
    addFactory(new CGUseItemFromGQuestInventoryFactory());

    addFactory(new GCGuildResponseFactory());
    addFactory(new CGRequestGuildListFactory());
    addFactory(new CGAppointSubmasterFactory());
    addFactory(new CGRequestUnionFactory());
    addFactory(new CGAcceptUnionFactory());
    addFactory(new CGDenyUnionFactory());
    addFactory(new CGRequestUnionInfoFactory());
    addFactory(new CGExpelGuildFactory());
    addFactory(new CGQuitUnionFactory());
    addFactory(new CGQuitUnionAcceptFactory());
    addFactory(new CGQuitUnionDenyFactory());
    addFactory(new GCUnionOfferListFactory());

    addFactory(new GCBloodBibleListFactory());
    addFactory(new CGSelectBloodBibleFactory());
    addFactory(new GCBloodBibleSignInfoFactory());
    addFactory(new CGRangerSayFactory());
    addFactory(new CGModifyTaxRatioFactory());

    addFactory(new CGDisplayItemFactory());
    addFactory(new CGUndisplayItemFactory());
    addFactory(new CGStoreSignFactory());
    addFactory(new CGStoreOpenFactory());
    addFactory(new CGStoreCloseFactory());
    addFactory(new CGRequestStoreInfoFactory());
    addFactory(new CGBuyStoreItemFactory());
    addFactory(new GCMyStoreInfoFactory());
    addFactory(new GCOtherStoreInfoFactory());
    addFactory(new GCRemoveStoreItemFactory());
    addFactory(new GCAddStoreItemFactory());
    addFactory(new CGRequestPowerPointFactory());
    addFactory(new GCRequestPowerPointResultFactory());
    addFactory(new CGUsePowerPointFactory());
    addFactory(new GCUsePowerPointResultFactory());
    addFactory(new CGDonationMoneyFactory());
    addFactory(new CGGetEventItemFactory());


    // add by viva 2008-12-31
    addFactory(new CGConnectSetKeyFactory());
    addFactory(new GCFriendChattingFactory());
    // addFactory( new GCUseSkillCardOKFactory() );
    // end

#endif


#ifdef __LOGIN_SERVER__
    addFactory(new LCCreatePCErrorFactory());
    addFactory(new LCCreatePCOKFactory());
    addFactory(new LCDeletePCErrorFactory());
    addFactory(new LCDeletePCOKFactory());
    addFactory(new LCLoginErrorFactory());
    addFactory(new LCLoginOKFactory());
    addFactory(new LCPCListFactory());
    addFactory(new LCQueryResultPlayerIDFactory());
    addFactory(new LCQueryResultCharacterNameFactory());
    addFactory(new LCReconnectFactory());
    addFactory(new LCRegisterPlayerErrorFactory());
    addFactory(new LCRegisterPlayerOKFactory());
    addFactory(new LCSelectPCErrorFactory());
    addFactory(new LCVersionCheckOKFactory());
    addFactory(new LCVersionCheckErrorFactory());
    addFactory(new LCServerListFactory());
    addFactory(new LCWorldListFactory());
#endif

#if defined(__GAME_SERVER__) || defined(__LOGIN_SERVER__)
    addFactory(new LGIncomingConnectionFactory());
    addFactory(new LGIncomingConnectionOKFactory());
    addFactory(new LGIncomingConnectionErrorFactory());
    addFactory(new LGKickCharacterFactory());

    addFactory(new GGCommandFactory());
    addFactory(new GMServerInfoFactory());
    addFactory(new GLIncomingConnectionFactory());
    addFactory(new GLIncomingConnectionErrorFactory());
    addFactory(new GLIncomingConnectionOKFactory());
    addFactory(new GLKickVerifyFactory());
#endif

#ifdef __GAME_CLIENT__
    addFactory(new CRConnectFactory());
    addFactory(new RCConnectVerifyFactory());
    addFactory(new CRRequestFactory());
    addFactory(new RCPositionInfoFactory());
    addFactory(new CRDisconnectFactory());
    addFactory(new RCSayFactory());
    addFactory(new RCStatusHPFactory());
    addFactory(new CRWhisperFactory());
    addFactory(new RCRequestVerifyFactory());
    addFactory(new RCRequestedFileFactory());
    addFactory(new RCCharacterInfoFactory());
#endif

#if defined(__GAME_SERVER__) || defined(__SHARED_SERVER__)
    addFactory(new SGQuitGuildOKFactory());
    addFactory(new SGExpelGuildMemberOKFactory());
    addFactory(new SGModifyGuildMemberOKFactory());
    addFactory(new SGDeleteGuildOKFactory());
    addFactory(new SGModifyGuildOKFactory());
    addFactory(new GSExpelGuildMemberFactory());
    addFactory(new GSModifyGuildMemberFactory());
    addFactory(new SGAddGuildMemberOKFactory());
    addFactory(new SGAddGuildOKFactory());
    addFactory(new GSAddGuildFactory());
    addFactory(new GSAddGuildMemberFactory());
    addFactory(new GSQuitGuildFactory());

    addFactory(new GGGuildChatFactory());
    addFactory(new GSRequestGuildInfoFactory());
    addFactory(new SGGuildInfoFactory());

    addFactory(new GSModifyGuildIntroFactory());
    addFactory(new SGModifyGuildIntroOKFactory());

    addFactory(new GSGuildMemberLogOnFactory());
    addFactory(new SGGuildMemberLogOnOKFactory());
#endif

    // Exchange System Packets
#if defined(__GAME_SERVER__)
    addFactory(new CGExchangeListFactory());
    addFactory(new CGExchangeBuyFactory());
#endif


#if __OUTPUT_INIT__
    cout << toString() << endl;
#endif

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// Insert the factory into its slot using the packet ID as the index.
//
//////////////////////////////////////////////////////////////////////
void PacketFactoryManager::addFactory(PacketFactory* pFactory) {
    __BEGIN_TRY

    if (m_Factories[pFactory->getPacketID()] != NULL) {
        StringStream msg;
#ifdef __GAME_CLIENT__
#ifdef __DEBUG_OUTPUT__
        msg << "duplicate packet factories, " << pFactory->getPacketName();
#else
        msg << "duplicate packet factories ";
#endif
#else
        msg << "duplicate packet factories, " << pFactory->getPacketName();
#endif
        throw Error(msg.toString());
    }

    // Store the factory in the lookup table.
    m_Factories[pFactory->getPacketID()] = pFactory;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// Create a packet instance for the given packet ID.
//
//////////////////////////////////////////////////////////////////////
Packet* PacketFactoryManager::createPacket(PacketID_t packetID) {
    __BEGIN_TRY

    // Guard against invalid IDs to avoid accessing an empty slot and crashing.
    if (packetID >= m_Size || m_Factories[packetID] == NULL) {
        StringStream msg;
        msg << "packet factory [" << packetID << "] not exist.";
        throw InvalidProtocolException(msg.toString());
    }

    return m_Factories[packetID]->createPacket();

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// Return the max packet size for the given packet ID.
//
//////////////////////////////////////////////////////////////////////
PacketSize_t PacketFactoryManager::getPacketMaxSize(PacketID_t packetID) {
    __BEGIN_TRY

    // Guard against invalid IDs to avoid accessing an empty slot and crashing.
    if (packetID >= m_Size || m_Factories[packetID] == NULL) {
        StringStream msg;
        msg << "invalid packet id(" << packetID << ")";
        throw InvalidProtocolException(msg.toString());
    }

    return m_Factories[packetID]->getPacketMaxSize();

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// Return the packet name for the given packet ID.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__GAME_CLIENT__) || defined(__GAME_CLIENT__) && defined(__DEBUG_OUTPUT__)
string PacketFactoryManager::getPacketName(PacketID_t packetID) {
    __BEGIN_TRY

    // Guard against invalid IDs to avoid accessing an empty slot and crashing.
    if (packetID >= m_Size || m_Factories[packetID] == NULL) {
        StringStream msg;
        msg << "invalid packet id(" << packetID << ")";
        throw InvalidProtocolException(msg.toString());
    }

    return m_Factories[packetID]->getPacketName();

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string PacketFactoryManager::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "PacketFactoryManager(\n";

    for (int i = 0; i < m_Size; i++)
        msg << "PacketFactories[" << i << "] == " << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getPacketName())
            << "\n";

    msg << ")";

    return msg.toString();

    __END_CATCH
}
#endif

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////

PacketFactoryManager* g_pPacketFactoryManager = NULL;
