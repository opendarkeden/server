//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodyWall.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectBloodyWall.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBloodyWall::EffectBloodyWall(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_CasterName ="";
	m_CasterID = 0;
	m_PartyID = 0;

	m_CreatureClass = Creature::CREATURE_CLASS_VAMPIRE;
	m_ClanID = 0;

	m_bForce = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWall::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBloodyWall" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 이펙트를 사용한 크리쳐를 가져온다.
	// !! 이미 존을 나갔을 수도 있으므로 NULL이 될 수 있다.
	// by bezz. 2003.1.4
	Creature *pCastCreature = m_pZone->getCreature( m_CasterID );

	// 현재 이펙트가 붙어있는 타일을 받아온다.
    Tile& tile = m_pZone->getTile(m_X, m_Y);

	// 타일 안에 존재하는 오브젝트들을 검색한다.
    const slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::const_iterator itr = oList.begin();
    for (; itr != oList.end(); itr++) 
	{
		Assert(*itr != NULL);

		Object* pObject = *itr;
		Assert(pObject != NULL);

    	if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature != NULL);

			// 무적상태 체크. by sigi. 2002.9.5
			// 산 면역. by sigi. 2002.9.13
			// 자기 자신이면 안 맞는다.
			// 안전지대 체크
			// 2003.1.10 by bezz, Sequoia
			if ( !canAttack( pCastCreature, pCreature )
				|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
				|| pCreature->getObjectID()==m_CasterID
				|| !checkZoneLevelToHitTarget( pCreature )
			)
			{
				continue;
			}
			
			// 같은 조직(--;)이면 안 맞는다.
			if (m_CreatureClass==pCreature->getCreatureClass() && !isForce())
			{
				// vampire 끼리는 안 맞는다.
				if (m_CreatureClass==Creature::CREATURE_CLASS_VAMPIRE)
				{
					continue;	// by sigi. 2003.1.14
				}
				else if (m_CreatureClass==Creature::CREATURE_CLASS_MONSTER)
				{
					Creature* pAttacker = m_pZone->getCreature( m_CasterID );
					if (pAttacker!=NULL && pAttacker->isMonster())
					{
						Monster* pAttackMonster = dynamic_cast<Monster*>(pAttacker);
						Monster* pDefendMonster = dynamic_cast<Monster*>(pCreature);

						if (pAttackMonster->getClanType()==pDefendMonster->getClanType())
						{
							continue;
						}
					}
				}
			}

			int Damage = m_Damage;

			if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
			{
				if (pCreature->isSlayer()) 
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

					GCModifyInformation gcMI;
					::setDamage( pSlayer, Damage, pCastCreature, SKILL_BLOODY_WALL, &gcMI );

					Player* pPlayer = pSlayer->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					// knockback체크
					bool bKnockback = rand()%100 < 50;	// 20%의 확률로 knockback
					if (bKnockback)
					{
						int x = pCreature->getX() + rand()%3 - 1;
						int y = pCreature->getY() + rand()%3 - 1;
						knockbackCreature(m_pZone, pCreature, x, y);
						// Tile의 oList를 바뀌게 하므로 더 체크하지 않는다. 
						// 한 타일에서 하나가 knockback되면 뒤에 체크할 애들은 안 맞아도 관계없지~
						break;
					}
				} 
				else if (pCreature->isVampire())
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

					GCModifyInformation gcMI;
					::setDamage( pVampire, Damage, pCastCreature, SKILL_BLOODY_WALL, &gcMI );

					Player* pPlayer = pVampire->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					// knockback체크
					bool bKnockback = rand()%100 < 50;	// 20%의 확률로 knockback
					if (bKnockback)
					{
						int x = pCreature->getX() + rand()%3 - 1;
						int y = pCreature->getY() + rand()%3 - 1;
						knockbackCreature(m_pZone, pCreature, x, y);
						// Tile의 oList를 바뀌게 하므로 더 체크하지 않는다. 
						// 한 타일에서 하나가 knockback되면 뒤에 체크할 애들은 안 맞아도 관계없지~
						break;
					}
				}
				else if (pCreature->isOusters())
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

					GCModifyInformation gcMI;
					::setDamage( pOusters, Damage, pCastCreature, SKILL_BLOODY_WALL, &gcMI );

					Player* pPlayer = pOusters->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					// knockback체크
					bool bKnockback = rand()%100 < 50;	// 20%의 확률로 knockback
					if (bKnockback)
					{
						int x = pCreature->getX() + rand()%3 - 1;
						int y = pCreature->getY() + rand()%3 - 1;
						knockbackCreature(m_pZone, pCreature, x, y);
						// Tile의 oList를 바뀌게 하므로 더 체크하지 않는다. 
						// 한 타일에서 하나가 knockback되면 뒤에 체크할 애들은 안 맞아도 관계없지~
						break;
					}
				}
				else if (pCreature->isMonster())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, Damage, pCastCreature, SKILL_BLOODY_WALL );

					if ( pCastCreature != NULL && pCastCreature->isPC() )
					{
						pMonster->addEnemy( pCastCreature );
					}

					// knockback체크
					bool bKnockback = rand()%100 < 50;	// 20%의 확률로 knockback
					if (bKnockback)
					{
						int x = pCreature->getX() + rand()%3 - 1;
						int y = pCreature->getY() + rand()%3 - 1;
						knockbackCreature(m_pZone, pCreature, x, y);
						// Tile의 oList를 바뀌게 하므로 더 체크하지 않는다. 
						// 한 타일에서 하나가 knockback되면 뒤에 체크할 애들은 안 맞아도 관계없지~
						break;
					}
				}

				// 상대가 죽었다면 경험치를 올려준다.
				if ( pCreature->isDead() )
				{
					if ( pCastCreature != NULL && pCastCreature->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCastCreature);
						Assert( pVampire != NULL );

						GCModifyInformation gcAttackerMI;
						int exp = computeCreatureExp(pCreature, KILL_EXP);
						shareVampExp(pVampire, exp, gcAttackerMI);

						pVampire->getPlayer()->sendPacket( &gcAttackerMI );
					}
				}

				// m_CasterName이 pCreature를 죽인 경우의 KillCount 처리
				// by sigi. 2002.8.31
				// setDamage 를 호출하여 해결한다. 주석처리
				// by bezz. 2003.1.3
/*				if (pCreature->isDead())
				{
					Creature* pAttacker = m_pZone->getCreature( m_CasterID );

					if (pAttacker!=NULL)
					{ 
						affectKillCount(pAttacker, pCreature);
					}
				}*/
			}
		}
	}
	
	setNextTime(m_Tick);

	//cout << "EffectBloodyWall" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWall::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWall::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWall::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWall::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBloodyWall" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectBloodyWall" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBloodyWall::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBloodyWall::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectBloodyWall("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

/*
void EffectBloodyWallLoader::load(Zone* pZone)
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT LeftX, TopY, RightX, BottomY, Value1, Value2, Value3 FROM ZoneEffectInfo WHERE ZoneID = %d AND EffectID = %d", pZone->getZoneID(), (int)Effect::EFFECT_CLASS_BLOODY_WALL);

		while (pResult->next())
		{
			int count = 0;
			
			ZoneCoord_t left 	= pResult->getInt( ++count );
			ZoneCoord_t top 	= pResult->getInt( ++count );
			ZoneCoord_t right 	= pResult->getInt( ++count );
			ZoneCoord_t	bottom	= pResult->getInt( ++count );
			int 		value1	= pResult->getInt( ++count );
			int 		value2	= pResult->getInt( ++count );
			int 		value3	= pResult->getInt( ++count );

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			for ( int X = left ; X <= right ; X++ )
			for ( int Y = top ; Y <= bottom ; Y++ )
			{
				if ( rect.ptInRect(X, Y) )
				{
					Tile& tile = pZone->getTile(X,Y);
					if ( tile.canAddEffect() ) 
					{
						EffectBloodyWall* pEffect = new EffectBloodyWall(pZone, X, Y);
						pEffect->setDamage( value3 );
						pEffect->setTick( value2 );
						pEffect->setLevel( 300 );

						// 존 및 타일에다가 이펙트를 추가한다.
						pZone->registerObject(pEffect);
						pZone->addEffect(pEffect);
						tile.addEffect(pEffect);

					}

				}
			}

		}
	}
	END_DB(pStmt)

	__END_CATCH
}

EffectBloodyWallLoader* g_pEffectBloodyWallLoader = NULL;
*/
