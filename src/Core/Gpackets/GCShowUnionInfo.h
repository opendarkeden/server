
//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowUnionInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_UNION_INFO_H__
#define __GC_SHOW_UNION_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////
//
// class GCShowUnionInfo;
//
// 클라이언트에 길드 등록 창을 띄우도록 한다.
//
//////////////////////////////////////////////////////////////////////

struct SingleGuildInfo
{
	// get packet's body size
	PacketSize_t getSize() const throw()
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// Guild Name length
			   m_GuildName.size() +		// Guild Name
			   szGuildState +			// Guild State
			   szBYTE +					// Guild Master length
			   m_GuildMaster.size() +	// Guild Master
			   szBYTE +					// Guild Member Count
			   szBYTE +					// Guild Intro length
			   m_GuildIntro.size() +	// Guild Intro
			   szGold;					// Guild Join Fee
	}

	static PacketSize_t getMaxSize() throw()
	{
		return szGuildID +		// Guild ID
			   szBYTE +			// Guild Name length
			   30 +				// Guild Name
			   szGuildState +	// Guild State
			   szBYTE +			// Guild Master length
			   20 +				// Guild Master
			   szBYTE +			// Guild Member Count
			   szBYTE +			// Guild Intro length
			   256 +			// Guild Intro
			   szGold;			// Guild Join Fee
	}

    void read(SocketInputStream & iStream) throw(ProtocolException, Error)
	{
		__BEGIN_TRY

		BYTE szGuildName, szGuildMaster, szGuildIntro;

		iStream.read( m_GuildID );
		iStream.read( szGuildName );

		if ( szGuildName == 0 )
			throw InvalidProtocolException( "szGuildName == 0" );
		if ( szGuildName > 30 )
			throw InvalidProtocolException( "too long szGuildName length" );

		iStream.read( m_GuildName, szGuildName );
		iStream.read( m_GuildState );
		iStream.read( szGuildMaster );

		if ( szGuildMaster == 0 )
			throw InvalidProtocolException( "szGuildMaster == 0" );
		if ( szGuildMaster > 20 )
			throw InvalidProtocolException( "too long szGuildMaster length" );

		iStream.read( m_GuildMaster, szGuildMaster );
		iStream.read( m_GuildMemberCount );
		iStream.read( szGuildIntro );

		if ( szGuildIntro > 256 )
			throw InvalidProtocolException( "too long szGuildIntro length" );

		if ( szGuildIntro != 0 )
			iStream.read( m_GuildIntro, szGuildIntro );
		else
			m_GuildIntro = "";

		iStream.read( m_JoinFee );

		__END_CATCH
	}
		    
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error)
	{
		__BEGIN_TRY
			
		BYTE szGuildName = m_GuildName.size();
		BYTE szGuildMaster = m_GuildMaster.size();
		BYTE szGuildIntro = m_GuildIntro.size();

		if ( szGuildName == 0 )
			throw InvalidProtocolException( "szGuildName == 0" );
		if ( szGuildName > 30 )
			throw InvalidProtocolException( "too long szGuildName length" );

		if ( szGuildMaster == 0 )
			throw InvalidProtocolException( "szGuildMaster == 0" );
		if ( szGuildMaster > 20 )
			throw InvalidProtocolException( "too long szGuildMaster length" );

		if ( szGuildIntro > 256 )
			throw InvalidProtocolException( "too long szGuildIntro length" );

		oStream.write( m_GuildID );
		oStream.write( szGuildName );
		oStream.write( m_GuildName );
		oStream.write( m_GuildState );
		oStream.write( szGuildMaster );
		oStream.write( m_GuildMaster );
		oStream.write( m_GuildMemberCount );
		oStream.write( szGuildIntro );

		if ( szGuildIntro != 0 )
			oStream.write( m_GuildIntro );

		oStream.write( m_JoinFee );

		__END_CATCH
	}

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Guild Name
	const string& getGuildName() const throw() { return m_GuildName; }
	void setGuildName( const string& GuildName ) throw() { m_GuildName = GuildName; }

	// get/set Guild State
	GuildState_t getGuildState() const throw() { return m_GuildState; }
	void setGuildState( GuildState_t GuildState ) throw() { m_GuildState = GuildState; }

	// get/set Guild Master
	const string& getGuildMaster() const throw() { return m_GuildMaster; }
	void setGuildMaster( const string& GuildMaster ) throw() { m_GuildMaster = GuildMaster; }

	// get/set Guild Member Count
	BYTE getGuildMemberCount() const throw() { return m_GuildMemberCount; }
	void setGuildMemberCount( BYTE GuildMemberCount ) throw() { m_GuildMemberCount = GuildMemberCount; }

	// get/set Guild Intro
	const string& getGuildIntro() const throw() { return m_GuildIntro; }
	void setGuildIntro( const string& GuildIntro ) throw() { m_GuildIntro = GuildIntro; }

	// get/set Guild Join Fee
	Gold_t getJoinFee() const throw() { return m_JoinFee; }
	void setJoinFee( Gold_t JoinFee ) throw() { m_JoinFee = JoinFee; }
	

private :
	
	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	string m_GuildName;

	// Guild State
	GuildState_t m_GuildState;

	// Guild Master
	string m_GuildMaster;

	// Guild Member Count
	BYTE m_GuildMemberCount;

	// Guild Intro
	string m_GuildIntro;
	
	// Guild Join Fee
	Gold_t m_JoinFee;
};

class GCShowUnionInfo : public Packet {

public :

    ~GCShowUnionInfo() throw();

	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOW_UNION_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();

	// get packet name
	string getPacketName() const throw() { return "GCShowUnionInfo"; }
	
	// get packet's debug string
	string toString() const throw();

	SingleGuildInfo&	getMasterGuildInfo()	throw()	{ return m_MasterGuildInfo; }

	void	addGuildInfoList(SingleGuildInfo* pGuildInfo) throw()
	{
		m_GuildList.push_back(pGuildInfo);
	}

private :
	SingleGuildInfo	m_MasterGuildInfo;
	list<SingleGuildInfo*>	m_GuildList;
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowUnionInfoFactory;
//
// Factory for GCShowUnionInfo
//
//////////////////////////////////////////////////////////////////////

class GCShowUnionInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShowUnionInfo(); }

	// get packet name
	string getPacketName() const throw() { return "GCShowUnionInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOW_UNION_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return SingleGuildInfo::getMaxSize() * 4; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowUnionInfo;
//
//////////////////////////////////////////////////////////////////////

class GCShowUnionInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowUnionInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
