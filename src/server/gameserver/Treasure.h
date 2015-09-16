//////////////////////////////////////////////////////////////////////////////
// Filename    : Treasure.h
// Written by  : excel96
// Description :
//
// BEGIN_TREASURE (50)
//   BEGIN_ITEM_CLASS (SWORD, 50)
//     <(1,50,50) (STR+1,50)(STR+2,30)(STR+3,20)>
//     <(2,30,50) (STR+1,50)(STR+2,30)(STR+3,20)>
//     <(3,20,50) (STR+1,50)(STR+2,30)(STR+3,20)>
//   END_ITEM_CLASS
//   BEGIN_ITEM_CLASS (BLADE, 50)
//     <(2,50,50) (STR+1,50)(STR+2,30)(STR+3,20)>
//     <(3,30,50) (STR+1,50)(STR+2,30)(STR+3,20)>
//     <(4,20,50) (STR+1,50)(STR+2,30)(STR+3,20)>
//   END_ITEM_CLASS
// END_TREASURE
//
// BEGIN_TREASURE (100)
//   BEGIN_ITEM_CLASS (SKULL, 100)
//     <(12,100,0)()>
//   END_ITEM_CLASS
// END_TREASURE
//////////////////////////////////////////////////////////////////////////////

#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "Types.h"
#include "Exception.h"
#include "Item.h"
#include <list>
#include <vector>
#include <fstream>
#include <map>

//class XMLTree;

struct ITEM_TEMPLATE
{
	Item::ItemClass 		ItemClass;
	int             		ItemType;
	list<OptionType_t>    	OptionType;
	bool            		bCreateOption;
	int	            		NextOptionRatio;
};

//////////////////////////////////////////////////////////////////////////////
// class TreasureOptionType
//////////////////////////////////////////////////////////////////////////////
class TreasureOptionType
{
public:
	TreasureOptionType() throw();
	~TreasureOptionType() throw();

public:
	int getOptionType(void) const { return m_OptionType; }
	int getRatio(void) const { return m_Ratio; }

public:
	void loadFromFile(ifstream& file) throw();
	void parseString(const string& text) throw();

	string toString(void) const throw();
//	XMLTree*	makeXMLTree() const;

public:
	int m_OptionType;
	int m_Ratio;
};

//////////////////////////////////////////////////////////////////////////////
// class TreasureItemType
//////////////////////////////////////////////////////////////////////////////
class TreasureItemType
{
public:
	TreasureItemType() throw();
	~TreasureItemType() throw();

public:
	int getItemType(void) const { return m_ItemType; }
	int getRatio(void) const { return m_Ratio; }

public:
	void loadFromFile(int itemClass, ifstream& file) throw();
	void parseString(int itemClass, const string& text) throw();
	bool getRandomOption(ITEM_TEMPLATE* pTemplate) throw();
	string toString(void) const throw();
//	XMLTree*	makeXMLTree() const;

public:
	int m_ItemType;
	int m_Ratio;
	int m_OptionTypeTotalRatio;
	vector<TreasureOptionType*> m_TreasureOptionTypes;
};

//////////////////////////////////////////////////////////////////////////////
// class TreasureItemClass
//////////////////////////////////////////////////////////////////////////////
class TreasureItemClass
{
public:
	TreasureItemClass() throw();
	~TreasureItemClass() throw();

public:
	Item::ItemClass getItemClass(void) const { return m_ItemClass; }
	int getRatio(void) const { return m_Ratio; }

public:
	void loadFromFile(ifstream& file) throw();
	void parseString(const string& text) throw();
	bool getRandomItem(ITEM_TEMPLATE* pTemplate) throw();
	string toString(void) const throw();
//	XMLTree*	makeXMLTree() const;

public:
	static Item::ItemClass getItemClassFromString(const string& text) throw();

public:
	Item::ItemClass m_ItemClass;
	int m_Ratio;
	int m_ItemTypeTotalRatio;
	vector<TreasureItemType*> m_TreasureItemTypes;
};

//////////////////////////////////////////////////////////////////////////////
// class Treasure
//////////////////////////////////////////////////////////////////////////////
class Treasure
{
public:
	Treasure() throw();
	~Treasure() throw();

public:
	void loadFromFile(ifstream& file) throw();
	void parseString(const string& text) throw();
	bool getRandomItem(ITEM_TEMPLATE* pTemplate) throw();
	bool getRandomItem(ITEM_TEMPLATE* pTemplate, int nPercent) throw();
	string toString(void) const throw();
//	XMLTree*	makeXMLTree() const;

public:
	int m_ItemRatio; // 아이템 자체가 나올 확률
	int m_OptionRatio; // 나온 아이템에 옵션이 붙을 확률
	int m_ItemClassTotalRatio; // 모든 아이템 클래스의 확률의 합
	vector<TreasureItemClass*> m_TreasureItemClasses;
};

//////////////////////////////////////////////////////////////////////////////
// class TreasureList
//////////////////////////////////////////////////////////////////////////////
class TreasureList
{
public:
	TreasureList() throw();
	~TreasureList() throw();

public:
	const list<Treasure*>& getTreasures(void) const { return m_Treasures; }

public:
	void loadFromFile(ifstream& file) throw();
	void parseString(const string& text) throw();
	void addTreasure(Treasure* pTreasure) throw();

	string toString(void) const throw();
//	XMLTree*	makeXMLTree() const;

public:
	list<Treasure*> m_Treasures;
};


class TreasureLists
{
public :
    TreasureLists();
    ~TreasureLists();

    void clear();

    TreasureList*   getTreasure(const string& filename) const;
    void            addTreasure(const string& filename, TreasureList* pTreasureList);
    TreasureList*   loadTreasure(const string& filename);

private :
    map<string, TreasureList*>     m_TreasureLists;
};

#endif
