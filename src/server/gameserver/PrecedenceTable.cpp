//////////////////////////////////////////////////////////////////////////////
// Filename    : PrecedenceTable.cpp
// Written by  : excel96
// Description : 
// "먹자" 방지를 위한 우선권 계산을 위한 클래스이다.
// 개별적인 몬스터 객체 안에 존재하다가, 몬스터가 죽거나 흡혈 당할 때가 
// 되면 플레이어가 아이템을 먹거나, 흡혈을 할 수 있는 정당한 권리를 가지고
// 있는지를 검사한다.
//////////////////////////////////////////////////////////////////////////////

#include "PrecedenceTable.h"
#include "Creature.h"
#include "StringStream.h"

//////////////////////////////////////////////////////////////////////////////
// class PrecedenceElement member methods
//////////////////////////////////////////////////////////////////////////////

PrecedenceElement::PrecedenceElement()
{
	m_Name     = "";
	m_PartyID  = -1;
	m_Damage   = 0;

	getCurrentTime(m_Deadline);
}

void PrecedenceElement::setNextTime(void)
{
	getCurrentTime(m_Deadline);
	m_Deadline.tv_sec += 30;
}

string PrecedenceElement::toString(void) const
{
	StringStream msg;
	msg << "PrecedenceElement("
		<< "Name:" << m_Name
		<< ",PartyID:" << m_PartyID
		<< ",Damage:" << m_Damage
		<< ")";
	return msg.toString();
}


//////////////////////////////////////////////////////////////////////////////
// class PrecedenceTable member methods
//////////////////////////////////////////////////////////////////////////////

PrecedenceTable::PrecedenceTable()
{
	m_FirstAttackerName    = "";
	m_FirstAttackerPartyID = 0;
	m_HostName             = "";
	m_HostPartyID          = 0;
	m_bComputeFlag         = false;
}

PrecedenceTable::~PrecedenceTable()
{
	// 크리쳐 맵을 비운다.
	hash_map<string, PrecedenceElement*>::iterator itr = m_CreatureMap.begin();
	for (; itr != m_CreatureMap.end(); itr++)
	{
		SAFE_DELETE(itr->second);
	}
	m_CreatureMap.clear();

	// 파티 맵을 비운다.
	hash_map<int, PrecedenceElement*>::iterator itr2 = m_PartyMap.begin();
	for (; itr2 != m_PartyMap.end(); itr2++)
	{
		SAFE_DELETE(itr2->second);
	}
	m_PartyMap.clear();
}
/*
void PrecedenceTable::addPrecedence(Creature* pCreature, int damage)
{
	Assert(pCreature != NULL);

	// 크리쳐 맵이 비어있다는 말은, 최초의 공격자라는 말이다.
	if (m_CreatureMap.empty())
	{
		// 선공자의 이름을 세팅해 주고...
		m_FirstAttackerName = pCreature->getName();

		// 크리쳐 맵에다 데이터를 추가한다.
		PrecedenceElement* pElement = new PrecedenceElement;
		pElement->setName(pCreature->getName());
		pElement->setPartyID(-1);
		pElement->setDamage(damage);
		pElement->setNextTime();
		m_CreatureMap[pCreature->getName()] = pElement;
	}
	else
	{
		hash_map<string, PrecedenceElement*>::iterator itr = m_CreatureMap.find(pCreature->getName());
		if (itr == m_CreatureMap.end())
		{
			// 이전에 공격을 하지 않았다면 데이터를 새로 생성해 준다. 
			PrecedenceElement* pElement = new PrecedenceElement;
			pElement->setName(pCreature->getName());
			pElement->setPartyID(-1);
			pElement->setDamage(damage);
			pElement->setNextTime();
			m_CreatureMap[pCreature->getName()] = pElement;
		}
		else
		{
			// 이전에 공격을 했다면 데이터를 갱신해 준다.
			PrecedenceElement* pElement = itr->second;
			pElement->setDamage(pElement->getDamage() + damage);
			pElement->setNextTime();
		}
	}

	// 파티에 관한 계산도 해준다.
	// 파티에 가입되어 있지 않다면 파티 ID가 0이다.
	// 결국 0의 값은 파티에 가입되어 있지 않은 자들이 가한 데미지의 값이다.
	int PartyID = pCreature->getPartyID();
	if (m_PartyMap.empty())
	{
		PrecedenceElement* pElement = new PrecedenceElement;
		pElement->setPartyID(PartyID);
		pElement->setDamage(damage);
		pElement->setNextTime();
		m_PartyMap[PartyID] = pElement;
	}
	else
	{
		hash_map<int, PrecedenceElement*>::iterator itr = m_PartyMap.find(PartyID);
		if (itr == m_PartyMap.end())
		{
			PrecedenceElement* pElement = new PrecedenceElement;
			pElement->setPartyID(PartyID);
			pElement->setDamage(damage);
			pElement->setNextTime();
			m_PartyMap[PartyID] = pElement;
		}
		else
		{
			PrecedenceElement* pElement = itr->second;
			pElement->setDamage(pElement->getDamage() + damage);
			pElement->setNextTime();
		}
	}
}
*/

void PrecedenceTable::addPrecedence(const string & Name, int PartyID, int damage)
{
	// 크리쳐 맵이 비어있다는 말은, 최초의 공격자라는 말이다.
	if (m_CreatureMap.empty())
	{
		// 선공자의 이름을 세팅해 주고...
		m_FirstAttackerName = Name;

		// 크리쳐 맵에다 데이터를 추가한다.
		PrecedenceElement* pElement = new PrecedenceElement;
		pElement->setName(Name);
		pElement->setPartyID(-1);
		pElement->setDamage(damage);
		pElement->setNextTime();
		m_CreatureMap[Name] = pElement;
	}
	else
	{
		hash_map<string, PrecedenceElement*>::iterator itr = m_CreatureMap.find(Name);
		if (itr == m_CreatureMap.end())
		{
			// 이전에 공격을 하지 않았다면 데이터를 새로 생성해 준다. 
			PrecedenceElement* pElement = new PrecedenceElement;
			pElement->setName(Name);
			pElement->setPartyID(-1);
			pElement->setDamage(damage);
			pElement->setNextTime();
			m_CreatureMap[Name] = pElement;
		}
		else
		{
			// 이전에 공격을 했다면 데이터를 갱신해 준다.
			PrecedenceElement* pElement = itr->second;
			pElement->setDamage(pElement->getDamage() + damage);
			pElement->setNextTime();
		}
	}

	// 파티에 관한 계산도 해준다.
	// 파티에 가입되어 있지 않다면 파티 ID가 0이다.
	// 결국 0의 값은 파티에 가입되어 있지 않은 자들이 가한 데미지의 값이다.
//	int PartyID = PartyID;
	if (m_PartyMap.empty())
	{
		PrecedenceElement* pElement = new PrecedenceElement;
		pElement->setPartyID(PartyID);
		pElement->setDamage(damage);
		pElement->setNextTime();
		m_PartyMap[PartyID] = pElement;
	}
	else
	{
		hash_map<int, PrecedenceElement*>::iterator itr = m_PartyMap.find(PartyID);
		if (itr == m_PartyMap.end())
		{
			PrecedenceElement* pElement = new PrecedenceElement;
			pElement->setPartyID(PartyID);
			pElement->setDamage(damage);
			pElement->setNextTime();
			m_PartyMap[PartyID] = pElement;
		}
		else
		{
			PrecedenceElement* pElement = itr->second;
			pElement->setDamage(pElement->getDamage() + damage);
			pElement->setNextTime();
		}
	}

	// 다시 계산하도록 하기 위해서.. by sigi. 2002.10.14
	m_bComputeFlag = false;
}

void PrecedenceTable::heartbeat(const Timeval& currentTime)
{
	hash_map<string, PrecedenceElement*>::iterator c_before = m_CreatureMap.end();
	hash_map<string, PrecedenceElement*>::iterator c_current = m_CreatureMap.begin();

	while (c_current != m_CreatureMap.end())
	{
		PrecedenceElement* pElement = c_current->second;
		Assert(pElement != NULL);

		if (pElement->getDeadline() < currentTime)
		{
			if (c_before == m_CreatureMap.end())
			{
				m_CreatureMap.erase(c_current);
				c_current = m_CreatureMap.begin();
			}
			else
			{
				m_CreatureMap.erase(c_current);
				c_current = c_before;
				c_current++;
			}
		}
		else
		{
			c_before = c_current++;
		}
	}

	hash_map<string, PrecedenceElement*>::iterator p_before = m_CreatureMap.end();
	hash_map<string, PrecedenceElement*>::iterator p_current = m_CreatureMap.begin();

	while (p_current != m_CreatureMap.end())
	{
		PrecedenceElement* pElement = p_current->second;
		Assert(pElement != NULL);

		if (pElement->getDeadline() < currentTime)
		{
			if (p_before == m_CreatureMap.end())
			{
				m_CreatureMap.erase(p_current);
				p_current = m_CreatureMap.begin();
			}
			else
			{
				m_CreatureMap.erase(p_current);
				p_current = p_before;
				p_current++;
			}
		}
		else
		{
			p_before = p_current++;
		}
	}
}

void PrecedenceTable::compute(void)
{
	// 이미 계산했으면 안한다. by sigi. 2002.10.14
	if (m_bComputeFlag)
		return;

	int    MaxDamage           = 0;
	string MaxDamageName       = "";
	string SecondDamageName    = "";
	int    MaxDamagePartyID    = 0;
	int    SecondDamagePartyID = 0;

	Damage_t TotalDamage = 0;

	// 먼저 크리쳐 맵을 검색한다.
	hash_map<string, PrecedenceElement*>::const_iterator itr = m_CreatureMap.begin();
	for (; itr != m_CreatureMap.end(); itr++)
	{
		PrecedenceElement* pElement = itr->second;
		Assert(pElement != NULL);

		if (MaxDamage < pElement->getDamage())
		{
			if (MaxDamageName == "")
			{
				MaxDamageName = pElement->getName();
				MaxDamage     = pElement->getDamage();
			}
			else
			{
				SecondDamageName = MaxDamageName;
				MaxDamageName    = pElement->getName();
				MaxDamage        = pElement->getDamage();
			}
		}

		TotalDamage += pElement->getDamage();
	}

	m_TotalDamage = TotalDamage;

	if (MaxDamageName != "")
	{
		// 최고의 데미지를 준 자가 선공자라면,
		// 40+20 = 60 이 되어 주인이 된다.
		if (MaxDamageName == m_FirstAttackerName)
		{
			m_HostName = MaxDamageName;
		}
		// 최대 데미지를 준 자가 선공자가 아니라면,
		// 두번째로 데미지를 많이 준 자가, 선공자일 경우 30+20이 되어 주인이 된다.
		// 두번째로 데미지를 많이 준 자가 선공자가 아니라면, 
		// 최대 데미지를 준 자가 주인이 된다.
		else
		{
			if (SecondDamageName != "" && SecondDamageName == m_FirstAttackerName)
			{
				m_HostName = SecondDamageName;
			}
			else
			{
				m_HostName = MaxDamageName;
			}
		}
	}
	else
	{
		// 최대 데미지를 준 자가 없을 리는 없겠지만,
		// 혹시라도 그런 경우가 있다면 선공자를 주인으로 한다.
		m_HostName = m_FirstAttackerName;
	}

	// 파티에 관한 정보도 계산해 주어야 한다.
	// 파티 정보 계산에 있어서 유의할 점은 파티 ID가 0인 상태, 
	// 즉 파티에 가입되어 있지 않은 자들의 데미지도 같이 계산한다는 점이다.
	// 만일 최대 데미지를 입힌 파티ID가 0이라면, 즉 파티에 가입되어 있지 않은
	// 사람들이 최대 데미지를 입혔다면, HostPartyID가 0이 된다.
	// 이 경우에는 파티에 가입되어 있지 않은 사람들이 모두 권리를 가져서는 곤란하다.
	// 그러므로 canLoot나 canDrainBlood에서 파티 ID가 0이 아닌지를 검사해야 할 것이다.
	MaxDamage        = 0;
	MaxDamagePartyID = -1;
	SecondDamagePartyID    = -1;

	hash_map<int, PrecedenceElement*>::const_iterator itr2 = m_PartyMap.begin();
	for (; itr2 != m_PartyMap.end(); itr2++)
	{
		PrecedenceElement* pElement = itr2->second;
		Assert(pElement != NULL);

		if (MaxDamage < pElement->getDamage())
		{
			if (MaxDamagePartyID == -1)
			{
				MaxDamagePartyID = pElement->getPartyID();
				MaxDamage        = pElement->getDamage();
			}
			else
			{
				SecondDamagePartyID = MaxDamagePartyID;
				MaxDamagePartyID    = pElement->getPartyID();
				MaxDamage           = pElement->getDamage();
			}
		}
	}

	if (MaxDamagePartyID != -1)
	{
		// 최고의 데미지를 준 파티가 선공 파티라면,
		// 40+20 = 60 이 되어 주인이 된다.
		if (MaxDamagePartyID == m_FirstAttackerPartyID)
		{
			m_HostPartyID = MaxDamagePartyID;
		}
		// 최대 데미지를 준 파티가 선공자가 아니라면,
		// 두번째로 데미지를 많이 준 파티가, 선공파티일 경우 30+20이 되어 주인이 된다.
		// 두번째로 데미지를 많이 준 파티가 선공파티가 아니라면, 
		// 최대 데미지를 준 파티가 주인이 된다.
		else
		{
			if (SecondDamagePartyID != -1 && SecondDamagePartyID == m_FirstAttackerPartyID)
			{
				m_HostPartyID = SecondDamagePartyID;
			}
			else
			{
				m_HostPartyID = MaxDamagePartyID;
			}
		}
	}
	else
	{
		// 최대 데미지를 준 자가 없을 리는 없겠지만,
		// 혹시라도 그런 경우가 있다면 선공자를 주인으로 한다.
		m_HostPartyID = m_FirstAttackerPartyID;
	}

	m_bComputeFlag = true;
}

bool PrecedenceTable::canLoot(Creature* pCreature) const
{
	// 우선권을 가진 자라면 루트할 수 있다.
	if (m_HostName == pCreature->getName()) return true;

	// 우선권을 가진 파티에 가입되어 있다면 루트할 수 있다.
	int PartyID = pCreature->getPartyID();
	if (PartyID != 0 && m_HostPartyID == PartyID) return true;

	return false;
}

bool PrecedenceTable::canDrainBlood(Creature* pCreature) const
{
	// 우선권을 가진 자라면 루트할 수 있다.
	if (m_HostName == pCreature->getName()) return true;

	// 우선권을 가진 파티에 가입되어 있다면 루트할 수 있다.
	int PartyID = pCreature->getPartyID();
	if (PartyID != 0 && m_HostPartyID == PartyID) return true;

	return false;
}

bool PrecedenceTable::canGainRankExp(Creature* pCreature) const
{
	// 몬스터가 받은 데미지의 총합에서 1/4을 초과한 만큼 데미지를 줬다면 계급 경험치를 얻을 수 있다.
	hash_map<string, PrecedenceElement*>::const_iterator itr = m_CreatureMap.find( pCreature->getName() );
	if ( itr == m_CreatureMap.end() )
		return false;

	return ( m_TotalDamage >> 2 ) < itr->second->getDamage();
}

double PrecedenceTable::getDamagePercent(const string& Name, int PartyID) const
{
	if ( m_TotalDamage == 0 )
		return 0.0;

	double ownDamage = 0.0;
	hash_map<string, PrecedenceElement*>::const_iterator itr = m_CreatureMap.find(Name);
	if ( itr != m_CreatureMap.end() )
	{
		ownDamage = (double)(itr->second->getDamage());
	}

	double partyDamage = 0.0;
	if ( PartyID != 0 )
	{
		hash_map<int, PrecedenceElement*>::const_iterator itr = m_PartyMap.find(PartyID);
		if ( itr != m_PartyMap.end() )
		{
			partyDamage = (double)(itr->second->getDamage());
		}
	}

	double maxDamage = ( ownDamage > partyDamage ? ownDamage : partyDamage );

	return maxDamage / (double)m_TotalDamage;
}

string PrecedenceTable::toString(void) const
{
	StringStream msg;
	msg << "PrecedenceTable("
		<< "FirstAttackerName:" << m_FirstAttackerName
		<< ",FirstAttackerPartyID:" << m_FirstAttackerPartyID
		<< ",HostName:" << m_HostName
		<< ",HostPartyID:" << m_HostPartyID
		<< ",ComputeFlag:" << m_bComputeFlag;

	msg << "\n,CreatureMap:\n";

	hash_map<string, PrecedenceElement*>::const_iterator itr1 = m_CreatureMap.begin();
	for (; itr1 != m_CreatureMap.end(); itr1++)
	{
		msg << itr1->second->toString() << ",";
	}

	msg << "\n,PartyMap:\n";

	hash_map<int, PrecedenceElement*>::const_iterator itr2 = m_PartyMap.begin();
	for (; itr2 != m_PartyMap.end(); itr2++)
	{
		msg << itr2->second->toString() << ",";
	}

	msg << ")";

	return msg.toString();
}
