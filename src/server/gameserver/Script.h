//////////////////////////////////////////////////////////////////////////////
// Filename    : Script.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "Types.h"
#include "Exception.h"

const uint SCRIPT_MAX_SUBJECTS = 15;
const uint SCRIPT_MAX_CONTENTS = 15;

//////////////////////////////////////////////////////////////////////////////
// class Script
//////////////////////////////////////////////////////////////////////////////

class Script 
{
public: 
	Script() throw();
	Script(const Script & script) throw();

	void	clearContents();

	const Script & operator =(const Script & script) throw();

public:
	ScriptID_t getScriptID(void) const { return m_ScriptID; }
	void setScriptID(ScriptID_t id) { m_ScriptID = id; }

	string getSubject(uint index) const throw();
	void addSubject(const string& subject, DWORD code=0) throw();

	DWORD getSubjectCode(uint index) const 			{ return m_SubjectCodes[index]; }
	void  setSubjectCode(uint index, DWORD code) 	{ m_SubjectCodes[index] = code; }


	string getContent(uint index) const throw();
	void addContent(const string& content, DWORD code=0) throw();
	
	// by sigi. 2002.12.3
	DWORD getContentCode(uint index) const 			{ return m_ContentCodes[index]; }
	void  setContentCode(uint index, DWORD code) 	{ m_ContentCodes[index] = code; }

	string getRandomSubject(void) const throw();

	uint getSubjectCount(void) const throw() { return m_SubjectCount; }
	uint getContentCount(void) const throw() { return m_ContentCount; }

	string toString() const throw();

private:
	ScriptID_t 	m_ScriptID;

	string m_Subjects[SCRIPT_MAX_SUBJECTS];
	DWORD  m_SubjectCodes[SCRIPT_MAX_SUBJECTS];

	string m_Contents[SCRIPT_MAX_CONTENTS];
	DWORD  m_ContentCodes[SCRIPT_MAX_CONTENTS];

	uint m_SubjectCount;
	uint m_ContentCount;
};

#endif
