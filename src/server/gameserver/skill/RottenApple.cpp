//////////////////////////////////////////////////////////////////////////////
// Filename	: RottenApple.cpp
// Written by	: 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RottenApple.h"
#include "PacketUtil.h"

#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCAddEffect.h"
#include "GCModifyInformation.h"

//////////////////////////////////////////////////////////////////////////////
// ½½·¹ÀÌ¾î ¿ÀºêÁ§Æ® ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void RottenApple::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerobject)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		if (pTargetCreature==NULL || pTargetCreature->isSlayer())	// NoSuch Á¦°Å. by sigi. 2002.5.2
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerobject)" << endl;
			return;
		}

		bool isTargetChief = false;

		if ( pTargetCreature->isMonster() )
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
			if ( pTargetMonster->isMaster() )
			{
				executeSkillFailNormal(pSlayer, getSkillType(), pTargetMonster);
				return;
			}

			isTargetChief = pTargetMonster->isChief();
		}

		HP_t targetMaxHP = 0;
		HP_t targetCurrentHP = 0;

		if ( pTargetCreature->isVampire() )
		{
			Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
			targetMaxHP = pTargetVampire->getHP(ATTR_MAX);
			targetCurrentHP = pTargetVampire->getHP(ATTR_CURRENT);
		}
		else if ( pTargetCreature->isOusters() )
		{
			Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);
			targetMaxHP = pTargetOusters->getHP(ATTR_MAX);
			targetCurrentHP = pTargetOusters->getHP(ATTR_CURRENT);
		}
		else if ( pTargetCreature->isMonster() )
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
			targetMaxHP = pTargetMonster->getHP(ATTR_MAX);
			targetCurrentHP = pTargetMonster->getHP(ATTR_CURRENT);
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillType_t		SkillType	= pSkillSlot->getSkillType();
		SkillInfo*		pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int	RequiredMP	= (int)pSkillInfo->getConsumeMP();
		bool bManaCheck	= hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck	= verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll	= HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bCanUse	= targetCurrentHP * 2 < targetMaxHP;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanUse)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// ±â¼úÀÇ È¿°úÄ¡ ¹× Áö¼Ó½Ã°£À» °è»êÇÑ´Ù.
			SkillInput input(pSlayer, pSkillSlot);
			if( pTargetCreature->getCreatureClass() == Creature::CREATURE_CLASS_SLAYER )
				input.TargetType = SkillInput::TARGET_SELF;
			else
				input.TargetType = SkillInput::TARGET_OTHER;
			SkillOutput output;
			computeOutput(input, output);

			// °æÇèÄ¡¸¦ ¿Ã·ÁÁØ´Ù.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10* (Grade + 1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToTileOK1);

			Coord_t myX = pSlayer->getX();
			Coord_t myY = pSlayer->getY();
			Coord_t targetX = pTargetCreature->getX();
			Coord_t targetY = pTargetCreature->getY();

			for ( int i=-2; i<=2; ++i )
			for ( int j=-2; j<=2; ++j )
			{
				ZoneCoord_t X = targetX + i;
				ZoneCoord_t Y = targetY + j;

				if ( !isValidZoneCoord( pZone, X, Y ) ) continue;
				Tile& rTile = pZone->getTile( X, Y );
				forward_list<Object*>& oList = rTile.getObjectList();
				forward_list<Object*>::iterator itr = oList.begin();
				for ( ; itr != oList.end(); ++itr )
				{
					Object* pObject = *itr;
					if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

					Creature* pCreature = dynamic_cast<Creature*>(pObject);

					if ( pCreature->isSlayer() || pCreature->isNPC() ) continue;
					HP_t currentHP = 0, maxHP = 1;
					bool isChief = false;

					if ( pCreature->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
						maxHP = pVampire->getHP(ATTR_MAX);
						currentHP = pVampire->getHP(ATTR_CURRENT);
					}
					else if ( pCreature->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
						maxHP = pOusters->getHP(ATTR_MAX);
						currentHP = pOusters->getHP(ATTR_CURRENT);
					}
					else if ( pCreature->isMonster() )
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);
						// edit by sonic 2006.11.1  ÐÞÕýÈËÀà×£¸£ÃëÉ±BOSS¼¼ÄÜ(ÀÃÆ»¹û)
						if ( pMonster->getMonsterType() == 764 ||
						     pMonster->getMonsterType() == 765 ||
						     pMonster->getMonsterType() == 717 ||
						     //pMonster->getMonsterType() == 599 ||
						     //pMonster->getMonsterType() == 602 ||
						     //pMonster->getMonsterType() == 603 ||
						     (pMonster->getMonsterType() >= 682 && pMonster->getMonsterType() <= 686) ) continue;
						// end by sonic 
						maxHP = pMonster->getHP(ATTR_MAX);
						currentHP = pMonster->getHP(ATTR_CURRENT);
						isChief = pMonster->isChief();
					}

					HP_t goalHP = (HP_t)(2 * (long)maxHP * (long)targetCurrentHP / (long)targetMaxHP);
					if ( !isTargetChief && isChief )
					{
						goalHP = currentHP - min( (int)currentHP, (int)targetMaxHP - (int)targetCurrentHP );
					}

					if ( goalHP >= currentHP ) continue;
					Damage_t damage = currentHP - goalHP;

					_GCSkillToTileOK1.addCListElement( pCreature->getObjectID() );
					_GCSkillToTileOK2.addCListElement( pCreature->getObjectID() );
					_GCSkillToTileOK4.addCListElement( pCreature->getObjectID() );
					_GCSkillToTileOK5.addCListElement( pCreature->getObjectID() );

					GCModifyInformation gcTargetMI;
					::setDamage( pCreature, damage, pSlayer, getSkillType(), &gcTargetMI, &_GCSkillToTileOK1 );
					computeAlignmentChange(pCreature, damage, pSlayer, &gcTargetMI, &_GCSkillToTileOK1);
					increaseAlignment(pSlayer, pCreature, _GCSkillToTileOK1);

					if ( pCreature->isPC() ) pCreature->getPlayer()->sendPacket( &gcTargetMI );
				}
			}

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(targetX);
			_GCSkillToTileOK1.setY(targetY);
			_GCSkillToTileOK1.setDuration(0);
			_GCSkillToTileOK1.setRange(0);

			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(SkillType);
			_GCSkillToTileOK2.setX(targetX);
			_GCSkillToTileOK2.setY(targetY);
			_GCSkillToTileOK2.setDuration(0);
			_GCSkillToTileOK2.setRange(0);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(targetX);
			_GCSkillToTileOK3.setY(targetY);

			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(targetX);
			_GCSkillToTileOK4.setY(targetY);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(0);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(targetX);
			_GCSkillToTileOK5.setY(targetY);
			_GCSkillToTileOK5.setDuration(0);
			_GCSkillToTileOK5.setRange(0);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pSlayer);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToTileOK5, cList);
			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToTileOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToTileOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);

				pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
			} 

			pSkillSlot->setRunTime(output.Delay);
		}
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}

	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerobject)" << endl;

	__END_CATCH
}

RottenApple g_RottenApple;
