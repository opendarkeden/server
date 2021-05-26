//--------------------------------------------------------------------------------
// 
// Filename    : PacketFactoryManager.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "Assert.h"
#include "PacketFactoryManager.h"
#include "StringStream.h"

#include "Cpackets/CGAttack.h"
#include "Cpackets/CGAddGearToMouse.h"
#include "Cpackets/CGAddInventoryToMouse.h"
#include "Cpackets/CGAddMouseToGear.h"
#include "Cpackets/CGAddMouseToInventory.h"
#include "Cpackets/CGAddMouseToQuickSlot.h"
#include "Cpackets/CGAddMouseToZone.h"
#include "Cpackets/CGAddQuickSlotToMouse.h"
#include "Cpackets/CGAddZoneToMouse.h"
#include "Cpackets/CGAddZoneToInventory.h"
#include "Cpackets/CGBloodDrain.h"
#include "Cpackets/CGUnburrow.h"
#include "Cpackets/CGUntransform.h"
#include "Cpackets/CGCastingSkill.h"
#include "Cpackets/CGConnect.h"
#include "Cpackets/CGDissectionCorpse.h"
#include "Cpackets/CGDropMoney.h"
#include "Cpackets/CGGetOffMotorCycle.h"
#include "Cpackets/CGGlobalChat.h"
#include "Cpackets/CGLearnSkill.h"
#include "Cpackets/CGLogout.h"
#include "Cpackets/CGMakeItem.h"
#include "Cpackets/CGMove.h"
#include "Cpackets/CGNPCAskAnswer.h"
#include "Cpackets/CGNPCTalk.h"
#include "Cpackets/CGPickupMoney.h"
#include "Cpackets/CGReady.h"
#include "Cpackets/CGReloadFromInventory.h"
#include "Cpackets/CGReloadFromQuickSlot.h"
#include "Cpackets/CGRideMotorCycle.h"
#include "Cpackets/CGSay.h"
#include "Cpackets/CGShopRequestBuy.h"
#include "Cpackets/CGShopRequestList.h"
#include "Cpackets/CGShopRequestSell.h"
#include "Cpackets/CGSkillToInventory.h"
#include "Cpackets/CGThrowBomb.h"
#include "Gpackets/GCThrowBombOK1.h"
#include "Gpackets/GCThrowBombOK2.h"
#include "Gpackets/GCThrowBombOK3.h"
#include "Cpackets/CGThrowItem.h"
#include "Cpackets/CGUseBonusPoint.h"
#include "Cpackets/CGUsePotionFromInventory.h"
#include "Cpackets/CGUsePotionFromQuickSlot.h"
#include "Cpackets/CGRequestRepair.h"
#include "Cpackets/CGVisible.h"
#include "Cpackets/CGVerifyTime.h"
#include "Cpackets/CGRequestNewbieItem.h"
#include "Cpackets/CGWithdrawTax.h"
#include "Cpackets/CGTypeStringList.h"
#include "Cpackets/CGUseItemFromGear.h"

#include "Cpackets/CLCreatePC.h"
#include "Cpackets/CLDeletePC.h"
#include "Cpackets/CLGetPCList.h"
#include "Cpackets/CLLogin.h"
#include "Cpackets/CLLogout.h"
#include "Cpackets/CLQueryPlayerID.h"
#include "Cpackets/CLQueryCharacterName.h"
#include "Cpackets/CLRegisterPlayer.h"
#include "Cpackets/CLSelectPC.h"
#include "Cpackets/CLVersionCheck.h"
#include "Cpackets/CLGetServerList.h"
#include "Cpackets/CLChangeServer.h"
#include "Cpackets/CLReconnectLogin.h"
#include "Cpackets/CLGetWorldList.h"
#include "Cpackets/CLSelectWorld.h"
#include "Cpackets/CLSelectServer.h"


#include "GCAddBat.h"
#include "GCAddBurrowingCreature.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"
#include "GCAddGearToInventory.h"
#include "GCAddGearToZone.h"
#include "GCAddInstalledMineToZone.h"
#include "GCAddMonster.h"
#include "GCAddMonsterCorpse.h"
#include "GCAddMonsterFromBurrowing.h"
#include "GCAddMonsterFromTransformation.h"
#include "GCAddNewItemToZone.h"
#include "GCAddNPC.h"
#include "GCAddSlayer.h"
#include "GCAddSlayerCorpse.h"
#include "GCAddVampire.h"
#include "GCAddVampireCorpse.h"
#include "GCAddVampireFromBurrowing.h"
#include "GCAddVampireFromTransformation.h"
#include "GCAddWolf.h"
#include "GCAddInjuriousCreature.h"
#include "GCAttackArmsOK1.h"
#include "GCAttackArmsOK2.h"
#include "GCAttackArmsOK3.h"
#include "GCAttackArmsOK4.h"
#include "GCAttackArmsOK5.h"
#include "GCAttackMeleeOK1.h"
#include "GCAttackMeleeOK2.h"
#include "GCAttackMeleeOK3.h"
#include "GCAttack.h"
#include "GCBloodDrainOK1.h"
#include "GCBloodDrainOK2.h"
#include "GCBloodDrainOK3.h"
#include "GCCannotAdd.h"
#include "GCCannotUse.h"
#include "GCCastingSkill.h"
#include "GCCreateItem.h"
#include "GCCreatureDied.h"
#include "GCChangeShape.h"
#include "GCChangeDarkLight.h"
#include "GCChangeWeather.h"
#include "GCCrossCounterOK1.h"
#include "GCCrossCounterOK2.h"
#include "GCCrossCounterOK3.h"
#include "GCDeleteInventoryItem.h"
#include "GCDeleteObject.h"
#include "GCRemoveCorpseHead.h"
#include "GCRemoveInjuriousCreature.h"
#include "GCDeleteandPickUpOK.h"
#include "GCDeleteEffectFromTile.h"
#include "GCDisconnect.h"
#include "GCDropItemToZone.h"
#include "GCFastMove.h"
#include "GCFakeMove.h"
#include "GCGetDamage.h"
#include "GCGetOffMotorCycle.h"
#include "GCGetOffMotorCycleFailed.h"
#include "GCGetOffMotorCycleOK.h"
#include "GCGlobalChat.h"

#include "GCHPRecoveryStartToSelf.h"
#include "GCHPRecoveryStartToOthers.h"
#include "GCHPRecoveryEndToSelf.h"
#include "GCHPRecoveryEndToOthers.h"

#include "GCKnockBack.h"
#include "GCKnocksTargetBackOK1.h"
#include "GCKnocksTargetBackOK2.h"
#include "GCKnocksTargetBackOK4.h"
#include "GCKnocksTargetBackOK5.h"
#include "GCLearnSkillFailed.h"
#include "GCLearnSkillOK.h"
#include "GCLearnSkillReady.h"
#include "GCLightning.h"
#include "GCMakeItemOK.h"
#include "GCMakeItemFail.h"
#include "GCMineExplosionOK1.h"
#include "GCMineExplosionOK2.h"
#include "GCModifyInformation.h"
#include "GCMorph1.h"
#include "GCMorphSlayer2.h"
#include "GCMorphVampire2.h"
#include "GCMove.h"
#include "GCMoveOK.h"
#include "GCMoveError.h"

#include "GCMPRecoveryStart.h"
#include "GCMPRecoveryEnd.h"

#include "GCNPCAsk.h"
#include "GCNPCSay.h"
#include "GCRealWearingInfo.h"
#include "GCReconnect.h"
#include "GCReconnectLogin.h"
#include "GCRemoveEffect.h"
#include "GCRemoveFromGear.h"
#include "GCRideMotorCycle.h"
#include "GCRideMotorCycleFailed.h"
#include "GCRideMotorCycleOK.h"
#include "GCReloadOK.h"
#include "GCSay.h"
#include "GCSearchMotorcycleOK.h"
#include "GCSearchMotorcycleFail.h"
#include "GCSetPosition.h"
// Shop Interface
#include "GCShopBuyOK.h"
#include "GCShopBuyFail.h"
#include "GCShopList.h"
#include "GCShopListMysterious.h"
#include "GCShopSold.h"
#include "GCShopVersion.h"
#include "GCShopBought.h"
#include "GCShopSellOK.h"
#include "GCShopSellFail.h"
#include "GCShopMarketCondition.h"

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
#include "GCUnburrowOK.h"
#include "GCUnburrowFail.h"
#include "GCUntransformOK.h"
#include "GCUntransformFail.h"
#include "GCTeachSkillInfo.h"
#include "GCUpdateInfo.h"
#include "GCUseBonusPointFail.h"
#include "GCUseBonusPointOK.h"
#include "GCUseOK.h"
#include "GCTakeOff.h"
#include "GCThrowItemOK1.h"
#include "GCThrowItemOK2.h"
#include "GCThrowItemOK3.h"
#include "GCVisibleOK.h"
#include "GCVisibleFail.h"
#include "GCNPCInfo.h"
#include "GCNPCAskVariable.h"
#include "GCWarScheduleList.h"
#include "GCWarList.h"

#if defined(__GAME_CLIENT__) || defined(__LOGIN_SERVER__)
	#include "GMServerInfo.h"
	#include "GLIncomingConnection.h"
	#include "GLIncomingConnectionError.h"
	#include "GLIncomingConnectionOK.h"
	#include "GLKickVerify.h"
#endif

#include "Lpackets/LCCreatePCError.h"
#include "Lpackets/LCCreatePCOK.h"
#include "Lpackets/LCDeletePCError.h"
#include "Lpackets/LCDeletePCOK.h"
#include "Lpackets/LCLoginError.h"
#include "Lpackets/LCLoginOK.h"
#include "Lpackets/LCPCList.h"
#include "Lpackets/LCQueryResultPlayerID.h"
#include "Lpackets/LCQueryResultCharacterName.h"
#include "Lpackets/LCReconnect.h"
#include "Lpackets/LCRegisterPlayerError.h"
#include "Lpackets/LCRegisterPlayerOK.h"
#include "Lpackets/LCSelectPCError.h"

#ifndef __GAME_CLIENT__
	#include "Lpackets/LGIncomingConnection.h"
	#include "Lpackets/LGIncomingConnectionOK.h"
	#include "Lpackets/LGIncomingConnectionError.h"
	#include "Lpackets/LGKickCharacter.h"
#endif

#include "Lpackets/LCVersionCheckOK.h"
#include "Lpackets/LCVersionCheckError.h"
#include "Lpackets/LCServerList.h"
#include "Lpackets/LCWorldList.h"

// added by elcastle 2000-11-29
//#include "Cpackets/CGDialUp.h"
//#include "Cpackets/CGPhoneDisconnect.h"
//#include "Cpackets/CGPhoneSay.h"
#include "Cpackets/CGWhisper.h"

//#include "GCPhoneConnected.h"
//#include "GCRing.h"
//#include "GCPhoneDisconnected.h"
//#include "GCPhoneConnectionFailed.h"
//#include "GCPhoneSay.h"
#include "GCWhisper.h"
#include "GCWhisperFailed.h"

// added by elca 2000-11-29
#include "GCSkillInfo.h"

// added by elca 2000-12-09
#include "GCStatusCurrentHP.h"

// added by elca 2000-12-09
#include "Cpackets/CGSetSlayerHotKey.h"
#include "Cpackets/CGSetVampireHotKey.h"


// added by elca 2001-06-26
#include "Cpackets/CGSelectPortal.h"

// 2001-01-08 김성민
#include "Cpackets/CGMouseToStash.h"
#include "Cpackets/CGStashToMouse.h"
#include "Cpackets/CGStashList.h"
#include "GCStashList.h"
#include "Cpackets/CGStashDeposit.h"
#include "Cpackets/CGStashWithdraw.h"
#include "Cpackets/CGStashRequestBuy.h"
#include "GCStashSell.h"

#include "Cpackets/CGTradePrepare.h"
#include "Cpackets/CGTradeAddItem.h"
#include "Cpackets/CGTradeRemoveItem.h"
#include "Cpackets/CGTradeMoney.h"
#include "Cpackets/CGTradeFinish.h"
#include "GCTradePrepare.h"
#include "GCTradeAddItem.h"
#include "GCTradeRemoveItem.h"
#include "GCTradeMoney.h"
#include "GCTradeFinish.h"
#include "GCTradeError.h"
#include "GCTradeVerify.h"

#include "Cpackets/CGSkillToObject.h"
#include "Cpackets/CGSkillToSelf.h"
#include "Cpackets/CGSkillToTile.h"

#include "Cpackets/CGSilverCoating.h"
#include "GCNPCResponse.h"

#include "GCNPCSayDynamic.h"
#include "GCNPCAskDynamic.h"

#include "Cpackets/CGUseItemFromInventory.h"
#include "Cpackets/CGSelectWayPoint.h"
#include "GCAddHelicopter.h"
#include "GCAddVampirePortal.h"
#include "GCEnterVampirePortal.h"

#include "Cpackets/CGSelectTileEffect.h"

#include "Cpackets/CGPartyInvite.h"
#include "Cpackets/CGPartyLeave.h"

#include "GCPartyInvite.h"
#include "GCPartyLeave.h"
#include "GCPartyJoined.h"
#include "GCPartyError.h"

#include "Cpackets/CGResurrect.h"

#include "Cpackets/CGRequestIP.h"
#include "GCRequestedIP.h"

#include "GCRequestFailed.h"

#include "GCOtherModifyInfo.h"

#ifndef __GAME_CLIENT__
	#include "GGCommand.h"
#endif


#ifdef __GAME_CLIENT__
	#include "Rpackets/CRConnect.h"
	#include "Rpackets/RCConnectVerify.h"
	#include "Rpackets/CRRequest.h"
	#include "Rpackets/RCPositionInfo.h"
	#include "Rpackets/CRDisconnect.h"
	#include "Rpackets/RCSay.h"
	#include "Rpackets/RCStatusHP.h"
	#include "Rpackets/CRWhisper.h"
	#include "Rpackets/RCRequestVerify.h"
	#include "Rpackets/RCRequestedFile.h"
	#include "Rpackets/RCCharacterInfo.h"
#endif

// 길드관련 2002. 05. 31. bezz
//#include "GCShowGuildRegist.h"
#include "Cpackets/CGRegistGuild.h"
#include "GCWaitGuildList.h"
#include "GCShowWaitGuildInfo.h"
#include "GCShowGuildInfo.h"
#include "Cpackets/CGSelectGuild.h"
#include "Cpackets/CGTryJoinGuild.h"
#include "GCShowGuildJoin.h"
#include "Cpackets/CGJoinGuild.h"
#include "GCShowMessageBox.h"
//#include "GCModifyMoney.h"
//#include "Cpackets/CGQuitGuild.h"
#include "Cpackets/CGRequestGuildMemberList.h"
#include "Cpackets/CGSelectGuildMember.h"
//#include "Cpackets/CGExpelGuildMember.h"
#include "Cpackets/CGModifyGuildMember.h"
#include "GCActiveGuildList.h"
#include "GCShowGuildMemberInfo.h"
#include "GCGuildMemberList.h"
#include "GCModifyGuildMemberInfo.h"

#ifndef __GAME_CLIENT__
	#include "GSAddGuild.h"
	#include "GSAddGuildMember.h"
	#include "GSQuitGuild.h"
	#include "GSExpelGuildMember.h"
	#include "GSModifyGuildMember.h"
	#include "Spackets/SGAddGuildOK.h"
	#include "Spackets/SGAddGuildMemberOK.h"
	#include "Spackets/SGQuitGuildOK.h"
	#include "Spackets/SGExpelGuildMemberOK.h"
	#include "Spackets/SGModifyGuildMemberOK.h"
	#include "Spackets/SGDeleteGuildOK.h"
	#include "Spackets/SGModifyGuildOK.h"
#endif

#include "Cpackets/CGRelicToObject.h"

#include "Cpackets/CGPortCheck.h"

#include "Cpackets/CGGuildChat.h"
#include "GCGuildChat.h"

#ifndef __GAME_CLIENT__
	#include "GGGuildChat.h"
	#include "GSRequestGuildInfo.h"
	#include "Spackets/SGGuildInfo.h"
#endif

#include "Cpackets/CGAddItemToItem.h"
#include "GCAddItemToItemVerify.h"

#include "Cpackets/CGRequestInfo.h"
#include "GCNoticeEvent.h"

#include "Cpackets/CGModifyGuildIntro.h"
#include "Cpackets/CGModifyGuildMemberIntro.h"

#ifndef __GAME_CLIENT__
	#include "GSModifyGuildIntro.h"
	#include "Spackets/SGModifyGuildIntroOK.h"

	#include "GSGuildMemberLogOn.h"
	#include "Spackets/SGGuildMemberLogOnOK.h"
#endif

#include "Cpackets/CGSelectRankBonus.h"
#include "GCSelectRankBonusOK.h"
#include "GCSelectRankBonusFailed.h"
#include "GCRankBonusInfo.h"

#include "Cpackets/CGSkillToNamed.h"

#include "Cpackets/CGUseMessageItemFromInventory.h"

#include "GCHolyLandBonusInfo.h"
#include "GCBloodBibleStatus.h"
#include "GCKickMessage.h"
#include "GCTimeLimitItemInfo.h"
#include "GCSelectQuestID.h"
#include "Cpackets/CGSelectQuest.h"
#include "GCQuestStatus.h"
#include "GCMonsterKillQuestInfo.h"
#include "Cpackets/CGLotterySelect.h"
#include "GCNotifyWin.h"
#include "GCGoodsList.h"
#include "Cpackets/CGTakeOutGood.h"
#include "GCTakeOutOK.h"
#include "GCTakeOutFail.h"
#include "GCAddOusters.h"
#include "Cpackets/CGMixItem.h"
#include "GCAddOustersCorpse.h"
#include "Cpackets/CGAbsorbSoul.h"

#include "Cpackets/CGDownSkill.h"
#include "GCDownSkillOK.h"
#include "GCDownSkillFailed.h"

#include "GCMiniGameScores.h"
#include "Cpackets/CGSubmitScore.h"
#include "Cpackets/CGFailQuest.h"
#include "Cpackets/CGAddItemToCodeSheet.h"
#include "GCFlagWarStatus.h"
#include "GCOtherGuildName.h"
#include "GCSweeperBonusInfo.h"

#include "Cpackets/CGSelectRegenZone.h"
#include "GCRegenZoneStatus.h"
#include "GCPetInfo.h"
#include "Cpackets/CGTameMonster.h"
#include "Cpackets/CGPetGamble.h"
#include "Cpackets/CGCrashReport.h"
#include "GCPetUseSkill.h"
#include "GCSystemAvailabilities.h"
#include "GCPartyPosition.h"
#include "Cpackets/CGPartyPosition.h"
#include "GCPartySay.h"
#include "Cpackets/CGPartySay.h"

#include "GGServerChat.h"

#include "GCPetStashList.h"
#include "Cpackets/CGWithdrawPet.h"
#include "Cpackets/CGDepositPet.h"
#include "GCPetStashVerify.h"
#include "Cpackets/CGSMSSend.h"
#include "Cpackets/CGAddSMSAddress.h"
#include "Cpackets/CGDeleteSMSAddress.h"
#include "Cpackets/CGSMSAddressList.h"
#include "GCSMSAddressList.h"
#include "GCAddressListVerify.h"
#include "GCNicknameList.h"

#include "GCAddNickname.h"
#include "Cpackets/CGModifyNickname.h"
#include "Cpackets/CGSelectNickname.h"
#include "GCNicknameVerify.h"
#include "GCModifyNickname.h"

#include "GCGQuestStatusInfo.h"
#include "GCGQuestStatusModify.h"
#include "Cpackets/CGGQuestAccept.h"
#include "Cpackets/CGGQuestCancel.h"
#include "GCExecuteElement.h"
#include "GCGQuestInventory.h"
#include "GCAuthKey.h"
#include "Cpackets/CGAuthKey.h"
#include "Cpackets/CGUseItemFromGQuestInventory.h"

#include "GCGuildResponse.h"
#include "Cpackets/CGRequestGuildList.h"
#include "Cpackets/CGAppointSubmaster.h"
#include "Cpackets/CGRequestUnion.h"
#include "Cpackets/CGAcceptUnion.h"
#include "Cpackets/CGDenyUnion.h"
#include "Cpackets/CGRequestUnionInfo.h"
#include "Cpackets/CGExpelGuild.h"
#include "Cpackets/CGQuitUnion.h"
#include "Cpackets/CGQuitUnionAccept.h"
#include "Cpackets/CGQuitUnionDeny.h"
#include "GCUnionOfferList.h"
#include "GCBloodBibleList.h"
#include "Cpackets/CGSelectBloodBible.h"
#include "GCBloodBibleSignInfo.h"
#include "Cpackets/CGRangerSay.h"
#include "Cpackets/CGModifyTaxRatio.h"
#include "Cpackets/CGDisplayItem.h"
#include "Cpackets/CGUndisplayItem.h"
#include "Cpackets/CGStoreSign.h"
#include "Cpackets/CGStoreOpen.h"
#include "Cpackets/CGStoreClose.h"
#include "Cpackets/CGRequestStoreInfo.h"
#include "Cpackets/CGBuyStoreItem.h"
#include "GCMyStoreInfo.h"
#include "GCOtherStoreInfo.h"
#include "GCRemoveStoreItem.h"
#include "GCAddStoreItem.h"
#include "Cpackets/CGRequestPowerPoint.h"
#include "GCRequestPowerPointResult.h"
#include "Cpackets/CGUsePowerPoint.h"
#include "GCUsePowerPointResult.h"
#include "Cpackets/CGDonationMoney.h"
#include "Cpackets/CGGetEventItem.h"
//add by viva 2008-12-31
#include "Cpackets/CGConnectSetKey.h"
#include "GCFriendChatting.h"
//end
#ifndef __GAME_CLIENT__
//#include "GSGuildAction.h"
//#include "Spackets/SGGuildResponse.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
PacketFactoryManager::PacketFactoryManager () 
: m_Factories(NULL) , m_Size(Packet::PACKET_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// 패킷팩토리배열을 생성한다.
	m_Factories = new PacketFactory*[ m_Size ];
	
	// 팩토리에 대한 포인터들을 NULL 로 초기화한다.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
			
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
PacketFactoryManager::~PacketFactoryManager () 
{
	__BEGIN_TRY
		
	Assert(m_Factories != NULL);

	// 각각의 패킷팩토리들을 삭제한다.
	for (int i = 0 ; i < m_Size ; i ++) 
	{
#ifdef __GAME_CLIENT__
		if (m_Factories[i] != NULL)
		{
			delete m_Factories[i];
			m_Factories[i] = NULL;
		}
#else
		SAFE_DELETE(m_Factories[i]);
#endif
	}
	
	// 패킷팩토리배열을 삭제한다.
#ifdef __GAME_CLIENT__
	if (m_Factories != NULL)
	{
		delete [] m_Factories;
		m_Factories = NULL;
	}
#else
	SAFE_DELETE_ARRAY(m_Factories);
#endif
			
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 정의된 모든 패킷팩토리들을 여기에 추가한다.
//
//////////////////////////////////////////////////////////////////////
void PacketFactoryManager::init ()
{
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
#endif

#if defined(__GAME_SERVER__)
	// 2002.6.28
	addFactory( new CGPortCheckFactory() );

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

	// 전쟁 시스템
	addFactory( new CGRelicToObjectFactory() );

	addFactory( new CGRegistGuildFactory() );
	addFactory( new CGSelectGuildFactory() );
	addFactory( new CGTryJoinGuildFactory() );
	addFactory( new CGJoinGuildFactory() );
//	addFactory( new CGQuitGuildFactory() );
	addFactory( new CGRequestGuildMemberListFactory() );
	addFactory( new CGSelectGuildMemberFactory() );
//	addFactory( new CGExpelGuildMemberFactory() );
	addFactory( new CGModifyGuildMemberFactory() );
	addFactory( new CGGuildChatFactory() );

	// 인챈트 아이템 : 별 --> 아이템 넣기
	addFactory( new CGAddItemToItemFactory() );

	// 정보 요청. 2002.9.2
	addFactory( new CGRequestInfoFactory() );

	addFactory( new CGModifyGuildIntroFactory() );
	addFactory( new CGModifyGuildMemberIntroFactory() );

	addFactory( new CGUseMessageItemFromInventoryFactory() );

	// 2003. 1. 21
	addFactory( new CGWithdrawTaxFactory() );

	addFactory( new CGTypeStringListFactory() );

	addFactory( new CGUseItemFromGearFactory() );

	addFactory( new CGSkillToNamedFactory() );

	addFactory( new CGSelectRankBonusFactory() );
	addFactory( new CGSelectQuestFactory() );
	addFactory( new CGLotterySelectFactory() );
	addFactory( new CGTakeOutGoodFactory() );
	addFactory( new CGMixItemFactory() );
	addFactory( new CGAbsorbSoulFactory() );
	addFactory( new CGDownSkillFactory() );
	addFactory( new CGSubmitScoreFactory() );
	addFactory( new CGFailQuestFactory() );
	addFactory( new CGAddItemToCodeSheetFactory() );
	addFactory( new CGSelectRegenZoneFactory() );
	addFactory( new CGTameMonsterFactory() );
	addFactory( new CGPetGambleFactory() );
	addFactory( new CGCrashReportFactory() );

	
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
	addFactory( new GCWaitGuildListFactory() );
	addFactory( new GCShowGuildInfoFactory() );
	addFactory( new GCShowGuildJoinFactory() );
	addFactory( new GCShowMessageBoxFactory() );
//	addFactory( new GCModifyMoneyFactory() );
	addFactory( new GCShowWaitGuildInfoFactory() );
	addFactory( new GCActiveGuildListFactory() );

	addFactory( new GCShowGuildMemberInfoFactory() );
	addFactory( new GCGuildChatFactory() );
	addFactory( new GCGuildMemberListFactory() );
	addFactory( new GCModifyGuildMemberInfoFactory() );
	addFactory( new GCAddItemToItemVerifyFactory() );

	// 2002.9.2
	addFactory( new GCNoticeEventFactory() );

	addFactory( new GCSelectRankBonusOKFactory() );
	addFactory( new GCSelectRankBonusFailedFactory() );
	addFactory( new GCRankBonusInfoFactory() );

	addFactory( new GCNPCInfoFactory() );
	addFactory( new GCNPCAskVariableFactory() );
	addFactory( new GCWarScheduleListFactory() );
	addFactory( new GCWarListFactory() );

	addFactory( new GCHolyLandBonusInfoFactory() );
	addFactory( new GCBloodBibleStatusFactory() );
	addFactory( new GCKickMessageFactory() );
	addFactory( new GCTimeLimitItemInfoFactory() );
	addFactory( new GCSelectQuestIDFactory() );
	addFactory( new GCQuestStatusFactory() );
	addFactory( new GCMonsterKillQuestInfoFactory() );
	addFactory( new GCNotifyWinFactory() );
	addFactory( new GCGoodsListFactory() );
	addFactory( new GCTakeOutOKFactory() );
	addFactory( new GCTakeOutFailFactory() );
	addFactory( new GCAddOustersFactory() );
	addFactory( new GCAddOustersCorpseFactory() );
	addFactory( new GCDownSkillOKFactory() );
	addFactory( new GCDownSkillFailedFactory() );

	addFactory( new GCMiniGameScoresFactory() );
	addFactory( new GCFlagWarStatusFactory() );
	addFactory( new GCOtherGuildNameFactory() );
	addFactory( new GCSweeperBonusInfoFactory() );
	addFactory( new GCRegenZoneStatusFactory() );
	addFactory( new GCPetInfoFactory() );
	addFactory( new GCPetUseSkillFactory() );
	addFactory( new GCSystemAvailabilitiesFactory() );

	addFactory( new GCPartyPositionFactory() );
	addFactory( new CGPartyPositionFactory() );
	addFactory( new CGPartySayFactory() );
	addFactory( new GCPartySayFactory() );

	addFactory( new GGServerChatFactory() );

	addFactory( new GCPetStashListFactory() );
	addFactory( new CGWithdrawPetFactory() );
	addFactory( new CGDepositPetFactory() );
	addFactory( new GCPetStashVerifyFactory() );

	addFactory( new CGSMSSendFactory() );

	addFactory( new CGAddSMSAddressFactory() );
	addFactory( new CGDeleteSMSAddressFactory() );
	addFactory( new CGSMSAddressListFactory() );
	addFactory( new GCSMSAddressListFactory() );
	addFactory( new GCAddressListVerifyFactory() );

	addFactory( new GCNicknameListFactory() );
	addFactory(	new GCAddNicknameFactory() );
	addFactory(	new CGModifyNicknameFactory() );
	addFactory(	new CGSelectNicknameFactory() );
	addFactory(	new GCNicknameVerifyFactory() );
	addFactory(	new GCModifyNicknameFactory() );

	addFactory( new GCGQuestStatusInfoFactory() );
	addFactory( new GCGQuestStatusModifyFactory() );
	addFactory( new CGGQuestAcceptFactory() );
	addFactory( new CGGQuestCancelFactory() );
	addFactory( new GCExecuteElementFactory() );
	addFactory( new GCGQuestInventoryFactory() );

	addFactory( new GCAuthKeyFactory() );
	addFactory( new CGAuthKeyFactory() );
	addFactory( new CGUseItemFromGQuestInventoryFactory() );

	addFactory( new GCGuildResponseFactory() );
	addFactory( new CGRequestGuildListFactory() );
	addFactory( new CGAppointSubmasterFactory() );
	addFactory( new CGRequestUnionFactory() );
	addFactory( new CGAcceptUnionFactory() );
	addFactory( new CGDenyUnionFactory() );
	addFactory( new CGRequestUnionInfoFactory() );
	addFactory( new CGExpelGuildFactory() );
	addFactory( new CGQuitUnionFactory() );
	addFactory( new CGQuitUnionAcceptFactory() );
	addFactory( new CGQuitUnionDenyFactory() );
	addFactory( new GCUnionOfferListFactory() );

	addFactory( new GCBloodBibleListFactory() );
	addFactory( new CGSelectBloodBibleFactory() );
	addFactory( new GCBloodBibleSignInfoFactory() );
	addFactory( new CGRangerSayFactory() );
	addFactory( new CGModifyTaxRatioFactory() );

	addFactory( new CGDisplayItemFactory() );
	addFactory( new CGUndisplayItemFactory() );
	addFactory( new CGStoreSignFactory() );
	addFactory( new CGStoreOpenFactory() );
	addFactory( new CGStoreCloseFactory() );
	addFactory( new CGRequestStoreInfoFactory() );
	addFactory( new CGBuyStoreItemFactory() );
	addFactory( new GCMyStoreInfoFactory() );
	addFactory( new GCOtherStoreInfoFactory() );
	addFactory( new GCRemoveStoreItemFactory() );
	addFactory( new GCAddStoreItemFactory() );
	addFactory( new CGRequestPowerPointFactory() );
	addFactory( new GCRequestPowerPointResultFactory() );
	addFactory( new CGUsePowerPointFactory() );
	addFactory( new GCUsePowerPointResultFactory() );
	addFactory( new CGDonationMoneyFactory() );
	addFactory( new CGGetEventItemFactory() );


//add by viva 2008-12-31
	addFactory( new CGConnectSetKeyFactory() );
	addFactory( new GCFriendChattingFactory() );
	//addFactory( new GCUseSkillCardOKFactory() );
//end

	addFactory(new GGCommandFactory());
	// addFactory(new GMServerInfoFactory());

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


#if defined(__GAME_CLIENT__) || defined(__LOGIN_SERVER__)
	addFactory(new GLIncomingConnectionFactory());
	addFactory(new GLIncomingConnectionErrorFactory());
	addFactory(new GLIncomingConnectionOKFactory());
	addFactory(new GLKickVerifyFactory());

	addFactory(new LGIncomingConnectionFactory());
	addFactory(new LGIncomingConnectionOKFactory());
	addFactory(new LGIncomingConnectionErrorFactory());
	addFactory(new LGKickCharacterFactory());
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
		addFactory( new SGQuitGuildOKFactory() );
		addFactory( new SGExpelGuildMemberOKFactory() );
		addFactory( new SGModifyGuildMemberOKFactory() );
		addFactory( new SGDeleteGuildOKFactory() );
		addFactory( new SGModifyGuildOKFactory() );
		addFactory( new GSExpelGuildMemberFactory() );
		addFactory( new GSModifyGuildMemberFactory() );
		addFactory( new SGAddGuildMemberOKFactory() );
		addFactory(new SGAddGuildOKFactory() );
		addFactory(new GSAddGuildFactory() );
		addFactory(new GSAddGuildMemberFactory() );
		addFactory( new GSQuitGuildFactory());

		// addFactory( new GGGuildChatFactory() );
		addFactory( new GSRequestGuildInfoFactory() );
		addFactory( new SGGuildInfoFactory() );

		addFactory( new GSModifyGuildIntroFactory() );
		addFactory( new SGModifyGuildIntroOKFactory() );

		addFactory( new GSGuildMemberLogOnFactory() );
		addFactory( new SGGuildMemberLogOnOKFactory() );
#endif



#if __OUTPUT_INIT__
	cout << toString() << endl;
#endif
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// 팩토리 객체를 특정 인덱스에 추가한다.
//
//////////////////////////////////////////////////////////////////////
void PacketFactoryManager::addFactory (PacketFactory * pFactory) 
{
	__BEGIN_TRY
		
	if (m_Factories[ pFactory->getPacketID() ] != NULL) {
		StringStream msg;
#ifdef __GAME_CLIENT__
	#ifdef __DEBUG_OUTPUT__
		msg << "duplicate packet factories, " << pFactory->getPacketName() ;
	#else	
		msg << "duplicate packet factories ";
	#endif
#else
		msg << "duplicate packet factories, " << pFactory->getPacketName() ;
#endif
		throw Error(msg.toString());
	}
	
	// 패킷팩토리를 등록한다.
	m_Factories[ pFactory->getPacketID() ] = pFactory;
			
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
//
// 패킷아이디로 패킷객체를 생성한다.
//
//////////////////////////////////////////////////////////////////////
Packet * PacketFactoryManager::createPacket (PacketID_t packetID) 
{
	__BEGIN_TRY

	// 패킷 아이디가 범위를 넘어섬으로 인해서 Seg.Fault 가 발생하지 않도록.
	// 이런 사용자는 당장 짤라야 한다.
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
// 패킷아이디로 특정 패킷의 최대 크기를 리턴한다.
//
//////////////////////////////////////////////////////////////////////
PacketSize_t PacketFactoryManager::getPacketMaxSize (PacketID_t packetID) 
{
	__BEGIN_TRY

	// 패킷 아이디가 범위를 넘어섬으로 인해서 Seg.Fault 가 발생하지 않도록.
	// 이런 사용자는 당장 짤라야 한다.
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
// 패킷아이디로 특정 패킷의 이름을 리턴한다.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__GAME_CLIENT__) || defined(__GAME_CLIENT__) && defined(__DEBUG_OUTPUT__)
string PacketFactoryManager::getPacketName (PacketID_t packetID) 
{
	__BEGIN_TRY

	// 패킷 아이디가 범위를 넘어섬으로 인해서 Seg.Fault 가 발생하지 않도록.
	// 이런 사용자는 당장 짤라야 한다.
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
string PacketFactoryManager::toString () const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "PacketFactoryManager(\n";

	for (int i = 0 ; i < m_Size ; i ++)
		msg << "PacketFactories[" << i << "] == " << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getPacketName()) << "\n";

	msg << ")";

	return msg.toString();

	__END_CATCH
}
#endif

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////

PacketFactoryManager * g_pPacketFactoryManager = NULL;
