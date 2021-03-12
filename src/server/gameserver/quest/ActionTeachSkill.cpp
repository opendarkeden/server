////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTeachSkill.cpp
// Written By  : 
// Description : 
// NPC가 플레이어에게 기술을 가르쳐 줄 때 쓰이는 액션이다.
// 실제적으로는 NPC가 가르쳐 줄 수 있는 기술을 패킷으로
// 전송해 줄 뿐이고, 나머지 작업들은 패킷이 왕복하는 사이에
// 처리된다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionTeachSkill.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "SkillInfo.h"
#include "Gpackets/GCTeachSkillInfo.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTeachSkill::read (PropertyBuffer & propertyBuffer)
    
{
	__BEGIN_TRY

	try 
	{
		// 도메인 타입을 읽어들인다.
		string domainType = propertyBuffer.getProperty("DomainType");

		if (domainType == "BLADE")        m_DomainType = SKILL_DOMAIN_BLADE;
		else if (domainType == "SWORD")   m_DomainType = SKILL_DOMAIN_SWORD;
		else if (domainType == "GUN")     m_DomainType = SKILL_DOMAIN_GUN;
		//else if (domainType == "RIFLE")   m_DomainType = SKILL_DOMAIN_RIFLE;
		else if (domainType == "ENCHANT") m_DomainType = SKILL_DOMAIN_ENCHANT;
		else if (domainType == "HEAL")    m_DomainType = SKILL_DOMAIN_HEAL;
		else if (domainType == "ETC")     m_DomainType = SKILL_DOMAIN_ETC;
		else if (domainType == "VAMPIRE") m_DomainType = SKILL_DOMAIN_VAMPIRE;
		else throw Error("TeachSkill::read() : 잘못된 기술 타입입니다.");
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
void ActionTeachSkill::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	// 일단 클라이언트를 위해서 OK 패킷을 함 날린다.
	GCNPCResponse okpkt;
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&okpkt);

	if (pCreature2->isSlayer())       executeSlayer(pCreature1, pCreature2);
	else if (pCreature2->isVampire()) executeVampire(pCreature1, pCreature2);
	else throw ("ActionTeachSkill::execute() : 알 수 없는 플레이어 크리쳐입니다!");

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionTeachSkill::executeSlayer (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Slayer*          pSlayer = dynamic_cast<Slayer*>(pCreature2);
	Player*          pPlayer = pCreature2->getPlayer();
	GCTeachSkillInfo teachinfo;

	Assert(pPlayer != NULL);

	// 일단 기술을 배울 수 있는지 체크를 한다.
	if (pSlayer->getGoalExp(m_DomainType) != 0)
	{
		// 패킷을 만들어 가지고...
		teachinfo.setDomainType(m_DomainType);
		teachinfo.setTargetLevel(0);
		pPlayer->sendPacket(&teachinfo);
		return;
	}

	Level_t     DomainLevel = pSlayer->getSkillDomainLevel(m_DomainType);
	SkillType_t SkillType   = g_pSkillInfoManager->getSkillTypeByLevel(m_DomainType, DomainLevel);

	/*

	// 크리쳐가 배울 수 있는 기술의 레벨을 확인한다.
	LastLearnSkillType = pSlayer->findLastSkill();

	// 플레이어가 배운 기술이 하나도 없다면 다음 배울 기술은 1레벨이다.
	// 플레이어가 모든 기술을 배웠다면 정해놓은 상수를 보내준다.
	if (LastLearnSkillType == 0)
	{
		targetLevel = 1;
	}
	else if (LastLearnSkillType == SKILL_MAX)
	{
		targetLevel = ALL_SKILL_LEARNED;
	}
	else
	{
		pSkillInfo  = g_pSkillInfoManager->getSkillInfo(LastLearnSkillType);
		targetLevel = pSkillInfo->getLevel() + 1;
	}
	*/

	// 패킷을 만들어 가지고...
	teachinfo.setDomainType(m_DomainType);
	teachinfo.setTargetLevel(SkillType);

	pPlayer->sendPacket(&teachinfo);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionTeachSkill::executeVampire (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);

	/*
	// 크리쳐가 배울 수 있는 기술의 레벨을 확인한다.
	SkillType_t  LastLearnSkillType = pVampire->findLastSkill();
	SkillInfo*   pSkillInfo         = NULL;
	SkillLevel_t targetLevel        = 0;

	// 플레이어가 배운 기술이 하나도 없다면 다음 배울 기술은 1레벨이다.
	// 플레이어가 모든 기술을 배웠다면 정해놓은 상수를 보내준다.
	if (LastLearnSkillType == 0)
	{
		targetLevel = 1;
	}
	else if (LastLearnSkillType == SKILL_MAX) 
	{
		targetLevel = ALL_SKILL_LEARNED;
	}
	else
	{
		pSkillInfo  = g_pSkillInfoManager->getSkillInfo(LastLearnSkillType);
		targetLevel = pSkillInfo->getLevel() + 1;
	}
	*/

	Level_t DomainLevel = pVampire->getLevel();

	SkillType_t SkillType = g_pSkillInfoManager->getSkillTypeByLevel(m_DomainType, DomainLevel);


	// 패킷을 만들어 가지고...
	GCTeachSkillInfo teachinfo;
	teachinfo.setDomainType(m_DomainType);
	teachinfo.setTargetLevel(SkillType);

	// 전송한다.
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);
	pPlayer->sendPacket(&teachinfo);

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTeachSkill::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTeachSkill(" << ")";
	return msg.toString();

	__END_CATCH
}
