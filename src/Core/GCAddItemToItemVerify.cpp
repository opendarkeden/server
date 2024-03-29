//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToItemVerify.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCAddItemToItemVerify.h"

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	iStream.read(m_Code);

	switch (m_Code)
	{
		// 파라미터를 써야 하는 코드
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
			iStream.read(m_Parameter);
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THREE_ENCHANT_OK:
			iStream.read(m_Parameter);
			iStream.read(m_Parameter2);
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
void GCAddItemToItemVerify::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	oStream.write(m_Code);

	switch (m_Code)
	{
		// 파라미터를 써야 하는 코드
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
			oStream.write(m_Parameter);
			break;
		case ADD_ITEM_TO_ITEM_VERIFY_THREE_ENCHANT_OK:
			oStream.write(m_Parameter);
			oStream.write(m_Parameter2);
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
void GCAddItemToItemVerify::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCAddItemToItemVerifyHandler::execute(this , pPlayer);
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 패킷 사이즈
//////////////////////////////////////////////////////////////////////////////

PacketSize_t GCAddItemToItemVerify::getPacketSize () const 
	 
{
	__BEGIN_TRY

	PacketSize_t size = szBYTE;

	switch (m_Code)
	{
		// 파라미터를 써야 하는 코드
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
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
string GCAddItemToItemVerify::toString () const
       
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddItemToItemVerify(" 
	    << "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
	    << ")";
	return msg.toString();

	__END_CATCH
}
