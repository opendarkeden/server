//////////////////////////////////////////////////////////////////////////////
// Filename    : WildTyphoon.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "WildTyphoon.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include <list>

const int dir_advance[8][2] =
{
	{ -1, 0 },
	{ -1, 1 },
	{  0, 1 },
	{  1, 1 },
	{  1, 0 },
	{  1,-1 },
	{  0,-1 },
	{ -1,-1 }
};

void WildTyphoon::execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error)
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

	execute( pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID );

	__END_CATCH
}

void WildTyphoon::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
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
	param.ItemClass     = Item::ITEM_CLASS_BLADE;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
	param.bExpForTotalDamage = false;

	Dir_t dir = getDirectionToPosition( pSlayer->getX(), pSlayer->getY(), X, Y );

	SIMPLE_SKILL_OUTPUT result;

	// 목표위치+4방향
	param.addMask( 0 + dir_advance[dir][0],  0 + dir_advance[dir][1], 100);
	param.addMask(-1 + dir_advance[dir][0], -1 + dir_advance[dir][1], 100);
	param.addMask( 0 + dir_advance[dir][0], -1 + dir_advance[dir][1], 100);
	param.addMask( 1 + dir_advance[dir][0], -1 + dir_advance[dir][1], 100);
	param.addMask(-1 + dir_advance[dir][0],  0 + dir_advance[dir][1], 100);
	param.addMask( 1 + dir_advance[dir][0],  0 + dir_advance[dir][1], 100);
	param.addMask(-1 + dir_advance[dir][0],  1 + dir_advance[dir][1], 100);
	param.addMask( 0 + dir_advance[dir][0],  1 + dir_advance[dir][1], 100);
	param.addMask( 1 + dir_advance[dir][0],  1 + dir_advance[dir][1], 100);

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	list<Creature*>::iterator itr = result.targetCreatures.begin();
	list<Creature*>::iterator endItr = result.targetCreatures.end();

	for ( ; itr != endItr ; ++itr )
	{
		Creature* pCreature = *itr;
		if (pCreature!=NULL)
		{
			// 몬스터인 경우만 delay를 추가한다.
			// player들은 client에서 처리하게 되어있다.
			int stunRatio = pSlayer->getSTR()/5;
			if (pCreature->isMonster() && (rand()%100) < stunRatio)
			{
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);

				// delay설정 ( + 2초 )
				if (!pMonster->isMaster()
#ifdef __UNDERWORLD__
						&& !pMonster->isUnderworld() && pMonster->getMonsterType() != 599
#endif
				)
				{
					Timeval delay;
					delay.tv_sec  = 2;
					delay.tv_usec = 0;//500000;
					pMonster->addAccuDelay(delay);
				}
			}
		}
	}

	__END_CATCH
}

WildTyphoon g_WildTyphoon;

//					if ( param.SkillType == SKILL_WILD_TYPHOON )
//					{
//						int ratio = pSlayer->getSTR() / 10;
//						if ( (rand()%100) < ratio )
//						{
//							_GCSkillToTileOK2.setSkillType( SKILL_ATTACK_MELEE );
//						}
//					}
//

