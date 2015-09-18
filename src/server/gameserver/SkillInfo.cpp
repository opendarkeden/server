//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillInfo.cpp
// Written By  : beowulf
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SkillInfo.h"
#include "Assert1.h"
#include "DB.h"
#include "SkillPropertyManager.h"
#include "SkillUtil.h"

#include <algorithm>

//////////////////////////////////////////////////////////////////////////////
// class SkillInfo member methods
//////////////////////////////////////////////////////////////////////////////

SkillInfo::SkillInfo()
{
	__BEGIN_TRY

	m_RequireSkills.clear();

	m_RequireFire = 0;
	m_RequireWater = 0;
	m_RequireEarth = 0;
	m_RequireWind = 0;
	m_RequireSum = 0;

	m_RequireWristletElemental = ELEMENTAL_ANY;
	m_RequireStone1Elemental = ELEMENTAL_ANY;
	m_RequireStone2Elemental = ELEMENTAL_ANY;
	m_RequireStone3Elemental = ELEMENTAL_ANY;
	m_RequireStone4Elemental = ELEMENTAL_ANY;

	m_CanDelete = 0;

	__END_CATCH
}

SkillInfo::~SkillInfo()
{
	__BEGIN_TRY
	__END_CATCH
}

void SkillInfo::setRequireSkill(const string& requireSkill )
{

	if (requireSkill == "" ) return;

	/////////////////////////////
	// 012345678901234567890
	// 111,112,114
	// c  d
	//     c  d
	//         c  d
	/////////////////////////////
    size_t a = requireSkill.find_first_of('(', 0);
    size_t b = requireSkill.find_first_of(')', a+1);

	if (a > b ) return;

	string requires = trim(requireSkill.substr(a+1, b-a-1 ));

    size_t c = 0;
    size_t d;
	do
	{
		d = requires.find_first_of(',', c+1);
		if (d == string::npos )
			d = requires.size();

		SkillType_t skillType = (SkillType_t)atoi(trim(requires.substr(c, d-c ) ).c_str());
		addRequireSkill(skillType);
		
		c = d + 1;
	} while (c < requires.size() - 1);
}

void SkillInfo::setCondition(const string& condition )
{
	if (condition == "" ) return;

    size_t a = 0, b = 0, c = 0;

	do
	{
		///////////////////////////////////////////////////////
		// 01234567890123456789012345678901234567890123456789
		// (Fire,10)(Water,5)(Wristlet,Fire)(Stone1,Water)
		// a    b  ca     b ca        b    ca      b     c
		///////////////////////////////////////////////////////
		a = condition.find_first_of('(', c);
		b = condition.find_first_of(',', a+1);
		c = condition.find_first_of(')', b+1);

		if (a > b || b > c ) break;

		Assert(a+1<b && b+1<c);

		string identifier = trim(condition.substr(a+1, b-a-1 ));
		string require    = trim(condition.substr(b+1, c-b-1 ));

		if (identifier == "Fire" ) setRequireFire(atoi(require.c_str() ));
		else if (identifier == "Water" ) setRequireWater(atoi(require.c_str() ));
		else if (identifier == "Earth" ) setRequireEarth(atoi(require.c_str() ));
		else if (identifier == "Wind" ) setRequireWind(atoi(require.c_str() ));
		else if (identifier == "Sum" ) setRequireSum(atoi(require.c_str() ));
		else if (identifier == "Wristlet" ) setRequireWristletElemental(getElementalTypeFromString(require ));
		else if (identifier == "Stone1" ) setRequireStone1Elemental(getElementalTypeFromString(require ));
		else if (identifier == "Stone2" ) setRequireStone2Elemental(getElementalTypeFromString(require ));
		else if (identifier == "Stone3" ) setRequireStone3Elemental(getElementalTypeFromString(require ));
		else if (identifier == "Stone4" ) setRequireStone4Elemental(getElementalTypeFromString(require ));

	} while (c < condition.size() - 1);
}

string SkillInfo::toString() const
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "SkillInfo ("
		<< "Type:"         << (int)m_Type
		<< ",Name:"        << m_Name
		<< ",Level:"       << (int)m_Level
		<< ",MinDam:"      << (int)m_MinDamage
		<< ",MaxDam:"      << (int)m_MaxDamage
		<< ",MinDelay:"    << (int)m_MinDelay
		<< ",MaxDelay:"    << (int)m_MaxDelay
		<< ",MinCastTime:" << (int)m_MinCastTime
		<< ",MaxCastTime:" << (int)m_MaxCastTime
		<< ",MinDuration:" << (int)m_MinDuration
		<< ",MaxDuration:" << (int)m_MaxDuration
		<< ",ConsumeMP:"   << (int)m_ConsumeMP
		<< ",MaxRange:"    << (int)m_MaxRange
		<< ",MinRange:"    << (int)m_MinRange
		<< ",Point:"       << (int)m_Point
		<< ",Target:"      << (int)m_Target
		<< ",RequireFire:"	<< (int)m_RequireFire
		<< ",RequireWater:"	<< (int)m_RequireWater
		<< ",RequireEarth:"	<< (int)m_RequireEarth
		<< ",RequireWind:"	<< (int)m_RequireWind
		<< ",RequireSum:"	<< (int)m_RequireSum
		<< ",RequireWristletElemental:"	<< (int)m_RequireWristletElemental
		<< ",RequireStone1Elemental:"	<< (int)m_RequireStone1Elemental
		<< ",RequireStone2Elemental:"	<< (int)m_RequireStone2Elemental
		<< ",RequireStone3Elemental:"	<< (int)m_RequireStone3Elemental
		<< ",RequireStone4Elemental:"	<< (int)m_RequireStone4Elemental
		<< ",SkillPoint:"				<< (int)m_SkillPoint
		<< ",LevelUpPoint:"				<< (int)m_LevelUpPoint;
	for (list<SkillType_t>::const_iterator itr = m_RequireSkills.begin() ; itr != m_RequireSkills.end() ; itr++ )
	{
		msg << ",SkillType:" << (int)(*itr);
	}

	msg << ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class SkillInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

SkillInfoManager::SkillInfoManager()
	throw()
{
	__BEGIN_TRY

	m_SkillCount = 0;
	m_SkillInfoList = NULL;

	__END_CATCH
}

SkillInfoManager::~SkillInfoManager()
	throw()
{
	__BEGIN_TRY

	// 이것만 해서는 안되는디.. 어차피 안 불려질거기 때문에 일단 무시.. by sigi
	SAFE_DELETE_ARRAY(m_SkillInfoList);

	__END_CATCH
}

void SkillInfoManager::init()
	throw(Error)
{
	__BEGIN_TRY

	load();

	for (uint i=0; i<m_SkillCount; ++i )
	{
		if (m_SkillInfoList[i] != NULL )
		{
			list<SkillType_t>& rSkills = m_SkillInfoList[i]->getRequireSkills();
			list<SkillType_t>::iterator itr = rSkills.begin();

			for (; itr != rSkills.end(); ++itr )
			{
				SkillInfo* pRequireSkillInfo = m_SkillInfoList[(*itr)];

				if (pRequireSkillInfo == NULL )
				{
					//cout << "스킬 로드 순서가 틀려먹었습니다. : " << (int)m_SkillInfoList[i]->getType() << " / " << (int)(*itr) << endl;
					Assert(false);
				}

				pRequireSkillInfo->addRequiredSkill(m_SkillInfoList[i]->getType());
			}
		}
	}

	// 스킬 레벨 맵 초기화
	for(int i = 0 ; i < SKILL_DOMAIN_MAX; i++) 
	{
		for(int j = 0; j < SLAYER_MAX_DOMAIN_LEVEL+1 ; j++) 
		{
			m_SkillLevelMap[i][j] = 0;
		}
	}

	// 레벨에 따른 도메인 그레이드 초기화
	for(int i = 0; i < GRADE_APPRENTICE_LIMIT_LEVEL + 1; i++) 
	{
		m_DomainGradeMap[i] = SKILL_GRADE_APPRENTICE;
	}
	for(int i = GRADE_APPRENTICE_LIMIT_LEVEL + 1 ; i < GRADE_ADEPT_LIMIT_LEVEL + 1; i++) 
	{
		m_DomainGradeMap[i] = SKILL_GRADE_ADEPT;
	}
	for(int i = GRADE_ADEPT_LIMIT_LEVEL + 1 ; i < GRADE_EXPERT_LIMIT_LEVEL + 1; i++) 
	{
		m_DomainGradeMap[i] = SKILL_GRADE_EXPERT;
	}
	for(int i = GRADE_EXPERT_LIMIT_LEVEL + 1 ; i < GRADE_MASTER_LIMIT_LEVEL + 1; i++) 
	{
		m_DomainGradeMap[i] = SKILL_GRADE_MASTER;
	}
	for(int i = GRADE_MASTER_LIMIT_LEVEL + 1 ; i < GRADE_GRAND_MASTER_LIMIT_LEVEL + 1; i++) 
	{
		m_DomainGradeMap[i] = SKILL_GRADE_GRAND_MASTER;
	}
	for(int i = GRADE_GRAND_MASTER_LIMIT_LEVEL + 1 ; i < SLAYER_MAX_DOMAIN_LEVEL + 1; i++) 
	{
		m_DomainGradeMap[i] = SKILL_GRADE_GRAND_MASTER;
	}


	// 도메인 그레이드에 따른 기술 레벨 제한 초기화
	m_LimitLevelMap[SKILL_GRADE_APPRENTICE] = GRADE_APPRENTICE_LIMIT_LEVEL;
	m_LimitLevelMap[SKILL_GRADE_ADEPT] = GRADE_ADEPT_LIMIT_LEVEL;
	m_LimitLevelMap[SKILL_GRADE_EXPERT] = GRADE_EXPERT_LIMIT_LEVEL;
	m_LimitLevelMap[SKILL_GRADE_MASTER] = GRADE_MASTER_LIMIT_LEVEL;
	m_LimitLevelMap[SKILL_GRADE_GRAND_MASTER] = GRADE_GRAND_MASTER_LIMIT_LEVEL;
	m_LimitLevelMap[SKILL_GRADE_GRAND_MASTER + 1] = GRADE_GRAND_MASTER_LIMIT_LEVEL;

	// 인트에 따른 MP 감소율 테이블 초기화
	for(int i = 0; i < 43; i++) 
	{
		m_decreaseConsumeMP[i] = 0;
	}

	int provide = 8;
	int Multiple = 1;
	for(int i = 43; i < 85; i++) 
	{
		m_decreaseConsumeMP[i] = 5* Multiple;
		provide--;
		if (provide  == 0) 
		{
			provide = 8;
			Multiple++;
		}
	}

	provide = 10;

	for(int i = 85; i < 140; i++) 
	{
		m_decreaseConsumeMP[i] = 5* Multiple;
		provide--;
		if (provide == 0) 
		{
			provide = 10;
			Multiple++;
		}
	}

	provide = 15;
	for(int i = 140; i < 201; i++) 
	{
		m_decreaseConsumeMP[i] = 5* Multiple;
		provide--;
		if (provide == 0) 
		{
			provide = 15;
			Multiple++;
		}
	}

	provide = 15;
	for(int i = 201; i < 301; i++) 
	{
		m_decreaseConsumeMP[i] = 5* Multiple;
		provide--;
		if (provide == 0) 
		{
			provide = 15;
			Multiple++;
		}
	}

	__END_CATCH
}

void SkillInfoManager::load()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Statement* pStmt    = NULL;
	Result*    pResult  = NULL;

	// Skill Property Manager 를 초기화한다.
	g_pSkillPropertyManager->init();
	
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(Type) FROM SkillBalance");
		//Result = pStmt->executeQuery("SELECT MAX(Type) FROM SkillInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error ("There is no data in SkillInfo Table");
		}

		pResult->next();

		m_SkillCount = pResult->getInt(1) +1;

		Assert (m_SkillCount > 0);

		m_SkillInfoList = new SkillInfo* [m_SkillCount];

		for (uint i=0 ; i < m_SkillCount; i++)
			m_SkillInfoList[i] = NULL;

		pResult = pStmt->executeQuery("Select Type, Name, Level, MinDam, MaxDam, MinDelay, MaxDelay, MinDur, MaxDur, Mana, MinRange, MaxRange, Target, SubExp, Point, Domain, MagicDomain, Melee, Magic, Physic, SkillPoint, LevelUpPoint, RequireSkill, `Condition`, ElementalDomain, CanDelete from SkillBalance");

		while (pResult->next()) 
		{
			SkillInfo* pSkillInfo = new SkillInfo ();
			int i = 0;

			pSkillInfo->setType(pResult->getInt(++i));
			pSkillInfo->setName (pResult->getString(++i));
			pSkillInfo->setLevel(pResult->getInt(++i));

			pSkillInfo->setMinDamage(pResult->getInt(++i));
			pSkillInfo->setMaxDamage(pResult->getInt(++i));
			pSkillInfo->setMinDelay(pResult->getInt(++i));
			pSkillInfo->setMaxDelay(pResult->getInt(++i));
			pSkillInfo->setMinDuration(pResult->getInt(++i));
			pSkillInfo->setMaxDuration(pResult->getInt(++i));

			pSkillInfo->setConsumeMP(pResult->getInt(++i));
			pSkillInfo->setMinRange(pResult->getInt(++i));
			pSkillInfo->setMaxRange(pResult->getInt(++i));
			pSkillInfo->setTarget(pResult->getInt(++i));
			pSkillInfo->setSubSkill(pResult->getInt(++i));
			pSkillInfo->setPoint(pResult->getInt(++i));
			pSkillInfo->setDomainType(pResult->getBYTE(++i));
			pSkillInfo->setMagicDomain(pResult->getBYTE(++i));

			// Skill Property 추가
			SkillProperty* pSkillProperty = new SkillProperty();

			pSkillProperty->setType(pSkillInfo->getType());
			pSkillProperty->setMelee(pResult->getInt(++i));
			pSkillProperty->setMagic(pResult->getInt(++i));
			pSkillProperty->setPhysic(pResult->getInt(++i));

			g_pSkillPropertyManager->addSkillProperty(pSkillProperty);

			if (pSkillInfo->getDomainType() == SKILL_DOMAIN_OUSTERS )
			{
				pSkillInfo->setSkillPoint(pResult->getInt(++i));
				pSkillInfo->setLevelUpPoint(pResult->getInt(++i));
				pSkillInfo->setRequireSkill(pResult->getString(++i));
				pSkillInfo->setCondition(pResult->getString(++i));
				pSkillInfo->setElementalDomain(pResult->getInt(++i));
				pSkillInfo->setCanDelete(pResult->getInt(++i));
			}

			// Skill Info 추가
			addSkillInfo(pSkillInfo);
		}
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void SkillInfoManager::save()
	throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError (__PRETTY_FUNCTION__);
	
	__END_CATCH
}

void SkillInfoManager::addSkillInfo(SkillInfo* pSkillInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

  	Assert (pSkillInfo != NULL);

	if (m_SkillInfoList[pSkillInfo->getType()] != NULL)
		throw DuplicatedException ();

	m_SkillInfoList[pSkillInfo->getType()] = pSkillInfo;

	m_SkillLevelMap[pSkillInfo->getDomainType()][pSkillInfo->getLevel()] = pSkillInfo->getType();

/*	list<SkillType_t>& rSkills = pSkillInfo->getRequireSkills();
	list<SkillType_t>::iterator itr = rSkills.begin();

	for (; itr != rSkills.end(); ++itr )
	{
		SkillInfo* pRequireSkillInfo = m_SkillInfoList[(*itr)];

		if (pRequireSkillInfo == NULL )
		{
			cout << "스킬 로드 순서가 틀려먹었습니다. : " << (int)pSkillInfo->getType() << " / " << (int)(*itr) << endl;
			Assert(false);
		}

		pRequireSkillInfo->addRequiredSkill(pSkillInfo->getType());
	}*/
	
	__END_CATCH
}

SkillInfo* SkillInfoManager::getSkillInfo(SkillType_t SkillType)
	const throw(NoSuchElementException , OutOfBoundException, Error)
{
	__BEGIN_TRY

	if (SkillType >= m_SkillCount)
	{
		cerr << "SkillInfoManager::getSkillInfo() : out of bounds : " << (int)SkillType << endl;
		throw OutOfBoundException ();
	}

	if (m_SkillInfoList[SkillType] == NULL)
	{
		cerr << "SkillInfoManager::getSkillInfo() : no such element : " << (int)SkillType << endl;
		throw NoSuchElementException ();
	}

	return m_SkillInfoList[SkillType];
	
	__END_CATCH
}

SkillType_t SkillInfoManager::getSkillTypeByLevel(SkillDomainType_t SkillDomain , SkillLevel_t SkillLevel)
	throw(OutOfBoundException)
{
	__BEGIN_TRY

	if (SkillDomain >= SKILL_DOMAIN_MAX) throw OutOfBoundException();
	if (SkillLevel > SLAYER_MAX_DOMAIN_LEVEL) throw OutOfBoundException();

	return m_SkillLevelMap[SkillDomain][SkillLevel];

	__END_CATCH
}

// 도메인의 레벨로 그 레벨은 어떤 등급에 해당하는지 아는 함수.
SkillGrade SkillInfoManager::getGradeByDomainLevel(Level_t Level)
	throw(OutOfBoundException)
{
	__BEGIN_TRY

	if (Level > SLAYER_MAX_DOMAIN_LEVEL) throw OutOfBoundException();
	return m_DomainGradeMap[Level];

	__END_CATCH
}

// 현재 등급에서 기술이 어느정도 레벨까지 올라갈 수 있는지 알아 본다.
Level_t SkillInfoManager::getLimitLevelByDomainGrade(SkillGrade Grade)
	throw(OutOfBoundException)
{
	__BEGIN_TRY

	if (Grade > SKILL_GRADE_MAX) throw OutOfBoundException();
	return m_LimitLevelMap[Grade];

	__END_CATCH
}

// SkillInfoManager:: toString()
string SkillInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SkillInfoManager(\n";

	for (int i = 0 ; i < (int)m_SkillCount ; i ++)
	{
		msg << "SkillInfos[" << i << "] == ";
		msg	<< (m_SkillInfoList[i] == NULL ? "NULL" : m_SkillInfoList[i]->getName());
		msg << "\n";
		if (m_SkillInfoList[i] != NULL) {
			msg << m_SkillInfoList[i]->toString() << "\n";
		}
	}

	msg << "\n";

	for(int i = 0 ; i < SKILL_DOMAIN_MAX; i++) {
		for(int j = 0 ; i < SLAYER_MAX_DOMAIN_LEVEL+1 ; i++) {
			msg << "SkillLevelMap [" << i << "][" << j << "] == ";
			msg << (int)m_SkillLevelMap[i][j] << "\n";
		}
	}

	for(int i = 0; i < SLAYER_MAX_DOMAIN_LEVEL+1 ; i++) {
		msg << "DomainGradeMap [" << i << "] == ";
		msg << (int)m_DomainGradeMap[i] << "\n";
	}

	for(int i = 0 ; i < SKILL_GRADE_MAX; i++) {
		msg << "LimitLevelMap [" << i << "] == ";
		msg << (int)m_LimitLevelMap[i] << "\n";
	}

	msg << ")";

	/*
	StringStream msg;
	msg << "SkillInfoManager(";

	for (uint i = 0 ; i < m_SkillCount ; i ++) 
	{
		if (m_SkillInfoList[i] != NULL)
		{
			msg << m_SkillInfoList[i]->toString();
		}
		else 
		{
			msg << "NULL" ;
		}
	}
	
	msg << ")";
	*/

	return msg.toString();

	__END_CATCH
}

// Global Variable definition
SkillInfoManager* g_pSkillInfoManager = NULL;
