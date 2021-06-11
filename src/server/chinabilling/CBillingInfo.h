//////////////////////////////////////////////////////////
// filename : CBillingInfo.h
//////////////////////////////////////////////////////////

#ifndef __CBILLING_INFO_H__
#define __CBILLING_INFO_H__

#include <string>
using namespace std;

//#define __CONNECT_CBILLING_SYSTEM__
//#define __COUT_CBILLING_SYSTEM__

#ifdef __GAME_SERVER__
	#define LOGFILE_CBILLING_PLAYER		"cbillingPlayerGame.txt"
	#define LOGFILE_CBILLING_PACKET		"cbillingPacketGame.txt"
	#define LOGFILE_CBILLING_ERROR		"cbillingErrorGame.txt"
#elif defined(__LOGIN_SERVER__)
	#define LOGFILE_CBILLING_PLAYER		"cbillingPlayerLogin.txt"
	#define LOGFILE_CBILLING_PACKET		"cbillingPacketLogin.txt"
	#define LOGFILE_CBILLING_ERROR		"cbillingErrorLogin.txt"
#else
	#define LOGFILE_CBILLING_PLAYER		"cbillingPlayer.txt"
	#define LOGFILE_CBILLING_PACKET		"cbillingPacket.txt"
	#define LOGFILE_CBILLING_ERROR		"cbillingError.txt"
#endif

/////////////////////////////////////////
// PacketType 에 대한 값
/////////////////////////////////////////
enum CBillingPacketType
{
	CBILLING_PACKET_REQUEST		= 1,		// request packet
	CBILLING_PACKET_RESPONSE	= 2,		// response packet

	CBILLING_PACKET_MAX
};

/////////////////////////////////////////
// MethodCode 에 대한 값
/////////////////////////////////////////
enum CBillingMethodCode
{
	CBILLING_METHOD_CODE_LOGIN					= 1001,		// Login, 플레이어의 접속
	CBILLING_METHOD_CODE_MINUS_POINT			= 1002,		// minus point, 일정 시간이 지난 후 포인트를 깐다.
	CBILLING_METHOD_CODE_MINUS_MINUTE			= 1003,		// minus minute, 일정 시간이 지난 후 시간을 깐다.
	CBILLING_METHOD_CODE_LOGOUT					= 1004,		// Logout, 플레이어의 접속 종료
	CBILLING_METHOD_CODE_INTERVAL_VALIDATION	= 1005,		// interval validation, 간격 확인용

	CBILLING_METHOD_CODE_MAX
};

/////////////////////////////////////////
// ReturnCode 에 대한 값
/////////////////////////////////////////
enum CBillingReturnCode
{
	CBILLING_RETURN_CODE_SUCCESS			= 0,		// success, 성공
	CBILLING_RETURN_CODE_FAIL				= 1,		// fail, 실패
	CBILLING_RETURN_CODE_DB_ERROR			= 2,		// db error, 데이터 베이스 에러
	CBILLING_RETURN_CODE_INVALID_LOGIN_NAME	= 11,		// login name invalid, 유효하지 않은 login name
	CBILLING_RETURN_CODE_FAIL_MINUS_POINT	= 12,		// fail to minus point, minus point 에 대한 실패
	CBILLING_RETURN_CODE_FAIL_MINUS_MINUTE	= 13,		// fail to minus minute, minus minute 에 대한 실패

	CBILLGIN_RETURN_CODE_MAX
};

/////////////////////////////////////////
// PlayerType 에 대한 값
/////////////////////////////////////////
enum CBillingPlayerType
{
	CBILLING_PLAYER_TYPE_UNLIMITED		= 1,		// unlimited using, 무제한 사용자
	CBILLING_PLAYER_TYPE_LIMITED		= 2,		// limited using, 제한 사용자
	CBILLING_PLAYER_TYPE_MONTHLY		= 3,		// monthly, 월단위 사용자
	CBILLING_PLAYER_TYPE_POINT			= 4,		// point, point 사용자

	CBILLING_PLAYER_TYPE_MAX
};

/////////////////////////////////////////
// PayType 에 대한 값
/////////////////////////////////////////
enum CBillingPayType
{
	CBILLING_PAY_TYPE_PRE_PAID		= 1,		// PrePaid, 선결제
	CBILLING_PAY_TYPE_POST_PAID		= 2,		// PostPaid, 후결제

	CBILLING_PAY_TYPE_MAX
};

/////////////////////////////////////////
// CBillingPacketHeaderInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_HEADER
{
	mutable int		Version_No;				// interface version
	mutable int		Packet_Type;			// packet type
	mutable int		Method_Code;			// method code
	mutable int		Return_Code;			// return code
	mutable int		Session_ID;				// session id
	char			Reserve[4];				// reserved
	mutable int		Body_Length;			// body length
};

typedef _CBILLING_PACKET_HEADER CBillingPacketHeaderInfo;
const int szCBillingPacketHeaderInfo = sizeof(CBillingPacketHeaderInfo);

/////////////////////////////////////////
// CBillingPacketErrorBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_ERROR_BODY
{
	char		Login_Name[64];			// login name
	char		Return_Message[128];	// error message
};

typedef _CBILLING_PACKET_ERROR_BODY CBillingPacketErrorBodyInfo;
const int szCBillingPacketErrorBodyInfo = sizeof(CBillingPacketErrorBodyInfo);

/////////////////////////////////////////
// CBillingPacketRequestLoginBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_REQUEST_LOGIN_BODY
{
	char		Login_Name[64];			// login name
	char		Player_IP[32];			// IP address. xxx.xxx.xxx.xxx
	char		Player_MAC[32];			// MAC address
};

typedef _CBILLING_PACKET_REQUEST_LOGIN_BODY CBillingPacketRequestLoginBodyInfo;
const int szCBillingPacketRequestLoginBodyInfo = sizeof(CBillingPacketRequestLoginBodyInfo);

/////////////////////////////////////////
// CBillingPacketResponseLoginBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_RESPONSE_LOGIN_BODY
{
	char			Login_Name[64];			// login name
	char			End_Date_Time[16];		// end date time of monthly user. format : YYYYMMDDHHMISS
	mutable int		Player_Type;			// type of user. unlimited, limited, monthly, point.
	mutable int		Pay_Type;				// pre paid or post paid
	mutable int		Free_Left_Time;			// free left time ( minute )
	mutable int		Rating_Left_Time;		// rating left time ( minute )
};

typedef _CBILLING_PACKET_RESPONSE_LOGIN_BODY CBillingPacketResponseLoginBodyInfo;
const int szCBillingPacketResponseLoginBodyInfo = sizeof(CBillingPacketResponseLoginBodyInfo);


///////////////////////////////////////////
// CBillingPacketRequestMinusPointBodyInfo
///////////////////////////////////////////
struct _CBILLING_PACKET_REQUEST_MINUS_POINT_BODY
{
	char		Login_Name[64];			// login name
};

typedef _CBILLING_PACKET_REQUEST_MINUS_POINT_BODY CBillingPacketRequestMinusPointBodyInfo;
const int szCBillingPacketRequestMinusPointBodyInfo = sizeof(CBillingPacketRequestMinusPointBodyInfo);

/////////////////////////////////////////
// CBillingPacketResponseMinusPointBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_RESPONSE_MINUS_POINT_BODY
{
	char			Login_Name[64];			// login name
	mutable int		Player_Type;			// type of user. unlimited, limited, monthly, point.
	mutable int		Pay_Type;				// pre paid or post paid
	mutable int		Free_Left_Time;			// free left time ( minute )
	mutable int		Rating_Left_Time;		// rating left time ( minute )
	mutable int		Minus_Free_Point;		// minus point from free left time
	mutable int		Minus_Point;			// minus point from pay left time
};

typedef _CBILLING_PACKET_RESPONSE_MINUS_POINT_BODY CBillingPacketResponseMinusPointBodyInfo;
const int szCBillingPacketResponseMinusPointBodyInfo = sizeof(CBillingPacketResponseMinusPointBodyInfo);

/////////////////////////////////////////
// CBillingPacketRequestMinusMinuteBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_REQUEST_MINUS_MINUTE_BODY
{
	char		Login_Name[64];			// login name
};

typedef _CBILLING_PACKET_REQUEST_MINUS_MINUTE_BODY CBillingPacketRequestMinusMinuteBodyInfo;
const int szCBillingPacketRequestMinusMinuteBodyInfo = sizeof(CBillingPacketRequestMinusMinuteBodyInfo);

/////////////////////////////////////////
// CBillingPacketResponseMinusMinuteBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_RESPONSE_MINUS_MINUTE_BODY
{
	char			Login_Name[64];			// login name
	mutable int		Pay_Type;				// pre paid or post paid
	mutable int		Free_Left_Time;			// free left time ( minute )
	mutable int		Rating_Left_Time;		// rating left time( minute )
	mutable int		Minus_Free_Duration;	// minus minute from free left time
	mutable int		Minus_Duration;			// minus minute from pay left time
};

typedef _CBILLING_PACKET_RESPONSE_MINUS_MINUTE_BODY CBillingPacketResponseMinusMinuteBodyInfo;
const int szCBillingPacketResponseMinusMinuteBodyInfo = sizeof(CBillingPacketResponseMinusMinuteBodyInfo);

/////////////////////////////////////////
// CBillingPacketRequestLogoutBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_REQUEST_LOGOUT_BODY
{
	char		Login_Name[64];			// login name
};

typedef _CBILLING_PACKET_REQUEST_LOGOUT_BODY CBillingPacketRequestLogoutBodyInfo;
const int szCBillingPacketRequestLogoutBodyInfo = sizeof(CBillingPacketRequestLogoutBodyInfo);

/////////////////////////////////////////
// CBillingPacketResponseLogoutBodyInfo
/////////////////////////////////////////
struct _CBILLING_PACKET_RESPONSE_LOGOUT_BODY
{
	char			Login_Name[64];			// login name
	mutable int		Minus_Free_Point;		// minus point from free left time
	mutable int		Minus_Point;			// minus point from pay left time 
};

typedef _CBILLING_PACKET_RESPONSE_LOGOUT_BODY CBillingPacketResponseLogoutBodyInfo;
const int szCBillingPacketResponseLogoutBodyInfo = sizeof(CBillingPacketResponseLogoutBodyInfo);

////////////////////////////////////////////////////
// CBillingPacketRequestIntervalValidationBodyInfo
////////////////////////////////////////////////////
struct _CBILLING_PACKET_REQUEST_INTERVAL_VALIDATION_BODY
{
	char		Parameter_Name[64];		// Name of parameter. always "MINUS_INTERVAL"
	char		Parameter_Value[64];	// Value of minus interval configured in gameserver. unit second
};

typedef _CBILLING_PACKET_REQUEST_INTERVAL_VALIDATION_BODY CBillingPacketRequestIntervalValidationBodyInfo;
const int szCBillingPacketRequestIntervalValidationBodyInfo = sizeof(CBillingPacketRequestIntervalValidationBodyInfo);

////////////////////////////////////////////////////
// CBillingPacketResponseIntervalValidationBodyInfo
////////////////////////////////////////////////////
struct _CBILLING_PACKET_RESPONSE_INTERVAL_VALIDATION_BODY
{
	char		Parameter_Name[64];		// Name of parameter. always "MINUS_INTERVAL"
	char		Parameter_Value[64];	// Value of minus interval configured in gameserver. unit second
};

typedef _CBILLING_PACKET_RESPONSE_INTERVAL_VALIDATION_BODY CBillingPacketResponseIntervalValidationBodyInfo;
const int szCBillingPacketResponseIntervalValidationBodyInfo = sizeof(CBillingPacketResponseIntervalValidationBodyInfo);

#endif

