////////////////////////////////////////////////////////////////////////////////
// Filename    : PropertyBuffer.h
// Written By  : 
// Description :
// DB에 TEXT 로 저장된 Condition/Action 필드를 파싱해준다.
// Properties 와 다른 점은, Properties 는 파일 내용을 모두 파싱해서 map 으로
// 변환한 다음, getProperty() 가 호출되면 적절한 value 를 리턴하지만,
// PropertyBuffer 는 내부에 큰 스트링의 버퍼를 두고, getProperty()가 호출될
// 때마다 버퍼의 앞에서부터 파싱을 한번씩 실행한다는 점이다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __PROPERTY_BUFFER_H__
#define __PROPERTY_BUFFER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class PropertyBuffer;
//////////////////////////////////////////////////////////////////////////////

class PropertyBuffer 
{
public:
	static const char Comment;
	static const char Separator;
	static const char EOL;
	static const char* WhiteSpaces;
	static const char* SpaceTab;
	
public:
	PropertyBuffer(const string & buffer) throw();
	~PropertyBuffer() throw();
	
public:
	string getProperty(string key) throw(NoSuchElementException, Error);
	int getPropertyInt(string key) throw(NoSuchElementException, Error);

	bool getProperty(string key, string& value) throw(NoSuchElementException, Error);
	bool getPropertyInt(string key, int& value) throw(NoSuchElementException, Error);

	string toString() const throw();
	
private:
	uint   m_Index;
	string m_Buffer;
	
};

#endif
