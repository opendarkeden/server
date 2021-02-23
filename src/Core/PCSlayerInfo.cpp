//----------------------------------------------------------------------
//
// Filename    : PCSlayerInfo.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "PCSlayerInfo.h"

//----------------------------------------------------------------------
// set ShapeInfo
//----------------------------------------------------------------------
void 
PCSlayerInfo::setShapeInfo(DWORD flag, Color_t color[SLAYER_COLOR_MAX]) 
	throw()
{
	m_Outlook = bitset<SLAYER_BIT_MAX>(flag);

	//cout << "-----------SET------------" << endl;
	//cout << m_Outlook << endl;

	for ( uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++ )
	{
		m_Colors[i] = color[i];
		//cout << (int)color[i] << endl;
	}
}

//----------------------------------------------------------------------
// read data from socket input stream
//----------------------------------------------------------------------
void PCSlayerInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	try {

	//--------------------------------------------------
	// read slayer name
	//--------------------------------------------------
	BYTE szName;

	iStream.read( szName );

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	iStream.read( m_Name , szName );

	//--------------------------------------------------
	// read slot
	//
	// enum 변수들은 실제 크기와 스트림에 쓰여진 크기가
	// 다른 경우가 대부분이므로, 쓰여진 크기와 같은 변수
	// 를 사용해서 대신 읽어서 다시 enum 으로 변환해서
	// 저장하도록 한다.
	//
	// ex> Slot, Sex, HairStyle ...
	//
	//--------------------------------------------------
	BYTE slot;
	iStream.read( slot );
	m_Slot = Slot(slot);

	//--------------------------------------------------
	// read Alignment
	//--------------------------------------------------
	iStream.read( m_Alignment );

	//--------------------------------------------------
	// read attributes
	//--------------------------------------------------
	iStream.read( m_STR );
	iStream.read( m_DEX );
	iStream.read( m_INT );

	//--------------------------------------------------
	// read attributes Exp
	//--------------------------------------------------
	iStream.read( m_Rank );

	iStream.read( m_STRExp );
	iStream.read( m_DEXExp );
	iStream.read( m_INTExp );

	//--------------------------------------------------
	// read hp/mp
	//--------------------------------------------------
	iStream.read( m_HP[ATTR_CURRENT] );
	iStream.read( m_HP[ATTR_MAX] );
	iStream.read( m_MP[ATTR_CURRENT] );
	iStream.read( m_MP[ATTR_MAX] );

	//--------------------------------------------------
	// read misc
	//--------------------------------------------------
	iStream.read( m_Fame );
//	iStream.read( m_Gold );

	//--------------------------------------------------
	// read skills
	//--------------------------------------------------
	for ( uint i = 0 ; i < SKILL_DOMAIN_VAMPIRE; i ++ ) {
		iStream.read( m_DomainLevels[i] );
	}

	//--------------------------------------------------
	// read zone id
	//--------------------------------------------------
//	iStream.read( m_ZoneID );

	//--------------------------------------------------------------------------------
	// read outlook bitset
	//--------------------------------------------------------------------------------
	DWORD outlook;
	iStream.read( outlook);
	m_Outlook = bitset<SLAYER_BIT_MAX>(outlook);
	
	//--------------------------------------------------------------------------------
	// read colors
	//--------------------------------------------------------------------------------
	for ( uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++ )
		iStream.read( m_Colors[i] );


	} catch( Throwable & t ) {
		cout << t.toString() << endl;
	}

	iStream.read(m_AdvancementLevel);

	__END_CATCH
}

//----------------------------------------------------------------------
// write data to socket output stream
//----------------------------------------------------------------------
void PCSlayerInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	try {
	//--------------------------------------------------
	// write slayer name
	//--------------------------------------------------
	BYTE szName = m_Name.size();

	if ( szName == 0 )
		throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long name length");

	oStream.write( szName );
	oStream.write( m_Name );

	//--------------------------------------------------
	// write slot
	//--------------------------------------------------
	oStream.write( (BYTE)m_Slot );

	//--------------------------------------------------
	// write Alignment
	//--------------------------------------------------
	oStream.write( m_Alignment );

	//--------------------------------------------------
	// write attributes
	// 순수 능력치만 보낸다.
	//--------------------------------------------------
	oStream.write( m_STR );
	oStream.write( m_DEX );
	oStream.write( m_INT );

	//--------------------------------------------------
	// write attributes
	//--------------------------------------------------
	oStream.write( m_Rank );
	
	oStream.write( m_STRExp );
	oStream.write( m_DEXExp );
	oStream.write( m_INTExp );

	//--------------------------------------------------
	// write hp/mp
	//--------------------------------------------------
	oStream.write( m_HP[ATTR_CURRENT] );
	oStream.write( m_HP[ATTR_MAX] );
	oStream.write( m_MP[ATTR_CURRENT] );
	oStream.write( m_MP[ATTR_MAX] );

	//--------------------------------------------------
	// write misc
	//--------------------------------------------------
	oStream.write( m_Fame );
//	oStream.write( m_Gold );

	//--------------------------------------------------
	// write skills
	//--------------------------------------------------
	for ( uint i = 0 ; i < SKILL_DOMAIN_VAMPIRE; i ++ ) {
		oStream.write( m_DomainLevels[i] );
	}

	//--------------------------------------------------
	// write zone id
	//--------------------------------------------------
//	oStream.write( m_ZoneID );

	//--------------------------------------------------------------------------------
	// write outlook bitset
	//--------------------------------------------------------------------------------
	DWORD outlook = m_Outlook.to_ulong();
	oStream.write( outlook );
	
	//--------------------------------------------------------------------------------
	// write colors
	//--------------------------------------------------------------------------------
	for ( uint i = 0 ; i < SLAYER_COLOR_MAX ; i ++ )
		oStream.write( m_Colors[i] );

	} catch (Throwable & t ) {
		cout << t.toString() << endl;
	}

	oStream.write( m_AdvancementLevel );

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string PCSlayerInfo::toString () const 
	throw ()
{
	StringStream msg;

	msg << "PCSlayerInfo("
		<< "NSize:" << m_Name.size()
		<< ",Name:" << m_Name 
		<< ",Slot:" << Slot2String[m_Slot]
		<< ",Alignment:" << m_Alignment
		<< ",Rank:" << m_Rank
		<< ",STR[BASIC]:" << (int)m_STR 
		<< ",DEX[BASIC]:" << (int)m_DEX
		<< ",INT[BASIC]:" << (int)m_INT
		<< ",HP:" << m_HP[ATTR_CURRENT] << "/" << m_HP[ATTR_MAX]
		<< ",MP:" << m_MP[ATTR_CURRENT] << "/" << m_MP[ATTR_MAX]
		<< ",Fame:" << m_Fame;
//		<< ",Gold:" << m_Gold;

	for ( uint i = 0 ; i < SKILL_DOMAIN_VAMPIRE ; i ++ )
		msg << "," << SkillDomain2String[i] << ":" << (int)m_DomainLevels[i];

//	msg << ",ZoneID:" << m_ZoneID 
	msg	<< ",Sex:" << Sex2String[getSex()]
		<< ",HairStyle:" << HairStyle2String[getHairStyle()]
		<< ",HairColor:" << (int)getHairColor()
		<< ",SkinColor:" << (int)getSkinColor()
		<< " ,Helmet:" << (int)getHelmetType()
		<< ",HelmetColor:" << (int)getHelmetColor()
		<< " ,Jacket:" << (int)getJacketType()
		<< ",JacketColor:" << (int)getJacketColor()
		<< " ,Pants:" << (int)getPantsType()
		<< ",PantsColor:" << (int)getPantsColor()
		<< " ,Weapon:" << (int)getWeaponType()
		<< ",WeaponColor:" << (int)getWeaponColor()
		<< " ,Shield:" << (int)getShieldType()
		<< ",ShieldColor:" << (int)getShieldColor()
		<< ")";
	
	return msg.toString();
}
