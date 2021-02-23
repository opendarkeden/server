//////////////////////////////////////////////////////////////////////////////
// Filename    : DefaultOptionSetInfo.h
// Written By  : 배재형
// Description :
//////////////////////////////////////////////////////////////////////////////


#ifndef __DEFAULT_OPTION_SET_INFO_H__
#define __DEFAULT_OPTION_SET_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "OptionInfo.h"
#include <hash_map>
#include <list>


enum DefaultOptionSetTypes
{
	DEFAULT_OPTION_SET_FAMILY_PAY,		// 0. 패밀리 요금제용. 모든저항 +7

	DEFAULT_OPTION_SET_MAX
};

class DefaultOptionSetInfo
{
public:
	DefaultOptionSetInfo();
	~DefaultOptionSetInfo();

public:
	void setType( DefaultOptionSetType_t type ) { m_Type = type; }
	DefaultOptionSetType_t getType() const { return m_Type; }

	void setOptionTypeList( const list<OptionType_t>& optionTypes ) { m_OptionTypes = optionTypes; }
	const list<OptionType_t>& getOptionTypeList() const { return m_OptionTypes; }

private:
	DefaultOptionSetType_t		m_Type;
	list<OptionType_t>			m_OptionTypes;

};

typedef hash_map<DefaultOptionSetType_t, DefaultOptionSetInfo*>		HashMapDefaultOptionSetInfo;
typedef HashMapDefaultOptionSetInfo::iterator						HashMapDefaultOptionSetInfoItor;
typedef HashMapDefaultOptionSetInfo::const_iterator					HashMapDefaultOptionSetInfoConstItor;


class DefaultOptionSetInfoManager
{
public:
	DefaultOptionSetInfoManager();
	~DefaultOptionSetInfoManager();

public:
	void load() throw();

	DefaultOptionSetInfo* getDefaultOptionSetInfo( DefaultOptionSetType_t type );
	void addDefaultOptionSetInfo( DefaultOptionSetInfo* pDefaultOptionSetInfo ) throw(DuplicatedException,Error);

private:
	HashMapDefaultOptionSetInfo	m_DefaultOptionSetInfos;
};

//////////////////////////////////////////////////////////////////////////////
// global varibles
//////////////////////////////////////////////////////////////////////////////
extern DefaultOptionSetInfoManager* g_pDefaultOptionSetInfoManager;

#endif
