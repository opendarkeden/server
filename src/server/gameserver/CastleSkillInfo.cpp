//////////////////////////////////////////////////////////////////////////////
// Filename    : CastleSkillInfo.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CastleSkillInfo.h"
#include "Skill.h"
#include "Assert.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
// class CastleSkillInfo member methods
//////////////////////////////////////////////////////////////////////////////

CastleSkillInfo::CastleSkillInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

CastleSkillInfo::~CastleSkillInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

string CastleSkillInfo::toString() const
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "CastleSkillInfo ("
		<< "SkillType:"         << (int)m_SkillType
		<< ",ZoneID:" << (int)m_ZoneID
		<< ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class CastleSkillInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

CastleSkillInfoManager::CastleSkillInfoManager()
	
{
	__BEGIN_TRY

	__END_CATCH
}

CastleSkillInfoManager::~CastleSkillInfoManager()
	
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void CastleSkillInfoManager::clear()
	
{
	__BEGIN_TRY

	HashMapCastleSkillInfoItor itr = m_CastleSkillInfos.begin();

	for ( ; itr != m_CastleSkillInfos.end() ; ++itr )
	{
		SAFE_DELETE( itr->second );
	}

	m_CastleSkillInfos.clear();

	__END_CATCH
}

void CastleSkillInfoManager::load()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt    = NULL;
	Result*    pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pResult = pStmt->executeQuery("Select SkillType, ZoneID from CastleSkillInfo");

		while (pResult->next()) 
		{
			int count = 0;

			CastleSkillInfo* pCastleSkillInfo = new CastleSkillInfo();

			pCastleSkillInfo->setSkillType( pResult->getInt( ++count ) );
			pCastleSkillInfo->setZoneID( pResult->getInt( ++count ) );

			addCastleSkillInfo( pCastleSkillInfo );
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void CastleSkillInfoManager::addCastleSkillInfo( CastleSkillInfo* pCastleSkillInfo )
	
{
	__BEGIN_TRY

	Assert( pCastleSkillInfo != NULL );

	HashMapCastleSkillInfoItor itr = m_CastleSkillInfos.find( pCastleSkillInfo->getSkillType() );

	if ( itr != m_CastleSkillInfos.end() )
	{
		throw Error("CastleSkillInfoManager::addCastleSkillInfo : 이미 들어가있는 SkillType입니다.");
	}

	m_CastleSkillInfos[ pCastleSkillInfo->getSkillType() ] = pCastleSkillInfo;

	__END_CATCH
}

SkillType_t	CastleSkillInfoManager::getSkillType( ZoneID_t ZoneID ) const
{
	HashMapCastleSkillInfoConstItor itr = m_CastleSkillInfos.begin();

	for ( ; itr != m_CastleSkillInfos.end() ; ++itr )
	{
		CastleSkillInfo* pCastleSkillInfo = itr->second;

		if ( pCastleSkillInfo != NULL && pCastleSkillInfo->getZoneID() == ZoneID )
		{
			return pCastleSkillInfo->getSkillType();
		}
	}

	// 없다.
	return SKILL_MAX;
}

ZoneID_t CastleSkillInfoManager::getZoneID( SkillType_t SkillType ) const
{
	HashMapCastleSkillInfoConstItor itr = m_CastleSkillInfos.find( SkillType );

	if ( itr != m_CastleSkillInfos.end() )
	{
		return itr->second->getZoneID();
	}

	return 0;
}

string CastleSkillInfoManager::toString() const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "CastleSkillInfoManager(";

	HashMapCastleSkillInfoConstItor itr = m_CastleSkillInfos.begin();

	for ( ; itr != m_CastleSkillInfos.end() ; ++itr )
	{
		msg << itr->second->toString();
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
CastleSkillInfoManager* g_pCastleSkillInfoManager = NULL;
