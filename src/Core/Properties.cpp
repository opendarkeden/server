//--------------------------------------------------------------------------------
//
// Filename    : Properties.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "Properties.h"
#include <stdlib.h>			// atoi()

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
const char Properties::Comment = '#';
const char Properties::Separator = ':';
const char * Properties::WhiteSpaces = " \t";


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Properties::Properties () 
{
	__BEGIN_TRY
	__END_CATCH
}

Properties::Properties ( const string & filename ) 
: m_Filename(filename)
{
	__BEGIN_TRY
	__END_CATCH
}
	

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
Properties::~Properties () noexcept
{ 
	// ��� pair �� �����Ѵ�.
	m_Properties.clear();
}


//--------------------------------------------------------------------------------
// load from file
//--------------------------------------------------------------------------------
void Properties::load () 
{
	__BEGIN_TRY
		
	if ( m_Filename.empty() )
		throw Error("filename not specified");
		
	ifstream ifile( m_Filename.c_str() , ios::in );
	
	if ( ! ifile )
		throw FileNotExistException( m_Filename.c_str() );

	while ( true ) {

		string line;
		getline( ifile , line );
		
		if ( ifile.eof() )
			break;

		// �ڸ�Ʈ �����̰ų� �� �����̹Ƿ� skip �Ѵ�.
		if ( line.size() == 0 || line[0] == Comment )	
			continue;

		// key �� ���۹���(white space�� �ƴ� ����)�� ã�´�. 
		size_t key_begin = line.find_first_not_of( WhiteSpaces );
		
		// key_begin�� npos ��� ���� �׷� ���ڸ� ã�� ���ߴٴ� ���̴�.
		// ��, ���� white space �θ� �Ǿ� �ִ� �����̹Ƿ� skip �Ѵ�.
		if ( key_begin == string::npos )
			continue;

		// key �� value �� �������� separator �� ã�´�.
		// key_end ���� sep �� ���� ã�� ������ find_last_not_of()�� �Ἥ
		// sep �������� ������ key_end �� ã�� ���ؼ��̴�. ^^;
		size_t sep = line.find( Separator , key_begin );

		// Separator �� �߰����� ������ ���� �Ľ� ������ �����Ѵ�.
		if ( sep == string::npos )
			throw IOException("missing separator");
		
		// sep �������� ������ key_end �� ã�Ƴ�����.
		size_t key_end = line.find_last_not_of( WhiteSpaces , sep - 1 );
		
		// sep �������� value_begin �� ã�´�.
		size_t value_begin = line.find_first_not_of( WhiteSpaces , sep + 1 );
		
		// key �� ������ value �� ���� �����̴�. 
		if ( value_begin == string::npos )
			throw IOException("missing value");
		
		// �� ���������� ������ value_end �� ã�´�. 
		// ( value_begin �� ������ value_end �� ������ �����Ѵ�.)
		size_t value_end = line.find_last_not_of( WhiteSpaces ); 

		// key_begin,key_end �� value_begin,value_end �� ����ؼ� 
		// line �� substring �� key �� value �� �����Ѵ�.
		string key = line.substr( key_begin , key_end - key_begin + 1 );
		string value = line.substr( value_begin , value_end - value_begin + 1 );

		// property �� ����Ѵ�.
		setProperty( key , value );
	}
	
	ifile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save to file
//--------------------------------------------------------------------------------
void Properties::save () 
{
	__BEGIN_TRY
		
	if ( m_Filename.empty() )
		throw Error("filename not specified");

	ofstream ofile( m_Filename.c_str() , ios::out | ios::trunc );
	
	for ( map< string , string , StringCompare >::iterator itr = m_Properties.begin() ;
		  itr != m_Properties.end() ;
		  itr ++ )
		ofile << itr->first << ' ' << Separator << ' ' << itr->second << endl;
	
	ofile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get property
//--------------------------------------------------------------------------------
string Properties::getProperty ( string key ) const 
{
	__BEGIN_TRY
	
	string value;
   
	map< string , string , StringCompare >::const_iterator itr = m_Properties.find( key );
	
	if ( itr != m_Properties.end() )
		value = itr->second;
	else
		throw NoSuchElementException(key);
	
	return value;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get property as int
//--------------------------------------------------------------------------------
int Properties::getPropertyInt ( string key ) const 
{
	__BEGIN_TRY
		
	return atoi( getProperty(key).c_str() );
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// set property
//--------------------------------------------------------------------------------
void Properties::setProperty ( string key , string value )
{
	__BEGIN_TRY
		
	// �̹� Ű�� ������ ���, value �� �����.
	m_Properties[ key ] = value;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string Properties::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;

	for ( map< string , string , StringCompare >::const_iterator itr = m_Properties.begin() ;
		  itr != m_Properties.end() ;
		  itr ++ ) {
		
		msg << itr->first << " : " << itr->second << "\n";
	}
	
	if ( msg.isEmpty() )
		msg << "empty properties";
	
	return msg.toString();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// global variable definition
//--------------------------------------------------------------------------------
Properties * g_pConfig = NULL;
Properties * g_pTestConfig = NULL;	// by sigi. 2002.12.26
