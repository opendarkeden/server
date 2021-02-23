//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillProperty.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PROPERTY_H__
#define __SKILL_PROPERTY_H__

#include "Exception.h"
#include "Types.h"
#include "SkillInfo.h"
#include <bitset>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// Class SkillProperty
//////////////////////////////////////////////////////////////////////////////

class SkillProperty 
{
public:
	SkillProperty();
	~SkillProperty();

public:
	SkillType_t getType() const { return m_SkillType; }
	void setType( SkillType_t skillType ) { m_SkillType = skillType; }

	bool isMelee() const { return m_PropertyType.test(SKILL_PROPERTY_TYPE_MELEE); }
	void setMelee( bool bMelee )
	{
		( bMelee ? m_PropertyType.set( SKILL_PROPERTY_TYPE_MELEE )
		  		 : m_PropertyType.reset( SKILL_PROPERTY_TYPE_MELEE ) ); }

	bool isMagic() const { return m_PropertyType.test(SKILL_PROPERTY_TYPE_MAGIC); }
	void setMagic( bool bMagic ) 
	{
		( bMagic ? m_PropertyType.set( SKILL_PROPERTY_TYPE_MAGIC )
				 : m_PropertyType.reset( SKILL_PROPERTY_TYPE_MAGIC ) );
	}

	bool isPhysic() const { return m_PropertyType.test( SKILL_PROPERTY_TYPE_PHYSIC ); }
	void setPhysic( bool bPhysic )
	{ 
		( bPhysic ? m_PropertyType.set( SKILL_PROPERTY_TYPE_PHYSIC )
		  		  : m_PropertyType.reset( SKILL_PROPERTY_TYPE_PHYSIC ) );
	}

	// toString
	string toString() const ;

private:
	SkillType_t						m_SkillType;
	bitset<SKILL_PROPERTY_TYPE_MAX> m_PropertyType;
};

//////////////////////////////////////////////////////////////////////////////
// Class SkillPropertyManager
//////////////////////////////////////////////////////////////////////////////

class SkillPropertyManager 
{
public:
	SkillPropertyManager() throw();
	~SkillPropertyManager() throw();

public:

	// init SkillProperties
	void init() throw();

	// clear SkillProperties
	void clear() throw();

	// init default SkillProperty
	void initDefaultSkillProperty() throw();

	// get SkillProperty
	SkillProperty* getSkillProperty(SkillType_t SkillType) const throw(NoSuchElementException, OutOfBoundException, Error);

	// add SkillProperty
	void addSkillProperty(SkillProperty* pSkillProperty) throw(DuplicatedException, OutOfBoundException, Error);

	// toString for Debug
	string toString() const throw();

private:
	vector<SkillProperty*> 	m_SkillProperties;
};

// Global Variable Definition
extern SkillPropertyManager* g_pSkillPropertyManager;

#endif	// __SKILL_PROPERTY_MANAGER_H__
