//////////////////////////////////////////////////////////////////////////////
// Filename    : IllusionInversion.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "IllusionInversion.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK3.h"
#include "GCSkillToObjectOK4.h"
#include "GCSkillToObjectOK5.h"
#include "GCSkillToObjectOK6.h"
#include "GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void IllusionInversion::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

//	cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	// Holy Smashing 이 있다면 데미지 증가
	if ( pSlayer->hasRankBonus( RankBonus::RANK_BONUS_SOUL_SMASHING ) )
	{
		RankBonus* pRankBonus = pSlayer->getRankBonus( RankBonus::RANK_BONUS_SOUL_SMASHING );
		Assert( pRankBonus != NULL );

		param.SkillDamage += pRankBonus->getPoint();
	}
	//////////////////////////////////////////////////////////////////////////
	
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, param.SkillType);
			return;
		}

		result.pTargetCreature = pTargetCreature;

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;


		SkillInfo*        pSkillInfo   = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType   = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel   = pSkillSlot->getExpLevel();
		bool              bCriticalHit = false;
		Damage_t          Damage       = 0;

		if (param.bAdd)
		{
			// 파라미터로 전달된 데미지 값이 더해지는 데미지라면, 
			// 일반 데미지를 계산 후, 데미지를 더해야 한다.
			// 파라미터로 전달된 데미지 값이 직접적으로 쓰이는 데미지라면,
			// 이 부분까지 들어오지 않으므로, 밑의 부분까지 0으로 전달된다.
			Damage += computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
		}

		if (param.bMagicDamage)
		{
			// 만일 스킬 데미지가 마법 데미지라면, 마법 데미지 계산 함수를 이용해 계산을 해준다.
			Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
		}
		else
		{
			Damage += param.SkillDamage;
		}

		ZoneCoord_t myX     = pSlayer->getX();
		ZoneCoord_t myY     = pSlayer->getY();
		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = false;
		bool bPK         = verifyPK(pSlayer, pTargetCreature);

		bool bUseSkill	 = false;
		/*
		// 혤놔뎠품賈痰세콘실�ニ學밉천켑渥�
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		//청唐嶠포꼇콘賈痰세콘
		if (pWeapon != NULL) 
		{
			Silver_t silverDamage= pWeapon->getSilver();
			if (silverDamage >50)
			{
				silverDamage-=50;
				pWeapon->setSilver(silverDamage);
				bUseSkill=true;
			}
		}
		*/
		bUseSkill =true;
		
		
		

		if (param.bMagicHitRoll)
		{
			bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		}
		else
		{
			bHitRoll = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bPK &&bUseSkill)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			// 데미지를 가하고, 내구도를 떨어뜨린다.
			setDamage(pTargetCreature, Damage, pSlayer, param.SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			decreaseDurability(pSlayer, pTargetCreature, NULL, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

			// 타겟이 슬레이어가 아닌 경우에만 경험치를 올려준다.
			if (!pTargetCreature->isSlayer())
			{
				shareAttrExp(pSlayer, Damage , param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToObjectOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
				increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);
			}
			// 俱혤커깃HP
			HP_t HealPoint = Damage;
			HP_t CurrentHP = pSlayer->getHP();
			HP_t MaxHP	   = pSlayer->getHP(ATTR_MAX);
			HP_t NewHP     = min((int)MaxHP , (int)CurrentHP + ( (int)HealPoint /2 ) );
			pSlayer->setHP(NewHP);
			GCStatusCurrentHP gcStatusCurrentHP;
			gcStatusCurrentHP.setObjectID(pSlayer->getObjectID());
			gcStatusCurrentHP.setCurrentHP(NewHP);
			pPlayer->sendPacket(&gcStatusCurrentHP);



			_GCSkillToObjectOK1.setSkillType(param.SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(param.SkillType);
			_GCSkillToObjectOK2.setDuration(0);

			_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK3.setSkillType(param.SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);

			_GCSkillToObjectOK4.setSkillType(param.SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(param.SkillType);
			_GCSkillToObjectOK5.setDuration(0);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pSlayer);
			}

			list<Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcStatusCurrentHP, pSlayer);
			pSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}
/*
	g_SimpleMissileSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);
	// 혤놔�襁┶�
	Zone* pZone = pSlayer->getZone();
	Player* pPlayer = pSlayer->getPlayer();
	Assert(pPlayer != NULL);
	Assert(pZone != NULL);
	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

	if (pTargetCreature==NULL		// NoSuch 제거. by sigi. 2002.5.2
		|| pTargetCreature->isNPC()
		|| !canAttack( pSlayer, pTargetCreature )
		|| pTargetCreature->isDead()
		)
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}
	int targetLevel = 0;
	int targetMaxHP = 0;
	Exp_t Exp = output.Damage;
	cout << "賈痰세콘:왜꼭뼙얾,芚냥�襁�:"<< (int)output.Damage << endl;
//	cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;
*/
	__END_CATCH
}

IllusionInversion g_IllusionInversion;
