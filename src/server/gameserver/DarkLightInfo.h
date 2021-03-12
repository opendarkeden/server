//////////////////////////////////////////////////////////////////////////////
// Filename    : DarkLightInfo.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __DARK_LIGHT_INFO_H__
#define __DARK_LIGHT_INFO_H__

#include "Types.h"
#include "Exception.h"

class Zone;

//////////////////////////////////////////////////////////////////////////////
// class DarkLightInfo
//////////////////////////////////////////////////////////////////////////////

class DarkLightInfo 
{
public:
	DarkLightInfo() ;
	DarkLightInfo(const DarkLightInfo & dli) ;

public:
	DarkLevel_t getDarkLevel() const  { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel)  { m_DarkLevel = darkLevel; }

	LightLevel_t getLightLevel() const  { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel)  { m_LightLevel = lightLevel; }

	string toString() const ;

private:

	// 어둡기 레벨 
	// 0 - 15 사이의 값으로, 높을 수록 화면이 어두워진다.
	DarkLevel_t m_DarkLevel;

	// 빛의 크기
	// 1 - 13 사이의 값으로, 높을 수록 빛의 범위가 커진다.
	LightLevel_t m_LightLevel;

};


////////////////////////////////////////////////////////////////////////////////
// DLIM 의 내부 DLI 의 배열의 크기
////////////////////////////////////////////////////////////////////////////////
const uint nDarkLightInfos = 12* 24* 6;


////////////////////////////////////////////////////////////////////////////////
// class DarkLightInfoManager
////////////////////////////////////////////////////////////////////////////////

class DarkLightInfoManager 
{
public:
	DarkLightInfoManager() ;
	~DarkLightInfoManager() ;

public:
	void init() ;
	void load() ;

	DarkLightInfo* getDarkLightInfo(BYTE month, BYTE hour, BYTE minute) ;
	const DarkLightInfo* getDarkLightInfo(BYTE month, BYTE hour, BYTE minute) const ;

	DarkLightInfo* getCurrentDarkLightInfo( Zone* pZone ) ;
	const DarkLightInfo* getCurrentDarkLightInfo( Zone* pZone ) const ;

	string toString() const ;

private:
	DarkLightInfo* m_DarkLightInfos[nDarkLightInfos];

};


// global variable declaration
extern DarkLightInfoManager* g_pDarkLightInfoManager;

#endif
