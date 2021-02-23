////////////////////////////////////////////////////////////////////////////////
// Filename    : ShopTemplate.cpp
// Written By  : ±è¼º¹Î
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "ShopTemplate.h"
#include "DB.h"

////////////////////////////////////////////////////////////////////////////////
// global varible initialization
////////////////////////////////////////////////////////////////////////////////
ShopTemplateManager* g_pShopTemplateManager = NULL;

////////////////////////////////////////////////////////////////////////////////
// class ShopTemplate member methods
////////////////////////////////////////////////////////////////////////////////

ShopTemplate::ShopTemplate()
	throw()
{
	__BEGIN_TRY
	
	m_ID             = 0;
	m_RackType       = 0;
	m_ItemClass      = 0;
	m_MinItemType    = 0;
	m_MaxItemType    = 0;
	m_MinOptionLevel  = 0;
	m_MaxOptionLevel  = 0;
		
	__END_CATCH
}

ShopTemplate::~ShopTemplate()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

string ShopTemplate::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ShopTemplate("
		<< "TemplateID : "     << (int)m_ID
		<< ",RackType : "      << (int)m_RackType 
		<< ",ItemClass : "     << (int)m_ItemClass
		<< ",MinItemType : "   << (int)m_MinItemType
		<< ",MaxItemType : "   << (int)m_MaxItemType
		<< ",MinOptionLevel : " << (int)m_MinOptionLevel
		<< ",MaxOptionLevel : " << (int)m_MaxOptionLevel 
		<< ")";
	return msg.toString();
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// class ShopTemplateManager member methods
////////////////////////////////////////////////////////////////////////////////

ShopTemplateManager::ShopTemplateManager()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}

ShopTemplateManager::~ShopTemplateManager()
	throw()
{
	__BEGIN_TRY
		
	hash_map<ShopTemplateID_t, ShopTemplate*>::iterator itr = m_Entries.begin();
	for (; itr != m_Entries.end(); itr++)
	{
		ShopTemplate* pTemplate = itr->second;
		SAFE_DELETE(pTemplate);
	}

	m_Entries.clear();

	__END_CATCH
}

void ShopTemplateManager::init() 
	throw (Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void ShopTemplateManager::load() 
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;
	
	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ID, ShopType, ItemClass, MinItemType, MaxItemType, MinOptionLevel, MaxOptionLevel FROM ShopTemplate");

		while (pResult->next()) 
		{
			ShopTemplate* pTemplate = new ShopTemplate();

			pTemplate->setID(pResult->getInt(1));
			pTemplate->setShopType(pResult->getInt(2));
			pTemplate->setItemClass(pResult->getInt(3));
			pTemplate->setMinItemType(pResult->getInt(4));
			pTemplate->setMaxItemType(pResult->getInt(5));
			pTemplate->setMinOptionLevel(pResult->getInt(6));
			pTemplate->setMaxOptionLevel(pResult->getInt(7));

			setTemplate(pTemplate->getID(), pTemplate);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

ShopTemplate* ShopTemplateManager::getTemplate(ShopTemplateID_t id) const 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map<ShopTemplateID_t, ShopTemplate*>::const_iterator itr = m_Entries.find(id);

	if (itr == m_Entries.end())
	{
		cerr << "ShopTemplateManager::getTemplate() : NoSuchElementException" << endl;
		throw NoSuchElementException("template not exist.");
	}

	return itr->second;

	__END_CATCH
}

void ShopTemplateManager::setTemplate(ShopTemplateID_t id, ShopTemplate* pTemplate) 
	throw ()
{
	__BEGIN_TRY

	hash_map<ShopTemplateID_t, ShopTemplate*>::iterator itr = m_Entries.find(id);

	if (itr != m_Entries.end()) throw ("ShopTemplateManager::setTemplate() : Same ID already exist!");

	m_Entries[id] = pTemplate;

	__END_CATCH
}

string ShopTemplateManager::toString() const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ShopTemplateManager(";
	hash_map<ShopTemplateID_t, ShopTemplate*>::const_iterator itr = m_Entries.begin();
	for (; itr != m_Entries.end(); itr++) 
		msg << "(ShopTemplate:" << (int)(itr->first) << "," << itr->second->toString() << ")"; msg << ")";
	return msg.toString();

	__END_CATCH
}

