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
#include <unordered_map>

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
	TreasureOptionType() ;
	~TreasureOptionType() ;

public:
	int getOptionType(void) const { return m_OptionType; }
	int getRatio(void) const { return m_Ratio; }

public:
	void loadFromFile(ifstream& file) ;
	void parseString(const string& text) ;

	string toString(void) const ;
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
	TreasureItemType() ;
	~TreasureItemType() ;

public:
	int getItemType(void) const { return m_ItemType; }
	int getRatio(void) const { return m_Ratio; }

public:
	void loadFromFile(int itemClass, ifstream& file) ;
	void parseString(int itemClass, const string& text) ;
	bool getRandomOption(ITEM_TEMPLATE* pTemplate) ;
	string toString(void) const ;
//	XMLTree*	makeXMLTree() const;

public:
	int m_ItemType;
	int m_Ratio;
	int m_OptionTypeTotalRatio;
	vector<TreasureOptionType*> m_TreasureOptionTypes;

	void setRndItemOptionMax( int Value=2 ){ m_OptionRatioMax=Value; }
	int  getRndItemOptionMax( ) { return m_OptionRatioMax ; }
	int  m_OptionRatioMax;
};

//////////////////////////////////////////////////////////////////////////////
// class TreasureItemClass
//////////////////////////////////////////////////////////////////////////////
class TreasureItemClass
{
public:
	TreasureItemClass() ;
	~TreasureItemClass() ;

public:
	Item::ItemClass getItemClass(void) const { return m_ItemClass; }
	int getRatio(void) const { return m_Ratio; }

public:
	void loadFromFile(ifstream& file) ;
	void parseString(const string& text) ;
	bool getRandomItem(ITEM_TEMPLATE* pTemplate) ;
	string toString(void) const ;
//	XMLTree*	makeXMLTree() const;

public:
	static Item::ItemClass getItemClassFromString(const string& text) ;

public:
	Item::ItemClass m_ItemClass;
	int m_Ratio;
	int m_ItemTypeTotalRatio;
	vector<TreasureItemType*> m_TreasureItemTypes;
	
	// Add By Sonic 2006.10.21  增加一个掉宝属性最大值变量
	void setRndItemOptionMax( int Value=2 ){ m_OptionRatioMax=Value; }
	int  getRndItemOptionMax( ) { return m_OptionRatioMax ; }
	int  m_OptionRatioMax;
	// End By Sonic 2006.10.21
};

//////////////////////////////////////////////////////////////////////////////
// class Treasure
//////////////////////////////////////////////////////////////////////////////
class Treasure
{
public:
	Treasure() ;
	~Treasure() ;

public:
	void loadFromFile(ifstream& file) ;
	void parseString(const string& text) ;
	bool getRandomItem(ITEM_TEMPLATE* pTemplate) ;
	bool getRandomItem(ITEM_TEMPLATE* pTemplate, int nPercent) ;
	
	string toString(void) const ;
//	XMLTree*	makeXMLTree() const;

public:
	int m_ItemRatio; // 酒捞袍 磊眉啊 唱棵 犬伏
	int m_OptionRatio; // 唱柯 酒捞袍俊 可记捞 嘿阑 犬伏
	int m_ItemClassTotalRatio; // 葛电 酒捞袍 努贰胶狼 犬伏狼 钦
	vector<TreasureItemClass*> m_TreasureItemClasses;
	// Add By Sonic 2006.10.21  增加一个掉宝属性最大值变量
	void setRndItemOptionMax( int Value=2 ){ m_OptionRatioMax=Value; }
	int  getRndItemOptionMax( ) { return m_OptionRatioMax ; }
	int  m_OptionRatioMax;
	// End By Sonic 2006.10.21
};

//////////////////////////////////////////////////////////////////////////////
// class TreasureList
//////////////////////////////////////////////////////////////////////////////
class TreasureList
{
public:
	TreasureList() ;
	~TreasureList() ;

public:
	const list<Treasure*>& getTreasures(void) const { return m_Treasures; }

public:
	void loadFromFile(ifstream& file) ;
	void parseString(const string& text) ;
	void addTreasure(Treasure* pTreasure) ;

	string toString(void) const ;
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
    unordered_map<string, TreasureList*>     m_TreasureLists;
};

#endif
