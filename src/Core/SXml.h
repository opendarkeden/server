//////////////////////////////////////////////////////////////////////////////
/// \file XML.h
/// \author excel96
/// \date 2003.7.25
///
/// \todo
/// \bug
/// \warning
//////////////////////////////////////////////////////////////////////////////

//#pragma once
#ifndef __SXML_H__
#define __SXML_H__

#include "Types.h"

#include <hash_map>
#include <vector>
#include <string>
#include <fstream>

//////////////////////////////////////////////////////////////////////////////
/// \class XMLAttribute
/// \brief 
//////////////////////////////////////////////////////////////////////////////
class XMLAttribute
{
private:
	string	m_Name;
	string	m_Value;

public:
	XMLAttribute( const string &name, const string &value );
	virtual ~XMLAttribute();

	void	SetValue( string value );

	const char*		GetName() const;
	const char*		ToString() const;
	const int		ToInt() const;
	const DWORD		ToHex() const;
	const bool		ToBool() const;
	const double	ToDouble() const;
	const float		ToFloat() const;
};


//////////////////////////////////////////////////////////////////////////////
/// \class XMLTree
/// \brief 
//////////////////////////////////////////////////////////////////////////////

class XMLTree
{
private:
	typedef hash_map<string, XMLAttribute *> ATTRIBUTES_MAP;
	typedef vector<XMLAttribute *> ATTRIBUTES_VECTOR;
	
	typedef hash_map<string, XMLTree*> CHILDREN_MAP;
	typedef vector<XMLTree *> CHILDREN_VECTOR;

	string     m_Name;        ///< 노드의 이름
	string     m_Text;        ///< 노드에 속한 텍스트
	XMLTree*   m_pParent;     ///< 부모 노드의 포인터

	ATTRIBUTES_MAP m_AttributesMap;  ///< 가지고 있는 속성값들
	ATTRIBUTES_VECTOR m_AttributesVector;  ///< 가지고 있는 속성값들
	CHILDREN_MAP   m_ChildrenMap;    ///< 자식 노드들
	CHILDREN_VECTOR   m_ChildrenVector;    ///< 자식 노드들

public:
	XMLTree();
	XMLTree( const string& name );
	XMLTree( const XMLTree& xmlTree );	// copy constructor : 깊은 복사
	virtual ~XMLTree();

public:
	const string& GetName() const;
	void SetName( const string& name );

	const string& GetText() const;
	void SetText( const string& text );


	const XMLTree* GetParent() const;
	void SetParent( XMLTree* pParent );

	void AddAttribute( const string& name, const string& value );
	void AddAttribute( const string& name, const char * value );
	void AddAttribute( const string& name, const int& value );
	void AddAttribute( const string& name, const unsigned int& value, const bool bHex = false );
	void AddAttribute( const string& name, const DWORD& value, const bool bHex = false );
	void AddAttribute( const string& name, const float& value );
	void AddAttribute( const string& name, const double& value );
	void AddAttribute( const string& name, const bool& value );

	XMLAttribute *GetAttribute( const string& name ) const;

	const bool GetAttribute( const string& name, string &value );
	const bool GetAttribute( const string& name, int &value );
	const bool GetAttribute( const string& name, unsigned int &value, const bool bHex = false );
	const bool GetAttribute( const string& name, DWORD &value, const bool bHex = false );
	const bool GetAttribute( const string& name, float &value );
	const bool GetAttribute( const string& name, double &value );
	const bool GetAttribute( const string& name, bool &value );

	XMLTree* AddChild( const string& name );
	XMLTree* AddChild( XMLTree* pChild );
	XMLTree* GetChild( const string& name ) const;
	XMLTree* GetChild( size_t index ) const;
	const size_t GetChildCount() const;

	void Release();

	void SaveToFile(const char* pFilename);

	void LoadFromFile( const char *pFilename );
	void LoadFromMem( const char *pBuffer );

	void Save(ofstream& file, size_t indent);
};

#endif
