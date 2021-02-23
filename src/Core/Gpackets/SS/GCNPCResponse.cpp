//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCResponse.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCNPCResponse.h"

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCNPCResponse::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_Code);

	switch (m_Code)
	{
		// 파라미터를 써야 하는 코드
		case NPC_RESPONSE_REPAIR_OK:
		case NPC_RESPONSE_SILVER_COATING_OK:
		case NPC_RESPONSE_DONATION_OK:
		case NPC_RESPONSE_DECREASE_BALL:
		case NPC_RESPONSE_GUILD_SHOW_REGIST:
		case NPC_RESPONSE_SHOW_TAX_BALANCE:
		case NPC_RESPONSE_WITHDRAW_TAX_OK:				// 길드 마스터가 세금을 찾는 데에 성공했다.
		case NPC_RESPONSE_COUPLE_CANNOT_MEET:
		case NPC_RESPONSE_NOT_COUPLE:
		case NPC_RESPONSE_QUEST:
		case NPC_RESPONSE_LOTTERY:
		case NPC_RESPONSE_SHOW_TAX_RATIO:
		case NPC_RESPONSE_SHOW_DONATION_DIALOG:
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:
		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:
			iStream.read(m_Parameter);
			break;
		// 파라미터를 쓰지 않아도 되는 코드
		default:
			break;
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCNPCResponse::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_Code);

	switch (m_Code)
	{
		// 파라미터를 써야 하는 코드
		case NPC_RESPONSE_REPAIR_OK:
		case NPC_RESPONSE_SILVER_COATING_OK:
		case NPC_RESPONSE_DONATION_OK:
		case NPC_RESPONSE_DECREASE_BALL:
		case NPC_RESPONSE_GUILD_SHOW_REGIST:
		case NPC_RESPONSE_SHOW_TAX_BALANCE:
		case NPC_RESPONSE_WITHDRAW_TAX_OK:				// 길드 마스터가 세금을 찾는 데에 성공했다.
		case NPC_RESPONSE_COUPLE_CANNOT_MEET:
		case NPC_RESPONSE_NOT_COUPLE:
		case NPC_RESPONSE_QUEST:
		case NPC_RESPONSE_LOTTERY:
		case NPC_RESPONSE_SHOW_TAX_RATIO:
		case NPC_RESPONSE_SHOW_DONATION_DIALOG:
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:
		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:
			oStream.write(m_Parameter);
			break;
		// 파라미터를 쓰지 않아도 되는 코드
		default:
			break;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCNPCResponse::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCNPCResponseHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 패킷 사이즈
//////////////////////////////////////////////////////////////////////////////

PacketSize_t GCNPCResponse::getPacketSize () const 
	throw() 
{
	__BEGIN_TRY

	PacketSize_t size = szBYTE;

	switch (m_Code)
	{
		// 파라미터를 써야 하는 코드
		case NPC_RESPONSE_REPAIR_OK:
		case NPC_RESPONSE_SILVER_COATING_OK:
		case NPC_RESPONSE_DONATION_OK:
		case NPC_RESPONSE_DECREASE_BALL:
		case NPC_RESPONSE_GUILD_SHOW_REGIST:
		case NPC_RESPONSE_SHOW_TAX_BALANCE:
		case NPC_RESPONSE_WITHDRAW_TAX_OK:				// 길드 마스터가 세금을 찾는 데에 성공했다.
		case NPC_RESPONSE_COUPLE_CANNOT_MEET:
		case NPC_RESPONSE_NOT_COUPLE:
		case NPC_RESPONSE_QUEST:
		case NPC_RESPONSE_LOTTERY:
		case NPC_RESPONSE_SHOW_TAX_RATIO:
		case NPC_RESPONSE_SHOW_DONATION_DIALOG:
		case NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG:
		case NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG:
			size += szuint;
			break;
		// 파라미터를 쓰지 않아도 되는 코드
		default:
			break;
	}

	return size;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCNPCResponse::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCNPCResponse(" 
	    << "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
	    << ")";
	return msg.toString();

	__END_CATCH
}
