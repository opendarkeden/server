#ifndef __RANK_EXP_TABLE_H__
#define __RANK_EXP_TABLE_H__

#include "Types.h"
#include "Exception.h"
#include "SomethingGrowingUp.h"

#include <cstdio>

enum RankType
{
	RANK_TYPE_SLAYER,
	RANK_TYPE_VAMPIRE,
	RANK_TYPE_OUSTERS,

	RANK_TYPE_MAX
};

class RankExpTable : public ExpTable<RankExp_t, Rank_t, 1, 50>
{
public:
	RankExpTable( RankType type )
	{
		static const char* QueryTemplate = "where RankType=%1d";
		snprintf( m_QueryCondition, 19, QueryTemplate, type );
		m_QueryCondition[19] = '\0';
	}

	const string getDBTableName() const { return "RankEXPInfo"; }
	const string getDBQueryCondition() const { return m_QueryCondition; }

private:
	char m_QueryCondition[20];

public:
	static RankExpTable s_RankExpTables[RANK_TYPE_MAX];
};

typedef SomethingGrowingUp<RankExpTable> Rank;

#endif
