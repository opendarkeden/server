#include "TriggerParser.h"
#include "Utility.h"
#include "Assert.h"
#include "ScriptManager.h"

const char Comment = '#';
const char Separator = ':';
const char EOL = '\n';
const char * WhiteSpaces = " \t\n";
const char * SpaceTab = " \t";

void TriggerParser::parseTrigger(const string& type, const string& condition, const string& action)
{
	m_TargetScriptID = 0;
	m_TargetContentID = 0;

	XMLTree* pTrigger = new XMLTree("Trigger");
	XMLTree* pCondition = new XMLTree("Condition");
	XMLTree* pAction = new XMLTree("Action");

	Assert(parseElement(pCondition, "ConditionType", condition));
	Assert(parseElement(pAction, "ActionType", action));

	pTrigger->AddChild(pCondition);
	pTrigger->AddChild(pAction);

	if ( m_pTargetTree == NULL ) m_pTargetTree = new XMLTree("Triggers");
	if ( m_TargetScriptID == 0 )
	{
		m_pTargetTree->AddChild(pTrigger);
	}
	else
	{
		XMLTree* pScriptTree = m_ScriptMap[m_TargetScriptID];
		if ( pScriptTree  == NULL )
		{
			m_ScriptMap[m_TargetScriptID] = pScriptTree = new XMLTree( *(g_pPublicScriptManager->getScriptXML(m_TargetScriptID)) );
			m_pTargetTree->AddChild( pScriptTree );
		}

		for ( size_t i=0; i<pScriptTree->GetChildCount(); ++i )
		{
			XMLTree* pScriptChild = pScriptTree->GetChild(i);
			if ( pScriptChild != NULL && pScriptChild->GetName() == "Content" && pScriptChild->GetAttribute("AnswerID")->ToInt() == m_TargetContentID )
			{
				pScriptChild->AddChild( pTrigger );
			}
		}
	}
}

bool TriggerParser::parseElement(XMLTree* pTree, const string& key, const string& element)
{
	uint len = element.size();
	uint index = 0;

	XMLTree* pChild = NULL;

	while ( index < len )
	{
		string line = trim(getline(element, index));
		if ( line.size() == 0 || line[0] == Comment ) continue;

		uint i = line.find(Separator);

		if ( i == string::npos ) return false;
		string name = trim(line.substr(0, i-1));
		string value = trim(line.substr(i+1));

		if ( name == key )
		{
			if ( pChild != NULL )
			{
				if ( findText( pChild ) ) pTree->AddChild( pChild );
			}

			pChild = new XMLTree( value );
		}
		else
		{
			if ( pChild == NULL ) return false;
			pChild->AddAttribute(name, value);
		}
	}

	if ( findText( pChild ) ) pTree->AddChild( pChild );

	return true;
}

bool TriggerParser::findText(XMLTree* pTree)
{
/*	if ( pTree->GetName() == "Ask" || pTree->GetName() == "AskVariable" )
	{
		uint scriptID = 0;
		Assert(pTree->GetAttribute("ScriptID", scriptID));
		pTree->SetText(g_pPublicScriptManager->getScript( scriptID )->getSubject(0));
	}*/
	if ( pTree->GetName() == "AnsweredBy" )
	{
		uint scriptID = 0, answerID = 0;
		Assert(pTree->GetAttribute("ScriptID", scriptID));
		Assert(pTree->GetAttribute("AnswerID", answerID));
		m_TargetScriptID = scriptID;
		m_TargetContentID = answerID;
		return false;
//		pTree->SetText(g_pPublicScriptManager->getScript( scriptID )->getContent(answerID-1));
	}
	if ( pTree->GetName() == "RandomSay" )
	{
		uint start = 0, end = 0;
		Assert(pTree->GetAttribute("StartScriptID", start));
		Assert(pTree->GetAttribute("EndScriptID", end));

		for ( uint i=start; i<=end; ++i )
		{
			XMLTree* pScriptTree = m_ScriptMap[i];
			if ( pScriptTree  == NULL )
			{
				m_ScriptMap[i] = pScriptTree = new XMLTree( *(g_pPublicScriptManager->getScriptXML(i)) );
				m_pTargetTree->AddChild( pScriptTree );
			}
		}
	}

	return true;
}
