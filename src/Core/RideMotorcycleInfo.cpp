//////////////////////////////////////////////////////////////////////////////
// Filename    : RideMotorcycleInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RideMotorcycleInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
RideMotorcycleInfo::RideMotorcycleInfo () 
{
	__BEGIN_TRY

	m_ObjectID   = 0;
	m_ItemType   = 0;
	m_ListNum    = 0;

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
RideMotorcycleInfo::~RideMotorcycleInfo () noexcept
{
	while ( !m_RideMotorcycleSlotInfoList.empty() ) 
	{
		RideMotorcycleSlotInfo * pRideMotorcycleSlotInfo = m_RideMotorcycleSlotInfoList.front();
		SAFE_DELETE(pRideMotorcycleSlotInfo);
		m_RideMotorcycleSlotInfoList.pop_front();
	}
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void RideMotorcycleInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
	
	iStream.read( m_ObjectID );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );

	for( int i = 0; i < optionSize; i++ ) 
	{
		OptionType_t optionType;
		iStream.read( optionType );
		addOptionType( optionType );
	}


	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) 
	{
		RideMotorcycleSlotInfo * pRideMotorcycleSlotInfo = new RideMotorcycleSlotInfo();
		pRideMotorcycleSlotInfo->read( iStream );
		m_RideMotorcycleSlotInfoList.push_back( pRideMotorcycleSlotInfo );
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void RideMotorcycleInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_ItemType );

	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );

	list<OptionType_t>:: const_iterator iOption = m_OptionType.begin();
    for (; iOption!= m_OptionType.end();iOption++) 
	{
		OptionType_t optionType = *iOption;
		oStream.write( optionType );
	}

	oStream.write( m_ListNum );

	list<RideMotorcycleSlotInfo*>:: const_iterator itr = m_RideMotorcycleSlotInfoList.begin();
    for (;itr!= m_RideMotorcycleSlotInfoList.end(); itr++) 
	{
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// getSize
//////////////////////////////////////////////////////////////////////////////
PacketSize_t RideMotorcycleInfo::getSize()
{
	PacketSize_t PacketSize = 0;

	PacketSize += szObjectID;   // motorcycle object id
	PacketSize += szItemType;   // motorcycle type
	PacketSize += szBYTE + m_OptionType.size(); // motorcycle option type
	PacketSize += szBYTE;       // number of item in motorcycle inventory

	list<RideMotorcycleSlotInfo*>::const_iterator itr = m_RideMotorcycleSlotInfoList.begin();
	for (; itr != m_RideMotorcycleSlotInfoList.end(); itr ++) 
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string RideMotorcycleInfo::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "RideMotorcycleInfo( "
		<< "ObjectID : "    << (int)m_ObjectID
		<< ",ItemType : "   << (int)m_ItemType
		<< ",OptionTypeSize : " << (int)m_OptionType.size()
		<< ",ListNum :"     << (int)m_ListNum 
		<< ",ListSet( ";

	list<RideMotorcycleSlotInfo*>::const_iterator itr = m_RideMotorcycleSlotInfoList.begin();
	for (; itr!= m_RideMotorcycleSlotInfoList.end() ; itr++) 
	{
		msg << (*itr)->toString() << ",";
	}

	msg << ")";
	return msg.toString();

	__END_CATCH
}
