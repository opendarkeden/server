//--------------------------------------------------------------------------------
// 
// Filename    : GCRequestPowerPointResult.h 
// Written By  : bezz
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_REQUEST_POWER_POINT_RESULT_H__
#define __GC_REQUEST_POWER_POINT_RESULT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCRequestPowerPointResult;
//
//--------------------------------------------------------------------------------

class GCRequestPowerPointResult : public Packet
{
public:
	enum RESULT_CODE
	{
		NO_ERROR = 0,
		SERVER_ERROR,		// 파워짱 서버는 살아있으나 현재 정상적으로 동작하지 못하는 상황
		PROCESS_ERROR,		// 서버 처리 오류 ( ex DB 오류 )
		NO_MEMBER,			// 파워짱 회원이 아닌 경우
		NO_POINT,			// 누적된 파워짱 포인트가 없음
		NO_MATCHING,		// 매칭 정보가 없음.
							// 파워짱 홈페이지에서 게임 매칭을 하지 않은 경우
							// 파워짱 홈페이지에서 매칭을 유도하는 문장을 부여준다.
		CONNECT_ERROR,		// 게임코드 확인 실패 및 패킷 오류
	};
public:
	GCRequestPowerPointResult() throw();
	~GCRequestPowerPointResult() throw();

public :
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);

    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_REQUEST_POWER_POINT_RESULT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + szint + szint; }

	// get packet name
	string getPacketName() const throw() { return "GCRequestPowerPointResult"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set Error Code
	BYTE getErrorCode() const { return m_ErrorCode; }
	void setErrorCode( BYTE errorcode ) { m_ErrorCode = errorcode; }

	// get / set SumPowerPoint
	int getSumPowerPoint() const { return m_SumPowerPoint; }
	void setSumPowerPoint( int powerpoint ) { m_SumPowerPoint = powerpoint; }

	// get / set RequestPowerPoint
	int getRequestPowerPoint() const { return m_RequestPowerPoint; }
	void setRequestPowerPoint( int powerpoint ) { m_RequestPowerPoint = powerpoint; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :
	// 에러 코드
	BYTE	m_ErrorCode;

	// 현재 누적된 파워짱 포인트
	int		m_SumPowerPoint;

	// 요청으로 가져온 파워짱 포인트
	int		m_RequestPowerPoint;
};


//--------------------------------------------------------------------------------
//
// class GCRequestPowerPointResultFactory;
//
// Factory for GCRequestPowerPointResult
//
//--------------------------------------------------------------------------------

class GCRequestPowerPointResultFactory : public PacketFactory
{
public :
	// create packet
	Packet* createPacket() throw() { return new GCRequestPowerPointResult(); }

	// get packet name
	string getPacketName() const throw() { return "GCRequestPowerPointResult"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_REQUEST_POWER_POINT_RESULT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRequestPowerPointResultPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szint + szint; }
};



//--------------------------------------------------------------------------------
//
// class GCRequestPowerPointResultHandler;
//
//--------------------------------------------------------------------------------

class GCRequestPowerPointResultHandler
{
public :
	// execute packet's handler
	static void execute(GCRequestPowerPointResult* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif

