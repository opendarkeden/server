////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketHeader.cpp
//
////////////////////////////////////////////////////////////////////////

// include files
#include "CBillingPacketHeader.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Properties.h"

CBillingPacketHeader::CBillingPacketHeader()
	throw ()
{
	__BEGIN_TRY

	memset( this, 0, szCBillingPacketHeaderInfo );

	static int versionno = g_pConfig->getPropertyInt( "ChinaBillingVersionNumber" );

	Version_No = versionno;

	__END_CATCH
}

void CBillingPacketHeader::read( SocketInputStream& iStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY
	
	CBillingPacketHeaderInfo* pInfo = this;

	iStream.read( (char*)pInfo, szCBillingPacketHeaderInfo );

	// change order network to host
	Version_No	= ntohl( Version_No );
	Packet_Type	= ntohl( Packet_Type );
	Method_Code	= ntohl( Method_Code );
	Return_Code	= ntohl( Return_Code );
	Body_Length	= ntohl( Body_Length );

	__END_CATCH
}

void CBillingPacketHeader::write( SocketOutputStream& oStream )
	throw ( ProtocolException, Error )
{
	__BEGIN_TRY

	// change order host to network
	Version_No	= htonl( Version_No );
	Packet_Type	= htonl( Packet_Type );
	Method_Code	= htonl( Method_Code );
	Return_Code	= htonl( Return_Code );
	Body_Length	= htonl( Body_Length );

	const CBillingPacketHeaderInfo* pInfo = this;
	oStream.write( (const char*)pInfo, szCBillingPacketHeaderInfo );

	// restore order
	Version_No	= ntohl( Version_No );
	Packet_Type	= ntohl( Packet_Type );
	Method_Code	= ntohl( Method_Code );
	Return_Code	= ntohl( Return_Code );
	Body_Length	= ntohl( Body_Length );

	__END_CATCH
}

string CBillingPacketHeader::toString() const
	throw ()
{
	StringStream msg;
	msg << "Header("
		<< "Version_No:" << Version_No 
		<< ",Packet_Type:" << Packet_Type
		<< ",Method_Code:" << Method_Code
		<< ",Return_Code:" << Return_Code
		<< ",Session_ID:" << Session_ID
		<< ",Body_Length:" << Body_Length
		<< ")";

	return msg.toString();
}

