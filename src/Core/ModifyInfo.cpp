//////////////////////////////////////////////////////////////////////////////
// Filename    : ModifyInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
ModifyInfo::ModifyInfo () 
     throw ()
{
	__BEGIN_TRY

	m_ShortCount = 0;
	m_LongCount = 0;

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
ModifyInfo::~ModifyInfo () 
    throw ()
{
	__BEGIN_TRY

	m_ShortList.clear();
	m_LongList.clear();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void ModifyInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	SHORTDATA short_data;
	LONGDATA  long_data;

	iStream.read(m_ShortCount);

	for (BYTE s=0; s<m_ShortCount; s++)
	{
		iStream.read(short_data.type);
		iStream.read(short_data.value);

		m_ShortList.push_back(short_data);
	}

	iStream.read(m_LongCount);

	for (BYTE s=0; s<m_LongCount; s++)
	{
		iStream.read(long_data.type);
		iStream.read(long_data.value);

		m_LongList.push_back(long_data);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void ModifyInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_ShortCount);
	list<SHORTDATA>::const_iterator short_itr = m_ShortList.begin();
	for (; short_itr != m_ShortList.end(); short_itr++)
	{
		SHORTDATA short_data = *short_itr;
		oStream.write(short_data.type);
		oStream.write(short_data.value);
	}

	oStream.write(m_LongCount);
	list<LONGDATA>::const_iterator long_itr = m_LongList.begin();
	for (; long_itr != m_LongList.end(); long_itr++)
	{
		LONGDATA long_data = *long_itr;
		oStream.write(long_data.type);
		oStream.write(long_data.value);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string ModifyInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ModifyInfo["
		<< "ShortCount:" << (int)m_ShortCount
		<< ",ShortListSet(";

	list<SHORTDATA>::const_iterator short_itr = m_ShortList.begin();
	for (; short_itr != m_ShortList.end(); short_itr++)
	{
		SHORTDATA short_data = *short_itr;
		msg << ModifyType2String[short_data.type] << ":"
			<< (int)short_data.value << ",";
	}

	msg << "),LongCount:" << (int)m_LongCount
		<< ",LongListSet(";

	list<LONGDATA>::const_iterator long_itr = m_LongList.begin();
	for (; long_itr != m_LongList.end(); long_itr++)
	{
		LONGDATA long_data = *long_itr;
		msg << ModifyType2String[long_data.type] << ":"
			<< (int)long_data.value << ",";
	}

	msg << ")]";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ModifyInfo::addShortData(ModifyType type, ushort value)
	    throw()
{
	__BEGIN_TRY

	SHORTDATA short_data;
	short_data.type = type;
	short_data.value = value;

	m_ShortList.push_back(short_data);

	m_ShortCount++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ModifyInfo::addLongData(ModifyType type, ulong value)
	    throw()
{
	__BEGIN_TRY

	LONGDATA long_data;
	long_data.type = type;
	long_data.value = value;

	m_LongList.push_back(long_data);

	m_LongCount++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ModifyInfo::popShortData(SHORTDATA& rData)
	    throw()
{
	__BEGIN_TRY

	SHORTDATA short_data = m_ShortList.front();

	rData.type = short_data.type;
	rData.value = short_data.value;

	m_ShortList.pop_front();
	m_ShortCount--;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ModifyInfo::popLongData(LONGDATA& rData)
	    throw()
{
	__BEGIN_TRY

	LONGDATA long_data = m_LongList.front();

	rData.type = long_data.type;
	rData.value = long_data.value;

	m_LongList.pop_front();
	m_LongCount--;

	__END_CATCH
}

