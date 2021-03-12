//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyWave.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyWave.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
BloodyWave::BloodyWave()
	throw()
{
	__BEGIN_TRY

	m_pBloodyWaveMask[0].set(0,  -2);
	m_pBloodyWaveMask[1].set(-2,  0);
	m_pBloodyWaveMask[2].set(2,  0);
	m_pBloodyWaveMask[3].set(0,  2);
	m_pBloodyWaveMask[4].set(-1, -1);
	m_pBloodyWaveMask[5].set(0, -1);
	m_pBloodyWaveMask[6].set(1, -1);
	m_pBloodyWaveMask[7].set(-1,  0);
	m_pBloodyWaveMask[8].set(1,  0);
	m_pBloodyWaveMask[9].set(-1,  1);
	m_pBloodyWaveMask[10].set(0,  1);
	m_pBloodyWaveMask[11].set(1,  1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 셀프
//////////////////////////////////////////////////////////////////////////////
void BloodyWave::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		execute(pVampire, pVampire->getX(), pVampire->getY(), pVampireSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyWave::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

    try
    {
		//Zone* pZone = pVampire->getZone();
		//Assert(pZone != NULL);

		//Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		/*
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pVampire, getSkillType());

			return;
		}
		*/

		execute(pVampire, pVampire->getX(), pVampire->getY(), pVampireSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyWave::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	SkillInput input(pVampire);
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

	for (int i=0; i<maxBloodyWaveMask; i++)
	{
		param.addMask(m_pBloodyWaveMask[i].x, m_pBloodyWaveMask[i].y, 100);
	}

	// 강제로 knockback시킬 확률
	bool bForceKnockback = rand()%100 < output.ToHit;

    // Knowledge of Blood 가 있다면 hit bonus 10
	int HitBonus = 0;
	if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD ) )
	{
		RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD );
		Assert( pRankBonus != NULL );

		HitBonus = pRankBonus->getPoint();
	}

	g_SimpleTileMissileSkill.execute(pVampire, pVampire->getX(), pVampire->getY(), pVampireSkillSlot, param, result, 0, HitBonus, bForceKnockback);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyWave::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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

	for (int i=0; i<maxBloodyWaveMask; i++)
	{
		param.addMask(m_pBloodyWaveMask[i].x, m_pBloodyWaveMask[i].y, 100);
	}

	bool bForceKnockback = false;

	// 마스터는 강제로 knockback시킨다.
	if (pMonster->isMaster())
	{
		bForceKnockback = true;
	}

	g_SimpleTileMissileSkill.execute(pMonster, pMonster->getX(), pMonster->getY(), param, result, 0, bForceKnockback);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

BloodyWave g_BloodyWave;
