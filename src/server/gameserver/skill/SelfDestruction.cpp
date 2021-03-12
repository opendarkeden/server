//////////////////////////////////////////////////////////////////////////////
// Filename    : SelfDestruction.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SelfDestruction.h"
//#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "SimpleTileMissileSkill.h"
#include "EffectKillTimer.h"


//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
SelfDestruction::SelfDestruction()
	    throw()
{
	__BEGIN_TRY

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void SelfDestruction::execute(Monster* pMonster)
	
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


			for ( int i=-1; i<=1; ++i )
			for ( int j=-1; j<=1; ++j )
				param.addMask(i, j, 100);

			g_SimpleTileMissileSkill.execute(pMonster, x, y,
											param, result, 
											0, 
											false);

			if ( result.bSuccess )
			{
//				pMonster->setHP(0);
				EffectKillTimer* pEffect = new EffectKillTimer(pMonster);
				pEffect->setDeadline(8);
				pMonster->addEffect(pEffect);
			}
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

SelfDestruction g_SelfDestruction;
