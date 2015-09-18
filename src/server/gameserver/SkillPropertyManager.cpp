//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillProperty.cpp
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SkillPropertyManager.h"
#include "Skill.h"

//////////////////////////////////////////////////////////////////////////////
// class SkillProperty member methods
//////////////////////////////////////////////////////////////////////////////

const int DefaultSkillMax = 20;
const int DefaultSkill[DefaultSkillMax][4] = 
{
	// SkillType, bMelee, bMagic, bPhysic
	{ SKILL_ATTACK_MELEE,		1, 0, 1 },
	{ SKILL_ATTACK_ARMS,		0, 0, 1 },
	{ SKILL_SELF,				0, 0, 0 },
	{ SKILL_TILE,				0, 0, 0 },
	{ SKILL_OBJECT,				0, 0, 0 },
	{ SKILL_UN_BURROW,			0, 0, 0 },
	{ SKILL_UN_TRANSFORM,		0, 0, 0 },
	{ SKILL_UN_INVISIBILITY,	0, 0, 0 },
	{ SKILL_THROW_HOLY_WATER,	0, 0, 0 },
	{ SKILL_SUMMON_BAT,			0, 0, 0 },
	{ SKILL_CHARM,				0, 0, 0 },
	{ SKILL_POLYMORPH,			0, 0, 0 },
	{ SKILL_HYPNOSIS,			0, 0, 0 },
	{ SKILL_CURE_EFFECT,		0, 0, 0 },
	{ SKILL_CRITICAL_EFFECT,	0, 0, 0 },
	{ SKILL_REFLECTION_EFFECT,	0, 0, 0 },
	{ SKILL_TEMP,				0, 0, 0 },
	{ SKILL_DARKNESS_WIDE,		0, 1, 0 },
	{ SKILL_POISON_STORM_WIDE,	0, 1, 0 },
	{ SKILL_ACID_STORM_WIDE,	0, 1, 0 },
};

SkillProperty::SkillProperty()
{
	__BEGIN_TRY
	__END_CATCH
}

SkillProperty::~SkillProperty()
{
	__BEGIN_TRY
	__END_CATCH
}

string SkillProperty::toString() const
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "(" << (int)m_SkillType << ":";
	for (int i = 0; i < SKILL_PROPERTY_TYPE_MAX; i++ )
	{
		msg << (m_PropertyType.test(i ) ? "1" : "0");
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class SkillPropertyManager member methods
//////////////////////////////////////////////////////////////////////////////

SkillPropertyManager::SkillPropertyManager()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}

SkillPropertyManager::~SkillPropertyManager()
	throw()
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

void SkillPropertyManager::init()
	throw()
{
	__BEGIN_TRY

	m_SkillProperties.reserve(SKILL_MAX);

	for (int i = 0 ; i < SKILL_MAX; i++ )
	{
		m_SkillProperties[i] = NULL;
	}
	
	initDefaultSkillProperty();

	__END_CATCH
}

void SkillPropertyManager::clear()
	throw()
{
	__BEGIN_TRY

	for (int i = 0 ; i < SKILL_MAX; i++ )
	{
		SAFE_DELETE(m_SkillProperties[i]);
	}
	
	m_SkillProperties.clear();

	__END_CATCH
}

void SkillPropertyManager::initDefaultSkillProperty()
	throw()
{
	__BEGIN_TRY

	for (int i = 0; i < DefaultSkillMax; i++ )
	{
		SkillProperty* pSkillProperty = new SkillProperty();
		pSkillProperty->setType(DefaultSkill[i][0]);
		pSkillProperty->setMelee(DefaultSkill[i][1]);
		pSkillProperty->setMagic(DefaultSkill[i][2]);
		pSkillProperty->setPhysic(DefaultSkill[i][3]);

		addSkillProperty(pSkillProperty);
	}

	__END_CATCH
}

SkillProperty* SkillPropertyManager::getSkillProperty(SkillType_t SkillType)
	const throw(NoSuchElementException , OutOfBoundException, Error)
{
	__BEGIN_TRY

	if (SkillType >= SKILL_MAX)
	{
		cerr << "SkillPropertyManager::getSkillProperty() : out of bounds" << endl;
		throw OutOfBoundException ();
	}

	if (m_SkillProperties[SkillType] == NULL)
	{
		cerr << "SkillPropertyManager::getSkillProperty() : no such element" << endl;
		throw NoSuchElementException ();
	}

	return m_SkillProperties[SkillType];
	
	__END_CATCH
}

void SkillPropertyManager::addSkillProperty(SkillProperty* pSkillProperty )
	throw(DuplicatedException, OutOfBoundException, Error )
{
	__BEGIN_TRY

	if (pSkillProperty->getType() >= SKILL_MAX)
	{
		cerr << "SkillPropertyManager::getSkillProperty() : out of bounds" << endl;
		throw OutOfBoundException ();
	}

	if (m_SkillProperties[pSkillProperty->getType()] != NULL)
	{
		cerr << "SkillPropertyManager::getSkillProperty() : Dup element" << endl;
		throw DuplicatedException ();
	}

	m_SkillProperties[ pSkillProperty->getType() ] = pSkillProperty;

	__END_CATCH
}

// SkillPropertyManager:: toString()
string SkillPropertyManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SkillPropertyManager(\n";

	for (int i = 0 ; i < (int)SKILL_MAX; i ++)
	{
		msg << m_SkillProperties[i]->toString() << ",";
	}

	msg << "\n)";

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
SkillPropertyManager* g_pSkillPropertyManager = NULL;
