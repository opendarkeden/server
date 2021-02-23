#ifndef __EVENT_ZONE_INFO_H__
#define __EVENT_ZONE_INFO_H__

#include "Types.h"
#include "Exception.h"

#include <vector>
#include <hash_map>

class Zone;
class EventZoneInfoManager;

class EventZoneInfo
{
public:
	EventZoneInfo( WORD eventID, ZoneID_t zoneID );

	ZoneID_t	getZoneID() const;
	WORD		getEventID() const { return m_EventID; }
	bool		canEnter() const;
	bool		isEventOn() const { return m_bEventOn; }
	void		turnOn() { m_bEventOn = true; }
	void		turnOff() { m_bEventOn = false; }
	void		setPCLimit( WORD lim ) { m_PCLimit = lim; }

	ZoneCoord_t	getEnterX() const { return m_EnterX; }
	ZoneCoord_t	getEnterY() const { return m_EnterY; }

	ZoneCoord_t	getResurrectX() const { return m_ResurrectX; }
	ZoneCoord_t	getResurrectY() const { return m_ResurrectY; }

	friend class EventZoneInfoManager;

private:
	WORD		m_EventID;
	Zone*		m_pZone;
	WORD		m_PCLimit;
	bool		m_bEventOn;

	ZoneCoord_t	m_EnterX;
	ZoneCoord_t	m_EnterY;
	ZoneCoord_t	m_ResurrectX;
	ZoneCoord_t m_ResurrectY;
};

class ZoneEventInfo
{
public:
	ZoneEventInfo( WORD eventID ) : m_EventID(eventID) { }

	WORD			getEventID() const { return m_EventID; }

	EventZoneInfo*	getEventZoneInfo( ZoneID_t zoneID ) const;
	void			addEventZoneInfo( EventZoneInfo* pEventZoneInfo );

	EventZoneInfo*	getCurrentEventZoneInfo() const;

private:
	WORD								m_EventID;
	hash_map<ZoneID_t, EventZoneInfo*>	m_EventZoneInfos;
};

class EventZoneInfoManager
{
public:
	void	load() throw(Error);
	
	ZoneEventInfo*	getZoneEventInfo( WORD eventID ) const;
	EventZoneInfo*	getEventZoneInfo( ZoneID_t zoneID ) const;

	static EventZoneInfoManager& Instance() { static EventZoneInfoManager theInstance; return theInstance; }

private:
	hash_map<WORD, ZoneEventInfo*>		m_ZoneEventInfos;
	hash_map<ZoneID_t, EventZoneInfo*>	m_EventZoneInfos;
};

#endif
