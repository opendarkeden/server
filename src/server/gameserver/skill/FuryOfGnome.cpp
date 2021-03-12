//////////////////////////////////////////////////////////////////////////////
// Filename    : FuryOfGnome.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "FuryOfGnome.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCAddEffectToTile.h"

#include "Player.h"
#include "EffectFuryOfGnome.h"
#include "EffectFuryOfGnomeMark.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void FuryOfGnome::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

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
        //cout << t.toString() << endl;
    }

	__END_CATCH
}

void FuryOfGnome::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Zone* pZone = pOusters->getZone();
	Assert( pZone != NULL );

/*	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

	if (pTargetCreature==NULL
		|| !canAttack( pOusters, pTargetCreature )
		|| pTargetCreature->isNPC())
	{
		executeSkillFailException(pOusters, getSkillType());
		return;
	}*/

/*	if ( pTargetCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
		targetLevel = pSlayer->getHighestSkillDomainLevel();
	}
	else
	{
		targetLevel = pTargetCreature->getLevel();
	}*/

	SkillInput input(pOusters, pOustersSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	Item* pWeapon = pOusters->getWearItem( Ousters::WEAR_RIGHTHAND );
	if ( pWeapon == NULL )
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;

	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_WRISTLET;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd = false;

	SIMPLE_SKILL_OUTPUT result;

	int offset = 2;

	for ( int i=-offset; i<=offset; ++i )
	for ( int j=-offset; j<=offset; ++j )
		param.addMask( i, j, 100 );

	g_SimpleTileMissileSkill.execute(pOusters, X, Y, pOustersSkillSlot, param, result, CEffectID );

	if(result.bSuccess)
	{
		Tile& markTile = pZone->getTile(X, Y);

		if ( markTile.canAddEffect() )
		{
			Effect* pOldEffect = markTile.getEffect(Effect::EFFECT_CLASS_FURY_OF_GNOME_MARK);

			if ( pOldEffect != NULL )
			{
				pZone->deleteEffect(pOldEffect->getObjectID());
			}

			EffectFuryOfGnomeMark* pMarkEffect = new EffectFuryOfGnomeMark(pZone, X, Y );
			pMarkEffect->setDeadline(output.Duration);
			pZone->registerObject( pMarkEffect );
			pZone->addEffect(pMarkEffect);

			markTile.addEffect(pMarkEffect);

			GCAddEffectToTile gcMarkEffect;
			
			gcMarkEffect.setEffectID( pMarkEffect->getSendEffectClass() );
			gcMarkEffect.setDuration( output.Duration );
			gcMarkEffect.setObjectID( pMarkEffect->getObjectID() );
			gcMarkEffect.setXY( X, Y );

			pZone->broadcastPacket( X, Y, &gcMarkEffect );
		}

		for ( int i=-offset; i<=offset; ++i )
		for ( int j=-offset; j<=offset; ++j )
		{
			int targetX = X + i;
			int targetY = Y + j;
			if( isValidZoneCoord( pZone, targetX, targetY ) )
			{
				Tile& tile = pZone->getTile(targetX, targetY);
				if ( tile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION) ) continue;

				// 현재 타일에다 이펙트를 추가할 수 있다면...
				if (tile.canAddEffect())
				{
					// 같은 effect가 있으면 지운다.
					Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_FURY_OF_GNOME);
					if (pOldEffect != NULL)
					{
						ObjectID_t effectID = pOldEffect->getObjectID();
						pZone->deleteEffect(effectID);// fix me
					}

					// 이펙트 클래스를 생성한다.
					EffectFuryOfGnome* pEffect = new EffectFuryOfGnome(pZone , targetX, targetY);
					pEffect->setDeadline(output.Duration);

					// Tile에 붙이는 Effect는 ObjectID를 등록받아야 한다.
					ObjectRegistry & objectregister = pZone->getObjectRegistry();
					objectregister.registerObject(pEffect);
					pZone->addEffect(pEffect);
					tile.addEffect(pEffect);

					GCAddEffectToTile gcEffect;
					gcEffect.setEffectID( pEffect->getSendEffectClass() );
					gcEffect.setDuration( output.Duration );
					gcEffect.setObjectID( pEffect->getObjectID() );
					gcEffect.setXY( targetX, targetY );

					pZone->broadcastPacket( targetX, targetY, &gcEffect );
				}
			}
		}
	}
	

	__END_CATCH
}

FuryOfGnome g_FuryOfGnome;
