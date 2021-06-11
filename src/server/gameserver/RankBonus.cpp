//////////////////////////////////////////////////////////////////////////////
// Filename    : RankBonus.cpp
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////


#include "RankBonus.h"
#include "Exception.h"


RankBonus::RankBonus()
	
{
	__BEGIN_TRY

	__END_CATCH
}

RankBonus::RankBonus( DWORD type, DWORD point, Rank_t rank )
	
{
	__BEGIN_TRY

	m_Type = type;
	m_Point = point;
	m_Rank = rank;

	__END_CATCH
}

RankBonus::~RankBonus()
	
{
	__BEGIN_TRY

	__END_CATCH
}

