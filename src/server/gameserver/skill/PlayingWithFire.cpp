//////////////////////////////////////////////////////////////////////////////
// Filename    : PlayingWithFire.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PlayingWithFire.h"
//#include "Gpackets/GCSkillToSelfOK1.h"
//#include "Gpackets/GCSkillToSelfOK2.h"
#include "SimpleTileMeleeSkill.h"


//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
PlayingWithFire::PlayingWithFire()
	    throw()
{
	__BEGIN_TRY

	// 주위 8타일
	m_pPlayingWithFireMask[0].set(1,  1);
	m_pPlayingWithFireMask[1].set(-1, -1);
	m_pPlayingWithFireMask[2].set(0, -1);
	m_pPlayingWithFireMask[3].set(1, -1);
	m_pPlayingWithFireMask[4].set(-1,  0);
	m_pPlayingWithFireMask[5].set(1,  0);
	m_pPlayingWithFireMask[6].set(-1,  1);
	m_pPlayingWithFireMask[7].set(0,  1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
/*
void PlayingWithFire::execute(Vampire* pVampire, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
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
void PlayingWithFire::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
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
		bool bMoveModeCheck = pMonster->isWalking();

		if (bRangeCheck && bMoveModeCheck)
		{
			//--------------------------------------------------------
			// Critical Ground 기술을 보이게 한다.
			//--------------------------------------------------------
			//_GCSkillToSelfOK2.setObjectID(pMonster->getObjectID());
			//_GCSkillToSelfOK2.setDuration(0);
			//_GCSkillToSelfOK2.setSkillType(getSkillType());
			//pZone->broadcastPacket(x, y, &_GCSkillToSelfOK2);


			//--------------------------------------------------------
			// 주위에 knockback되는맞는 애들을 체크해준다.
			//--------------------------------------------------------
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			SIMPLE_SKILL_INPUT param;
			param.SkillType     = getSkillType();
			param.SkillDamage   = output.Damage;
			param.Delay         = output.Delay;
			param.ItemClass     = Item::ITEM_CLASS_MAX;
			param.STRMultiplier = 0;
			param.DEXMultiplier = 0;
			param.INTMultiplier = 0;
			param.bMagicHitRoll = true;
			param.bMagicDamage  = true;
			param.bAdd          = false;

			SIMPLE_SKILL_OUTPUT result;

		/*	for (int i=0; i<8; i++)
			{
				param.addMask(m_pPlayingWithFireMask[i].x, m_pPlayingWithFireMask[i].y, 100);
			}
		*/
			for ( int i=-10; i<=10; ++i )
				for ( int j=-10; j<=10; ++j )
					param.addMask(i, j, 100);
			

			// 강제로 맞는 애들을 knockback 시킨다.
			bool bForceKnockback = true;
			g_SimpleTileMeleeSkill.execute(pMonster, x, y,
											param, result, 
											0, 
											bForceKnockback);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

PlayingWithFire g_PlayingWithFire;
