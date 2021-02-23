//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectTileEffectHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectTileEffect.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Effect.h"
	#include "EffectManager.h"
	#include "ZoneInfoManager.h"
	#include "ZoneUtil.h"
	#include "PacketUtil.h"
	#include "Properties.h"
	#include "RelicUtil.h"
	#include "StringPool.h"
	#include "GQuestManager.h"

	#include "skill/EffectVampirePortal.h"

	#include "Gpackets/GCEnterVampirePortal.h"
	#include "Gpackets/GCSystemMessage.h"
#endif // __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectTileEffectHandler::execute(CGSelectTileEffect* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		// 게임 플레이어의 상태가 정상이 아니라면 걍 리턴한다.
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);
		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		// 성물 들고 있으면 포탈에 들어갈 수 없다.
		if ( pCreature->hasRelicItem() 
			|| pCreature->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) 
			|| pCreature->isFlag( Effect::EFFECT_CLASS_HAS_SWEEPER ) )
		{
			return;
		}

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		Effect* pEffect = NULL;

		// 먼저 뱀파이어 포탈 매니저에서 찾는다.
		EffectManager* pVampirePortalManager = pZone->getVampirePortalManager();

		pEffect = pVampirePortalManager->findEffect(pPacket->getEffectObjectID());

		if (pEffect != NULL)
		{
			//cout << "CGSelectTileEffectHandler::execute() : Effect Exist" << endl;

			switch (pEffect->getEffectClass())
			{
				case Effect::EFFECT_CLASS_VAMPIRE_PORTAL:
					executeVampirePortal(pPacket, pPlayer, pEffect);
					break;
				default:
					Assert(false);
					break;
			}
		}
		else
		{
			cout << "CGSelectTileEffectHandler::execute() : Effect DOES NOT Exist" << endl;

			// 흠... 그런 OID를 가진 이펙트가 없을 때에는 살짝 무시해준다.
		}
	} 
	catch (Throwable & t) 
	{ 
		cerr << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectTileEffectHandler::executeVampirePortal(CGSelectTileEffect* pPacket , Player* pPlayer, Effect* pEffect)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	Assert(pEffect != NULL);
	Assert(pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL);

	try 
	{
		// 게임 플레이어의 상태가 정상이 아니라면 걍 리턴한다.
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);
		if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);
		
		// 뱀파이어만이 이용할 수 있다.
		if (!pCreature->isVampire()) return;

		Zone* pZone = pCreature->getZone();
		Assert(pZone != NULL);

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		Assert(pVampire != NULL);

		EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
		ZONE_COORD zonecoord = pEffectVampirePortal->getZoneCoord();

		// 테메리에로는 갈 수 없다.
		// 원래는 아예 블러디 터널을 만들 수 없도록해야 하지만
		// 이미 좌표가 설정되어 있는 씰이 있어서 어쩔 수 없이 여기서도 막는다.
		if ( zonecoord.id == 1122 || zonecoord.id == 8000 )
		{
			return;
		}

		try {

			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( zonecoord.id );

#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
			// 유료존인데 유료사용중이 아니면...
			// 그리고 패밀리 요금제 적용중인 아니면
			if (pZoneInfo==NULL
				|| (pZoneInfo->isPayPlay() || pZoneInfo->isPremiumZone())
					&& !pGamePlayer->isPayPlaying() && !pGamePlayer->isFamilyFreePass() )
			{
				//Statement* pStmt = NULL;
				string connectIP = pGamePlayer->getSocket()->getHost();

				// 유료 서비스 사용이 가능한가?
				if (pGamePlayer->loginPayPlay(connectIP, pGamePlayer->getID()))
				{
					sendPayInfo(pGamePlayer);
				}
				else if (pZoneInfo->isPayPlay())
				{
					// 유료 서비스 사용 불가인 경우
					GCSystemMessage gcSystemMessage;

					if (g_pConfig->getPropertyInt("IsNetMarble")==0)
					{
						gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
					}
					else
					{
						gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
					}

					pGamePlayer->sendPacket (&gcSystemMessage);

					return;
				}
			}
#endif
		} catch (NoSuchElementException&) {
			return;
		}

		if (pEffectVampirePortal->getCount() > 0)
		{
			// 뱀파이어 자신에게 플래그를 걸어준다.
			// 이는 Zone::addPC에서 뱀파이어가 추가될 때, 주위에다 뿌리는
			// GCAddVampire 에다 포탈로부터 왔음을 알리기 위해서이다.
			// Zone::addPC에서 다시 풀어주면 된다.
			pVampire->setFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);

			// 먼저 주위에다가 뱀파이어가 포탈을 이용해 사라진다는 사실을 알려준다.
			GCEnterVampirePortal gcEnterVampirePortal;
			gcEnterVampirePortal.setObjectID(pVampire->getObjectID());
			gcEnterVampirePortal.setX(pEffectVampirePortal->getX());
			gcEnterVampirePortal.setY(pEffectVampirePortal->getY());
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcEnterVampirePortal);

			pVampire->getGQuestManager()->illegalWarp();
			// 실제로 이동을 시킨다.
			transportCreature(pCreature, zonecoord.id, zonecoord.x, zonecoord.y, false);

			// 이동시켰다면 카운트를 줄이고, 카운트가 0이 되면 이펙트는 사라진다.
			pEffectVampirePortal->setCount(pEffectVampirePortal->getCount()-1);
			//if (pEffectVampirePortal->getCount() == 0) pEffectVampirePortal->setDeadline(0);
		}
	} 
	catch (Throwable & t) 
	{ 
		cerr << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
