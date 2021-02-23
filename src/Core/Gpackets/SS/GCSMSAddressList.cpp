//////////////////////////////////////////////////////////////////////
// 
// Filename	: GCSMSAddressList.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//			   멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCSMSAddressList.h"

void AddressUnit::read( SocketInputStream& iStream )
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE szStr;

	iStream.read( ElementID );
	iStream.read(szStr);
	iStream.read( CharacterName, szStr );
	iStream.read(szStr);
	iStream.read( CustomName, szStr );
	iStream.read(szStr);
	iStream.read( Number, szStr );

	__END_CATCH
}

void AddressUnit::write( SocketOutputStream& oStream ) const
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE szStr;

	oStream.write( ElementID );

	szStr = CharacterName.size();
	oStream.write(szStr);
	oStream.write(CharacterName);

	szStr = CustomName.size();
	oStream.write(szStr);
	oStream.write(CustomName);

	szStr = Number.size();
	oStream.write(szStr);
	oStream.write(Number);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSMSAddressList::GCSMSAddressList () 
	 throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSMSAddressList::~GCSMSAddressList () 
	throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSMSAddressList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_Addresses.clear();

	BYTE Num;
	iStream.read(Num);

	for ( int i=0; i<Num; ++i )
	{
		AddressUnit* pUnit = new AddressUnit;
		pUnit->read(iStream);
		m_Addresses.push_back( pUnit );
	}
		
	__END_CATCH
}

			
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSMSAddressList::write ( SocketOutputStream & oStream ) 
	 const throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE Num = m_Addresses.size();
	oStream.write(Num);

	vector<AddressUnit*>::const_iterator itr = m_Addresses.begin();
	vector<AddressUnit*>::const_iterator endItr = m_Addresses.end();

	for ( ; itr != endItr; ++itr )
	{
		(*itr)->write(oStream);
	}
		
	__END_CATCH
}

PacketSize_t GCSMSAddressList::getPacketSize() const throw()
{
	__BEGIN_TRY

	PacketSize_t ret = szBYTE;

	vector<AddressUnit*>::const_iterator itr = m_Addresses.begin();
	vector<AddressUnit*>::const_iterator endItr = m_Addresses.end();

	for ( ; itr != endItr; ++itr )
	{
		ret += (*itr)->getPacketSize();
	}

	return ret;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSMSAddressList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSMSAddressListHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCSMSAddressList::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSMSAddressList("
		<< ")";
	return msg.toString();

	__END_CATCH
}

