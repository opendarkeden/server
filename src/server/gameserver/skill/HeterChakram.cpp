//////////////////////////////////////////////////////////////////////////////
// Filename    : HeterChakram.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "HeterChakram.h"
#include "EffectHeterChakram.h"

#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////////////
// ¾Æ¿ì½ºÅÍÁî ¿ÀºêÁ§Æ® ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void HeterChakram::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);
	int Grade = 0;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

		// NPC´Â °ø°ÝÇÒ ¼ö°¡ ¾ø´Ù.
		// NoSuchÁ¦°Å. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pOusters, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			return;
		}

		if ( pTargetCreature->isMonster() )
		{
			Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
			if ( pMonster != NULL && pMonster->isMaster() )
			{
				executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature, Grade);
				return;
			}
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;
		
		// ¼ì²âÎäÆ÷ºÏ·¨ÐÔ
		Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_OUSTERS_CHAKRAM || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			return;
		}

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());

		int  RequiredMP         = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3;
		// Çå³ýËùÓÐMP
		//RequiredMP = pOusters->getMP();
		
		bool bManaCheck         = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck        = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll           = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bCanHit            = canHit(pOusters, pTargetCreature, getSkillType());
		bool bPK                = verifyPK(pOusters, pTargetCreature);
		bool bSatisfyRequire	= pOusters->satisfySkillRequire( pSkillInfo );
// 		if (RequiredMP < ((int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3 ) )
// 			bManaCheck = false;
		

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && bSatisfyRequire )
		{
            decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);
			bool bCanSeeCaster = canSee(pTargetCreature, pOusters);

			ZoneCoord_t X   = pOusters->getX();
			ZoneCoord_t Y   = pOusters->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);
			int cx = pTargetCreature->getX();
			int cy = pTargetCreature->getY();
			if ( pTargetCreature == NULL || 
				pTargetCreature->isDead() || 
				pTargetCreature->isFlag( Effect::EFFECT_CLASS_HETER_CHAKRAM )
				)
			{
				executeSkillFailException(pOusters, getSkillType(), Grade);
				return;
			}
			EffectHeterChakram* pEffect = new EffectHeterChakram( pTargetCreature );
			pEffect->setUserOID( pOusters->getObjectID() );
			pEffect->setDamage( output.Damage );
			pEffect->setDeadline( output.Duration );
			pEffect->setDuration( output.Duration );
			pEffect->setNextTime(10);
			pTargetCreature->setFlag( pEffect->getEffectClass() );
			pTargetCreature->addEffect( pEffect );

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
			gcAddEffect.setEffectID( pEffect->getEffectClass() );
			gcAddEffect.setDuration( output.Duration );

			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );

			if (pTargetCreature->isDead())
			{
				int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, _GCSkillToObjectOK1);
			}

			increaseAlignment(pOusters, pTargetCreature, _GCSkillToObjectOK1);

			_GCSkillToObjectOK1.setSkillType(getSkillType());
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
			_GCSkillToObjectOK1.setGrade(Grade);
			_GCSkillToObjectOK1.setDuration(output.Duration);

			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(getSkillType());
			_GCSkillToObjectOK2.setDuration(0);
			_GCSkillToObjectOK2.setGrade(Grade);
			_GCSkillToObjectOK2.setDuration(output.Duration);

			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(getSkillType());
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
			_GCSkillToObjectOK3.setGrade(Grade);

			_GCSkillToObjectOK4.setSkillType(getSkillType());
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setGrade(Grade);
			_GCSkillToObjectOK4.setDuration(output.Duration);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(getSkillType());
			_GCSkillToObjectOK5.setGrade(Grade);
			_GCSkillToObjectOK5.setDuration(output.Duration);

			_GCSkillToObjectOK6.setXY(X, Y);
			_GCSkillToObjectOK6.setSkillType(getSkillType());
			_GCSkillToObjectOK6.setDuration(0);
			_GCSkillToObjectOK6.setGrade(Grade);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			Player* pTargetPlayer = NULL;
			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pOusters);
			}

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(X, Y, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(X, Y,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);

// 			for ( int i=-2; i<=2; ++i )
// 			for ( int j=-2; j<=2; ++j )
// 			{
// 				int tx = cx + i;
// 				int ty = cy + j;
// 				if ( tx < 0 || ty < 0 ) continue;
// 				if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;
// 				// 	 
// 				slist<Object*>& olist = pZone->getTile(tx, ty).getObjectList();
// 				slist<Object*>::iterator itr = olist.begin();
// 				for ( ; itr != olist.end() ; ++itr )
// 				{
// 					Object* pObject = *itr;
// 					if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;
// 				 	 
// 					Creature* pTargetCreature2 = dynamic_cast<Creature*>(pObject);
// 					if ( pTargetCreature2 == NULL || pTargetCreature2->isDead() ) continue;
// 					if ( pTargetCreature2->isFlag( Effect::EFFECT_CLASS_HETER_CHAKRAM ) ) continue;
// 					if (pTargetCreature2->isOusters() && pTargetCreature->isOusters() ||
// 						pTargetCreature2->isVampire() && pTargetCreature->isVampire() ||
// 						pTargetCreature2->isSlayer() && pTargetCreature->isSlayer() ||
// 						pTargetCreature2->isMonster() && pTargetCreature->isMonster() 
// 						)
// 					{					
// 						EffectHeterChakram* pEffect = new EffectHeterChakram( pTargetCreature2 );
// 						pEffect->setUserOID( pOusters->getObjectID() );
// 						pEffect->setDamage( output.Damage );
// 						pEffect->setDeadline( output.Duration );
// 						pEffect->setDuration( output.Duration );
// 						pEffect->setNextTime(10);
// 						pTargetCreature->setFlag( pEffect->getEffectClass() );
// 						pTargetCreature->addEffect( pEffect );
// 			
// 						GCAddEffect gcAddEffect;
// 						gcAddEffect.setObjectID( pTargetCreature2->getObjectID() );
// 						gcAddEffect.setEffectID( pEffect->getEffectClass() );
// 						gcAddEffect.setDuration( output.Duration );
// 						pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
// 					}
// 				 	 
// 				}
// 			}

		}
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature, Grade);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	__END_CATCH
}

HeterChakram g_HeterChakram;

