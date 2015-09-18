/////////////////////////////////////////////////////////////////////////////
// filename	: MPacketID.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_ID_H__
#define __MPACKET_ID_H__

// MPacketID send enum
enum
{
	PTC_CONNECT_ASK = 0x01,			// 게임서버의 접속 요청
	PTC_LOGOUT = 0x11,				// 게임서버의 접속 종료
	PTC_USERINFO = 0x20,			// 유저 정보 요청
	PTC_RECEIVE_OK = 0x30,			// 받은 자료에 대한 처리 여부
	PTC_RESULT = 0x40,				// 마지막으로 전송받은 자료에 대한 처리 여부
	PTC_ERROR = 0xFF,				// 게임서버에서 처리 에러에 대한 결과를 보내기 위해서 사용된다.

	PTC_SEND_MAX
};

// MPacketID recv enum
enum
{
	PTS_CONNECT_ACCEPT = 0x01,		// 게임서버의 접속 요청 허가
	PTS_POWERPOINT = 0x20,			// 요청한 정보
	PTS_ERROR = 0xFF,				// 서버 오류 알림

	PTC_MAX
};

#endif

