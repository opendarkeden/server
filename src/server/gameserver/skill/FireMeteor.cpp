//////////////////////////////////////////////////////////////////////////////
// Filename    : FireMeteor.cpp
// Written by  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "FireMeteor.h"
#include "RankBonus.h"
#include "EffectFireMeteor.h"
#include "SkillUtil.h"
#include "SimpleTileMissileSkill.h"

//////////////////////////////////////////////////////////////////////////////
// ¾Æ¿ì½ºÅÍÁî ¿ÀºêÁ§Æ® ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void FireMeteor::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
{
  __BEGIN_TRY

    //cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

    Assert(pOusters != NULL);
  Assert(pOustersSkillSlot != NULL);

  try
    {
      Zone* pZone = pOusters->getZone();
      Assert(pZone != NULL);

      Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
      //Assert(pTargetCreature != NULL);

      // NoSuch����. by sigi. 2002.5.2
      if (pTargetCreature==NULL
	  || !canAttack( pOusters, pTargetCreature )
	  )
	{
	  executeSkillFailException(pOusters, getSkillType());
	  return;
	}

      execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
    } 
  catch (Throwable & t) 
    {
      executeSkillFailException(pOusters, getSkillType());
    }

  __END_CATCH
    return;
}

void FireMeteor::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
{
  __BEGIN_TRY

    //cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

    SkillInput input(pOusters, pOustersSkillSlot);
  SkillOutput output;
  computeOutput(input, output);

  if (pOusters->hasRankBonus(RankBonus::RANK_BONUS_FIRE_ENDOW ) )
    {
      RankBonus* pRankBonus = pOusters->getRankBonus(RankBonus::RANK_BONUS_FIRE_ENDOW);
      Assert( pRankBonus != NULL );
      output.Damage += pRankBonus->getPoint();
    }
  // if (pOusters->hasRankBonus(RankBonus::RANK_BONUS_FIRE_OF_SPIRIT ) )
  //   {
  //     NewRankGem* pRankBonus = pOusters->getRankBonus(RankBonus::RANK_BONUS_FIRE_OF_SPIRIT);
  //     Assert( pRankBonus != NULL );

  //     bool isCri = HitRoll::isCriticalHit(pOusters, 200);
  //     if(isCri)
  // 	output.Damage += output.Damage*0.5;
  //   }


  SIMPLE_SKILL_INPUT param;
  param.SkillType     = getSkillType();
  param.SkillDamage   = output.Damage;
  param.Delay         = output.Delay;
  param.ItemClass     = Item::ITEM_CLASS_OUSTERS_WRISTLET;
  param.STRMultiplier = 0;
  param.DEXMultiplier = 0;
  param.INTMultiplier = 0;
  param.bMagicHitRoll = true;
  param.bMagicDamage  = true;
  param.bAdd          = false;
  param.Grade			= 0;

  SIMPLE_SKILL_OUTPUT result;

  int diff =2;

  for ( int i=-diff; i<=diff; ++i )
    for ( int j=-diff; j<=diff; ++j )
      param.addMask( i, j, 100 );

  return g_SimpleTileMissileSkill.execute(pOusters, X, Y, pOustersSkillSlot, param, result, CEffectID);

  __END_CATCH
    }

FireMeteor g_FireMeteor;
