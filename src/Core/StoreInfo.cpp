#include "StoreInfo.h"

void StoreItemInfo::read(SocketInputStream& iStream) throw(ProtocolException, Error)
{
	__BEGIN_TRY

	iStream.read(m_ItemExist);

	if ( m_ItemExist != 0 )
	{
		PCItemInfo::read(iStream);
		iStream.read(m_Price);
	}

	__END_CATCH
}

void StoreItemInfo::write(SocketOutputStream& oStream) const throw(ProtocolException, Error)
{
	__BEGIN_TRY

	oStream.write(m_ItemExist);
//	cout << __PRETTY_FUNCTION__ << " exist : " << (int)m_ItemExist << endl;

	if ( m_ItemExist != 0 )
	{
		PCItemInfo::write(oStream);
		oStream.write(m_Price);
	}

	__END_CATCH
}

PacketSize_t StoreInfo::getSize(bool toOther) const
{
	PacketSize_t ret = szBYTE;
	if ( toOther && m_Open == 0 ) return ret;

	ret += szBYTE + m_Sign.size() + szBYTE;

	vector<StoreItemInfo>::const_iterator itr = m_Items.begin();

	for ( ; itr != m_Items.end(); ++itr )
	{
		ret += itr->getSize();
	}

	return ret;
}

void StoreInfo::read(SocketInputStream& iStream, bool toOther) throw(ProtocolException, Error)
{
	__BEGIN_TRY

	iStream.read(m_Open);
	if ( toOther && m_Open == 0 ) return;

	BYTE szSign;
	iStream.read(szSign);

	if ( szSign != 0 ) iStream.read(m_Sign, szSign);

	BYTE ItemNum;
	iStream.read(ItemNum);

	for ( int i=0; i<ItemNum; ++i )
	{
		m_Items[i].read(iStream);
//		StoreItemInfo info;
//		info.read(iStream);
//		m_Items.push_back(info);
	}

	__END_CATCH
}

void StoreInfo::write(SocketOutputStream& oStream, bool toOther) const throw(ProtocolException, Error)
{
	__BEGIN_TRY

	oStream.write(m_Open);
//	cout << "m_Open = " << (int)m_Open << endl;
	if ( toOther && m_Open == 0 ) return;

	BYTE szSign = m_Sign.size();
	oStream.write(szSign);

	if ( szSign != 0 ) oStream.write(m_Sign);

	BYTE ItemNum = m_Items.size();
	oStream.write(ItemNum);

	vector<StoreItemInfo>::const_iterator itr = m_Items.begin();

	for ( ; itr != m_Items.end(); ++itr )
	{
		itr->write(oStream);
	}

	__END_CATCH
}

void StoreOutlook::read(SocketInputStream& iStream) throw(ProtocolException, Error)
{
	__BEGIN_TRY

	iStream.read(m_Open);
	if ( m_Open == 0 ) return;

	BYTE szSign;
	iStream.read(szSign);

	if ( szSign != 0 ) iStream.read(m_Sign, szSign);

	__END_CATCH
}

void StoreOutlook::write(SocketOutputStream& oStream) const throw(ProtocolException, Error)
{
	__BEGIN_TRY

	oStream.write(m_Open);
	if ( m_Open == 0 ) return;

	BYTE szSign = m_Sign.size();
	oStream.write(szSign);

	if ( szSign != 0 ) oStream.write(m_Sign);

	__END_CATCH
}
