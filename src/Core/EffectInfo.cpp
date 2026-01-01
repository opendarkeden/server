//////////////////////////////////////////////////////////////////////
// 
// Filename    : EffectInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : ����Ʈ ���� ����Ʈ ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "EffectInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
EffectInfo::EffectInfo () 
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
EffectInfo::~EffectInfo () noexcept = default;


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void EffectInfo::read ( SocketInputStream & iStream ) 
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	iStream.read( m_ListNum );

	WORD m_Value;
	for( int i = 0; i < m_ListNum * 2 ; i++ ) {
		iStream.read( m_Value );
		m_EList.push_back(m_Value);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void EffectInfo::write ( SocketOutputStream & oStream ) 
     const
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ �����ϵ��� �Ѵ�.
	oStream.write( m_ListNum );

    for ( list<WORD>:: const_iterator itr = m_EList.begin(); itr!= m_EList.end(); itr++) {
		oStream.write(*itr);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// EffectInfo::addListElement()
// 
// ( ��ȭ����, ��ȭ��ġ ) �� �� ���� ����Ʈ�� �ֱ� ���� ��� �Լ�. 
//
//////////////////////////////////////////////////////////////////////
void EffectInfo::addListElement( EffectID_t EffectID , WORD Value )
{
	__BEGIN_TRY

	// ���ϴ� ���� �������� List�� �ִ´�.
	m_EList.push_back( EffectID );

	// ���ϴ� ��ġ�� List�� �ִ´�.
	m_EList.push_back( Value );

	// ��ȭ ���� ������ �ϳ� ���� ��Ų��.
	m_ListNum++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string EffectInfo::toString () 
	const
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectInfo( "
		<< ",ListNum: " << (int)m_ListNum 
		<< " ListSet(" ;
	for ( list<WORD>::const_iterator itr = m_EList.begin(); itr!= m_EList.end() ; itr++ ) {
		msg << (int)(*itr) << ",";
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}

