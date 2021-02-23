#ifndef __PK_ZONE_INFO_MANAGER_H__
#define __PK_ZONE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Mutex.h"

#include "Cpackets/CGSay.h"

class PKZoneInfo
{
public:
	PKZoneInfo( ZoneID_t zoneID, ZoneCoord_t enterX, ZoneCoord_t enterY, ZoneCoord_t resX, ZoneCoord_t resY, Race_t race, int pcLimit )
	{
		m_ZoneID=zoneID;
		m_EnterPosition.x=enterX;
		m_EnterPosition.y=enterY;
		m_ResurrectPosition.x=resX;
		m_ResurrectPosition.y=resY;
		m_bFree=race>1;
		m_Race=race;
		m_PCLimit=pcLimit;
		m_CurrentPCNum=0;
	}
	~PKZoneInfo() { }

	ZoneID_t	getZoneID() const { return m_ZoneID; }
	bool		isFree() const { return m_bFree; }
	Race_t		getRace() const { return m_Race; }
	ZoneCoord_t	getEnterX() const { return m_EnterPosition.x; }
	ZoneCoord_t getEnterY() const { return m_EnterPosition.y; }
	ZoneCoord_t	getResurrectX() const { return m_ResurrectPosition.x; }
	ZoneCoord_t getResurrectY() const { return m_ResurrectPosition.y; }
	int			getPCLimit() const { return m_PCLimit; }
	int			getCurrentPCNum() const { return m_CurrentPCNum; }

	bool		canEnter() const { return m_CurrentPCNum < m_PCLimit; }
	bool		enterZone() { if ( canEnter() ) m_CurrentPCNum++; else return false; return true; }
	bool		leaveZone() { if ( m_CurrentPCNum > 0 ) m_CurrentPCNum--; else return false; return true; }

	void		lock() throw(Error) { m_Mutex.lock(); }
	void		unlock() throw(Error) { m_Mutex.unlock(); }

	string		toString() throw(Error);

protected:
	void		setCurrentPCNum( int num ) { if ( num <= m_PCLimit && num >= 0 ) m_CurrentPCNum = num; }
	friend		void CGSayHandler::opcommand(GamePlayer*, string, int);

private:
	ZoneID_t	m_ZoneID;
	bool		m_bFree;
	Race_t		m_Race;
	TPOINT		m_EnterPosition;
	TPOINT		m_ResurrectPosition;
	int			m_PCLimit;
	int			m_CurrentPCNum;

	mutable Mutex		m_Mutex;
};

class PKZoneInfoManager
{
public:
	typedef hash_map<ZoneID_t,PKZoneInfo*> PKZoneInfoMap;
public:
	PKZoneInfoManager() { }
	~PKZoneInfoManager() { }

	void		load() throw(Error);

	void		addPKZoneInfo( PKZoneInfo* pPKZoneInfo ) throw(Error);
	PKZoneInfo*	getPKZoneInfo( ZoneID_t	zoneID ) const throw(Error);
	bool		isPKZone( ZoneID_t zoneID ) const throw(Error);

	bool		canEnterPKZone( ZoneID_t zoneID ) throw(Error);
	bool		enterPKZone( ZoneID_t zoneID ) throw(Error);
	bool		leavePKZone( ZoneID_t zoneID ) throw(Error);

	bool		getResurrectPosition( ZoneID_t zoneID, ZONE_COORD& zoneCoord ) const throw(Error);

private:
	PKZoneInfoMap m_PKZoneInfos;
};

extern PKZoneInfoManager* g_pPKZoneInfoManager;

#endif// __PK_ZONE_INFO_MANAGER_H__
