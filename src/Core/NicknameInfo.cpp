#include "NicknameInfo.h"
#include "Assert.h"

PacketSize_t NicknameInfo::getSize() const
{
	switch ( m_NicknameType )
	{
		case NICK_NONE:
			return szWORD + szBYTE;
		case NICK_BUILT_IN:
		case NICK_QUEST:
		case NICK_FORCED:
			return szWORD + szBYTE + szWORD;
		case NICK_CUSTOM_FORCED:
		case NICK_CUSTOM:
			return szWORD + szBYTE + szBYTE + m_Nickname.size();
		default:
			Assert(false);
	}

	return 0;
}

void NicknameInfo::read(SocketInputStream& iStream)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	iStream.read( m_NicknameID );
	iStream.read( m_NicknameType );

	switch ( m_NicknameType )
	{
		case NICK_NONE:
			{
				break;
			}
		case NICK_BUILT_IN:
		case NICK_QUEST:
		case NICK_FORCED:
			{
				iStream.read( m_NicknameIndex );
				break;
			}
		case NICK_CUSTOM_FORCED:
		case NICK_CUSTOM:
			{
				BYTE szSTR;
				iStream.read( szSTR );
				iStream.read( m_Nickname, szSTR );
				break;
			}
		default:
			Assert(false);
	}

	__END_CATCH
}

void NicknameInfo::write(SocketOutputStream& oStream) const
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	oStream.write( m_NicknameID );
	oStream.write( m_NicknameType );

	switch ( m_NicknameType )
	{
		case NICK_NONE:
			{
				break;
			}
		case NICK_BUILT_IN:
		case NICK_QUEST:
		case NICK_FORCED:
			{
				oStream.write( m_NicknameIndex );
				break;
			}
		case NICK_CUSTOM_FORCED:
		case NICK_CUSTOM:
			{
				BYTE szSTR = m_Nickname.size();
				oStream.write( szSTR );
				oStream.write( m_Nickname );
				break;
			}
		default:
			Assert(false);
	}

	__END_CATCH
}
