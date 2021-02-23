//////////////////////////////////////////////////////////////////////
// 
// Filename    : SweeperBonusInfo.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SWEEPER_BONUS_INFO_H__
#define __SWEEPER_BONUS_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include <list>

//////////////////////////////////////////////////////////////////////
//
// class SweeperBonusInfo;
//
//////////////////////////////////////////////////////////////////////

typedef list<OptionType_t> OptionTypeList;
typedef OptionTypeList::const_iterator OptionTypeListConstItor;

class SweeperBonusInfo {

public :
	
	// constructor
	SweeperBonusInfo () throw ();
	
	// destructor
	~SweeperBonusInfo () throw ();

public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	PacketSize_t getSize () throw () { return szBYTE; }

	// get packet's max size
	static uint getMaxSize() throw() { return szBYTE; }

	// get packet's debug string
	string toString () const throw ();

	// get/set SweeperBonus Type
	BYTE getType() const { return m_Type; }
	void setType( BYTE type ) { m_Type = type; }

	// get/set Owner Race
	BYTE getRace() const { return m_Race; }
	void setRace( BYTE race ) { m_Race = race; }

	void clearOptionTypeList() { m_OptionTypeList.clear(); }
	void addOptionType( OptionType_t optionType ) { m_OptionTypeList.push_back( optionType ); }
	void setOptionType( const OptionTypeList& optionTypeList ) { m_OptionTypeList = optionTypeList; }
	int getOptionTypeSize() const { return m_OptionTypeList.size(); }
	OptionType_t popOptionType()
	{
		if ( m_OptionTypeList.empty() ) return 0;
		OptionType_t optionType = m_OptionTypeList.front();
		m_OptionTypeList.pop_front();
		return optionType;
	}

private :

	// Sweeper Bonus type
	BYTE m_Type;

	// Owner Race
	BYTE m_Race;

	// Option Type List;
	OptionTypeList m_OptionTypeList;

};

#endif
