//////////////////////////////////////////////////////////////////////////////
// Filename    : CLDeletePCHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLDeletePC.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
	#include "ItemDestroyer.h"
	#include "Properties.h"

	#include "Lpackets/LCDeletePCOK.h"
	#include "Lpackets/LCDeletePCError.h"

	#include <cstdio>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CLDeletePCHandler::execute (CLDeletePC* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	cout << pPacket->toString() << endl;

	LoginPlayer*    pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	Statement*      pStmt        = NULL;
	Statement*      pLoginStmt   = NULL;
	Result*         pResult      = NULL;
	LCDeletePCError lcDeletePCError;
	WorldID_t		WorldID		 = pLoginPlayer->getWorldID();

	try 
	{
		pLoginStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt = g_pDatabaseManager->getConnection( WorldID )->createStatement();

		////////////////////////////////////////////////////////////
		// 일단 그런 슬레이어가 존재하는지 체크한다.
		////////////////////////////////////////////////////////////
//		printf("SELECT Active FROM Slayer WHERE Name = '%s' AND Active='ACTIVE' AND PlayerID='%s'", pPacket->getName().c_str(), pPlayer->getID().c_str());
		pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer WHERE Name = '%s' AND Active='ACTIVE'", pPacket->getName().c_str());
		if (pResult->getRowCount() != 1) 
		{
			lcDeletePCError.setErrorID(NOT_FOUND_PLAYER);
			throw InvalidProtocolException("no such slayer exist.");
		}

		if ( pResult->next() )
		{
			string id = pResult->getString(1);
			if ( id != pPlayer->getID() )
			{
				filelog("DeletePC.log", "Illegal PC Delete : [%s:%s]", pPlayer->getID().c_str(), pPacket->getName().c_str());
				throw InvalidProtocolException("illegal pc delete");
			}
		}

		////////////////////////////////////////////////////////////
		// 주민등록번호를 확인한다.
		////////////////////////////////////////////////////////////

//add by zdj 2005.5.11

//팁귁苟충侶뙈

/*

#if !defined(__CHINA_SERVER__) && !defined(__THAILAND_SERVER__)
		if ( (pLoginPlayer->isFreePass() && !pLoginPlayer->isWebLogin() )
			|| g_pConfig->getPropertyInt("IsNetMarble")==1)
		{
			// 무조건 지울 수 있다.
			pResult = pLoginStmt->executeQuery("SELECT length(Password) FROM Player Where PlayerID = '%s'", pPlayer->getID().c_str());

			if(!pResult->next())
			{
				lcDeletePCError.setErrorID(NOT_FOUND_PLAYER);
				throw InvalidProtocolException("no such slayer exist.");
			}

			int    PasswordLength = pResult->getInt(1);

			if (PasswordLength != 12) 
			{
				lcDeletePCError.setErrorID(INVALID_SSN);
				throw InvalidProtocolException("invalid SSN");
			}
		}
		else
		{
			pResult = pLoginStmt->executeQuery("SELECT SSN FROM Player Where PlayerID = '%s'", pPlayer->getID().c_str());

			if(!pResult->next())
			{
				lcDeletePCError.setErrorID(NOT_FOUND_PLAYER);
				throw InvalidProtocolException("no such slayer exist.");
			}

			string SSN = pResult->getString(1);

			cout << "DB SSN:" << SSN << endl;

			if (SSN != pPacket->getSSN())
			{
				lcDeletePCError.setErrorID(INVALID_SSN);
				throw InvalidProtocolException("invalid SSN");
			}
		}
#endif

*/ //팁귁

		////////////////////////////////////////////////////////////
		// 일단 슬레이어 테이블에는 확실히 존재한다.
		////////////////////////////////////////////////////////////
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		pResult = pStmt->executeQuery("DELETE FROM Slayer WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#else
		pResult = pStmt->executeQuery("UPDATE Slayer SET Active='INACTIVE' WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#endif

		if (pStmt->getAffectedRowCount() != 1) 
		{
			lcDeletePCError.setErrorID(NOT_FOUND_ID);
			throw InvalidProtocolException("no such slayer exist.");
		}

#if !defined(__CHINA_SERVER__) && !defined(__THAILAND_SERVER__) && !defined(__NETMARBLE_SERVER__)
		pLoginStmt->executeQuery("INSERT INTO DeleteChar (PlayerID, WorldID, Name, delDate) VALUES ('%s',%u,'%s',now())",
			pLoginPlayer->getID().c_str(), WorldID, pPacket->getName().c_str());
#endif

		////////////////////////////////////////////////////////////
		// 뱀파이어 테이블을 지운다.
		////////////////////////////////////////////////////////////
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		pResult = pStmt->executeQuery("DELETE FROM Vampire WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#else
		pResult = pStmt->executeQuery("UPDATE Vampire SET Active='INACTIVE' WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#endif
		//if (pStmt->getAffectedRowCount() == 1) //cout << "Vampire(" << pPacket->getName() << ") deleted successfully...." << endl;

		////////////////////////////////////////////////////////////
		// 아우스터스 테이블을 지운다.
		////////////////////////////////////////////////////////////
#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		pResult = pStmt->executeQuery("DELETE FROM Ousters WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#else
		pResult = pStmt->executeQuery("UPDATE Ousters SET Active='INACTIVE' WHERE Name = '%s' AND Slot = '%s'", pPacket->getName().c_str(), Slot2String[pPacket->getSlot()].c_str());
#endif

#if defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__) || defined(__NETMARBLE_SERVER__)
		////////////////////////////////////////////////////////////
		// 슬레이어 스킬을 지운다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM SkillSave WHERE OwnerID = '%s'", pPacket->getName().c_str());
		//cout << "Slayer(" << pPacket->getName() << ") deleted successfully...." << endl;

		////////////////////////////////////////////////////////////
		// 뱀파이어 스킬을 지워준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM VampireSkillSave WHERE OwnerID = '%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// 아우스터즈 스킬을 지워준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM OustersSkillSave WHERE OwnerID = '%s'", pPacket->getName().c_str());
#endif

		////////////////////////////////////////////////////////////
		// 계급 보너스를 지워준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM RankBonusData WHERE OwnerID = '%s'", pPacket->getName().c_str() );

		////////////////////////////////////////////////////////////
		// 아이템을 깡그리 지운다.
		////////////////////////////////////////////////////////////
//		g_pItemDestroyer->destroyAll(pPacket->getName());
		string ownerID = pPacket->getName();
		pStmt->executeQuery("DELETE FROM ARObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BeltObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BladeObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BloodBibleObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BombMaterialObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BombObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM BraceletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CastleSymbolObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CrossObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventGiftBoxObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventStarObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventTreeObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GloveObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM HelmObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM HolyWaterObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM KeyObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM LearningItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MagazineObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MineObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MoneyObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MotorcycleObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM NecklaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PotionObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM QuestItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM RelicObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SGObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SMGObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SRObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SerumObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShieldObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShoesObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SkullObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SlayerPortalItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SwordObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM TrouserObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM RingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoupleRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireAmuletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireBraceletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireCoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireETCObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireEarringObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireNecklaceObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampirePortalItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireWeaponObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM VampireCoupleRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM WaterObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EventItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM DyePotionObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ResurrectItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MixingItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersArmsbandObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersBootsObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersChakramObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersCircletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersCoatObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersPendentObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersRingObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersStoneObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersWristletObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM LarvaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PupaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ComposMeiObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM OustersSummonItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM EffectItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CodeSheetObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MoonCardObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM SweeperObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PetItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PetFoodObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PetEnchantItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM LuckyBagObject WHERE OwnerID = '" + ownerID + "'");
#ifndef __THAILAND_SERVER__
		pStmt->executeQuery("DELETE FROM SMSItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM CoreZapObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GQuestItemObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM GQuestSave WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM TrapItemObject WHERE OwnerID = '" + ownerID + "'");
#endif
		pStmt->executeQuery("DELETE FROM CarryingReceiverObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM ShoulderArmorObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM DermisObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM PersonaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM FasciaObject WHERE OwnerID = '" + ownerID + "'");
		pStmt->executeQuery("DELETE FROM MittenObject WHERE OwnerID = '" + ownerID + "'");

		////////////////////////////////////////////////////////////
		// 커플일 경우 커플 목록에서 지워준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM CoupleInfo WHERE FemalePartnerName='%s'",ownerID.c_str());
		pStmt->executeQuery("DELETE FROM CoupleInfo WHERE MalePartnerName='%s'",ownerID.c_str());

		////////////////////////////////////////////////////////////
		// 남아 있는 이펙트들도 지운다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM EffectAcidTouch where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectAftermath where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectBloodDrain where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectDetectHidden where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectFlare where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectLight where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectParalysis where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectPoison where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectPoisonousHands where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectProtectionFromParalysis where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectProtectionFromPoison where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectRestore where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectYellowPoisonToCreature where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EffectMute where OwnerID='%s'", pPacket->getName().c_str());
		pStmt->executeQuery("DELETE FROM EnemyErase where OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// 플래그 셋도 삭제해 준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM FlagSet WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// 시간제한 아이템도 삭제해 준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM TimeLimitItems WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// 이벤트 정보도 삭제해 준다.
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM EventQuestAdvance WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// 모퍼스 파워 포인트도 삭제.. 잇힝
		////////////////////////////////////////////////////////////
		pStmt->executeQuery("DELETE FROM MofusPowerPoint WHERE OwnerID='%s'", pPacket->getName().c_str());

		////////////////////////////////////////////////////////////
		// 클라이언트에게 PC 삭제 성공 패킷을 날린다.
		////////////////////////////////////////////////////////////
		LCDeletePCOK lcDeletePCOK;
		pLoginPlayer->sendPacket(&lcDeletePCOK);
	
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);

		SAFE_DELETE(pStmt);
	} 
	catch (InvalidProtocolException & ipe) 
	{
		cout << "Fail to deletePC : " << ipe.toString() << endl;

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pLoginStmt);

		// 클라이언트에게 PC 삭제 실패 패킷을 날린다.
		pLoginPlayer->sendPacket(&lcDeletePCError);
	} 
	catch (SQLQueryException & sqe) 
	{
		cout << "Fail to deletePC : " << sqe.toString() << endl;

		SAFE_DELETE(pStmt);
		SAFE_DELETE(pLoginStmt);

		// 클라이언트에게 PC 삭제 실패 패킷을 날린다.
		pLoginPlayer->sendPacket(&lcDeletePCError);
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
