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
{
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
ResourceManager::~ResourceManager () 
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
{
	__BEGIN_TRY

	ifstream ifile( filename.c_str() , ios::in | ios::binary );

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
{
	__BEGIN_TRY

	ofstream ofile( filename.c_str() , ios::out );

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
// �ٿ�޴� ������ �ߺ� ���� ���� üũ�ؼ� �ٿ�ε� �ð��� �뷮�� ����ȭ�ϵ��� �Ѵ�.
// �ϴ��� ���� ������ �ߺ� ���θ��� üũ�Ѵ�.
//--------------------------------------------------------------------------------
void ResourceManager::optimize ()
{
	__BEGIN_TRY

/*
	// �ڿ������� üũ�Ѵ�.
	bool exefileFound = false;

	list< Resource * >::reverse_iterator before = m_Resources.rend();
	list< Resource * >::reverse_iterator current = m_Resources.rbegin();

	while ( current != m_Resources.rend() ) {

		// ���ϸ��� �޾ƿ´�.
		string filename = (*current)->getFilename();

		// ���� ����� �߶󳻰� �����ϰ� ���ϸ��� �����صд�.
		size_t i = filename.find_first_of(' ');
		filename = filename.substr(0,i);

		// �� ���ϸ�ȿ� darkeden.exe �� ���Ե� ���, �ߺ� üũ�� ����.
		if ( filename == "DarkEden.exe" ) {
			if ( exefileFound == false ) {
				exefileFound = true;
			} else {
				// ��带 �����Ѵ�.
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

