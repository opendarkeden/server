//////////////////////////////////////////////////////////////////////////////
// Filename    : ShiftBreak.cpp
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Utility.h"
#include "ShiftBreak.h"
#include "SimpleTileMeleeSkill.h"
#include "ZoneUtil.h"
#include "Zone.h"
#include "EffectDarkness.h"

#include "Gpackets/GCDeleteEffectFromTile.h"

//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
ShiftBreak::ShiftBreak()
	throw()
{
	__BEGIN_TRY

	TPOINT mask[8];
	mask[0].x =  0;
	mask[0].y = -1;
	mask[1].x = -1;
	mask[1].y = -1;
	mask[2].x = -1;
	mask[2].y =  0;
	mask[3].x = -1;
	mask[3].y =  1;
	mask[4].x =  0;
	mask[4].y =  1;
	mask[5].x =  1;
	mask[5].y =  1;
	mask[6].x =  1;
	mask[6].y =  0;
	mask[7].x =  1;
	mask[7].y = -1;

	for ( int k = 0; k < 8; k++ )
	{
		int l = k;
		for ( int i = 1; i < 6; i++ )
		{
			if ( l == 8 )
				l = 0;

			m_pShiftBreakMask[k][i].set(mask[l].x , mask[l].y);
			++l;
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void ShiftBreak::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) 
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " begin(slayerobject)" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(slayerobject)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// ShiftBreak::execute()
//
//////////////////////////////////////////////////////////////////////
void ShiftBreak::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " begin" << endl;

	SkillInput input(pOusters, pOustersSkillSlot);
	SIMPLE_SKILL_INPUT param;

	if ( input.SkillLevel < 15 ) param.Grade = 0;
	else if ( input.SkillLevel < 30 ) param.Grade = 1;
	else param.Grade = 2;

	SkillOutput output;
	computeOutput(input, output);

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

	Dir_t dir = calcDirection( pOusters->getX(), pOusters->getY(), X, Y);

	for ( int i = 0 ; i < 6 ; i++ )
	{
		param.addMask(m_pShiftBreakMask[(int)dir][i].x, m_pShiftBreakMask[(int)dir][i].y, 100);
	}

	g_SimpleTileMeleeSkill.execute(pOusters, pOusters->getX(), pOusters->getY(), pOustersSkillSlot, param, result);

	list<TILE_MASK>::iterator itr = param.MaskList.begin();
	list<TILE_MASK>::iterator endItr = param.MaskList.end();

	Zone* pZone = pOusters->getZone();

	for ( ; itr != endItr ; ++itr )
	{
		int tx = pOusters->getX() + itr->x;
		int ty = pOusters->getY() + itr->y;
		if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;
		Tile& rTile = pZone->getTile( tx, ty );

		EffectDarkness* pEffect = dynamic_cast<EffectDarkness*>(rTile.getEffect( Effect::EFFECT_CLASS_DARKNESS ));
		if ( pEffect == NULL ) continue;

		int Ratio = pOusters->getLevel() + pOustersSkillSlot->getExpLevel() - (pEffect->getLevel()/3);
		Ratio = max( Ratio, 0 );

		if ( input.SkillLevel <= 15 )
		{
			Ratio += 40;
			Ratio = min( Ratio, 60 );
		}
		else
		{
			Ratio += 45;
			Ratio = min( Ratio, 75 );
		}

//		Ratio = min(30, Ratio);
//		if ( input.SkillLevel > 15 ) Ratio += 10;
//		Ratio = max(10, Ratio);

		cout << "다크니스 있음. 확률 " << Ratio << endl;

		if ( rand()%100 < Ratio )
		{
			cout << "성공 " << endl;
			pZone->deleteEffect( pEffect->getObjectID() );

			GCDeleteEffectFromTile gcDeleteEffectFromTile;
			gcDeleteEffectFromTile.setXY(tx, ty);
			gcDeleteEffectFromTile.setObjectID(pEffect->getObjectID());
			gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_DARKNESS);
			pZone->broadcastPacket(tx, ty, &gcDeleteEffectFromTile);
		}
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end" << endl;

	__END_CATCH
}

ShiftBreak g_ShiftBreak;
