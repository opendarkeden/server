////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTakeDonation.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionTakeDonation.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionTakeDonation::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try
	{
		// 받을 돈의 양을 읽어들인다.
		m_Amount = (Gold_t)propertyBuffer.getPropertyInt("Amount");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionTakeDonation::execute (Creature * pCreature1, Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	int oldAlignment = 0;
	int newAlignment = 0;

	GCNPCResponse       gcNPCResponse;
	GCModifyInformation gcModifyInformation;

	if (pCreature2->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);

		// 기부량보다 가진 돈이 적다면 기부할 수가 없다. 
		if (pSlayer->getGold() < m_Amount)
		{
			gcNPCResponse.setCode(NPC_RESPONSE_DONATION_FAIL_MONEY);
			pPlayer->sendPacket(&gcNPCResponse);
			return;
		}

		// 기부 금액에 따라 성향을 회복시켜준다.
		oldAlignment = pSlayer->getAlignment();
		newAlignment = pSlayer->getAlignment();

		// 성향이 -2500 이하일 경우에만 변화한다.
		if (oldAlignment < -2500)
		{
			if (-4999 <= oldAlignment && oldAlignment <= -2500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/100));
			}
			else if (-7499 <= oldAlignment && oldAlignment <= -5000)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/200));
			}
			else if (-10000 <= oldAlignment && oldAlignment <= -7500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/500));
			}

			pSlayer->saveAlignment(newAlignment);
		}

		// 기부금액만큼 돈을 줄인다.
		//pSlayer->setGoldEx(pSlayer->getGold() - m_Amount);
		// by sigi. 2002.9.17
		pSlayer->decreaseGoldEx(m_Amount);

		// 패킷을 보낸다.
		gcNPCResponse.setCode(NPC_RESPONSE_DONATION_OK);
		gcNPCResponse.setParameter(pSlayer->getGold());
		pPlayer->sendPacket(&gcNPCResponse);

		gcModifyInformation.addShortData(MODIFY_ALIGNMENT, pSlayer->getAlignment());
		pPlayer->sendPacket(&gcModifyInformation);
	}
	else if (pCreature2->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);

		// 기부량보다 가진 돈이 적다면 기부할 수가 없다. 
		if (pVampire->getGold() < m_Amount)
		{
			gcNPCResponse.setCode(NPC_RESPONSE_DONATION_FAIL_MONEY);
			pPlayer->sendPacket(&gcNPCResponse);
			return;
		}

		// 기부 금액에 따라 성향을 회복시켜준다.
		oldAlignment = pVampire->getAlignment();
		newAlignment = pVampire->getAlignment();

		// 성향이 -2500 이하일 경우에만 변화한다.
		if (oldAlignment < -2500)
		{
			if (-4999 <= oldAlignment && oldAlignment <= -2500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/100));
			}
			else if (-7499 <= oldAlignment && oldAlignment <= -5000)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/200));
			}
			else if (-10000 <= oldAlignment && oldAlignment <= -7500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/500));
			}

			pVampire->saveAlignment(newAlignment);
		}

		// 기부금액만큼 돈을 줄인다.
		//pVampire->setGoldEx(pVampire->getGold() - m_Amount);
		// by sigi. 2002.9.18
		pVampire->decreaseGoldEx(m_Amount);

		// 패킷을 보낸다.
		gcNPCResponse.setCode(NPC_RESPONSE_DONATION_OK);
		gcNPCResponse.setParameter(pVampire->getGold());
		pPlayer->sendPacket(&gcNPCResponse);

		gcModifyInformation.addShortData(MODIFY_ALIGNMENT, pVampire->getAlignment());
		pPlayer->sendPacket(&gcModifyInformation);
	}
	else if (pCreature2->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);

		// 기부량보다 가진 돈이 적다면 기부할 수가 없다. 
		if (pOusters->getGold() < m_Amount)
		{
			gcNPCResponse.setCode(NPC_RESPONSE_DONATION_FAIL_MONEY);
			pPlayer->sendPacket(&gcNPCResponse);
			return;
		}

		// 기부 금액에 따라 성향을 회복시켜준다.
		oldAlignment = pOusters->getAlignment();
		newAlignment = pOusters->getAlignment();

		// 성향이 -2500 이하일 경우에만 변화한다.
		if (oldAlignment < -2500)
		{
			if (-4999 <= oldAlignment && oldAlignment <= -2500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/100));
			}
			else if (-7499 <= oldAlignment && oldAlignment <= -5000)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/200));
			}
			else if (-10000 <= oldAlignment && oldAlignment <= -7500)
			{
				newAlignment = min(-2500, (int)(oldAlignment + m_Amount/500));
			}

			pOusters->saveAlignment(newAlignment);
		}

		// 기부금액만큼 돈을 줄인다.
		//pOusters->setGoldEx(pOusters->getGold() - m_Amount);
		// by sigi. 2002.9.18
		pOusters->decreaseGoldEx(m_Amount);

		// 패킷을 보낸다.
		gcNPCResponse.setCode(NPC_RESPONSE_DONATION_OK);
		gcNPCResponse.setParameter(pOusters->getGold());
		pPlayer->sendPacket(&gcNPCResponse);

		gcModifyInformation.addShortData(MODIFY_ALIGNMENT, pOusters->getAlignment());
		pPlayer->sendPacket(&gcModifyInformation);
	}
	else Assert(false);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTakeDonation::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTakeDonation("
		<< "Amount:" << (int)m_Amount
		<< ")";
	return msg.toString();

	__END_CATCH
}
