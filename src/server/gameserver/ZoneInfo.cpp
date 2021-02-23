//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneInfo.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ZoneInfo.h"
#include "DB.h"
#include "StringStream.h"

ZoneInfo::ZoneInfo()
{
	m_bMasterLair = false;	// 이건 MasterLairInfoManager에서 설정한다.
	m_bCastle = false;	// 이건 CastleInfoManager에서 설정한다.
}

ZoneInfo::~ZoneInfo()
{
}

void ZoneInfo::load( ZoneID_t zoneID )
	throw ( Error )
{
	__BEGIN_TRY

	/*
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		// create statement
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// OwnerID, 가 다 NULL이라서 일단 빼버렸다.
		Result* pResult = pStmt->executeQuery( "SELECT ZoneGroupID, Type, Level, AccessMode, PayPlayZone, PremiumZone, PKZone, NoPortalZone, SMPFilename, SSIFilename, FullName, ShortName FROM ZoneInfo WHERE ZoneID = %d", zoneID );
		if ( pResult->next() )
		{
			uint i = 0;

			m_ZoneID = zoneID;
			m_ZoneGroupID = pResult->getInt(++i);
			setZoneType( pResult->getString(++i) );
			m_ZoneLevel = pResult->getInt(++i);
			m_ZoneAccessMode = (ZoneAccessMode)pResult->getInt(++i);
			//m_OwnerID = pResult->getString(++i);
			m_bPayPlay = pResult->getInt(++i)!=0;
			m_bPremiumZone = pResult->getInt(++i)!=0;
			m_bPKZone = pResult->getInt(++i)!=0;
			m_bNoPortalZone = pResult->getInt(++i)!=0;
			m_SMPFilename = pResult->getString(++i);
			m_SSIFilename = pResult->getString(++i);
			m_FullName = pResult->getString(++i);
			m_ShortName = pResult->getString(++i);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	*/
	Assert(false);

	__END_CATCH
}

void ZoneInfo::setZoneType ( const string & zoneType ) 
	throw ( Error ) 
{ 
	if ( zoneType == "NORMAL_FIELD" ) 
		m_ZoneType = ZONE_NORMAL_FIELD;
	else if ( zoneType == "NORMAL_DUNGEON" )
		m_ZoneType = ZONE_NORMAL_DUNGEON;
	else if ( zoneType == "SLAYER_GUILD" ) 
		m_ZoneType = ZONE_SLAYER_GUILD;
	else if ( zoneType == "RESERVED_SLAYER_GUILD" ) 
		m_ZoneType = ZONE_RESERVED_SLAYER_GUILD;
	else if ( zoneType == "PC_VAMPIRE_LAIR" ) 
		m_ZoneType = ZONE_PC_VAMPIRE_LAIR;
	else if ( zoneType == "NPC_VAMPIRE_LAIR" ) 
		m_ZoneType = ZONE_NPC_VAMPIRE_LAIR;
	else if ( zoneType == "NPC_HOME" ) 
		m_ZoneType = ZONE_NPC_HOME;
	else if ( zoneType == "NPC_SHOP" ) 
		m_ZoneType = ZONE_NPC_SHOP;
	else if ( zoneType == "RANDOM_MAP" ) 
		m_ZoneType = ZONE_RANDOM_MAP;
	else if ( zoneType == "CASTLE" ) 
		m_ZoneType = ZONE_CASTLE;
	else
	{
		StringStream msg;
		msg << "ZoneInfo::setZoneType() : Invalid Zone Type[" << zoneType << "]";

		cerr << msg.toString() << endl;
		throw Error(msg.toString());
	}
}

void ZoneInfo::setZoneAccessMode ( const string & zoneAccessMode ) throw ( Error )
{
	if ( zoneAccessMode == "PUBLIC" ) m_ZoneAccessMode = PUBLIC;
	else if ( zoneAccessMode == "PRIVATE" ) m_ZoneAccessMode = PRIVATE;
}

string ZoneInfo::toString () const throw ()
{
	StringStream msg;
	msg << "ZoneInfo("
		<< "ZoneID:" << (int)m_ZoneID
		<< ",ZoneGroupID:" << (int)m_ZoneGroupID
		<< ",ZoneType:" << (int)m_ZoneType
		<< ",ZoneLevel:" << (int)m_ZoneLevel
		<< ",ZoneAccessMode:" << (int)m_ZoneAccessMode
		<< ",OwnerID:" << m_OwnerID
		<< ",PayPlayZone:" << (int)m_bPayPlay
		<< ",PremiumZone:" << (int)m_bPremiumZone
		<< ",PKZone:" << (int)m_bPKZone
		<< ",NoPortalZone:" << (int)m_bNoPortalZone
		<< ",Castle:" << (int)m_bCastle
		<< ",HolyLand:" << (int)m_bHolyLand
		<< ",SMPFilename:" << m_SMPFilename
		<< ",SSIFilename:" << m_SSIFilename
		<< ",FullName:" << m_FullName
		<< ",ShortName:" << m_ShortName
		<< ")";
	return msg.toString();
}

