//////////////////////////////////////////////////////////////////////////////
// Filename   : PaySystem.h
// Written by : sigi
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PAY_SYSTEM_H__
#define __PAY_SYSTEM_H__

#include "Types.h"
#include "Timeval.h"
#include "VSDateTime.h"
#include "Exception.h"

class Statement;



//////////////////////////////////////////////////////////////////////////////
// 요금제
//////////////////////////////////////////////////////////////////////////////
enum PayPlayType
{
	PAY_PLAY_TYPE_PERSON,   // 개인 요금
	PAY_PLAY_TYPE_PCROOM,   // 게임방 요금
	PAY_PLAY_TYPE_ETC,      // 기타(뭐지.. 그냥 넣어둠 -_-;)
	PAY_PLAY_TYPE_MAX
};

enum PayType
{
	PAY_TYPE_FREE,      // 무료 사용자
	PAY_TYPE_PERIOD,    // 월 사용자
	PAY_TYPE_TIME,      // 시간제 사용자
	PAY_TYPE_POST,		// 후불 시간제 사용자
    PAY_TYPE_MAX
};

enum PayIPType
{
    PAY_IP_TYPE_ALL,        // IP전체
    PAY_IP_TYPE_LIMIT,      // 동시접속 사용대수 제한
    PAY_IP_TYPE_ASSIGN,     // 특정IP
    PAY_IP_TYPE_MAX
};

enum FamilyPayPartyType
{
	FAMILY_PAY_PARTY_TYPE_NONE,
	FAMILY_PAY_PARTY_TYPE_FREE_PASS,		// 패밀리 요금제 파티 유료존 출입가능
	FAMILY_PAY_PARTY_TYPE_FREE_PASS_END,	// 패밀리 요금제 파티 유료존 출입가능 끝
};

#define PAY_PLAY_FLAG_ALL			0xFFFF
#define PAY_PLAY_FLAG_ZONE			0x0001


#define __PAY_SYSTEM_ZONE__			// Zone 출입여부에 PaySystem을 적용
//#define __PAY_SYSTEM_LOGIN__		// Login여부에 PaySystem을 적용
//#define __PAY_SYSTEM_FREE_LIMIT__		// 게임 불가 사용자인 경우, 자체 무료 서비스로..


//////////////////////////////////////////////////////////////////////////////
// class PaySystem
//////////////////////////////////////////////////////////////////////////////

class PaySystem
{

public:
	PaySystem();
	~PaySystem();

	PayPlayType   	getPayPlayType() const			{ return m_PayPlayType; }
	void   			setPayPlayType(PayPlayType ppt)	{ m_PayPlayType = ppt; }

	uint   			getPCRoomID() const			{ return m_PCRoomID; }
	void   			setPCRoomID(uint id)	{ m_PCRoomID = id; }

	PayType     	getPayType() const				{ return m_PayType; }
	void     		setPayType(PayType pt) 			{ m_PayType = pt; }

	PayIPType   	getPayIPType() const			{ return m_PayIPType; }
	void   			setPayIPType(PayIPType pipt) 	{ m_PayIPType = pipt; }

	uint		   	getPayPlayFlag() const			{ return m_PayPlayFlag; }
	void   			setPayPlayFlag(uint ppf)		{ m_PayPlayFlag = ppf; }
	bool			hasPayPlayFlag(uint flag) const	{ return m_PayPlayFlag & flag; }

	void			setPayPlayAvailableDateTime(const string& pat) throw (Error);
	const VSDateTime& getPayPlayAvailableDateTime() const	{ return m_PayPlayAvailableDateTime; }	// 언제까지 play가능한가?

	void			setFamilyPayPlayAvailableDateTime(const string& pat) throw (Error);
	const VSDateTime& getFamilyPayPlayAvailableDateTime() const	{ return m_FamilyPayPlayAvailableDateTime; }	// 언제까지 play가능한가?

	void			setPayStartAvailableDateTime(const string& pat) throw (Error);
	const VSDateTime& getPayStartAvailableDateTime() const	{ return m_PayStartAvailableDateTime; }	// 언제부터 play가능한가?

	Timeval			getPayPlayTime(const Timeval& currentTime) const	{ return timediff(m_PayPlayStartTime, currentTime); }
	void			setPayPlayStartTime(const Timeval& tv)	{ m_PayPlayStartTime = tv; }

	void			setPayPlayAvailableHours(int h) { m_PayPlayAvailableHours = h; }
	int 			getPayPlayAvailableHours() const 		{ return m_PayPlayAvailableHours; }



public :
	// 사용 가능한지 체크
	bool			checkPayPlayAvailable();

	// 일단 값만 설정
	void 			setPayPlayValue(PayType payType,
									const string& payPlayDate, int payPlayHours, uint payPlayFlag, const string& familyPayPlayDate = "");
	
	// pay시작
	bool 			loginPayPlay(PayType payType,
								const string& payPlayDate, int payPlayHours, uint payPlayFlag,
								const string& ip, const string& playerID)
											throw (Error);

	// pay시작
	bool 			loginPayPlay(const string& ip, const string& playerID)
											throw (Error);
	
	// pay 시간 update 등..
	bool			updatePayPlayTime(const string& playerID,
										const VSDateTime& currentDateTime, 
										const Timeval& currentTime) throw (ProtocolException, Error);

	// pay끝
	void			logoutPayPlay(const string& playerID, bool bClear=false, bool bDecreaseTime=true) throw (Error);

	//
	bool			isPayPlaying() const	{ return m_PayPlayStartTime.tv_sec!=0; }

	void			setPremiumPlay(bool bPremium=true) 		{ m_bPremiumPlay = bPremium; }
	bool			isPremiumPlay() const	{ return m_bPremiumPlay; }

	void			setFamilyPayAvailable(bool bFamilyPayAvailable=true)	{ m_bFamilyPayAvailable = bFamilyPayAvailable; }
	bool			isFamilyPayAvailable() const	{ return m_bFamilyPayAvailable; }

	void			setFamilyPayPartyType(FamilyPayPartyType familyPayPartyType)	{ m_FamilyPayPartyType = familyPayPartyType; }
	bool			isFamilyFreePass() const	{ return m_FamilyPayPartyType == FAMILY_PAY_PARTY_TYPE_FREE_PASS; }
	bool			isFamilyFreePassEnd() const	{ return m_FamilyPayPartyType == FAMILY_PAY_PARTY_TYPE_FREE_PASS_END; }

	void			setPCRoomPlay(bool bPCRoom = true) 		{ m_bPCRoomPlay = bPCRoom; }
	bool			isPCRoomPlay() const	{ return m_bPCRoomPlay; }

	// 개인 유료 정액 사용자인가?
	static bool		isPayPlayingPeriodPersonal(const string& PlayerID) throw (Error);

	bool			isPlayInPayPCRoom( const string& ip, const string& playerID ) throw (Error);

protected :
	// PC방인 경우의 처리
	bool		loginPayPlayPCRoom(const string& ip, const string& playerID) throw (Error);
	void		logoutPayPlayPCRoom(const string& playerID) throw (Error);

	// 정량제인 경우 시간 줄일때..
	void		decreasePayPlayTime(const string& playerID, uint mm) throw (Error);
	void		decreasePayPlayTimePCRoom(uint mm) throw (Error);

	// 이상한 정액제 코드
	void		increasePayPlayTimePCRoom(uint mm) throw (Error);

	// 모든 Pay정보를 삭제하고, 무료 사용자로 만든다. by sigi. 2002.11.18
	void		clearPayPlayDateTime(const string& playerID) throw (Error);

protected:
	bool			m_bSetPersonValue;			// 값이 설정되었나.

	PayPlayType   	m_PayPlayType;        		// 개인/겜방..
	ObjectID_t		m_PCRoomID;					// PC방 ID
	uint			m_UserLimit;				// 사용자 숫자 제한(종량제)
	uint			m_UserMax;					// 사용자 숫자 최대제한(정량제)
	
	PayType     	m_PayType;          		// 무료/시간/기간/기타..
	PayIPType   	m_PayIPType;        		// 게임방인 경우의 IP type

	VSDateTime	    m_PayStartAvailableDateTime;	// 언제부터 play가능한가?
	VSDateTime	    m_PayPlayAvailableDateTime;	// 언제까지 play가능한가?
	int				m_PayPlayAvailableHours;	// 사용 가능한 시간(시간제인 경우)
	Timeval 	   	m_PayPlayStartTime;         // 접속해서 play한 시간
	VSDateTime	    m_FamilyPayPlayAvailableDateTime;	// 언제까지 Family Pay play가 가능한가?

	uint			m_PayPlayFlag;				// 사용가능한 서비스

	bool			m_bPremiumPlay;
	bool			m_bPCRoomPlay;				// PC 방 사용자인가?
												// PC 방 유저 제한에 상관없이 유료 적용 중인 PC 방에서 플레이하고 있는가?

	bool			m_bFamilyPayAvailable;		// 패밀리 요금제 사용자인가?
	FamilyPayPartyType	m_FamilyPayPartyType;	// 패밀리 요금제 파티 적용 타입
};

#endif

