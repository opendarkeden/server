//////////////////////////////////////////////////////////////////////////////
// Filename    : SweepVice.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SweepVice.h"
#include "Assert.h"
#include "Zone.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"

void SweepVice::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuchÁ¦°Å. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());

			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
        //cout << t.toString() << endl;
    }

	__END_CATCH
}

void SweepVice::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	cout << pSlayer->getName() << " use sweep vice level " << m_Level << endl;

	SkillInput input(pSlayer, pSkillSlot);
	input.Range = m_Level;
	SkillOutput output;
	computeOutput(input, output);

	cout << "Damage : " << output.Damage << endl;

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MACE;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;
//	param.bExpForTotalDamage = true;

	SIMPLE_SKILL_OUTPUT result;

	for ( int i=-m_Level; i<=m_Level; ++i )
	for ( int j=-m_Level; j<=m_Level; ++j )
		param.addMask( i, j, 100 );

	param.Grade = m_Level;
	
	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	__END_CATCH
}

SweepVice g_SweepVice1(0);
SweepVice g_SweepVice3(1);
SweepVice g_SweepVice5(2);
