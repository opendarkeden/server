//////////////////////////////////////////////////////////////////////////////
// Filename     : CombatInfoManager.cpp
// Written by   : bezz
// Description  :
//////////////////////////////////////////////////////////////////////////////

#include "StringPool.h"
#include "CombatInfoManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "ZoneGroupManager.h"

//////////////////////////////////////////////////////////////////////////////
// global variable initialize
//////////////////////////////////////////////////////////////////////////////

CombatInfoManager* g_pCombatInfoManager = NULL;

//////////////////////////////////////////////////////////////////////////////
// class CombatInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

CombatInfoManager::CombatInfoManager()
{
	__BEGIN_TRY
	
	for ( int i = 0; i < maxRelic; i++ )
	{
		m_RelicOwner[i] = RELIC_OWNER_NULL;
	}

	m_SlayerHPModify = 0;
	m_SlayerToHitModify = 0;
	m_VampireHPModify = 0;
	m_VampireToHitModify = 0;

	m_bSlayerBonus = false;
	m_bVampireBonus = false;

	m_bCombat = false;

	__END_CATCH
}

void CombatInfoManager::initModify()
{
	__BEGIN_TRY

	//computeModify();

	__END_CATCH
}

void CombatInfoManager::computeModify()
{
	__BEGIN_TRY
	
	m_SlayerHPModify = 0;
	m_SlayerToHitModify = 0;
	m_VampireHPModify = 0;
	m_VampireToHitModify = 0;

	for ( int i = 0; i < maxRelic; i++ )
	{
		// bonus, penalty 계산
	}

	GCSystemMessage gcSystemMessage;
	bool bSendMessage = false;
	
	bool bSlayerBonus = m_RelicOwner[0] == RELIC_OWNER_SLAYER
						&& m_RelicOwner[1] == RELIC_OWNER_SLAYER;

	bool bVampireBonus = m_RelicOwner[0] == RELIC_OWNER_VAMPIRE
						&& m_RelicOwner[1] == RELIC_OWNER_VAMPIRE;

	// 슬레이어 승리
	if (bSlayerBonus)
	{
		//m_SlayerHPModify = g_pVariableManager->getCombatSlayerHPBonusRatio();
//		gcSystemMessage.setMessage("슬레이어에게 보너스를 뭐줄까?");
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_APPLICATE_COMBAT_SLAYER_BONUS ) );
		bSendMessage = true;
	}
	// 뱀파이어 승리
	else if (bVampireBonus)
	{
		//m_VampireHPModify = g_pVariableManager->getCombatVampireHPBonusRatio();
//		gcSystemMessage.setMessage("뱀파이어에게 보너스를 뭐줄까?");
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_APPLICATE_COMBAT_VAMPIRE_BONUS ) );
		bSendMessage = true;
	}

	else if (!bSlayerBonus && !bVampireBonus)
	{
		// 적용되고 있다가 적용안되는 경우
		if (m_bSlayerBonus && m_bVampireBonus)
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_MORE_COMBAT_BONUS ) );
			bSendMessage = true;
		}
		// 슬레이어 보너스가 사라지는 경우
		else if (m_bSlayerBonus)
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_MORE_COMBAT_SLAYER_BONUS ) );
			bSendMessage = true;
		}
		// 뱀파이어 보너스가 사라지는 경우
		else if (m_bVampireBonus)
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_MORE_COMBAT_VAMPIRE_BONUS ) );
			bSendMessage = true;
		}
	}

//	if (bSendMessage)
//		g_pZoneGroupManager->broadcast(&gcSystemMessage);

	m_bSlayerBonus = bSlayerBonus;
	m_bVampireBonus = bVampireBonus;

	__END_CATCH
}

void CombatInfoManager::setRelicOwner( int index, RelicOwner relicOwner )
	throw ( OutOfBoundException )
{
	__BEGIN_TRY

	if ( index < 0 || index >= maxRelic )
	{
		throw OutOfBoundException();
	}

	m_RelicOwner[index] = relicOwner;

	//computeModify();
	
	__END_CATCH
}
