////////////////////////////////////////////////////////////////////////////////
// Filename    : VariableBuffer.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VARIABLE_BUFFER_H__
#define __VARIABLE_BUFFER_H__

#include "Types.h"
#include "Exception.h"

#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class VariableBuffer;
//////////////////////////////////////////////////////////////////////////////

class VariableInfo;

class VariableBuffer 
{
public:
	static const char Comment;
	static const char Separator;
	static const char EOL;
	static const char* WhiteSpaces;
	static const char* SpaceTab;
	
public:
	VariableBuffer(const string & buffer) throw();
	~VariableBuffer() throw();
	
public:
	int getCount() const { return m_VariableInfos.size(); }
	VariableInfo* getVariableInfo( int index ) throw(OutOfBoundException, Error);

	string toString() const throw();
	
private:
	void parse() throw (Error);
	
	void clear();

private:
	vector<VariableInfo*> m_VariableInfos;

	string m_Buffer;
};

#endif
