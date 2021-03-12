//////////////////////////////////////////////////////////////////////////////
// Filename    : Script.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Script.h"
#include "StringStream.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Script::Script()
	
{
	m_SubjectCount = 0;
	m_ContentCount = 0;

	for (uint i=0; i<SCRIPT_MAX_SUBJECTS; i++)
		m_SubjectCodes[i] = 0;

	for (uint i=0; i<SCRIPT_MAX_CONTENTS; i++)
		m_ContentCodes[i] = 0;
}

//////////////////////////////////////////////////////////////////////////////
// copy constructor
//////////////////////////////////////////////////////////////////////////////
Script::Script (const Script & script)
	
{
	uint i;

	for (i=0; i<SCRIPT_MAX_SUBJECTS; i++)
	{
		m_Subjects[i] = script.m_Subjects[i];
		m_SubjectCodes[i] = script.m_SubjectCodes[i];
	}

	for (i=0; i<SCRIPT_MAX_CONTENTS; i++)
	{
		m_Contents[i] = script.m_Contents[i];
		m_ContentCodes[i] = script.m_ContentCodes[i];
	}

	m_SubjectCount = script.m_SubjectCount;
	m_ContentCount = script.m_ContentCount;
}


void Script::clearContents()
{
	m_ContentCount = 0;

	for (uint i=0; i<SCRIPT_MAX_CONTENTS; i++)
	{
		m_Contents[i].clear();
		m_ContentCodes[i] = 0;
	}

}

//////////////////////////////////////////////////////////////////////////////
// assignment operator
//////////////////////////////////////////////////////////////////////////////
const Script & Script::operator = (const Script & script)
	
{
	if (&script != this)
	{
		uint i=0;

		for (i=0; i<SCRIPT_MAX_SUBJECTS; i++)
		{
			m_Subjects[i] = script.m_Subjects[i];
			m_Subjects[i] = script.m_SubjectCodes[i];
		}

		for (i=0; i<SCRIPT_MAX_CONTENTS; i++)
		{
			m_Contents[i] = script.m_Contents[i];
			m_ContentCodes[i] = script.m_ContentCodes[i];
		}

		m_SubjectCount = script.m_SubjectCount;
		m_ContentCount = script.m_ContentCount;
	}

	return *this;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string Script::getSubject(uint index) const 
	
{
	if (index >= SCRIPT_MAX_SUBJECTS || index >= m_SubjectCount)
	{
		cerr << "Script::getSubject() : Out of bounds" << endl;
		throw ("Script::getSubject() : Out of bounds");
	}

	return m_Subjects[index];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Script::addSubject(const string& content, DWORD code) 
	
{
	if (m_SubjectCount >= SCRIPT_MAX_SUBJECTS)
	{
		cerr << "Script::addSubject() : Out of bounds" << endl;
		throw ("Script::addSubject() : Out of bounds");
	}

	m_Subjects[m_SubjectCount] = content;
	m_SubjectCodes[m_SubjectCount] = code;
	m_SubjectCount++;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string Script::getContent(uint index) const 
	
{
	if (index >= SCRIPT_MAX_CONTENTS || index >= m_ContentCount)
	{
		cerr << "Script::getContent() : Out of bounds" << endl;
		throw ("Script::getContent() : Out of bounds");
	}

	return m_Contents[index];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Script::addContent(const string& content, DWORD code) 
	
{
	if (m_ContentCount >= SCRIPT_MAX_CONTENTS)
	{
		cerr << "Script::addContent() : Out of bounds" << endl;
		throw ("Script::addContent() : Out of bounds");
	}

	m_Contents[m_ContentCount] = content;
	m_ContentCodes[m_ContentCount] = code;
	m_ContentCount++;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string Script::getRandomSubject(void) const
	
{
	int rvalue = rand()%m_SubjectCount;
	return m_Subjects[rvalue];
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string Script::toString () const
	
{
	StringStream msg;
	uint         i = 0;

	msg << "Script(";

	for (i=0; i<SCRIPT_MAX_SUBJECTS; i++)
		msg << "Subject" << (int)i << ":" << m_Contents[i] << ",";

	for (i=0; i<SCRIPT_MAX_CONTENTS; i++)
		msg << "Content" << (int)i << ":" << m_Contents[i] << ",";

	msg << ")";

	return msg.toString();
}

