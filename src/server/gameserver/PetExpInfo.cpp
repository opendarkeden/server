#include "PetExpInfo.h"
#include "DB.h"

void PetExpInfoManager::clear()
{
	vector<PetExpInfo*>::iterator itr = m_PetExpInfos.begin();
	vector<PetExpInfo*>::iterator endItr = m_PetExpInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( *itr );
	}

	m_PetExpInfos.clear();
}

void PetExpInfoManager::load()
{
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT PetLevel, PetAccumExp FROM PetExpInfo");

		while( pResult->next() )
		{
			PetLevel_t PetLevel = pResult->getInt(1);
			PetExp_t PetExp = pResult->getInt(2);

			m_PetExpInfos[PetLevel] = new PetExpInfo(PetLevel, PetExp);
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )
}

bool PetExpInfoManager::canLevelUp( PetLevel_t level, PetExp_t exp )
{
	if ( level >= PetMaxLevel ) return false;
	PetExpInfo* pPetExpInfo = m_PetExpInfos[level];
	if ( pPetExpInfo == NULL ) return false;

	return pPetExpInfo->getPetGoalExp() <= exp;
}
