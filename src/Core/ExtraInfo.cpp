//////////////////////////////////////////////////////////////////////
// 
// Filename    : ExtraInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "ExtraInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ExtraInfo::ExtraInfo () 
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ExtraInfo::~ExtraInfo () noexcept
{
	// �Ҽӵ� ��� ��ü���� �����Ѵ�.
	while ( !m_ExtraSlotInfoList.empty() ) 
	{
		ExtraSlotInfo * pExtraSlotInfo = m_ExtraSlotInfoList.front();
		SAFE_DELETE(pExtraSlotInfo);
		m_ExtraSlotInfoList.pop_front();
	}
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void ExtraInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		ExtraSlotInfo * pExtraSlotInfo = new ExtraSlotInfo();
		pExtraSlotInfo->read( iStream );
		m_ExtraSlotInfoList.push_back( pExtraSlotInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void ExtraInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ListNum );

    for ( list<ExtraSlotInfo*>:: const_iterator itr = m_ExtraSlotInfoList.begin(); itr!= m_ExtraSlotInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t ExtraInfo::getSize()
{

	PacketSize_t PacketSize = szBYTE;

	for ( list< ExtraSlotInfo* >::const_iterator itr = m_ExtraSlotInfoList.begin() ; itr != m_ExtraSlotInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string ExtraInfo::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ExtraInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<ExtraSlotInfo*>::const_iterator itr = m_ExtraSlotInfoList.begin(); itr!= m_ExtraSlotInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
