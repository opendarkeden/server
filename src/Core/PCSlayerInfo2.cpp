//////////////////////////////////////////////////////////////////////////////
// Filename    : PCSlayerInfo2.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "PCSlayerInfo2.h"

//////////////////////////////////////////////////////////////////////////////
// read data from socket input stream
//////////////////////////////////////////////////////////////////////////////
void PCSlayerInfo2::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try 
	{
		// read object id
		iStream.read( m_ObjectID );

		// read slayer name
		BYTE szName;

		iStream.read( szName );

		if ( szName == 0 )
			throw InvalidProtocolException("szName == 0");

		if ( szName > 20 )
			throw InvalidProtocolException("too long name length");

		iStream.read( m_Name , szName );

		// read sex
		BYTE sex;
		iStream.read( sex );
		m_Sex = Sex(sex);

		// read hair style
		BYTE hairStyle;
		iStream.read( hairStyle );
		m_HairStyle = HairStyle(hairStyle);

		// read colors
		iStream.read( m_HairColor );
		iStream.read( m_SkinColor );
		iStream.read( m_MasterEffectColor );

		// read Alignment
		iStream.read( m_Alignment );
		
		// read attributes
		iStream.read( m_STR[ATTR_CURRENT] );
		iStream.read( m_STR[ATTR_MAX] );
		iStream.read( m_STR[ATTR_BASIC] );
		iStream.read( m_DEX[ATTR_CURRENT] );
		iStream.read( m_DEX[ATTR_MAX] );
		iStream.read( m_DEX[ATTR_BASIC] );
		iStream.read( m_INT[ATTR_CURRENT] );
		iStream.read( m_INT[ATTR_MAX] );
		iStream.read( m_INT[ATTR_BASIC] );
		
		iStream.read( m_Rank );
		iStream.read( m_RankExp );

		// read attributes Exp
		iStream.read( m_STRExp );
		iStream.read( m_DEXExp );
		iStream.read( m_INTExp );

		// read hp/mp
		iStream.read( m_HP[ATTR_CURRENT] );
		iStream.read( m_HP[ATTR_MAX] );
		iStream.read( m_MP[ATTR_CURRENT] );
		iStream.read( m_MP[ATTR_MAX] );

		// read misc
		iStream.read( m_Fame );
		iStream.read( m_Gold );

		// read skills
		for ( uint i = 0 ; i < SKILL_DOMAIN_VAMPIRE ; i ++ ) {
			iStream.read( m_DomainLevels[i] );
			iStream.read( m_DomainExps[i] );
		}

		// read sight
		iStream.read( m_Sight );

		// read sight
		for( int i = 0 ; i < 4 ; i++ ) 
		{
			iStream.read( m_HotKey[i] );
		}

		// read competence
		iStream.read( m_Competence );
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
		iStream.read( m_AttrBonus );
	} 
	catch ( Throwable & t ) 
	{
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// write data to socket output stream
//////////////////////////////////////////////////////////////////////////////
void PCSlayerInfo2::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try 
	{
		// write object id
		oStream.write( m_ObjectID );

		// write slayer name
		BYTE szName = m_Name.size();

		if ( szName == 0 )
			throw InvalidProtocolException("szName == 0");

		if ( szName > 20 )
			throw InvalidProtocolException("too long name length");

		oStream.write( szName );
		oStream.write( m_Name );

		// write sex
		oStream.write( (BYTE)m_Sex );

		// write hair style
		oStream.write( (BYTE)m_HairStyle );

		// write colors
		oStream.write( m_HairColor );
		oStream.write( m_SkinColor );
		oStream.write( m_MasterEffectColor );

		// write Alignment
		oStream.write( m_Alignment );
		
		// write attributes
		// 넣는 순서는 ATTR_CURRENT, ATTR_MAX, ATTR_BASIC
		oStream.write( m_STR[ATTR_CURRENT] );
		oStream.write( m_STR[ATTR_MAX] );
		oStream.write( m_STR[ATTR_BASIC] );
		oStream.write( m_DEX[ATTR_CURRENT] );
		oStream.write( m_DEX[ATTR_MAX] );
		oStream.write( m_DEX[ATTR_BASIC] );
		oStream.write( m_INT[ATTR_CURRENT] );
		oStream.write( m_INT[ATTR_MAX] );
		oStream.write( m_INT[ATTR_BASIC] );
		
		oStream.write( m_Rank );
		oStream.write( m_RankExp );

//		cout << m_RankExp << endl;

		// write attributes
		oStream.write( m_STRExp );
		oStream.write( m_DEXExp );
		oStream.write( m_INTExp );

		// write hp/mp
		oStream.write( m_HP[ATTR_CURRENT] );
		oStream.write( m_HP[ATTR_MAX] );
		oStream.write( m_MP[ATTR_CURRENT] );
		oStream.write( m_MP[ATTR_MAX] );

		// write misc
		oStream.write( m_Fame );
		oStream.write( m_Gold );

		// write skills
		for ( uint i = 0 ; i < SKILL_DOMAIN_VAMPIRE ; i ++ ) {
			oStream.write( m_DomainLevels[i] );
			oStream.write( m_DomainExps[i] );
		}

		// write sight
		oStream.write( m_Sight );

		// write HotKey
		for( int i = 0; i < 4; i++ ) 
		{
			oStream.write( m_HotKey[i] );
		}

		// write competence
		oStream.write( m_Competence );
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
		oStream.write( m_AttrBonus );
	} 
	catch ( Throwable & t ) 
	{
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string PCSlayerInfo2::toString () const 
	throw ()
{
	StringStream msg;

	msg << "PCSlayerInfo2("
		<< "ObjectID:" << m_ObjectID
		<< ",Name:" << m_Name
		<< ",Sex:" << Sex2String[m_Sex]
		<< ",HairStyle:" << HairStyle2String[m_HairStyle]
		<< ",HairColor:" << (int)m_HairColor
		<< ",SkinColor:" << (int)m_SkinColor
		<< ",MasterEffectColor:" << (int)m_MasterEffectColor
		<< ",Alignment:" << m_Alignment
		<< ",Rank:" << (int)m_Rank
		<< ",RankExp:" << (int)m_RankExp
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
		<< ",MP:" << m_MP[ATTR_CURRENT] << "/" << m_MP[ATTR_MAX]
		<< ",Fame:" << m_Fame
		<< ",Gold:" << m_Gold;
		
	for(uint i=0;i<SKILL_DOMAIN_VAMPIRE;i++)
		msg << "," << SkillDomain2String[i] << ":" 
			<< (int)m_DomainLevels[i] << "/" << m_DomainExps[i];

	msg << ",Sight:" << (int)m_Sight
		<< ",F9:" << (int)m_HotKey[0]
		<< ",F10:" << (int)m_HotKey[1]
		<< ",F11:" << (int)m_HotKey[2]
		<< ",F12:" << (int)m_HotKey[3]
		<< ",Competence:" << (int)m_Competence
		<< ",GuildID:" << (int)m_GuildID
		<< ",AttrBonus:" << (int)m_AttrBonus
		<< ")";
	
	return msg.toString();
}
