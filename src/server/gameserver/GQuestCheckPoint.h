#ifndef __GQUEST_CHECK_POINT_H__
#define __GQUEST_CHECK_POINT_H__

#include "Types.h"
#include "Exception.h"
#include "Assert.h"

#include <map>
#include <vector>
class MonsterCorpse;

class GQuestCheckPoint
{
public:
	void load() throw(Error);
	static GQuestCheckPoint& Instance()
	{
		static GQuestCheckPoint theInstance;
		return theInstance;
	}

	DWORD	getCheckPointID(MonsterCorpse* pCheckPoint);
	vector<DWORD>&	getWayPointVector(Race_t race, DWORD grade)
	{
		Assert( grade <= 4 && grade >= 1 );
		Assert( race<3 );

		return m_EventWayPoints[race][grade-1];
	}

	string	getTargetList(Race_t race, Level_t level, DWORD grade, DWORD basenum, vector<DWORD>& outList);
	const string&	getStringFromWayPoint(DWORD id) const;

private:
	map<MonsterCorpse*, DWORD>	m_CheckPointMap;
	map<DWORD, MonsterCorpse*>	m_IDMap;
	map<DWORD, string>			m_NameMap;

	vector<DWORD>	m_EventWayPoints[3][4];
};

#endif
