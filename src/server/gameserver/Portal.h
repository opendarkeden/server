//////////////////////////////////////////////////////////////////////////////
// Filename    : Portal.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "Object.h"
#include "quest/TriggerManager.h"

//////////////////////////////////////////////////////////////////////////////
// Portal Type
//////////////////////////////////////////////////////////////////////////////

typedef BYTE PortalType_t;
const uint szPortalType = sizeof(PortalType_t);

enum PortalType 
{
	PORTAL_NORMAL,				// 0
	PORTAL_SLAYER,				// 1
	PORTAL_VAMPIRE,				// 2
	PORTAL_MULTI_TARGET,		// 3
	PORTAL_PRIVATE,				// 4
	PORTAL_GUILD,				// 5
	PORTAL_BATTLE,				// 6
	PORTAL_OUSTERS				// 7
};

enum PortalClass 
{
	PORTAL_CLASS_NORMAL,		// 0
	PORTAL_CLASS_PRIVATE,		// 1
	PORTAL_CLASS_MULTI,			// 2
	PORTAL_CLASS_TRIGGERED      // 3
};

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;


//////////////////////////////////////////////////////////////////////////////
// class PortalTargetInfo
//////////////////////////////////////////////////////////////////////////////

class PortalTargetInfo 
{
public:
	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID) throw() { m_ZoneID = zoneID; }

	ZoneCoord_t getX() const throw() { return m_X; }
	void setX(ZoneCoord_t x) throw() { m_X = x; }

	ZoneCoord_t getY() const throw() { return m_Y; }
	void setY(ZoneCoord_t y) throw() { m_Y = y; }

private:
	ZoneID_t    m_ZoneID; // target zone id
	ZoneCoord_t m_X;      // target x coord.
	ZoneCoord_t m_Y;      // target y coord.

};


//////////////////////////////////////////////////////////////////////////////
// class Portal;
//////////////////////////////////////////////////////////////////////////////

class Portal : public Object 
{
public:
	Portal(ObjectID_t objectID = 0) throw() : Object(objectID) {}
	virtual ~Portal() throw() {}

public:
	virtual ObjectClass getObjectClass() const throw() { return OBJECT_CLASS_PORTAL; }
	virtual ObjectPriority getObjectPriority() const throw(Error) { return OBJECT_PRIORITY_PORTAL; }
	virtual PortalClass getPortalClass() const throw() = 0;
	virtual bool activate(Creature* pCreature) throw(Error) { return false; };
	virtual bool activate(Creature* pCreature, ZoneID_t ZoneID) throw(Error) { return false; };
	virtual string toString() const throw() = 0;

public:
	PortalType_t getObjectType() const throw() { return m_PortalType; }
	void setObjectType(PortalType_t portalType) throw() { m_PortalType = portalType; }

protected:
	PortalType_t m_PortalType;
};

//////////////////////////////////////////////////////////////////////////////
// class PrivatePortal
//////////////////////////////////////////////////////////////////////////////

class PrivatePortal : public Portal 
{
public:
	PrivatePortal(ObjectID_t objectID = 0) throw();
	~PrivatePortal() throw();

public:
	PortalClass getPortalClass() const throw() { return PORTAL_CLASS_PRIVATE; }

	ZoneID_t getZoneID() const throw();
	void setZoneID(ZoneID_t zoneID) throw();

	ZoneCoord_t getX() const throw();
	void setX(ZoneCoord_t x) throw();

	ZoneCoord_t getY() const throw();
	void setY(ZoneCoord_t y) throw();

	bool activate(Creature* pCreature) throw(Error);
	virtual string toString() const throw();

public:
	string getName() const throw() { return m_Name; }
	void setName(const string Name) throw() { m_Name = Name; }

	bool isReturning() throw() { return m_Return; }

private:
	string m_Name;
	bool m_Return;
	PortalTargetInfo* m_pTarget;
};


//////////////////////////////////////////////////////////////////////////////
// class NormalPortal
//////////////////////////////////////////////////////////////////////////////

class NormalPortal : public Portal 
{
public:
	NormalPortal(ObjectID_t objectID = 0) throw() : Portal(objectID) {
		m_pTarget = new PortalTargetInfo();
	}

	~NormalPortal() throw() {
		if(m_pTarget != NULL) delete m_pTarget;
	}

	// get Portal class
	PortalClass getPortalClass() const throw() { return PORTAL_CLASS_NORMAL; }

	// get/set zone id
	ZoneID_t getZoneID() const throw() { return m_pTarget->getZoneID(); }
	void setZoneID(ZoneID_t zoneID) throw() { m_pTarget->setZoneID(zoneID); }

	ZoneCoord_t getX() const throw() { return m_pTarget->getX(); }
	void setX(ZoneCoord_t x) throw() { m_pTarget->setX(x); }

	ZoneCoord_t getY() const throw() { return m_pTarget->getY(); }
	void setY(ZoneCoord_t y) throw() { m_pTarget->setY(y); }

	// PC를 특정 위치로 이동시킨다.
	bool activate(Creature* pCreature) throw(Error);

	// get debug string
	virtual string toString() const throw();

private:

	PortalTargetInfo* m_pTarget;

};


//////////////////////////////////////////////////////////////////////////////
// class GuildPortal
//////////////////////////////////////////////////////////////////////////////

class GuildPortal : public Portal 
{
public:
	GuildPortal(ObjectID_t objectID = 0) throw() : Portal(objectID) {
		m_pTarget = new PortalTargetInfo();
	}

	~GuildPortal() throw() {
		if(m_pTarget != NULL) delete m_pTarget;
	}

	// get Portal class
	PortalClass getPortalClass() const throw() { return PORTAL_CLASS_NORMAL; }

	// get/set zone id
	ZoneID_t getZoneID() const throw() { return m_pTarget->getZoneID(); }
	void setZoneID(ZoneID_t zoneID) throw() { m_pTarget->setZoneID(zoneID); }

	ZoneCoord_t getX() const throw() { return m_pTarget->getX(); }
	void setX(ZoneCoord_t x) throw() { m_pTarget->setX(x); }

	ZoneCoord_t getY() const throw() { return m_pTarget->getY(); }
	void setY(ZoneCoord_t y) throw() { m_pTarget->setY(y); }

	// PC를 특정 위치로 이동시킨다.
	bool activate(Creature* pCreature) throw(Error);

	// get debug string
	virtual string toString() const throw();

private:

	PortalTargetInfo* m_pTarget;

};


//////////////////////////////////////////////////////////////////////////////
// class MultiPortal
//////////////////////////////////////////////////////////////////////////////

class MultiPortal : public Portal 
{
public:
	MultiPortal(ObjectID_t objectID= 0) throw() : Portal(objectID) {}
	~MultiPortal() throw() { 
		while(!m_Targets.empty()) {
			PortalTargetInfo* pPortalTargetInfo = m_Targets.front();
			m_Targets.pop_front();
			delete pPortalTargetInfo;
		}
	}

	// get Portal class
	PortalClass getPortalClass() const throw() { return PORTAL_CLASS_MULTI; }

	void setPortalTargetInfo(PortalTargetInfo* pPortalTargetInfo) throw() { m_Targets.push_back(pPortalTargetInfo); }
	void getPortalTargetInfo(ZoneID_t ZoneID) throw();

	// PC를 특정 위치로 이동시킨다.
	bool activate(Creature* pCreature, ZoneID_t ZoneID) throw(Error);

	// get debug string
	virtual string toString() const throw();

private:
	//  목표 좌표 Info
	list<PortalTargetInfo*> m_Targets;

};


//////////////////////////////////////////////////////////////////////////////
// class TriggeredPortal
//////////////////////////////////////////////////////////////////////////////

class TriggeredPortal : public Portal
{

///// member methods /////

public: // constructor & destructor
	TriggeredPortal(ObjectID_t id=0) throw() : Portal(id) {}
	~TriggeredPortal() throw() {}

public: // methods from base class
	PortalClass getPortalClass() const throw() { return PORTAL_CLASS_TRIGGERED; }
	bool activate(Creature* pCreature) throw(Error);
	virtual string toString() const throw();

public: // public methods
	void load(ZoneID_t id, int left, int top, int right, int bottom) throw();

	TriggerManager& getTriggerManager() throw() { return m_TriggerManager; }
	const TriggerManager& getTriggerManager() const throw() { return m_TriggerManager; }


///// member data /////

private:
	TriggerManager m_TriggerManager;

};

#endif
