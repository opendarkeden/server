
//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUnionOfferList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNION_OFFER_LIST_H__
#define __GC_UNION_OFFER_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////
//
// class GCUnionOfferList;
//
// 클라이언트에게 연합을 신청한 길드 리스트를 만들어서 보내준다.
//
//////////////////////////////////////////////////////////////////////


class SingleGuildUnionOffer
{
public:
    enum OfferType
    {
        JOIN,
        QUIT
    };

	PacketSize_t getSize() const throw()
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// Guild Type
			   szBYTE +					// Guild Name length
			   m_GuildName.size() +		// Guild Name
			   szBYTE +					// Guild Master length
			   m_MasterName.size() + 	// Guild Master
			   szDWORD;			// Date
	}

	static PacketSize_t getMaxSize() throw()
	{
		return szGuildID +		// Guild ID
			   szBYTE +			// Guild Type
			   szBYTE +			// Guild Name length
			   30 +				// Guild Name
			   szBYTE +			// Guild Master length
			   20 +				// Guild Master
			   szDWORD;			// Date
	}

    void read(SocketInputStream & iStream) throw(ProtocolException, Error)
	{
		__BEGIN_TRY

		BYTE szGuildName, szGuildMaster;

		iStream.read( m_GuildID );
		iStream.read( m_Type );
		iStream.read( szGuildName );
	
		if ( szGuildName == 0 )
			throw InvalidProtocolException( "szGuildName == 0" );
		if ( szGuildName > 30 )
			throw InvalidProtocolException( "too long szGuildName length" );

		iStream.read( m_GuildName, szGuildName );
		iStream.read( szGuildMaster );

		if ( szGuildMaster == 0 )
			throw InvalidProtocolException( "szGuildMaster == 0" );
		if ( szGuildMaster > 20 )
			throw InvalidProtocolException( "too long szGuildMaster length" );

		iStream.read( m_MasterName, szGuildMaster );

		iStream.read( m_Date );

		__END_CATCH
	}
		    
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error)
	{
		__BEGIN_TRY
			
		BYTE szGuildName = m_GuildName.size();
		BYTE szGuildMaster = m_MasterName.size();

		if ( szGuildName == 0 )
			throw InvalidProtocolException( "szGuildName == 0" );
		if ( szGuildName > 30 )
			throw InvalidProtocolException( "too long szGuildName length" );

		if ( szGuildMaster == 0 )
			throw InvalidProtocolException( "szGuildMaster == 0" );
		if ( szGuildMaster > 20 )
			throw InvalidProtocolException( "too long szGuildMaster length" );

		oStream.write( m_GuildID );
		oStream.write( m_Type);
		oStream.write( szGuildName );
		oStream.write( m_GuildName );
		oStream.write( szGuildMaster );
		oStream.write( m_MasterName);

		oStream.write( m_Date );

		__END_CATCH
	}

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set OfferGuild Type (JOIN-신청자 목록, QUIT-탈퇴신청한 길드)
	BYTE	getGuildType()	const throw() { return m_Type; }
	void	setGuildType( BYTE Type ) throw() { m_Type = Type; }

	// get/set Guild Name
	const string& getGuildName() const throw() { return m_GuildName; }
	void setGuildName( const string& GuildName ) throw() { m_GuildName = GuildName; }

	// get/set Guild Master
	const string& getGuildMaster() const throw() { return m_MasterName; }
	void setGuildMaster( const string& GuildMaster ) throw() { m_MasterName = GuildMaster; }

	// get/set Date
	const DWORD getDate() const throw() { return m_Date; }
	void setDate( DWORD date  ) throw() { m_Date = date; }

private :

    BYTE    	m_Type;
    GuildID_t   m_GuildID;
    string      m_GuildName;
    string      m_MasterName;
	DWORD		m_Date;

};


class GCUnionOfferList : public Packet {

public :

    ~GCUnionOfferList() throw();

	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_UNION_OFFER_LIST;}
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();

	// get packet name
	string getPacketName() const throw() { return "GCUnionOfferList"; }
	
	// get packet's debug string
	string toString() const throw();

	list<SingleGuildUnionOffer*>	getUnionOfferList() const throw() { return m_UnionOfferList; }
	
	void	addUnionOfferList(SingleGuildUnionOffer* pUnionOffer) throw()
	{
		m_UnionOfferList.push_back(pUnionOffer);
	}
	
private :
	list<SingleGuildUnionOffer*>	m_UnionOfferList;
};


//////////////////////////////////////////////////////////////////////
//
// class GCUnionOfferListFactory;
//
// Factory for GCUnionOfferList
//
//////////////////////////////////////////////////////////////////////

class GCUnionOfferListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUnionOfferList(); }

	// get packet name
	string getPacketName() const throw() { return "GCUnionOfferList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_UNION_OFFER_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return SingleGuildUnionOffer::getMaxSize() * 20; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUnionOfferList;
//
//////////////////////////////////////////////////////////////////////

class GCUnionOfferListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCUnionOfferList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
