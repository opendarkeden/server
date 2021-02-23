//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHarpoonBomb.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectHarpoonBomb.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK2.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHarpoonBomb::EffectHarpoonBomb(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectHarpoonBomb::EffectHarpoonBomb(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y)
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;
	m_UserObjectID = 0;
	m_bBroadcastingEffect = false;

	__END_CATCH
}

void EffectHarpoonBomb::crash(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y)
{
	cout << "crashing " << X << ", " << Y << endl;
	Assert(pZone != NULL);
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );

	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

	GCAddEffectToTile gcAE;
	gcAE.setEffectID( getSendEffectClass() );
	gcAE.setObjectID( getObjectID() );
	gcAE.setDuration( 10 );
	gcAE.setXY( X, Y );
	pZone->broadcastPacket( X, Y, &gcAE );

	for( int x = -1; x <= 1; x++)
	{
		for(int y= -1; y <= 1; y++)
		{
			if(!rect.ptInRect(X+x, Y+y)) continue;
			Tile& tile = pZone->getTile(X+x, Y+y);
			
			const slist<Object*>& oList = tile.getObjectList();
			slist<Object*>::const_iterator itr = oList.begin();
			for(; itr != oList.end(); itr++)
			{
				Object* pObject = *itr;
				Assert(pObject != NULL);

				if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					Creature* pCreature = dynamic_cast<Creature*>(pObject);
					Assert(pCreature != NULL);

					// ÀÚ½ÅÀº ¸ÂÁö ¾Ê´Â´Ù
					// ¹«Àû»óÅÂ Ã¼Å©. by sigi. 2002.9.5
					if (pCreature->getObjectID()==m_UserObjectID
						|| !canAttack( pCastCreature, pCreature )
						|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA)
						|| !checkZoneLevelToHitTarget( pCreature )
						|| pCreature->isDead()
						|| pCreature->isSlayer()
					)
					{
						continue;
					}

					if ( pCastCreature != NULL && pCastCreature->isMonster() )
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCastCreature);
						if ( pMonster != NULL && !pMonster->isEnemyToAttack( pCreature ) ) continue;
					}

					//GCModifyInformation gcMI;
					GCModifyInformation gcAttackerMI;
					GCSkillToObjectOK2 gcSkillToObjectOK2;

					if (pCreature->isSlayer()) 
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

						::setDamage( pSlayer, m_Damage, pCastCreature, SKILL_HARPOON_BOMB, &gcSkillToObjectOK2, &gcAttackerMI);

/*						Player* pPlayer = pSlayer->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);*/

					} 
					else if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

						::setDamage( pVampire, m_Damage, pCastCreature, SKILL_HARPOON_BOMB, &gcSkillToObjectOK2, &gcAttackerMI );

/*						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);*/
					}
					else if (pCreature->isOusters())
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

						::setDamage( pOusters, m_Damage, pCastCreature, SKILL_HARPOON_BOMB, &gcSkillToObjectOK2, &gcAttackerMI );

/*						Player* pPlayer = pOusters->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);*/
					}
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);

						::setDamage( pMonster, m_Damage, pCastCreature, SKILL_HARPOON_BOMB, NULL, &gcAttackerMI );

						if ( pCastCreature != NULL ) pMonster->addEnemy( pCastCreature );
					}

					// userÇÑÅ×´Â ¸Â´Â ¸ð½ÀÀ» º¸¿©ÁØ´Ù.
					if (pCreature->isPC())
					{
						gcSkillToObjectOK2.setObjectID( 1 );	// ÀÇ¹Ì ¾ø´Ù.
						gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK2.setDuration(0);
						pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);
					}

					GCSkillToObjectOK4 gcSkillToObjectOK4;
					gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
					gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
					gcSkillToObjectOK4.setDuration(0);

					pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcSkillToObjectOK4, pCreature);
				}
			}
		}
	}

	cout << "crashed" << endl;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHarpoonBomb::affect()
	throw(Error)
{
	__BEGIN_TRY

	cout << "harpoon bomb affect ";
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	Zone* pZone = NULL;
	int cX, cY;

	if ( pCreature == NULL )
	{
		cout << "to zone" << endl;
		pZone = m_pZone;
		cX = m_X;
		cY = m_Y;
	}
	else
	{
		cout << "to creature" << endl;
		pZone = pCreature->getZone();
		cX = pCreature->getX();
		cY = pCreature->getY();
	}

	Assert(pZone != NULL);

	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

	for( int x = -1; x <= 1; x++)
	{
		for(int y= -1; y <= 1; y++)
		{
			int X = cX + x;
			int Y = cY + y;
			cout << "check " << X << ", " << Y << endl;

			if(!rect.ptInRect(X, Y)) continue;
			Tile& tile = pZone->getTile(X, Y);

			const slist<Object*>& oList = tile.getObjectList();
			slist<Object*>::const_iterator itr = oList.begin();
			for(; itr != oList.end(); itr++)
			{
				Object* pObject = *itr;
				Assert(pObject != NULL);

				if(pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
					Assert(pTargetCreature != NULL);

					if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA ) )
					{
						//cout << "Test1 " << endl;
						crash( pZone, X, Y );
						Effect* pComa = pTargetCreature->findEffect( Effect::EFFECT_CLASS_COMA );
						if ( pComa != NULL )
						{
							pTargetCreature->setFlag( Effect::EFFECT_CLASS_HARPOON_BOMB );
							pComa->setDeadline(0);
						}
					}
				}
				else if ( pObject->getObjectClass() == Object::OBJECT_CLASS_ITEM )
				{
					Item* pTargetItem = dynamic_cast<Item*>(pObject);
					if ( pTargetItem->getItemClass() == Item::ITEM_CLASS_CORPSE )
					{
						// add by coffee 2006-12.29 ÐÞÕýÇ¹ÊÖÕ¨Ê¥µ®Ê÷ºÍÖØÉúËþ
								//if( pMonster->getMonsterType() 	== 482 || pMonster->getMonsterType() 	== 673 ) continue;
						/*
						//cout << "Test2 " << endl;
						crash( pZone, X, Y );
						pZone->deleteItemDelayed(pTargetItem, X, Y);
						*/
						// end 2006-12.29
//						SAFE_DELETE(pTargetItem);
					}
				}
			}
		}
	}

	setDeadline(0);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHarpoonBomb::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
//	unaffect(pCreature);

	if ( pCreature == NULL )
	{
		Tile& tile = m_pZone->getTile(m_X, m_Y);
		tile.deleteEffect(m_ObjectID);
	}
	else
	{
		pCreature->removeFlag(Effect::EFFECT_CLASS_HARPOON_BOMB);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHarpoonBomb::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHarpoonBomb("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

