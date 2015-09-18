////////////////////////////////////////////////////////////////////////////////
// Project     : DARKEDEN
// Module      : Skill - Effect
// File Name   : TurnUndead.cpp
////////////////////////////////////////////////////////////////////////////////

#include "TurnUndead.h"
#include "RankBonus.h"

#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK4.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void TurnUndead::execute(Slayer * pSlayer, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	// Slayer Object Assertion
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Player* pPlayer = pSlayer->getPlayer();
		Assert(pPlayer != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t SkillType = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo =  g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();

		int  RequiredMP		= (int)pSkillInfo->getConsumeMP();
		bool bManaCheck		= hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck		= verifyRunTime(pSkillSlot);
		bool bRangeCheck	= verifyDistance(pSlayer, X, Y, pSkillInfo->getRange()) && checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll		= HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// calculate damage and duration time
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			bool bHit = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			int oX, oY;

			for(oX = -2; oX <= 2; oX++)
			for(oY = -2; oY <= 2; oY++)
			{
				int tileX = X+oX;
				int tileY = Y+oY;

				if (oX == 0 && oY == 0 ) continue;
				if (!rect.ptInRect(tileX, tileY)) continue;

				Tile& tile = pZone->getTile(tileX, tileY);

				// 타일에 있는 크리처들을 리스트로 만든다.
				list<Creature*> targetList;
				if(tile.hasCreature(Creature::MOVE_MODE_WALKING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
					targetList.push_back(pCreature);
				}
				if(tile.hasCreature(Creature::MOVE_MODE_FLYING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
					targetList.push_back(pCreature);
				}
				if(tile.hasCreature(Creature::MOVE_MODE_BURROWING))
				{
					Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
					targetList.push_back(pCreature);
				}

				list<Creature*>::iterator itr = targetList.begin();
				for (; itr != targetList.end(); itr++ )
				{
					Creature* pTargetCreature = (*itr);
					Assert(pTargetCreature != NULL);

					if(checkZoneLevelToHitTarget(pTargetCreature ) && !pTargetCreature->isSlayer()
						   	&& !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)
						   	&& canAttack(pSlayer, pTargetCreature )
					)
					{
						if(pTargetCreature->isVampire() || pTargetCreature->isOusters())
						{
							Player* pTargetPlayer = pTargetCreature->getPlayer();

							bHit = true;

							// 데미지를 적용시킨다.
							GCModifyInformation gcMI;
							::setDamage(pTargetCreature, output.Damage, pSlayer, pSkillSlot->getSkillType(), &gcMI);

							// HP 가 변했다고 당사자에게 보낸다.
							pTargetPlayer->sendPacket(&gcMI);

							GCSkillToObjectOK2 gcSkillToObjectOK2;
							gcSkillToObjectOK2.setObjectID(1);    // 의미 없다.
							gcSkillToObjectOK2.setSkillType(SKILL_ATTACK_MELEE);
							gcSkillToObjectOK2.setDuration(0);
						}
						else if(pTargetCreature->isMonster())
						{
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							bHit = true;

							::setDamage(pMonster, output.Damage, pSlayer, pSkillSlot->getSkillType());
							pMonster->addEnemy(pSlayer);
						}
						else
						{
							continue;
						}

						if (maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
						EnemyNum++;

						GCSkillToObjectOK4 gcSkillToObjectOK4;
						gcSkillToObjectOK4.setTargetObjectID(pTargetCreature->getObjectID());
						gcSkillToObjectOK4.setSkillType(SKILL_ATTACK_MELEE);
						gcSkillToObjectOK4.setDuration(0);
						pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcSkillToObjectOK4);

						// 성향을 올린다.
						increaseAlignment(pSlayer, pTargetCreature, _GCSkillToSelfOK1);
					}
				}
			}

			if(bHit)
			{
				//cout << "Skill Succesfully Attacked(" << output.Damage << ")" << endl;
				shareAttrExp(pSlayer, output.Damage, 1, 1, 8, _GCSkillToSelfOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1, maxEnemyLevel, EnemyNum);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);
			}

            // 패킷을 만들어 보낸다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);

			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);

			// 기술을 사용한 사람에게 packet 전달
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pSlayer);

			// 기술 delay setting
			pSkillSlot->setRunTime(output.Delay);

		}
		else
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch(Throwable& t)
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

TurnUndead g_TurnUndead;
