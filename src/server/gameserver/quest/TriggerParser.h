#ifndef __TRIGGER_PARSER_H__
#define __TRIGGER_PARSER_H__

#include "Types.h"
#include "SXml.h"
#include <map>

class XMLTree;

class TriggerParser
{
public:
	TriggerParser() : m_pTargetTree(NULL), m_TargetScriptID(0), m_TargetContentID(0) { }
	void parseTrigger(const string& type, const string& condition, const string& action);

	bool parseElement(XMLTree* pTree, const string& key, const string& element);
	bool findText(XMLTree* pTree);

	XMLTree*	getResult() const { return m_pTargetTree; }

private:
	map<ScriptID_t, XMLTree*>	m_ScriptMap;
	XMLTree*					m_pTargetTree;
	uint						m_TargetScriptID, m_TargetContentID;
};

#endif
