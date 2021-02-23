#include "EffectCastingTrap.h"
#include "EffectWithWarning.h"
#include "Utility.h"
#include "ZoneUtil.h"
#include "Tile.h"
#include "Zone.h"

void EffectCastingIcicleTrap::affect() throw(Error)
{
	__BEGIN_TRY

	for ( int i=0; i<m_Unit; ++i )
	{
		ZoneCoord_t x, y;

//		cout << "EffectCastingIcicleTrap::affect" << endl;

		// 100번 찾아도 안되면 관둔다.
		for ( int j=0; j<100; ++j )
		{
			int offset = rand()%m_Length;
			Dir_t dir90 = (m_Dir+2)%8;
			int pitch = (rand()%7)-3;
			int scatterX = (rand()%3)-1;
			int scatterY = (rand()%3)-1;

			x = m_StartX + dirMoveMask[m_Dir].x*offset + dirMoveMask[dir90].x*pitch + scatterX;
			y = m_StartY + dirMoveMask[m_Dir].y*offset + dirMoveMask[dir90].y*pitch + scatterY;

			if ( isValidZoneCoord( m_pZone, x, y ) )
			{
				if ( m_pZone->getTile(x, y).canAddEffect()
						&& m_pZone->getTile(x, y).getEffect(m_IcicleEffect) == NULL 
						&& m_pZone->getTile(x, y).getEffect((EffectClass)(m_IcicleEffect+1)) == NULL 
						&& !m_pZone->getTile(x, y).isFixedGroundBlocked() ) break;
			}

			if ( j == 9 )
			{
				setNextTime( m_Tick );
				return;
			}
		}

//		cout << x << ", " << y << " 에 이펙트 붙일께용" << endl;

		if ( m_bLarge )
		{
			EffectLargeIcicle *pEffectLargeIcicle = new EffectLargeIcicle( m_IcicleEffect, m_pZone, x, y );
			pEffectLargeIcicle->setSignDuration(5);
			pEffectLargeIcicle->setMainDuration(20);
			m_pZone->registerObject( pEffectLargeIcicle );
			m_pZone->addEffect( pEffectLargeIcicle );
			m_pZone->getTile(x, y).addEffect(pEffectLargeIcicle);
			pEffectLargeIcicle->start();
		}
		else
		{
			EffectIcicle *pEffectIcicle = new EffectIcicle( m_IcicleEffect, m_pZone, x, y );
			pEffectIcicle->setSignDuration(5);
			pEffectIcicle->setMainDuration(20);
			m_pZone->registerObject( pEffectIcicle );
			m_pZone->addEffect( pEffectIcicle );
			m_pZone->getTile(x, y).addEffect(pEffectIcicle);
			pEffectIcicle->start();
		}
	}

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectCastingSideTrap::affect() throw(Error)
{
	__BEGIN_TRY

	for ( int i=0; i<m_Unit; ++i )
	{
		ZoneCoord_t x, y;
		Dir_t dir180;
		int j=0;

		while ( true )
		{
			int offset = rand()%m_Length;
			dir180 = (((int)m_Dir) + (int)(((rand()%2)-0.5)*4)+8)%8;

			x = m_StartX + dirMoveMask[m_Dir].x*offset - dirMoveMask[dir180].x*4;
			y = m_StartY + dirMoveMask[m_Dir].y*offset - dirMoveMask[dir180].y*4;

			if ( isValidZoneCoord( m_pZone, x, y ) )
			{
				if ( m_pZone->getTile(x, y).canAddEffect() &&
//					!m_pZone->getTile(x, y).hasEffect() &&
					m_pZone->getTile(x, y).getEffect((Effect::EffectClass)(Effect::EFFECT_CLASS_ICE_STICK_SW + dir180 - 1)) == NULL &&
					m_pZone->getTile(x, y).getEffect((Effect::EffectClass)(Effect::EFFECT_CLASS_ICE_STICK_SW + dir180)) == NULL &&
//					!m_pZone->getTile(x + dirMoveMask[dir180].x*8, y + dirMoveMask[dir180].y*8).hasEffect() &&
					m_pZone->getTile(x + dirMoveMask[dir180].x*8, y + dirMoveMask[dir180].y*8).getEffect((Effect::EffectClass)(Effect::EFFECT_CLASS_ICE_STICK_SW + ((dir180+4)%8) - 1)) == NULL &&
					m_pZone->getTile(x + dirMoveMask[dir180].x*8, y + dirMoveMask[dir180].y*8).getEffect((Effect::EffectClass)(Effect::EFFECT_CLASS_ICE_STICK_SW + ((dir180+4)%8))) == NULL
				) break;
			}

			j++;
			if ( j == 9 )
			{
				setNextTime( m_Tick );
				return;
			}
//			cout << m_pZone->getZoneID() << " : " << x << ", " << y << endl;
		}

		EffectSideTrap *pEffectSideTrap = new EffectSideTrap( (Effect::EffectClass)(Effect::EFFECT_CLASS_ICE_STICK_SW + dir180 - 1), m_pZone, x, y );
		pEffectSideTrap->setSignDuration(10);
		pEffectSideTrap->setMainDuration(30);
		pEffectSideTrap->setDir( dir180 );
		m_pZone->registerObject( pEffectSideTrap );
		m_pZone->getTile(x, y).addEffect(pEffectSideTrap);
		m_pZone->addEffect( pEffectSideTrap );
		pEffectSideTrap->start();
	}

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectCastingIceWall::affect() throw(Error)
{
	__BEGIN_TRY

	int trapCount = m_Length / m_WallLength;
	int pitch = 0;

	for ( int i=0; i<trapCount; ++i )
	{
		ZoneCoord_t iX = m_StartX + dirMoveMask[m_Dir].x*i*m_WallLength;
		ZoneCoord_t iY = m_StartY + dirMoveMask[m_Dir].y*i*m_WallLength;

		for ( int j=0; j<m_WallLength; ++j )
		{
			ZoneCoord_t tX = iX + dirMoveMask[m_Dir].x*j;
			ZoneCoord_t tY = iY + dirMoveMask[m_Dir].y*j + m_State - pitch;

			for ( int k=-2; k<=2; ++k )
			{
//				ZoneCoord_t X = tX + dirMoveMask[(m_Dir+2)%8].x*k*2;
				ZoneCoord_t X = tX;
				ZoneCoord_t Y = tY + k*3;

				if ( isValidZoneCoord( m_pZone, X, Y ) && m_pZone->getTile( X, Y ).canAddEffect() && !m_pZone->getTile(X, Y).isFixedGroundBlocked() )
				{
					EffectIcicle *pEffectIcicle = new EffectIcicle( Effect::EFFECT_CLASS_ICICLE_AUGER, m_pZone, X, Y );
					pEffectIcicle->setSignDuration(5);
					pEffectIcicle->setMainDuration(20);
					m_pZone->registerObject( pEffectIcicle );
					m_pZone->addEffect( pEffectIcicle );
					m_pZone->getTile(X, Y).addEffect(pEffectIcicle);
					pEffectIcicle->start();
				}
			}
		}

		pitch = (pitch+1)%2;
	}

	m_State = (m_State+1)%2;
	setNextTime(m_Tick);

	__END_CATCH
}
