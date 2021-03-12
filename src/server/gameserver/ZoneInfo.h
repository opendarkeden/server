//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneInfo.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZONEINFO_H__
#define __ZONEINFO_H__

#include "Types.h"
#include "Exception.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class ZoneInfo;
//////////////////////////////////////////////////////////////////////////////

class ZoneInfo 
{
public:
	ZoneInfo();
	~ZoneInfo();

	void load( ZoneID_t zoneID ) ;

public:
	ZoneID_t getZoneID() const  { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID)  { m_ZoneID = zoneID; }

	ZoneGroupID_t getZoneGroupID() const  { return m_ZoneGroupID; }
	void setZoneGroupID(ZoneGroupID_t zoneGroupID)  { m_ZoneGroupID = zoneGroupID; }

	ZoneType getZoneType() const  { return m_ZoneType; }
	void setZoneType(ZoneType zoneType)  { m_ZoneType = zoneType; }
	void setZoneType(const string & zoneType) ;

	ZoneLevel_t getZoneLevel() const  { return m_ZoneLevel; }
	void setZoneLevel(ZoneLevel_t zoneLevel)  { m_ZoneLevel = zoneLevel; }

	ZoneAccessMode getZoneAccessMode() const  { return m_ZoneAccessMode; }
	void setZoneAccessMode(ZoneAccessMode zoneAccessMode)  { m_ZoneAccessMode = zoneAccessMode; }
	void setZoneAccessMode(const string & zoneAccessMode) ;

	bool isPayPlay() const  { return m_bPayPlay; }
	void setPayPlay(bool bPayPlay=true)  { m_bPayPlay = bPayPlay; }

	bool isPremiumZone() const  { return m_bPremiumZone; }
	void setPremiumZone(bool bPremiumZone=true)  { m_bPremiumZone = bPremiumZone; }

	string getZoneOwnerID() const  { return m_OwnerID; }
	void setZoneOwnerID(const string & ownerID)  { m_OwnerID = ownerID; }

	string getSMPFilename(void) const  { return m_SMPFilename; }
	void setSMPFilename(const string& name)  { m_SMPFilename = name; }

	string getSSIFilename(void) const  { return m_SSIFilename; }
	void setSSIFilename(const string& name)  { m_SSIFilename = name; }

	string getFullName(void) const  { return m_FullName; }
	void setFullName(const string& name)  { m_FullName = name; }

	string getShortName(void) const  { return m_ShortName; }
	void setShortName(const string& name)  { m_ShortName = name; }

	bool isPKZone() const  { return m_bPKZone; }
	void setPKZone(bool bPKZone=true)  { m_bPKZone = bPKZone; }

	bool isNoPortalZone() const  { return m_bNoPortalZone; }
	void setNoPortalZone(bool bNoPortalZone=true)  { m_bNoPortalZone = bNoPortalZone; }

	bool isMasterLair() const  { return m_bMasterLair; }
	void setMasterLair(bool bMasterLair=true)  { m_bMasterLair = bMasterLair; }

	bool isCastle() const  { return m_bCastle; }
	void setCastle(bool bCastle=true)  { m_bCastle = bCastle; }

	bool isHolyLand() const  { return m_bHolyLand; }
	void setHolyLand(bool bHolyLand=true)  { m_bHolyLand = bHolyLand; }

	bool isLevelWarZone() const
	{
		switch ( m_ZoneID )
		{
			case 1131:
			case 1132:
			case 1133:
			case 1134:
				{
					return true;
				}
				break;
			default:
				{
					return false;
				}
				break;
		}
	}

	bool isAvailable() const  { return m_bAvailable; }
	void setAvailable(bool bAvailable=true)  { m_bAvailable = bAvailable; }

	int getOpenLevel() const  { return m_OpenLevel; }
	void setOpenLevel(int OpenLevel)  { m_OpenLevel = OpenLevel; }

	string toString() const ;

private:
	ZoneID_t       m_ZoneID;         // 존 아이디
	ZoneGroupID_t  m_ZoneGroupID;    // 존 그룹 아이디
	ZoneType       m_ZoneType;       // 존 타입
	ZoneLevel_t    m_ZoneLevel;      // 존 레벨(0 - 10)
	ZoneAccessMode m_ZoneAccessMode; // 존 접근 모드
	bool           m_bPayPlay;		 // 유료화 존? = 돈 내야 들어갈 수 있는 곳
	bool           m_bPremiumZone;	 // 프리미엄 서비스가 되는 존 
	string         m_OwnerID;        // 존 소유자 아이디
	string         m_SMPFilename;    // SMP 파일 이름
	string         m_SSIFilename;    // SSI 파일 이름
	string         m_FullName;       // 존 이름
	string         m_ShortName;      // 짧은 이름

	bool           m_bPKZone;        // 성향 안 떨어지는 존
	bool           m_bNoPortalZone;  // portal로 이동이 불가능한 존
	bool           m_bMasterLair;  	 // 마스터 레어인가?
	bool           m_bCastle;  	 		// Castle인가?
	bool           m_bHolyLand;  	 	// 아담의 성지인가?
	bool           m_bAvailable;        // 나와야 되는 존인가?

	int            m_OpenLevel;         // 존의 공개 레벨. OpenDegree가 존의 공개 레벨보다 높아야 나온다.

};

#endif
