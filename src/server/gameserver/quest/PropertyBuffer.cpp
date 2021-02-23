////////////////////////////////////////////////////////////////////////////////
// Filename    : PropertyBuffer.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "PropertyBuffer.h"
#include "Utility.h"			// trim(), getline()


////////////////////////////////////////////////////////////////////////////////
// static constant variables
////////////////////////////////////////////////////////////////////////////////
const char PropertyBuffer::Comment = '#';
const char PropertyBuffer::Separator = ':';
const char PropertyBuffer::EOL = '\n';
const char * PropertyBuffer::WhiteSpaces = " \t\n";
const char * PropertyBuffer::SpaceTab = " \t";

	
////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
PropertyBuffer::PropertyBuffer (const string & buffer) 
	throw ()
{
	m_Index  = 0;
	m_Buffer = buffer;
}
	

////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
PropertyBuffer::~PropertyBuffer () 
	throw ()
{
}

string PropertyBuffer::getProperty (string key)
	    throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	uint bufferLen = m_Buffer.size();

	while (m_Index < bufferLen)
	{
		string line = trim(getline(m_Buffer , m_Index));

		// 빈 라인 또는 코멘트 라인이 아닌 경우
		if (line.size() != 0 && line[0] != Comment)
		{
			uint i = line.find(Separator);

			if (i == string::npos)
			{
				throw Error("missing separator");
			}

			string paramName  = trim(line.substr(0 , i - 1));

			if (paramName == key)
			{
				return trim(line.substr(i + 1));
			}
			else
			{
				throw NoSuchElementException(key);
			}
		}
	}

	cout << "PropertyBuffer::getProperty() : thers is no [" << key << "] element." << endl;
	throw NoSuchElementException(key);

	__END_CATCH
}

int PropertyBuffer::getPropertyInt (string key)
	    throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	return atoi(getProperty(key).c_str());

	__END_CATCH
}

bool PropertyBuffer::getProperty (string key, string& value)
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	uint bufferLen = m_Buffer.size();

    while (m_Index < bufferLen)
    {
        string line = trim(getline(m_Buffer , m_Index));

        // 빈 라인 또는 코멘트 라인이 아닌 경우
        if (line.size() != 0 && line[0] != Comment)
        {
            uint i = line.find(Separator);

            if (i == string::npos)
            {
				return false;
            }

            string paramName  = trim(line.substr(0 , i - 1));

            if (paramName == key)
            {
            	value = trim(line.substr(i + 1));
				return true;
            }
            else
            {
				return false;
            }
        }
    }

	return false;

	__END_CATCH
}

bool PropertyBuffer::getPropertyInt (string key, int& value)
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	string rstring;
	
	if (getProperty(key, rstring))
	{
		value = atoi(rstring.c_str());
		return true;
	}

	return false;

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string PropertyBuffer::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "PropertyBuffer("
			<< "Index:"   << m_Index
			<< ",Buffer:" << m_Buffer
			<< ")";

	return msg.toString();	

	__END_CATCH
}
