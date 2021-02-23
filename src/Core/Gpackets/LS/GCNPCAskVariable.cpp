//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCAskVariable.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCNPCAskVariable.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCNPCAskVariable::GCNPCAskVariable()
	throw ()
{
	__BEGIN_TRY 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCNPCAskVariable::~GCNPCAskVariable() 
	throw ()
{
	__BEGIN_TRY 

	clearScriptParameters();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskVariable::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_ObjectID );
	iStream.read( m_ScriptID );

	BYTE szParameters;
	iStream.read( szParameters );
	for ( int i = 0; i < szParameters ; i++ )
	{
		ScriptParameter* pParam = new ScriptParameter();
		pParam->read( iStream );
		addScriptParameter( pParam );
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskVariable::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_ScriptID );

	BYTE szParam = m_ScriptParameters.size();
	oStream.write( szParam );

	HashMapScriptParameterConstItor itr = m_ScriptParameters.begin();
	for( ; itr != m_ScriptParameters.end() ; itr++ )
	{
		(itr->second)->write( oStream );
	}
	
	__END_CATCH
}

void GCNPCAskVariable::addScriptParameter( ScriptParameter* pParam )
	throw(DuplicatedException)
{
	__BEGIN_TRY

	HashMapScriptParameterItor itr = m_ScriptParameters.find( pParam->getName() );

	if ( itr != m_ScriptParameters.end() )
	{
		throw DuplicatedException( "Dup Parameter Variable name" );
		return;
	}

	m_ScriptParameters[pParam->getName()] = pParam;

	__END_CATCH
}

void GCNPCAskVariable::clearScriptParameters()
	throw()
{
	__BEGIN_TRY

	HashMapScriptParameterItor itr = m_ScriptParameters.begin();

	for ( ; itr != m_ScriptParameters.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_ScriptParameters.clear();

	__END_CATCH
}

string GCNPCAskVariable::getValue( const string& name ) const
	throw( NoSuchElementException )
{
	__BEGIN_TRY

	HashMapScriptParameterConstItor itr = m_ScriptParameters.find( name );

	if ( itr == m_ScriptParameters.end() )
	{
		// name 이 없는 경우다. NoSuchElement 를 던져야하나
		// 걍 name 을 돌려주도록 한다.
		return name;
	}

	return (itr->second)->getValue();
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskVariable::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCNPCAskVariableHandler::execute( this , pPlayer );

	__END_CATCH
}

PacketSize_t GCNPCAskVariable::getPacketSize() const
	throw()
{
	__BEGIN_TRY

	PacketSize_t result = 0;

	result += szObjectID + szScriptID + szBYTE;

	HashMapScriptParameterConstItor itr = m_ScriptParameters.begin();

	for ( ; itr != m_ScriptParameters.end() ; itr++ )
	{
		result += (itr->second)->getSize();
	}

	return result;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCNPCAskVariable::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCNPCAskVariable("
		<< "ObjectID:" << m_ObjectID 
		<< ",ScriptID: " << m_ScriptID
		<< ",Parameters: (" ;

	HashMapScriptParameterConstItor itr = m_ScriptParameters.begin();
	for( ; itr != m_ScriptParameters.end() ; itr++ )
	{
		msg << (itr->second)->toString() << ", ";
	}
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

