/////////////////////////////////////////////////////////////////////
// 깃발뺏기에 대한 전반적인 정보 및 깃발뺏기 시작 및 종료시 처리루틴.
/////////////////////////////////////////////////////////////////////

#ifndef __FLAG_WAR_H__
#define __FLAG_WAR_H__

#include "war/Work.h"
#include "VSDateTime.h"
#include <vector>
#include <list>

class FlagWar : public Work
{
	struct FlagGenZone
	{
		vector<ZoneID_t>	ZoneIDs;
		uint				FlagCount;
	};
public:
	FlagWar() { m_State = STATE_WAIT; }
	virtual void	execute() ;

	virtual VSDateTime	getNextFlagWarTime();
	virtual int			getWarTime() const;

protected:
	virtual void	executeReady() ;
	virtual void	executeStart() ;
	virtual void	executeFinish() ;
	virtual void	executeEnd() ;

	virtual void		addFlags();

	void addFlagsRandom( ZoneID_t zoneID, uint no );

	string toString() const  { return "FlagWar"; }

private:
	enum State
	{
		STATE_WAIT,
		STATE_READY,
		STATE_START,
		STATE_FINISH,
		STATE_END
	};

	State m_State;

	State getState() const { return m_State; }
	void  setState(State state) { m_State = state; }

	vector<ItemID_t> m_Flags;
	static list<FlagGenZone> m_FlagGenInfo;
};

#endif// __FLAG_WAR_H__
