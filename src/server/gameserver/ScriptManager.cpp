//////////////////////////////////////////////////////////////////////////////
// Filename    : ScriptManager.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ScriptManager.h"
#include "DB.h"
#include "SXml.h"
#include "Properties.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// load from database with NPC ID
//////////////////////////////////////////////////////////////////////////////
void ScriptManager::load (const string & ownerID) 
	throw (Error)
{
	__BEGIN_TRY
	
	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		//pResult = pStmt->executeQuery("SELECT ScriptID, Subject, Content FROM Script WHERE OwnerID='%s'", ownerID.c_str());
		pResult = pStmt->executeQuery("SELECT ScriptID, OwnerID, Subject, Content FROM Script ORDER BY ScriptID");
//		XMLTree* pTree = new XMLTree("Scripts");

		while (pResult->next())
		{
			ScriptID_t scriptID = pResult->getInt(1);
			string	   owner	= pResult->getString(2);
			string     subject  = pResult->getString(3);
			string     content  = pResult->getString(4);
			Script*    pScript  = new Script;
			XMLTree*	pChild = new XMLTree("Script");

			pScript->setScriptID(scriptID);
			pChild->AddAttribute("ScriptID", scriptID);
//			pChild->AddAttribute("Owner", owner);

			if ( m_XMLS[owner] == NULL ) m_XMLS[owner] = new XMLTree("Scripts");

			string     seperator    = "**";
			uint       start        = 0;
			uint       end          = 0;
			string     msg;

			////////////////////////////////////////////////////////////
			// subject¸¦ ÆÄ½ÌÇÑ´Ù.
			////////////////////////////////////////////////////////////
			start = 0;
			end   = 0;

			while (end < subject.size())
			{
				start = end;
				end   = subject.find(seperator, start);

				if (end == string::npos) end = subject.size();
				end++;

				msg = trim(subject.substr(start, end-start-1));

				pScript->addSubject(msg);

				XMLTree* pSubject = new XMLTree("Subject");
				pSubject->SetText(msg);
				pChild->AddChild(pSubject);

				//cout << "SUBJECT:" << msg << endl;
			}

			////////////////////////////////////////////////////////////
			// content¸¦ ÆÄ½ÌÇÑ´Ù.
			////////////////////////////////////////////////////////////
			start = 0;
			end   = 0;
			uint answerid = 0;

			while (end < content.size())
			{
				start = end;
				end   = content.find(seperator, start);

				if (end == string::npos) end = content.size();
				end++;

				msg = trim(content.substr(start, end-start-1));

				pScript->addContent(msg);

				end++;

				XMLTree* pContent = new XMLTree("Content");
				pContent->SetText(msg);
				pContent->AddAttribute("AnswerID", ++answerid);
				pChild->AddChild(pContent);

				//cout << "CONTENT:" << msg << endl;
			}

			setScript(scriptID, pScript);
			m_XMLS[owner]->AddChild(pChild);
			Assert( m_ScriptXMLs[scriptID] == NULL );
			m_ScriptXMLs[scriptID] = pChild;
//			pTree->AddChild(pChild);
		}

//		pTree->SaveToFile( (g_pConfig->getProperty("HomePath") + "/data/Script.xml").c_str() );
//		SAFE_DELETE( pTree );

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get script
//////////////////////////////////////////////////////////////////////////////
Script* ScriptManager::getScript (ScriptID_t scriptID) const 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	hash_map<ScriptID_t , Script*>::const_iterator itr = m_Scripts.find(scriptID);

	if (itr == m_Scripts.end()) 
	{
		StringStream msg;
		msg << "No Such Script(ID:" << scriptID << ") exist...";
		cerr << msg.toString() << endl;
		throw NoSuchElementException(msg.toString());
	}

	return itr->second;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// set script
//////////////////////////////////////////////////////////////////////////////
void ScriptManager::setScript (ScriptID_t scriptID , Script* pScript) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	hash_map<ScriptID_t , Script*>::iterator itr = m_Scripts.find(scriptID);

	if (itr != m_Scripts.end()) 
	{
		StringStream msg;
		msg << scriptID << " script already exist.";
		throw DuplicatedException(msg.toString());
	}

	m_Scripts[scriptID] = pScript;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string ScriptManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ScriptManager(";

	hash_map<ScriptID_t, Script*>::const_iterator i = m_Scripts.begin();
	for (; i != m_Scripts.end() ; i++) 
	{
		msg << "(ScriptID:" << (int)(i->first) << ",";
		msg << i->second->toString() << ")";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
ScriptManager* g_pPublicScriptManager = NULL;
