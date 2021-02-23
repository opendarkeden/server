//////////////////////////////////////////////////////////////////////////////
// Filename    : CastleSkillInfo.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CASTLE_SKILL_INFO_H__
#define __CASTLE_SKILL_INFO_H__

#include "Exception.h"
#include "Types.h"
#include <hash_map>


//////////////////////////////////////////////////////////////////////////////
// Class CastleSkillInfo
//////////////////////////////////////////////////////////////////////////////

class CastleSkillInfo 
{
public:
	CastleSkillInfo();
	~CastleSkillInfo();

public:
	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) { m_SkillType = SkillType; }

	ZoneID_t getZoneID() const { return m_ZoneID; }
	void setZoneID( ZoneID_t ZoneID ) { m_ZoneID = ZoneID; }

	string toString() const;

private:
	SkillType_t m_SkillType;
	ZoneID_t m_ZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// Class CastleSkillInfoManager
//////////////////////////////////////////////////////////////////////////////


class CastleSkillInfoManager 
{
public:
	CastleSkillInfoManager() throw();
	~CastleSkillInfoManager() throw();

	typedef hash_map<SkillType_t, CastleSkillInfo*>		HashMapCastleSkillInfo;
	typedef HashMapCastleSkillInfo::iterator			HashMapCastleSkillInfoItor;
	typedef HashMapCastleSkillInfo::const_iterator		HashMapCastleSkillInfoConstItor;

public:

	// void load() throw();
	void load() throw(Error);

	void clear() throw(Error);

	void addCastleSkillInfo( CastleSkillInfo* pCastleSkillInfo ) throw(Error);
	
	SkillType_t getSkillType( ZoneID_t ZoneID ) const;
	ZoneID_t getZoneID(SkillType_t SkillType) const;
	
	// toString for Debug
	string toString() const throw();

private:

	HashMapCastleSkillInfo m_CastleSkillInfos;

};

// Global Variable Definition
extern CastleSkillInfoManager* g_pCastleSkillInfoManager;

#endif	// __CASTLE_SKILL_INFO_H__
