//////////////////////////////////////////////////////////////////////////////
// Filename    : ClaymoreExplosion.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ClaymoreExplosion.h"
//#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "SimpleTileMeleeSkill.h"


//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
ClaymoreExplosion::ClaymoreExplosion()
	    throw()
{
	__BEGIN_TRY

	int index=0;

	for ( int i=0; i<5; ++i )
		for ( int j=i-4; j<=0; ++j )
		{
//			if ( i==0 && j==0 ) continue;
			m_pClaymoreExplosionMask[index++].set(j, i);
		}

	// 주위 8타일
/*	m_pClaymoreExplosionMask[0].set(1,  1);
	m_pClaymoreExplosionMask[1].set(-1, -1);
	m_pClaymoreExplosionMask[2].set(0, -1);
	m_pClaymoreExplosionMask[3].set(1, -1);
	m_pClaymoreExplosionMask[4].set(-1,  0);
	m_pClaymoreExplosionMask[5].set(1,  0);
	m_pClaymoreExplosionMask[6].set(-1,  1);
	m_pClaymoreExplosionMask[7].set(0,  1);*/

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void ClaymoreExplosion::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		//GCSkillToSelfOK2 _GCSkillToSelfOK2;

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);

		if (bRangeCheck)
		{
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

			for (int i=0; i<15; i++)
			{
				param.addMask(m_pClaymoreExplosionMask[i].x, m_pClaymoreExplosionMask[i].y, 100);
			}

			// 강제로 맞는 애들을 knockback 시킨다.
		//	bool bForceKnockback = true;
			g_SimpleTileMeleeSkill.execute(pMonster, x, y,
											param, result, 
											0, 
											false);
			GCAddEffectToTile gcAE;
			gcAE.setXY(x, y);
			gcAE.setEffectID(Effect::EFFECT_CLASS_CLAYMORE_EXPLOTION);
			gcAE.setObjectID(0);
			gcAE.setDuration(0);
			pZone->broadcastPacket( x, y, &gcAE );
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

ClaymoreExplosion g_ClaymoreExplosion;
