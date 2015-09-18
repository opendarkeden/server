//////////////////////////////////////////////////////////////////////////////
// Filename    : HitRoll.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "HitRoll.h"
#include "SkillInfo.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
//#include "LogClient.h"
#include "RankBonus.h"
#include "Skill.h"
#include "Zone.h"
//#include <math.h>

#include "EffectPrecedence.h"
#include "EffectHymn.h"

//////////////////////////////////////////////////////////////////////////////
// 일반 공격 hitroll 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccess(Creature* pAttacker, Creature* pDefender, int ToHitBonus)
{
	Assert(pAttacker != NULL);
	Assert(pDefender != NULL);

	Zone* pZone = pAttacker->getZone();
	Assert(pZone != NULL);

	// 무적상태 체크. by sigi. 2002.9.5
	if (pDefender->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
	{
		return false;
	}


	ToHit_t   ToHit    = 0;
	Defense_t Defense  = 0;
	uint      timeband = pZone->getTimeband();

	bool 	  isMonster = false;
	
	// 공격자의 투힛을 계산한다.
	if (pAttacker->isSlayer())
	{
		Slayer* pSlayerAttacker = dynamic_cast<Slayer*>(pAttacker);
		Assert(pSlayerAttacker != NULL);

		ToHit = pSlayerAttacker->getToHit();

		//cout << "HitRoll: " << pSlayerAttacker->getName().c_str() << " --> ";
	} 
	else if (pAttacker->isVampire())
	{
		Vampire* pVampireAttacker = dynamic_cast<Vampire*>(pAttacker);
		Assert(pVampireAttacker != NULL);

		ToHit = pVampireAttacker->getToHit();
		ToHit = (ToHit_t)getPercentValue(ToHit, VampireTimebandFactor[timeband]);

		// 언젠가 최적화를 하게 된다면.. -_-;
		// Creature에다가 Penalty관련 member들을 넣는게 나을 것이다.
		if (pAttacker->isFlag(Effect::EFFECT_CLASS_HYMN))
		{
			EffectHymn* pHymn = dynamic_cast<EffectHymn*>(pAttacker->getEffectManager()->findEffect(Effect::EFFECT_CLASS_HYMN ));	

			ToHit = ToHit*(100-pHymn->getToHitPenalty())/100;
		}
	} 
	else if (pAttacker->isOusters())
	{
		Ousters* pOustersAttacker = dynamic_cast<Ousters*>(pAttacker);
		Assert(pOustersAttacker != NULL);

		ToHit = pOustersAttacker->getToHit();
	} 
	else if (pAttacker->isMonster())
	{
		Monster* pMonsterAttacker = dynamic_cast<Monster*>(pAttacker);
		Assert(pMonsterAttacker != NULL);

		ToHit = pMonsterAttacker->getToHit();
		ToHit = (ToHit_t)getPercentValue(ToHit, MonsterTimebandFactor[timeband]);
		isMonster = true;

		// 언젠가 최적화를 하게 된다면.. -_-;
		// Creature에다가 Penalty관련 member들을 넣는게 나을 것이다.
		if (pAttacker->isFlag(Effect::EFFECT_CLASS_HYMN))
		{
			EffectHymn* pHymn = dynamic_cast<EffectHymn*>(pAttacker->getEffectManager()->findEffect(Effect::EFFECT_CLASS_HYMN ));

			ToHit = ToHit*(100-pHymn->getToHitPenalty())/100;
		}

	}
	else
	{
		// 현재 크리쳐의 클래스는 Slayer, Vampire, Monster, NPC 뿐인데...
		// 이까지 왔다는 말은 공격자가 NPC라는 말이지.
		// NPC AI는 구현되지 않은 상태이므로, 무조건 리턴이다.
		return false;
	}
	
	// 방어자의 디펜스를 계산해 준다.
	if (pDefender->isSlayer())
	{
		Slayer* pSlayerDefender = dynamic_cast<Slayer*>(pDefender);
		Defense = pSlayerDefender->getDefense();

		//cout << pSlayerDefender->getName().c_str() << " : ";
	} 
	else if (pDefender->isVampire())
	{
		Vampire* pVampireDefender = dynamic_cast<Vampire*>(pDefender);
		Defense = pVampireDefender->getDefense();
		Defense = (Defense_t)getPercentValue(Defense, VampireTimebandFactor[timeband]);
	} 
	else if (pDefender->isOusters())
	{
		Ousters* pOustersDefender = dynamic_cast<Ousters*>(pDefender);
		Defense = pOustersDefender->getDefense();
	} 
	else if (pDefender->isMonster())
	{
		Monster* pMonsterDefender= dynamic_cast<Monster*>(pDefender);
		Defense = pMonsterDefender->getDefense();
		Defense = (Defense_t)getPercentValue(Defense, MonsterTimebandFactor[timeband]);
#ifndef __CHINA_SERVER__
		isMonster = true;
#endif
	}
	else
	{
		// 현재 크리쳐의 클래스는 Slayer, Vampire, Monster, NPC 뿐인데...
		// 이까지 왔다는 말은 방어자가 NPC라는 말이지.
		// NPC AI는 구현되지 않은 상태이므로, 무조건 리턴이다.
		return false;
	}

	int RandValue = Random(0, 100);
	int Result    = 0;

	if (ToHit >= Defense) 
	{
		// 투힛이 디펜스보다 높은 경우에는 맞출 확률이 꽤...높다.
#ifdef __CHINA_SERVER__
		Result = min(90, (int)(((ToHit - Defense) / 1.5) + 60) + ToHitBonus);
#else
		if (isMonster ) 
		{
			Result = min(95, (int)(((ToHit - Defense) / 3) + 50) + ToHitBonus/2);
		}
		else
		{
			Result = min(90, (int)(((ToHit - Defense) / 3) + 50) + ToHitBonus/2);
		}
#endif
	} 
	else 
	{
		// 투힛이 디펜스보다 낮은 경우에는 맞출 확률이 많이 떨어진다.
#ifdef __CHINA_SERVER__
		if(isMonster ) {
			Result = max(10, (int)(60 - ((Defense - ToHit) / 1.5) + ToHitBonus));
		} else {
			Result = max(20, (int)(60 - ((Defense - ToHit) / 1.5) + ToHitBonus));
		}
#else
		if(isMonster ) {
			Result = max(5, (int)(50 - ((Defense - ToHit) / 3) + ToHitBonus/2));
		} else {
			Result = max(10, (int)(50 - ((Defense - ToHit) / 3) + ToHitBonus/2));
		}
#endif
	}

	//cout << ToHit << " --> " << Defense << " : " << RandValue << "<=" << Result 
	//		<< (RandValue <= Result? "Success" : "Fail") << endl;
	if (RandValue <= Result) return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 일반 공격 hitroll 함수
//////////////////////////////////////////////////////////////////////////////
/*bool HitRoll::isSuccess(ToHit_t ToHit, Creature* pDefender, int ToHitBonus)
{
	Assert(pDefender != NULL);

	Zone* pZone = pDefender->getZone();
	Assert(pZone != NULL);

	// 무적상태 체크. by sigi. 2002.9.5
	if (pDefender->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
	{
		return false;
	}


	Defense_t Defense  = 0;
	uint      timeband = pZone->getTimeband();

	// 방어자의 디펜스를 계산해 준다.
	if (pDefender->isSlayer())
	{
		Slayer* pSlayerDefender = dynamic_cast<Slayer*>(pDefender);
		Defense = pSlayerDefender->getDefense();
	} 
	else if (pDefender->isVampire())
	{
		Vampire* pVampireDefender = dynamic_cast<Vampire*>(pDefender);
		Defense = pVampireDefender->getDefense();
		Defense = (Defense_t)getPercentValue(Defense, VampireTimebandFactor[timeband]);
	} 
	else if (pDefender->isOusters())
	{
		Ousters* pOustersDefender = dynamic_cast<Ousters*>(pDefender);
		Defense = pOustersDefender->getDefense();
	} 
	else if (pDefender->isMonster())
	{
		Monster* pMonsterDefender= dynamic_cast<Monster*>(pDefender);
		Defense = pMonsterDefender->getDefense();
		Defense = (Defense_t)getPercentValue(Defense, MonsterTimebandFactor[timeband]);
	}
	else
	{
		// 현재 크리쳐의 클래스는 Slayer, Vampire, Monster, NPC 뿐인데...
		// 이까지 왔다는 말은 방어자가 NPC라는 말이지.
		// NPC AI는 구현되지 않은 상태이므로, 무조건 리턴이다.
		return false;
	}

	int RandValue = Random(0, 100);
	int Result    = 0;

	if (ToHit >= Defense) 
	{
		// 투힛이 디펜스보다 높은 경우에는 맞출 확률이 꽤...높다.
#ifdef __CHINA_SERVER__
		Result = min(90, (int)(((ToHit - Defense) / 1.5) + 60) + ToHitBonus);
#else
		Result = min(95, (int)(((ToHit - Defense) / 3) + 50) + ToHitBonus/2);
#endif
	} 
	else 
	{
		// 투힛이 디펜스보다 낮은 경우에는 맞출 확률이 많이 떨어진다.
#ifdef __CHINA_SERVER__
		Result = max(20, (int)(60 - ((Defense - ToHit) / 1.5) + ToHitBonus));
#else
		Result = max(5, (int)(50 - ((Defense - ToHit) / 3) + ToHitBonus/2));
#endif
	}

	if (RandValue <= Result) return true;

	return false;
}*/


//////////////////////////////////////////////////////////////////////////////
// 슬레이어용 마법 hitroll 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessMagic(Slayer* pSlayer, SkillInfo* pSkillInfo, SkillSlot* pSkillSlot)
{
	Assert(pSlayer != NULL);
	Assert(pSkillInfo != NULL);
	Assert(pSkillSlot != NULL);

	int RandValue = Random (1, 100);
#ifdef __CHINA_SERVER__
	int SuccessRatio = (int)(45 - pSkillInfo->getLevel() / 2 + (int)((pSlayer->getINT() + pSkillSlot->getExpLevel()) / 2.5));
#else
	int SuccessRatio = (int)(60 - pSkillInfo->getLevel() / 3 + (int)((pSlayer->getINT() + pSkillSlot->getExpLevel()) / 2.5));
#endif

	// 슬레이어 셀프 스킬일 경우 최소 확률이 50%이다.
	if (isSlayerSelfSkill(pSkillSlot->getSkillType() ) )
		SuccessRatio = max(50, SuccessRatio);

	if (RandValue < SuccessRatio ) return true;

	return false;
}


//////////////////////////////////////////////////////////////////////////////
// 뱀파이어용 마법 hitroll 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessMagic(Vampire* pVampire, SkillInfo* pSkillInfo, VampireSkillSlot* pVampireSkillSlot, int BonusPoint)
{
	Assert(pVampire != NULL);
	Assert(pSkillInfo != NULL);
	Assert(pVampireSkillSlot != NULL);

	int RandValue = Random(1, 100); 
	int Success = (int)(45 - pSkillInfo->getLevel() / 2 + (pVampire->getINT() + pVampire->getLevel()) / 4);

	if (BonusPoint != 0 )
	{
		Success = getPercentValue(Success, 100 + BonusPoint);
	}
	
	if (RandValue < Success ) return true;
	
//	if (RandValue < (int)(45 - pSkillInfo->getLevel() / 2 + (pVampire->getINT() + pVampire->getLevel()) / 4)) return true;

	return false;
}


//////////////////////////////////////////////////////////////////////////////
// 아우스터스용 마법 hitroll 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessMagic(Ousters* pOusters, SkillInfo* pSkillInfo, OustersSkillSlot* pOustersSkillSlot, int BonusPoint)
{
	Assert(pOusters != NULL);
	Assert(pSkillInfo != NULL);
	Assert(pOustersSkillSlot != NULL);

	int RandValue = Random(1, 100); 
//	int Success = (int)(45 - pSkillInfo->getLevel() / 2 + (pOusters->getINT() + pOusters->getLevel())/10);
	int Success = (int)(45 + (pOusters->getINT() + pOusters->getLevel())/4 + pOustersSkillSlot->getExpLevel()/3);

	if (isOustersSelfSkill(pOustersSkillSlot->getSkillType() ) )
	{
		Success = max(Success, 60);
	}

	if (BonusPoint != 0 )
	{
		Success = getPercentValue(Success, 100 + BonusPoint);
	}
	
	if (RandValue < Success ) return true;
	
	return false;
}

 
//////////////////////////////////////////////////////////////////////////////
// 몬스터용 일반 마법 명중 굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessMagic(Monster* pMonster, SkillInfo* pSkillInfo)
{
	Assert(pMonster != NULL);
	Assert(pSkillInfo != NULL);

	int ratio = (int)(45 - pSkillInfo->getLevel() / 2 + (pMonster->getINT() + pMonster->getLevel()) / 4);
	if (rand()%100 < ratio) return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 및 몬스터용 흡혈 명중 굴림 함수
//////////////////////////////////////////////////////////////////////////////
// multiplier는 보통은 3이다. 즉.. 33%이하가 흡혈 가능수치인데..
// 마스터인 경우에는 multiplier를 2로 해서.. 50% 이하가 흡혈 가능수치로 사용
// by sigi. 2002.9.16
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessBloodDrain(Creature* pAttacker, Creature* pDefender, int multiplier)
{
	Assert(pAttacker != NULL);
	Assert(pDefender != NULL);

	Zone* pZone = pAttacker->getZone();
	Assert(pZone != NULL);

	// 무적상태 체크. by sigi. 2002.9.5
	if (pDefender->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
	{
		return false;
	}


	const int normalMultiplier = 3;	// master flag를 parameter로 받고 이건 빼야한다. - -;
	bool bHPCheck  = false;
	bool bEffected = false;
	uint timeband  = pZone->getTimeband();

	int ToHit      = 0;
	int Defense    = 0;
	int VampLevel  = 0;
	int OtherLevel = 0;
	int ratio      = 0;

	// 타겟이 피를 빨 수 있는 상태인지,
	// 디펜스가 얼마인지, 레벨이 얼마인지를 계산한다.
	if (pDefender->isSlayer())
	{
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pDefender);
		int MaxHP = pTargetSlayer->getHP(ATTR_MAX);
		int CurHP = pTargetSlayer->getHP(ATTR_CURRENT);	

		bHPCheck  = (CurHP*multiplier <= MaxHP) ? true : false;
		bEffected = (normalMultiplier==multiplier) && pTargetSlayer->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		Defense   = pTargetSlayer->getDefense();

		OtherLevel = 
			pTargetSlayer->getSTR(ATTR_CURRENT) +
			pTargetSlayer->getDEX(ATTR_CURRENT) +
			pTargetSlayer->getINT(ATTR_CURRENT) +
			pTargetSlayer->getSkillDomainLevel(SKILL_DOMAIN_BLADE) +
			pTargetSlayer->getSkillDomainLevel(SKILL_DOMAIN_SWORD) +
			pTargetSlayer->getSkillDomainLevel(SKILL_DOMAIN_GUN) +
			pTargetSlayer->getSkillDomainLevel(SKILL_DOMAIN_HEAL) +
			pTargetSlayer->getSkillDomainLevel(SKILL_DOMAIN_ENCHANT);

		OtherLevel = (int)(OtherLevel/350);

		// 체력이 아직 1/3이 넘거나,
		// 이미 흡혈을 당한 상태라면 흡혈을 할 수 없다.
		if (!bHPCheck || bEffected) return false;
	}
	else if (pDefender->isVampire())
	{
		Vampire* pTargetVampire = dynamic_cast<Vampire*>(pDefender);
		int MaxHP = pTargetVampire->getHP(ATTR_MAX);
		int CurHP = pTargetVampire->getHP(ATTR_CURRENT);		

		bHPCheck   = (CurHP*multiplier <= MaxHP) ? true : false;
		//bEffected  = pTargetVampire->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		bEffected = (normalMultiplier==multiplier) && pTargetVampire->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		Defense    = pTargetVampire->getDefense() + pTargetVampire->getLevel() / 5;
		OtherLevel = pTargetVampire->getLevel();

		Defense = (Defense_t)getPercentValue(Defense, VampireTimebandFactor[timeband]);

		// 체력이 아직 1/3이 넘거나,
		// 이미 흡혈을 당한 상태라면 흡혈을 할 수 없다.
		if (!bHPCheck || bEffected) return false;
	}
	else if (pDefender->isOusters())
	{
		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pDefender);
		int MaxHP = pTargetOusters->getHP(ATTR_MAX);
		int CurHP = pTargetOusters->getHP(ATTR_CURRENT);		

		bHPCheck   = (CurHP*multiplier <= MaxHP) ? true : false;
		//bEffected  = pTargetOusters->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		bEffected = (normalMultiplier==multiplier) && pTargetOusters->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		Defense    = pTargetOusters->getDefense() + pTargetOusters->getLevel() / 5;
		OtherLevel = pTargetOusters->getLevel();

		// 체력이 아직 1/3이 넘거나,
		// 이미 흡혈을 당한 상태라면 흡혈을 할 수 없다.
		if (!bHPCheck || bEffected) return false;
	}
	else if (pDefender->isMonster())
	{
		Monster* pTargetMonster = dynamic_cast<Monster*>(pDefender);
		int MaxHP = pTargetMonster->getHP(ATTR_MAX);
		int CurHP = pTargetMonster->getHP(ATTR_CURRENT);		

		bHPCheck   = (CurHP*multiplier <= MaxHP) ? true : false;
		//bEffected  = pTargetMonster->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		bEffected = (normalMultiplier==multiplier) && pTargetMonster->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		Defense    = pTargetMonster->getDefense() + pTargetMonster->getLevel() / 5;
		OtherLevel = pTargetMonster->getLevel();

		Defense = (Defense_t)getPercentValue(Defense, MonsterTimebandFactor[timeband]);

		// 체력이 아직 1/3이 넘거나,
		// 이미 흡혈을 당한 상태라면 흡혈을 할 수 없다.
		if (!bHPCheck || bEffected) return false;

		// 만일 우선권이 이미 세팅되어 있는 몬스터라면...
		// 흡혈할 수 있는 조건은 우선권을 가진 자이거나, 우선권을 가진 파티에 속한 자여야 한다.
		if (pTargetMonster->isFlag(Effect::EFFECT_CLASS_PRECEDENCE))
		{
			EffectPrecedence* pEffectPrecedence = dynamic_cast<EffectPrecedence*>(pTargetMonster->findEffect(Effect::EFFECT_CLASS_PRECEDENCE));
			Assert(pEffectPrecedence != NULL);

			// 우선권을 가진 자가 아니라면...
			if (pAttacker->getName() != pEffectPrecedence->getHostName()) 
			{
				// 아무 파티에도 가입되어 있지 않거나,
				// 파티에 가입되어 있는데, 호스트 파티 ID가 아니라면, 흡혈할 수 없다.
				if (pAttacker->getPartyID() == 0 || pAttacker->getPartyID() != pEffectPrecedence->getHostPartyID())
				{
					return false;
				}
			}
		}
	}
	else Assert(false);
     
	// 공격자의 투힛 및 레벨을 계산한다.
	if (pAttacker->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pAttacker);

		ToHit     = pVampire->getToHit();
		VampLevel = pVampire->getLevel();

		ToHit = (ToHit_t)getPercentValue(ToHit, VampireTimebandFactor[timeband]);
	}
	else if (pAttacker->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pAttacker);

		ToHit     = pMonster->getToHit();
		VampLevel = pMonster->getLevel();

		ToHit = (ToHit_t)getPercentValue(ToHit, MonsterTimebandFactor[timeband]);
	}

//	cout << pAttacker->getName() << "의 투힛 : " << ToHit << endl;
//	cout << pDefender->getName() << "의 디펜 : " << Defense << endl;

	if (ToHit >= Defense)
	{
		// 투힛이 디펜스보다 높은 경우에는 맞출 확률이 꽤...높다.
		ratio = min(90, (ToHit - Defense) / 2 + 70);
	}
	else
	{
		// 투힛이 디펜스보다 낮은 경우에는 맞출 확률이 많이 떨어진다.
		ratio = max(10, 70 - (Defense - ToHit) / 2);
	}

	if ((rand()%100) < ratio)
	{
//		cout << "흡혈 성공" << endl;
		return true;
	}

//	cout << "흡혈 실패" << endl;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 저주 마법 히트롤 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessCurse(int MagicLevel, Resist_t resist)
{
	// MagicLevel은 뱀파이어가 그 마법을 배우는 데 필요한 레벨이다.
	// 즉 높은 레벨의 저주 마법일수록 MagicLevel이 높아진다.
	//
	// MagicLevel이 30이고, 저항이 20이라면...
	// curse_prob = 110이고, 저주는 항상 성공하게 된다.
	// MagicLevel이 30이고, 저항이 100이라면...
	// curse_prob = 30이고, 마법은 70% 확률로 실패하게 된다.
#ifdef __CHINA_SERVER__
	int prob_penalty = (int)(MagicLevel - resist);
	int curse_prob   = 65 + prob_penalty;
#else
	int prob_penalty = (int)(MagicLevel*2/1.5 - resist);
	int curse_prob   = 75 + prob_penalty;
	curse_prob = max(5, curse_prob);
#endif
	int randomValue  = rand()%100;

	// 아, 씨바. 저주 걸렸다.
	if (randomValue < curse_prob) return true;

	// 저항력에 의해서 걸리지 않았다. 아싸리...
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 저주 마법 히트롤 함수 - 뱀파이어가 저주를 걸때
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessVampireCurse(int MagicLevel, Resist_t resist)
{
	// MagicLevel은 뱀파이어가 그 마법을 배우는 데 필요한 레벨을 2로 나눈
	// 것이다. 즉 높은 레벨의 저주 마법일수록 MagicLevel이 높아진다.
	//
	// MagicLevel이 30이고, 저항이 20이라면...
	// curse_prob = 110이고, 저주는 항상 성공하게 된다.
	// MagicLevel이 30이고, 저항이 100이라면...
	// curse_prob = 30이고, 마법은 70% 확률로 실패하게 된다.
	int prob_penalty = (int)((int)(MagicLevel/1.5) - resist);
	int curse_prob   = 75 + prob_penalty;
	curse_prob = max(5, curse_prob);

	int randomValue  = rand()%100;

	// 아, 씨바. 저주 걸렸다.
	if (randomValue < curse_prob) return true;

	// 저항력에 의해서 걸리지 않았다. 아싸리...
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// CurePoison 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessCurePoison(int Base, int SkillLevel, int Difficulty, int MagicLevel, int MinRatio)
{
	int ratio = Base + SkillLevel - Difficulty - MagicLevel;

	// 최소확률을 집어넣었다. by Sequoia 2003. 3. 20
	ratio = max(MinRatio, ratio);

	if (rand()%100 < ratio) return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// Flare 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessFlare(Creature* pTargetCreature, int SkillLevel)
{
	Assert(pTargetCreature != NULL);

	// 무적상태 체크. by sigi. 2002.9.5
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
		return false;

	int ratio = 0;

	if (pTargetCreature->isPC())
	{
//		Vampire* pVampire = dynamic_cast<Vampire*>(pTargetCreature);
		ratio = 75 + SkillLevel - pTargetCreature->getLevel();
	}
	else if (pTargetCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);

		// 
		// by sigi. 2002.10.30
		if (pMonster->isMaster()
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
		)
		{
			return false;
		}

		ratio = 75 + SkillLevel - pMonster->getLevel();
	}

	if (rand()%100 < ratio) return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// RemoveCurse 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessRemoveCurse(int Base, int SkillLevel, int Difficulty, int MagicLevel, int MinRatio)
{
	int ratio = Base + SkillLevel - Difficulty - MagicLevel;

	// 최소확률을 집어넣었다. by Sequoia 2003. 3. 20
	ratio = max(MinRatio, ratio);

	if (rand()%100 < ratio) return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// Rebuke 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessRebuke(Slayer* pSlayer, SkillSlot* pSkillSlot, Creature* pDefender)
{
	if(pDefender->isSlayer() ) return false;

	// 80레벨 이상의 뱀파이어는 잠들지 않는다.
	if (pDefender->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pDefender);
		if (pVampire->getLevel() >= 80 )
			return false;
	}
	else if (pDefender->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pDefender);
		if (pOusters->getLevel() >= 80 )
			return false;
	}

	// 마스터 (바토리, 테페즈)는 잠들지 않는다.
	if(pDefender->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pDefender);
		if(pMonster->isMaster()
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599 
#endif
		)
			return false;
	}

	Attr_t			INTE		= pSlayer->getINT(ATTR_CURRENT);
	SkillLevel_t	SkillLevel	= pSkillSlot->getExpLevel();

//	int ratio = (INTE / 10 ) + (SkillLevel / 3);
	int ratio = 20 + (INTE / 10 ) + (SkillLevel / 2);
	if (rand()%100 < ratio ) return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// Magic Elusion 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessMagicElusion(Slayer* pSlayer)
{
	Attr_t	SUM		=	pSlayer->getTotalAttr(ATTR_CURRENT);
	int		Ratio	=	50 + (SUM/15);

	return (rand()%100) < Ratio;
}

//////////////////////////////////////////////////////////////////////////////
// Posion Mesh 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessPoisonMesh(Vampire* pVampire)
{
	int		Ratio	=	30 + (pVampire->getLevel()/5);

	return (rand()%100) < Ratio;
}

//////////////////////////////////////////////////////////////////////////////
// Illusion Of Avenge 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessIllusionOfAvenge(Slayer* pSlayer)
{
	Attr_t	SUM		=	pSlayer->getTotalAttr(ATTR_CURRENT);
	int		Ratio	=	50 + (SUM/15);

	return (rand()%100) < Ratio;
}

//////////////////////////////////////////////////////////////////////////////
// Will Of Life 명중굴림 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSuccessWillOfLife(Vampire* pVampire)
{
	int		Ratio	=	50 + pVampire->getLevel()/5;

	return (rand()%100) < Ratio;
}


//////////////////////////////////////////////////////////////////////////////
// 크리티컬 히트 롤을 수행한다.
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isCriticalHit(Creature* pCreature, int CriticalBonus)
{
	Assert(pCreature != NULL);

	int CriticalRatio = pCreature->getCriticalRatio() + CriticalBonus;

	if (rand()%1000 < CriticalRatio) return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 스킬인가를 체크하는 함수
//////////////////////////////////////////////////////////////////////////////
bool HitRoll::isSlayerSelfSkill(SkillType_t skillType )
{
	switch (skillType )
	{
		case SKILL_DANCING_SWORD:
		case SKILL_CROSS_COUNTER:
		case SKILL_EXPANSION:
		case SKILL_SHARP_SHIELD:

		case SKILL_GHOST_BLADE:
		case SKILL_POTENTIAL_EXPLOSION:
		case SKILL_CHARGING_POWER:
		case SKILL_BERSERKER:
		case SKILL_AIR_SHIELD:

		case SKILL_SNIPING:
		case SKILL_OBSERVING_EYE:

		case SKILL_CREATE_HOLY_WATER:
		case SKILL_LIGHT:
		case SKILL_DETECT_HIDDEN:
		case SKILL_BLESS:
		case SKILL_STRIKING:
		case SKILL_DETECT_INVISIBILITY:
		case SKILL_AURA_SHIELD:
		case SKILL_REFLECTION:
		case SKILL_REBUKE:
		case SKILL_SPIRIT_GUARD:

		case SKILL_CURE_LIGHT_WOUNDS:
		case SKILL_CURE_POISON:
		case SKILL_PROTECTION_FROM_POISON:
		case SKILL_CURE_SERIOUS_WOUNDS:
		case SKILL_REMOVE_CURSE:
		case SKILL_PROTECTION_FROM_CURSE:
		case SKILL_CURE_CRITICAL_WOUNDS:
		case SKILL_PROTECTION_FROM_ACID:
		case SKILL_CURE_ALL:
		case SKILL_PEACE:
		case SKILL_ACTIVATION:
		case SKILL_REGENERATION:
		case SKILL_TURN_UNDEAD:
			return true;

		default:
			return false;
	}
}

bool HitRoll::isOustersSelfSkill(SkillType_t skillType )
{
	switch (skillType )
	{
		case SKILL_EVADE:
		case SKILL_BLUNTING:
		case SKILL_CROSS_GUARD:
		case SKILL_SHARP_CHAKRAM:
			return true;

		default:
			return false;
	}
}
bool HitRoll::isSuccessHallucination(Vampire* pAttacker, Creature* pTarget )
{
	if (pTarget->isMonster() ) return true;

	Attr_t attackTotalAttr = pAttacker->getSTR() + pAttacker->getDEX() + pAttacker->getINT();
	Attr_t targetTotalAttr = 0;
	int minRatio = 0, maxRatio = 100;

	if (pTarget->isSlayer() )
	{
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTarget);
		targetTotalAttr = pTargetSlayer->getTotalAttr();
		minRatio = 30;
		maxRatio = 60;
	}
	else if (pTarget->isVampire() )
	{
		Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTarget);
		targetTotalAttr = pTargetVampire->getSTR() + pTargetVampire->getDEX() + pTargetVampire->getINT();
		minRatio = 10;
		maxRatio = 40;
	}
	else if (pTarget->isOusters() )
	{
		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTarget);
		targetTotalAttr = pTargetOusters->getSTR() + pTargetOusters->getDEX() + pTargetOusters->getINT();
		minRatio = 10;
		maxRatio = 50;

	}
	else return false;

	int Ratio = attackTotalAttr - targetTotalAttr;
	Ratio = max(minRatio, Ratio);
	Ratio = min(maxRatio, Ratio);

	return (rand() % 100 ) < Ratio;
}

bool HitRoll::isSuccessBackStab(Ousters* pAttacker )
{
	int Ratio = min(50, (pAttacker->getINT()/5) + (pAttacker->getDEX()/5));
	if (rand() % 100 < Ratio ) return true;
	return false;
}
