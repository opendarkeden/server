#include "LevelNickInfoManager.h"
#include "DB.h"
#include "Creature.h"

void LevelNickInfoManager::clear()
{
	hash_map<Level_t, vector<LevelNickInfo*> >::iterator itr = m_LevelNickInfoMap.begin();
	hash_map<Level_t, vector<LevelNickInfo*> >::iterator endItr = m_LevelNickInfoMap.end();

	for ( ; itr != endItr ; ++itr )
	{
		vector<LevelNickInfo*>::iterator vitr = itr->second.begin();
		vector<LevelNickInfo*>::iterator eitr = itr->second.end();

		for ( ; vitr != eitr ; ++vitr )
		{
			SAFE_DELETE( (*vitr) );
		}
	}

	m_LevelNickInfoMap.clear();
}

void LevelNickInfoManager::load()
{
	clear();
	Statement *pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT NickIndex, Race, Level10 FROM NicknameIndex WHERE NickType='LEVEL'" );

		while ( pResult->next() )
		{
			DWORD index = pResult->getInt(1);
			Race_t race = pResult->getInt(2);
			Level_t level10 = pResult->getInt(3);

			LevelNickInfo* pInfo = new LevelNickInfo(race, level10, index);

			m_LevelNickInfoMap[level10].push_back( pInfo );
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )
}

bool LevelNickInfo::isFitRace(Creature* pCreature) const
{
	return m_Race == 3 || pCreature->getRace()==m_Race;
}
