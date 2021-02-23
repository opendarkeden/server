//////////////////////////////////////////////////////////////////////////////
// Filename    : TurretFire.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "TurretFire.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include "ItemUtil.h"

void TurretFire::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	if ( !pSlayer->isFlag( Effect::EFFECT_CLASS_INSTALL_TURRET ) )
	{
		executeSkillFailException( pSlayer, getSkillType() );
	}

	Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	if (pWeapon == NULL || isArmsWeapon(pWeapon) == false )
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

	// 총알 숫자는 무조건 떨어뜨린다.
	Bullet_t RemainBullet = 0;
	if (bBulletCheck)
	{
		// 총알 숫자를 떨어뜨리고, 저장하고, 남은 총알 숫자를 받아온다.
		decreaseBullet(pWeapon);
		RemainBullet = getRemainBullet(pWeapon);
	}
	else
	{
		executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
		return;
	}

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = 0xffffffff;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 8;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
//	param.bExpForTotalDamage = true;

	SIMPLE_SKILL_OUTPUT result;

	// 목표위치+4방향
	param.addMask( 0,  0, 100);
	param.addMask(-1, -1, 100);
	param.addMask( 0, -1, 100);
	param.addMask( 1, -1, 100);
	param.addMask(-1,  0, 100);
	param.addMask( 1,  0, 100);
	param.addMask(-1,  1, 100);
	param.addMask( 0,  1, 100);
	param.addMask( 1,  1, 100);

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void TurretFire::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

	if (pTargetCreature!=NULL)
	{
		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	}
	else
	{
		executeSkillFailException(pSlayer, getSkillType());
	}


	__END_CATCH
}

TurretFire g_TurretFire;
