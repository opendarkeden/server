//////////////////////////////////////////////////////////////////////////////
// Filename    : Treasure.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Treasure.h"
#include "Assert1.h"
#include "StringStream.h"
#include "OptionInfo.h"
#include "ItemInfoManager.h"
#include "VariableManager.h"
#include "UniqueItemManager.h"
#include "ItemUtil.h"
#include <string.h>

#include "SXml.h"

#include <map>

const uint TREASURE_RATIO_MODULUS = 100000;

//////////////////////////////////////////////////////////////////////////////
// class TreasureOptionType member methods
//////////////////////////////////////////////////////////////////////////////

TreasureOptionType::TreasureOptionType()
	throw()
{
	__BEGIN_TRY

	m_Ratio      = 0;
	m_OptionType = 0;

	__END_CATCH
}

TreasureOptionType::~TreasureOptionType()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void TreasureOptionType::loadFromFile(ifstream& file) 
	throw()
{
	__BEGIN_TRY

	file.read((char*)&m_OptionType, sizeof(int));
	file.read((char*)&m_Ratio, sizeof(int));

	try
	{
		OptionInfo* pInfo = g_pOptionInfoManager->getOptionInfo(m_OptionType);
		Assert(pInfo!=NULL);
	}
	catch (NoSuchElementException & nsee)
	{
		cerr << "TreasureOptionType::loadFromFile() : Unknown Option" << endl;
		throw("TreasureOptionType::loadFromFile() : Unknown Option");
	}

	__END_CATCH
}

void TreasureOptionType::parseString(const string& text) 
	throw()
{
	__BEGIN_TRY

	//cout << "OptionTypeText:" << text << endl;

	if (text.size() < 3) return;

    size_t a = text.find_first_of(',', 0);

	if (a != string::npos)
	{
		string optionString = trim(text.substr(0, a));
		m_Ratio = atoi(text.substr(a+1, text.size()-a-1).c_str());

		// 옵션 스트링을 이용해서, 옵션 타입을 얻어낸다.
		try
		{
			OptionInfo* pInfo = g_pOptionInfoManager->getOptionInfo(optionString);
			Assert(pInfo!=NULL);
			m_OptionType = pInfo->getType();
		}
		catch (NoSuchElementException & nsee)
		{
			cerr << "TreasureOptionType::parseString() : Unknown Option String[" << optionString << "]" << endl;
			throw("TreasureOptionType::parseString() : Unknown Option String");
		}
	}
	else
	{
		cerr << "TreasureOptionType::parseString() : Error[" << text << "]" << endl;
		throw("TreasureOptionType::parseString() : Error");
	}

	__END_CATCH
}

string TreasureOptionType::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "TreasureOptionType("
		<< "OptionType:" << m_OptionType
		<< ",Ratio:" << m_Ratio
		<< ")";
	return msg.toString();

	__END_CATCH
}

/*XMLTree* TreasureOptionType::makeXMLTree() const
{
	XMLTree* ret = NULL;
	OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(m_OptionType);
	if (pOptionInfo != NULL )
	{
		ret = new XMLTree("OptionType");
		ret->AddAttribute("Option", pOptionInfo->getNickname());
		ret->AddAttribute("Ratio", m_Ratio);
	}

	return ret;
}*/

//////////////////////////////////////////////////////////////////////////////
// class TreasureItemType member methods
//////////////////////////////////////////////////////////////////////////////

TreasureItemType::TreasureItemType()
	throw()
{
	__BEGIN_TRY
		
	m_ItemType = 0;
	m_Ratio    = 0;

	__END_CATCH
}

TreasureItemType::~TreasureItemType()
	throw()
{
	__BEGIN_TRY
		
	for (uint i=0; i<m_TreasureOptionTypes.size(); i++)
	{
		TreasureOptionType* pTOT = m_TreasureOptionTypes[i];
		SAFE_DELETE(pTOT);
	}

	m_TreasureOptionTypes.clear();

	__END_CATCH
}

void TreasureItemType::loadFromFile(int itemClass, ifstream& file) 
	throw()
{
	__BEGIN_TRY

	int OptionTypeCount = 0;

	file.read((char*)&m_ItemType, sizeof(int));
	file.read((char*)&m_Ratio, sizeof(int));
	file.read((char*)&OptionTypeCount, sizeof(int));

	// 지정된 아이템 타입이 존재하는지를 체크한다.
	list<OptionType_t> optionNULL;
	if (!g_pItemInfoManager->isPossibleItem((Item::ItemClass)itemClass, m_ItemType, optionNULL))
	{
		StringStream msg;
		msg << "TreasureItemType::loadFromFile() : Invalid Item Type!\n" 
			<< "ItemClass:" << ItemClass2String[itemClass] 
			<< ",ItemType:" << (int)m_ItemType << "\n";
		cerr << msg.toString();
		throw(msg.toString());
	}

	for (int i=0; i<OptionTypeCount; i++)
	{
		TreasureOptionType* pTOT = new TreasureOptionType;
		pTOT->loadFromFile(file);
		m_TreasureOptionTypes.push_back(pTOT);
	}

	// 확률합계를 계산해 둔다.
	m_OptionTypeTotalRatio = 0;
	for (uint i=0; i<m_TreasureOptionTypes.size(); i++)
	{
		TreasureOptionType* pTOT = m_TreasureOptionTypes[i];
		m_OptionTypeTotalRatio += pTOT->getRatio();
	}

	__END_CATCH
}

void TreasureItemType::parseString(int itemClass, const string& text) 
	throw()
{
	__BEGIN_TRY
	
	////////////////////////////////////////////////////////////
	// (1,50) (STR+1,50)(STR+2,30)(STR+30)
	////////////////////////////////////////////////////////////
	
	// 먼저 item type을 읽어들인다.
    size_t i = text.find_first_of('(', 0);
    size_t j = text.find_first_of(',', i+1);
    size_t k = text.find_first_of(')', j+1);

	if (i == string::npos || j == string::npos || k == string::npos)
	{
		cerr << "TreasureItemType::parseString() : Error" << endl;
		throw("TreasureItemType::parseString() : Error");
	}

	m_ItemType    = atoi(trim(text.substr(i+1, j-i-1)).c_str());
	m_Ratio       = atoi(trim(text.substr(j+1, k-j-1)).c_str());

	// 지정된 아이템 타입이 존재하는지를 체크한다.
	list<OptionType_t> optionNULL;
	if (!g_pItemInfoManager->isPossibleItem((Item::ItemClass)itemClass, m_ItemType, optionNULL))
	{
		StringStream msg;
		msg << "TreasureItemType::parseString() : Invalid Item Type!\n" 
			<< "ItemClass:" << ItemClass2String[itemClass] 
			<< ",ItemType:" << (int)m_ItemType << "\n";
		cerr << msg.toString();
		throw(msg.toString());
	}

	// 옵션 정보를 읽어들인다.
	string newText = text.substr(k+1, text.size()-k-1);

    size_t a = 0;
    size_t b = 0;

	if (newText.size() > 0)
	{
		while (b < newText.size()-1)
		{
			////////////////////////////////////////////////////////////
			// (STR+1,50)(STR+2,30)(STR+30)
			////////////////////////////////////////////////////////////
			a = newText.find_first_of('(', b);
			b = newText.find_first_of(')', a);

			if (a == string::npos || b == string::npos) break;

			string substring = trim(newText.substr(a+1, b-a-1));

			//cout << "TIT::substring\n" << substring << endl << endl;

			TreasureOptionType* pTOT = new TreasureOptionType;
			pTOT->parseString(substring);

			m_TreasureOptionTypes.push_back(pTOT);

			substring.clear();
		}
	}

	newText.clear();

	// 파싱이 끝났으니, 확률합계를 계산해 둔다.
	m_OptionTypeTotalRatio = 0;
	for (uint i=0; i<m_TreasureOptionTypes.size(); i++)
	{
		TreasureOptionType* pTOT = m_TreasureOptionTypes[i];
		m_OptionTypeTotalRatio += pTOT->getRatio();
	}
	
	__END_CATCH
}

bool TreasureItemType::getRandomOption(ITEM_TEMPLATE* pTemplate)
	throw()
{
	__BEGIN_TRY

	if (m_OptionTypeTotalRatio == 0) 
	{
		//pTemplate->OptionType.clear();
		//cout << "OptionTypeTotalRatio = 0" << endl;
		return false;
	}
		
	for (int k=0; k<2; k++)
	{
		bool bOneMore = false;

		int optionRatio = rand()%m_OptionTypeTotalRatio;
		int ratioSum    = 0;

		//cout << "numOption=" << m_TreasureOptionTypes.size()
		//	 << ", Ratio=" << optionRatio << "/" << m_OptionTypeTotalRatio << endl;

		for (uint i=0; i<m_TreasureOptionTypes.size(); i++)
		{
			TreasureOptionType* pTOT = m_TreasureOptionTypes[i];

			ratioSum += pTOT->getRatio();

			if (optionRatio < ratioSum)
			{
				if (pTemplate->bCreateOption)
				{
					// 이미 그 옵션이 붙어있는 경우
					if (hasOptionClass(pTemplate->OptionType, pTOT->getOptionType() ))
					{
						// 더 이상 찾지 말자.
						//cout << "has Same OptionClass(" << pTOT->getOptionType() << ")" << endl;
						return true;
					}

					if (pTOT->getOptionType()!=0)
					{
						//cout << "add Option: " << pTOT->getOptionType() << endl;
						pTemplate->OptionType.push_back(pTOT->getOptionType());
					}
				}
				//else
				{
					//pTemplate->OptionType = 0;
				}

				// 옵션이 하나 더 붙을 확률 체크 해서 통과하면
				// 한번더 옵션의 확률을 체크해보자.
				if (isPossibleNextOption(pTemplate))
				{
					bOneMore = true;
					break;
				}

				return true;
			}
		}

		if (!bOneMore)
		{
			// 옵션을 선택하지 못한 경우?
			break;
		}
	}
	//while (1);

	//cout << "Cannot Select Option: "
	//	<< optionRatio << ", "
	//	<< ratioSum << endl;
	return false;

	__END_CATCH
}

string TreasureItemType::toString(void) const
	throw()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "\tTreasureItemType\n\t\t\t("
		<< "\n\t\t\t\tItemType:" << m_ItemType
		<< ",Ratio:" << m_Ratio << "\n";

	for (uint i=0; i<m_TreasureOptionTypes.size(); i++)
	{
		msg << "\t\t\t\t" << m_TreasureOptionTypes[i]->toString() << "\n";
	}

	msg	<< "\n\t\t\t)";
	return msg.toString();

	__END_CATCH
}

/*XMLTree* TreasureItemType::makeXMLTree() const
{
	XMLTree* ret = new XMLTree("ItemType");
	ret->AddAttribute("Type", m_ItemType);
	ret->AddAttribute("Ratio", m_Ratio);

	vector<TreasureOptionType*>::const_iterator itr = m_TreasureOptionTypes.begin();
	vector<TreasureOptionType*>::const_iterator endItr = m_TreasureOptionTypes.end();

	for (; itr != endItr ; ++itr )
	{
		ret->AddChild((*itr)->makeXMLTree());
	}

	return ret;
}*/

//////////////////////////////////////////////////////////////////////////////
// class TreasureItemClass member methods
//////////////////////////////////////////////////////////////////////////////

TreasureItemClass::TreasureItemClass()
	throw()
{
	__BEGIN_TRY

	m_ItemClass = Item::ITEM_CLASS_MAX;
	m_Ratio     = 0;

	__END_CATCH
}

TreasureItemClass::~TreasureItemClass()
	throw()
{
	__BEGIN_TRY

	for (uint i=0; i<m_TreasureItemTypes.size(); i++)
	{
		TreasureItemType* pTIT = m_TreasureItemTypes[i];
		SAFE_DELETE(pTIT);
	}

	m_TreasureItemTypes.clear();

	__END_CATCH
}

void TreasureItemClass::loadFromFile(ifstream& file) 
	throw()
{
	__BEGIN_TRY

	int ItemTypeCount = 0;
	file.read((char*)&m_ItemClass, sizeof(int));
	file.read((char*)&m_Ratio, sizeof(int));
	file.read((char*)&ItemTypeCount, sizeof(int));

	for (int i=0; i<ItemTypeCount; i++)
	{
		TreasureItemType* pTIT = new TreasureItemType;
		pTIT->loadFromFile(m_ItemClass, file);
		m_TreasureItemTypes.push_back(pTIT);
	}

	// 전체 확률의 합을 계산해 둔다.
	m_ItemTypeTotalRatio = 0;
	for (uint i=0; i<m_TreasureItemTypes.size(); i++)
	{
		TreasureItemType* pTIT = m_TreasureItemTypes[i];
		m_ItemTypeTotalRatio += pTIT->getRatio();
	}

	__END_CATCH
}

void TreasureItemClass::parseString(const string& text) 
	throw()
{
	__BEGIN_TRY

	////////////////////////////////////////////////////////////
	// (SWORD, 50)
	// <(1,50) (STR+1,50)(STR+2,30)(STR+3,20)>
	// <(2,30) (STR+1,50)(STR+2,30)(STR+3,20)>
	// <(3,20) (STR+1,50)(STR+2,30)(STR+3,20)>
	////////////////////////////////////////////////////////////
	
	// 아이템 클래스 및 확률을 읽어들인다. 
    size_t i = text.find_first_of('(', 0);
    size_t j = text.find_first_of(',', i+1);
    size_t k = text.find_first_of(')', j+1);

	string itemClassString = trim(text.substr(i+1, j-i-1));
	m_Ratio = atoi(trim(text.substr(j+1, k-j-1)).c_str());

	// 문자열로부터 아이템 클래스를 얻어낸다.
	m_ItemClass = getItemClassFromString(itemClassString);

	string newText = text.substr(k+1, text.size()-k-1);

	//cout << "TIC::newText\n" << newText << endl << endl;

    size_t a = 0;
    size_t b = 0;

	while (b < newText.size()-1)
	{
		////////////////////////////////////////////////////////////
		// <(1,50,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// <(2,30,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// <(3,20,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		////////////////////////////////////////////////////////////
		a = newText.find_first_of('<', b);
		b = newText.find_first_of('>', a);

		if (a == string::npos || b == string::npos) break;

		string substring = trim(newText.substr(a+1, b-a-1));

		//cout << "TIC::substring\n" << substring << endl << endl;

		TreasureItemType* pTIT = new TreasureItemType;
		pTIT->parseString(m_ItemClass, substring);

		m_TreasureItemTypes.push_back(pTIT);

		substring.clear();
	}

	newText.clear();
	
	// 파싱이 끝났으면, 전체 확률의 합을 계산해 둔다.
	m_ItemTypeTotalRatio = 0;
	for (uint i=0; i<m_TreasureItemTypes.size(); i++)
	{
		TreasureItemType* pTIT = m_TreasureItemTypes[i];
		m_ItemTypeTotalRatio += pTIT->getRatio();
	}

	__END_CATCH
}

bool TreasureItemClass::getRandomItem(ITEM_TEMPLATE* pTemplate)
	throw()
{
	__BEGIN_TRY

	int itemTypeRatio = rand()%TREASURE_RATIO_MODULUS;
	int ratioSum      = 0;

	for (uint i=0; i<m_TreasureItemTypes.size(); i++)
	{
		TreasureItemType* pTIT = m_TreasureItemTypes[i];
		ratioSum += pTIT->getRatio();

		if (itemTypeRatio < ratioSum)
		{
			pTemplate->ItemType = pTIT->getItemType();

			// 유니크 아이템에 관한 체크를 해야한다. by sigi. 2002.8.16
			ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pTemplate->ItemClass, pTemplate->ItemType);
			Assert(pItemInfo!=NULL);

			// 유니크 아이템인 경우
			if (pItemInfo->isUnique())
			{
				int okRatio = rand()%10000; 
				int uniqueRatio = g_pVariableManager->getUniqueItemRatio();

				if (okRatio < uniqueRatio
					&& UniqueItemManager::isPossibleCreate(
											pTemplate->ItemClass, pTemplate->ItemType))
				{
					// unique는 option이 붙지 않는다.
					return true;
				}

				// 유니크 확률에 걸렸는데..
				// 유니크 숫자제한 때문에 생성 불가능한 경우이다.
				return false;
			}
			else
			{
				pTIT->getRandomOption(pTemplate);
				return true;
			}

		}
	}

	return false;

	__END_CATCH
}

string TreasureItemClass::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "\tTreasureItemClass\n\t\t(" 
		<< "\n\t\t\tItemClass:" << m_ItemClass
		<< ",Ratio:" << m_Ratio << "\n";

	for (uint i=0; i<m_TreasureItemTypes.size(); i++)
	{
		msg << "\t\t" << m_TreasureItemTypes[i]->toString() << "\n";
	}
	
	msg << "\n\t\t)";
	return msg.toString();

	__END_CATCH
}

/*XMLTree* TreasureItemClass::makeXMLTree() const
{
	XMLTree* ret = new XMLTree("ItemClass");
	ret->AddAttribute("Class", ItemClass2ShortString[m_ItemClass]);
	ret->AddAttribute("Ratio", m_Ratio);

	vector<TreasureItemType*>::const_iterator itr = m_TreasureItemTypes.begin();
	vector<TreasureItemType*>::const_iterator endItr = m_TreasureItemTypes.end();

	for (; itr != endItr ; ++itr )
	{
		ret->AddChild((*itr)->makeXMLTree());
	}

	return ret;
}*/

Item::ItemClass TreasureItemClass::getItemClassFromString(const string& text) 
	throw()
{
	__BEGIN_TRY

	for (int i=0; i<Item::ITEM_CLASS_MAX; i++)
	{
		if (strcasecmp(text.c_str(), ItemClass2ShortString[i].c_str()) == 0)
		{
			return (Item::ItemClass)i;
		}
	}

	StringStream msg;
	msg << "TreasureItemClass::getItemClassFromString() : Unknown String[" << text << "]";
	cerr << msg.toString() << endl;
	throw(msg.toString());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class Treasure member methods
//////////////////////////////////////////////////////////////////////////////

Treasure::Treasure()
	throw()
{
	__BEGIN_TRY

	m_ItemRatio           = 0;
	m_OptionRatio         = 0;
	m_ItemClassTotalRatio = 0;

	__END_CATCH
}

Treasure::~Treasure()
	throw()
{
	__BEGIN_TRY

	for (uint i=0; i<m_TreasureItemClasses.size(); i++)
	{
		TreasureItemClass* pTIC = m_TreasureItemClasses[i];
		SAFE_DELETE(pTIC);
	}

	m_TreasureItemClasses.clear();

	__END_CATCH
}

void Treasure::loadFromFile(ifstream& file) 
	throw()
{
	__BEGIN_TRY

	int ItemClassCount = 0;

	file.read((char*)&m_ItemRatio, sizeof(int));
	file.read((char*)&m_OptionRatio, sizeof(int));
	file.read((char*)&ItemClassCount, sizeof(int));

	for (int i=0; i<ItemClassCount; i++)
	{
		TreasureItemClass* pTIC = new TreasureItemClass;
		pTIC->loadFromFile(file);
		m_TreasureItemClasses.push_back(pTIC);
	}

	// 확률 합계를 계산해 둔다.
	m_ItemClassTotalRatio = 0;
	for (uint i=0; i<m_TreasureItemClasses.size(); i++)
	{
		TreasureItemClass* pTIC = m_TreasureItemClasses[i];
		m_ItemClassTotalRatio += pTIC->getRatio();
	}

	__END_CATCH
}

void Treasure::parseString(const string& text) 
	throw()
{
	__BEGIN_TRY

	////////////////////////////////////////////////////////////
	// (50,50)
	// BEGIN_ITEM_CLASS (SWORD, 50)
	// <(1,50)(STR+1,50)(STR+2,30)(STR+3,20)>
	// <(2,30)(STR+1,50)(STR+2,30)(STR+3,20)>
	// <(3,20)(STR+1,50)(STR+2,30)(STR+3,20)>
	// END_ITEM_CLASS
	// BEGIN_ITEM_CLASS (BLADE, 50)
	// <(1,50)(STR+1,50)(STR+2,30)(STR+3,20)>
	// <(2,30)(STR+1,50)(STR+2,30)(STR+3,20)>
	// <(3,20)(STR+1,50)(STR+2,30)(STR+3,20)>
	// END_ITEM_CLASS
	////////////////////////////////////////////////////////////
	
	// 먼저 아이템 자체가 나올 확률과, 그 아이템에 옵션이 붙을 확률을 읽어들인다.
    size_t i = text.find_first_of('(');
    size_t j = text.find_first_of(',');
    size_t k = text.find_first_of(')');

	if (i == string::npos || j == string::npos || k == string::npos) 
	{
		cerr << "Treasure::parseString() : Error" << endl;
		throw("Treasure::parseString() : Error");
	}

	//m_ItemRatio = atoi(trim(text.substr(i+1, j-i-1)).c_str()) * 150 / 100 ;
	m_ItemRatio = atoi(trim(text.substr(i+1, j-i-1)).c_str());

	// 보상을 위한 코드
	//m_ItemRatio = (int)((float)atoi(trim(text.substr(i+1, j-i-1)).c_str()) * 1.5);
	
	//m_OptionRatio = atoi(trim(text.substr(j+1, k-j-1)).c_str()) * 150 / 100;
	m_OptionRatio = atoi(trim(text.substr(j+1, k-j-1)).c_str());

	// 아이템 자체가 나올 확률을 읽어들였으니, 잘라낸다.
	string newText = trim(text.substr(k+1, text.size()-k-1));

	string btoken = "BEGIN_ITEMCLASS";
	string etoken = "END_ITEMCLASS";
	uint   BTOKENSIZE = btoken.size();

    size_t a = 0;
    size_t b = 0;

	while (b < newText.size()-1)
	{
		////////////////////////////////////////////////////////////
		// BEGIN_ITEM_CLASS (SWORD, 50)
		// <(1,50,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// <(2,30,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// <(3,20,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// END_ITEM_CLASS
		// BEGIN_ITEM_CLASS (BLADE, 50)
		// <(1,50,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// <(2,30,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// <(3,20,50) (STR+1,50)(STR+2,30)(STR+3,20)>
		// END_ITEM_CLASS
		////////////////////////////////////////////////////////////
		a = newText.find(btoken, b);
		b = newText.find(etoken, a+1);
	
		if (a == string::npos || b == string::npos) break;

		string substring = trim(newText.substr(a+BTOKENSIZE, b-a-BTOKENSIZE));

		TreasureItemClass* pTIC = new TreasureItemClass;
		pTIC->parseString(substring);

		m_TreasureItemClasses.push_back(pTIC);

		substring.clear();
	}

	newText.clear();

	// 파싱이 끝났으면, 전체 확률을 계산한다.
	m_ItemClassTotalRatio = 0;
	for (uint i=0; i<m_TreasureItemClasses.size(); i++)
	{
		TreasureItemClass* pTIC = m_TreasureItemClasses[i];
		m_ItemClassTotalRatio += pTIC->getRatio();
	}
	
	__END_CATCH
}

bool Treasure::getRandomItem(ITEM_TEMPLATE* pTemplate)
	throw()
{
	__BEGIN_TRY

	
	// 트레져리스트에 아이템이 없는 경우일 꺼다..아마도...생까자~.
	if (0 == m_ItemClassTotalRatio )
		return false;

	// 먼저 아이템이 나올지 안 나올지에 대한 확률체크를 시행한다.
	int ItemRatio = rand()%TREASURE_RATIO_MODULUS;

	//cout << "Item확률체크: " << ItemRatio << " " << m_ItemRatio << endl
	//	 << "수정확률"       << ItemRatio << " " << g_pVariableManager->getItemProbRatio()/100 << endl;

	//cout << "Item확률 체크 : " << ItemRatio << " < " << m_ItemRatio << endl;

	// 아이템이 나오기로 결정되었다면...
	double EventMultiplier = 0.0;
	if(g_pVariableManager->getEventActivate() == 1)
		EventMultiplier = g_pVariableManager->getItemProbRatio()/100;
	else
		EventMultiplier = 1;

	if (ItemRatio < m_ItemRatio * EventMultiplier)
	{
		int OptionRatio = rand()%TREASURE_RATIO_MODULUS;

		if (OptionRatio < m_OptionRatio)
		{
			pTemplate->bCreateOption = true;
		}
		else
		{
			pTemplate->bCreateOption = false;
		}

		//cout << "옵션 확률 체크 : " << OptionRatio << " < " << m_OptionRatio << endl;

		int itemClassRatio = rand()%m_ItemClassTotalRatio;
		int ratioSum       = 0;
		int preRatioSum	   = 0;

		//cout << "아이템 클래스 확률 : " << itemClassRatio << " / " << m_ItemClassTotalRatio << endl;

		for (uint i=0; i<m_TreasureItemClasses.size(); i++)
		{
			TreasureItemClass* pTIC = m_TreasureItemClasses[i];

			preRatioSum = ratioSum;
			ratioSum += pTIC->getRatio();

			if (itemClassRatio > preRatioSum && itemClassRatio < ratioSum)
			{
				pTemplate->ItemClass = pTIC->getItemClass();
				if (pTIC->getRandomItem(pTemplate))
					return true;
				else
					return false;
			}
		}
	}

	return false;

	__END_CATCH
}

bool Treasure::getRandomItem(ITEM_TEMPLATE* pTemplate, int nPercent)
	throw()
{
	__BEGIN_TRY

	// 먼저 아이템이 나올지 안 나올지에 대한 확률체크를 시행한다.
	int ItemRatio = rand()%TREASURE_RATIO_MODULUS;

	// 아이템 확률에 수정치 대입
	int ModifyItemRatio = getPercentValue(m_ItemRatio, nPercent);

//	cout << "Item value : " << ItemRatio << endl;
//	cout << "Bonus Ratio : " << nPercent << endl;
//	cout << "Item Ratio : " << ModifyItemRatio << endl;

	if (ItemRatio < ModifyItemRatio )
	{
		int OptionRatio = rand()%TREASURE_RATIO_MODULUS;

		if (OptionRatio < m_OptionRatio)
		{
			pTemplate->bCreateOption = true;
		}
		else
		{
			pTemplate->bCreateOption = false;
		}

		//cout << "옵션 확률 체크 : " << OptionRatio << " < " << m_OptionRatio << endl;

		if (m_ItemClassTotalRatio == 0 )
			return false;

		int itemClassRatio = rand()%m_ItemClassTotalRatio;
		int ratioSum       = 0;
		int preRatioSum	   = 0;

		//cout << "아이템 클래스 확률 : " << itemClassRatio << " / " << m_ItemClassTotalRatio << endl;

		for (uint i=0; i<m_TreasureItemClasses.size(); i++)
		{
			TreasureItemClass* pTIC = m_TreasureItemClasses[i];

			preRatioSum = ratioSum;
			ratioSum += pTIC->getRatio();

			if (itemClassRatio > preRatioSum && itemClassRatio < ratioSum)
			{
				pTemplate->ItemClass = pTIC->getItemClass();
				if (pTIC->getRandomItem(pTemplate))
					return true;
				else
					return false;
			}
		}
	}

	return false;

	__END_CATCH
}

string Treasure::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "\tTreasure\n\t("
		<< "\n\t\tItemRatio:" << m_ItemRatio
		<< "\n\t\tOptionRatio:" << m_ItemRatio << "\n";

	for (uint i=0; i<m_TreasureItemClasses.size(); i++)
	{
		msg << "\t" << m_TreasureItemClasses[i]->toString() << "\n";
	}

	msg	<< "\n\t)";
	return msg.toString();

	__END_CATCH
}

/*XMLTree* Treasure::makeXMLTree() const
{
	XMLTree* ret = new XMLTree("Treasure");
	ret->AddAttribute("Ratio", m_ItemRatio);
	ret->AddAttribute("OptionRatio", m_OptionRatio);

	vector<TreasureItemClass*>::const_iterator itr = m_TreasureItemClasses.begin();
	vector<TreasureItemClass*>::const_iterator endItr = m_TreasureItemClasses.end();

	for (; itr != endItr ; ++itr )
	{
		ret->AddChild((*itr)->makeXMLTree());
	}

	return ret;
}*/

//////////////////////////////////////////////////////////////////////////////
// class TreasureList member methods
//////////////////////////////////////////////////////////////////////////////

TreasureList::TreasureList()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

TreasureList::~TreasureList()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void TreasureList::loadFromFile(ifstream& file) 
	throw()
{
	__BEGIN_TRY

	
	// 기존에 있던걸 지워준다.
	list<Treasure*>::iterator itr = m_Treasures.begin();
	for (; itr!=m_Treasures.end(); itr++)
	{
		Treasure* pTreasure = *itr;
		SAFE_DELETE(pTreasure);
	}
	m_Treasures.clear();


	// 다시 로딩
	int TreasureCount = 0;
	file.read((char*)&TreasureCount, sizeof(int));

	for (int i=0; i<TreasureCount; i++)
	{
		Treasure* pTreasure = new Treasure;
		pTreasure->loadFromFile(file);
		addTreasure(pTreasure);
	}

	__END_CATCH
}

void TreasureList::parseString(const string& text) 
	throw()
{
	__BEGIN_TRY

	////////////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////
	
	string bToken = "BEGIN_TREASURE";
	string eToken = "END_TREASURE";
	uint   BTOKENSIZE = bToken.size();

    size_t a = 0;
    size_t b = 0;

	int count = 0;

	while (b < text.size())
	{
		a = text.find(bToken, b);
		b = text.find(eToken, a+1);

		if (a == string::npos || b == string::npos) break;

		string substring = trim(text.substr(a+BTOKENSIZE, b-a-BTOKENSIZE));

		//cout << "TreasureList SubString:\n" << substring << endl << endl;

		Treasure* pTreasure = new Treasure;
		pTreasure->parseString(substring);
		addTreasure(pTreasure);

		count += 1;

		substring.clear();
	}

	__END_CATCH
}

void TreasureList::addTreasure(Treasure* pTreasure)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasure != NULL);
	m_Treasures.push_back(pTreasure);

	__END_CATCH
}

string TreasureList::toString(void) const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "TreasureList\n(\n";

	list<Treasure*>::const_iterator itr = m_Treasures.begin();
	for (; itr != m_Treasures.end(); itr++)
	{
		msg << (*itr)->toString() << "\n";
	}

	msg << "\n)";
	return msg.toString();

	__END_CATCH
}

/*XMLTree* TreasureList::makeXMLTree() const
{
	XMLTree* ret = new XMLTree("TreasureList");

	list<Treasure*>::const_iterator itr = m_Treasures.begin();
	list<Treasure*>::const_iterator endItr = m_Treasures.end();

	for (; itr != endItr ; ++itr )
	{
		ret->AddChild((*itr)->makeXMLTree());
	}

	return ret;
}*/

TreasureLists::TreasureLists()
{
}

TreasureLists::~TreasureLists()
{
	clear();
}

void 
TreasureLists::clear()
{
	map<string, TreasureList*>::iterator itr = m_TreasureLists.begin();
	for (; itr!=m_TreasureLists.end(); itr++)
	{
		TreasureList* pTreasureList = itr->second;
		SAFE_DELETE(pTreasureList);
	}
	m_TreasureLists.clear();
}

TreasureList*   
TreasureLists::getTreasure(const string& filename) const
{
	map<string, TreasureList*>::const_iterator itr = m_TreasureLists.find(filename);

	if (itr!=m_TreasureLists.end())
	{
		return itr->second;
	}

	return NULL;
}

void            
TreasureLists::addTreasure(const string& filename, TreasureList* pTreasureList)
{
	map<string, TreasureList*>::const_iterator itr = m_TreasureLists.find(filename);

	if (itr!=m_TreasureLists.end())
	{
		TreasureList* pTreasureList = itr->second;
		SAFE_DELETE(pTreasureList);
	}

	m_TreasureLists[filename] = pTreasureList;
}

TreasureList*            
TreasureLists::loadTreasure(const string& filename)
{
	TreasureList* pTreasureList = new TreasureList;
	ifstream file(filename.c_str(), ios::in | ios::binary);

	if (!file)
	{
		StringStream msg;
		msg << "Cannot open " << filename << " to read.";
		cerr << msg.toString() << endl;
		throw(msg.toString());
	}

	pTreasureList->loadFromFile(file);
	file.close();

	addTreasure(filename, pTreasureList);

//	cout << "Generating XML File.. " << endl;
//	XMLTree* pXML = pTreasureList->makeXMLTree();
//	pXML->SaveToFile((filename+".xml").c_str());

	return pTreasureList;
}

