//////////////////////////////////////////////////////////////////////////////
// Filename    : ScriptManager.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SCRIPT_MANAGER_H__
#define __SCRIPT_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Script.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class ScriptManager
//
// 모든 NPC들이 공유하는 public script 또는 특정 NPC 만이 사용하는 private script db
// 를 나타내는 script manager 이다.
//////////////////////////////////////////////////////////////////////////////

class XMLTree;

class ScriptManager 
{
public:
	void init() throw(Error) { load("PUBLIC"); }
	void load(const string & name) throw(Error);

public:
	Script* getScript(ScriptID_t scriptID) const throw(NoSuchElementException, Error);
	void setScript(ScriptID_t scriptID, Script* pScript) throw(DuplicatedException, Error);

	string toString() const throw();

	// 갖다 쓰지 마세요.
	XMLTree*	getXML(const string& owner) { return m_XMLS[owner]; }
	XMLTree*	getScriptXML(ScriptID_t scriptID) { return m_ScriptXMLs[scriptID]; }

private:
	hash_map< ScriptID_t, Script* > m_Scripts; // hash map of script
	hash_map< string, XMLTree* > m_XMLS;
	hash_map< ScriptID_t, XMLTree* > m_ScriptXMLs;

};

// global variable declaration
extern ScriptManager* g_pPublicScriptManager;

#endif
