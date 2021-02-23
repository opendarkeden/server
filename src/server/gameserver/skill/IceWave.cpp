//////////////////////////////////////////////////////////////////////////////
// Filename    : IceWave.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "IceWave.h"
//#include "Gpackets/GCSkillToSelfOK1.h"
//#include "Gpackets/GCSkillToSelfOK2.h"
#include "SimpleTileMeleeSkill.h"
#include "Utility.h"
#include "Gpackets/GCAddEffectToTile.h"


//////////////////////////////////////////////////////////////////////////////
// 생성자
// 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
IceWave::IceWave()
	    throw()
{
	__BEGIN_TRY

	int index=0;

	for ( int i=-3; i<=3; ++i )
	{
		for ( int j=-3; j<=3; ++j )
		{
			filelog("IceWave.log", "%d:(%d,%d)", index, i, j );
			m_pIceWaveMask[index++].set( i, j );
		}
	}

	for ( int i=0; i<8; ++i )
	{
		for ( int j=1; j<=2; ++j )
		{
			int ox = dirMoveMask[i].x * j * 3 + dirMoveMask[i].x * 2;
			int oy = dirMoveMask[i].y * j * 3 + dirMoveMask[i].y * 2;

			for ( int k=-1; k<=1; ++k )
			{
				for ( int l=-1; l<=1; ++l )
				{
					filelog("IceWave.log", "%d:(%d,%d)", index, ox+k, oy+l );
					m_pIceWaveMask[index++].set( ox+k, oy+l );
				}
			}
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void IceWave::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		int dx = (rand()%7)-3;
		int dy = (rand()%7)-3;

		X -= min((int)X, dx);
		Y -= min((int)Y, dy);

		if ( X > pZone->getWidth() ) X = pZone->getWidth()-1;
		if ( Y > pZone->getHeight() ) Y = pZone->getHeight()-1;

		pZone->moveFastMonster( pMonster, pMonster->getX(), pMonster->getY(), X, Y, getSkillType() );

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);
		bool bMoveModeCheck = pMonster->isWalking();

		if (bRangeCheck && bMoveModeCheck)
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

			for ( int i=0; i<8; ++i )
			{
				for ( int j=0; j<3; ++j )
				{
					int ox = pMonster->getX() + dirMoveMask[i].x * j * 3 + dirMoveMask[i].x * 2;
					int oy = pMonster->getY() + dirMoveMask[i].y * j * 3 + dirMoveMask[i].y * 2;

					GCAddEffectToTile gcAE;
					gcAE.setXY( ox, oy );
					gcAE.setEffectID( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE );
					gcAE.setDuration( 15 );
					pMonster->getZone()->broadcastPacket( ox, oy, &gcAE );
				}
			}

			for (int i=0; i<193; i++)
			{
				if ((abs((int)x - (int)m_pIceWaveMask[i].x) <= 2) && (abs((int)y - (int)m_pIceWaveMask[i].y) <= 2))
					param.addMask(m_pIceWaveMask[i].x, m_pIceWaveMask[i].y, 80);
				else
					param.addMask(m_pIceWaveMask[i].x, m_pIceWaveMask[i].y, 100);
			}

			// 강제로 맞는 애들을 knockback 시킨다.
			bool bForceKnockback = false;
			g_SimpleTileMeleeSkill.execute(pMonster, x, y,
											param, result, 
											0, 
											bForceKnockback);
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

IceWave g_IceWave;
