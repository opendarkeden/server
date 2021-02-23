/////////////////////////////////////////////////////////////////////////////
// BroadcastFilter.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __BROADCAST_FILTER_H__
#define __BROADCAST_FILTER_H__

// include files
#include "Types.h"
#include "Exception.h"

// forward declaration
class GamePlayer;

/////////////////////////////////////////////////////////////////////////////
// class BroadcastFilter
/////////////////////////////////////////////////////////////////////////////
class BroadcastFilter
{
public:
	BroadcastFilter() {}
	virtual ~BroadcastFilter() {}

public:
	virtual bool isSatisfy( GamePlayer* ) throw() = 0;
	virtual BroadcastFilter* Clone() throw() = 0;
};


/////////////////////////////////////////////////////////////////////////////
// class BroadcastFilterRace
/////////////////////////////////////////////////////////////////////////////
class BroadcastFilterRace : public BroadcastFilter
{
public:
	BroadcastFilterRace( Race_t race ) : m_Race(race) {}
	virtual ~BroadcastFilterRace() {}

public:
	virtual bool isSatisfy( GamePlayer* ) throw();
	virtual BroadcastFilter* Clone() throw();

private:
	Race_t m_Race;
};

#endif

