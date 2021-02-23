//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonMonsters.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SummonMonsters.h"
#include "MonsterSummonInfo.h"
#include "ZoneUtil.h"
#include "MasterLairManager.h"
#include "MasterLairInfoManager.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSay.h"


//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
SummonMonsters::SummonMonsters()
	    throw()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
/*
void SummonMonsters::execute(Vampire* pVampire, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
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

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pVampire->getX();
		ZoneCoord_t y = pVampire->getY();

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll       = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot);
		bool bTileCheck     = canBurrow(pZone, x, y);
		bool bMoveModeCheck = pVampire->isWalking();
		bool bEffected      = pVampire->isFlag(Effect::EFFECT_CLASS_HIDE);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck && bMoveModeCheck && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);
			
			// 뱀파이어를 땅 위에서 삭제하기 이전에 기술 패킷들을 날린다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
		
			_GCSkillToSelfOK2.setXY(x, y);
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2, pVampire);

			// 땅 위에 나와있는 뱀파이어 삭제하라고 알린다.
			GCDeleteObject gcDO;
			gcDO.setObjectID(pVampire->getObjectID());
			pZone->broadcastPacket(x, y, &gcDO, pVampire);

			// 땅 속에다가 뱀파이어를 추가한다.
			addBurrowingCreature(pZone, pVampire, x, y);
			
			pSkillSlot->setRunTime();
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
*/

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void SummonMonsters::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	//cout << "SummonMonsters" << endl;

	Assert(pMonster != NULL);
	Zone* pZone = pMonster->getZone();
	Assert(pZone != NULL);


	try 
	{
		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "SummonMonsters: hide" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		//GCSkillToSelfOK2 _GCSkillToSelfOK2;

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);
		//bool bMoveModeCheck = pMonster->isWalking();

		if (bRangeCheck)// && bMoveModeCheck)
		{
			//--------------------------------------------------------
			// 주위에 knockback되는맞는 애들을 체크해준다.
			//--------------------------------------------------------
			//SkillInput input(pMonster);
			//SkillOutput output;
			//computeOutput(input, output);

			SUMMON_INFO2 summonInfo;

			bool hasInfo = pMonster->getMonsterSummonInfo( summonInfo );

			if (!hasInfo || summonInfo.pMonsters==NULL)
			{
				//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
				// 소환할 몹이 없는 경우다. -_-;
				executeSkillFailNormal(pMonster, getSkillType(), NULL);

				// 마스터 레어에서 마스터가 몹을 소환할려고 한 경우
				if (pZone->isMasterLair() && pMonster->isMaster())
				{
					MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
					Assert(pMasterLairManager!=NULL);

					// 더 이상 소환할게 없다면..
					// 마스터가 직접 나서서 싸워야겠지..
					pMasterLairManager->setMasterReady();
					//cout << "no more SummonMonsters: set MasterReady" << endl;
				}
			}

			if (pMonster->isMaster() && pZone->isMasterLair())
			{
				MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
				Assert(pMasterLairManager!=NULL);
				// minion combat에서는 지정된 좌표에 소환한다.

				MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( pZone->getZoneID() );
				Assert(pInfo!=NULL);

				if (!pMasterLairManager->isMasterReady())
				{
					x = pInfo->getSummonX();
					y = pInfo->getSummonY();

					GCSay gcSay;
					gcSay.setObjectID( pMonster->getObjectID() );
					gcSay.setColor( MASTER_SAY_COLOR );
					gcSay.setMessage( pInfo->getRandomMasterSummonSay() );
					if (!gcSay.getMessage().empty())
						pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &gcSay);
				}

				// 마스터 레어에서는 소환된 몬스터들이 아템 안 준다.
				// by sigi. 2002.11.21
				summonInfo.hasItem = false;
			}

			summonInfo.scanEnemy = true;
			summonInfo.clanType = SUMMON_INFO::CLAN_TYPE_GROUP;
			summonInfo.clanID = pMonster->getClanType(); // 주인의 clan을 따른다.
			summonInfo.X = x;
			summonInfo.Y = y;
			summonInfo.regenType = REGENTYPE_PORTAL;

			// 몬스터를 존에 추가한다.
			addMonstersToZone( pZone, summonInfo );

			//cout << "SummonMonsters OK" << endl;
			GCSkillToTileOK5 _GCSkillToTileOK5;

			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setX(x);
			_GCSkillToTileOK5.setY(y);
			_GCSkillToTileOK5.setDuration(  0);

			pZone->broadcastPacket(x, y,  &_GCSkillToTileOK5);
		}
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	__END_CATCH

}

SummonMonsters g_SummonMonsters;
