//////////////////////////////////////////////////////////////////////////////
// Filename    : AbilityBalance.cpp
// Written By  : �輺��
// Description :
// �� ũ���� ���� �ɷ�ġ�� �����ϴ� �Լ����� ���Ƴ��� �����̴�.
//////////////////////////////////////////////////////////////////////////////

#include "AbilityBalance.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "ItemUtil.h"
#include "Properties.h"
#include "VariableManager.h"

// �̰� �ٲ��� Slayer::load(), Vampire::load(), Ousters::load() ����
// maxHP�� �����ؼ� �������ִ� �κе� �ٲ����� �Ѵ�. by sigi.
HP_t computeHP(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	HP_t   maxHP = 0;
	double CSTR   = pAttr->nSTR;
	double CDEX   = pAttr->nDEX;
	double CINT   = pAttr->nINT;
	double CLEVEL = pAttr->nLevel;
	Item* pWeapon = pAttr->pWeapon;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxHP = (int)(CSTR*2.00);

#ifndef __CHINA_SERVER__
		if (pWeapon != NULL )
		{
			switch (pWeapon->getItemClass() )
			{
				case Item::ITEM_CLASS_SWORD:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_SWORD];
					break;
				case Item::ITEM_CLASS_BLADE:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_BLADE];
					break;
				case Item::ITEM_CLASS_CROSS:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_HEAL];
					break;
				case Item::ITEM_CLASS_MACE:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_ENCHANT];
					break;
				case Item::ITEM_CLASS_AR:
				case Item::ITEM_CLASS_SMG:
				case Item::ITEM_CLASS_SR:
				case Item::ITEM_CLASS_SG:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_GUN];
					break;
				default:
					break;
			}
		}
#endif

		maxHP = getPercentValue(maxHP, g_pVariableManager->getVariable(SLAYER_HP_RATIO));
		maxHP = min((int)maxHP, SLAYER_MAX_HP);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		maxHP = (int)(CSTR*2.00 + CINT + CDEX + CLEVEL);
		maxHP = getPercentValue(maxHP, g_pVariableManager->getVariable(VAMPIRE_HP_RATIO));
		maxHP = min((int)maxHP, VAMPIRE_MAX_HP);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS)
	{
		maxHP = (int)(CSTR*1.50 + CINT/2.00 + CDEX + CLEVEL);
		maxHP = getPercentValue(maxHP, g_pVariableManager->getVariable(OUSTERS_HP_RATIO));
		maxHP = min((int)maxHP, OUSTERS_MAX_HP);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		maxHP = (int)(CSTR*(2.00 + CLEVEL/100.0));
		maxHP += getPercentValue(maxHP, enhance);
		maxHP = getPercentValue(maxHP, g_pVariableManager->getVariable(MONSTER_HP_RATIO));
		maxHP = min((int)maxHP, MONSTER_MAX_HP);
//		maxHP = min((int)maxHP, 20000);
	}

	if (g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 )
	{
		maxHP *= 3;
	}

	return maxHP;
}

MP_t computeMP(Creature::CreatureClass CClass, BASIC_ATTR* pAttr)
{
	Assert(pAttr != NULL);

	MP_t   maxMP = 0;
	double CINTE = pAttr->nINT;
	double CLEVEL = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxMP = (int)(CINTE*2.0);
		maxMP = min((int)maxMP, SLAYER_MAX_MP);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		maxMP = (int)((CINTE + CLEVEL)*0.7);
		maxMP = min((int)maxMP, OUSTERS_MAX_MP);
	}

	return maxMP;
}

ToHit_t computeToHit(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	ToHit_t toHit             = 0;
	double  CDEX              = pAttr->nDEX;
	double  CLEVEL            = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		toHit = (int)(CDEX/2);

		if (pAttr->pWeapon != NULL)
		{
			// ���� ���⳪, ���� ���⸦ ���� ���� ����,
			// ������ ������ ���ؼ� ���ʽ� ����Ʈ�� �����Ѵ�.
			if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_SWORD]*1.5);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_BLADE]*1.5);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_CROSS)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_HEAL]*1.5);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_MACE)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_ENCHANT]*1.5);
			}
			else if (isArmsWeapon(pAttr->pWeapon))
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_GUN]*1.5);
			}
		}

		toHit = min((int)toHit, SLAYER_MAX_TOHIT);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		toHit = (int)(CDEX + CLEVEL/2.5);
		toHit = min((int)toHit, VAMPIRE_MAX_TOHIT);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		toHit = (int)(CDEX + CLEVEL/2.5);
		toHit = min((int)toHit, OUSTERS_MAX_TOHIT);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		toHit = (int)((CDEX/2.0) * (1.0 + CLEVEL/100.0));
		toHit += getPercentValue(toHit, enhance);
		toHit = min((int)toHit, MONSTER_MAX_TOHIT);
	}

	return toHit;
}

Defense_t computeDefense(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Defense_t Defense = 0;
	double    CDEX    = pAttr->nDEX;
	double    CLEVEL  = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		Defense = (int)(CDEX/2.0);
		Defense = min((int)Defense, SLAYER_MAX_DEFENSE);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		Defense = (int)(CDEX/2.0 + CLEVEL/5.0);
		Defense = min((int)Defense, VAMPIRE_MAX_DEFENSE);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		Defense = (int)(CDEX/2.0 + CLEVEL/5.0);
		Defense = min((int)Defense, OUSTERS_MAX_DEFENSE);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		Defense = (int)((CDEX/2.0) * (1.0 + CLEVEL/100.0));
		Defense += getPercentValue(Defense, enhance);
		Defense = min((int)Defense, MONSTER_MAX_DEFENSE);
	}

	return Defense;
}

Protection_t computeProtection(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Protection_t Protection  = 0;
	double       CSTR        = pAttr->nSTR;
	//double       CSTRBonus   = pAttr->nSTR/15.0;
	double       CLEVEL      = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		//Protection = (int)(CSTRBonus);
		Protection = (int)(CSTR);
		Protection = min((int)Protection, SLAYER_MAX_PROTECTION);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		//Protection = (int)(CSTR/5.0 + CLEVEL/5.0);
		Protection = (int)(CSTR + CLEVEL / 5.0);
		Protection = min((int)Protection, VAMPIRE_MAX_PROTECTION);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		Protection = (int)(CSTR + CLEVEL/10.0);
		Protection = min((int)Protection, OUSTERS_MAX_PROTECTION);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		Protection = (int)(CSTR / (5.0 - CLEVEL/100.0));
		Protection += getPercentValue(Protection, enhance);
		Protection = min((int)Protection, MONSTER_MAX_PROTECTION);
	}

	return Protection;
}

Damage_t computeMinDamage(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Damage_t minDamage  = 0;
	double   CSTR       = pAttr->nSTR;
	double   CLEVEL     = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		minDamage = (int)(CSTR/15.0);

		if (pAttr->pWeapon != NULL)
		{
			// ���� ���� ���� ���쿡�� ���� ���� ���ʽ��� �������� �ʴ´�.
			if (isArmsWeapon(pAttr->pWeapon))
			{
				minDamage = 1;
			}
		}

		minDamage += g_pVariableManager->getCombatSlayerDamageBonus();

		minDamage = min((int)minDamage, SLAYER_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		minDamage = (int)(CSTR/6.0 + CLEVEL/5.0);

		minDamage += g_pVariableManager->getCombatVampireDamageBonus();
		
		minDamage = min((int)minDamage, VAMPIRE_MAX_DAMAGE);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		minDamage = (int)(CSTR/10.0 + CLEVEL/10.0);

		minDamage = min((int)minDamage, OUSTERS_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		minDamage = (int)(CSTR / (6.0 - CLEVEL/100.0));
		minDamage += getPercentValue(minDamage, enhance);
		minDamage = getPercentValue(minDamage, g_pVariableManager->getVariable(MONSTER_DAMAGE_RATIO ));
		minDamage = min((int)minDamage, MONSTER_MAX_DAMAGE);
	}

	return minDamage;
}

Damage_t computeMaxDamage(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Damage_t maxDamage = 0;
	double   CSTR      = pAttr->nSTR;
	double   CLEVEL    = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxDamage = (int)(CSTR/10.0);

		if (pAttr->pWeapon != NULL)
		{
			// ���� ���� ���� ���쿡�� ���� ���� ���ʽ��� �������� �ʴ´�.
			if (isArmsWeapon(pAttr->pWeapon))
			{
				maxDamage = 2;
			}
		}
		 
		maxDamage += g_pVariableManager->getCombatSlayerDamageBonus();

		maxDamage = min((int)maxDamage, SLAYER_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		maxDamage = (int)(CSTR / 4.0 + CLEVEL / 5.0);

		maxDamage += g_pVariableManager->getCombatVampireDamageBonus();

		maxDamage = min((int)maxDamage, VAMPIRE_MAX_DAMAGE);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		maxDamage = (int)(CSTR / 6.0 + CLEVEL / 6.0);

		maxDamage = min((int)maxDamage, OUSTERS_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		maxDamage = (int)(CSTR / (4.0 - CLEVEL/100.0));
		maxDamage += getPercentValue(maxDamage, enhance);
		maxDamage = getPercentValue(maxDamage, g_pVariableManager->getVariable(MONSTER_DAMAGE_RATIO ));
		maxDamage = min((int)maxDamage, MONSTER_MAX_DAMAGE);
	}
	
	return maxDamage;
}

Speed_t computeAttackSpeed(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Speed_t  AttackSpeed       = 0;
	double   CSTR              = pAttr->nSTR;
	double   CDEX              = pAttr->nDEX;
	double   CLEVEL            = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		// �⺻�����δ� ���� ���� ���� ���ǵ尡 �����ȴ�.
		AttackSpeed = (int)(CSTR/10.0);

		if (pAttr->pWeapon != NULL)
		{
			// ���� ���⳪, ���� ���⸦ ���� ���� ����,
			// ������ ������ ���ؼ� ���ʽ� ����Ʈ�� �����Ѵ�.
			if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD)
			{
				AttackSpeed += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_SWORD]/5.0);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE)
			{
				AttackSpeed += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_BLADE]/5.0);
			}
			else if (isArmsWeapon(pAttr->pWeapon))
			{
				// ���� ������ ���쿡�� ������ ���� ���� ���ǵ尡 �����ȴ�.
				AttackSpeed = (int)(CDEX/10.0);
				AttackSpeed += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_GUN]/5.0);
			}
		}
		AttackSpeed = min((Speed_t)SLAYER_MAX_ATTACK_SPEED, AttackSpeed);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		AttackSpeed = (int)(CDEX/10.0 + 10.0);
		AttackSpeed = min((Speed_t)VAMPIRE_MAX_ATTACK_SPEED, AttackSpeed);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		AttackSpeed = (int)(CDEX/10.0 + CLEVEL/10.0);
		AttackSpeed = min((Speed_t)OUSTERS_MAX_ATTACK_SPEED, AttackSpeed);
	}
	
	return AttackSpeed;
}

int computeCriticalRatio(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	int    CriticalRatio = 0;
	double CDEX          = pAttr->nDEX;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		if (pAttr->pWeapon != NULL)
		{
			if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD)
			{
				CriticalRatio = (int)(pAttr->pDomainLevel[SKILL_DOMAIN_SWORD]/5.0);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE)
			{
				CriticalRatio = (int)(pAttr->pDomainLevel[SKILL_DOMAIN_BLADE]/5.0);
			}
			else if (isArmsWeapon(pAttr->pWeapon))
			{
				// ���� ������ ���쿡�� ������ ���� ���� ���ǵ尡 �����ȴ�.
				CriticalRatio = (int)(pAttr->pDomainLevel[SKILL_DOMAIN_GUN]/5.0);
			}
		}
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		CriticalRatio = (int)((CDEX-20.0)/30.0);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		CriticalRatio = (int)((CDEX-20.0)/30.0);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		CriticalRatio = (int)((CDEX-20.0)/30.0);
		CriticalRatio += getPercentValue(CriticalRatio, enhance);
	}

	return CriticalRatio;
}

Steal_t computeStealRatio(Creature::CreatureClass CClass, Steal_t amount, BASIC_ATTR* pAttr)
{
	// ���� ��ƿ�ϴ� ���� 0�̶���, ��ƿ�� Ȯ�� ���� 0�̴�.
	if (amount == 0) return 0;

	Steal_t result = 0;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		if (pAttr->pWeapon != NULL)
		{
			switch (pAttr->pWeapon->getItemClass())
			{
				case Item::ITEM_CLASS_SWORD:
				case Item::ITEM_CLASS_BLADE:
					result = (Steal_t)(90.0 - (float)amount * 1.4);
					break;
				default:
					result = (Steal_t)(65.0 - (float)amount * 1.4);
					break;
			}
		}
		else
		{
			result = (Steal_t)(90.0 - (float)amount * 1.4);
		}
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		result = (Steal_t)(90.0 - (float)amount * 1.4);
	}
	// �ƿ콺�ͽ� �߰� by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		result = (Steal_t)(90.0 - (float)amount * 1.4);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
	}

	return result;
}

