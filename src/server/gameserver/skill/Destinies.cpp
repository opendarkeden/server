//////////////////////////////////////////////////////////////////////////////
// Filename    : Destinies.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Destinies.h"
#include "SimpleMissileSkill.h"
#include "EffectDestinies.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Utility.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Destinies::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

	SkillInput input(pOusters, pOustersSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_WRISTLET;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMissileSkill.execute(pOusters, TargetObjectID, pOustersSkillSlot, param, result, CEffectID);

	if ( result.bSuccess )
	{
		cout << "Destinies 성공" << endl;
		if ( result.pTargetCreature->isOusters() ) return;

		EffectDestinies* pEffect = new EffectDestinies( pOusters );
		pEffect->setTargetType( result.pTargetCreature );
		pEffect->setDamage( output.Damage );
		pEffect->setNextTime( 10 );
		pEffect->setBroadcastingEffect(false);

		pOusters->addEffect( pEffect );
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH
}

Destinies g_Destinies;
