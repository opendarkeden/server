//////////////////////////////////////////////////////////////////////////////
// Filename    : SoulChain.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SoulChain.h"
#include "EffectSoulChain.h"
#include "PCFinder.h"
#include "GamePlayer.h"
#include "ZoneInfoManager.h"
#include "PKZoneInfoManager.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "GDRLairManager.h"
#include "war/WarSystem.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void SoulChain::execute(Slayer* pSlayer, const string& targetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);

		if ( pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) 
			|| pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) )
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// 이 스킬은 모든 슬레이어 그랜드 마스터라면 쓸 수 있다.
		// 도메인데 종속된 스킬이 아니므로 도메인 중 최고 레벨을 현재 도메인으로 한다.
		SkillDomainType_t DomainType = pSlayer->getHighestSkillDomain();

		ZoneCoord_t x = pSlayer->getX();
		ZoneCoord_t y = pSlayer->getY();
		
		bool bValidTarget = false;
		__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

		Creature* pTarget = g_pPCFinder->getCreature_LOCKED( targetName );
		if ( pTarget != NULL )
		{
			Zone* pTargetZone = pTarget->getZone();
			if ( pTargetZone != NULL )
			{
				// Target 체크
				// 같은 종족이어야 한다.
				bool bSlayer = pTarget->isSlayer();
				// 일반 유저이여야 된다.
				bool bPLAYER = pTarget->getCompetence() == PLAYER;
				bool bMasterLair = pTargetZone->isMasterLair() || GDRLairManager::Instance().isGDRLairZone(pTargetZone->getZoneID());
				// 유료 서비스 사용이 가능한가?
				bool bValidPay = pGamePlayer->loginPayPlay( pGamePlayer->getSocket()->getHost(), pGamePlayer->getID() )
							|| pGamePlayer->isFamilyFreePass()
							|| !g_pZoneInfoManager->getZoneInfo( pTargetZone->getZoneID() )->isPayPlay();

				// 야전사령부, 시외곽지역, 이벤트경기장, 이벤트OX, 테메리에로는 갈 수 없다.
				bool bValidZone = pTargetZone->getZoneID() != 2101 && pTargetZone->getZoneID() != 2102 &&
								  pTargetZone->getZoneID() != 1005 && pTargetZone->getZoneID() != 1006 &&
								  pTargetZone->getZoneID() != 1122 && pTargetZone->getZoneID() != 1131 &&
								  pTargetZone->getZoneID() != 1132 && pTargetZone->getZoneID() != 1133 &&
								  pTargetZone->getZoneID() != 1134 && !pTargetZone->isCastleZone() &&
				// 성이나 마스터 레어로도 쫓아갈 수 없다. 2003. 1.20. by bezz, Sequoia
				// 아담의 성지 내로도 쫓아갈 수 없다. 2003. 2. 8. by Sequoia
								  (!g_pWarSystem->hasActiveRaceWar() || !pTargetZone->isHolyLand()) && !pTargetZone->isCastle() && !pTargetZone->isMasterLair() &&
								  !g_pPKZoneInfoManager->isPKZone( pTargetZone->getZoneID() ) &&
								  // 다이나믹 존으로도 갈 수 없다.
								  !pTargetZone->isDynamicZone();

				bValidTarget = bSlayer && bPLAYER && !bMasterLair && bValidPay && bValidZone;
			}
		}

		__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

		int  RequiredMP  = pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
//		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
//		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_SOUL_CHAIN)
							|| pSlayer->hasRelicItem()
							|| pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
							|| pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && !bEffected && bValidTarget)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 10 초 동안 움직일 수 없도록 이펙트를 붙인다.
			EffectSoulChain* pEffect= new EffectSoulChain(pSlayer);
			pEffect->setDuration(output.Duration);
			pEffect->setDeadline(100);
			pEffect->setTargetName( targetName );
			pEffect->setZone( pZone );

			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_SOUL_CHAIN);

			// 경험치를 올린다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);

			int STRPoint, DEXPoint, INTPoint;
			switch ( DomainType )
			{
				case SKILL_DOMAIN_BLADE:
				case SKILL_DOMAIN_SWORD:
					STRPoint = 8; DEXPoint = 1; INTPoint = 1;
					break;
				case SKILL_DOMAIN_GUN:
					STRPoint = 1; DEXPoint = 8; INTPoint = 1;
					break;
				case SKILL_DOMAIN_ENCHANT:
				case SKILL_DOMAIN_HEAL:
					STRPoint = 1; DEXPoint = 1; INTPoint = 8;
					break;
				default:
					Assert(false);
			}
			shareAttrExp(pSlayer, ExpUp, STRPoint, DEXPoint, INTPoint, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			// 패킷을 보낸다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
			_GCSkillToSelfOK1.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_SOUL_CHAIN);

			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 셀프
//////////////////////////////////////////////////////////////////////////////
void SoulChain::execute(Vampire* pVampire, const string& targetName, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);

		if ( pVampire->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
			|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) )
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pVampire->getX();
		ZoneCoord_t y = pVampire->getY();

		bool bValidTarget = false;
		__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

		Creature* pTarget = g_pPCFinder->getCreature_LOCKED( targetName );
		if ( pTarget != NULL )
		{
			Zone* pTargetZone = pTarget->getZone();
			if ( pTargetZone != NULL )
			{
				// Target 체크
				// 같은 종족이어야 한다.
				bool bVampire = pTarget->isVampire();
				// 일반 유저이여야 된다.
				bool bPLAYER = pTarget->getCompetence() == PLAYER;
				// 마스터 레어로는 이동할 수 없다.
				bool bMasterLair = pTargetZone->isMasterLair() || GDRLairManager::Instance().isGDRLairZone(pTargetZone->getZoneID());
				// 유료 서비스 사용이 가능한가?
				bool bValidPay = pGamePlayer->loginPayPlay( pGamePlayer->getSocket()->getHost(), pGamePlayer->getID() )
							|| pGamePlayer->isFamilyFreePass()
							|| !g_pZoneInfoManager->getZoneInfo( pTargetZone->getZoneID() )->isPayPlay();

				// 야전사령부, 시외곽지역, 이벤트경기장, 이벤트OX, 테메리에로는 갈 수 없다.
				bool bValidZone = pTargetZone->getZoneID() != 2101 && pTargetZone->getZoneID() != 2102 &&
								  pTargetZone->getZoneID() != 1005 && pTargetZone->getZoneID() != 1006 &&
								  pTargetZone->getZoneID() != 1122 && pTargetZone->getZoneID() != 1131 &&
								  pTargetZone->getZoneID() != 1132 && pTargetZone->getZoneID() != 1133 &&
								  pTargetZone->getZoneID() != 1134 && !pTargetZone->isCastleZone() &&
								  (!g_pWarSystem->hasActiveRaceWar() || !pTargetZone->isHolyLand()) && !pTargetZone->isCastle() && !pTargetZone->isMasterLair() &&
								  !g_pPKZoneInfoManager->isPKZone( pTargetZone->getZoneID() ) &&
								  // 다이나믹 존으로도 갈 수 없다.
								  !pTargetZone->isDynamicZone();

				bValidTarget = bVampire && bPLAYER && !bMasterLair && bValidPay && bValidZone;
			}
		}

		__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
//		bool bRangeCheck = checkZoneLevelToUseSkill(pVampire);
//		bool bHitRoll    = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot);
		bool bEffected   = pVampire->isFlag(Effect::EFFECT_CLASS_SOUL_CHAIN) || 
							pVampire->hasRelicItem() ||
							pVampire->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) ||
							pVampire->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && !bEffected && bValidTarget)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);
		
			// 10 초 동안 움직일 수 없도록 이펙트를 붙인다.
			EffectSoulChain* pEffect = new EffectSoulChain( pVampire );
			pEffect->setDuration(output.Duration);
			pEffect->setDeadline(100);
			pEffect->setTargetName( targetName );
			pEffect->setZone( pZone );

			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			pVampire->setFlag(Effect::EFFECT_CLASS_SOUL_CHAIN);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
			_GCSkillToSelfOK1.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_SOUL_CHAIN);

			_GCSkillToSelfOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pVampire);

			pSkillSlot->setRunTime(output.Delay);
		}
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 셀프
//////////////////////////////////////////////////////////////////////////////
void SoulChain::execute(Ousters* pOusters, const string& targetName, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);

		if ( pOusters->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
			|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) )
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL);
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pOusters->getX();
		ZoneCoord_t y = pOusters->getY();

		bool bValidTarget = false;
		__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

		Creature* pTarget = g_pPCFinder->getCreature_LOCKED( targetName );
		if ( pTarget != NULL )
		{
			Zone* pTargetZone = pTarget->getZone();
			if ( pTargetZone != NULL )
			{
				// Target 체크
				// 같은 종족이어야 한다.
				bool bOusters = pTarget->isOusters();
				// 일반 유저이여야 된다.
				bool bPLAYER = pTarget->getCompetence() == PLAYER;
				// 마스터 레어로는 이동할 수 없다.
				bool bMasterLair = pTargetZone->isMasterLair() || GDRLairManager::Instance().isGDRLairZone(pTargetZone->getZoneID());
				// 유료 서비스 사용이 가능한가?
				bool bValidPay = pGamePlayer->loginPayPlay( pGamePlayer->getSocket()->getHost(), pGamePlayer->getID() )
							|| pGamePlayer->isFamilyFreePass()
							|| !g_pZoneInfoManager->getZoneInfo( pTargetZone->getZoneID() )->isPayPlay();

				// 야전사령부, 시외곽지역, 이벤트경기장, 이벤트OX, 테메리에로는 갈 수 없다.
				bool bValidZone = pTargetZone->getZoneID() != 2101 && pTargetZone->getZoneID() != 2102 &&
								  pTargetZone->getZoneID() != 1005 && pTargetZone->getZoneID() != 1006 &&
								  pTargetZone->getZoneID() != 1122 && pTargetZone->getZoneID() != 1131 &&
								  pTargetZone->getZoneID() != 1132 && pTargetZone->getZoneID() != 1133 &&
								  pTargetZone->getZoneID() != 1134 && !pTargetZone->isCastleZone() &&
								  (!g_pWarSystem->hasActiveRaceWar() || !pTargetZone->isHolyLand()) && !pTargetZone->isCastle() && !pTargetZone->isMasterLair() &&
								  !g_pPKZoneInfoManager->isPKZone( pTargetZone->getZoneID() ) &&
								  // 다이나믹 존으로도 갈 수 없다.
								  !pTargetZone->isDynamicZone();

				bValidTarget = bOusters && bPLAYER && !bMasterLair && bValidPay && bValidZone;
			}
		}

		__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

		int  RequiredMP  = pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
//		bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);
//		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pSkillSlot);
		bool bEffected   = pOusters->isFlag(Effect::EFFECT_CLASS_SOUL_CHAIN) || 
							pOusters->hasRelicItem() || 
							pOusters->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) ||
							pOusters->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && !bEffected && bValidTarget)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pOusters, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);
		
			// 10 초 동안 움직일 수 없도록 이펙트를 붙인다.
			EffectSoulChain* pEffect = new EffectSoulChain( pOusters );
			pEffect->setDuration(output.Duration);
			pEffect->setDeadline(100);
			pEffect->setTargetName( targetName );
			pEffect->setZone( pZone );

			ObjectRegistry & objectregister = pZone->getObjectRegistry();
			objectregister.registerObject(pEffect);

			pZone->addEffect(pEffect);
			pOusters->setFlag(Effect::EFFECT_CLASS_SOUL_CHAIN);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
			_GCSkillToSelfOK1.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_SOUL_CHAIN);

			_GCSkillToSelfOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
		
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pOusters);

			pSkillSlot->setRunTime(output.Delay);
		}
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

SoulChain g_SoulChain;
