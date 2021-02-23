//////////////////////////////////////////////////////////////////////////////
// Filename    : PCVampireInfo2.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PCVampireInfo2.h"

//////////////////////////////////////////////////////////////////////////////
// read data from socket input stream
//////////////////////////////////////////////////////////////////////////////
void PCVampireInfo2::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read object id
	//--------------------------------------------------
	iStream.read( m_ObjectID );

	//--------------------------------------------------
	// read vampire name
	//--------------------------------------------------
	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	iStream.read( m_Name , szName );

	//--------------------------------------------------
	// read Level
	//--------------------------------------------------
	iStream.read( m_Level );

	//--------------------------------------------------
	// read sex
	//--------------------------------------------------
	BYTE sex;
	iStream.read( sex );
	m_Sex = Sex(sex);

	//--------------------------------------------------
	// read colors
	//--------------------------------------------------
	iStream.read( m_BatColor );
	iStream.read( m_SkinColor );
	iStream.read( m_MasterEffectColor );

    //--------------------------------------------------
	// read Alignment
	//--------------------------------------------------
	iStream.read( m_Alignment );
    //--------------------------------------------------
	// read attributes
	//--------------------------------------------------
	iStream.read( m_STR[ATTR_CURRENT] );
	iStream.read( m_STR[ATTR_MAX] );
	iStream.read( m_STR[ATTR_BASIC] );
	iStream.read( m_DEX[ATTR_CURRENT] );
	iStream.read( m_DEX[ATTR_MAX] );
	iStream.read( m_DEX[ATTR_BASIC] );
	iStream.read( m_INT[ATTR_CURRENT] );
	iStream.read( m_INT[ATTR_MAX] );
	iStream.read( m_INT[ATTR_BASIC] );

	//--------------------------------------------------
	// read hp
	//--------------------------------------------------
	iStream.read( m_HP[ATTR_CURRENT] );
	iStream.read( m_HP[ATTR_MAX] );
	
	//--------------------------------------------------
	// read misc
	//--------------------------------------------------
	iStream.read( m_Rank );
	iStream.read( m_RankExp );

	iStream.read( m_Exp );
	iStream.read( m_Gold );


	//--------------------------------------------------
	// read fame&notoriety 
	//--------------------------------------------------
	iStream.read( m_Fame );

	//--------------------------------------------------
	// read sight
	//--------------------------------------------------
	iStream.read( m_Sight );

	//--------------------------------------------------
	// read sight
	//--------------------------------------------------
	iStream.read( m_Bonus );

	//--------------------------------------------------
	// read HotKey
	//--------------------------------------------------
	for( int i = 0 ; i < 8 ; i++ ) {
		iStream.read( m_HotKey[i] );
	}

	// 은도금 데미쥐
	iStream.read( m_SilverDamage );

	// 권한
	iStream.read( m_Competence );

	// 길드 아이디
	iStream.read( m_GuildID );

	BYTE szGuildName;

	iStream.read( szGuildName );

	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long szGuildName size" );

	if ( szGuildName != 0 )
		iStream.read( m_GuildName, szGuildName );

	iStream.read( m_GuildMemberRank );
	iStream.read( m_UnionID );
	iStream.read( m_AdvancementLevel );
	iStream.read( m_AdvancementGoalExp );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// write data to socket output stream
//////////////////////////////////////////////////////////////////////////////
void PCVampireInfo2::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write object id
	//--------------------------------------------------
	oStream.write( m_ObjectID );

	//--------------------------------------------------
	// write vampire name
	//--------------------------------------------------
	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	oStream.write( szName );

	oStream.write( m_Name );

	//--------------------------------------------------
	// write sex
	//--------------------------------------------------
	oStream.write( m_Level );

	//--------------------------------------------------
	// write sex
	//--------------------------------------------------
	oStream.write( (BYTE)m_Sex );

	//--------------------------------------------------
	// write colors
	//--------------------------------------------------
	oStream.write( m_BatColor );
	oStream.write( m_SkinColor );
	oStream.write( m_MasterEffectColor );

    //--------------------------------------------------
	// write Alignment
	//--------------------------------------------------
	oStream.write( m_Alignment);

    //--------------------------------------------------
	// write attributes
	//--------------------------------------------------
	oStream.write( m_STR[ATTR_CURRENT] );
	oStream.write( m_STR[ATTR_MAX] );
	oStream.write( m_STR[ATTR_BASIC] );
	oStream.write( m_DEX[ATTR_CURRENT] );
	oStream.write( m_DEX[ATTR_MAX] );
	oStream.write( m_DEX[ATTR_BASIC] );
	oStream.write( m_INT[ATTR_CURRENT] );
	oStream.write( m_INT[ATTR_MAX] );
	oStream.write( m_INT[ATTR_BASIC] );

	//--------------------------------------------------
	// write hp
	//--------------------------------------------------
	oStream.write( m_HP[ATTR_CURRENT] );
	oStream.write( m_HP[ATTR_MAX] );
	
	//--------------------------------------------------
	// write misc
	//--------------------------------------------------
	oStream.write( m_Rank );
	oStream.write( m_RankExp );

	oStream.write( m_Exp );
	oStream.write( m_Gold );

	//--------------------------------------------------
	// read fame&notoriety 
	//--------------------------------------------------
	oStream.write( m_Fame );
	
	//--------------------------------------------------
	// write sight
	//--------------------------------------------------
	oStream.write( m_Sight );

	//--------------------------------------------------
	// write Bonus
	//--------------------------------------------------
	oStream.write( m_Bonus );

	//--------------------------------------------------
	// write HotKey
	//--------------------------------------------------
	for( int i = 0; i < 8; i++ ) {
		oStream.write( m_HotKey[i] );
	}

	// 은도금 데미지
	oStream.write( m_SilverDamage );

	// 권한
	oStream.write( m_Competence );

	// 길드 아이디
	oStream.write( m_GuildID );

	BYTE szGuildName = m_GuildName.size();

	if ( szGuildName > 30 )
		throw InvalidProtocolException( "too long guild name length" );

	oStream.write( szGuildName );
	if ( szGuildName != 0 )
		oStream.write( m_GuildName );

	oStream.write( m_GuildMemberRank );
	oStream.write( m_UnionID );
	oStream.write( m_AdvancementLevel );
	oStream.write( m_AdvancementGoalExp );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string PCVampireInfo2::toString () const 
	throw ()
{
	StringStream msg;

	msg << "PCVampireInfo2("
		<< "ObjectID:" << m_ObjectID
		<< ",Name:" << m_Name
		<< ",Level:" << m_Level
		<< ",Sex:" << Sex2String[m_Sex]
		<< ",BatColor:" << (int)m_BatColor
		<< ",SkinColor:" << (int)m_SkinColor
		<< ",MasterEffectColor:" << (int)m_MasterEffectColor
		<< ",Alignment:" << (int)m_Alignment
        << ",STR[CURRENT]:" << (int)m_STR[ATTR_CURRENT]
		<< ",STR[MAX]:" << (int)m_STR[ATTR_MAX]
		<< ",STR[BASIC]:" << (int)m_STR[ATTR_BASIC]
		<< ",DEX[CURRENT]:" << (int)m_DEX[ATTR_CURRENT]
		<< ",DEX[MAX]:" << (int)m_DEX[ATTR_MAX]
		<< ",DEX[BASIC]:" << (int)m_DEX[ATTR_BASIC]
		<< ",INT[CURRENT]:" << (int)m_INT[ATTR_CURRENT]
		<< ",INT[MAX]:" << (int)m_INT[ATTR_MAX]
		<< ",INT[BASIC]:" << (int)m_INT[ATTR_BASIC]
		<< ",HP:" << m_HP[ATTR_CURRENT] << "/" << m_HP[ATTR_MAX]
		<< ",Rank:" << (int)m_Rank
		<< ",RankExp:" << (int)m_RankExp
		<< ",Exp:" << m_Exp
		<< ",Gold:" << m_Gold
		<< ",Fame:" << m_Fame
		<< ",Sight:" << (int)m_Sight
		<< ",Bonus:" << (int)m_Bonus
		<< ",F5:" << (int)m_HotKey[0]
		<< ",F6:" << (int)m_HotKey[1]
		<< ",F7:" << (int)m_HotKey[2]
		<< ",F8:" << (int)m_HotKey[3]
		<< ",F9:" << (int)m_HotKey[4]
		<< ",F10:" << (int)m_HotKey[5]
		<< ",F11:" << (int)m_HotKey[6]
		<< ",F12:" << (int)m_HotKey[7]
		<< ",SilverDamage:" << (int)m_SilverDamage
		<< ",Competence:" << (int)m_Competence
		<< ",GuildID:" << (int)m_GuildID
		<< ",GuildName:" << m_GuildName
		<< ",GuildMemberRank:" << (int)m_GuildMemberRank
		<< ")";

	return msg.toString();
}
