//--------------------------------------------------------------------------------
//
// Filename   : Update.cpp
// Written By : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Update.h"
#include "Socket.h"

//--------------------------------------------------------------------------------
// load from file
//--------------------------------------------------------------------------------
void Update::load ( ifstream & ifile ) 
	throw ( IOException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// load version
	//--------------------------------------------------------------------------------
	ifile.read( (char *)&m_Version , szVersion );
	
	//--------------------------------------------------------------------------------
	// load update type
	//--------------------------------------------------------------------------------
	BYTE updatetype;
	ifile.read( (char *)&updatetype, szBYTE );
	m_UpdateType = (UPDATETYPE)updatetype;

	//--------------------------------------------------------------------------------
	// load parameters
	//--------------------------------------------------------------------------------
	ParameterLen_t szParam;
	char buf[maxParameterLen+1];
	for ( uint i = 0 ; i < maxParams ; i ++ ) {

		//--------------------------------------------------------------------------------
		// load param size
		//--------------------------------------------------------------------------------
		ifile.read( (char *)&szParam , szParameterLen );

		if ( szParam == 0 )
			continue;

		if ( szParam > maxParameterLen )
			throw Error("too large parameter length");

		//--------------------------------------------------------------------------------
		// load param value
		//--------------------------------------------------------------------------------
		ifile.read( buf , szParam );
		buf[szParam] = 0;

		m_Params[i] = buf;
		
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save to file
//--------------------------------------------------------------------------------
void Update::save ( ofstream & ofile ) const 
	throw ( IOException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// save update type
	//--------------------------------------------------------------------------------
	ofile.write( (const char *)&m_Version , szVersion );

	//--------------------------------------------------------------------------------
	// save update type
	//--------------------------------------------------------------------------------
	BYTE updatetype = m_UpdateType;
	ofile.write( (const char *)&updatetype , szBYTE );

	//--------------------------------------------------------------------------------
	// save parameters
	//--------------------------------------------------------------------------------
	ParameterLen_t szParam;
	for ( uint i = 0 ; i < maxParams ; i ++ ) {

		//--------------------------------------------------------------------------------
		// save param size
		//--------------------------------------------------------------------------------
		szParam = m_Params[i].size();
		ofile.write( (const char *)&szParam , szParameterLen );

		if ( szParam == 0 )
			continue;

		if ( szParam > maxParameterLen )
			throw Error("too large parameter length");

		//--------------------------------------------------------------------------------
		// save param value
		//--------------------------------------------------------------------------------
		ofile.write( m_Params[i].c_str() , szParam );
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// read from socket input stream
//--------------------------------------------------------------------------------
void Update::read ( SocketInputStream & iStream ) 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// read version
	//--------------------------------------------------------------------------------
	iStream.read( m_Version );
	
	//--------------------------------------------------------------------------------
	// read update type
	//--------------------------------------------------------------------------------
	BYTE updatetype;
	iStream.read( updatetype );
	m_UpdateType = (UPDATETYPE)updatetype;

	if ( m_UpdateType >= UPDATETYPE_MAX )
		throw InvalidProtocolException("invalid update type");

	//--------------------------------------------------------------------------------
	// read parameters
	//--------------------------------------------------------------------------------
	ParameterLen_t szParam;
	for ( uint i = 0 ; i < maxParams ; i ++ ) {

		//--------------------------------------------------------------------------------
		// read param size
		//--------------------------------------------------------------------------------
		iStream.read( szParam );

		if ( szParam == 0 )
			continue;

		if ( szParam > maxParameterLen )
			throw Error("too large parameter length");

		//--------------------------------------------------------------------------------
		// read param value
		//--------------------------------------------------------------------------------
		iStream.read( m_Params[i] , szParam );
		
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// read from socket
//--------------------------------------------------------------------------------
void Update::read ( Socket * pSocket ) 
	throw ( IOException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// read version
	//--------------------------------------------------------------------------------
	pSocket->receive( &m_Version , szVersion );
	
	//--------------------------------------------------------------------------------
	// read update type
	//--------------------------------------------------------------------------------
	BYTE updatetype;
	pSocket->receive( &updatetype , szBYTE );
	m_UpdateType = (UPDATETYPE)updatetype;

	if ( m_UpdateType >= UPDATETYPE_MAX )
		throw InvalidProtocolException("invalid update type");

	//--------------------------------------------------------------------------------
	// read parameters
	//--------------------------------------------------------------------------------
	ParameterLen_t szParam;
	char buf[maxParameterLen+1];
	for ( uint i = 0 ; i < maxParams ; i ++ ) {

		//--------------------------------------------------------------------------------
		// read param size
		//--------------------------------------------------------------------------------
		pSocket->receive( &szParam , szParameterLen );

		if ( szParam == 0 )
			continue;

		if ( szParam > maxParameterLen )
			throw Error("too large parameter length");

		//--------------------------------------------------------------------------------
		// read param value
		//--------------------------------------------------------------------------------
		pSocket->receive( buf , szParam );
		buf[szParam] = 0;

		m_Params[i] = buf;
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// write to socket output stream
//--------------------------------------------------------------------------------
void Update::write ( SocketOutputStream & oStream ) const 
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// write version
	//--------------------------------------------------------------------------------
	oStream.write( m_Version );

	//--------------------------------------------------------------------------------
	// write update type
	//--------------------------------------------------------------------------------
	oStream.write( (BYTE)m_UpdateType );

	//--------------------------------------------------------------------------------
	// save parameters
	//--------------------------------------------------------------------------------
	ParameterLen_t szParam;
	for ( uint i = 0 ; i < maxParams ; i ++ ) {

		//--------------------------------------------------------------------------------
		// save param size
		//--------------------------------------------------------------------------------
		szParam = m_Params[i].size();
		oStream.write( szParam );

		if ( szParam == 0 )
			continue;

		if ( szParam > maxParameterLen )
			throw Error("too large parameter length");

		//--------------------------------------------------------------------------------
		// save param value
		//--------------------------------------------------------------------------------
		oStream.write( m_Params[i] );
	}


	__END_CATCH
}


//--------------------------------------------------------------------------------
// write to socket
//--------------------------------------------------------------------------------
void Update::write ( Socket * pSocket ) const 
	throw ( IOException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// write version
	//--------------------------------------------------------------------------------
	pSocket->send( &m_Version , szVersion );
	
	//--------------------------------------------------------------------------------
	// write update type
	//--------------------------------------------------------------------------------
	BYTE updatetype = m_UpdateType;
	pSocket->send( &updatetype , szBYTE );

	//--------------------------------------------------------------------------------
	// write parameters
	//--------------------------------------------------------------------------------
	ParameterLen_t szParam;
	for ( uint i = 0 ; i < maxParams ; i ++ ) {

		//--------------------------------------------------------------------------------
		// write param size
		//--------------------------------------------------------------------------------
		szParam = m_Params[i].size();
		pSocket->send( &szParam , szParameterLen );

		if ( szParam == 0 )
			continue;

		if ( szParam > maxParameterLen )
			throw Error("too large parameter length");

		//--------------------------------------------------------------------------------
		// write param value
		//--------------------------------------------------------------------------------
		pSocket->send( m_Params[i].c_str() , szParam );
	}


	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute update
//--------------------------------------------------------------------------------
void Update::execute () 
	throw ( Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG

#ifdef __UPDATE_CLIENT__

	switch ( m_UpdateType ) {
		case UPDATETYPE_CREATE_DIRECTORY :
			{
			}
			break;
		case UPDATETYPE_DELETE_DIRECTORY :
			{
			}
			break;
		case UPDATETYPE_RENAME_DIRECTORY :
			{
			}
			break;
		case UPDATETYPE_CREATE_FILE :
			{
			}
			break;
		case UPDATETYPE_DELETE_FILE :
			{
			}
			break;
		case UPDATETYPE_RENAME_FILE :
			{
			}
			break;
		case UPDATETYPE_APPEND_SPRITE_PACK :
			{
			}
			break;
		case UPDATETYPE_DELETE_SPRITE_PACK :
			{
			}
			break;
		case UPDATETYPE_UPDATE_SPRITE_PACK :
			{
			}
			break;
		case UPDATETYPE_APPEND_FRAME_PACK :
			{
			}
			break;
		case UPDATETYPE_APPEND_INFO :
			{
			}
			break;
		case UPDATETYPE_VERIFY :
			{
			}
			break;
		default :
			throw Error("invalid update type");
	}

#endif

	__END_DEBUG
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get size
//--------------------------------------------------------------------------------
uint Update::getSize () const
	throw ()
{
	// [Version] [UpdateType] 
	uint size = szVersion + szBYTE;

	for ( uint i = 0 ; i < maxParams ; i ++ ) {
		size += ( szParameterLen + m_Params[i].size() );
	}

	return size;
}


//--------------------------------------------------------------------------------
// get max size
//--------------------------------------------------------------------------------
uint Update::getMaxSize ()
	throw ()
{
	// [Version] [UpdateType] [ParameterLen] [Parameter0] ... [ParameterLen] [Parameter5]
	return szVersion + szBYTE + ( szParameterLen + maxParameterLen ) * maxParams;
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Update::toString () const
	throw ()
{
	StringStream msg;

	msg << "Update("
		<< "Version:" << m_Version
		<< ",UpdateType:" << UPDATETYPE2String[ m_UpdateType ];

	for ( uint i = 0 ; i < maxParams ; i ++ ) {
		if ( m_Params[i] == "" )
			break;
		msg << ",Params[" << i << "]:" << m_Params[i];
	}

	msg << ")";

	return msg.toString();
}
