//////////////////////////////////////////////////////////////////////////////
// Filename     : CombatInfoManager.h
// Written by   : bezz
// Description  : ������ ���п� �����ؼ� ���� ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __COMBAT_INFO_MANAGER_H__
#define __COMBAT_INFO_MANAGER_H__

#include "Types.h"
#include "Assert.h"
#include "Exception.h"
#include "Mutex.h"
#include "Relic.h"

//////////////////////////////////////////////////////////////////////////////
// class CombatInfoManager
//
// ���� Relic�� Onwer�� ������ ������
// �׿� ���� Bonus, Penalty ���� ����Ͽ� �˷��ش�.
//////////////////////////////////////////////////////////////////////////////

class CombatInfoManager
{
public:
	
	///////////////////////////////////////////////////////////////////
	// Relic Owner
	// Relic�� �����Ͽ� Bonus, Penalty�� ���� ���
	///////////////////////////////////////////////////////////////////
	enum RelicOwner
	{
		RELIC_OWNER_NULL,
		RELIC_OWNER_SLAYER,
		RELIC_OWNER_VAMPIRE
	};

public:

	// Constructor
	CombatInfoManager();

	// Bonus, Penalty ���� �ʱ�ȭ �Ѵ�.
	void initModify();

	// Bonus, Penalty�� ����Ѵ�.
	void computeModify();

	// Relic Onwer�� �����Ѵ�.
	void setRelicOwner( int index, RelicOwner relicOwner );


	// Bonus, Penalty ���� return
	int getSlayerHPModify() const { return m_SlayerHPModify; }
	int getSlayerToHitModify() const { return m_SlayerToHitModify; }
	int getVampireHPModify() const { return m_VampireHPModify; }
	int getVampireToHitModify() const { return m_VampireToHitModify; }

	bool isSlayerBonus() const		{ return m_bSlayerBonus; }
	bool isVampireBonus() const		{ return m_bVampireBonus; }

	bool isCombat() const			{ return m_bCombat; }
	void setCombat(bool bCombat=true) { m_bCombat = bCombat; }

private:
	// �� Relic�� Owner
	RelicOwner m_RelicOwner[maxRelic];

	// Bonus, Penalty ��
	int m_SlayerHPModify;
	int m_SlayerToHitModify;
	int m_VampireHPModify;
	int m_VampireToHitModify;

	bool m_bSlayerBonus;
	bool m_bVampireBonus;
	
	bool m_bCombat;
};

extern CombatInfoManager* g_pCombatInfoManager;

#endif
