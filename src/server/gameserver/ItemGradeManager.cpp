#include "ItemGradeManager.h"
#include "DB.h"
#include "Assert.h"

void ItemGradeManager::load() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT Grade, Ratio, GambleRatio, BeadRatio FROM ItemGradeRatioInfo" );

		Assert( pResult->getRowCount() == 10 );
		m_GradeGambleRatios.reserve(10);
		m_GradeBeadRatios.reserve(10);
		m_GradeRatios.reserve(10);

		while ( pResult->next() )
		{
			int Grade = pResult->getInt(1);
			int Ratio = pResult->getInt(2);
			int GambleRatio = pResult->getInt(3);
			int BeadRatio = pResult->getInt(4);

			m_GradeRatios[Grade-1] = Ratio;
			m_GradeGambleRatios[Grade-1] = GambleRatio;
			m_GradeBeadRatios[Grade-1] = BeadRatio;
			cout << Grade << "Бо : " << Ratio << ", " << GambleRatio << ", " << BeadRatio << endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

Grade_t ItemGradeManager::getRandomGrade() const
{
	int value = rand()%100000;
	int i=0;

	for ( ; i<10; ++i )
	{
		value -= m_GradeRatios[i];
		if ( value < 0 ) return i+1;
	}

	return i;
}

Grade_t ItemGradeManager::getRandomGambleGrade() const
{
	int value = rand()%100000;
	int i=0;

	for ( ; i<10; ++i )
	{
		value -= m_GradeGambleRatios[i];
		if ( value < 0 ) return i+1;
	}

	return i;
}

Grade_t ItemGradeManager::getRandomBeadGrade() const
{
	int value = rand()%100000;
	int i=0;

	for ( ; i<10; ++i )
	{
		value -= m_GradeBeadRatios[i];
		if ( value < 0 ) return i+1;
	}

	return i;
}

ItemGradeManager& ItemGradeManager::Instance()
{
	static ItemGradeManager theInstance;
	return theInstance;
}
