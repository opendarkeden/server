//////////////////////////////////////////////////////////////////////
// 
// Filename    : GearInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GearInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GearInfo::GearInfo () 
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GearInfo::~GearInfo () noexcept
{
	// �Ҽӵ� ��� ��ü���� �����Ѵ�.
	while ( !m_GearSlotInfoList.empty() ) {
		GearSlotInfo * pGearSlotInfo = m_GearSlotInfoList.front();
		SAFE_DELETE(pGearSlotInfo);
		m_GearSlotInfoList.pop_front();
	}
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GearInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		GearSlotInfo * pGearSlotInfo = new GearSlotInfo();
		pGearSlotInfo->read( iStream );
		m_GearSlotInfoList.push_back( pGearSlotInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GearInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ListNum );

    for ( list<GearSlotInfo*>:: const_iterator itr = m_GearSlotInfoList.begin(); itr!= m_GearSlotInfoList.end(); itr++) {
		Assert( *itr != NULL );
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t GearInfo::getSize()
{

	PacketSize_t PacketSize = szBYTE;

	for ( list< GearSlotInfo* >::const_iterator itr = m_GearSlotInfoList.begin() ; itr != m_GearSlotInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GearInfo::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GearInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( list<GearSlotInfo*>::const_iterator itr = m_GearSlotInfoList.begin(); itr!= m_GearSlotInfoList.end() ; itr++ ) {
		Assert( *itr != NULL );
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
