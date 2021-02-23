//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCChangeInventoryItemNum.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCChangeInventoryItemNum.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCChangeInventoryItemNum::GCChangeInventoryItemNum () 
     throw ()
{
	__BEGIN_TRY
	m_ChangedItemListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCChangeInventoryItemNum::~GCChangeInventoryItemNum () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCChangeInventoryItemNum::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ChangedItemListNum );

	int i;
	ObjectID_t item;
	ItemNum_t num;
	
	for( i = 0; i < m_ChangedItemListNum; i++ ) {
		iStream.read( item);
		m_ChangedItemList.push_back( item);
	}
	for( i = 0; i < m_ChangedItemListNum; i++ ) {
		iStream.read( num);
		m_ChangedItemNumList.push_back( num);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCChangeInventoryItemNum::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ChangedItemListNum );

    for ( list<ObjectID_t>:: const_iterator itr = m_ChangedItemList.begin(); itr!= m_ChangedItemList.end(); itr++) {
		oStream.write(*itr);
	}
    for ( list<ItemNum_t>:: const_iterator itr2 = m_ChangedItemNumList.begin(); itr2!= m_ChangedItemNumList.end(); itr2++) {
		oStream.write(*itr2);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// GCChangeInventoryItemNum::addListElement()
// 
// ( 변화부위, 변화수치 ) 의 한 셋을 리스트에 넣기 위한 멤버 함수. 
//
//////////////////////////////////////////////////////////////////////
void GCChangeInventoryItemNum::addChangedItemListElement( ObjectID_t id, ItemNum_t num)
	throw()
{
	__BEGIN_TRY

	// 변하는 것이 무엇인지 List에 넣는다.
	m_ChangedItemList.push_back( id);
	m_ChangedItemNumList.push_back( num);

	// 변화 셋의 갯수를 하나 증가 시킨다.
	m_ChangedItemListNum++;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCChangeInventoryItemNum::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Changed ListNum:" << (int)m_ChangedItemListNum 
		<< " ChangedListSet(";

	int i;
	list<ObjectID_t>::const_iterator itrItem = m_ChangedItemList.begin();
	list<ItemNum_t>::const_iterator itrItemNum = m_ChangedItemNumList.begin();
	for( i = 0; i < m_ChangedItemListNum; i++)
	{
		msg << "(" << (int)(*itrItem) << ","<<(int)(*itrItemNum)<<"),";
		itrItem++;
		itrItemNum++;
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}

