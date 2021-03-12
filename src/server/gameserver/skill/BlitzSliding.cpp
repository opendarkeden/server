//////////////////////////////////////////////////////////////////////////////
// Filename    : BlitzSliding.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BlitzSliding.h"
#include "EffectBlazeWalk.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BlitzSliding::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

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

		// NoSuch제거. by sigi. 2002.5.2
		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		// 무장하고 있는 무기가 널이거나, 검이 아니라면 기술을 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, computeSkillRange(pSkillSlot, pSkillInfo));
		bool bHitRoll    = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
		bool bCanHit     = canHit(pSlayer, pTargetCreature, SkillType);
		bool bPK         = verifyPK(pSlayer, pTargetCreature);
		bool bEffected	 = pSlayer->hasRelicItem();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && !bEffected )
		{
			// 빠르게 PC를 움직여준다.
			if (pZone->moveFastPC(pSlayer, pSlayer->getX(), pSlayer->getY(), pTargetCreature->getX(), pTargetCreature->getY(), getSkillType())) 
			{
				decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

				SkillInput input(pSlayer, pSkillSlot);
				SkillOutput output;
				computeOutput(input, output);

				bool bCriticalHit = false;

				// 데미지를 준다.
				Damage_t BasicDamage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
				Damage_t Damage = BasicDamage + output.Damage;
				setDamage(pTargetCreature, Damage, pSlayer, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				decreaseDurability( pSlayer, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2 );

				// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
				if (bCriticalHit)
				{
					knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
				}

				if (!pTargetCreature->isSlayer())
				{
					if ( bIncreaseDomainExp )
					{
						shareAttrExp(pSlayer, Damage, 8, 1, 1, _GCSkillToObjectOK1);
						increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
						increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
					}
					increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);
				}

/*				if ( !pTargetCreature->isFlag( Effect::EFFECT_CLASS_DECREASE_HP ) )
				{
					EffectDecreaseHP* pEffect = new EffectDecreaseHP( pTargetCreature );
					pEffect->setPoint( BasicDamage + output.Damage );
					pEffect->setUserObjectID( pSlayer->getObjectID() );
					pEffect->setDeadline(10);

					pTargetCreature->setFlag( Effect::EFFECT_CLASS_DECREASE_HP );
					pTargetCreature->addEffect( pEffect );
				}*/

				EffectBlazeWalk* pEffect = new EffectBlazeWalk( pTargetCreature );
				pEffect->setPoint( BasicDamage + output.Damage );
				pEffect->setUserObjectID( pSlayer->getObjectID() );
				pEffect->setAttackNum( 1 );
				pEffect->setNextTime(10);
				pEffect->setSkillType( SKILL_BLITZ_SLIDING );
				pTargetCreature->setFlag( Effect::EFFECT_CLASS_BLAZE_WALK );
				pTargetCreature->addEffect( pEffect );

				// 패킷을 준비하고 보낸다.
				_GCSkillToObjectOK1.setSkillType(SkillType);
				_GCSkillToObjectOK1.setCEffectID(CEffectID);
				_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK1.setDuration(0);

				_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
				_GCSkillToObjectOK2.setSkillType(SkillType);
				_GCSkillToObjectOK2.setDuration(0);

				_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
				_GCSkillToObjectOK3.setSkillType(getSkillType());
				_GCSkillToObjectOK3.setTargetXY(pTargetCreature->getX(), pTargetCreature->getY());
			
				_GCSkillToObjectOK4.setSkillType(getSkillType());
				_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

				_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
				_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK5.setSkillType(getSkillType());
				_GCSkillToObjectOK5.setDuration(0);
				
				pPlayer->sendPacket(&_GCSkillToObjectOK1);

				if (pTargetCreature->isPC()) 
				{
					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);
					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				} 
				else 
				{
					Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}

				list<Creature*> cList;
				cList.push_back(pSlayer);
				cList.push_back(pTargetCreature);

				cList = pZone->broadcastSkillPacket(pSlayer->getX(), pSlayer->getY(), pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToObjectOK5, cList);
				
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToObjectOK3 , cList);
				pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(),  &_GCSkillToObjectOK4 , cList);

				pSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
			}
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

BlitzSliding g_BlitzSliding;
