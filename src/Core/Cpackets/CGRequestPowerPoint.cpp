//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestPowerPoint.cpp 
// Written By  :
// Description :
// 서버에 원하는 사람의 IP 요청
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestPowerPoint.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPoint member methods
//////////////////////////////////////////////////////////////////////////////

CGRequestPowerPoint::CGRequestPowerPoint () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}
	
CGRequestPowerPoint::~CGRequestPowerPoint () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGRequestPowerPoint::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE szCellNum;
	iStream.read( szCellNum );

	if ( szCellNum == 0 )
		throw InvalidProtocolException( "szCellNum == 0" );

	if ( szCellNum > 12 )
		throw InvalidProtocolException( "szCellNum > 12" );

	iStream.read( m_CellNum, szCellNum );

	__END_CATCH
}
		    
void CGRequestPowerPoint::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szCellNum = m_CellNum.size();

	if ( szCellNum == 0 )
		throw InvalidProtocolException( "szCellNum == 0" );

	if ( szCellNum > 12 )
		throw InvalidProtocolException( "szCellNum > 12" );

	oStream.write( szCellNum );
	oStream.write( m_CellNum );

	__END_CATCH
}

void CGRequestPowerPoint::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CGRequestPowerPointHandler::execute( this , pPlayer );
		
	__END_CATCH
}

string CGRequestPowerPoint::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGRequestPowerPoint( "
		<< ",CellNum: " << m_CellNum
		<< ")";
	return msg.toString();

	__END_CATCH
}
