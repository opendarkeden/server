///////////////////////////////////////////////////////////////////
// 전쟁에 대한 전반적인 정보 및 전쟁 시작 및 종료시 처리루틴.
///////////////////////////////////////////////////////////////////

#ifndef __RACE_WAR_H__
#define __RACE_WAR_H__

#include "War.h"

class Mutex;
class PlayerCreature;

class RaceWar : public War
{
public:
	RaceWar( WarState warState, WarID_t warID=0 );
	virtual ~RaceWar();

	WarType_t		getWarType() const				{ return WAR_RACE; }
	string 			getWarType2DBString() const		{ return "RACE"; }
	string			getWarName() const throw (Error); 

public:
	//void			sendWarStartMessage() const throw (ProtocolException, Error);
	void			sendWarEndMessage() const throw (ProtocolException, Error);

protected :
	void 			executeStart() throw (Error);
	void 			executeEnd() throw (Error);

	void 			recordRaceWarStart() throw (Error);
	void 			recordRaceWarEnd() throw (Error);

public :
	void    makeWarScheduleInfo( WarScheduleInfo* pWSI ) const throw (Error);
	void 	makeWarInfo(WarInfo* pWarInfo) const throw (Error);

	virtual string	toString() const throw (Error);

private:
};

#endif // __WAR_H__
