//////////////////////////////////////////////////////////////////////////////
// Filename    : InfinityThunderbolt.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "InfinityThunderbolt.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
//#include "EffectInfinityThunderbolt.h"
#include "ZoneUtil.h"
#include "GCAddEffectToTile.h"
#include <list>

void InfinityThunderbolt::execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);
	
	Creature* pTargetCreature = pZone->getCreature(targetObjectID);
	//Assert(pTargetCreature != NULL);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetCreature==NULL)
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);

	__END_CATCH
}

void InfinityThunderbolt::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

//	cout << "(x,y)=" << X << "," << Y << endl;

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
	param.bExpForTotalDamage = false;

	for (int i=-1; i<=1; ++i )
	for (int j=-1; j<=1; ++j )
	{
		param.addMask(i, j, 100);
	}

	SIMPLE_SKILL_OUTPUT result;

	// 목표위치+4방향
/*	param.addMask(0 + dir_advance[dir][0],  0 + dir_advance[dir][1], 100);
	param.addMask(-1 + dir_advance[dir][0], -1 + dir_advance[dir][1], 100);
	param.addMask(0 + dir_advance[dir][0], -1 + dir_advance[dir][1], 100);
	param.addMask(1 + dir_advance[dir][0], -1 + dir_advance[dir][1], 100);
	param.addMask(-1 + dir_advance[dir][0],  0 + dir_advance[dir][1], 100);
	param.addMask(1 + dir_advance[dir][0],  0 + dir_advance[dir][1], 100);
	param.addMask(-1 + dir_advance[dir][0],  1 + dir_advance[dir][1], 100);
	param.addMask(0 + dir_advance[dir][0],  1 + dir_advance[dir][1], 100);
	param.addMask(1 + dir_advance[dir][0],  1 + dir_advance[dir][1], 100);*/

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

/*	if (result.bSuccess )
	{
		ZoneCoord_t tx = X+i;
		ZoneCoord_t ty = Y+j;

		if (!isValidZoneCoord(pZone, tx, ty) ) continue;
		Tile& rTile = pZone->getTile(tx, ty);
		if (!rTile.canAddEffect() ) continue;

		EffectInfinityThunderbolt* pEffect = new EffectInfinityThunderbolt(pZone, tx, ty);
		pEffect->setLevel(input.SkillLevel);
		pEffect->setDeadline(output.Duration);
		pZone->registerObject(pEffect);

		if (i != 0 || j != 0 ) pEffect->setBroadcastingEffect(false);
		else
		{
			GCAddEffectToTile gcAE;
			gcAE.setEffectID(pEffect->getSendEffectClass());
			gcAE.setXY(tx, ty);
			gcAE.setObjectID(pEffect->getObjectID());
			gcAE.setDuration(output.Duration);
			pZone->broadcastPacket(tx, ty, &gcAE);

//				cout << tx << ", " << ty << " Effect broadcast" << endl;
		}

		pZone->addEffect(pEffect);
		rTile.addEffect(pEffect);
//			cout << tx << ", " << ty << " add Effect" << endl;
	}
*/
	__END_CATCH
}

InfinityThunderbolt g_InfinityThunderbolt;

