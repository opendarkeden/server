#ifndef __BILLING_INFO_H__
#define __BILLING_INFO_H__

#include <string>
using namespace std;

#include "types/ServerType.h"

#ifdef __NETMARBLE_SERVER__
#define __CONNECT_BILLING_SYSTEM__
#endif
//#define __COUT_BILLING_SYSTEM__

#ifdef __GAME_SERVER__
	#define LOGFILE_BILLING_PLAYER	"billingPlayerGame.txt"
	#define LOGFILE_BILLING_PACKET	"billingPacketGame.txt"
#elif defined(__LOGIN_SERVER__)
	#define LOGFILE_BILLING_PLAYER	"billingPlayerLogin.txt"
	#define LOGFILE_BILLING_PACKET	"billingPacketLogin.txt"
#else
	#define LOGFILE_BILLING_PLAYER	"billingPlayer.txt"
	#define LOGFILE_BILLING_PACKET	"billingPacker.txt"
#endif

////////////////////////////////////////////////////////////////////////////////
// Packet_Type에 대한 값(G=GameServer, B=BillingServer)
////////////////////////////////////////////////////////////////////////////////
enum BillingPacketType
{
	BILLING_PACKET_LOGIN	= 0x00000001,	// 게임에 들어올때		(G->B 이면 B->G)
	BILLING_PACKET_LOGOUT	= 0x00000002,	// 게임에서 나갈때		(G->B only)
	BILLING_PACKET_POLLING	= 0x00000003,	// GameServer에서는 	(사용 안함)
	BILLING_PACKET_INIT		= 0x00000004,	// 게임서버 처음 뜰때	(G->B only)
	BILLING_PACKET_REMAIN	= 0x00000005,	// 남은 시간 보여준다.	(B->G only)
	BILLING_PACKET_CHECK	= 0x00000006,	// 접속 중 체크			(B->G 이면 G->B)
	BILLING_PACKET_LOGIN_CHECK	= 0x00000008,	// 접속 중 체크			(G->B 이면 B->G(LoginVerify(Type 1)))

	BILLING_PACKET_MAX
};

////////////////////////////////////////////////////////////////////////////////
// BILLING_PACKET_LOGIN의 Result값
////////////////////////////////////////////////////////////////////////////////
enum BillingResultLogin {
	BILLING_RESULT_LOGIN_OK				= 0,	// 인증 성공
	BILLING_RESULT_LOGIN_DB_ERROR		= 2,	// DB에 접근 불가
	BILLING_RESULT_LOGIN_NETWORK_ERROR	= 3,	// 네트워크 오류
	BILLING_RESULT_LOGIN_NO_ACCOUNT		= 10,	// 인증 정보 없음
	BILLING_RESULT_LOGIN_NO_CASH		= 11,	// 잔액 부족
	BILLING_RESULT_LOGIN_NO_SESSION		= 12,	// 세션 없음
	BILLING_RESULT_LOGIN_BAD_PACKET		= 20,	// 정의 되지않은 패킷
	BILLING_RESULT_LOGIN_COM_ERROR		= 25,	// COM Error
	BILLING_RESULT_LOGIN_NO_RESPONSE	= 26,	// 시간(30초)동안 응답없음
	BILLING_RESULT_LOGIN_NO_MACHINE		= 27,	// 해당 장비 접속 불가
	BILLING_RESULT_LOGIN_BAD_GAME_NO	= 30,	// 패킷의 게임 넘버와 빌링 서버에 등록된 게임번호가 다름
	BILLING_RESULT_LOGIN_ACCOUNT_ERROR	= 31,	// 빌링 어카운트의 서비스 에러
//	BILLING_RESULT_LOGIN_DUPLICATE		= 32,	// 동시접속 불가
	BILLING_RESULT_LOGIN_DENY			= 33,	// 사용 불가(결제 정보는 있음)
	BILLING_RESULT_LOGIN_TIME_OVER		= 34,	// 유효 기간 지남
	BILLING_RESULT_LOGIN_BUSY			= 35,	// 기다리는 사람이 많음
	BILLING_RESULT_LOGIN_UNKNOWN_ERROR	= 100,	// 정의 되지 않은 오류
	BILLING_RESULT_LOGIN_IP_COM_ERROR	= 200,	// IP확인 중 COM Error
	BILLING_RESULT_LOGIN_IP_ERROR		= 201,	// IP 공급자 정보 부족
	BILLING_RESULT_LOGIN_KEY_COM_ERROR	= 210,	// 인증키 확인중 COM 에러
	BILLING_RESULT_LOGIN_NO_KEY			= 211,	// 인증키 없음

	BILLING_RESULT_LOGIN_MAX
};

////////////////////////////////////////////////////////////////////////////////
// BILLING_PACKET_REMAIN의 Result값
////////////////////////////////////////////////////////////////////////////////
enum BillingResultRemain {
	BILLING_RESULT_REMAIN_DISCONNECT	= -4,	// 강제 종료
	BILLING_RESULT_REMAIN_RESERVE		= -3,	// 새로운 결제정보 사용 시작
	BILLING_RESULT_REMAIN_DUPLICATE		= -2,	// 중복 로그인
	BILLING_RESULT_REMAIN_REFUND		= -1,	// 환불 되었다.
	BILLING_RESULT_REMAIN_NONE			= 0,	// 남은 시간 없다.
	BILLING_RESULT_REMAIN_TIME			= 1,	// 정상적으로 남은 시간

	BILLING_RESULT_REMAIN_MAX
};

////////////////////////////////////////////////////////////////////////////////
// BILLING_PACKET_CHECK의 Result값
////////////////////////////////////////////////////////////////////////////////
enum BillingResultCheck {
	BILLING_RESULT_CHECK_PLAYING		= 0,	// 정상 사용자
	BILLING_RESULT_CHECK_DISCONNECTED	= 1,	// 종료된 사용자

	BILLING_RESULT_CHECK_MAX
};

////////////////////////////////////////////////////////////////////////////////
// User_CC 값
////////////////////////////////////////////////////////////////////////////////
enum BillingUserCC
{
	BILLING_USER_METROTECH,		// 본썹~
	BILLING_USER_NETMARBLE,		// 넷마블 서버

	BILLING_USER_MAX
};

const string BillingUserCC2String[BILLING_USER_MAX] =
{
	"DE", 		// BILLING_USER_METROTECH,		// 본썹~
	"NM"		// BILLING_USER_NETMARBLE,		// 넷마블 서버
};

////////////////////////////////////////////////////////////////////////////////
// BillingInfo == _AUTH_GAME
////////////////////////////////////////////////////////////////////////////////
struct _AUTH_GAME {
	mutable int 	Packet_Type;		// 패킷 타입
	mutable int 	Result;				// 처리결과값
	char 			S_KEY[32];			// 인증키를 사용할때만 사용한다.
	char 			Session[32];		// guid
	char 			User_CC[4];			// 구분 코드
	char 			User_No[20];		// 사용자 번호나 주민등록번호
	char 			User_ID[40]; 		// 사용자 아이디
	char 			User_IP[24];		// 사용자 접속 아이피
	char 			User_Gender;		// 사용자 성별
	char 			User_Status[3];		// 사용자 상태
	char 			User_PayType[2];	// 결제 수단 무료 사용자인 경우 "F0"
	mutable int 	User_Age;			// 사용자 나이
	mutable int 	Game_No;			// 게임 번호(과금 DB에 등록된 번호)
	char 			Bill_PayType[2];	// 지불 방식 "A0" 후불, "D0" 직불, "P0" 선불
	char 			Bill_Method[2];		// 과금 방식
	char 			Expire_Date[12];	// 과금 종료일 YYYYMMDDHHMM
	mutable int 	Remain_Time;		// 정량:남은 시간(초) 정액:번들 쿠폰번호

};

typedef _AUTH_GAME BillingInfo;

const int szBillingInfo = sizeof(BillingInfo);

#endif
