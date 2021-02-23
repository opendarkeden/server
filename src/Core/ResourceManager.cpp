//--------------------------------------------------------------------------------
// 
// Filename    : ResourceManager.cpp
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "ResourceManager.h"
#include "Assert.h"
#include "Socket.h"
#include "SocketOutputStream.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
ResourceManager::ResourceManager () 
	throw ()
{
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
ResourceManager::~ResourceManager () 
	throw ()
{
	while ( !m_Resources.empty() ) 
	{
		Resource * pResource = m_Resources.front();
		SAFE_DELETE(pResource);
		m_Resources.pop_front();
	}
}

	
//--------------------------------------------------------------------------------
// load from resource file
//--------------------------------------------------------------------------------
void ResourceManager::load ( const string & filename ) 
	throw ( Error )
{
	__BEGIN_TRY

	ifstream ifile( filename.c_str() , ios::in | ios::binary | ios::nocreate );

	if ( !ifile ) {
		StringStream msg;
		msg << "cannot open " << filename << " with read mode";
		throw Error(msg.toString());
	}

	//--------------------------------------------------------------------------------
	// read #Resources
	//--------------------------------------------------------------------------------
	WORD nResources;
	ifile.read( (char *)&nResources, szWORD );
	if ( nResources > maxResources )
		throw Error("too many resources");

	//--------------------------------------------------------------------------------
	// read each recource
	//--------------------------------------------------------------------------------
	for ( int i = 0 ; i < nResources ; i ++ ) {
		Resource * pResource = new Resource();
		pResource->load( ifile );
		push_back( pResource );
	}

	ifile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save to resource file
//--------------------------------------------------------------------------------
void ResourceManager::save ( const string & filename ) const 
	throw ( Error )
{
	__BEGIN_TRY

	ofstream ofile( filename.c_str() , ios::out | ios::noreplace );

	if ( !ofile ) {
		StringStream msg;
		msg << "cannot open " << filename << " with write mode";
		throw Error(msg.toString());
	}

	//--------------------------------------------------------------------------------
	// write #Resource
	//--------------------------------------------------------------------------------
	WORD nResources = m_Resources.size();
	if ( nResources > maxResources )
		throw Error("too many resources");
	ofile.write( (const char *)&nResources , szWORD );

	//--------------------------------------------------------------------------------
	// write each resource
	//--------------------------------------------------------------------------------
	for ( list< Resource * >::const_iterator itr = m_Resources.begin() ; itr != m_Resources.end() ; itr ++ ) {
		(*itr)->save( ofile );
	}

	ofile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// 다운받는 파일의 중복 여부 등을 체크해서 다운로드 시간과 용량을 최적화하도록 한다.
// 일단은 실행 파일의 중복 여부만을 체크한다.
//--------------------------------------------------------------------------------
void ResourceManager::optimize ()
	throw ( Error )
{
	__BEGIN_TRY

/*
	// 뒤에서부터 체크한다.
	bool exefileFound = false;

	list< Resource * >::reverse_iterator before = m_Resources.rend();
	list< Resource * >::reverse_iterator current = m_Resources.rbegin();

	while ( current != m_Resources.rend() ) {

		// 파일명을 받아온다.
		string filename = (*current)->getFilename();

		// 파일 사이즈를 잘라내고 순수하게 파일명만을 저장해둔다.
		uint i = filename.find_first_of(' ');
		filename = filename.substr(0,i);

		// 이 파일명안에 darkeden.exe 가 포함될 경우, 중복 체크에 들어간다.
		if ( filename == "DarkEden.exe" ) {
			if ( exefileFound == false ) {
				exefileFound = true;
			} else {
				// 노드를 삭제한다.
				if ( before == m_Resources.rend() ) {
					m_Resources.erase( current );
					current = m_Resources.rbegin();
				} else {
					m_Resources.erase( current );
					current = before;
					current ++;
				}
			}
		}
	}
*/

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string ResourceManager::toString () const 
	throw ()
{
	StringStream msg;

	msg << "ResourceManager(\n";
		
	for ( list< Resource * >::const_iterator itr = m_Resources.begin() ; itr != m_Resources.end() ; itr ++ ) 
	{
		msg << (*itr)->toString();
	}

	msg << ")";

	return msg.toString();
}

