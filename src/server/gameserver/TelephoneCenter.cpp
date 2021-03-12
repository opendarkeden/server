//--------------------------------------------------------------------------------
//
// Filename   : TelephoneCenter.cpp
// Written By : elca
//
//--------------------------------------------------------------------------------

// include files
#include "TelephoneCenter.h"

//--------------------------------------------------------------------------------
// add creature to unordered_map
// execute just once at PC's login
//--------------------------------------------------------------------------------
void TelephoneCenter::addSlayer (Slayer* pSlayer) 
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Assert(pSlayer != NULL);

	unordered_map< PhoneNumber_t , const Slayer* >::iterator itr = m_PCs.find(pSlayer ->getPhoneNumber());

	if (itr != m_PCs.end())
	{
		throw DuplicatedException();
	}

	m_PCs[ pSlayer->getPhoneNumber() ] = pSlayer;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// Delete creature from unordered_map
// execute just once at PC's logout
//--------------------------------------------------------------------------------
void TelephoneCenter::deleteSlayer (PhoneNumber_t PhoneNumber) 
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	unordered_map< PhoneNumber_t , const Slayer* >::iterator itr = m_PCs.find(PhoneNumber);

	if (itr == m_PCs.end())
	{
		throw NoSuchElementException();
	}

	m_PCs.erase(itr);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get creature with PC-name
//--------------------------------------------------------------------------------
Slayer* TelephoneCenter::getSlayer(PhoneNumber_t PhoneNumber) const 
{
	__BEGIN_TRY

	unordered_map< PhoneNumber_t , const Slayer* >::const_iterator itr = m_PCs.find(PhoneNumber);

	if (itr == m_PCs.end())
	{
		return NULL;
//		throw NoSuchElementException();
	}

	return (Slayer*)itr->second;

	__END_CATCH
}

// global variable definition
TelephoneCenter* g_pTelephoneCenter = NULL;
