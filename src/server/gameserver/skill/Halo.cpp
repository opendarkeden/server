//////////////////////////////////////////////////////////////////////////////
// Filename    : Halo.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Halo.h"
#include "SimpleMissileSkill.h"
#include "EffectHalo.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Utility.h"

#define	HALO_BASIS_DIRECTION_LOW		0.35
#define	HALO_BASIS_DIRECTION_HIGH		3.0

static BYTE getDirection_Halo(int originX, int originY, int destX, int destY)
{
	int	stepX = destX - originX,
		stepY = destY - originY;

	// 0일 때 check
	float	k	= (stepX==0)? 0 : (float)(stepY) / stepX;	// 기울기
									

	//--------------------------------------------------
	// 방향을 정해야 한다.	
	//--------------------------------------------------
	if (stepY == 0)
	{
		// X축
		// - -;;
		if (stepX == 0)
			return DOWN;
		else if (stepX > 0)
			return RIGHT;
		else 
			return LEFT;
	}
	else
	if (stepY < 0)	// UP쪽으로
	{
		// y축 위
		if (stepX == 0)
		{
			return UP;
		}
		// 1사분면
		else if (stepX > 0)
		{
			if (k < -HALO_BASIS_DIRECTION_HIGH)
				return UP;
			else if (k <= -HALO_BASIS_DIRECTION_LOW)
				return RIGHTUP;
			else
				return RIGHT;
		}
		// 2사분면
		else
		{
			if (k > HALO_BASIS_DIRECTION_HIGH)
				return UP;
			else if (k >= HALO_BASIS_DIRECTION_LOW)
				return LEFTUP;
			else
				return LEFT;
		}
	}
	// 아래쪽
	else
	{		
		// y축 아래
		if (stepX == 0)
		{
			return DOWN;
		}
		// 4사분면
		else if (stepX > 0)
		{
			if (k > HALO_BASIS_DIRECTION_HIGH)
				return DOWN;
			else if (k >= HALO_BASIS_DIRECTION_LOW)
				return RIGHTDOWN;
			else
				return RIGHT;
		}
		// 3사분면
		else
		{
			if (k < -HALO_BASIS_DIRECTION_HIGH)
				return DOWN;
			else if (k <= -HALO_BASIS_DIRECTION_LOW)
				return LEFTDOWN;
			else
				return LEFT;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Halo::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
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
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMissileSkill.execute(pOusters, TargetObjectID, pOustersSkillSlot, param, result, CEffectID);

	if ( result.bSuccess )
	{
		cout << "Halo 성공" << endl;
		Dir_t dir = getDirection_Halo( pOusters->getX(), pOusters->getY(), result.pTargetCreature->getX(), result.pTargetCreature->getY() );

		ZoneCoord_t effectX = result.pTargetCreature->getX() + dirMoveMask[(int)dir].x*3;
		ZoneCoord_t effectY = result.pTargetCreature->getY() + dirMoveMask[(int)dir].y*3;

		Zone* pZone = pOusters->getZone();
		if ( isValidZoneCoord( pZone, effectX, effectY ) )
		{
			EffectHalo* pEffect = new EffectHalo( pZone, effectX, effectY );
			pEffect->setTargetOID( TargetObjectID );
			pEffect->setUserOID( pOusters->getObjectID() );
			pEffect->setDamage( output.Range );
			pEffect->setDeadline( output.Duration );
			pEffect->setNextTime( 10 );
			pEffect->setBroadcastingEffect(false);

			pZone->registerObject(pEffect);
			pZone->getTile(effectX, effectY).addEffect(pEffect);
			pZone->addEffect(pEffect);
		}
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH
}

Halo g_Halo;
