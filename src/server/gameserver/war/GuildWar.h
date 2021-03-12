///////////////////////////////////////////////////////////////////
// 전쟁에 대한 전반적인 정보 및 전쟁 시작 및 종료시 처리루틴.
///////////////////////////////////////////////////////////////////

#ifndef __GUILD_WAR_H__
#define __GUILD_WAR_H__

#include "War.h"

class Mutex;
class PlayerCreature;

class GuildWar : public War
{
public:
	GuildWar( ZoneID_t castleZoneID, GuildID_t challenger, WarState warState, WarID_t warID=0 );
	virtual ~GuildWar();

	ZoneID_t		getCastleZoneID()	const				{ return m_CastleZoneID; }
	void			setCastleZoneID( ZoneID_t zoneID )		{ m_CastleZoneID = zoneID; }

	WarType_t		getWarType() const				{ return WAR_GUILD; }
	string 			getWarType2DBString() const		{ return "GUILD"; }
	string			getWarName() const ; 

	GuildID_t		getChallangerGuildID() const	{ return m_ChallangerGuildID; }

	Gold_t			getRegistrationFee() const		{ return m_RegistrationFee; }
	void			setRegistrationFee( Gold_t fee ){ m_RegistrationFee = fee; }

public:
	bool			isModifyCastleOwner( PlayerCreature* pPC ) ;
	GuildID_t		getWinnerGuildID( PlayerCreature* pPC ) ;

	//void			sendWarStartMessage() const ;
	void			sendWarEndMessage() const ;

	bool 			endWar(PlayerCreature* pPC) ;

protected :
	void 			executeStart() ;
	void 			executeEnd() ;

	void 			recordGuildWarStart() ;
	void 			recordGuildWarEnd() ;

public :
	void    makeWarScheduleInfo( WarScheduleInfo* pWSI ) const ;
	void    makeWarInfo( WarInfo* pWarInfo ) const ;
	virtual string	toString() const ;

private:
	ZoneID_t			m_CastleZoneID;			// 전쟁과 관련된 성의 ZoneID
	GuildID_t 			m_ChallangerGuildID;	// WAR_GUILD 일때 전쟁을 신청한 길드의 ID
	Gold_t				m_RegistrationFee;		// 지급된 전쟁 신청금

	// 전쟁 결과
	Race_t 				m_WinnerRace;
	GuildID_t 			m_WinnerGuildID;
	bool				m_bModifyCastleOwner;
};

#endif // __WAR_H__
