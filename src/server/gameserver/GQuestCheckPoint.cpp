#include "GQuestCheckPoint.h"
#include "MonsterCorpse.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "ZoneInfo.h"
#include "Properties.h"
#include "ZoneInfoManager.h"
#include "SXml.h"

void GQuestCheckPoint::load() throw(Error)
{
	__BEGIN_TRY

	XMLTree* pTree = new XMLTree;
	pTree->LoadFromFile((g_pConfig->getProperty("HomePath") + "/data/EventCheckPoint.xml").c_str());

	DWORD type, zoneid, x, y, id;
	for ( size_t i=0 ; i<pTree->GetChildCount() ; ++i )
	{
		XMLTree* pChild = pTree->GetChild(i);
		Assert( pChild->GetAttribute("type", type) );
		Assert( pChild->GetAttribute("zoneid", zoneid) );
		Assert( pChild->GetAttribute("x", x) );
		Assert( pChild->GetAttribute("y", y) );
		Assert( pChild->GetAttribute("id", id) );

		MonsterCorpse* pMonsterCorpse = new MonsterCorpse( type, "暇竟", 2 );
		pMonsterCorpse->setTreasureCount(255);
		Zone* pZone = getZoneByZoneID( zoneid );
		Assert( pZone != NULL );
		pZone->registerObject( pMonsterCorpse );
		pZone->addItem( pMonsterCorpse, x, y, true, 0xffffffff );

		m_CheckPointMap[pMonsterCorpse] = id;
		Assert( m_IDMap[id] == NULL );
		m_IDMap[id] = pMonsterCorpse;

		StringStream name;
		name << g_pZoneInfoManager->getZoneInfo(pMonsterCorpse->getZone()->getZoneID())->getFullName() << "("
			<< (int)pMonsterCorpse->getX()
			<< "," << (int)pMonsterCorpse->getY()
			<< ")";
		m_NameMap[id] = name.toString();
	}

	SAFE_DELETE( pTree );

	pTree = new XMLTree;
	pTree->LoadFromFile((g_pConfig->getProperty("HomePath") + "/data/TravelWay.xml").c_str());
	for ( size_t i=0; i<pTree->GetChildCount() ; ++i )
	{
		XMLTree* pChild = pTree->GetChild(i);
		Assert( pChild->GetName() == "TravelWay" );
		DWORD race;
		string grade;
		Assert( pChild->GetAttribute( "race", race ) );
		Assert( pChild->GetAttribute( "grade", grade ) );
		DWORD nGrade = grade[0]-'A';
		Assert( nGrade <= 3 );
		vector<DWORD>& target = m_EventWayPoints[race][nGrade];
		for ( size_t j=0; j<pChild->GetChildCount(); ++j )
		{
			XMLTree* pWay = pChild->GetChild(j);
			Assert( pWay->GetName() == "Way" );
			DWORD id;
			Assert( pWay->GetAttribute( "id", id ) );
			target.push_back( id );
		}
	}

	__END_CATCH
}

DWORD	GQuestCheckPoint::getCheckPointID(MonsterCorpse* pCheckPoint)
{
	map<MonsterCorpse*, DWORD>::iterator itr = m_CheckPointMap.find( pCheckPoint );
	if ( itr == m_CheckPointMap.end() ) return 0;
	return itr->second;
}

string GQuestCheckPoint::getTargetList(Race_t race, Level_t level, DWORD grade, DWORD basenum, vector<DWORD>& outList)
{
	string ret;
	vector<DWORD>& waypoints = getWayPointVector(race, grade);
	int pointnum=basenum;
	if ( level<=50 ) pointnum += 0;
	else if ( level <= 90 ) pointnum += 1;
	else pointnum += 2;

	cout << (int)grade << "그레이드 " << (int)level << "레벨 " << pointnum << "개" << endl;

	if ( pointnum > waypoints.size() ) pointnum = waypoints.size();
	for ( int i=0; i<waypoints.size(); ++i )
	{
		int last = waypoints.size() - i;

		if ( (rand()%last)<pointnum )
		{
			pointnum--;
			outList.push_back(waypoints[i]);
			ret += getStringFromWayPoint(waypoints[i]);
			if ( pointnum <= 0 ) break;
			else ret += ", ";
		}
	}

	cout << "결과물 " << ret;
	return ret;
}

const string& GQuestCheckPoint::getStringFromWayPoint(DWORD id) const
{
	static const string empty = "";
	map<DWORD, string>::const_iterator itr = m_NameMap.find(id);
	if ( itr == m_NameMap.end() ) return empty;
	return itr->second;

}
