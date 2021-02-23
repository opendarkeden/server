//----------------------------------------------------------------------
//
// Filename    : SkillParentInfo.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#include "SkillParentInfo.h"
#include "DB.h"
#include "Assert.h"
#include <algo.h>

//----------------------------------------------------------------------
//
// constructor
//
//----------------------------------------------------------------------
SkillParentInfo::SkillParentInfo (SkillType_t SkillType) 
	throw () 
: m_SkillType(SkillType)
{
	__BEGIN_TRY
	init();
	__END_CATCH
}


//----------------------------------------------------------------------
//
// destructor
//
//----------------------------------------------------------------------
SkillParentInfo::~SkillParentInfo () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//----------------------------------------------------------------------
//
// SkillParentInfo::init()
//
//----------------------------------------------------------------------
void SkillParentInfo::init ()
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}


//----------------------------------------------------------------------
//
// SkillParentInfo::hasParent()
//
// 특정 타입을 가지는 부모가 있는지 확인한다.
//
//----------------------------------------------------------------------
bool SkillParentInfo::hasParent (SkillType_t SkillType)
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	try 
	{
		SkillType_t FirstType = m_Parents.front();

		if (FirstType == 0) return true;

		list<SkillType_t>::iterator itr = find(m_Parents.begin(), m_Parents.end() , SkillType);

		if (itr == m_Parents.end()) return false;

		return true;
	}
	catch(Throwable & t) 
	{
		//cerr << t.toString() << endl;
	}
	return false;

	__END_CATCH
}


//----------------------------------------------------------------------
// 적 리스트의 특정 위치의 크리처의 아이디를 리턴한다.
//----------------------------------------------------------------------
SkillType_t SkillParentInfo::getParents (SkillType_t SkillType) const
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	for (list<SkillType_t>::const_iterator itr = m_Parents.begin() ; itr != m_Parents.end() ; itr ++) 
	{
		if (SkillType == (*itr)) return *itr;
	}

	cerr << "SkillParentInfo::getParents() : NoSuchElementException" << endl;
	throw NoSuchElementException();

	__END_CATCH
}


//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string SkillParentInfo::toString () const
	throw ()
{

	__BEGIN_TRY

	StringStream msg;

	msg << "SkillParentInfo("
			<< "SkillType:" << (int)m_SkillType
			<< ",Parents(";

	for (list<SkillType_t>::const_iterator i = m_Parents.begin(); i != m_Parents.end(); i++)
	{
		msg << (int)(*i) << " ";
	}
	msg << ")";
	msg << ")";

	return msg.toString();

	__END_CATCH
}






//--------------------------------------------------------------------
//
// constructor
//
//--------------------------------------------------------------------
SkillParentInfoManager::SkillParentInfoManager()
	throw()
: m_SkillCount(0), m_SkillParentInfoList(NULL)
{
	__BEGIN_TRY
	__END_CATCH
}

//--------------------------------------------------------------------
//
// destructor
//
//--------------------------------------------------------------------
SkillParentInfoManager::~SkillParentInfoManager()
	throw()
{
	__BEGIN_TRY

	// 덜 지웠음둥 -_-; by sigi

	SAFE_DELETE_ARRAY(m_SkillParentInfoList);
	
	__END_CATCH
}

//--------------------------------------------------------------------
//
// SkillParentInfoManager:: init()
//
//--------------------------------------------------------------------
void SkillParentInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	// Loading from DataBase and addSkillParentInfo
	load();

	__END_CATCH
}

//--------------------------------------------------------------------
//
// SkillParentInfoManager:: load()
//
//--------------------------------------------------------------------
void SkillParentInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

    Statement  * pStmt = NULL;	// by sigi
    Result     * pResult;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(SkillType) FROM SkillTreeInfo");

		if (pResult -> getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in SkillTreeInfo Table");
		}

		pResult->next();

		m_SkillCount = pResult->getInt(1) +1;

		Assert (m_SkillCount > 0);

		m_SkillParentInfoList = new SkillParentInfo* [m_SkillCount];

		for (uint i = 0 ; i < m_SkillCount ; i ++)
			m_SkillParentInfoList[i] = NULL;
		
		pResult = pStmt->executeQuery("SELECT SkillType, Parent FROM SkillTreeInfo ");

		//cout<<"======= SkillParentInfo Manager ==========="<<endl;
	
		SkillType_t tempSkillType = 0;

		while (pResult->next()) 
		{
			int         i         = 0;
			SkillType_t SkillType = pResult->getInt(++i);

			if (tempSkillType != SkillType) 
			{
				SkillParentInfo* pSkillParentInfo = new SkillParentInfo (SkillType);
				pSkillParentInfo->addParents(pResult->getInt(++i));
				addSkillParentInfo(pSkillParentInfo);
				tempSkillType = SkillType;
			} 
			else 
			{
				m_SkillParentInfoList[ SkillType ]->addParents(pResult->getInt(++i));
			}
		}

		//for (uint i = 0; i < m_SkillCount; i++) 
		//{
		//	if (m_SkillParentInfoList[ i ] != NULL) 
		//		//cout<< m_SkillParentInfoList[ i ]->toString()<<endl;
		//}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

//--------------------------------------------------------------------
//
// SkillParentInfoManager:: save()
//
//--------------------------------------------------------------------
void SkillParentInfoManager::save()
	throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError (__PRETTY_FUNCTION__);
	
	__END_CATCH
}


//--------------------------------------------------------------------
//
// SkillParentInfoManager:: addSkillParentInfo()
//
//--------------------------------------------------------------------
void SkillParentInfoManager::addSkillParentInfo(SkillParentInfo* pSkillParentInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert (pSkillParentInfo != NULL);

	if (m_SkillParentInfoList[pSkillParentInfo->getSkillType()] != NULL)
		throw DuplicatedException ();

	m_SkillParentInfoList[pSkillParentInfo->getSkillType()] = pSkillParentInfo;
	
	__END_CATCH
}

//--------------------------------------------------------------------
//
// SkillParentInfoManager:: getSkillParentInfo()
//
//--------------------------------------------------------------------
SkillParentInfo* SkillParentInfoManager::getSkillParentInfo(SkillType_t SkillType)
	const throw(NoSuchElementException , OutOfBoundException, Error)
{
	__BEGIN_TRY

	if (SkillType >= m_SkillCount)
	{
		cerr << "SkillParentInfoManager::getSkillParentInfo() : out of bounds" << endl;
		throw OutOfBoundException ();
	}

	if (m_SkillParentInfoList[SkillType] == NULL)
	{
		cerr << "SkillParentInfoManager::getSkillParentInfo() : NoSuchElementException" << endl;
		throw NoSuchElementException ();
	}

	return m_SkillParentInfoList[SkillType];
	
	__END_CATCH
}

//--------------------------------------------------------------------
//
// SkillParentInfoManager:: toString()
//
//--------------------------------------------------------------------
string SkillParentInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SkillParentInfoManager(";

	for (uint i = 0 ; i < m_SkillCount ; i ++) 
	{
		if (m_SkillParentInfoList[i] != NULL)
		{
			msg << m_SkillParentInfoList[i]->toString();
		}
		else 
		{
			msg << "NULL" ;
		}
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
SkillParentInfoManager* g_pSkillParentInfoManager = NULL;
