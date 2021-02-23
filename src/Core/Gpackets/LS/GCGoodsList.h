//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGoodsList.h 
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GOODS_LIST_H__
#define __GC_GOODS_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include <list>

#define MAX_GOODS_LIST 20

typedef struct _GoodsInfo
{
	int getPacketSize() const
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szGrade +
				szBYTE + optionType.size() +
				szItemNum +
				szDWORD;
	}

	static int getPacketMaxSize() 
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szGrade +
				szBYTE + 255 +
				szItemNum +
				szDWORD;
	}

	string toString() const
	{
		StringStream msg;
		msg << "Good( "
			<< "ObjectID : " << objectID
			<< ", ItemClass : " << (int)itemClass
			<< ", ItemType : " << itemType
			<< ", Grade : " << grade
			<< ", Options : (";

		list<OptionType_t>::const_iterator itr = optionType.begin();
		list<OptionType_t>::const_iterator endItr = optionType.end();

		for ( ; itr != endItr ; ++itr )
		{
			msg << *itr << ", ";
		}

		msg << "), Num : " << num
			<< ", TimeLimit : " << timeLimit;

		return msg.toString();
	}

	ObjectID_t     		objectID;
	BYTE           		itemClass;
	ItemType_t     		itemType;
	Grade_t				grade;
	list<OptionType_t>  optionType;
	ItemNum_t      		num;
	DWORD				timeLimit;
} GoodsInfo;

//////////////////////////////////////////////////////////////////////////////
// class GCGoodsList;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCGoodsList : public Packet 
{
public:
	GCGoodsList() throw();
	virtual ~GCGoodsList() throw();

	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_GOODS_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCGoodsList"; }
	string toString() const throw();

public:
	void		addGoodsInfo( GoodsInfo* pGI ) { m_GoodsList.push_back( pGI ); }
	GoodsInfo*	popGoodsInfo( ) { GoodsInfo* pRet = m_GoodsList.front(); if ( pRet ) m_GoodsList.pop_front(); return pRet; }

private:
	list<GoodsInfo*> m_GoodsList;
};


//////////////////////////////////////////////////////////////////////////////
// class GCGoodsListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGoodsListFactory : public PacketFactory 
{
public :
	Packet* createPacket() throw() { return new GCGoodsList(); }
	string getPacketName() const throw() { return "GCGoodsList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GOODS_LIST; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t size = szBYTE;
		size += GoodsInfo::getPacketMaxSize() * MAX_GOODS_LIST;

		return size;
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCGoodsListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCGoodsListHandler 
{
public :
	static void execute(GCGoodsList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
