////////////////////////////////////////////////////////////////////////
// Filename    : Directive.cpp
// Written By  : 김성민
// Description : 
// MonsterAI에서 행동을 결정하는 Directive와 DirectiveSet을
// 구현해놓은 파일이다.
////////////////////////////////////////////////////////////////////////

#include "Directive.h"
#include "StringStream.h"
#include "DB.h"
#include "Assert.h"
#include <string.h>
#include <stdio.h>

#include "skill/Skill.h"

// 상수들...
#define MODE_CONDITION   0
#define MODE_ACTION      1

// 전역 변수
DirectiveSetManager* g_pDirectiveSetManager = NULL;

////////////////////////////////////////////////////////////////////////
// class Directive member methods
////////////////////////////////////////////////////////////////////////

Directive::Directive()
	throw()
{
	__BEGIN_TRY

	m_Action    = 0;
	m_Parameter = 0;
	m_Ratio     = 0;
	m_Weight    = 0;

	__END_CATCH
}

Directive::~Directive()
	throw()
{
	__BEGIN_TRY

	m_Conditions.clear();

	__END_CATCH
}

void Directive::addCondition(int condition) 
	throw()
{
	__BEGIN_TRY

	// 같은 컨디션이 있지 않은지 검사한다.
	list<int>::iterator itr = m_Conditions.begin();
	for (; itr != m_Conditions.end(); itr++)
	{
		if (condition == *itr) return;
	}

	m_Conditions.push_back(condition);

	__END_CATCH
}

string Directive::toString()
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	// header
	msg << "Directive(";

	// condition output
	msg	<< "Condition : ";
	list<int>::const_iterator itr = m_Conditions.begin();
	for (; itr != m_Conditions.end(); itr++)
		msg << DirectiveCondition2String[*itr] << ",";
	msg << " ";

	// action output
	msg << "Action : " << DirectiveAction2String[m_Action] << " ";

	// parameter output
	if (m_Parameter != 0)
		msg << "Parameter : " << SkillTypes2String[m_Parameter] << " ";

	// ratio output
	if (m_Ratio != 0)
		msg << "Ratio : " << m_Ratio;

	// tail 
	msg << ")";

	return msg.toString();

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// class DirectiveSet member methods
////////////////////////////////////////////////////////////////////////

DirectiveSet::DirectiveSet()
	throw()
{
	__BEGIN_TRY

	__END_CATCH
}

DirectiveSet::~DirectiveSet()
	throw()
{
	__BEGIN_TRY

	// 리스트를 검색하면서 Directive 객체를 삭제한다.
	list<Directive*>::iterator itr = m_Directives.begin();
	for (; itr != m_Directives.end(); itr++)
	{
		Directive* pDirective = *itr;
		SAFE_DELETE(pDirective);
	}

	m_Directives.clear();

	__END_CATCH
}

void DirectiveSet::clear()
	throw()
{
	__BEGIN_TRY

	// 리스트를 검색하면서 Directive 객체를 삭제한다.
	list<Directive*>::iterator itr = m_Directives.begin();
	for (; itr != m_Directives.end(); itr++)
	{
		Directive* pDirective = *itr;
		SAFE_DELETE(pDirective);
	}

	m_Directives.clear();

	__END_CATCH
}

bool DirectiveSet::hasCondition( int condition ) const
{
	list<Directive*>::const_iterator itr = m_Directives.begin();
	list<Directive*>::const_iterator endItr = m_Directives.end();

	for (; itr != endItr; ++itr)
	{
		if ( (*itr)->hasCondition(condition) ) return true;
	}

	return false;
}

void DirectiveSet::addDirective(Directive* pDirective)
	throw()
{
	__BEGIN_TRY

	m_Directives.push_back(pDirective);	

	__END_CATCH
}

void DirectiveSet::addDeadDirective(Directive* pDirective)
	throw()
{
	__BEGIN_TRY

	m_DeadDirectives.push_back(pDirective);	

	__END_CATCH
}



////////////////////////////////////////////////////////////////////////
// 생성자
////////////////////////////////////////////////////////////////////////
DirectiveSetManager::DirectiveSetManager()
	throw()
{
	__BEGIN_TRY

	m_nSetCount = 0;
	m_ppSet     = NULL;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// 소멸자
////////////////////////////////////////////////////////////////////////
DirectiveSetManager::~DirectiveSetManager()
	throw()
{
	__BEGIN_TRY

	if (m_ppSet)
	{
		for (uint i=0; i<m_nSetCount; i++)
		{
			SAFE_DELETE(m_ppSet[i]);
		}

		SAFE_DELETE_ARRAY(m_ppSet);	// 이게 불려질 일은 없겠지만.. -_-; by sigi
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// init()
// 객체를 초기화한다. 초기화는 ObjectManager에서...
////////////////////////////////////////////////////////////////////////
void DirectiveSetManager::init()
	throw()
{
	__BEGIN_TRY

	load();

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////
// load()
// DB에서 모든 DirectiveSet을 로드한다. 
// MonsterAI 객체들은 로드된 DirectiveSet에 대한 포인터만을 가지게 된다.
////////////////////////////////////////////////////////////////////////
void DirectiveSetManager::load()
	throw()
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// 셋의 숫자를 읽어온다.
		pResult = pStmt->executeQuery("SELECT MAX(ID) FROM DirectiveSet");

		if (pResult->getRowCount() == 0) throw ("DirectiveSetManager::load() : 테이블에 없습니다.");

		pResult->next();
		m_nSetCount = pResult->getInt(1)+1;

		// 읽어들인 숫자만큼 메모리를 할당하고...
		if (m_ppSet==NULL)
		{
			m_ppSet = new (DirectiveSet*)[m_nSetCount];
			Assert(m_ppSet != NULL);
			for (uint i=0; i<m_nSetCount; i++)
			{
				m_ppSet[i] = NULL;
			}
		}

		// 각각의 directive를 읽어들인다.
		pResult = pStmt->executeQuery("SELECT ID, Name, Content, DeadContent FROM DirectiveSet");

		while (pResult->next())
		{
			uint   index    = pResult->getInt(1);
			string name     = pResult->getString(2);
			string text     = pResult->getString(3);
			string deadtext = pResult->getString(4);

			printf("ID[%d] Directive Loading Begin >> ", index);

			////////////////
			///filelog("Directive.txt", "===============================================");
			//filelog("Directive.txt", "Name:%s", name.c_str());
			////////////////

			createDirectiveSet(index, name, text, deadtext);

			printf("Loading End\n");
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// getDirectiveSet()
// 지정된 타입의 DirectiveSet의 포인터를 리턴한다.
////////////////////////////////////////////////////////////////////////
DirectiveSet* DirectiveSetManager::getDirectiveSet(uint index)
	throw()
{
	__BEGIN_TRY

	if (index >= m_nSetCount)
	{
		cerr << "DirectiveSetManager::getDirectiveSet() : Out of bounds, value = [" << index << "]" << endl;
		throw("DirectiveSetManager::getDirectiveSet() : Out of bounds!");
	}

	return m_ppSet[index];

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// createDirectiveSet()
// 문자열을 파싱해서 지정된 인덱스의 자리에다 DirectiveSet을 생성.
////////////////////////////////////////////////////////////////////////
void DirectiveSetManager::createDirectiveSet(uint index, const string& name, const string& text, const string& deadtext)
	throw()
{
	__BEGIN_TRY

	if (index >= m_nSetCount)
	{
		cerr << "DirectiveSetManager::createDirectiveSet() : Out of bounds!" << endl;
		throw("DirectiveSetManager::createDirectiveSet() : Out of bounds!");
	}

	// 이전의 DirectiveSet을 삭제하고, 새 것을 만든다.
	if (m_ppSet[index]==NULL)	// by sigi. 2002.9.26
	{
		//SAFE_DELETE(m_ppSet[index]);
		m_ppSet[index] = new DirectiveSet;
	}
	else
	{
		// 기존에 있던게 있다면.. 지운다.
		m_ppSet[index]->clear();
	}

	m_ppSet[index]->setName(name);

	string beginToken = "DIRECTIVE BEGIN";
	string endToken   = "DIRECTIVE END";
	uint   start      = 0;
	uint   end        = 0;

	while (end < text.size() - 1)
	{
		////////////////////////////////////////////////////////////
		// ex)
		// DIRECTIVE BEGIN
		//   (CONDITION:ImDying)
		//   (ACTION:Flee)
		// DIRECTIVE END
		// DIRECTIVE BEGIN
		//   (CONDITION:EnemyRangeMelee)
		//   (CONDITION:EnemyDying)
		//   (CONDITION:EnemyNotBloodDrained)
		//   (ACTION:UseSkill,BloodDrain,30)
		// DIRECTIVE END
		////////////////////////////////////////////////////////////

		start = text.find(beginToken, end);
		end   = text.find(endToken,   start+1);

		if (start > end) break;

		Directive* pDirective = new Directive;
		string     directive  = trim(text.substr(start+beginToken.size()+1, end-start-beginToken.size()-1));

		Assert(pDirective != NULL);

		uint i = 0, j = 0, k = 0;

		while (k < directive.size())
		{
			// Directive를 구성하는 액션이나 컨디션 중의 
			// 하나를 읽어들인다.
			i = directive.find_first_of('(', k);
			j = directive.find_first_of(':', i+1);
			k = directive.find_first_of(')', j+1);

			// 문자열의 끝을 초과했다면, 파싱을 중단한다.
			if (i > j || j > k) break;

			// identifier는 액션이냐, 컨디션이냐의 여부.
			// parameter는 그 뒤에 따라오는 인수이다.
			string identifier = directive.substr(i+1, j-i-1);
			string parameter  = directive.substr(j+1, k-j-1);

			if (identifier == "CONDITION")
			{
				parseDirectiveParameter(pDirective, parameter, MODE_CONDITION);
			}
			else if (identifier == "ACTION")
			{
				parseDirectiveParameter(pDirective, parameter, MODE_ACTION);
			}
			else
			{
				cerr << "DirectiveSetManager::createDirectiveSet() : 알 수 없는 IDENTIFIER" << endl;
				throw ("DirectiveSetManager::createDirectiveSet() : 알 수 없는 IDENTIFIER");
			}
		}

		m_ppSet[index]->addDirective(pDirective);
	}

	// 죽었을 때 하는 행동을 읽어들인다. 5란 숫자에 큰 의미는 없다.
	// 아무 행동도 하지 않을 때는 보통 0이지만, 무언가 액션이 들어가면 
	// 길이가 대강 50은 되리라고 생각은 하는데... 하옇튼 액션이 없는 
	// 경우에는 읽어들이지 않기 위해서, 하는 검사다. -- 김성민
	if (deadtext.size() > 5)
	{
		start = 0;
		end   = 0;

		while (end < deadtext.size() - 1)
		{
			////////////////////////////////////////////////////////////
			// ex)
			// DIRECTIVE BEGIN
			//   (CONDITION:ImDying)
			//   (ACTION:Flee)
			// DIRECTIVE END
			// DIRECTIVE BEGIN
			//   (CONDITION:EnemyRangeMelee)
			//   (CONDITION:EnemyDying)
			//   (CONDITION:EnemyNotBloodDrained)
			//   (ACTION:UseSkill,BloodDrain,30)
			// DIRECTIVE END
			////////////////////////////////////////////////////////////

			start = deadtext.find(beginToken, end);
			end   = deadtext.find(endToken,   start+1);

			if (start > end) break;

			Directive* pDirective = new Directive;
			string     directive  = trim(deadtext.substr(start+beginToken.size()+1, end-start-beginToken.size()-1));

			Assert(pDirective != NULL);

			uint i = 0, j = 0, k = 0;

			while (k < directive.size())
			{
				// Directive를 구성하는 액션이나 컨디션 중의 
				// 하나를 읽어들인다.
				i = directive.find_first_of('(', k);
				j = directive.find_first_of(':', i+1);
				k = directive.find_first_of(')', j+1);

				// 문자열의 끝을 초과했다면, 파싱을 중단한다.
				if (i > j || j > k) break;

				// identifier는 액션이냐, 컨디션이냐의 여부.
				// parameter는 그 뒤에 따라오는 인수이다.
				string identifier = directive.substr(i+1, j-i-1);
				string parameter  = directive.substr(j+1, k-j-1);

				if (identifier == "CONDITION")
				{
					parseDirectiveParameter(pDirective, parameter, MODE_CONDITION);
				}
				else if (identifier == "ACTION")
				{
					parseDirectiveParameter(pDirective, parameter, MODE_ACTION);
				}
				else
				{
					cerr << "DirectiveSetManager::createDirectiveSet() : 알 수 없는 IDENTIFIER" << endl;
					throw ("DirectiveSetManager::createDirectiveSet() : 알 수 없는 IDENTIFIER");
				}
			}

			m_ppSet[index]->addDeadDirective(pDirective);
		}
	}

	m_ppSet[index]->setAttackAir( m_ppSet[index]->hasCondition( DIRECTIVE_COND_ENEMY_ON_AIR ) );
	m_ppSet[index]->setSeeSafeZone( m_ppSet[index]->hasCondition( DIRECTIVE_COND_ENEMY_ON_SAFE_ZONE ) );

	if ( m_ppSet[index]->canSeeSafeZone() ) cout << index << " : can see safe zone" << endl;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// parseDirectiveParameter()
// 문자열을 파싱해서, 컨디션이나 액션을 만들어 Directive에 세팅한다.
////////////////////////////////////////////////////////////////////////
void DirectiveSetManager::parseDirectiveParameter(Directive* pDirective, const string& text, int mode)
	throw()
{
	__BEGIN_TRY

	uint oldpos     = 0;
	uint pos        = 0;
	uint paramCount = 0;

	while (oldpos < text.size() && pos < text.size())
	{
		// 연속된 파라미터는 ","로 구분된다.
		oldpos = pos;
		pos    = text.find_first_of(',', oldpos);

		// 컨디션 같은 경우에는 파라미터가 하나이기 때문에
		// ","를 찾으면 맥스 값이 무조건 나온다. 
		// 이걸로는 서브스트링 함수를 제대로 부를 수가 
		// 없기 때문에 문자열의 길이로 pos 값을 세팅해준다.
		if (pos == string::npos) pos = text.size();
		pos++;

		string token = text.substr(oldpos, (pos-1)-oldpos);

		switch (mode)
		{
			case MODE_CONDITION:
				if (paramCount != 0) 
				{
					cerr << "DirectiveSetManager::parseParameter() : There's two or more parameters in condition" << endl;
					cerr << "ParsingText: " << text.c_str() << endl;
					throw("DirectiveSetManager::parseParameter() : There's two or more parameters in condition");
				}
				pDirective->addCondition(getCondition(token));
				break;
			case MODE_ACTION:
				if (paramCount == 0)      pDirective->setAction(getAction(token));
				else if (paramCount == 1)
				{
					switch (pDirective->getAction())
					{
						case DIRECTIVE_ACTION_USE_SKILL :
							pDirective->setParameter(getParameter(token));
						break;

						case DIRECTIVE_ACTION_CHANGE_ENEMY :
						case DIRECTIVE_ACTION_MOVE_RANDOM :
						case DIRECTIVE_ACTION_SAY :
							pDirective->setParameter(atoi(token.c_str()));
						break;


						default :
							cerr << "DirectiveSetManager::parseParameter() : There's two or more parameters in condition" << endl;
							cerr << "ParsingText: " << text.c_str() << endl;
							throw Error("No Need Parameter!");
					}

					////////////////
					//if (pDirective->getAction() == DIRECTIVE_ACTION_USE_SKILL)
					//{
					//	filelog("Directive.txt", "%s", token.c_str());
					//}
					////////////////
				}
				else if (paramCount == 2) pDirective->setRatio(getRatio(token));
				break;	
			default:
				break;
		}

		paramCount++;
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// getCondition()
// 문자열을 받아 그에 해당하는 컨디션 상수를 리턴한다.
////////////////////////////////////////////////////////////////////////
int DirectiveSetManager::getCondition(const string& token)
	throw()
{
	__BEGIN_TRY

	for (int i=0; i<DIRECTIVE_COND_MAX; i++)
		if (DirectiveCondition2String[i] == token) return i;

	StringStream msg;
	msg << "DirectiveSetManager::getCondition() : Invalid condition string["
		<< token << "]";

	cerr << msg.toString() << endl;
	throw(msg.toString());
	return DIRECTIVE_COND_MAX;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// getAction()
// 문자열을 받아 그에 해당하는 액션 상수를 리턴한다.
////////////////////////////////////////////////////////////////////////
int DirectiveSetManager::getAction(const string& token)
	throw()
{
	__BEGIN_TRY
	
	for (int i=0; i<DIRECTIVE_ACTION_MAX; i++)
		if (DirectiveAction2String[i] == token) return i;

	cerr << "DirectiveSetManager::getAction() : Invalid action[" << token << "]" << endl;
	throw("DirectiveSetManager::getAction() : Invalid action");
	return DIRECTIVE_COND_MAX;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// getParameter()
// 문자열을 받아 그에 해당하는 파라미터를 리턴한다.
// 현재로서는 몬스터가 사용하는 스킬 타입 뿐이다.
////////////////////////////////////////////////////////////////////////
int DirectiveSetManager::getParameter(const string& token)
	throw()
{
	__BEGIN_TRY

	for (int i=0; i<SKILL_MAX; i++)
	{
		if (strcasecmp(token.c_str(), SkillTypes2String[i].c_str()) == 0)
			return i;
	}

	cerr << "DirectiveSetManager::getParameter() : Invalid parameter[" << token << "]" << endl;
	throw("DirectiveSetManager::getParameter() : Invalid parameter");

	return 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////
// getRatio()
// 문자열을 받아 그에 해당하는 확률값을 리턴한다. 백분율이다.
////////////////////////////////////////////////////////////////////////
int DirectiveSetManager::getRatio(const string& token)
	throw()
{
	__BEGIN_TRY

	int rValue = atoi(token.c_str());

	if (rValue < 0 || rValue > 100) 
	{
		cerr << "DirectiveSetManager::getRatio() : Invalid ratio value" << endl;
		throw ("DirectiveSetManager::getRatio() : Invalid ratio value");
	}

	return rValue;

	__END_CATCH
}


