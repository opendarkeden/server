//--------------------------------------------------------------------------------
// 
// Filename    : UpdateManager.cpp
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "UpdateManager.h"
#include "Assert.h"
#include "Socket.h"
#include "SocketOutputStream.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
UpdateManager::UpdateManager () 
	throw ()
: m_pResourceManager(NULL)
{
}


//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
UpdateManager::~UpdateManager () 
	throw ()
{
	// delete all update
	while ( !m_Updates.empty() ) {
		Update * pUpdate = m_Updates.front();
		delete pUpdate;
		m_Updates.pop_front();
	}

	// delete resource manager
	if ( m_pResourceManager != NULL ) {
		delete m_pResourceManager;
		m_pResourceManager = NULL;
	}
}

	
//--------------------------------------------------------------------------------
// load from update file
//--------------------------------------------------------------------------------
void UpdateManager::load ( const string & filename ) 
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
	// read #Updates
	//--------------------------------------------------------------------------------
	WORD size;
	ifile.read( (char *)&size , szWORD );

	//--------------------------------------------------------------------------------
	// read each recource
	//--------------------------------------------------------------------------------
	for ( int i = 0 ; i < size ; i ++ ) {

		Update * pUpdate = new Update();
		pUpdate->load( ifile );

		push_back( pUpdate );
	
	}

	cout << "filename = " << filename.c_str() << " num = " << size << endl;

	ifile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save to update file
//--------------------------------------------------------------------------------
void UpdateManager::save ( const string & filename ) const 
	throw ( Error )
{
	__BEGIN_TRY

	ofstream ofile( filename.c_str() , ios::out | ios::binary | ios::noreplace );
	if ( !ofile ) {
		StringStream msg;
		msg << "cannot open " << filename << " with write mode";
		throw Error(msg.toString());
	}

	//--------------------------------------------------------------------------------
	// write #Update
	//--------------------------------------------------------------------------------
	WORD size = m_Updates.size();
	ofile.write( (const char *)&size , szWORD );

	for ( list< Update * >::const_iterator itr = m_Updates.begin() ; itr != m_Updates.end() ; itr ++ ) {

		Update * pUpdate = *itr;

		pUpdate->save( ofile );

	}

	ofile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// read from socket 
//--------------------------------------------------------------------------------
void UpdateManager::read ( Socket * pSocket )
	throw ( IOException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// read #updates
	//--------------------------------------------------------------------------------
	WORD nUpdates;

	pSocket->receive( &nUpdates , szWORD );

	if ( nUpdates > maxUpdates )
		throw InvalidProtocolException("too many updates");

	for ( int i = 0 ; i < nUpdates ; i ++ ) {

		Update * pUpdate = new Update();
		pUpdate->read( pSocket );

		push_back( pUpdate );
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// write to socket 
//--------------------------------------------------------------------------------
void UpdateManager::write ( Socket * pSocket ) const
	throw ( IOException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// #updates
	//--------------------------------------------------------------------------------
	WORD nUpdates = m_Updates.size();
	
	//cout << "============================================"<< endl;
	//cout << "업데이트할 항목의 갯수는 얼마 일까요? : " << (int)nUpdates << endl;
	//cout << "============================================"<< endl;

	if ( nUpdates > maxUpdates )
		throw InvalidProtocolException("too many updates");

	pSocket->send( &nUpdates , szWORD );

	//--------------------------------------------------------------------------------
	// write each update
	//--------------------------------------------------------------------------------
	for ( list< Update * >::const_iterator itr = m_Updates.begin() ; itr != m_Updates.end() ; itr ++ ) {
		(*itr)->write( pSocket );
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get resource manager
//--------------------------------------------------------------------------------
ResourceManager * UpdateManager::getResourceManager ()
	throw ( Error )
{
	__BEGIN_TRY

	// 아직 리소스매니저를 생성하지 않았으며, 업데이트 리스트가 empty 가 아닐 경우
	if ( m_pResourceManager == NULL && !m_Updates.empty() ) {

		// 리소스 매니저를 생성하자.
		m_pResourceManager = new ResourceManager();

		Resource * pResource;
	
		for ( list< Update * >::const_iterator itr = m_Updates.begin() ; itr != m_Updates.end() ; itr ++ ) {
		
			// 어떤 업데이트 명령의 특정 파라미터는 리소스를 나타낸다. 
			// 그런 파라미터를 리소스 객체로 만들어서 리소스 매니저에 등록시키자.	
			switch ( (*itr)->getUpdateType() ) {
	
				// 다음 명령들에는 리소스가 존재하지 않는다.
				case UPDATETYPE_CREATE_DIRECTORY :
				case UPDATETYPE_DELETE_DIRECTORY :
				case UPDATETYPE_RENAME_DIRECTORY :
				case UPDATETYPE_DELETE_FILE :
				case UPDATETYPE_RENAME_FILE :
					break;
	
				// param[0]
				case UPDATETYPE_CREATE_FILE :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				// param[0], param[2]
				case UPDATETYPE_APPEND_SPRITE_PACK :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(2) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				// param[0], param[2]
				case UPDATETYPE_DELETE_SPRITE_PACK :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(2) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				// param[0], param[1]
				case UPDATETYPE_UPDATE_SPRITE_PACK :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(1) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				// param[0]
				case UPDATETYPE_APPEND_FRAME_PACK :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				// param[0]
				case UPDATETYPE_APPEND_INFO :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				// param[0]
				case UPDATETYPE_VERIFY :
					{
						pResource = new Resource( (*itr)->getVersion() , (*itr)->getParam(0) );
						m_pResourceManager->push_back( pResource );
					}
					break;
	
				default :
					throw Error("invalid update type");
	
			}//switch
	
		}//for

//		cout << "Generating Resource Manager\n" << m_pResourceManager->toString() << endl;

	}//!empty

	return m_pResourceManager;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get size
//--------------------------------------------------------------------------------
uint UpdateManager::getSize () const
	throw ()
{
	uint size = szWORD;	// nUpdates

	for ( list< Update * >::const_iterator itr = m_Updates.begin() ; itr != m_Updates.end() ; itr ++ ) {
		size += (*itr)->getSize();
	}

	return size;
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string UpdateManager::toString () const 
	throw ()
{
	StringStream msg;

	msg << "UpdateManager(\n";
		
	for ( list< Update * >::const_iterator itr = m_Updates.begin() ; itr != m_Updates.end() ; itr ++ ) 
	{
		msg << (*itr)->toString();
	}

	msg << ")";

	return msg.toString();
}

