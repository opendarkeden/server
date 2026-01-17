//////////////////////////////////////////////////////////////////////
// 
// Filename    : WorldInfo.h 
// Written By  : elca@ewestsoft.com
// Description : �κ��丮 �������� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __WORLD_INFO_H__
#define __WORLD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class WorldInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class WorldInfo {

public :
	
	// constructor
	WorldInfo () ;
	
	// destructor
	~WorldInfo () noexcept;

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () ;

	static uint getMaxSize()  {
		return (szBYTE + szBYTE + 20 + szBYTE)* 37;
	}

	// get packet's debug string
	string toString () const ;

	// get / set ID
	BYTE getID() const  { return m_ID; }
	void setID(WorldID_t ID)  { m_ID = ID; }

	// get / set Name
	string getName() const  { return m_Name; }
	void setName(string Name)  { m_Name = Name; }

	// get / set  Stat
	BYTE getStat() const  { return m_Stat; }
	void setStat(BYTE Stat)  { m_Stat = Stat; }

private :

	// �׷� ���̵�
	WorldID_t m_ID;

	// �׷� �̸�
	string m_Name;

	// �׷��� ����
	BYTE	m_Stat;

};

#endif
