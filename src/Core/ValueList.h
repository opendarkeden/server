//////////////////////////////////////////////////////////////////////////////
// Filename    : ValueList.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __VALUE_LIST_H__
#define __VALUE_LIST_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
// class ValueList
//////////////////////////////////////////////////////////////////////////////
template <class T>
class ValueList 
{
public:
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	PacketSize_t 	getPacketSize () const throw()		{ return szBYTE + sizeof(T) * m_Values.size(); }
	static uint 	getPacketMaxSize() throw() 	{ return szBYTE + sizeof(T) * 255; }

	string toString () const throw ();

public:
	int 	getSize() const throw() 			{ return m_Values.size(); }
	bool 	isEmpty() const throw() 			{ return m_Values.empty(); }

	void addValue(const T& info) throw() 	{ m_Values.push_back(info); }

	T popValue() throw() 
	{ 
		const T info = m_Values.front(); 
		m_Values.pop_front(); 
		return info; 
	}

	void operator = (const ValueList<T>& VL)
	{
		m_Values.clear();

		list<T>::const_iterator itr = VL.m_Values.begin();

		for (; itr!=VL.m_Values.end(); itr++)
		{
			addValue( *itr );
		}
	}

private:
	list<T> m_Values;

};

//////////////////////////////////////////////////////////////////////////////
// Filename    : ValueList.cpp 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

//#include "ValueList.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
template <class T>
void ValueList<T>::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE numValue;
	iStream.read( numValue );

	T info;

	for( int i = 0; i < numValue; i++ ) 
	{
		iStream.read( info );
		m_Values.push_back( info );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
template <class T>
void ValueList<T>::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE numValue = m_Values.size();
	oStream.write( numValue );

	list<T>::const_iterator itr = m_Values.begin();
    for (; itr!= m_Values.end(); itr++) 
	{
		oStream.write( *itr );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
template <class T>
string ValueList<T>::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Values(";

	list<T>::const_iterator itr = m_Values.begin();

	for ( ; itr!= m_Values.end() ; itr++ ) {
		const T& info = *itr;
		msg << (int)info << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

#endif
