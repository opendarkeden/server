/////////////////////////////////////////////////////////////////////////////
// DynamicZone.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_H__
#define __DYNAMIC_ZONE_H__

#include "Types.h"
#include "Timeval.h"


enum DYNAMIC_ZONE_STATUS
{
	DYNAMIC_ZONE_STATUS_READY = 0,
	DYNAMIC_ZONE_STATUS_RUNNING,

	DYNAMIC_ZONE_STATUS_MAX
};

class Zone;

///////////////////////////////////////////////////////////
// class DynamicZone
///////////////////////////////////////////////////////////
class DynamicZone
{
public:
	DynamicZone();
	virtual ~DynamicZone();

public:
	virtual void init() {}		// 다이나믹 존 초기화
	virtual void heartbeat() {}	// 다이나믹 존 하트비트

public:
	// 새로 DynamicZone을 만들어서 ZoneGroup 에 추가한다.
	void makeDynamicZone();

	ZoneID_t getTemplateZoneID() const { return m_TemplateZoneID; }
	void setTemplateZoneID( ZoneID_t templateZoneID ) { m_TemplateZoneID = templateZoneID; }

	ZoneID_t getZoneID() const { return m_ZoneID; }
	void setZoneID( ZoneID_t zoneID ) { m_ZoneID = zoneID; }

	int getStatus() const { return m_Status; }
	void setStatus( int status ) { m_Status = status; }

protected:
	ZoneID_t m_TemplateZoneID;
	ZoneID_t m_ZoneID;
	int m_Status;
	Zone* m_pZone;
	Timeval m_Deadline;
};

///////////////////////////////////////////////////////////
// class DynamicZoneFactory
///////////////////////////////////////////////////////////
class DynamicZoneFactory
{
public:
	virtual ~DynamicZoneFactory() {}
	virtual int getDynamicZoneType() const = 0;
	virtual string getDynamicZoneName() const = 0;
	virtual DynamicZone* createDynamicZone() const = 0;
};

///////////////////////////////////////////////////////////
// DynamicZoneFactory macro
///////////////////////////////////////////////////////////
#define DECLARE_DYNAMIC_ZONE_FACTORY( DYNAMIC_ZONE ) 						\
	class DYNAMIC_ZONE##Factory	: public DynamicZoneFactory					\
	{																		\
	public:																	\
		int getDynamicZoneType() const;										\
		string getDynamicZoneName() const { return "##DYNAMIC_ZONE##"; }	\
		DynamicZone* createDynamicZone() const { return new DYNAMIC_ZONE; }	\
	};

#define DEFINE_DYNAMIC_ZONE_FACTORY( DYNAMIC_ZONE, DYNAMIC_ZONE_ID )					\
	int DYNAMIC_ZONE##Factory::getDynamicZoneType() const { return DYNAMIC_ZONE_ID; }

#endif

