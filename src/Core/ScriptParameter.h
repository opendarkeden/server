//////////////////////////////////////////////////////////////////////
// 
// Filename    : ScriptParameter.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SCRIPT_PARAMETER_H__
#define __SCRIPT_PARAMETER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class ScriptParameter;
//
// 
//
//////////////////////////////////////////////////////////////////////

class ScriptParameter {

public :
	
	// constructor
	ScriptParameter () ;
	
	// destructor
	~ScriptParameter () noexcept;

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () ;

	static uint getMaxSize()  {
		return szBYTE + 255 + szBYTE + 255;
	}

	// get packet's debug string
	string toString () const ;

	// get/set Name
	string getName() const  { return m_Name; }
	void setName( const string& name )  { m_Name = name; }

	// get/set Value
	string getValue() const  { return m_Value; }
	void setValue( const string& value )  { m_Value = value; }

private :

	string m_Name;
	string m_Value;
};

#endif
