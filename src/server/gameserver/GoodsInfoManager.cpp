//////////////////////////////////////////////////////////////////////////////
// Filename    : GoodsInfo.cpp
// Written By  : beowulf
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GoodsInfoManager.h"
#include "Assert1.h"
#include "DB.h"
#include "ItemFactoryManager.h"
#include "ItemInfoManager.h"
#include "ItemUtil.h"

//////////////////////////////////////////////////////////////////////////////
// class GoodsInfo member methods
//////////////////////////////////////////////////////////////////////////////

GoodsInfo::GoodsInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

GoodsInfo::~GoodsInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

string GoodsInfo::toString() const
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "GoodsInfo ("
		<< "Type:"			<< (int)m_ItemType
		<< ",Name:"			<< m_Name
		<< ",ItemClass:"	<< (int)m_ItemClass
		<< ",ItemType:"		<< (int)m_ItemType
		<< ",TimeLimit:"	<< (m_bTimeLimit?"Y":"N")
		<< ",Hour:"			<< m_Hour
		<< ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class GoodsInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

GoodsInfoManager::GoodsInfoManager()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}

GoodsInfoManager::~GoodsInfoManager()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}

void GoodsInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void GoodsInfoManager::clear()
	throw()
{
	__BEGIN_TRY

	HashMapGoodsInfoItr itr = m_GoodsInfos.begin();

	for (; itr != m_GoodsInfos.end(); itr++ )
	{
		SAFE_DELETE(itr->second);
	}

	m_GoodsInfos.clear();
	
	__END_CATCH
}

void GoodsInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	clear();

	Statement* pStmt    = NULL;
	Result*    pResult  = NULL;
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		pResult = pStmt->executeQuery("SELECT GoodsID, Name, ItemClass, ItemType, Grade, OptionType, Num, Limited+0, Hour FROM GoodsListInfo WHERE Kind<>'SET'");

		while (pResult->next()) 
		{
			GoodsInfo* pGoodsInfo = new GoodsInfo();
			int i = 0;

			pGoodsInfo->setID(pResult->getInt(++i));
			pGoodsInfo->setName(pResult->getString(++i));
			pGoodsInfo->setItemClass((Item::ItemClass)(pResult->getInt(++i)));
			pGoodsInfo->setItemType(pResult->getInt(++i));
			pGoodsInfo->setGrade(pResult->getInt(++i));
			string optionField = pResult->getString(++i);
			pGoodsInfo->setNum(pResult->getInt(++i));
			pGoodsInfo->setTimeLimit(pResult->getInt(++i) == 1); // enum('LIMITED'(1), 'UNLIMITED'(2) ) 
			pGoodsInfo->setHour(pResult->getInt(++i));

			list<OptionType_t> optionTypes;
			setOptionTypeFromField(optionTypes, optionField);
			pGoodsInfo->setOptionTypeList(optionTypes);

			addGoodsInfo(pGoodsInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void GoodsInfoManager::addGoodsInfo(GoodsInfo* pGoodsInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert (pGoodsInfo != NULL);

	HashMapGoodsInfoItr itr = m_GoodsInfos.find(pGoodsInfo->getID());

	if (itr != m_GoodsInfos.end() )
		throw DuplicatedException();

	m_GoodsInfos[ pGoodsInfo->getID() ] = pGoodsInfo;

	__END_CATCH
}

GoodsInfo* GoodsInfoManager::getGoodsInfo(DWORD id ) const
	throw()
{
	__BEGIN_TRY

	HashMapGoodsInfoConstItr itr = m_GoodsInfos.find(id);

	if (itr == m_GoodsInfos.end() )
		return NULL;

	return itr->second;

	__END_CATCH
}

string GoodsInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GoodsInfoManager(\n";

	HashMapGoodsInfoConstItr itr = m_GoodsInfos.begin();

	for (; itr != m_GoodsInfos.end(); itr++ )
	{
		msg << "GoodsInfos[" << itr->second->getID() << "] == ";
		msg	<< itr->second->getName();
		msg << "\n";
		msg << itr->second->toString() << "\n";
	}

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
GoodsInfoManager* g_pGoodsInfoManager = NULL;
