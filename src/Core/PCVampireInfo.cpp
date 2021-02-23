//----------------------------------------------------------------------
//
// Filename    : PCVampireInfo.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "PCVampireInfo.h"

void PCVampireInfo::setShapeInfo(DWORD flag, Color_t color[VAMPIRE_COLOR_MAX]) 
	throw()
{
	// 현재는 vampire coat만 모양이 바뀌므로..
	// 나중에 다른 부위도 바뀐다면 PCSlayerInfo를 참조해서 바꿔야될 것이다
	m_CoatType = flag;//(flag & 7);
	m_CoatColor = color[0];
}

//----------------------------------------------------------------------
// read data from socket input stream
//----------------------------------------------------------------------
void PCVampireInfo::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

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
	// read slot
	//--------------------------------------------------
	BYTE slot;	
	iStream.read( slot );
	m_Slot = Slot(slot);

	//--------------------------------------------------
	// read Alignment
	//--------------------------------------------------
	iStream.read( m_Alignment );

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

	//--------------------------------------------------
	// read Shape
	//--------------------------------------------------
	BYTE coatType;
	iStream.read( coatType );
	m_CoatType = (ItemType_t)coatType;
	iStream.read( m_CoatColor );

	//--------------------------------------------------
	// read attributes
	//--------------------------------------------------
	iStream.read( m_STR );
	iStream.read( m_DEX );
	iStream.read( m_INT );

	//--------------------------------------------------
	// read hp
	//--------------------------------------------------
	iStream.read( m_HP[ATTR_CURRENT] );
	iStream.read( m_HP[ATTR_MAX] );
	
	//--------------------------------------------------
	// read misc
	//--------------------------------------------------
	iStream.read( m_Level );
	iStream.read( m_Rank );
	iStream.read( m_Exp );
//	iStream.read( m_Gold );

	//--------------------------------------------------
	// read Fame 
	//--------------------------------------------------
	iStream.read( m_Fame );
	
	//--------------------------------------------------
	// read zone id
	//--------------------------------------------------
//	iStream.read( m_ZoneID );

	//--------------------------------------------------
	// read Bonus Point
	//--------------------------------------------------
	iStream.read( m_Bonus );
	iStream.read( m_AdvancementLevel );

	__END_CATCH
}

//----------------------------------------------------------------------
// write data to socket output stream
//----------------------------------------------------------------------
void PCVampireInfo::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

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
	// write slot
	//--------------------------------------------------
	oStream.write( (BYTE)m_Slot );

	//--------------------------------------------------
	// write Alignment
	//--------------------------------------------------
	oStream.write( m_Alignment);

	//--------------------------------------------------
	// write sex
	//--------------------------------------------------
	oStream.write( (BYTE)m_Sex );

	//--------------------------------------------------
	// write colors
	//--------------------------------------------------
	oStream.write( m_BatColor );
	oStream.write( m_SkinColor );

	//--------------------------------------------------
	// write Shape
	//--------------------------------------------------
	BYTE coatType = (BYTE)m_CoatType;
	oStream.write( coatType );
	oStream.write( m_CoatColor );

	//--------------------------------------------------
	// write attributes
	//--------------------------------------------------
	oStream.write( m_STR );
	oStream.write( m_DEX );
	oStream.write( m_INT );

	//--------------------------------------------------
	// write hp
	//--------------------------------------------------
	oStream.write( m_HP[ATTR_CURRENT] );
	oStream.write( m_HP[ATTR_MAX] );
	
	//--------------------------------------------------
	// write misc
	//--------------------------------------------------
	oStream.write( m_Level );
	oStream.write( m_Rank );
	oStream.write( m_Exp );
//	oStream.write( m_Gold );

	//--------------------------------------------------
	// read Fame
	//--------------------------------------------------
	oStream.write( m_Fame );
	
	//--------------------------------------------------
	// write zone id
	//--------------------------------------------------
//	oStream.write( m_ZoneID );

	//--------------------------------------------------
	// write Bonus Point
	//--------------------------------------------------
	oStream.write( m_Bonus );
	oStream.write( m_AdvancementLevel );

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string PCVampireInfo::toString () const 
	throw ()
{

	StringStream msg;

	msg << "PCVampireInfo("
		<< "Name:" << m_Name
		<< ",Level:" << (int)m_Level
		<< ",Slot:" << Slot2String[m_Slot]
		<< ",Alignment:" << m_Alignment
		<< ",Sex:" << Sex2String[m_Sex]
		<< ",BatColor:" << (int)m_BatColor
		<< ",SkinColor:" << (int)m_SkinColor
		<< ",CoatType:" << (int)m_CoatType
		<< ",CoatColor:" << (int)m_CoatColor
		<< ",STR[BASIC]:" << (int)m_STR
		<< ",DEX[BASIC]:" << (int)m_DEX
		<< ",INT[BASIC]:" << (int)m_INT
		<< ",HP:" << m_HP[ATTR_CURRENT] << "/" << m_HP[ATTR_MAX]
		<< ",Rank:" << m_Rank
		<< ",Exp:" << m_Exp
//		<< ",Gold:" << m_Gold
		<< ",Fame:" << m_Fame
//		<< ",ZoneID:" << m_ZoneID
		<< ")";

	return msg.toString();
}
