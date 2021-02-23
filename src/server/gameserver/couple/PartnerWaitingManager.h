#ifndef __PARTNER_WAITING_MANAGER_H__
#define __PARTNER_WAITING_MANAGER_H__

#include <hash_map>
#include "Exception.h"
#include "Types.h"
#include "Timeval.h"
#include "PlayerCreature.h"

class Zone;

enum WaitType
{
	WAIT_FOR_MEET,		// 0
	WAIT_FOR_APART		// 1
};

class PartnerWaitInfo
{
protected:
	PartnerWaitInfo( PlayerCreature* pWaitingPC, string RequestedPCName );
public:
	virtual ~PartnerWaitInfo() { }

	// Factory Method
	static PartnerWaitInfo*	getPartnerWaitInfo(PlayerCreature* pWaitingPC, string RequestedPCName, WaitType waitType) throw(Error);

public:
	virtual uint			waitPartner( PlayerCreature* pTargetPC ) throw(Error) = 0;
	virtual uint			acceptPartner( PlayerCreature* pPC ) throw(Error) = 0;
	virtual void			timeExpired() throw(Error) = 0;
	virtual WaitType		getWaitType() = 0;

public:
	PlayerCreature*	getWaitingPC() const;
	Timeval			getDeadline() const { return m_Deadline; }

public:
	static Item::ItemClass getItemClass( PlayerCreature* pPC )
	{
		return ( pPC->getRace() == RACE_SLAYER )? Item::ITEM_CLASS_COUPLE_RING : Item::ITEM_CLASS_VAMPIRE_COUPLE_RING;
	}
	static ItemType_t getItemType( PlayerCreature* pPC ) { return ( pPC->getSex() == FEMALE )? 1 : 0; }
	static bool	isMatchCoupleRing( PlayerCreature* pPC, Item* pRing )
	{
		return pRing->getItemClass() == getItemClass( pPC ) &&	pRing->getItemType() == getItemType( pPC );
	}

private:
	string			m_RequestedPCName;
	ObjectID_t		m_WaitingPCOID;
	Zone*			m_pZone;
	Timeval			m_Deadline;
};

class PartnerWaitingManager
{
public:
	typedef hash_map<string, PartnerWaitInfo*>	WaitInfoHashMap;
public:
	PartnerWaitingManager( WaitType waitType ) : m_WaitType( waitType ) { };
	virtual ~PartnerWaitingManager();

public:
	WaitType	getWaitType() const { return m_WaitType; }

public:
	uint		waitForPartner( PlayerCreature* pWaitingPC, string RequestedPCName ) throw(Error);
	bool		stopWaitForPartner( PlayerCreature* pWaitingPC ) throw(Error);
	uint		acceptPartner( PlayerCreature* pRequestedPC ) throw(Error);
	bool		isWaitForPartner( PlayerCreature* pRequestedPC ) throw(Error);
	PlayerCreature* getWaitingPartner( PlayerCreature* pRequestedPC ) throw(Error);

public:
	void		heartbeat() throw(Error);

private:
	WaitInfoHashMap	m_WaitInfos;
	WaitType		m_WaitType;
};

#endif// __PARTNER_WAITING_MANAGER_H__

