//////////////////////////////////////////////////////////////////////////////
// Filename    : GCStashList.h 
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_STASH_LIST_H__
#define __GC_STASH_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include <list>

typedef struct _STASHITEM
{
	int getPacketSize() const
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szBYTE + optionType.size() +
				szDurability +
				szItemNum +
				szSilver +
				szGrade +
				szEnchantLevel;
	}

	static int getPacketMaxSize() 
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szBYTE + 255 +
				szDurability +
				szItemNum +
				szSilver +
				szGrade +
				szEnchantLevel;
	}

	ObjectID_t     		objectID;
	BYTE           		itemClass;
	ItemType_t     		itemType;
	list<OptionType_t>  optionType;
	Durability_t   		durability;
	ItemNum_t      		num;
	Silver_t       		silver;
	Grade_t       		grade;
	EnchantLevel_t 		enchantLevel;
} STASHITEM;

//////////////////////////////////////////////////////////////////////////////
// class GCStashList;
//////////////////////////////////////////////////////////////////////////////

class Item;

class GCStashList : public Packet 
{
public:
	GCStashList() throw();
	virtual ~GCStashList() throw();

	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_STASH_LIST; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCStashList"; }
	string toString() const throw();

public:
	bool isExist(BYTE rack, BYTE index) const throw();

	STASHITEM getStashItem(BYTE rack, BYTE index) const throw();
	void setStashItem(BYTE rack, BYTE index, Item* pItem) throw();

	list<SubItemInfo*>& getSubItems(BYTE rack, BYTE index) throw();

	BYTE getSubItemCount(BYTE rack, BYTE index) throw();

	Gold_t getStashGold() const throw() { return m_StashGold; }
	void setStashGold(Gold_t gold) throw() { m_StashGold = gold; }

	BYTE getStashNum() const throw() { return m_StashNum; }
	void setStashNum(BYTE num) throw() { m_StashNum = num; }
	
private:
	bool               m_bExist[STASH_RACK_MAX][STASH_INDEX_MAX];
	STASHITEM          m_pItems[STASH_RACK_MAX][STASH_INDEX_MAX];
	list<SubItemInfo*> m_pSubItems[STASH_RACK_MAX][STASH_INDEX_MAX];
	BYTE               m_SubItemsCount[STASH_RACK_MAX][STASH_INDEX_MAX];
	Gold_t             m_StashGold;
	BYTE               m_StashNum;
};


//////////////////////////////////////////////////////////////////////////////
// class GCStashListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCStashListFactory : public PacketFactory 
{
public :
	Packet* createPacket() throw() { return new GCStashList(); }
	string getPacketName() const throw() { return "GCStashList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_STASH_LIST; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t size = 0;
		PacketSize_t unit_size = 
			szBYTE*2 +                  // rack과 인덱스
			//sizeof(STASHITEM) +         // 실제 정보
			STASHITEM::getPacketMaxSize() +
			szBYTE +                    // 벨트에 들어있는 아이템의 숫자
			SubItemInfo::getSize()* 8; // 벨트 아이템(8개가 맥스)
		
		size += szBYTE; // 보관함의 갯수
		size += szBYTE; // 총 아이템의 숫자
		size += unit_size* STASH_RACK_MAX* STASH_INDEX_MAX; // 아이템이 꽉 차 있다면...
		size += szGold; // 돈

		return size;
	}

};


//////////////////////////////////////////////////////////////////////////////
// class GCStashListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCStashListHandler 
{
public :
	static void execute(GCStashList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
