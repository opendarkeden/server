//////////////////////////////////////////////////////////////////////////////
// Filename    : OptionInfo.cpp
// Written By  : 김성민
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "OptionInfo.h"
#include "Assert1.h"
#include "DB.h"
#include "StringStream.h"
#include <algorithm>

#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

#include <map>

//////////////////////////////////////////////////////////////////////////////
// global varible initialization
//////////////////////////////////////////////////////////////////////////////
OptionInfoManager* g_pOptionInfoManager = NULL;


// itemClass에 optionType이 붙을 수 있는가?
bool
isPossibleOptionClass(Item::ItemClass itemClass, OptionClass optionClass)
{
	switch (itemClass)
	{
		// WEAPON
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			switch (optionClass)
			{
				case OPTION_STR :
				case OPTION_DEX :
				case OPTION_INT :
				case OPTION_HP :
				case OPTION_MP :
				case OPTION_HP_STEAL :
				case OPTION_MP_STEAL :
				case OPTION_TOHIT :
				case OPTION_DAMAGE :
				case OPTION_DURABILITY :
				case OPTION_ATTACK_SPEED :
				case OPTION_LUCK :
				case OPTION_ALL_ATTR :
					return true;

				default :
					return false;
			}
		break;

		// ARMOR
		case Item::ITEM_CLASS_HELM:
		case Item::ITEM_CLASS_COAT:
		case Item::ITEM_CLASS_TROUSER:
		case Item::ITEM_CLASS_SHOES:
		case Item::ITEM_CLASS_GLOVE:
		case Item::ITEM_CLASS_BELT:
		case Item::ITEM_CLASS_SHIELD:
		case Item::ITEM_CLASS_VAMPIRE_COAT:
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
			switch (optionClass)
			{
				case OPTION_STR :
				case OPTION_DEX :
				case OPTION_INT :
				case OPTION_HP :
				case OPTION_MP :
				case OPTION_DEFENSE :
				case OPTION_PROTECTION :
				case OPTION_DURABILITY :
				case OPTION_LUCK :
				case OPTION_ALL_ATTR :
					return true;
				break;

				default :
					return false;
			}
		break;

		// ACCESSORY
		case Item::ITEM_CLASS_RING:
		case Item::ITEM_CLASS_BRACELET:
		case Item::ITEM_CLASS_NECKLACE:
		case Item::ITEM_CLASS_VAMPIRE_RING:
		case Item::ITEM_CLASS_VAMPIRE_EARRING:
		case Item::ITEM_CLASS_VAMPIRE_BRACELET:
		case Item::ITEM_CLASS_VAMPIRE_NECKLACE:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
			switch (optionClass)
			{
				case OPTION_STR :
				case OPTION_DEX :
				case OPTION_INT :
				case OPTION_HP :
				case OPTION_MP :
				case OPTION_HP_STEAL :
				case OPTION_MP_STEAL :
				case OPTION_HP_REGEN :
				case OPTION_MP_REGEN :
				case OPTION_TOHIT :
				case OPTION_DAMAGE :
				case OPTION_DEFENSE :
				case OPTION_PROTECTION :
				case OPTION_DURABILITY :
				case OPTION_POISON :
				case OPTION_ACID :
				case OPTION_CURSE :
				case OPTION_BLOOD :
				case OPTION_VISION :
				case OPTION_ATTACK_SPEED :
				case OPTION_LUCK :
				case OPTION_ALL_RES :
				case OPTION_ALL_ATTR :
					return true;
				break;

				default :
					return false;
			}
			break;

		case Item::ITEM_CLASS_VAMPIRE_AMULET:
			switch (optionClass)
			{
				case OPTION_STR :
				case OPTION_DEX :
				case OPTION_INT :
				case OPTION_HP :
				case OPTION_MP :
				case OPTION_HP_STEAL :
				case OPTION_MP_STEAL :
				case OPTION_HP_REGEN :
				case OPTION_MP_REGEN :
				case OPTION_TOHIT :
				case OPTION_DAMAGE :
				case OPTION_DURABILITY :
				case OPTION_POISON :
				case OPTION_ACID :
				case OPTION_CURSE :
				case OPTION_BLOOD :
				case OPTION_VISION :
				case OPTION_ATTACK_SPEED :
				case OPTION_LUCK :
				case OPTION_ALL_RES :
				case OPTION_ALL_ATTR :
					return true;
				break;

				default :
					return false;
			}
			break;
				
		/* 삽 -.-;
		case Item::ITEM_CLASS_BLOOD_BIBLE :
			switch (optionClass)
			{
				case OPTION_STR :
				case OPTION_DEX :
				case OPTION_INT :
				case OPTION_HP :
				case OPTION_LUCK :
				case OPTION_ALL_RES :
				case OPTION_ALL_ATTR :
				case OPTION_VISION :
				case OPTION_CONSUME_MP :
				case OPTION_TRANS :
				case OPTION_MAGIC_DAMAGE :
				case OPTION_MELEE_DAMAGE :
				case OPTION_GAMBLE_PRICE :
				case OPTION_POTION_PRICE :
					return true;
				break;

				default :
					return false;

			}
			break;
		*/

		default:
			break;
	}

	return false;
}

/*
bool OptionClassInfo::ApplyOption(PlayerCreature* pPC, int PlusPoint )
{
	if (pPC == NULL ) return false;
	if (pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		return ApplyOption(pSlayer, PlusPoint);
	}
	else if (pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		return ApplyOption(pVampire, PlusPoint);
	}
	else if (pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		return ApplyOption(pOusters, PlusPoint);
	}
}

bool OptionClassInfo::ApplyOption(Slayer* pSlayer, int PlusPoint )
{
	if (pSlayer == NULL ) return false;
}

bool OptionClassInfo::ApplyOption(Vampire* pVampire, int PlusPoint )
{
	if (pVampire == NULL ) return false;
}

bool OptionClassInfo::ApplyOption(Ousters* pOusters, int PlusPoint )
{
	if (pOusters == NULL ) return false;
}
*/

//////////////////////////////////////////////////////////////////////////////
// class OptionInfo member methods
//////////////////////////////////////////////////////////////////////////////

OptionInfo::OptionInfo()
	throw()
{
	__BEGIN_TRY

	m_OptionType      = 0;
	m_Name            = "";
	m_HName           = "";
	m_Nickname        = "";
	m_OptionClass     = OPTION_MAX;
	m_PlusPoint       = 0;
	m_PriceMultiplier = 0;
	m_ReqSTR          = 0;
	m_ReqDEX          = 0;
	m_ReqINT          = 0;
	m_ReqSum          = 0;
	m_ReqLevel        = 0;
	m_Level           = 0;
	m_Color           = 0;
	m_Ratio           = 0;
	m_GambleLevel     = 0;

	// 다음 단계의 option으로 upgrade할때 필요한 정보
	m_PreviousOptionType   = 0;
	m_UpgradeOptionType    = 0;
	m_UpgradeRatio         = 0;
	m_UpgradeSecondRatio         = 0;
	m_UpgradeCrashPercent  = 0;
	m_NextOptionRatio      = 0;

	__END_CATCH
}

OptionInfo::~OptionInfo()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void OptionInfo::setReqAbility(const string& req) 
	throw()
{
	__BEGIN_TRY

    size_t a = 0, b = 0, c = 0;

	do
	{
		//////////////////////////////////////////////
		// (DEX,40) (INT,40)
		// a   b  c a
		//////////////////////////////////////////////
		a = req.find_first_of('(', c);
		b = req.find_first_of(',', a+1);
		c = req.find_first_of(')', b+1);

		if (a > b || b > c) break;

		Assert(a+1<b && b+1<c);

		string identifier =              req.substr(a+1, b-a-1);
		Attr_t reqAbility = (Attr_t)atoi(req.substr(b+1, c-b-1).c_str());

		if (identifier == "STR")      { setReqSTR(reqAbility);    }
		else if (identifier == "DEX") { setReqDEX(reqAbility);    }
		else if (identifier == "INT") { setReqINT(reqAbility);    }
		else if (identifier == "LEV") { setReqLevel(reqAbility);  }
		else if (identifier == "SUM") { setReqSum(reqAbility);    }
		else if (identifier != "")
		{
			//cerr << "OptionInfo::setReqAbility() : Unknown ability type [" << identifier << "]" << endl;
			throw("OptionInfo::setReqAbility() : Unknown ability type");
		}

	} while (c < req.size() -1);

	__END_CATCH
}

// 다음 단계의 옵션으로 upgrade가 성공했나?
bool OptionInfo::isUpgradeSucceed() const
{
	// 0이 아니고
	// 확률만큼 rand()했을때 특정한 한 값(0)이 나오는 경우가 성공이다.
	//return m_UpgradeRatio!=0 && (rand()%m_UpgradeRatio==0);

	// 그런데.. 기획이 백분율로 나왔다. -_-;
	return (rand()%100 < (int)m_UpgradeRatio);
}

// 다음 단계의 옵션으로 upgrade가 성공했나?
bool OptionInfo::isUpgradeSecondSucceed() const
{
	// 0이 아니고
	// 확률만큼 rand()했을때 특정한 한 값(0)이 나오는 경우가 성공이다.
	//return m_UpgradeRatio!=0 && (rand()%m_UpgradeRatio==0);

	// 그런데.. 기획이 백분율로 나왔다. -_-;
	return (rand()%100 < (int)m_UpgradeSecondRatio);
}

// 다음 단계의 옵션으로 upgrade 하다가 실패해서 item이 부서졌나?
bool OptionInfo::isUpgradeCrash() const
{
	return (rand()%100 < m_UpgradeCrashPercent);
}

string OptionInfo::toString() const
	throw()
{
	__BEGIN_TRY
	
	StringStream msg;
	msg << "OptionInfo ("
		<< "Type:"            << (int)m_OptionType
		<< "Name:"            << m_Name
		<< "HName:"           << m_HName
		<< "Nickname:"        << m_Nickname
		<< "Class:"           << (int)m_OptionClass
		<< "PlusPoint:"       << (int)m_PlusPoint
		<< "PriceMultiplier:" << (int)m_PriceMultiplier
		<< "ReqSTR:"          << (int)m_ReqSTR
		<< "ReqDEX:"          << (int)m_ReqDEX
		<< "ReqINT:"          << (int)m_ReqINT
		<< "ReqSum:"          << (int)m_ReqSum
		<< "ReqLevel:"        << (int)m_ReqLevel
		<< "Level:"           << (int)m_Level
		<< "GambleLevel:"     << (int)m_GambleLevel
		<< "Color:"           << (int)m_Color
		<< "Ratio:"           << (int)m_Ratio
		<< "PreviousOptionType:"  << (int)m_PreviousOptionType
		<< "UpgradeOptionType:"   << (int)m_UpgradeOptionType
		<< "UpgradeRatio:"        << (int)m_UpgradeRatio
		<< "UpgradeSecondRatio:"        << (int)m_UpgradeSecondRatio
		<< "UpgradeCrashPercent:" << (int)m_UpgradeCrashPercent
		<< "NextOptionRatio:"     << (int)m_NextOptionRatio
		<< ")";
	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class OptionInfoSet
//////////////////////////////////////////////////////////////////////////////

OptionInfoSet::OptionInfoSet()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

OptionInfoSet::~OptionInfoSet()
	throw()
{
	__BEGIN_TRY

	m_OptionTypes.clear();

	__END_CATCH
}

// 지정된 레벨에 따라서 맵에다 옵션 타입을 집어넣는다.
void OptionInfoSet::addOptionType(uint level, OptionType_t type)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	map<uint, OptionType_t>::iterator itr = m_OptionTypes.find(level);

	if (itr != m_OptionTypes.end())
	{
		StringStream msg;
		msg << "DupOptionLevel(OptionInfoSet): level=" << (int)level
			<< ", OptionType=" << (int)type;

		throw DuplicatedException(msg.toString().c_str());
	}

	m_OptionTypes[level] = type;

	__END_CATCH
}

// 지정된 최소, 최대 레벨에 따라, 그 범위 안의 옵션을 벡터에다 집어넣는다.
void OptionInfoSet::getPossibleOptionTypes(uint minLevel, uint maxLevel, vector<OptionType_t>& rOptionVector)
	throw()
{
	__BEGIN_TRY

	map<uint, OptionType_t>::iterator itr = m_OptionTypes.begin();
	for (; itr != m_OptionTypes.end(); itr++)
	{
		uint level = itr->first;
		if (minLevel <= level && level <= maxLevel)
		{
			OptionType_t OType = itr->second;
			rOptionVector.push_back(OType);
		}
	}

	__END_CATCH
}

string OptionInfoSet::toString(void) const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "OptionInfoSet(";

	map<uint, OptionType_t>::const_iterator itr = m_OptionTypes.begin();
	for (; itr != m_OptionTypes.end(); itr++)
		msg << (int)itr->first << ":" << (int)itr->second << ",";

	msg << ")\n";

	return msg.toString();

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// class OptionInfoManager member methods
//////////////////////////////////////////////////////////////////////////////

OptionInfoManager::OptionInfoManager()
	throw()
{
	__BEGIN_TRY

	m_nOptionCount = 0;
	m_OptionClassInfos.clear();
	m_OptionClassInfos.reserve((int)OPTION_MAX);
	m_ToTalPetEnchantOption = 0;
	m_PetEnchantOptionList.clear();

	__END_CATCH
}

OptionInfoManager::~OptionInfoManager()
	throw()
{
	__BEGIN_TRY

	release();

	__END_CATCH
}

void
OptionInfoManager::release()
	throw()
{
	__BEGIN_TRY

	m_nOptionCount = 0;

	map<OptionType_t, OptionInfo*>::iterator itr = m_OptionInfos.begin();
	for (; itr != m_OptionInfos.end(); itr++)
	{
		OptionInfo* pInfo = itr->second;
		SAFE_DELETE(pInfo);
	}
	m_OptionInfos.clear();

	m_NicknameOptionInfos.clear();

	for (int i=0; i<OPTION_MAX; i++)
	{
		m_OptionInfoSet[i].clear();
	}

	for (int ic=0; ic<Item::ITEM_CLASS_MAX; ic++)
    {
        for (uint l=0; l<GAMBLE_OPTION_LEVEL_MAX; l++)
        {
            m_GambleOptions[ic][l].clear();
        }
    }

	vector<OptionClassInfo*>::iterator citr = m_OptionClassInfos.begin();
	vector<OptionClassInfo*>::iterator endcItr = m_OptionClassInfos.end();

	for (; citr != endcItr ; ++citr )
	{
		if (*citr != NULL ) SAFE_DELETE(*citr);
	}

	m_OptionClassInfos.clear();

	list<PetEnchantOption*>::iterator pitr = m_PetEnchantOptionList.begin();
	list<PetEnchantOption*>::iterator endpItr = m_PetEnchantOptionList.end();

	for (; pitr!=endpItr; pitr++)
	{
		PetEnchantOption* pPetEnchantOption = *pitr;
		SAFE_DELETE(pPetEnchantOption);
	}
	m_PetEnchantOptionList.clear();
	m_ToTalPetEnchantOption = 0;
	
	__END_CATCH
}

void OptionInfoManager::init()
	throw()
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void OptionInfoManager::load()
	throw()
{
	__BEGIN_TRY

	release();

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	try {

	BEGIN_DB
	{
		StringStream sql;
		sql << "SELECT OptionType, Name, HName, Nickname, "
			<< "Class, PlusPoint, PriceMultiplier, "
			<< "ReqAbility, Color, Ratio, OptionLevel, GambleLevel, "
			<< "PreviousOptionType, UpgradeOptionType, UpgradeRatio, UpgradeSecondRatio, "
			<< "UpgradeCrashPercent, NextOptionRatio, Grade "
			<< "FROM OptionInfo";

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery(sql.toString());

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("There is no data in OptionInfo Table");
		}

		while (pResult->next())
		{
			OptionInfo* pInfo = new OptionInfo;
			int         i     = 0;

			pInfo->setType(pResult->getInt(++i));
			pInfo->setName(pResult->getString(++i));
			pInfo->setHName(pResult->getString(++i));
			pInfo->setNickname(pResult->getString(++i));
			pInfo->setClass((OptionClass)pResult->getInt(++i));
			pInfo->setPlusPoint(pResult->getInt(++i));
			pInfo->setPriceMultiplier(pResult->getInt(++i));
			pInfo->setReqAbility(pResult->getString(++i));
			pInfo->setColor(pResult->getInt(++i));
			pInfo->setRatio(pResult->getInt(++i));
			pInfo->setLevel(pResult->getInt(++i));
			pInfo->setGambleLevel(pResult->getInt(++i));
			pInfo->setPreviousType(pResult->getInt(++i));
			pInfo->setUpgradeType(pResult->getInt(++i));
			pInfo->setUpgradeRatio(pResult->getInt(++i));
			pInfo->setUpgradeSecondRatio(pResult->getInt(++i));
			pInfo->setUpgradeCrashPercent(pResult->getInt(++i));
			pInfo->setNextOptionRatio(pResult->getInt(++i));
			pInfo->setGrade(pResult->getInt(++i));

			addOptionInfo(pInfo);

			// 옵션 클래스에 따라서 알맞은 OptionInfoSet에다가 
			// level, type을 집어넣어준다.
			uint         OClass = pInfo->getClass();
			uint         level  = pInfo->getLevel();
			OptionType_t type   = pInfo->getType();
			Ratio_t		 gambleRatio = pInfo->getRatio();

			m_OptionInfoSet[OClass].addOptionType(level, type);			

			// gamble을 위한 option정보 설정
			for (int ic=0; ic<Item::ITEM_CLASS_MAX; ic++)
			{
				// itemClass에 붙을 수 있는 option인 경우
				// m_GambleOptions에 추가해둔다.
				if (gambleRatio>0
					&& isPossibleOptionClass((Item::ItemClass)ic, (OptionClass)OClass))
				{
					uint gambleLevel = pInfo->getGambleLevel();

					// level까지 추가해둔다.
					for (uint l=gambleLevel; l<=GAMBLE_OPTION_LEVEL_MAX; l++)
					{
						m_GambleOptions[ic][l].push_back(type);
						//cout << "GambleOption[" << ic << "][" << l << "] = " << (int)type << endl;
					}
				}
			}
		}

		pResult = pStmt->executeQuery("SELECT OptionClassType, Name, HName, Level, TotalGrade, OptionGroup FROM OptionClassInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("There is no data in OptionClassInfo Table");
		}

		while (pResult->next() )
		{
			OptionClassInfo* pInfo = new OptionClassInfo((OptionClass)pResult->getInt(1));
			pInfo->setName(pResult->getString(2));
			pInfo->setHName(pResult->getString(3));
			pInfo->setLevel(pResult->getInt(4));
			pInfo->setTotalGrade(pResult->getInt(5));
			pInfo->setOptionGroup((OptionGroup)pResult->getInt(6));

			addOptionClassInfo(pInfo);
		}

		pResult = pStmt->executeQuery("SELECT Level, TotalGrade, Grade, RatioWhenFail, RatioWhenSuccess FROM RareEnchantInfo");

		if (pResult->getRowCount() == 0)
		{
			SAFE_DELETE(pStmt);
			throw Error("There is no data in RareEnchantInfo Table");
		}

		while (pResult->next() )
		{
			int level = pResult->getInt(1);
			int total = pResult->getInt(2);

			int key = level*10 + total;

			map<int,RareOptionUpgradeInfo*>::iterator itr = m_RareEnchantInfo.find(key);

			if (itr == m_RareEnchantInfo.end() )
			{
				RareOptionUpgradeInfo* pInfo = new RareOptionUpgradeInfo(level, total);
				m_RareEnchantInfo[key] = pInfo;
			}

			int grade = pResult->getInt(3);

			m_RareEnchantInfo[key]->setRatio(grade, false, pResult->getInt(4));
			m_RareEnchantInfo[key]->setRatio(grade, true, pResult->getInt(5));
		}

		pResult = pStmt->executeQuery("SELECT OptionType, Ratio FROM PetEnchantOptionRatioInfo");

		while (pResult->next() )
		{
			OptionType_t optionType = pResult->getInt(1);
			int 		 ratio 		= pResult->getInt(2);

			ratio = ratio + getTotalPetEnchantOption();
			setTotalPetEnchantOption(ratio);
		
			PetEnchantOption* pPetEnchantOption = new PetEnchantOption();
			pPetEnchantOption->setOptionType(optionType);
			pPetEnchantOption->setRatio(ratio);

			addPetEnchantOption(pPetEnchantOption);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)


	// gamble option별로 totalRatio를 구해둔다.
    for (int ic=0; ic<Item::ITEM_CLASS_MAX; ic++)
    {
        for (uint l=0; l<=GAMBLE_OPTION_LEVEL_MAX; l++)
        {
            m_TotalGambleRatio[ic][l] = 0;

            const vector<OptionType_t>& optionVector = m_GambleOptions[ic][l];
            vector<OptionType_t>::const_iterator iOption;

            int totalRatio = 0;
            for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
            {
                OptionType_t optionType = *iOption;

                try {
                    OptionInfo* pOptionInfo = getOptionInfo(optionType);

					if (pOptionInfo==NULL)
					{
                    	cerr << "No Such Option : "  << optionType << endl;
                    	Assert(false);
					}

                    totalRatio += pOptionInfo->getRatio();
                } catch (NoSuchElementException&) {
                    cerr << "No Such Option : "  << optionType << endl;
                    Assert(false);
                }
            }

            m_TotalGambleRatio[ic][l] = totalRatio;
        }
    }


	} catch (Throwable& t) {
		cerr << t.toString().c_str() << endl;
		throw;
	}
	
	__END_CATCH
}

void OptionInfoManager::addOptionInfo(OptionInfo* pOptionInfo)
	throw(DuplicatedException, Error)
{
	__BEGIN_TRY

	// OptionType으로 구분되는 해쉬맵에다 집어넣는다.
	map<OptionType_t, OptionInfo*>::iterator itr = m_OptionInfos.find(pOptionInfo->getType());

	if (itr != m_OptionInfos.end())
	{
		StringStream msg;
		msg << "DupOptionType: OptionType=" << (int)pOptionInfo->getType()
			<< ", Nickname=" << pOptionInfo->getNickname();

		throw DuplicatedException(msg.toString());
	}

	m_OptionInfos[pOptionInfo->getType()] = pOptionInfo;

	// Nickname으로 구분되는 해쉬맵에다 집어넣는다.
	map<string, OptionInfo*>::iterator itr2 = m_NicknameOptionInfos.find(pOptionInfo->getNickname());

	if (itr2 != m_NicknameOptionInfos.end())
	{
		StringStream msg;
		msg << "DupNickname: OptionType=" << (int)pOptionInfo->getType()
			<< ", Nickname=" << pOptionInfo->getNickname();

		throw DuplicatedException(msg.toString().c_str());
	}

	m_NicknameOptionInfos[pOptionInfo->getNickname()] = pOptionInfo;
	
	__END_CATCH
}

OptionInfo* OptionInfoManager::getOptionInfo(OptionType_t OptionType)
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	//cout << "getOptionInfo(" << (int)OptionType << ") " << endl;

	map<OptionType_t, OptionInfo*>::iterator itr = m_OptionInfos.find(OptionType);

	if (itr == m_OptionInfos.end())
	{
		//cerr << "OptionInfoManager::getOptionInfo() : No Such Element Exception. OptionType=" << (int)OptionType << endl;
		//throw NoSuchElementException();

		// nosuch제거. 2002.8.23. by sigi
		return NULL;
	}

	return itr->second;
	
	__END_CATCH
}

OptionInfo* OptionInfoManager::getOptionInfo(const string& nickname)
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	map<string, OptionInfo*>::iterator itr = m_NicknameOptionInfos.find(nickname);

	if (itr == m_NicknameOptionInfos.end())
	{
		//cerr << "OptionInfoManager::getOptionInfo() : No Such Element Exception" << endl;
		//throw NoSuchElementException();

		// nosuch제거. 2002.8.23. by sigi
		return NULL;
	}

	return itr->second;
	
	__END_CATCH
}

OptionType_t OptionInfoManager::getOptionType(const string& nickname)
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	map<string, OptionInfo*>::iterator itr = m_NicknameOptionInfos.find(nickname);

	if (itr == m_NicknameOptionInfos.end())
	{
		cerr << "OptionInfoManager::getOptionInfo() : No Such Element Exception" << endl;
		throw NoSuchElementException();
	}

	OptionInfo* pInfo = itr->second;
	return pInfo->getType();
	
	__END_CATCH
}

string OptionInfoManager::getOptionName(const list<OptionType_t>& optionTypes)
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	StringStream optionName;

	list<OptionType_t>::const_iterator itr;

	for (itr = optionTypes.begin() ; itr != optionTypes.end() ; itr++)
	{
		OptionInfo* pOptionInfo = getOptionInfo(*itr);
		optionName << pOptionInfo->getName() << " ";
	}

	return optionName.toString();

	__END_CATCH
}



vector<OptionType_t> OptionInfoManager::getPossibleOptionVector(Item::ItemClass IClass, uint minLevel, uint maxLevel)
	throw()
{
	__BEGIN_TRY

	vector<OptionType_t> temp;

	switch (IClass)
	{
		// WEAPON
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_TOHIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DAMAGE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DURABILITY].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ATTACK_SPEED].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);

			if (IClass != Item::ITEM_CLASS_VAMPIRE_WEAPON )
				m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);

			break;
		// ARMOR
		case Item::ITEM_CLASS_HELM:
		case Item::ITEM_CLASS_COAT:
		case Item::ITEM_CLASS_TROUSER:
		case Item::ITEM_CLASS_SHOES:
		case Item::ITEM_CLASS_GLOVE:
		case Item::ITEM_CLASS_BELT:
		case Item::ITEM_CLASS_SHIELD:
		case Item::ITEM_CLASS_VAMPIRE_COAT:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEFENSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_PROTECTION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DURABILITY].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);

			if (IClass != Item::ITEM_CLASS_VAMPIRE_COAT )
				m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);

			break;
		// ACCESSORY
		case Item::ITEM_CLASS_RING:
		case Item::ITEM_CLASS_BRACELET:
		case Item::ITEM_CLASS_NECKLACE:
		case Item::ITEM_CLASS_VAMPIRE_RING:
		case Item::ITEM_CLASS_VAMPIRE_EARRING:
		case Item::ITEM_CLASS_VAMPIRE_BRACELET:
		case Item::ITEM_CLASS_VAMPIRE_NECKLACE:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_REGEN].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_REGEN].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_TOHIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DAMAGE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEFENSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_PROTECTION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DURABILITY].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_POISON].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ACID].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_CURSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_BLOOD].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_VISION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ATTACK_SPEED].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_RES].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);

			m_OptionInfoSet[OPTION_STR_TO_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_STR_TO_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX_TO_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX_TO_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT_TO_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT_TO_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);

			if (IClass!=Item::ITEM_CLASS_VAMPIRE_EARRING)
				m_OptionInfoSet[OPTION_LUCK].getPossibleOptionTypes(minLevel, maxLevel, temp);

			if (IClass != Item::ITEM_CLASS_VAMPIRE_RING &&
			 	 IClass != Item::ITEM_CLASS_VAMPIRE_EARRING &&
				 IClass != Item::ITEM_CLASS_VAMPIRE_BRACELET &&
				 IClass != Item::ITEM_CLASS_VAMPIRE_NECKLACE )
				m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);

			break;

		case Item::ITEM_CLASS_VAMPIRE_AMULET:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
//			m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_REGEN].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_REGEN].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_TOHIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DAMAGE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DURABILITY].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_POISON].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ACID].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_CURSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_BLOOD].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_VISION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ATTACK_SPEED].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_LUCK].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_RES].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			break;

		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_TOHIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DAMAGE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DURABILITY].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ATTACK_SPEED].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_CRITICAL_HIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			break;

		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEFENSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_PROTECTION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DURABILITY].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_POISON].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ACID].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_CURSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_BLOOD].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_LUCK].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_RES].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			break;

		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
			m_OptionInfoSet[OPTION_STR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEX].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_INT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_HP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_MP_STEAL].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_TOHIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DAMAGE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_DEFENSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_PROTECTION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_POISON].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ACID].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_CURSE].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_BLOOD].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_VISION].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ATTACK_SPEED].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_CRITICAL_HIT].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_LUCK].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_RES].getPossibleOptionTypes(minLevel, maxLevel, temp);
			m_OptionInfoSet[OPTION_ALL_ATTR].getPossibleOptionTypes(minLevel, maxLevel, temp);
			break;

		default:
			break;
	}

	return temp;

	__END_CATCH
}

void OptionInfoManager::addGambleOption(Item::ItemClass itemClass, uint level, OptionType_t optionType) 
	throw(DuplicatedException, Error)
{
	m_GambleOptions[itemClass][level].push_back(optionType);
}

int OptionInfoManager::getRareUpgradeRatio(OptionType_t optionType, bool success )
{
	OptionInfo* pOI = getOptionInfo(optionType);
	if (pOI == NULL ) throw Error("OptionInfoManager::getRareUpgradeRatio() : 옵션 인포가 없습니다.");

	OptionClassInfo* pOCI = m_OptionClassInfos[pOI->getClass()];
	if (pOCI == NULL ) throw Error("OptionInfoManager::getRareUpgradeRatio() : 옵션 클래스 인포가 없습니다.");

	RareOptionUpgradeInfo* pROUI = m_RareEnchantInfo[pOCI->getKey()];
	if (pROUI == NULL ) throw Error("OptionInfoManager::getRareUpgradeRatio() : 레어 인챈트 인포가 없습니다.");

	return pROUI->getRatio(pOI->getGrade(), success);
}

void OptionInfoManager::addPetEnchantOption(PetEnchantOption* pPetEnchantOption)
	throw()
{
	__BEGIN_TRY

	Assert(pPetEnchantOption != NULL);
	m_PetEnchantOptionList.push_back(pPetEnchantOption);

	__END_CATCH
}


string OptionInfoManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "OptionInfoManager(\n";

	for (uint i=0; i<OPTION_MAX; i++)
		msg << m_OptionInfoSet[i].toString();

	msg << "\n)";
	return msg.toString();

	__END_CATCH
}
