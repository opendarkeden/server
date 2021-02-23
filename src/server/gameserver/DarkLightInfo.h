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
	DarkLightInfo() throw();
	DarkLightInfo(const DarkLightInfo & dli) throw();

public:
	DarkLevel_t getDarkLevel() const throw() { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	LightLevel_t getLightLevel() const throw() { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }

	string toString() const throw();

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
	DarkLightInfoManager() throw();
	~DarkLightInfoManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

	DarkLightInfo* getDarkLightInfo(BYTE month, BYTE hour, BYTE minute) throw(OutOfBoundException, Error);
	const DarkLightInfo* getDarkLightInfo(BYTE month, BYTE hour, BYTE minute) const throw(OutOfBoundException, Error);

	DarkLightInfo* getCurrentDarkLightInfo( Zone* pZone ) throw(Error);
	const DarkLightInfo* getCurrentDarkLightInfo( Zone* pZone ) const throw(Error);

	string toString() const throw();

private:
	DarkLightInfo* m_DarkLightInfos[nDarkLightInfos];

};


// global variable declaration
extern DarkLightInfoManager* g_pDarkLightInfoManager;

#endif
