//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSoulChain.cpp
// Written by  : elca
// Description : 
// 군인기술 Sniping 또는 뱀파이어 기술 Invisibility로 인해서
// 현재 점점 희미해져가고 있는(사라지고 있는) 크리쳐에 붙는 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#include "EffectSoulChain.h"
#include "Slayer.h"
#include "Vampire.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCSkillFailed1.h"
#include "Gpackets/GCSkillFailed2.h"
#include "GDRLairManager.h"
#include "Store.h"
#include "GQuestManager.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSoulChain::EffectSoulChain(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//setTarget(pCreature);

	m_OwnerOID = pCreature->getObjectID();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSoulChain::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSoulChain::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	
	//cout << "EffectSoulChain " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// 이펙트 플레그가 없다면 죽었다거나 하는 문제로 transport 하지 않겠다는걸 의미한다.
	if ( !pCreature->isFlag( Effect::EFFECT_CLASS_SOUL_CHAIN ) )
		return;

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Player* pPlayer = pCreature->getPlayer();
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	ZoneCoord_t x = pCreature->getX();
	ZoneCoord_t y = pCreature->getY();
	pCreature->removeFlag(Effect::EFFECT_CLASS_SOUL_CHAIN);

	// Effect 가 없어졌음을 알린다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_SOUL_CHAIN );
	pZone->broadcastPacket( x, y, &gcRemoveEffect );

	// Target 을 체크해서 전송이 가능하면 전송한다.
	bool bValid = false;

	if ( pPC->hasRelicItem() || pPC->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) || pPC->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) )
	{
	}
	else if ( pPC->isSlayer() && dynamic_cast<Slayer*>(pPC)->hasRideMotorcycle() )
	{
	}
	else if ( pPC->getStore()->isOpen() )
	{
	}
	else
	{
		__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

		Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED( m_TargetName );
		if ( pTargetCreature != NULL )
		{
			Zone* pTargetZone = pTargetCreature->getZone();
			if ( pTargetZone != NULL )
			{
				// 마스터 레어로는 이동할 수 없다.
				if ( !pTargetZone->isMasterLair() && !GDRLairManager::Instance().isGDRLairZone( pTargetZone->getZoneID() ) )
				{
					// 유료 서비스 이용이 가능한가?
					if ( pGamePlayer->loginPayPlay( pGamePlayer->getSocket()->getHost(), pGamePlayer->getID() )
						|| pGamePlayer->isFamilyFreePass()
						|| !( g_pZoneInfoManager->getZoneInfo( pTargetZone->getZoneID() )->isPayPlay() ) )
					{
						// 야전사령부, 시외곽지역, 이벤트경기장, 이벤트OX 존으로는 갈 수 없다.
						// 테메리에 성지로도 갈 수 없다.
						if ( pTargetZone->getZoneID() != 2101 && pTargetZone->getZoneID() != 2102 &&
							 pTargetZone->getZoneID() != 1005 && pTargetZone->getZoneID() != 1006 &&
							 pTargetZone->getZoneID() != 1122 && pTargetZone->getZoneID() != 1131 &&
							 pTargetZone->getZoneID() != 1132 && pTargetZone->getZoneID() != 1133 &&
							 pTargetZone->getZoneID() != 1134 && !pTargetZone->isCastleZone() &&
							 !pTargetZone->isDynamicZone() )
						{
							bValid = true;
							pPC->getGQuestManager()->illegalWarp();
							transportCreature( pCreature, pTargetZone->getZoneID(), pTargetCreature->getX(), pTargetCreature->getY(), false );
						}
					}
				}
			}
		}

		__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )
	}

	if ( !bValid )
	{
		GCSkillFailed1 gcSkillFailed1;
		gcSkillFailed1.setSkillType( SKILL_SOUL_CHAIN );
		pPlayer->sendPacket( &gcSkillFailed1 );

		GCSkillFailed2 gcSkillFailed2;
		gcSkillFailed2.setSkillType(SKILL_SOUL_CHAIN);
		gcSkillFailed2.setObjectID(pCreature->getObjectID());

		pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcSkillFailed2, pCreature );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSoulChain::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	if ( m_pZone != NULL )
	{
		Creature* pCreature = m_pZone->getCreature( m_OwnerOID );
		if ( pCreature != NULL )
			unaffect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSoulChain::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSoulChain("
		<< "ObjectID:" << getObjectID()
		<< "TargetName:" << m_TargetName
		<< ")";
	return msg.toString();

	__END_CATCH
}

