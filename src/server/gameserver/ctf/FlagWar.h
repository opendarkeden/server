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
	virtual void	execute() throw(Error);

	virtual VSDateTime	getNextFlagWarTime();
	virtual int			getWarTime() const;

protected:
	virtual void	executeReady() throw(Error);
	virtual void	executeStart() throw(Error);
	virtual void	executeFinish() throw(Error);
	virtual void	executeEnd() throw(Error);

	virtual void		addFlags();

	void addFlagsRandom( ZoneID_t zoneID, uint no );

	string toString() const throw(Error) { return "FlagWar"; }

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
