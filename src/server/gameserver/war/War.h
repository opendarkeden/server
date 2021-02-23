///////////////////////////////////////////////////////////////////
// 전쟁에 대한 전반적인 정보 및 전쟁 시작 및 종료시 처리루틴.
///////////////////////////////////////////////////////////////////

#ifndef __WAR_H__
#define __WAR_H__

#include "Types.h"
#include "Work.h"
#include "Exception.h"
#include "VSDateTime.h"

class Mutex;
class PlayerCreature;
class WarScheduleInfo;
class WarInfo;

class War : public Work
{
public:
	enum WarState {
		WAR_STATE_WAIT,				// 0
		WAR_STATE_CURRENT,			// 1
		WAR_STATE_END,				// 2
		WAR_STATE_CANCEL,			// 3

		MAX_WAR_STATE				// 4
	};

public:
	War( WarState warState, WarID_t warID=0 );
	virtual ~War();

	virtual WarType_t	getWarType() const = 0;
	virtual string 		getWarType2DBString() const = 0;
	virtual string		getWarName() const throw (Error) = 0;

	WarID_t			getWarID()	const				{ return m_WarID; }
	void			setWarID( WarID_t warID )		{ m_WarID = warID; }

	WarState		getState()	const				{ return m_State; }
	const string&	getState2DBString() const;
	void			setState( WarState warState )	{ m_State = warState; }

	const VSDateTime&	getWarStartTime() const		{ return m_StartTime; }
	void				setWarStartTime(VSDateTime dt) { m_StartTime = dt; }

public:
	virtual bool	isModifyCastleOwner( PlayerCreature* pPC ) throw (Error) { return false; }

	virtual void	sendWarStartMessage() const throw (ProtocolException, Error);
	virtual void	sendWarEndMessage() const throw (ProtocolException, Error);

public:
	static void		initWarIDRegistry() throw (Error);

public:
	virtual void 	execute() throw (Error);
	virtual bool    endWar(PlayerCreature* pPC) throw(Error) { return false; }

protected :
	virtual void 	executeStart() throw (Error) = 0;
	virtual void 	executeEnd() throw (Error) = 0;


public :
	virtual void	makeWarScheduleInfo( WarScheduleInfo* pWSI ) const throw (Error) = 0;
	virtual void 	makeWarInfo(WarInfo* pWarInfo) const throw (Error) = 0;

	virtual string	toString() const throw (Error) = 0;

private:
	WarID_t				m_WarID;
	WarState 			m_State;				// 전쟁의 현재 상태.
	VSDateTime			m_StartTime;			// 전쟁 시작 시간

	static Mutex		m_Mutex;
	static WarID_t		m_WarIDRegistry;
};

#endif // __WAR_H__
