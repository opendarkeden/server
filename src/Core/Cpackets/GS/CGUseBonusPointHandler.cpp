//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseBonusPointHandler.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGUseBonusPoint.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "SkillHandlerManager.h"
	#include "SkillInfo.h"
	#include "SkillParentInfo.h"
	#include "Creature.h"
	#include "LogClient.h"
	#include "Slayer.h"

	#include "Gpackets/GCUseBonusPointFail.h"
	#include "Gpackets/GCUseBonusPointOK.h"
	#include "Gpackets/GCLearnSkillReady.h"
#endif	

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseBonusPointHandler::execute (CGUseBonusPoint* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 정상적인 상태가 아니라면 리턴
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	if (pGamePlayer->getPlayerStatus() != GPS_NORMAL) return;

	Creature*      pCreature  = pGamePlayer->getCreature();
	BYTE           which      = pPacket->getWhich();
	Attr_t         cur        = 0;

	if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		if ( pSlayer->getBonus() <= 0 )
		{
			GCUseBonusPointFail failPkt;
			pPlayer->sendPacket(&failPkt);
			return;
		}

		bool success = false;
		if ( which == INC_INT )
		{
			success = pSlayer->putAdvancedBonusToINT();
		}
		else if (which == INC_STR)
		{
			success = pSlayer->putAdvancedBonusToSTR();
		}
		else if (which == INC_DEX)
		{
			success = pSlayer->putAdvancedBonusToDEX();
		}

		if ( success )
		{
			GCUseBonusPointOK okpkt;
			pGamePlayer->sendPacket (&okpkt);

			pSlayer->saveExps();
			pSlayer->initAllStatAndSend();
		}
		else
		{
			GCUseBonusPointFail failPkt;
			pPlayer->sendPacket(&failPkt);
			return;
		}
	}
	else if ( pCreature->isVampire() ) 
	{
		// 보너스 포인트가 없다면 리턴
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		if (pVampire->getBonus() <= 0)
		{
			GCUseBonusPointFail failPkt;
			pPlayer->sendPacket(&failPkt);
			return;
		}

		VAMPIRE_RECORD oldRecord;
		// 능력치를 올리기 전에 기존의 능력치를 저장한다.
		pVampire->getVampireRecord(oldRecord);

		if (which == INC_INT)
		{
			cur = pVampire->getINT(ATTR_BASIC) + 1;
			pVampire->setINT(cur, ATTR_BASIC);

			StringStream sst;
			sst << "INTE = " << (int)cur;
			pVampire->tinysave(sst.toString());
			
			/*
			// INT가 증가하면 새로운 기술을 배울 수 있는 가능성이 있다.
			SkillType_t lastSkill = pVampire->findLastSkill();


			// lastSkill의 다음 level의 기술을 찾는다.
			// 못찾았다면 더이상 배울것이 없다는 것.
			for(int i = SKILL_BLOOD_DRAIN + 1 ; i < SKILL_MAX; i++)
			{
				SkillParentInfo* pParentInfo = g_pSkillParentInfoManager->getSkillParentInfo(i);

				if (pParentInfo->hasParent(lastSkill))// 찾았다!
				{
					SkillInfo* pNewSkillInfo = g_pSkillInfoManager->getSkillInfo(i);
					if (pNewSkillInfo->getEXP() <= cur && pVampire->hasSkill(i) == NULL)
					{
						//cout << "(" << pVampire->getName() << ") can learn new skill >> ";

						// 새로운 기술을 배울 수 있다.
						GCLearnSkillReady gcLSR;
						gcLSR.setSkillDomainType(SKILL_DOMAIN_VAMPIRE);
						pVampire->getPlayer()->sendPacket(&gcLSR);
						break;
					}
				}

			}
			*/

			log(LOG_USE_BONUS_POINT, pVampire->getName(), "", "INT");
		}
		else if (which == INC_STR)
		{
			cur = pVampire->getSTR(ATTR_BASIC) + 1;
			pVampire->setSTR(cur, ATTR_BASIC);

			StringStream sst;
			sst << "STR = " << (int)cur;
			pVampire->tinysave(sst.toString());

			log(LOG_USE_BONUS_POINT, pVampire->getName(), "", "STR");
		}
		else if (which == INC_DEX)
		{
			cur = pVampire->getDEX(ATTR_BASIC) + 1;
			pVampire->setDEX(cur, ATTR_BASIC);

			StringStream sst;
			sst << "DEX = " << (int)cur;
			pVampire->tinysave(sst.toString());

			log(LOG_USE_BONUS_POINT, pVampire->getName(), "", "DEX");
		}

		// 바뀐 보너스 포인트를 저장한다.
		Bonus_t OldBonus = pVampire->getBonus();
		pVampire->setBonus(OldBonus - 1);
		StringStream sst;
		sst << "Bonus = " << (int)(OldBonus - 1);
		pVampire->tinysave(sst.toString());

		// 능력치가 변화되었으니, stat을 새로 고친다.
		pVampire->initAllStat();
		
		// 클라이언트의 계산 순서 때문에 생기는 버그로 인하여,
		// 먼저 인증 패킷을 날려준 후에, 바뀐 능력치에 대한 정보를 보낸다.
		// 나중에 CGUseBonusPointOK에다 바로 바뀐 능력치에 대한 정보를 
		// 실어보내도록 해야 한다.

		// OK 패킷을 보내준다.
		GCUseBonusPointOK okpkt;
		pGamePlayer->sendPacket (&okpkt);

		// 바뀐 능력치에 관한 정보를 보내준다.
		pVampire->sendModifyInfo(oldRecord);
		pVampire->sendRealWearingInfo();
	}
	else if ( pCreature->isOusters() ) 
	{
		// 보너스 포인트가 없다면 리턴
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		if (pOusters->getBonus() <= 0)
		{
			GCUseBonusPointFail failPkt;
			pPlayer->sendPacket(&failPkt);
			return;
		}

		OUSTERS_RECORD oldRecord;
		// 능력치를 올리기 전에 기존의 능력치를 저장한다.
		pOusters->getOustersRecord(oldRecord);

		if (which == INC_INT)
		{
			cur = pOusters->getINT(ATTR_BASIC) + 1;
			pOusters->setINT(cur, ATTR_BASIC);

			StringStream sst;
			sst << "INTE = " << (int)cur;
			pOusters->tinysave(sst.toString());
		}
		else if (which == INC_STR)
		{
			cur = pOusters->getSTR(ATTR_BASIC) + 1;
			pOusters->setSTR(cur, ATTR_BASIC);

			StringStream sst;
			sst << "STR = " << (int)cur;
			pOusters->tinysave(sst.toString());
		}
		else if (which == INC_DEX)
		{
			cur = pOusters->getDEX(ATTR_BASIC) + 1;
			pOusters->setDEX(cur, ATTR_BASIC);

			StringStream sst;
			sst << "DEX = " << (int)cur;
			pOusters->tinysave(sst.toString());
		}

		// 바뀐 보너스 포인트를 저장한다.
		Bonus_t OldBonus = pOusters->getBonus();
		pOusters->setBonus(OldBonus - 1);
		StringStream sst;
		sst << "Bonus = " << (int)(OldBonus - 1);
		pOusters->tinysave(sst.toString());

		// 능력치가 변화되었으니, stat을 새로 고친다.
		pOusters->initAllStat();
		
		// OK 패킷을 보내준다.
		GCUseBonusPointOK okpkt;
		pGamePlayer->sendPacket(&okpkt);

		// 바뀐 능력치에 관한 정보를 보내준다.
		pOusters->sendModifyInfo(oldRecord);
		pOusters->sendRealWearingInfo();
	}
	else
	{
		GCUseBonusPointFail failPkt;
		pPlayer->sendPacket(&failPkt);
		return;
	}


#endif	// __GAME_SERVER__

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
