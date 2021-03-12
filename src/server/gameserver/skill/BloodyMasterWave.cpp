//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyMasterWave.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyMasterWave.h"
#include "SimpleTileMissileSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
BloodyMasterWave::BloodyMasterWave()
	throw()
{
	__BEGIN_TRY

	m_pBloodyMasterWaveMask[0].set(0,  -3);
	m_pBloodyMasterWaveMask[1].set(-3,  0);
	m_pBloodyMasterWaveMask[2].set(3,  0);
	m_pBloodyMasterWaveMask[3].set(0,  3);

	m_pBloodyMasterWaveMask[4].set(-2, -1);
	m_pBloodyMasterWaveMask[5].set(-2,  1);
	m_pBloodyMasterWaveMask[6].set(-1,  -2);
	m_pBloodyMasterWaveMask[7].set(-1,  2);
	m_pBloodyMasterWaveMask[8].set(1,  -2);
	m_pBloodyMasterWaveMask[9].set(1,  2);
	m_pBloodyMasterWaveMask[10].set(2,  -1);
	m_pBloodyMasterWaveMask[11].set(2,  1);

	m_pBloodyMasterWaveMask[12].set(0,  -2);
	m_pBloodyMasterWaveMask[13].set(-2,  0);
	m_pBloodyMasterWaveMask[14].set(2,  0);
	m_pBloodyMasterWaveMask[15].set(0,  2);

	m_pBloodyMasterWaveMask[16].set(-1, -1);
	m_pBloodyMasterWaveMask[17].set(0, -1);
	m_pBloodyMasterWaveMask[18].set(1, -1);
	m_pBloodyMasterWaveMask[19].set(-1,  0);

	m_pBloodyMasterWaveMask[20].set(1,  0);
	m_pBloodyMasterWaveMask[21].set(-1,  1);
	m_pBloodyMasterWaveMask[22].set(0,  1);
	m_pBloodyMasterWaveMask[23].set(1,  1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 셀프
//////////////////////////////////////////////////////////////////////////////
void BloodyMasterWave::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
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
        ////cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyMasterWave::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
    
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
void BloodyMasterWave::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
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

	for (int i=0; i<maxBloodyMasterWaveMask; i++)
	{
		param.addMask(m_pBloodyMasterWaveMask[i].x, m_pBloodyMasterWaveMask[i].y, 100);
	}

	// 강제로 knockback시킬 확률
    bool bForceKnockback = rand()%100 < output.ToHit;

	g_SimpleTileMissileSkill.execute(pVampire, pVampire->getX(), pVampire->getY(), pVampireSkillSlot, param, result, 0, bForceKnockback);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 타일 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyMasterWave::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	
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

	for (int i=0; i<maxBloodyMasterWaveMask; i++)
	{
		param.addMask(m_pBloodyMasterWaveMask[i].x, m_pBloodyMasterWaveMask[i].y, 100);
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

BloodyMasterWave g_BloodyMasterWave;
