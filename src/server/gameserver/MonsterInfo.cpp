//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterInfo.cpp
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MonsterInfoTypes.h"
#include "MonsterInfo.h"
#include "Treasure.h"
#include "DB.h"
#include "StringStream.h"
#include "Properties.h"
#include "MonsterSummonInfo.h"
#include "EffectObservingEye.h"
#include "EffectDetectInvisibility.h"
#include "SXml.h"
#include <fstream>
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <iterator>
#include <map>

int DefaultClanID[CLAN_MAX] =
{
	0, //CLAN_NONE,							// ���𿡵� ������ �ʴ� �ִ�.. 0
	1, //CLAN_VAMPIRE_MONSTER,				// ������ ���� ������ -_-;     1
	2, //CLAN_VAMPIRE_BATHORY_MONSTER,		// ���丮 �Ҽ� ������          2
	3, //CLAN_VAMPIRE_TEPEZ_MONSTER,			// ������ �Ҽ� ������          3
	4, //CLAN_SLAYER_MONSTER,				// �����̾� ������ - -;;       4
};

extern int DefaultClanID[CLAN_MAX];

//////////////////////////////////////////////////////////////////////////////
// global varible initialization
//////////////////////////////////////////////////////////////////////////////
MonsterInfoManager* g_pMonsterInfoManager = NULL;

//////////////////////////////////////////////////////////////////////////////
// functions
//////////////////////////////////////////////////////////////////////////////

void saveTreasure(const string& filename, TreasureList* pTreasureList)
{
	ofstream file(filename.c_str(), ios::out | ios::binary | ios::trunc);
	if (!file) return;

	const list<Treasure*>& TList = pTreasureList->getTreasures();
	int TreasureCount = TList.size();

	file.write((char*)&TreasureCount, sizeof(int));

	list<Treasure*>::const_iterator itr = TList.begin();
	for (; itr != TList.end(); itr++)
	{
		Treasure* pTreasure = *itr;

		int ItemRatio           = pTreasure->m_ItemRatio;
		int OptionRatio         = pTreasure->m_OptionRatio;

		file.write((char*)&ItemRatio, sizeof(int));
		file.write((char*)&OptionRatio, sizeof(int));

		vector<TreasureItemClass*> TICs = pTreasure->m_TreasureItemClasses;
		int ItemClassCount = TICs.size();

		file.write((char*)&ItemClassCount, sizeof(int));

		for (uint i=0; i<TICs.size(); i++)
		{
			TreasureItemClass* pTIC = TICs[i];

			int ItemClass          = (int)pTIC->m_ItemClass;
			int ItemClassRatio     = pTIC->m_Ratio;

			file.write((char*)&ItemClass, sizeof(int));
			file.write((char*)&ItemClassRatio, sizeof(int));

			vector<TreasureItemType*> TITs = pTIC->m_TreasureItemTypes;
			int ItemTypeCount = TITs.size();

			file.write((char*)&ItemTypeCount, sizeof(int));

			for (uint j=0; j<TITs.size(); j++)
			{
				TreasureItemType* pTIT = TITs[j];

				int ItemType             = pTIT->m_ItemType;
				int ItemTypeRatio        = pTIT->m_Ratio;

				file.write((char*)&ItemType, sizeof(int));
				file.write((char*)&ItemTypeRatio, sizeof(int));

				vector<TreasureOptionType*> TOTs = pTIT->m_TreasureOptionTypes;
				int OptionTypeCount = TOTs.size();

				file.write((char*)&OptionTypeCount, sizeof(int));

				for (uint k=0; k<TOTs.size(); k++)
				{
					TreasureOptionType* pTOT = TOTs[k];

					int OptionType  = pTOT->m_OptionType;
					int OptionRatio = pTOT->m_Ratio;

					file.write((char*)&OptionType, sizeof(int));
					file.write((char*)&OptionRatio, sizeof(int));
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// class MonsterInfo member methods
//////////////////////////////////////////////////////////////////////////////

MonsterInfo::MonsterInfo()
	throw()
{
	__BEGIN_TRY

	m_MonsterType = 0;
	m_SpriteType = 0;
	m_HName = "";
	m_EName = "";
	m_Level = 0;
	m_STR = 0;
	m_DEX = 0;
	m_INT = 0;
	m_BodySize = BODYSIZE_SMALL;
	m_HP = 0;
	m_Exp = 0;
	m_MainColor = 0;
	m_SubColor = 0;
	m_Alignment = ALIGNMENT_FRIENDLY;
	m_AttackOrder = ATTACK_FIRST;
	m_Moral = 0;
	m_Delay = 0;
	m_AttackDelay = 0;
	m_Sight = 0;
	m_MoveMode = Creature::MOVE_MODE_WALKING;
	m_AIType = 0;

	m_EnhanceHP         = 0;
	m_EnhanceToHit      = 0;
	m_EnhanceDefense    = 0;
	m_EnhanceProtection = 0;
	m_EnhanceMinDamage     = 0;
	m_EnhanceMaxDamage     = 0;

	m_pSlayerTreasureList  = NULL;//new TreasureList;
	m_pVampireTreasureList = NULL;//new TreasureList;
	m_pOustersTreasureList = NULL;//new TreasureList;

	m_RegenType[REGENTYPE_HIDE] 	 = 128;
	m_RegenType[REGENTYPE_PORTAL] 	 = 0;
	m_RegenType[REGENTYPE_INVISIBLE] = 0;
	m_RegenType[REGENTYPE_BAT] 		 = 0;
	
	m_UnburrowChance = 128;
	m_bMaster = false;
	m_ClanType = CLAN_VAMPIRE_MONSTER;
	m_pMonsterSummonInfo = NULL;

	// 2002.10.16 by sigi
	m_bNormalRegen = true;

	__END_CATCH
}

MonsterInfo::~MonsterInfo()
	throw()
{
	__BEGIN_TRY

	// �̰Ŵ� MonsterInfo���� �����Ѵ�.
	//SAFE_DELETE(m_pSlayerTreasureList);
	//SAFE_DELETE(m_pVampireTreasureList);

	m_pSlayerTreasureList = NULL;
	m_pVampireTreasureList = NULL;
	m_pOustersTreasureList = NULL;

	SAFE_DELETE(m_pMonsterSummonInfo);

	__END_CATCH
}

void MonsterInfo::setRegenType(RegenType rt, int percent)
{ 
	m_RegenType[rt] = percent;

	// REGENTYPE_NORMAL�� Ȯ���� �ٲ㼭 100%�� �������� ������
	// �� �ǹ̰� ���� �� �Ͽ�.. - -;  by sigi
}

//---------------------------------------------------------------------------
// select RegenType
//---------------------------------------------------------------------------
// Hide�� Portal�� Ȯ���� ���� üũ�غ��� �� �� �ƴϸ�.. Normal�̴�. by sigi
//---------------------------------------------------------------------------
RegenType MonsterInfo::selectRegenType() const
{
	// �ӵ� �ణ ��������
	// 100�з��� �ƴϰ� 128�з��̴� - -;
	int dice = rand() & 0x0000007F; //rand()%100;

	int acc = 0;
	const int REGENTYPE_MAX_1 = REGENTYPE_MAX-1;
	for (int i=0; i<REGENTYPE_MAX_1; i++)
	{
		// �� Ȯ������ �������Ѽ� ��~ üũ
		acc += m_RegenType[i];
		if (dice < acc)
		{
			return (RegenType)i;
		}
	}

	return REGENTYPE_HIDE;
}

void MonsterInfo::setMoveMode(const string& moveMode)
	throw(Error)
{
	__BEGIN_TRY

	if (moveMode == "WALK") m_MoveMode = Creature::MOVE_MODE_WALKING;
	else if (moveMode == "FLY") m_MoveMode = Creature::MOVE_MODE_FLYING;
	else if (moveMode == "BURROW") m_MoveMode = Creature::MOVE_MODE_BURROWING;
	else throw Error("invalid move mode");

	__END_CATCH
}

void MonsterInfo::parseEnhanceAttr(const string& enhance) 
	throw()
{
	m_EnhanceHP         = 0;
	m_EnhanceToHit      = 0;
	m_EnhanceDefense    = 0;
	m_EnhanceProtection = 0;
	m_EnhanceMinDamage     = 0;
	m_EnhanceMaxDamage     = 0;

	if (enhance.size() < 1) return;

    size_t a = 0 , b = 0 , c = 0;

	while (c < enhance.size() - 1)
	{
		///////////////////////////////////////////////////////
		// (HP,1)(DAMAGE,1)...
		// a  b ca
		///////////////////////////////////////////////////////
		a = enhance.find_first_of('(',c);
		b = enhance.find_first_of(',',a+1);
		c = enhance.find_first_of(')',b+1);

		if (a > b || b > c) break;

		string part  = enhance.substr(a+1, b-a-1);
		int    value = atoi(enhance.substr(b+1, c-b-1).c_str());

		if (part == "HP")              m_EnhanceHP         = value;
		else if (part == "DEFENSE")    m_EnhanceDefense    = value;
		else if (part == "PROTECTION") m_EnhanceProtection = value;
		else if (part == "TOHIT")      m_EnhanceToHit      = value;
		else if (part == "DAMAGE")     m_EnhanceMinDamage = m_EnhanceMaxDamage = value;
		else if (part == "MINDAMAGE")     m_EnhanceMinDamage     = value;
		else if (part == "MAXDAMAGE")     m_EnhanceMaxDamage     = value;
	}
}

void MonsterInfo::parseSlayerTreasureString(const string& text)
	throw()
{
	__BEGIN_TRY

	string newtext = trim(text);
	/*
	if (newtext.size() < 10)
	{
		cerr << "MonsterInfo::parseSlayerTreasureString() : Too short treasure string" << endl;
		throw("MonsterInfo::parseSlayerTreasureString() : Too short treasure string");
	}
	*/

	m_pSlayerTreasureList->parseString(newtext);

	__END_CATCH
}

void MonsterInfo::setSlayerTreasureList(TreasureList* pTreasureList)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasureList != NULL);
	//SAFE_DELETE(m_pSlayerTreasureList);
	m_pSlayerTreasureList = pTreasureList;

	__END_CATCH
}

void MonsterInfo::parseVampireTreasureString(const string& text)
	throw()
{
	__BEGIN_TRY

	string newtext = trim(text);
	/*
	if (newtext.size() < 10)
	{
		cerr << "MonsterInfo::parseVampireTreasureString() : Too short treasure string" << endl;
		throw("MonsterInfo::parseVampireTreasureString() : Too short treasure string");
	}
	*/

	m_pVampireTreasureList->parseString(newtext);

	__END_CATCH
}

void MonsterInfo::setVampireTreasureList(TreasureList* pTreasureList)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasureList != NULL);
	//SAFE_DELETE(m_pVampireTreasureList);
	m_pVampireTreasureList = pTreasureList;

	__END_CATCH
}

void MonsterInfo::parseOustersTreasureString(const string& text)
	throw()
{
	__BEGIN_TRY

	string newtext = trim(text);

	m_pOustersTreasureList->parseString(newtext);

	__END_CATCH
}

void MonsterInfo::setOustersTreasureList(TreasureList* pTreasureList)
	throw()
{
	__BEGIN_TRY

	Assert(pTreasureList != NULL);

	m_pOustersTreasureList = pTreasureList;

	__END_CATCH
}

void MonsterInfo::setMonsterSummonInfo(const string& text)
{
	SAFE_DELETE(m_pMonsterSummonInfo);

	if (text.size() > 0)
	{
		m_pMonsterSummonInfo = new MonsterSummonInfo;

		m_pMonsterSummonInfo->parseString(text);

//		cout << "[SummonInfo] " 
//			<< getHName().c_str() << " : " 
//			<< m_pMonsterSummonInfo->toString().c_str() 
//			<< endl;
	}
}

bool MonsterInfo::getMonsterSummonInfo(int step, SUMMON_INFO2& summonInfo) const
{
	if (m_pMonsterSummonInfo==NULL)
	{
		summonInfo.pMonsters = NULL;
		return false;
	}

	summonInfo.pMonsters = (MonsterCollection*)m_pMonsterSummonInfo->getRandomMonsterCollection(step);

	return true;
}

bool MonsterInfo::hasNextMonsterSummonInfo(int step) const
{
	if (m_pMonsterSummonInfo==NULL)
	{
		return false;
	}

	return m_pMonsterSummonInfo->hasNextMonsterCollection(step);
}

// a                    b
// IMMUNE_TO_BLOOD_DRAIN, IMMUNE_TO_PARALYZE, IMMUNE_TO_POISON, IMMUNE_TO_ACID, IMMUNE_TO_CURSE
void MonsterInfo::setDefaultEffects(const string& text) 
{
	m_DefaultEffects.clear();

	if (text.size() < 1) return;

    size_t a = 0 , b = 0;

	while (b < text.size() - 1)
	{
		b = text.find_first_of(',',a);

		string part  = trim(text.substr(a, b-a));	//b-1 -a+1);

		if (part == "IMMUNE_TO_BLOOD_DRAIN")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN);
		else if (part == "IMMUNE_TO_PARALYZE")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_PARALYZE);
		else if (part == "IMMUNE_TO_POISON")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_POISON);
		else if (part == "IMMUNE_TO_ACID")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_ACID);
		else if (part == "IMMUNE_TO_CURSE")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_CURSE);
		else if (part == "IMMUNE_TO_HALLUCINATION")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_HALLUCINATION);
        else if (part == "IMMUNE_TO_ROTTEN_APPLE") m_DefaultEffects.push_back(Effect::EFFECT_CLASS_IMMUNE_TO_ROTTEN_APPLE);
		else if (part == "DETECT_INVISIBILITY")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_DETECT_INVISIBILITY);
		else if (part == "OBSERVING_EYE")	m_DefaultEffects.push_back(Effect::EFFECT_CLASS_OBSERVING_EYE);
		else 
		{
			cout << "MonsterInfo::setDefaultEffects() - Wrong EffectClass: " << part.c_str() << endl;
			Assert(false);
		}

		a = b+1;
	}
}
	     
void MonsterInfo::addDefaultEffects(Creature* pCreature) const
{
	list<Effect::EffectClass>::const_iterator itr = m_DefaultEffects.begin();

	for (; itr!=m_DefaultEffects.end(); itr++)
	{
		Effect::EffectClass effectClass = *itr;

		pCreature->setFlag(effectClass);

		// ������ effect�� �ٿ��ش�.
		// �ٸ� ������ effect�� �����ϱ� �����̴�. by sigi. 2002.10.25
		// �ٵ�.. �ٸ� ������ assert(isSlayer())�س����� �� �־ �ϴ� ����. by sigi. 2002.10.28
		/*
		switch (effectClass)
		{
			case Effect::EFFECT_CLASS_OBSERVING_EYE :
			{
				EffectObservingEye* pEffect = new EffectObservingEye(pCreature);
				pEffect->setDeadline(99999);
				pEffect->setDamageBonus(13);
				pEffect->setCriticalHitBonus(50);
				pEffect->setVisionBonus(1);
				pEffect->setSkillLevel(99);

				pCreature->addEffect(pEffect);
			}																					
			break;
			
			case Effect::EFFECT_CLASS_DETECT_INVISIBILITY :
			{
				EffectDetectInvisibility* pEffectDetectInvisibility = new EffectDetectInvisibility(pCreature);
				pEffectDetectInvisibility->setDeadline(99999);

				pCreature->addEffect(pEffectDetectInvisibility);
			}
			break;

			default :
			break;
		}
		*/
	}
}


string MonsterInfo::toString () const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "MonsterInfo("
		<< "MonsterType:" << m_MonsterType
		<< ",SpriteType:" << m_SpriteType
		<< ",HName:" << m_HName
		<< ",EName:" << m_EName
		<< ",Level:" << (int)m_Level
		<< ",STR:" << (int)m_STR
		<< ",DEX:" << (int)m_DEX
		<< ",INT:" << (int)m_INT
		<< ",HP:" << m_HP
		<< ",Exp:" << m_Exp
		<< ",MainColor:" << (int)m_MainColor
		<< ",SubColor:" << (int)m_SubColor
		<< ",Alignment:" << MAlignment2String[m_Alignment]
		<< ",AttackOrder:" << AttackOrder2String[m_AttackOrder]
		<< ",Moral:" << (int)m_Moral
		<< ",Delay:" << (int)m_Delay
		<< ",Sight:" << (int)m_Sight
		<< ",MoveMode:" << MoveMode2String[m_MoveMode]
		<< ",RegenPortal:" << m_RegenType[REGENTYPE_PORTAL]
		<< ",RegenInvisible:" << m_RegenType[REGENTYPE_INVISIBLE]
		<< ",RegenBat:" << m_RegenType[REGENTYPE_BAT]
		<< ",RegenHide:" << m_RegenType[REGENTYPE_HIDE]
		<< ",UnburrowChance:" << m_UnburrowChance
		<< ",HasTreasure:" << (int)m_bHasTreasure
		<< ")";

	return msg.toString();
	
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// class MonsterInfoManager member methods
////////////////////////////////////////////////////////////////////////////////

MonsterInfoManager::MonsterInfoManager ()
	throw()
{
	__BEGIN_TRY

	m_MonsterInfos = NULL;

	__END_CATCH
}

MonsterInfoManager::~MonsterInfoManager ()
	throw()
{
	__BEGIN_TRY
		
	SAFE_DELETE_ARRAY(m_MonsterInfos);

	__END_CATCH
}

void MonsterInfoManager::init ()
	throw(Error)
{
	__BEGIN_TRY

	load();

	__END_CATCH
}

void MonsterInfoManager::clearTreasures()
{
	m_SlayerTreasureLists.clear();	
	m_VampireTreasureLists.clear();	
	m_OustersTreasureLists.clear();	
}

void MonsterInfoManager::load () 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
    cout << "[MonsterInfoManager] Loading..." << endl;
	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(MType) FROM MonsterInfo");

		// MonsterInfo ���̺����� �ִ� MonsterType ���� �����´�.
		// �� ���� MonsterInfoManager�� ���� MonsterInfo* �迭�� ũ�Ⱑ �ȴ�.
		if (pResult->getRowCount() == 0)
		{
			// ���̺��� ���ٸ� �翬�� ������...
			SAFE_DELETE(pStmt);
			throw Error("MonsterInfo table is empty.. insert any row."); 
		}

		// Ŭ���̾�Ʈ������ �����̾�-�����̾�-������-NPC �� �������� �ʰ�,
		// ���� ĳ���ͷμ� �ε����� �ϱ� ������, ������ ���� �츮�� �����ؼ�
		// �������� �ϰڴ�. -_-; ���� �ƽ����� 4�� ���ؼ� �迭�� �����Ѵ�.
		// 0:Male Slayer, 1:Female Slayer, 2:Male Vampire, 3:Female Vampire
		pResult->next();
		m_MaxMonsterType = pResult->getInt(1) + 4 + 1;
		m_MonsterInfos = new MonsterInfo*[m_MaxMonsterType];

		for (uint i = 0 ; i < m_MaxMonsterType ; i ++)
			m_MonsterInfos[i] = NULL;

		// MonsterInfo ���̺��κ��� ������ ������ �о MonsterInfo ��ü�� ����, add �Ѵ�.
		//RegenInvisible, RegenBat, 
		/*
		StringStream sql;
		sql << "SELECT MType, SType, HName, EName, "
			<< "Level, STR, DEX, INTE, BSize, Exp, "
			<< "MColor, SColor, Align, AOrder, "
			<< "Moral, Delay, ADelay, Sight, MeleeRange, MissileRange, "
			<< "RegenPortal, RegenInvisible, RegenBat, "
			<< "MMode, AIType, Enhance "
			<< "FROM MonsterInfo";
		*/

		//pResult = pStmt->executeQuery(sql.toString());

		pResult = pStmt->executeQuery("SELECT MType, SType, HName, EName, Level, STR, DEX, INTE, BSize, Exp, MColor, SColor, Align, AOrder, Moral, Delay, ADelay, Sight, MeleeRange, MissileRange, RegenPortal, RegenInvisible, RegenBat, MMode, AIType, Enhance, UnburrowChance, Master, ClanType, DefaultEffects, Chief, NormalRegen, HasTreasure, MonsterClass, SkullType FROM MonsterInfo");

		while (pResult->next()) 
		{
			int i = 0;

			MonsterInfo* pMonsterInfo = new MonsterInfo();

			pMonsterInfo->setMonsterType(pResult->getInt(++i));
			pMonsterInfo->setSpriteType(pResult->getInt(++i));
			pMonsterInfo->setHName(pResult->getString(++i));
			pMonsterInfo->setEName(pResult->getString(++i));
			pMonsterInfo->setLevel(pResult->getInt(++i));
			pMonsterInfo->setSTR(pResult->getInt(++i));
			pMonsterInfo->setDEX(pResult->getInt(++i));
			pMonsterInfo->setINT(pResult->getInt(++i));
			pMonsterInfo->setBodySize(pResult->getInt(++i));
			pMonsterInfo->setExp(pResult->getInt(++i));
			pMonsterInfo->setMainColor(pResult->getInt(++i));
			pMonsterInfo->setSubColor(pResult->getInt(++i));
			pMonsterInfo->setAlignment((MAlignment)pResult->getInt(++i));
			pMonsterInfo->setAttackOrder((AttackOrder)pResult->getInt(++i));
			pMonsterInfo->setMoral(pResult->getInt(++i));
			pMonsterInfo->setDelay(pResult->getInt(++i));
			pMonsterInfo->setAttackDelay(pResult->getInt(++i));
			pMonsterInfo->setSight(pResult->getInt(++i));
			pMonsterInfo->setMeleeRange(pResult->getInt(++i));
			pMonsterInfo->setMissileRange(pResult->getInt(++i));

			int nPortal    = pResult->getInt(++i);
			int nInvisible = pResult->getInt(++i);
			int nBat       = pResult->getInt(++i);

			pMonsterInfo->setRegenType(REGENTYPE_PORTAL, nPortal);
			pMonsterInfo->setRegenType(REGENTYPE_INVISIBLE, nInvisible);
			pMonsterInfo->setRegenType(REGENTYPE_BAT, nBat);

			pMonsterInfo->setMoveMode(pResult->getString(++i));
			pMonsterInfo->setAIType(pResult->getInt(++i));
			pMonsterInfo->parseEnhanceAttr(pResult->getString(++i));
			pMonsterInfo->setUnburrowChance(pResult->getInt(++i));
			pMonsterInfo->setMaster(pResult->getInt(++i)!=0);
			pMonsterInfo->setClanType(pResult->getInt(++i));
			//pMonsterInfo->setMonsterSummonInfo(pResult->getString(++i));
			pMonsterInfo->setDefaultEffects(pResult->getString(++i));
			pMonsterInfo->setChief(pResult->getInt(++i)!=0);
			pMonsterInfo->setNormalRegen(pResult->getInt(++i)!=0);
			pMonsterInfo->setHasTreasure(pResult->getInt(++i)!=0);
			pMonsterInfo->setMonsterClass(pResult->getInt(++i));
			pMonsterInfo->setSkullType(pResult->getInt(++i));

			addMonsterInfo(pMonsterInfo->getMonsterType(), pMonsterInfo);
		}

		// MonsterSummonInfo�� ���� �����Ѵ�.
		// �ϴ� ������ ������ load�� ���¿��� �ϱ� �����̴�. (�̸� ���� ������)
		pResult = pStmt->executeQuery(
			"SELECT MType, MonsterSummonInfo FROM MonsterInfo");

		while (pResult->next()) 
		{
			int i = 0;

			MonsterInfo* pMonsterInfo = m_MonsterInfos[ pResult->getInt(++i) ];
			Assert(pMonsterInfo!=NULL);

			pMonsterInfo->setMonsterSummonInfo(pResult->getString(++i));
		}
        cout << "[MonsterInfoManager] Loaded." << endl;

        cout << "[MonsterInfoManager] Loading Treasures..." << endl;
		clearTreasures();

		for (uint i=0; i<m_MaxMonsterType; i++)
		{
			MonsterInfo* pInfo = m_MonsterInfos[i];
			if (pInfo != NULL)
			{
				if (pInfo->hasTreasure())
				{
					string slayer_filename;
					string vampire_filename;
					string ousters_filename;

					if (pInfo->getMonsterClass() == 0 )
					{
//						slayer_filename  = g_pConfig->getProperty("HomePath") + "/data/" + pInfo->getHName() + ".slayer.bin";
//						vampire_filename = g_pConfig->getProperty("HomePath") + "/data/" + pInfo->getHName() + ".vampire.bin";
//						ousters_filename = g_pConfig->getProperty("HomePath") + "/data/" + pInfo->getHName() + ".ousters.bin";

						slayer_filename  = g_pConfig->getProperty("HomePath") + "/data/Class1.slayer.bin";
						vampire_filename = g_pConfig->getProperty("HomePath") + "/data/Class1.vampire.bin";
						ousters_filename = g_pConfig->getProperty("HomePath") + "/data/Class1.ousters.bin";
					}
					else
					{
						char buffer[10];
						sprintf(buffer, "Class%d", pInfo->getMonsterClass());
						slayer_filename  = g_pConfig->getProperty("HomePath") + "/data/" + buffer + ".slayer.bin";
						vampire_filename = g_pConfig->getProperty("HomePath") + "/data/" + buffer + ".vampire.bin";
						ousters_filename = g_pConfig->getProperty("HomePath") + "/data/" + buffer + ".ousters.bin";
					}

					TreasureList* pSlayerTreasureList = m_SlayerTreasureLists.getTreasure(slayer_filename);
					TreasureList* pVampireTreasureList = m_VampireTreasureLists.getTreasure(vampire_filename);
					TreasureList* pOustersTreasureList = m_OustersTreasureLists.getTreasure(ousters_filename);

					if (pSlayerTreasureList==NULL) 
					{
						//printf("Load - slayer_filename:%s\n", slayer_filename.c_str());
						pSlayerTreasureList = m_SlayerTreasureLists.loadTreasure(slayer_filename);
						Assert(pSlayerTreasureList!=NULL); 
					}

					if (pVampireTreasureList==NULL)
					{
						//printf("Load - vampire_filename:%s\n", vampire_filename.c_str());
						pVampireTreasureList = m_VampireTreasureLists.loadTreasure(vampire_filename);
						Assert(pVampireTreasureList!=NULL); 
					}
					
					if (pOustersTreasureList==NULL)
					{
						//printf("Load - ousters_filename:%s\n", ousters_filename.c_str());
						pOustersTreasureList = m_OustersTreasureLists.loadTreasure(ousters_filename);
						Assert(pOustersTreasureList!=NULL); 
					}

					pInfo->setSlayerTreasureList(pSlayerTreasureList);
					pInfo->setVampireTreasureList(pVampireTreasureList);
					pInfo->setOustersTreasureList(pOustersTreasureList);

					// �����Ѵ�.
					//cout << "MonsterType:" << pInfo->getMonsterType() 
					//	<< ",MonsterName:" << pInfo->getEName()
					//	<< ",SlayerTreasure:" << pInfo->getSlayerTreasureList()->getTreasures().size()
					//	<< ",VampireTreasure:" << pInfo->getVampireTreasureList()->getTreasures().size()
					//	<< endl;
				}
				else
				{
					//cout << "[NoTreasureFile] " << pInfo->getHName().c_str() << endl;
				}
			}
		}
        cout << "[MonsterInfoManager] Treasures Loaded." << endl;

		/*

		pResult = pStmt->executeQuery("SELECT SType, SlayerTreasure, VampireTreasure, HName FROM MonsterInfo GROUP BY SType");

		while (pResult->next())
		{
			int    SType            = 0;
			string slayer_treasure  = "";
			string vampire_treasure = "";
			string hname            = "";

			//slayer_treasure.reserve(100000);
			//vampire_treasure.reserve(50000);

			SType            = pResult->getInt(1);
			slayer_treasure  = pResult->getString(2);
			vampire_treasure = pResult->getString(3);
			hname            = pResult->getString(4);

			TreasureList* pSlayerTreasureList = new TreasureList;
			TreasureList* pVampireTreasureList = new TreasureList;

			const vector<MonsterType_t>& MTypeVector = getMonsterTypeBySprite(SType);
			for (uint i=0; i<MTypeVector.size(); i++)
			{
				int MType = MTypeVector[i];

				MonsterInfo* pMonsterInfo = (MonsterInfo*)getMonsterInfo(MType);

				if (i == 0)
				{
					pMonsterInfo->setSlayerTreasureList(pSlayerTreasureList);
					pMonsterInfo->setVampireTreasureList(pVampireTreasureList);
					pMonsterInfo->parseSlayerTreasureString(slayer_treasure);
					pMonsterInfo->parseVampireTreasureString(vampire_treasure);

					// ���Ͽ��� ����.
					//saveTreasure((string)(hname + ".slayer"), pSlayerTreasureList);
					//saveTreasure((string)(hname + ".vampire"), pVampireTreasureList);
				}
				else
				{
					pMonsterInfo->setSlayerTreasureList(pSlayerTreasureList);
					pMonsterInfo->setVampireTreasureList(pVampireTreasureList);
				}

				// �����Ѵ�.
				cout << "MonsterType:" << pMonsterInfo->getMonsterType() 
					<< ",MonsterName:" << pMonsterInfo->getEName()
					<< ",SlayerTreasure:" << pMonsterInfo->getSlayerTreasureList()->getTreasures().size()
					<< ",VampireTreasure:" << pMonsterInfo->getVampireTreasureList()->getTreasures().size()
					<< endl;
			}

			slayer_treasure.clear();
			vampire_treasure.clear();
		}

		*/

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	map<int, vector<SpriteType_t> >::iterator itr = m_MonsterClassMap.begin();
	map<int, vector<SpriteType_t> >::iterator endItr = m_MonsterClassMap.end();
/*
	for (; itr != endItr ; ++itr )
	{
		cout << "Class[" << itr->first << "] : ";
		copy(itr->second.begin(), itr->second.end(), ostream_iterator<SpriteType_t>(cout, ", " ));
		cout << endl;
	}
*/
	__END_DEBUG
	__END_CATCH
}


void MonsterInfoManager::reload (MonsterType_t monsterType) 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	bool bLoadAll = (monsterType==0);

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT MAX(MType) FROM MonsterInfo");

		StringStream sql;
		sql << "SELECT MType, SType, HName, EName, Level, STR, DEX, INTE, BSize, Exp, MColor, SColor, Align, AOrder, Moral, Delay, ADelay, Sight, MeleeRange, MissileRange, RegenPortal, RegenInvisible, RegenBat, MMode, AIType, Enhance, UnburrowChance, Master, ClanType, MonsterSummonInfo, DefaultEffects, NormalRegen FROM MonsterInfo";

		// ���� �� loading�ϴ°� �ƴ϶��� Ư�� MonsterType�� �����Ѵ�.
		if (!bLoadAll)
		{
			sql << " WHERE MType=" << monsterType;
		}

		pResult = pStmt->executeQuery(sql.toString().c_str());

		while (pResult->next()) 
		{
			int i = 0;

			int MType = pResult->getInt(++i);

			MonsterInfo* pMonsterInfo = (MonsterInfo*)getMonsterInfo(MType);

			if (pMonsterInfo!=NULL)
			{
				pMonsterInfo->setSpriteType(pResult->getInt(++i));
				pMonsterInfo->setHName(pResult->getString(++i));
				pMonsterInfo->setEName(pResult->getString(++i));
				pMonsterInfo->setLevel(pResult->getInt(++i));
				pMonsterInfo->setSTR(pResult->getInt(++i));
				pMonsterInfo->setDEX(pResult->getInt(++i));
				pMonsterInfo->setINT(pResult->getInt(++i));
				pMonsterInfo->setBodySize(pResult->getInt(++i));
				pMonsterInfo->setExp(pResult->getInt(++i));
				pMonsterInfo->setMainColor(pResult->getInt(++i));
				pMonsterInfo->setSubColor(pResult->getInt(++i));
				pMonsterInfo->setAlignment((MAlignment)pResult->getInt(++i));
				pMonsterInfo->setAttackOrder((AttackOrder)pResult->getInt(++i));
				pMonsterInfo->setMoral(pResult->getInt(++i));
				pMonsterInfo->setDelay(pResult->getInt(++i));
				pMonsterInfo->setAttackDelay(pResult->getInt(++i));
				pMonsterInfo->setSight(pResult->getInt(++i));
				pMonsterInfo->setMeleeRange(pResult->getInt(++i));
				pMonsterInfo->setMissileRange(pResult->getInt(++i));

				int nPortal    = pResult->getInt(++i);
				int nInvisible = pResult->getInt(++i);
				int nBat       = pResult->getInt(++i);

				pMonsterInfo->setRegenType(REGENTYPE_PORTAL, nPortal);
				pMonsterInfo->setRegenType(REGENTYPE_INVISIBLE, nInvisible);
				pMonsterInfo->setRegenType(REGENTYPE_BAT, nBat);

				pMonsterInfo->setMoveMode(pResult->getString(++i));
				pMonsterInfo->setAIType(pResult->getInt(++i));
				pMonsterInfo->parseEnhanceAttr(pResult->getString(++i));
				pMonsterInfo->setUnburrowChance(pResult->getInt(++i));
				pMonsterInfo->setMaster(pResult->getInt(++i)!=0);
				pMonsterInfo->setClanType(pResult->getInt(++i));
				pMonsterInfo->setMonsterSummonInfo(pResult->getString(++i));
				pMonsterInfo->setDefaultEffects(pResult->getString(++i));
				pMonsterInfo->setNormalRegen(pResult->getInt(++i)!=0);
			}
		}

		int startType = 0; 
		int endType   = m_MaxMonsterType;

		// ���� �� loading�ϴ°� �ƴ϶��� Ư�� MonsterType�� �����Ѵ�.
		if (!bLoadAll)
		{
			startType = monsterType;
			endType   = monsterType+1;
		}

/*		clearTreasures();

		for (int i=startType; i<endType; i++)
		{
			MonsterInfo* pInfo = m_MonsterInfos[i];
			if (pInfo != NULL)
			{
				if (pInfo->hasTreasure())
				{
					string slayer_filename  = g_pConfig->getProperty("HomePath") + "/data/" + pInfo->getHName() + ".slayer.bin";
					string vampire_filename = g_pConfig->getProperty("HomePath") + "/data/" + pInfo->getHName() + ".vampire.bin";
					string ousters_filename = g_pConfig->getProperty("HomePath") + "/data/" + pInfo->getHName() + ".ousters.bin";

					TreasureList* pSlayerTreasureList = m_SlayerTreasureLists.getTreasure(slayer_filename);
					TreasureList* pVampireTreasureList = m_VampireTreasureLists.getTreasure(vampire_filename);
					TreasureList* pOustersTreasureList = m_OustersTreasureLists.getTreasure(ousters_filename);

					if (pSlayerTreasureList==NULL) 
					{
						printf("Load - slayer_filename:%s\n", slayer_filename.c_str());

						pSlayerTreasureList = m_SlayerTreasureLists.loadTreasure(slayer_filename);
						Assert(pSlayerTreasureList!=NULL); 
					}

					if (pVampireTreasureList==NULL)
					{
						printf("Load - vampire_filename:%s\n", vampire_filename.c_str());
						
						pVampireTreasureList = m_VampireTreasureLists.loadTreasure(vampire_filename);
						Assert(pVampireTreasureList!=NULL); 
					}

					if (pOustersTreasureList==NULL)
					{
						printf("Load - ousters_filename:%s\n", ousters_filename.c_str());
						
						pOustersTreasureList = m_OustersTreasureLists.loadTreasure(ousters_filename);
						Assert(pOustersTreasureList!=NULL); 
					}

					pInfo->setSlayerTreasureList(pSlayerTreasureList);
					pInfo->setVampireTreasureList(pVampireTreasureList);
					pInfo->setOustersTreasureList(pOustersTreasureList);

					// �����Ѵ�.
//					cout << "MonsterType:" << pInfo->getMonsterType() 
//						<< ",MonsterName:" << pInfo->getEName()
//						<< ",SlayerTreasure:" << pInfo->getSlayerTreasureList()->getTreasures().size()
//						<< ",VampireTreasure:" << pInfo->getVampireTreasureList()->getTreasures().size()
//						<< endl;
				}
			}
		}
*/
		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_DEBUG
	__END_CATCH
}

void MonsterInfoManager::addMonsterInfo (MonsterType_t monsterType , MonsterInfo* pMonsterInfo) 
	throw(DuplicatedException , OutOfBoundException , Error)
{
	__BEGIN_TRY

	if (monsterType >= m_MaxMonsterType) 
	{
		cerr << "MonsterInfoManager::addMonsterInfo() : Out of bounds" << endl;
		throw OutOfBoundException();
	}
	
	if (m_MonsterInfos[monsterType] != NULL)
	{
		cerr << "MonsterInfoManager::addMonsterInfo() : Duplicated Exception" << endl;
		throw DuplicatedException();
	}

	m_MonsterInfos[monsterType] = pMonsterInfo;

	if (pMonsterInfo->isNormalRegen())
	{
		m_MonsterSpriteSet[pMonsterInfo->getSpriteType()].push_back(monsterType);
	}

	m_MonsterSpriteTypes[pMonsterInfo->getHName()] = pMonsterInfo->getSpriteType();

	if (pMonsterInfo->isChief())
	{
		m_ChiefMonster[pMonsterInfo->getHName()] = pMonsterInfo->getMonsterType();
	}

	if (pMonsterInfo->getMonsterClass() != 0 && pMonsterInfo->isNormalRegen() )
	{
		vector<SpriteType_t>& mList = m_MonsterClassMap[pMonsterInfo->getMonsterClass()];
		vector<SpriteType_t>::iterator itr = find_if(mList.begin(), mList.end(), bind2nd(greater_equal<int>(), pMonsterInfo->getSpriteType() ));
		if (itr == mList.end() || *itr != pMonsterInfo->getSpriteType() ) mList.insert(itr, pMonsterInfo->getSpriteType());
	}

	__END_CATCH
}

const MonsterInfo* MonsterInfoManager::getMonsterInfo (MonsterType_t monsterType) const 
	throw(NoSuchElementException , OutOfBoundException , Error)
{
	__BEGIN_TRY

	if (monsterType >= m_MaxMonsterType)
	{
		cerr << "MonsterInfoManager::getMonsterInfo() : Out of bounds" << endl;
		throw OutOfBoundException();
	}
	
	if (m_MonsterInfos[monsterType] == NULL)
	{
		cerr << "MonsterInfoManager::getMonsterInfo() : No Such Element Exception" << endl;
		throw NoSuchElementException();
	}

	// �ϴ� ������ �ѹ� üũ�� �Ǹ� [] �� �ᵵ �ȴ�.
	return m_MonsterInfos[monsterType]; 

	__END_CATCH
}

const vector<MonsterType_t>& MonsterInfoManager::getMonsterTypeBySprite(SpriteType_t spriteType) const
	throw(NoSuchElementException , OutOfBoundException , Error)
{
	__BEGIN_TRY

	if (m_MonsterSpriteSet[spriteType].empty())
	{
		cerr << "MonsterInfoManager::getMonsterTypeBySprite() : no such element exception" << (int)spriteType << endl;
		throw NoSuchElementException();
	}
	
	if (spriteType >= MAX_SPRITE_TYPE)
	{
		cerr << "MonsterInfoManager::getMonsterTypeBySprite() : out of bounds" << endl;
		throw OutOfBoundException();
	}

	return m_MonsterSpriteSet[spriteType];

	__END_CATCH
}

string MonsterInfoManager::getNameBySpriteType(SpriteType_t spriteType) const
{
	__BEGIN_TRY

	if (m_MonsterSpriteSet[spriteType].empty())
	{
		cerr << "MonsterInfoManager::getMonsterTypeBySprite() : no such element exception" << (int)spriteType << endl;
		throw NoSuchElementException();
	}
	
	if (spriteType >= MAX_SPRITE_TYPE)
	{
		cerr << "MonsterInfoManager::getMonsterTypeBySprite() : out of bounds" << endl;
		throw OutOfBoundException();
	}

	return m_MonsterInfos[m_MonsterSpriteSet[spriteType].front()]->getHName();

	__END_CATCH
}

SpriteType_t MonsterInfoManager::getSpriteTypeByName(const string& monsterName) const
	throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	map<string, SpriteType_t>::const_iterator itr = m_MonsterSpriteTypes.find(monsterName);
	
	if (itr==m_MonsterSpriteTypes.end())
	{
		//cerr << "MonsterInfoManager::getMonsterTypeBySprite() : no such element exception" << endl;
		//throw NoSuchElementException();

		return 0;
	}
	
	return itr->second;

	__END_CATCH
}

MonsterType_t MonsterInfoManager::getChiefMonsterTypeByName(const string& monsterName) const
	throw(NoSuchElementException , Error)
{
	__BEGIN_TRY

	map<string, SpriteType_t>::const_iterator itr = m_ChiefMonster.find(monsterName);
	
	if (itr==m_ChiefMonster.end())
	{
		//cerr << "MonsterInfoManager::getMonsterTypeBySprite() : no such element exception" << endl;
		//throw NoSuchElementException();

		return 0;
	}
	
	return itr->second;

	__END_CATCH
}

MonsterType_t MonsterInfoManager::getRandomMonsterByClass(int minClass, int maxClass )
{
	int totalCand = 0;
	for (int i = minClass; i <= maxClass; ++i )
	{
		totalCand += m_MonsterClassMap[i].size();
	}

	int value = rand()%totalCand;
	SpriteType_t Target;
	int index = minClass;

	while (true )
	{
		vector<SpriteType_t>& sList = m_MonsterClassMap[index];
		if (value >= sList.size() )
		{
			value -= sList.size();
			++index;
		}
		else
		{
			Target = sList[value];
			break;
		}
	}

	return getMonsterTypeBySprite(Target).front();
}

string MonsterInfoManager::toString () const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "MonsterInfoManager(";

	for (uint i = 0 ; i < m_MaxMonsterType ; i ++) 
	{
		if (m_MonsterInfos[i] == NULL) msg << "NULL";
		else                           msg << m_MonsterInfos[i]->toString();
	}

	msg << ")";
	return msg.toString();

	__END_CATCH
}

