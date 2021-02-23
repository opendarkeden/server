//////////////////////////////////////////////////////////////////////////////
// Filename    : SweeperBonus.cpp
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "SweeperBonus.h"

void SweeperBonus::setRace( Race_t race )
{
	__BEGIN_TRY

	if ( m_Race != race) 
	{
		m_Race = race;
		Statement* pStmt    = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery( "UPDATE SweeperBonusInfo SET OwnerRace = %d WHERE Type = %d", m_Race, m_Type);

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
	}

	__END_CATCH
}

string SweeperBonus::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SweeperBonus(\n";

	OptionTypeListConstItor itr = m_OptionTypeList.begin();
	for ( ; itr != m_OptionTypeList.end() ; itr++) 
	{
		msg << (int)(*itr) << ",";
	}

	msg << ")\n";

	return msg.toString();

	__END_CATCH
}

