//////////////////////////////////////////////////////////////////////////////
/// \file XML.cpp
/// \author excel96
/// \date 2003.7.25
///
/// \todo
/// \bug
/// \warning
//////////////////////////////////////////////////////////////////////////////

//#include "SFCPCH.h"
#include "SXml.h"
#include <iostream>
#include <iosfwd>
#include <assert.h>
#include <cstdio>
#include <cstdarg>
#include <ctime>

void itoa( int value, char* buf, int r )
{
	if ( r == 10 )
	{
		sprintf(buf, "%d", value);
	}
	else
	{
		sprintf(buf, "%x", value);
	}
}

//using namespace std;

//#pragma warning (push, 1)
	#include "xercesc/sax/SAXParseException.hpp"
	#include "xercesc/sax/SAXException.hpp"
	#include "xercesc/framework/MemBufInputSource.hpp"
	#include "xercesc/util/PlatformUtils.hpp"
	#include "xercesc/util/XMLString.hpp"
	#include "xercesc/sax2/XMLReaderFactory.hpp"
	#include "xercesc/sax2/SAX2XMLReader.hpp"
	#include "xercesc/sax2/Attributes.hpp"
	#include "xercesc/sax2/DefaultHandler.hpp"
//#pragma warning (pop)

//#pragma warning(disable:4100)

XERCES_CPP_NAMESPACE_USE

//////////////////////////////////////////////////////////////////////////////
/// \class XMLUtil
/// \brief
//////////////////////////////////////////////////////////////////////////////

class XMLUtil
{
public:
	static string trim(const string& str);
	static void filelog(char* fmt, ...);
	static string WideCharToString(const XMLCh * wstr, int wstrlen = -1);
};


//////////////////////////////////////////////////////////////////////////////
/// \class StrX
/// \brief 
//////////////////////////////////////////////////////////////////////////////

class StrX
{
private:
	char* m_pCSTR; ///< 내부 문자열 버퍼

public:
	StrX(const XMLCh* const toTranscode) { m_pCSTR = XMLString::transcode(toTranscode); }
	~StrX() { XMLString::release(&m_pCSTR); }

	const char* c_str() const { return m_pCSTR; }
	string	toString() const { return m_pCSTR; }
};

//////////////////////////////////////////////////////////////////////////////
/// \class XMLTreeGenerator
/// \brief 
//////////////////////////////////////////////////////////////////////////////

class XMLTreeGenerator : public DefaultHandler
{
private:
	XMLTree* m_pRoot;   ///< 최상위 노드
	XMLTree* m_pBuffer; ///< XML 파싱용 임시 노드


public:
	XMLTreeGenerator( XMLTree* pTree );
	virtual ~XMLTreeGenerator();


public:
	// Handlers for the SAX ContentHandler interface
	void startElement( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs );
	void endElement( const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname );
	void characters( const XMLCh* const chars, const unsigned int length );
	void ignorableWhitespace( const XMLCh* const, const unsigned int ) {}
	void resetDocument();

	// Handlers for the SAX ErrorHandler interface
	void warning( const SAXParseException& e );
	void error( const SAXParseException& e );
	void fatalError( const SAXParseException& e );


private:
	XMLTreeGenerator( const XMLTreeGenerator& ) {}
	XMLTreeGenerator& operator = ( const XMLTreeGenerator& ) { return *this; }
};

//////////////////////////////////////////////////////////////////////////////
/// \class XMLParser
/// \brief 
//////////////////////////////////////////////////////////////////////////////

class XMLParser
{
private:
	DefaultHandler* m_pHandler;


public:
	XMLParser(XMLTree* pTree);
	virtual ~XMLParser();


public:
	/// \brief 지정된 위치에 있는 파일 또는 웹 문서를 파싱한다.
	void parseURL(const char* pURL);

	/// \brief 인수로 넘겨지는 문자열을 XML 문서로 가정하고 파싱한다.
	void parse(const char* buffer);
};


static const char* XML_ERROR_FILENAME = "__XMLError.log";

//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// \param str 
/// \return string 
//////////////////////////////////////////////////////////////////////////////
string XMLUtil::WideCharToString(const XMLCh * wstr, int wstrlen)
{
//	return StrX( wstr ).c_str();

/*	if ( wstrlen == -1 )
	{
		wstrlen = (int)wcslen(wstr);
	}*/

	// test korean with WideCharToMultiByte
	//	int WideCharToMultiByte(
	//		UINT CodePage,            // code page
	//		DWORD dwFlags,            // performance and mapping flags
	//		LPCWSTR lpWideCharStr,    // wide-character string
	//		int cchWideChar,          // number of chars in string
	//		LPSTR lpMultiByteStr,     // buffer for new string
	//		int cbMultiByte,          // size of buffer
	//		LPCSTR lpDefaultChar,     // default for unmappable chars
	//		LPBOOL lpUsedDefaultChar  // set when default char used
	//	);
	//
	//lpDefaultChar 
	//	[in] Points to the character used if a wide character cannot be represented in the specified code page. 
	//  If this parameter is NULL, a system default value is used. 
	//  The function is faster when both lpDefaultChar and lpUsedDefaultChar are NULL. 
	//	For the code pages mentioned in dwFlags, lpDefaultChar must be NULL, 
	//  otherwise the function fails with ERROR_INVALID_PARAMETER. 

	//	lpUsedDefaultChar 
	//	[in] Points to a flag that indicates whether a default character was used. 
	//  The flag is set to TRUE if one or more wide characters in the source string 
	//  cannot be represented in the specified code page. Otherwise, the flag is set to FALSE. 
	//  This parameter may be NULL. The function is faster when both lpDefaultChar and lpUsedDefaultChar are NULL. 
	//	For the code pages mentioned in dwFlags, lpUsedDefaultChar must be NULL, 
	//  otherwise the function fails with ERROR_INVALID_PARAMETER. 

	// 최소한의 복사를 줄이기 위해서 스트링을 준비. 	
/*	string strBuffer;
	strBuffer.reserve( wstrlen * 2 + 1 );		// capacity 를 충분하게.. 
	int nCopied = WideCharToMultiByte(
		CP_OEMCP,
		WC_COMPOSITECHECK,
		wstr,									// wide string
		wstrlen,								// length of wide string
		const_cast<LPSTR>(strBuffer.data()),	// mbcs string (unicode)
		(int)strBuffer.capacity(),					// length of mbcs string
		NULL,									// NULL 이 빠르다는데?
		NULL );
	strBuffer[nCopied] = 0;
	strBuffer._Mysize = nCopied;				// 수동으로 지정해야 한다.

	return strBuffer;*/
	return StrX(wstr).toString();
}

string XMLUtil::trim(const string& str)
{
	if (str.size() == 0) return "";

	static const char * WhiteSpaces = " \t\n\r";
	size_t begin = str.find_first_not_of(WhiteSpaces);
	size_t end = str.find_last_not_of(WhiteSpaces);

	if (begin == string::npos)
	{
		if (end == string::npos) return "";
		else begin = 0;
	}
	else if (end == string::npos)
	{
		end = str.size();
	}

	return str.substr(begin , end - begin + 1);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// \param fmt 
/// \param ... 
//////////////////////////////////////////////////////////////////////////////
void XMLUtil::filelog(char* fmt, ...)
{
	ofstream file(XML_ERROR_FILENAME, ios::out | ios::app);
	if (file.is_open())
	{
		va_list valist;
		va_start(valist, fmt);
		char message_buffer[30000] = {0, };
		int nchars = vsnprintf(message_buffer, 30000, fmt, valist);
		if (nchars == -1 || nchars > 30000)
		{
			filelog(NULL, "filelog buffer overflow!");
			throw ("filelog() : more buffer size needed for log");
		}
		va_end(valist);

		time_t now = time(0);
		char time_buffer[256] = {0, };
		sprintf(time_buffer, "%s : ", ctime(&now));

		file.write(time_buffer, (streamsize)strlen(time_buffer));
		file.write(message_buffer, (streamsize)strlen(message_buffer));
		file.write("\n", (streamsize)strlen("\n"));
	}
}

//////////////////////////////////////////////////////////////////////////////
//
//	XMLAttribute
//
//////////////////////////////////////////////////////////////////////////////

XMLAttribute::XMLAttribute( const string &name, const string &value )
: m_Name( name ), m_Value( value )
{
}

XMLAttribute::~XMLAttribute()
{
}

void
XMLAttribute::SetValue( string value )
{
	m_Value = value;
}

const char*
XMLAttribute::GetName() const
{
	return m_Name.c_str();
}

const char*
XMLAttribute::ToString() const
{
	return m_Value.c_str();
}

const int
XMLAttribute::ToInt() const
{
	return atoi( m_Value.c_str() );
}

const DWORD
XMLAttribute::ToHex() const
{
	return strtoul( m_Value.c_str(), NULL, 16 );
}

const bool
XMLAttribute::ToBool() const
{
	return ( m_Value == "true" || m_Value == "TRUE" ) ? true : false;
}

const double	
XMLAttribute::ToDouble() const
{
	return atof( m_Value.c_str() );
}

const float
XMLAttribute::ToFloat() const
{
	return (float)atof( m_Value.c_str() );
}


//////////////////////////////////////////////////////////////////////////////
//
//	XMLTree
//
//////////////////////////////////////////////////////////////////////////////

XMLTree::XMLTree()
: m_pParent( NULL )
{
}

XMLTree::XMLTree( const string& name )
: m_Name( name ), m_pParent( NULL )
{
}

XMLTree::XMLTree( const XMLTree& xmlTree )
	: m_Name(xmlTree.m_Name), m_Text(xmlTree.m_Text), m_pParent(NULL)
{
	ATTRIBUTES_VECTOR::const_iterator aitr = xmlTree.m_AttributesVector.begin();

	for ( ; aitr != xmlTree.m_AttributesVector.end() ; ++aitr )
	{
		AddAttribute( (*aitr)->GetName(), (*aitr)->ToString() );
	}

	CHILDREN_VECTOR::const_iterator citr = xmlTree.m_ChildrenVector.begin();

	for ( ; citr != xmlTree.m_ChildrenVector.end() ; ++citr )
	{
		XMLTree* pNewChild = new XMLTree( **citr );
		AddChild( pNewChild );
	}
}

XMLTree::~XMLTree()
{
	Release();
}

const string&
XMLTree::GetName() const
{
	return m_Name;
}

void
XMLTree::SetName( const string& name )
{
	m_Name = name;
}

const string&
XMLTree::GetText() const
{
	return m_Text;
}

void
XMLTree::SetText( const string& text )
{
	m_Text = text;
}

const XMLTree*
XMLTree::GetParent() const
{
	return m_pParent;
}

void
XMLTree::SetParent( XMLTree* pParent )
{
	m_pParent = pParent;
}

void XMLTree::AddAttribute( const string& name, const string& value )
{
	ATTRIBUTES_MAP::iterator itr = m_AttributesMap.find( name );
	
	if ( itr == m_AttributesMap.end() )
	{
		XMLAttribute *pAttr = new XMLAttribute( name, value );
		
		m_AttributesVector.push_back( pAttr );
		m_AttributesMap.insert( ATTRIBUTES_MAP::value_type( name, pAttr ) );
	}
	else
	{
		XMLAttribute *pAttr = itr->second;
		pAttr->SetValue( value );
	}
}

void XMLTree::AddAttribute( const string& name, const char *value )
{
	AddAttribute( name, string(value) );
}

void XMLTree::AddAttribute( const string& name, const int& value )
{
	char szTemp[20];
	itoa( value, szTemp, 10 );
	AddAttribute( name, string(szTemp) );
}

void XMLTree::AddAttribute( const string& name, const unsigned int& value, const bool bHex )
{
	char szTemp[20];
	if( bHex == true )
		itoa( value, szTemp, 16 );
	else
		itoa( value, szTemp, 10 );

	AddAttribute( name, string(szTemp) );
}

void XMLTree::AddAttribute( const string& name, const DWORD& value, const bool bHex )
{
	char szTemp[20];
	if( bHex == true )
		itoa( value, szTemp, 16 );
	else
		itoa( value, szTemp, 10 );

	AddAttribute( name, string(szTemp) );
}

void XMLTree::AddAttribute( const string& name, const float& value )
{
	char szTemp[512];
	sprintf( szTemp, "%f", value );
	AddAttribute( name, string(szTemp) );
}

void XMLTree::AddAttribute( const string& name, const double& value )
{
	char szTemp[512];
	sprintf( szTemp, "%f", value );
	AddAttribute( name, string(szTemp) );
}

void XMLTree::AddAttribute( const string& name, const bool& value )
{
	if( value == true )
		AddAttribute( name, string("true") );
	else
		AddAttribute( name, string("false") );
}

XMLAttribute *
XMLTree::GetAttribute( const string& name ) const
{
	if(m_AttributesMap.empty() == true)
		return NULL;

	ATTRIBUTES_MAP::const_iterator itr = m_AttributesMap.find( name );

	if( itr == m_AttributesMap.end() )
		return NULL;

	return itr->second;
}

const bool
XMLTree::GetAttribute( const string& name, string &value )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	value = pAttr->ToString();

	return true;
}

const bool
XMLTree::GetAttribute( const string& name, int &value )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	value = pAttr->ToInt();

	return true;
}

const bool
XMLTree::GetAttribute( const string& name, unsigned int &value, const bool bHex )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	if( bHex == true )
		value = pAttr->ToHex();
	else
		value = pAttr->ToInt();

	return true;
}

const bool
XMLTree::GetAttribute( const string& name, DWORD &value, const bool bHex )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	if( bHex == true )
		value = pAttr->ToHex();
	else
		value = pAttr->ToInt();

	return true;
}

const bool
XMLTree::GetAttribute( const string& name, float &value )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	value = pAttr->ToFloat();

	return true;
}

const bool
XMLTree::GetAttribute( const string& name, double &value )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	value = pAttr->ToDouble();

	return true;
}

const bool
XMLTree::GetAttribute( const string& name, bool &value )
{
	const XMLAttribute *pAttr = GetAttribute( name );

	if( pAttr == NULL )
		return false;

	value = pAttr->ToBool();

	return true;
}

XMLTree*
XMLTree::AddChild( const string& name )
{
	CHILDREN_MAP::iterator itr = m_ChildrenMap.find( name );

	XMLTree *pTree = new XMLTree( name );

	pTree->SetParent( this );
	m_ChildrenVector.push_back( pTree );

	if ( itr == m_ChildrenMap.end() )
	{
		m_ChildrenMap.insert( CHILDREN_MAP::value_type( name, pTree ) );
	}

	return pTree;
}

XMLTree*
XMLTree::AddChild( XMLTree* pChild )
{
	pChild->SetParent( this );
	m_ChildrenVector.push_back( pChild );
	m_ChildrenMap[pChild->GetName()] = pChild;
	return pChild;
}

XMLTree*
XMLTree::GetChild( const string& name ) const
{
	CHILDREN_MAP::const_iterator itr = m_ChildrenMap.find( name );

	if ( itr == m_ChildrenMap.end() )
		return NULL;

	return itr->second;
}

XMLTree*
XMLTree::GetChild( size_t index ) const
{
	return ( ( index < m_ChildrenVector.size() ) ? m_ChildrenVector[index] : NULL );
}

const size_t
XMLTree::GetChildCount() const
{
	return m_ChildrenVector.size();
}

void XMLTree::Release()
{
	ATTRIBUTES_VECTOR::iterator itr = m_AttributesVector.begin();
	ATTRIBUTES_VECTOR::iterator endItr = m_AttributesVector.end();

	while(itr != endItr)
	{
		delete (*itr);
		itr++;
	}

	m_AttributesMap.clear();
	m_AttributesVector.clear();

	CHILDREN_VECTOR::iterator itr2 = m_ChildrenVector.begin();
	CHILDREN_VECTOR::iterator endItr2 = m_ChildrenVector.end();

	while(itr2 != endItr2)
	{
		delete (*itr2);
		itr2++;
	}

	m_ChildrenMap.clear();
	m_ChildrenVector.clear();
}

void
XMLTree::LoadFromFile( const char *pFilename )
{
	XMLParser parser( this );
	parser.parseURL( pFilename );
}

void
XMLTree::LoadFromMem( const char *pBuffer )
{
	XMLParser parser( this );
	parser.parse( pBuffer );
}

void
XMLTree::SaveToFile( const char* pFilename )
{
	ofstream file( pFilename, ios::out | ios::trunc );

	if ( file == NULL ) return;

	file << "<?xml version=\"1.0\" encoding=\"EUC-KR\"?>" << endl;
	
	Save(file, 0);
}

void
XMLTree::Save( ofstream& file, size_t indent )
{
	for ( size_t i = 0; i < indent; i++ )
		file << "\t";

	file << "<" << m_Name;

	ATTRIBUTES_VECTOR::iterator itr = m_AttributesVector.begin();
	ATTRIBUTES_VECTOR::iterator endItr = m_AttributesVector.end();

	while( itr != endItr)
	{
		file << " " << (*itr)->GetName() << "='" << (*itr)->ToString() << "'";

		itr++;
	}

	if (m_ChildrenVector.empty() == true && GetText().empty() == true)
	{
		file << "/>" << endl;
	}
	else
	{
		file << ">" << GetText();

		if(m_ChildrenVector.empty() == true)
		{
			file << "</" << m_Name << ">" << endl;
		}
		else
		{
			file << endl;

			CHILDREN_VECTOR::iterator itr = m_ChildrenVector.begin();
			CHILDREN_VECTOR::iterator endItr = m_ChildrenVector.end();

			while( itr != endItr)
			{
				(*itr)->Save( file, indent + 1 );

				itr++;
			}

			for ( size_t i = 0; i < indent; i++ )
				file << "\t";

			file << "</" << m_Name << ">" << endl;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////
//
//	XMLTreeGenerator
//
//////////////////////////////////////////////////////////////////////////////

XMLTreeGenerator::XMLTreeGenerator( XMLTree* pTree )
: m_pRoot(pTree), m_pBuffer(NULL)
{
}

XMLTreeGenerator::~XMLTreeGenerator()
{
}

void
XMLTreeGenerator::startElement( const XMLCh* const uri, 
									const XMLCh* const localname, 
									const XMLCh* const qname, 
									const Attributes& attrs)
{
	string name = XMLUtil::trim( XMLUtil::WideCharToString( localname ) );

	if ( name.empty() ) return;

	XMLTree* pTree = NULL;

	if ( m_pBuffer == NULL )
	{
		m_pRoot->SetName( name );
		
		pTree = m_pRoot;
	}
	else
	{
		pTree = m_pBuffer->AddChild( name );
	}

	for ( unsigned int i = 0; i < attrs.getLength(); i++ ) 
	{
		pTree->AddAttribute(
			XMLUtil::trim( XMLUtil::WideCharToString( attrs.getLocalName( i ) ) ),
			XMLUtil::trim( XMLUtil::WideCharToString( attrs.getValue( i ) ) ) );
	}

	m_pBuffer = pTree;
}

void
XMLTreeGenerator::endElement(	const XMLCh* const uri, 
									const XMLCh* const localname, 
									const XMLCh* const qname )
{
	assert( m_pBuffer != NULL );

	m_pBuffer = const_cast<XMLTree *>(m_pBuffer->GetParent());
}

void
XMLTreeGenerator::characters( const XMLCh* const chars, 
								const unsigned int length )
{
	assert( m_pBuffer != NULL );

	string text = XMLUtil::trim( XMLUtil::WideCharToString( chars ) );
	m_pBuffer->SetText( m_pBuffer->GetText() + text );
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
//////////////////////////////////////////////////////////////////////////////
void XMLTreeGenerator::resetDocument()
{
	m_pRoot->Release();
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// \param e 
//////////////////////////////////////////////////////////////////////////////
void XMLTreeGenerator::warning(const SAXParseException& e)
{
	XMLUtil::filelog(
		"\nWarning at FILE %s, LINE %d, CHAR %d, \nMessage: %s\n",
		XMLUtil::WideCharToString(e.getSystemId()).c_str(), 
		e.getLineNumber(),
		e.getColumnNumber(),
		XMLUtil::WideCharToString(e.getMessage()).c_str());

	assert(false);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// \param e 
//////////////////////////////////////////////////////////////////////////////
void XMLTreeGenerator::error(const SAXParseException& e)
{
	XMLUtil::filelog(
		"\nError at FILE %s, LINE %d, CHAR %d, \nMessage: %s\n",
		XMLUtil::WideCharToString(e.getSystemId()).c_str(), 
		e.getLineNumber(),
		e.getColumnNumber(),
		XMLUtil::WideCharToString(e.getMessage()).c_str());

	assert(false);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// \param e 
//////////////////////////////////////////////////////////////////////////////
void XMLTreeGenerator::fatalError(const SAXParseException& e)
{
	XMLUtil::filelog(
		"\nFatal error at FILE %s, LINE %d, CHAR %d, \nMessage: %s\n",
		XMLUtil::WideCharToString(e.getSystemId()).c_str(), 
		e.getLineNumber(),
		e.getColumnNumber(),
		XMLUtil::WideCharToString(e.getMessage()).c_str());

	assert(false);
}


//////////////////////////////////////////////////////////////////////////////
/// \brief 
/// \param pTree 
//////////////////////////////////////////////////////////////////////////////
XMLParser::XMLParser(XMLTree* pTree)
{
	try // Initialize the XML4C2 system
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch)
	{
		XMLUtil::filelog(
			"Error during initialization! Message:%s\n",
			XMLUtil::WideCharToString(toCatch.getMessage()).c_str());
	}

	m_pHandler = new XMLTreeGenerator(pTree);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 
//////////////////////////////////////////////////////////////////////////////
XMLParser::~XMLParser()
{
	if (m_pHandler != NULL) delete m_pHandler;

	// And call the termination method
	XMLPlatformUtils::Terminate();
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 지정된 위치에 있는 파일 또는 웹 문서를 파싱한다.
/// 
/// \param pURL 
//////////////////////////////////////////////////////////////////////////////
void XMLParser::parseURL(const char* pURL)
{
	assert(pURL != NULL);
	assert(m_pHandler != NULL);

	// SAX 파서 오브젝트를 생성한다. 그리고 feature를 설정한다.
	// SAX2에서 지원되는 feature는 다음과 같다.
	//
	// validation (default: true) 
	// namespaces (default: true) 
	// namespace-prefixes (default: false) 
	// validation/dynamic (default: false) 
	// reuse-grammar (default: false) 
	// schema (default: true) 
	// schema-full-checking (default: false) 
	// load-external-dtd (default: true) 
	// continue-after-fatal-error (default: false) 
	// validation-error-as-fatal (default: false) 
	//
	// 자세한 사항은 다음 주소를 참고하기 바란다.
	// http://xml.apache.org/xerces-c/program-sax2.html#SAX2Features 
	SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();
	pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
	pParser->setFeature(XMLUni::fgXercesSchema, true);
	pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, false);
	pParser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
	pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	pParser->setFeature(XMLUni::fgXercesDynamic, true);
	pParser->setContentHandler(m_pHandler);
	pParser->setErrorHandler(m_pHandler);

	try
	{
		pParser->parse(pURL);
	}
	catch (const XMLException& e)
	{
		XMLUtil::filelog(
			"\nError during parsing! Exception Message: \n%s\n",
			XMLUtil::WideCharToString(e.getMessage()).c_str());
	}
	catch (...)
	{
		XMLUtil::filelog(
			"Unexpected exception during parsing!\n");
	}

	delete pParser;
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 인수로 넘겨지는 문자열을 XML 문서로 가정하고 파싱한다.
/// 
/// \param buffer 
//////////////////////////////////////////////////////////////////////////////
void XMLParser::parse(const char* buffer)
{
	assert(buffer != NULL);
	assert(m_pHandler != NULL);

	// SAX 파서 오브젝트를 생성한다. 그리고 feature를 설정한다.
	// feature에 관한 사항은 XMLParser::parseURL() 함수를 참고하기 바란다.
	SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();
	pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
	pParser->setFeature(XMLUni::fgXercesSchema, true);
	pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, false);
	pParser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, false);
	pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	pParser->setFeature(XMLUni::fgXercesDynamic, true);
	pParser->setContentHandler(m_pHandler);
	pParser->setErrorHandler(m_pHandler);

	try
	{
		MemBufInputSource source(
			(const XMLByte*)(buffer), (unsigned int)strlen(buffer), "", false);
		pParser->parse(source);
	}
	catch (const XMLException& e)
	{
		XMLUtil::filelog(
			"\nError during parsing! Exception Message: \n%s\n",
			XMLUtil::WideCharToString(e.getMessage()).c_str());
	}
	catch (...)
	{
		XMLUtil::filelog(
			"Unexpected exception during parsing!\n");
	}

	delete pParser;
}
