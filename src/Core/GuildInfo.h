//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildInfo.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_INFO_H__
#define __GUILD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class GuildInfo;
//
// Ŭ���̾�Ʈ�� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GuildInfo {

public :
	
	// constructor
	GuildInfo () ;
	
	// destructor
	~GuildInfo () noexcept;

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () ;

	static uint getMaxSize()  {
//		return ( szGuildID + szBYTE + 30 + szBYTE + 20 + szBYTE + szBYTE + 11 ) * 256 + szBYTE;
		return szGuildID + szBYTE + 30 + szBYTE + 20 + szBYTE + szBYTE + 11;
	}

	// get packet's debug string
	string toString () const ;

	// get/set GuildID
	GuildID_t getGuildID() const  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID )  { m_GuildID = GuildID; }

	// get/set Guild Name
	string getGuildName() const  { return m_GuildName; }
	void setGuildName( const string& GuildName )  { m_GuildName = GuildName; }

	// get/set Guild Master
	string getGuildMaster() const  { return m_GuildMaster; }
	void setGuildMaster( const string& GuildMaster )  { m_GuildMaster = GuildMaster; }

	// get/set Guild Member Count
	BYTE getGuildMemberCount() const  { return m_GuildMemberCount; }
	void setGuildMemberCount( BYTE GuildMemberCount )  { m_GuildMemberCount = GuildMemberCount; }

	// get/set Guild Expire Date
	string getGuildExpireDate() const  { return m_GuildExpireDate; }
	void setGuildExpireDate( const string& GuildExpireDate )  { m_GuildExpireDate = GuildExpireDate; }


private :

	// ��� ���̵�
	GuildID_t m_GuildID;

	// ��� �̸�
	string m_GuildName;

	// ��� ������
	string m_GuildMaster;

	// ��� ��� ī��Ʈ
	BYTE m_GuildMemberCount;

	// ��� Expire Date
	string m_GuildExpireDate;

};

#endif
