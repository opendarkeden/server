//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBibleSignInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// 입고 있는 기어 아이템들의 정보 리스트이다.
// 각각의 기어 아이템에 대한 정보는 BloodBibleSignSlotInfo를 참조하면 된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __BLOOD_BIBLE_SIGN_INFO_H__
#define __BLOOD_BIBLE_SIGN_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include <vector>

#define BLOOD_BIBLE_SIGN_SLOT_NUM 6

//////////////////////////////////////////////////////////////////////////////
// class BloodBibleSignInfo;
//////////////////////////////////////////////////////////////////////////////

class BloodBibleSignInfo 
{
public:
	BloodBibleSignInfo () throw ();
	~BloodBibleSignInfo () throw ();
	
public:
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	PacketSize_t getSize () const throw () { return szuint + szBYTE + szItemType * m_SignList.size(); }
	static uint getMaxSize () throw () { return szuint + szBYTE + szItemType * BLOOD_BIBLE_SIGN_SLOT_NUM; }

public:
	uint	getOpenNum() const { return m_OpenNum; }
	void	setOpenNum( uint num ) { m_OpenNum = num; }

	vector<ItemType_t>&	getList() { return m_SignList; }
	const vector<ItemType_t>& getList() const { return m_SignList; }
private:
	uint				m_OpenNum;
	vector<ItemType_t>	m_SignList;
};

#endif
