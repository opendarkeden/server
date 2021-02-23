//////////////////////////////////////////////////////////////////////////////
// Filename    : CGResurrectHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGResurrect.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Effect.h"
	#include "EffectComa.h"
	#include "EffectManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGResurrectHandler::execute (CGResurrect* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	if (pCreature->findEffect( Effect::EFFECT_CLASS_ETERNITY )) return;

	// 현재 크리쳐에게 COMA 이펙트가 붙어있지 않다면 에러다. 
	if (pCreature->isFlag(Effect::EFFECT_CLASS_COMA))
	{
		//cout << "플래그 붙어있음." << endl;

		// COMA 이펙트에 접근한다.
		EffectManager* pEffectManager = pCreature->getEffectManager();
		Assert(pEffectManager != NULL);

		EffectComa* pEffectComa = (EffectComa*)(pEffectManager->findEffect(Effect::EFFECT_CLASS_COMA));
		Assert(pEffectComa != NULL);

		// 죽은 지 5초가 아직 지나지 않았다면, 되살아날 수 없다.
		if (pEffectComa->canResurrect())
		{
			//cout << "5초가 지났으니 부활시킬 수 있음." << endl;

			/*
			if (pCreature->isSlayer())
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				//cout << "현재 HP:" << pSlayer->getHP(ATTR_CURRENT);
			}
			else if (pCreature->isVampire())
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				//cout << "현재 HP:" << pVampire->getHP(ATTR_CURRENT);
			}
			*/

			// 데드라인을 0으로 만들어준다. 이렇게 하면 하트비트에서
			// unaffect되면서 플레이어를 자동으로 부활시키게 된다.
			pEffectComa->setDeadline(0);
		}
		else
		{
			//cout << "5초가 지나지 않았다." << endl;
		}
	}
	else
	{
		//cout << "플래그가 없다." << endl;

		// 어디서인지는 확실히 알 수 없으나, 어딘가에서 죽은 뒤에
		// 코마 이펙트가 날아가 버리거나, 죽은 상태에서 HP가 올라가는 현상이 
		// 발생하는 듯 하다. 그래서 이펙트 걸려있지 않은 상황에서 패킷
		// 날아오면 강제로 죽이는 코드를 집어넣는다.
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			pSlayer->setHP(0, ATTR_CURRENT);
			pSlayer->deleteEffect(Effect::EFFECT_CLASS_COMA);

			EffectComa* pEffectComa = new EffectComa(pSlayer);
			pEffectComa->setStartTime();
			pEffectComa->setDeadline(0);
			pSlayer->addEffect(pEffectComa);
			pSlayer->setFlag(Effect::EFFECT_CLASS_COMA);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			pVampire->setHP(0, ATTR_CURRENT);
			pVampire->deleteEffect(Effect::EFFECT_CLASS_COMA);

			EffectComa* pEffectComa = new EffectComa(pVampire);
			pEffectComa->setStartTime();
			pEffectComa->setDeadline(0);
			pVampire->addEffect(pEffectComa);
			pVampire->setFlag(Effect::EFFECT_CLASS_COMA);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			pOusters->setHP(0, ATTR_CURRENT);
			pOusters->deleteEffect(Effect::EFFECT_CLASS_COMA);

			EffectComa* pEffectComa = new EffectComa(pOusters);
			pEffectComa->setStartTime();
			pEffectComa->setDeadline(0);
			pOusters->addEffect(pEffectComa);
			pOusters->setFlag(Effect::EFFECT_CLASS_COMA);
		}
		else
		{
			Assert(false);
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

