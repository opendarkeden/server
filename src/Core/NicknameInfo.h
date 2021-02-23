#ifndef __NICKNAME_INFO_H__
#define __NICKNAME_INFO_H__

#include "Types.h"
#include "Packet.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#include <string>

#define MAX_NICKNAME_SIZE	22

class NicknameInfo
{
public:
	enum
	{
		NICK_NONE = 0,		// 닉네임 없음
		NICK_BUILT_IN,		// 일반적으로 자동으로 주어지는 닉네임 (인덱스)
		NICK_QUEST,			// 퀘스트 클리어한 뒤 받는 닉네임 (인덱스)
		NICK_FORCED,		// 강제로 붙여진 닉네임 (인덱스)
		NICK_CUSTOM_FORCED,	// 강제로 붙여진 닉네임 (스트링)
		NICK_CUSTOM,		// 유저가 자유롭게 넣은 닉네임 (스트링)
	};

	PacketSize_t		getSize() const;
	static PacketSize_t	getMaxSize() { return szWORD + szBYTE + szBYTE + MAX_NICKNAME_SIZE; }

	void read(SocketInputStream& iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	WORD	getNicknameID() const { return m_NicknameID; }
	BYTE	getNicknameType() const { return m_NicknameType; }
	string	getNickname() const { return m_Nickname; }
	WORD	getNicknameIndex() const { return m_NicknameIndex; }

	void	setNicknameID( WORD id ) { m_NicknameID = id; }
	void	setNicknameType( BYTE type ) { m_NicknameType = type; }
	void	setNickname( const string& name ) { m_Nickname = name; }
	void	setNicknameIndex( WORD index ) { m_NicknameIndex = index; }

private:
	WORD	m_NicknameID;
	BYTE	m_NicknameType;
	string	m_Nickname;
	WORD	m_NicknameIndex;	// 스트링 또는 인덱스 하나만 사용된다.
};

#endif
