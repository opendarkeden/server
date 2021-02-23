#include "GQuestAdvanceClassElement.h"
#include "PlayerCreature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Gpackets/GCModifyInformation.h"
#include "Player.h"
#include "SkillDomainInfoManager.h"
#include "VampEXPInfo.h"
#include "OustersEXPInfo.h"

GQuestElement::ResultType GQuestAdvanceClassElement::checkCondition( PlayerCreature* pPC ) const
{
	if ( pPC->getLevel() != 150 ) return FAIL;
	Exp_t advExp = 0;
	if ( pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		SkillDomainType_t domain = pSlayer->getHighestSkillDomain();
		DomainInfo* pDomainInfo = g_pSkillDomainInfoManager->getDomainInfo((SkillDomain)domain, pPC->getLevel());
		if ( pDomainInfo == NULL ) return FAIL;
		Exp_t goalExp = pDomainInfo->getGoalExp();
		Exp_t currentExp = goalExp - pSlayer->getGoalExp(domain);
		cout << pPC->getName() << "의 현재 경험치 : " << currentExp << endl;
		advExp = (Exp_t)(currentExp * 0.0688933574);
	}
	else if ( pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		VampEXPInfo* pExpInfo = g_pVampEXPInfoManager->getVampEXPInfo( pVampire->getLevel() );
		if ( pExpInfo == NULL ) return FAIL;
		Exp_t goalExp = pExpInfo->getGoalExp();
		Exp_t currentExp = goalExp - pVampire->getGoalExp();
		cout << pPC->getName() << "의 현재 경험치 : " << currentExp << endl;
		advExp = currentExp / 100;
	}
	else if ( pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		OustersEXPInfo* pExpInfo = g_pOustersEXPInfoManager->getOustersEXPInfo( pOusters->getLevel() );
		if ( pExpInfo == NULL ) return FAIL;
		Exp_t goalExp = pExpInfo->getGoalExp();
		Exp_t currentExp = goalExp - pOusters->getGoalExp();
		cout << pPC->getName() << "의 현재 경험치 : " << currentExp << endl;
		advExp = currentExp / 100;
	}

	advExp = min( (int)advExp, 18496191 );
	// 하드코딩 -_-
	pPC->increaseAdvancementClassExp( advExp, false );

	return OK;
}

GQuestAdvanceClassElement* GQuestAdvanceClassElement::makeElement(XMLTree* pTree)
{
	GQuestAdvanceClassElement* pRet = new GQuestAdvanceClassElement;

	return pRet;
}

GQuestAdvanceClassElement g_AdvanceClassElement;
