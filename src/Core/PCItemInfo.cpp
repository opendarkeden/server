//////////////////////////////////////////////////////////////////////////////
// Filename    : PCItemInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "PCItemInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "StringStream.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
PCItemInfo::PCItemInfo () 
     throw ()
{
	__BEGIN_TRY

	m_ObjectID     = 0;
	m_IClass       = 0;
	m_ItemType     = 0;
	m_Durability   = 0;
	m_Silver       = 0;
	m_Grade        = 0;
	m_EnchantLevel = 0;
	m_ItemNum      = 0;
	m_MainColor    = 0;
	m_ListNum      = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
PCItemInfo::~PCItemInfo () 
    throw ()
{
	__BEGIN_TRY

	while (!m_SubItemInfoList.empty()) 
	{
		SubItemInfo* pSubItemInfo = m_SubItemInfoList.front();
		SAFE_DELETE(pSubItemInfo);
		m_SubItemInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void PCItemInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_IClass );
	iStream.read( m_ItemType );

	BYTE optionSize;
	iStream.read( optionSize );

	m_OptionType.clear();
	for (int i = 0; i < optionSize; i++) 
	{
		OptionType_t optionType;
		iStream.read( optionType );
		m_OptionType.push_back( optionType );
	}

	iStream.read( m_Durability );
	iStream.read( m_Silver );
	iStream.read( m_Grade );
	iStream.read( m_EnchantLevel );
	iStream.read( m_ItemNum );
	iStream.read( m_MainColor );
	iStream.read( m_ListNum );

	for (int i = 0; i < m_ListNum; i++) 
	{
		SubItemInfo* pSubItemInfo = new SubItemInfo();
		pSubItemInfo->read(iStream);
		m_SubItemInfoList.push_back( pSubItemInfo );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void PCItemInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	oStream.write( m_IClass );
	oStream.write( m_ItemType );

	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );

	list<OptionType_t>::const_iterator iOption = m_OptionType.begin();
    for (; iOption!= m_OptionType.end(); iOption++) 
	{
		OptionType_t optionType = *iOption;
		oStream.write( optionType );
	}

	oStream.write( m_Durability );
	oStream.write( m_Silver );
	oStream.write( m_Grade );
	oStream.write( m_EnchantLevel );
	oStream.write( m_ItemNum );
	oStream.write( m_MainColor );
	oStream.write( m_ListNum );

	list<SubItemInfo*>::const_iterator itr = m_SubItemInfoList.begin();
    for (; itr!= m_SubItemInfoList.end(); itr++) 
		(*itr)->write(oStream);

	//cout << toString().c_str() << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// debug string
//////////////////////////////////////////////////////////////////////////////
string PCItemInfo::toString() const
	throw()
{
	StringStream msg;
	msg << "PCItemInfo("
		<< "ObjectID:" << (int)m_ObjectID
		<< "ItemClass:" << (int)m_IClass
		<< "ItemType:" << (int)m_ItemType
		<< "OptionTypeSize:" << (int)m_OptionType.size()
		<< "Durability:" << (int)m_Durability
		<< "Silver:" << (int)m_Silver
		<< "Grade:" << (int)m_Grade
		<< "EnchantLevel:" << (int)m_EnchantLevel
		<< "ItemNum:" << (int)m_ItemNum
		<< "MainColor:" << (int)m_MainColor
		<< "ListNum:" << (int)m_ListNum
		<< ")";
	return msg.toString();
}
