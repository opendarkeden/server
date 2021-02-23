//////////////////////////////////////////////////////////////////////////////
// Filename    : DefaultOptionSetInfo.cpp
// Written By  : ¹èÀçÇü
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "DefaultOptionSetInfo.h"
#include "DB.h"
#include "ItemUtil.h"


//////////////////////////////////////////////////////////////////////////////
// DefalutOptionSetInfo class
//////////////////////////////////////////////////////////////////////////////
DefaultOptionSetInfo::DefaultOptionSetInfo()
{
}

DefaultOptionSetInfo::~DefaultOptionSetInfo()
{
}


//////////////////////////////////////////////////////////////////////////////
// global varible initialization
//////////////////////////////////////////////////////////////////////////////
DefaultOptionSetInfoManager* g_pDefaultOptionSetInfoManager = NULL;

//////////////////////////////////////////////////////////////////////////////
// DefalutOptionSetInfoManager class
//////////////////////////////////////////////////////////////////////////////
DefaultOptionSetInfoManager::DefaultOptionSetInfoManager()
{
}

DefaultOptionSetInfoManager::~DefaultOptionSetInfoManager()
{
}

void DefaultOptionSetInfoManager::load()
	throw()
{
	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( "SELECT Type, OptionList FROM DefaultOptionSetInfo" );

		while ( pResult->next() )
		{
			uint i = 0;

			DefaultOptionSetInfo* pDefaultOptionSetInfo = new DefaultOptionSetInfo();

			pDefaultOptionSetInfo->setType( (DefaultOptionSetType_t)pResult->getInt(++i) );
			string optionField = pResult->getString(++i);
			list<OptionType_t> optionList;
			makeOptionList( optionField, optionList );
			pDefaultOptionSetInfo->setOptionTypeList( optionList );

			addDefaultOptionSetInfo( pDefaultOptionSetInfo );
		}
	}
	END_DB(pStmt)
}

DefaultOptionSetInfo* DefaultOptionSetInfoManager::getDefaultOptionSetInfo( DefaultOptionSetType_t type )
{
	HashMapDefaultOptionSetInfoItor itr = m_DefaultOptionSetInfos.find( type );

	if ( itr == m_DefaultOptionSetInfos.end() )
		return NULL;

	return itr->second;
}

void DefaultOptionSetInfoManager::addDefaultOptionSetInfo( DefaultOptionSetInfo* pDefaultOptionSetInfo )
	throw(DuplicatedException, Error)
{
	HashMapDefaultOptionSetInfoItor itr = m_DefaultOptionSetInfos.find( pDefaultOptionSetInfo->getType() );

	if ( itr != m_DefaultOptionSetInfos.end() )
	{
		throw DuplicatedException();
		return;
	}

	m_DefaultOptionSetInfos[pDefaultOptionSetInfo->getType()] = pDefaultOptionSetInfo;
}

