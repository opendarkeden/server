//////////////////////////////////////////////////////////////////////////////
// Filename     : CombatInfoManager.h
// Written by   : bezz
// Description  : 전쟁의 승패와 관련해서 관련 값들을 설정한다.
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
// 현재 Relic의 Onwer를 가지고 있으며
// 그에 따른 Bonus, Penalty 값을 계산하여 알려준다.
//////////////////////////////////////////////////////////////////////////////

class CombatInfoManager
{
public:
	
	///////////////////////////////////////////////////////////////////
	// Relic Owner
	// Relic을 소유하여 Bonus, Penalty를 받을 대상
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

	// Bonus, Penalty 값을 초기화 한다.
	void initModify();

	// Bonus, Penalty를 계산한다.
	void computeModify();

	// Relic Onwer를 설정한다.
	void setRelicOwner( int index, RelicOwner relicOwner ) throw ( OutOfBoundException );


	// Bonus, Penalty 값을 return
	int getSlayerHPModify() const { return m_SlayerHPModify; }
	int getSlayerToHitModify() const { return m_SlayerToHitModify; }
	int getVampireHPModify() const { return m_VampireHPModify; }
	int getVampireToHitModify() const { return m_VampireToHitModify; }

	bool isSlayerBonus() const		{ return m_bSlayerBonus; }
	bool isVampireBonus() const		{ return m_bVampireBonus; }

	bool isCombat() const			{ return m_bCombat; }
	void setCombat(bool bCombat=true) { m_bCombat = bCombat; }

private:
	// 각 Relic의 Owner
	RelicOwner m_RelicOwner[maxRelic];

	// Bonus, Penalty 값
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
