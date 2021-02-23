//////////////////////////////////////////////////////////////////////
// 
// Filename	: GCNicknameList.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//			   멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCNicknameList.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCNicknameList::GCNicknameList () 
	 throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCNicknameList::~GCNicknameList () 
	throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCNicknameList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_Nicknames.clear();

	BYTE Num;
	iStream.read(Num);

	for ( int i=0; i<Num; ++i )
	{
		NicknameInfo* pUnit = new NicknameInfo;
		pUnit->read(iStream);
		m_Nicknames.push_back( pUnit );
	}
		
	__END_CATCH
}

			
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCNicknameList::write ( SocketOutputStream & oStream ) 
	 const throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE Num = m_Nicknames.size();
	oStream.write(Num);

	vector<NicknameInfo*>::const_iterator itr = m_Nicknames.begin();
	vector<NicknameInfo*>::const_iterator endItr = m_Nicknames.end();

	for ( ; itr != endItr; ++itr )
	{
		(*itr)->write(oStream);
	}
		
	__END_CATCH
}

PacketSize_t GCNicknameList::getPacketSize() const throw()
{
	__BEGIN_TRY

	PacketSize_t ret = szBYTE;

	vector<NicknameInfo*>::const_iterator itr = m_Nicknames.begin();
	vector<NicknameInfo*>::const_iterator endItr = m_Nicknames.end();

	for ( ; itr != endItr; ++itr )
	{
		ret += (*itr)->getSize();
	}

	return ret;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCNicknameList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCNicknameListHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCNicknameList::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCNicknameList("
		<< ")";
	return msg.toString();

	__END_CATCH
}

