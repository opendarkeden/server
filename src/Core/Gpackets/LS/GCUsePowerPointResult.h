//--------------------------------------------------------------------------------
// 
// Filename    : GCUsePowerPointResult.h 
// Written By  : bezz
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_USE_POWER_POINT_RESULT_H__
#define __GC_USE_POWER_POINT_RESULT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCUsePowerPointResult;
//
//--------------------------------------------------------------------------------

class GCUsePowerPointResult : public Packet
{
public:
	enum RESULT_CODE
	{
		NO_ERROR = 0,
		NOT_ENOUGH_POWER_POINT,		// 파워 포인트가 부족합니다.
		NOT_ENOUGH_INVENTORY_SPACE,	// 인벤토리에 공간이 부족합니다.
	};

	enum ITEM_CODE
	{
		CANDY = 0,				// 사탕 1개 
		RESURRECTION_SCROLL,	// 부활 스크롤 1개
		ELIXIR_SCROLL,			// 엘릭서 스크롤 1개
		MEGAPHONE,				// 확성기 30분
		NAMING_PEN,				// 네이밍 펜 1개
		SIGNPOST,				// 알림판 6시간
		BLACK_RICE_CAKE_SOUP,	// 검은 떡국 1개
	};

public:
	GCUsePowerPointResult() throw();
	~GCUsePowerPointResult() throw();

public :
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_USE_POWER_POINT_RESULT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + szBYTE + szint; }

	// get packet name
	string getPacketName() const throw() { return "GCUsePowerPointResult"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set Error Code
	BYTE getErrorCode() const { return m_ErrorCode; }
	void setErrorCode( BYTE errorcode ) { m_ErrorCode = errorcode; }

	// get / set Item Code
	BYTE getItemCode() const { return m_ItemCode; }
	void setItemCode( BYTE itemcode ) { m_ItemCode = itemcode; }

	// get / set Power Point
	int getPowerPoint() const { return m_PowerPoint; }
	void setPowerPoint( int powerpoint ) { m_PowerPoint = powerpoint; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :
	// 에러 코드
	BYTE	m_ErrorCode;

	// 아이템 코드
	BYTE	m_ItemCode;

	// 파워 포인트
	int		m_PowerPoint;
};


//--------------------------------------------------------------------------------
//
// class GCUsePowerPointResultFactory;
//
// Factory for GCUsePowerPointResult
//
//--------------------------------------------------------------------------------

class GCUsePowerPointResultFactory : public PacketFactory
{
public :
	// create packet
	Packet* createPacket() throw() { return new GCUsePowerPointResult(); }

	// get packet name
	string getPacketName() const throw() { return "GCUsePowerPointResult"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_USE_POWER_POINT_RESULT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUsePowerPointResultPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szBYTE + szint; }
};



//--------------------------------------------------------------------------------
//
// class GCUsePowerPointResultHandler;
//
//--------------------------------------------------------------------------------

class GCUsePowerPointResultHandler
{
public :
	// execute packet's handler
	static void execute(GCUsePowerPointResult* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif

