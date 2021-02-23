//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFriendChatting.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GCFriendChatting.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void string_replace(string & strBig, const string & strsrc, const string &strdst) {
        string::size_type pos=0;
        string::size_type srclen=strsrc.size();
        string::size_type dstlen=strdst.size();
        while( (pos=strBig.find(strsrc, pos)) != string::npos){
                strBig.replace(pos, srclen, strdst);
                pos += dstlen;
        }
}
GCFriendChatting::GCFriendChatting()
{

	m_Command = 0;
	m_IsBlack = 0;
	m_IsOnLine = 0;
}
void GCFriendChatting::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY  
	//cout<<"read1"<<endl;
	iStream.read( m_Command );

	//cout<<"read2"<<endl;
	BYTE szPlayerName;
	iStream.read( szPlayerName );
	if ( szPlayerName>32 )
		throw InvalidProtocolException("PlayerName Lenth error");
	if(szPlayerName>0)
		iStream.read(m_PlayerName, szPlayerName);

	//cout<<"read3"<<endl;
	WORD szMessage;
	iStream.read( szMessage);
	if ( szMessage > 512 )
		throw InvalidProtocolException("Too large Message length");
	if(szMessage>0)
		iStream.read( m_Message , szMessage );

	//cout<<"read4"<<endl;
	iStream.read(m_IsBlack);
	iStream.read(m_IsOnLine);

	string_replace(m_PlayerName, "'", "");
	string_replace(m_Message, "'", "");
	//if(m_PlayerName.size()>0)
	//	if(m_PlayerName.find('\'')>0 || m_PlayerName.find(' ')>0)
	//		throw InvalidProtocolException("String Filter Finded check by viva");
	//if(m_Message.size()>0)
	//	if(m_Message.find('\'')>0)
	//		throw InvalidProtocolException("String Filter Finded check by viva");

	//cout<<"read5:readend"<<endl;
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCFriendChatting::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_Command );

	BYTE szPlayerName = m_PlayerName.size();
	if(szPlayerName>32)
		throw InvalidProtocolException("Too Large PlayerName Lenth");
	oStream.write(szPlayerName);
	if(szPlayerName>0)
		oStream.write(m_PlayerName);

	WORD szMessage = m_Message.size();
	if(szMessage>512)
		throw InvalidProtocolException("Too Large Message Lenth");
	oStream.write(szMessage);
	if(szMessage>0)
		oStream.write(m_Message);

	oStream.write(m_IsBlack);
	oStream.write(m_IsOnLine);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCFriendChatting::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		 
	GCFriendChattingHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCFriendChatting::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCFriendChatting("
		<< "Command:" << m_Command 
		<< ",PlayerName:" << m_PlayerName
		<< ",Message:" << m_Message 
		<< ",m_IsBlack:"<<m_IsBlack
		<< ",m_IsOnLine:"<<m_IsOnLine
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


